#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#define EPSILON 0.000001

#include <glm/glm.hpp>
#include "primitive.h"
#include "../Rays/intersection_record.h"
#include "../Rays/ray.h"

class Triangle : public Primitive
{
public:

	Triangle(void);

	Triangle(glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3, Material *mat);

	//void Intersect(TriAccel &acc, Ray &ray, Hit &hit);
	bool intersect(const Ray &ray,
		IntersectionRecord &intersection_record) const;

	glm::vec3 points[3] = { { 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f } };

private:

	static const float kIntersectionTestEpsilon_;
};

#endif /* TRIANGLE_H_ */

