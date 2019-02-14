#include "triangle.h"
//#define TEST_CULL
Triangle::Triangle(void) {}

Triangle::Triangle(glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3) {
	points[0] = vert1;
	points[1] = vert2;
	points[2] = vert3;
}

bool Triangle::intersect(const Ray & ray, IntersectionRecord & intersection_record) const {
	glm::vec3 edge1, edge2, tvec, pvec, qvec;
	double det, inv_det, t, u, v;
	edge1 = points[1] - points[0];
	edge2 = points[2] - points[0];
	pvec = glm::cross(ray.direction_, edge2);
	det = glm::dot(edge1, pvec);
#ifdef TEST_CULL 
	if (det < EPSILON) return false;
	/* calculate distance from vert0 to ray origin */
	tvec = ray.origin_, points[0]);
	/* calculate U parameter and test bounds */
	u = glm::dot(tvec, pvec);
	if (u < 0.0 || u > det) return false;

	/* prepare to test V parameter */

	qvec = glm::cross(tvec, edge1);

	/* calculate V parameter and test bounds */
	v = glm::dot(dir, qvec);

	if (v < 0.0 || u + v > det) return false;
	/* calculate t, scale parameters, ray intersects triangle */

	t = glm::dot(edge2, qvec);

	inv_det = 1.0 / det;

	t = inv_det;
	u = inv_det;
	v = inv_det;
#else			/* the non-culling branch */
	if (det > -EPSILON && det < EPSILON)
		return	false;
	inv_det = 1.0 / det;
	/*	calculate distance from vert0 to ray origin */
	tvec = ray.origin_ - points[0];
	/*	calculate U	parameter and test bounds */
	u = glm::dot(tvec, pvec);
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

#endif
	return true;
}


//bool Triangle::intersect(const Ray & ray, IntersectionRecord & intersection_record) const {
//	#define ku modulo[k+1]
//	#define kv modulo[k+2]
//	// don’t prefetch here, assume data has already been prefetched
//	// start high-latency division as early as possible
//	const float nd = 1. / (ray.direction_[k] + n_u * ray.direction_[ku] + n_v * ray.direction_[kv]);
//	const float f = (n_d - ray.origin_[k] - n_u * ray.origin_[ku] - n_v * ray.origin_[kv]) * nd;
//	// check for valid distance.
//	// if (!(hit.dist > f && f > EPSILON)) return;
//	 if (!(hit.dist > f && f > EPSILON)) return;
//	// compute hitpoint positions on uv plane
//	const float hu = (ray.origin_[ku] + f * ray.direction_[ku]);
//	const float hv = (ray.origin_[kv] + f * ray.direction_[kv]);
//	// check first barycentric coordinate
//	const float lambda = (hu * b_nu + hv * b_nv + b_d);
//	if (lambda < 0.0f) return;
//	// check second barycentric coordinate*/
//	const float mue = (hu * c_nu + hv * c_nv + c_d);
//	if (mue < 0.0f) return;
//	// check third barycentric coordinate
//	if (lambda + mue > 1.0f) return;
//	// have a valid hitpoint here. store it.
//	hit.dist = f;
//	hit.tri = triNum;
//	hit.u = lambda;
//	hit.v = mue;
//}


