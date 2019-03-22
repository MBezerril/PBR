#include "triangle.h"
#define TEST_CULL
Triangle::Triangle(void) {}

Triangle::Triangle(glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3, Material *mat) {
	points[0] = vert1;
	points[1] = vert2;
	points[2] = vert3;
	obj_mat = mat;
}

bool Triangle::intersect(const Ray & ray, IntersectionRecord & intersection_record) const {
	glm::vec3 edge1, edge2, tvec, pvec, qvec;
	double det, inv_det, t, u, v;

	edge1 = points[1] - points[0];
	edge2 = points[2] - points[0];

	pvec = glm::cross(ray.direction_, edge2);
	det = glm::dot(edge1, pvec);

	if (det > -EPSILON && det < EPSILON)
		return	false;
	inv_det = 1.0 / det;
	/*	calculate distance from vert0 to ray origin */
	tvec = ray.origin_ - points[0];
	/*	calculate U	parameter and test bounds */
	u = glm::dot(tvec, pvec) * inv_det;
	if (u <	0.0 || u > 1.0)
		return	false;

	/* prepare to test V parameter */
	qvec = glm::cross(tvec, edge1);

	/* calculate V parameter and test bounds */
	v = glm::dot(ray.direction_, qvec) * inv_det;
	if (v < 0.0 || u + v > 1.0)	return false;

	/* calculate t, ray intersects triangle */
	t = glm::dot(edge2, qvec) * inv_det;
	intersection_record.t_ = t;
	intersection_record.position_ = ray.origin_ + intersection_record.t_ * ray.direction_;
	intersection_record.normal_ = glm::normalize(intersection_record.position_ - tvec);
	intersection_record.color_ = getBRDF(intersection_record);
	intersection_record.radiance_ = getEmitance(intersection_record);

	return true;
}



