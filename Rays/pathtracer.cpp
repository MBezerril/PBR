#include "pathtracer.h"

PathTracer::PathTracer(Camera &camera,
	const Scene &scene,
	const glm::vec3 background_color,
	Buffer &buffer, int samples, int depth) :
	camera_(camera),
	scene_(scene),
	background_color_{ background_color },
	buffer_(buffer),
	samples_(samples),
	max_depth_(depth)
{
}

void PathTracer::integrate(void) {
	IntersectionRecord intersection_record;
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::uniform_real_distribution<float> distribuition(0.0f, 1.0f);
	std::mt19937_64 generator(seed);
	// Image space origin (i.e. x = 0 and y = 0) at the top left corner.

	// Loops over image rows
	for (std::size_t y = 0; y < buffer_.v_resolution_; y++) {
		std::stringstream progress_stream;
		progress_stream << "\r  progress .........................: "
			<< std::fixed << std::setw(6)
			<< std::setprecision(2)
			<< 100.0 * y / (buffer_.v_resolution_ - 1)
			<< "%";

		std::clog << progress_stream.str();

		// Loops over image columns
		for (std::size_t x = 0; x < buffer_.h_resolution_; x++) {
			for (int w = 0; w < samples_; w++) {
				intersection_record.t_ = std::numeric_limits< double >::max();

				auto v = distribuition(generator);
				auto h = distribuition(generator);
				while (v == 1.0f)
					v = distribuition(generator);
				while (h == 1.0f)
					h = distribuition(generator);

				Ray ray{ camera_.getWorldSpaceRay(glm::vec2{ x + v, y + h }) };

				if (scene_.intersect(ray, intersection_record)) {
					//buffer_.buffer_data_[x][y] = glm::vec3{ 1.0f, 0.0f, 0.0f };
					buffer_.buffer_data_[x][y] += L(ray, 0);
				}
				else {
					break;
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
	glm::vec3 direction = glm::normalize(glm::vec3(glm::sin(theta)*glm::cos(phi), glm::sin(theta)*glm::sin(phi), glm::cos(theta)));
	direction = onb.getBasisMatrix() * direction;
	return Ray(interc.position_ + (interc.normal_*0.001f), direction);
}


glm::vec3 PathTracer::L(const Ray & ray, int depth) {
	glm::vec3 Lo = glm::vec3(0, 0, 0);
	IntersectionRecord intersection_record;
	if (depth < max_depth_) {
		intersection_record.t_ = std::numeric_limits< double >::max();
		if (scene_.intersect(ray, intersection_record)) {
			Ray refl_ray = getNewRay(intersection_record);
			float cossin_ = glm::dot(intersection_record.normal_, refl_ray.direction_);
			if (cossin_ < 0) {
				cossin_ = -cossin_;
				refl_ray.direction_ = -refl_ray.direction_;
			}
			Lo = intersection_record.emitance_ + (2.0f * PI_VALUE * intersection_record.color_ * L(refl_ray, ++depth) * cossin_);
		}
	}
	return Lo;
}