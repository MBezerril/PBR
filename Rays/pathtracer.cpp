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

{}


void PathTracer::integrate(void) {
	IntersectionRecord intersection_record;

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

				Ray ray{ camera_.getWorldSpaceRay(glm::vec2{ x + 0.5f, y + 0.5f }) };

				if (scene_.intersect(ray, intersection_record)) {
					//buffer_.buffer_data_[x][y] = glm::vec3{ 1.0f, 0.0f, 0.0f };
					buffer_.buffer_data_[x][y] += L(ray, 0);
				}
			}
			buffer_.buffer_data_[x][y] /= samples_;
		}
	}

	std::clog << std::endl;
}

Ray PathTracer::getNewRay(glm::vec3 orig) {
	int r1 = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
	int r2 = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
	float theta = glm::acos(1 - r1);
	float phi = 2 * PI_VALUE * r2;
	glm::vec3 direction = glm::vec3(glm::sin(theta)*glm::cos(phi), glm::sin(theta)*glm::sin(phi), glm::cos(theta));
	return Ray(orig, direction);
}



glm::vec3 PathTracer::L(const Ray & ray, int depth) {
	glm::vec3 Lo = glm::vec3(0, 0, 0);
	IntersectionRecord intersection_record;
	if (depth < max_depth_) {
		intersection_record.t_ = std::numeric_limits< double >::max();
		if (scene_.intersect(ray, intersection_record)) {
			Ray refl_ray = getNewRay(intersection_record.position_);
			Lo = intersection_record.radiance_ + 2.0f * PI_VALUE * intersection_record.color_ * L(refl_ray, depth++) * glm::dot(intersection_record.normal_, refl_ray.direction_);
		}
	}
	return Lo;
}