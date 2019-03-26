#ifndef PATHTRACER_H_
#define PATHTRACER_H_

#include <sstream>
#include <iomanip>
#include <cmath>
#include <random>
#include <chrono>
#include <functional>

#include "../Cameras/camera.h"
#include "../World/scene.h"
#include "../Cameras/buffer.h"
#include "../Data Structures/onb.h"
constexpr auto PI_VALUE = 3.14159265359f;

class PathTracer
{
public:

	PathTracer( Camera &camera,
               const Scene &scene,
               const glm::vec3 background_color,
               Buffer &buffer, int samples, int depth );

    void integrate( void );

private:

	Ray getNewRay(IntersectionRecord interc);

    const Camera &camera_;

    const Scene &scene_;

    glm::dvec3 background_color_;

    Buffer &buffer_;

	int samples_;

	int max_depth_;

	glm::vec3 L(const Ray &ray, int depth);

	std::mt19937_64 random_generator_;
};

#endif /* PATHTRACER_H_ */

