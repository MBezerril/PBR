#ifndef PATHTRACER_H_
#define PATHTRACER_H_

#include <sstream>
#include <iomanip>
#include <cmath>
#include <random>
#include <chrono>
#include <algorithm> 
#include <functional>

#include "../Cameras/camera.h"
#include "../World/scene.h"
#include "../Cameras/buffer.h"
#include "../Data Structures/onb.h"
#include "../Data Structures/bvhNode.h"

constexpr auto PI_VALUE = 3.14159265359f;

class PathTracer
{
public:

	PathTracer(Camera& camera,
		const Scene& scene,
		const glm::vec3 background_color,
		Buffer& buffer, int samples, int depth);

	void integrate(void);

	void integrateAcelerated(void);

private:

	Ray getNewRay(IntersectionRecord interc);

	const Camera& camera_;

	const Scene& scene_;

	std::shared_ptr<bvhNode> root_;

	glm::dvec3 background_color_;

	Buffer& buffer_;

	int samples_;

	int max_depth_;

<<<<<<< HEAD
	glm::vec3 L(const Ray& ray, int depth);

	glm::vec3 LBVH( const Ray& ray, int depth);

	void constructBVH(std::shared_ptr<bvhNode> &node, int start, int end, std::vector<int> objects, int depth);

	bool bvhIntersect(std::shared_ptr<bvhNode> node, const Ray& ray, IntersectionRecord& intersection_record) const;
=======
	glm::vec3 L(const Ray &ray, int depth);
>>>>>>> c68eefe950ec4d3664fc741270b86dd9f5539a98
};

#endif /* PATHTRACER_H_ */

