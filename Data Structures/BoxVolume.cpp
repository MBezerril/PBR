#include "boxVolume.h"

BoxVolume BoxVolume::operator+(BoxVolume const& obj) {
	//get the minimum and the maximum xyz from each box and create a new box
	//with the new maximum and minimum point
	glm::vec3 minLocal, maxLocal;

	float x = boundings[0].x < obj.boundings[0].x ? boundings[0].x : obj.boundings[0].x;
	float y = boundings[0].y < obj.boundings[0].y ? boundings[0].y : obj.boundings[0].y;
	float z = boundings[0].z < obj.boundings[0].z ? boundings[0].z : obj.boundings[0].z;
	minLocal = glm::vec3(x, y, z);

	x = boundings[1].x > obj.boundings[1].x ? boundings[1].x : obj.boundings[1].x;
	y = boundings[1].y > obj.boundings[1].y ? boundings[1].y : obj.boundings[1].y;
	z = boundings[1].z > obj.boundings[1].z ? boundings[1].z : obj.boundings[1].z;
	maxLocal = glm::vec3(x, y, z);

	return BoxVolume(minLocal, maxLocal);
}


//Minimum point and the maximum point
BoxVolume::BoxVolume(const glm::vec3& minu, const glm::vec3& maxi) {
	boundings[0] = minu;
	boundings[1] = maxi;
	center_ = (maxi + minu);
	center_ /= 2;
}

BoxVolume::~BoxVolume() {}

bool BoxVolume::intersect(const Ray & r) const {
	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	/** The sinalDirection is a precomputed value on constructor
	*  When the box position is greater than ray origin, so we need to swap the tmax and tmin
	*  The sinal direction help to calc directly or inverted, without need to check and swap after calculation
	*  This is an optimization from:
	*  https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
	*/
	tmin = (boundings[r.signalDirection_[0]].x - r.origin_.x);
	tmin *= r.invdirection_.x;
	tmax = (boundings[1 - r.signalDirection_[0]].x - r.origin_.x);
	tmax *= r.invdirection_.x;
	tymin = (boundings[r.signalDirection_[1]].y - r.origin_.y);
	tymin *= r.invdirection_.y;
	tymax = (boundings[1 - r.signalDirection_[1]].y - r.origin_.y);
	tymax *= r.invdirection_.y;

	//If the tmin is greater than max or the tmax is less than min, the ray doesn't instersetc the box
	if((tmin > tymax) || (tymin > tmax))
		return false;

	//Update the min and max value to compare with the z values
	if(tymin > tmin) tmin = tymin;
	if(tymax < tmax) tmax = tymax;

	tzmin = (boundings[r.signalDirection_[2]].z - r.origin_.z);
	tzmin *= r.invdirection_.z;
	tzmax = (boundings[1 - r.signalDirection_[2]].z - r.origin_.z);
	tzmax *= r.invdirection_.z;

	//If the tmin is greater than max or the tmax is less than min, the ray doesn't instersetc the box
	if((tmin > tzmax) || (tzmin > tmax)) return false;

	//Uncomment these two lines if you need to know the close and distant instersection points
	//if(tzmin > tmin) tmin = tzmin;
	//if(tzmax < tmax)tmax = tzmax;

	return true;
}
