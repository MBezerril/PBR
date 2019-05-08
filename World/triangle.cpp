#include "triangle.h"
#define TEST_CULL
Triangle::Triangle(void) {}

Triangle::Triangle(glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3, Material* mat) {
	points[0] = vert1;
	points[1] = vert2;
	points[2] = vert3;
	obj_mat = mat;
	float xmin, ymin, zmin;
	float xmax, ymax, zmax;
	//Getting the minimum XYZ to create the boudingBox
	xmin = vert1.x < vert2.x ? vert1.x : vert2.x;
	ymin = vert1.y < vert2.y ? vert1.y : vert2.y;
	zmin = vert1.z < vert2.y ? vert1.z : vert2.z;
	xmin = vert3.x < xmin ? vert3.x : xmin;
	ymin = vert3.y < ymin ? vert3.y : ymin;
	zmin = vert3.z < zmin ? vert3.z : zmin;
	//Getting the maximum XYZ to create the bouding box
	xmax = vert1.x > vert2.x ? vert1.x : vert2.x;
	ymax = vert1.y > vert2.y ? vert1.y : vert2.y;
	zmax = vert1.z > vert2.z ? vert1.z : vert2.z;
	xmax = vert3.x > xmax ? vert3.x : xmax;
	ymax = vert3.y > ymax ? vert3.y : ymax;
	zmax = vert3.z > zmax ? vert3.z : zmax;
	boundingBox = BoxVolume(glm::vec3{ xmin, ymin, zmin }, glm::vec3{ xmax, ymax, zmax });
}

bool Triangle::intersect(const Ray& ray, IntersectionRecord& intersection_record) const {
	glm::vec3 edge1, edge2, tvec, pvec, qvec;
	double det, inv_det, t, u, v;

	edge1 = points[1] - points[0];
	edge2 = points[2] - points[0];

	pvec = glm::cross(ray.direction_, edge2);
	det = glm::dot(edge1, pvec);

	if(det > -EPSILON && det < EPSILON)
		return	false;
	inv_det = 1.0 / det;
	/*	calculate distance from vert0 to ray origin */
	tvec = ray.origin_ - points[0];
	/*	calculate U	parameter and test bounds */
	u = glm::dot(tvec, pvec) * inv_det;
	if(u <	0.0 || u > 1.0)
		return	false;

	/* prepare to test V parameter */
	qvec = glm::cross(tvec, edge1);

	/* calculate V parameter and test bounds */
	v = glm::dot(ray.direction_, qvec) * inv_det;
	if(v < 0.0 || u + v > 1.0)	return false;

	/* calculate t, ray intersects triangle */
	t = glm::dot(edge2, qvec) * inv_det;
	intersection_record.t_ = t;
	intersection_record.position_ = ray.origin_ + intersection_record.t_ * ray.direction_;
	intersection_record.normal_ = glm::normalize(glm::cross(edge2, edge1));
	/*if (glm::dot(intersection_record.normal_, ray.direction_) > 0) {
		intersection_record.normal_ = glm::normalize(glm::cross(edge2, edge1));
	}*/
	intersection_record.color_ = getBRDF(intersection_record);
	intersection_record.emitance_ = getEmitance(intersection_record);

	return true;
}



