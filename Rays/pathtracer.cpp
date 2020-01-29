#include "pathtracer.h"

PathTracer::PathTracer(Camera& camera,
	const Scene& scene,
	const glm::vec3 background_color,
	Buffer& buffer, int samples, int depth) :
	camera_(camera),
	scene_(scene),
	background_color_{ background_color },
	buffer_(buffer),
	samples_(samples),
	max_depth_(depth)
{
	root_ = nullptr;
}

void PathTracer::integrate(void) {
	// Image space origin (i.e. x = 0 and y = 0) at the top left corner.
	// Loops over image rows
#pragma omp parallel for schedule(dynamic,1)
	for(int y = 0; y < buffer_.v_resolution_; y++) {
		IntersectionRecord intersection_record;
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::uniform_real_distribution<float> distribuition(0.0f, 1.0f);
		std::mt19937_64 generator(seed);
		std::stringstream progress_stream;
		progress_stream << "\r  progress .........................: "
			<< std::fixed << std::setw(6)
			<< std::setprecision(2)
			<< 100.0 * y / (buffer_.v_resolution_ - 1)
			<< "%";

		std::clog << progress_stream.str();

		// Loops over image columns
		for(std::size_t x = 0; x < buffer_.h_resolution_; x++) {
			for(int w = 0; w < samples_; w++) {
				intersection_record.t_ = std::numeric_limits< double >::max();

				auto v = distribuition(generator);
				auto h = distribuition(generator);
				while(v == 1.0f)
					v = distribuition(generator);
				while(h == 1.0f)
					h = distribuition(generator);

				Ray ray{ camera_.getWorldSpaceRay(glm::vec2{ x + v, y + h }) };

				if(scene_.intersect(ray, intersection_record)) {
					//buffer_.buffer_data_[x][y] = glm::vec3{ 1.0f, 0.0f, 0.0f };
					buffer_.buffer_data_[x][y] += L(ray, 0);
				}
			}
			buffer_.buffer_data_[x][y] /= samples_;
		}
	}

	std::clog << std::endl;
}

void PathTracer::integrateAcelerated(void) {
	// Image space origin (i.e. x = 0 and y = 0) at the top left corner.
	// Loops over image rows
	if(root_ == nullptr) {
		std::vector<int> objstIndexes;
		for(int i = 0; i < scene_.primitives_.size(); i++) objstIndexes.push_back(i);
		root_ = std::make_shared<bvhNode>();
		constructBVH(root_, 0, scene_.primitives_.size() - 1, objstIndexes, 0);
	}
#pragma omp parallel for schedule(dynamic,1)
	for(int y = 0; y < buffer_.v_resolution_; y++) {
		IntersectionRecord intersection_record;
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::uniform_real_distribution<float> distribuition(0.0f, 1.0f);
		std::mt19937_64 generator(seed);
		std::stringstream progress_stream;
		progress_stream << "\r  progress .........................: "
			<< std::fixed << std::setw(6)
			<< std::setprecision(2)
			<< 100.0 * y / (buffer_.v_resolution_ - 1)
			<< "%";

		std::clog << progress_stream.str();

		// Loops over image columns
		for(std::size_t x = 0; x < buffer_.h_resolution_; x++) {
			for(int w = 0; w < samples_; w++) {
				intersection_record.t_ = std::numeric_limits< double >::max();

				auto v = distribuition(generator);
				auto h = distribuition(generator);
				while(v == 1.0f)
					v = distribuition(generator);
				while(h == 1.0f)
					h = distribuition(generator);

				Ray ray{ camera_.getWorldSpaceRay(glm::vec2{ x + v, y + h }) };
				//if(y == 300 && x == 50 && w == 0) system("pause");
				if(bvhIntersect(root_, ray, intersection_record)) {
					//buffer_.buffer_data_[x][y] = glm::vec3{ 1.0f, 0.0f, 0.0f };
					buffer_.buffer_data_[x][y] += LBVH(ray, 0);
				}
			}
			buffer_.buffer_data_[x][y] /= samples_;
		}
	}

	std::clog << std::endl;
}

Ray PathTracer::getNewRay(IntersectionRecord interc) {
	ONB onb;
	onb.setFromV(interc.normal_);
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	auto real_rand = std::bind(std::uniform_real_distribution<double>(0, 1), std::mt19937_64(seed));
	float r1 = real_rand();
	float r2 = real_rand();
	float theta = glm::acos(1 - r1);
	float phi = 2 * PI_VALUE * r2;
	glm::vec3 direction = glm::normalize(glm::vec3(glm::sin(theta) * glm::cos(phi), glm::sin(theta) * glm::sin(phi), glm::cos(theta)));
	direction = onb.getBasisMatrix() * direction;
	return Ray(interc.position_ + (interc.normal_ * 0.001f), direction);
}


glm::vec3 PathTracer::L(const Ray & ray, int depth) {
	glm::vec3 Lo = glm::vec3(0, 0, 0);
	IntersectionRecord intersection_record;
	if(depth < max_depth_) {
		intersection_record.t_ = std::numeric_limits< double >::max();
		if(scene_.intersect(ray, intersection_record)) {
			Ray refl_ray = getNewRay(intersection_record);
			float cossin_ = glm::dot(intersection_record.normal_, refl_ray.direction_);
			if(cossin_ < 0) {
				cossin_ = -cossin_;
				refl_ray.direction_ = -refl_ray.direction_;
			}
			Lo = intersection_record.emitance_ + (2.0f * PI_VALUE * intersection_record.color_ * L(refl_ray, ++depth) * cossin_);
		}
	}
	return Lo;
}

glm::vec3 PathTracer::LBVH(const Ray & ray, int depth) {
	glm::vec3 Lo = glm::vec3(0, 0, 0);
	IntersectionRecord intersection_record;
	if(depth < max_depth_) {
		intersection_record.t_ = std::numeric_limits< double >::max();
		if(bvhIntersect(root_, ray, intersection_record)) {
			Ray refl_ray = getNewRay(intersection_record);
			float cossin_ = glm::dot(intersection_record.normal_, refl_ray.direction_);
			if(cossin_ < 0) {
				cossin_ = -cossin_;
				refl_ray.direction_ = -refl_ray.direction_;
			}
			Lo = intersection_record.emitance_ + (2.0f * PI_VALUE * intersection_record.color_ * LBVH(refl_ray, ++depth) * cossin_);
		}
	}
	return Lo;
}

void PathTracer::constructBVH(std::shared_ptr<bvhNode> & node, int start, int end, std::vector<int> objects, int depth) {
	if(end - start > 0) {
		//Select the axis to be used on sorting function 
		//TODO revisar método de divisão, está criando multiplas caixas identicas -3 -3 -3 -> 3 3 3 
		auto sortAxis = [&](int x1, int x2) {return scene_.primitives_[x1]->getCenter()[depth % 3] < scene_.primitives_[x2]->getCenter()[depth % 3]; };
		//The vector objects it's the vector that contains the index of the objects to be ordered or accessed
		std::sort(objects.begin() + start, objects.begin() + end, sortAxis);
		//int xmax = scene_.primitives_[0]->getCenter().x, ymax = scene_.primitives_[0]->getCenter().y, zmax = scene_.primitives_[0]->getCenter().z;
		//int xmin = xmax, ymin = ymax, zmin = zmax;
		////get the maximum and minimum value of this node and create a new bouding box
		node->boudingBox = scene_.primitives_[start]->boundingBox;
		for(int i = start; i <= end; i++) {
			node->boudingBox = node->boudingBox + scene_.primitives_[i]->boundingBox;
		}
		node->leftChild = std::make_shared<bvhNode>();
		node->rightChild = std::make_shared<bvhNode>();
		//TODO Revisar divisão e arredondamento
		constructBVH(node->leftChild, start, static_cast<int>((start + end) / 2.0f), objects, depth + 1);
		constructBVH(node->rightChild, static_cast<int>(((start + end) / 2.0f) + 0.5f), end, objects, depth + 1);
	}
	else {
		//If it's the last level, set the leaves and return;
		node->child = start;
		node->isLeaf = true;
		node->boudingBox = scene_.primitives_[start]->boundingBox;
		return;
	}

}

/*If doesn't colides with the node, so return false
 * We dont need to know the distance in the bouding box, only in the colisions with the objects*/
bool PathTracer::bvhIntersect(std::shared_ptr<bvhNode> node, const Ray & ray, IntersectionRecord & intersection_record) const {
	if(!node->boudingBox.intersect(ray)) return false;
	//creating the intersection record to each child, so we can compare wich one (if both colides) it's closer
	IntersectionRecord tmp_intersection;
	//intersection_record_left.t_ = std::numeric_limits< double >::max();
	//intersection_record_right.t_ = std::numeric_limits< double >::max();
	bool tmp_intersection_result;
	if(node->isLeaf) {
		if(scene_.primitives_[node->child]->intersect(ray, tmp_intersection)) {
			if(tmp_intersection.t_ > 0.0) {
				intersection_record = tmp_intersection;
				return true;
			}
			else return false;
		}
		else {
			return false;
		}
	}
	else {
		//Call the intersection to the childs nodes
		IntersectionRecord intersection_record_left, intersection_record_right;
		bool rightIntersection, leftIntersection;
		leftIntersection = bvhIntersect(node->leftChild, ray, intersection_record_left);
		rightIntersection = bvhIntersect(node->rightChild, ray, intersection_record_right);
		//Return false if there wasn't intersection or both aren't greater than 0
		if(!leftIntersection && !rightIntersection || (intersection_record_left.t_ < 0.0 && intersection_record_right.t_ < 0.0)) return false;
		//both intersections
		if(leftIntersection && rightIntersection) {
			//both greater than 0
			if(intersection_record_left.t_ > 0.0 && intersection_record_right.t_ > 0.0) {
				intersection_record_left.t_ < intersection_record_right.t_ ? intersection_record = intersection_record_left : intersection_record = intersection_record_right;
			}
			//only one greater
			else {
				if(intersection_record_left.t_ < 0.0) intersection_record = intersection_record_right;
				else intersection_record = intersection_record_left;
			}
			return true;
		}
		//One or the other collided
		//Check also if the distance is positive, if not, return false
		else if(leftIntersection && intersection_record_left.t_ > 0.0) {
			intersection_record = intersection_record_left;
			return true;
		}
		else if(rightIntersection && intersection_record_right.t_ > 0.0) {
			intersection_record = intersection_record_right;
			return true;
		}
		return false;
	}
}



/*
	Caso o inicio e o fio esteja a 1 unidade de diferença:
		start é a folha da esquerda
		end é a folha da direita

	Crio um nó raiz, se tiver vazio:
		ordeno o vetor de objetos em x
		pego o maior xyz e o menor xyz de todo o array
		crio um boxvolume pra começar o primeiro loop
	Caso contrário:
		ordeno o vetor de objetos em (0-x, 1-y, 2-z)[Profundidade da camada % 3]
		pego o maior xyz e o menor xyz do inicio até o meio do array
		Crio um novo bvhNode
		pego o maior xyz e o menor xyz do meio do array até o fim
		crio um novo bvhNode
		Coloc os dois novos bvhNode como filhos do nó atual
		Chamo o constructBVH pra cada nó

	*/