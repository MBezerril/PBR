#include "BoxVolume.h"

BoxVolume::BoxVolume(const glm::vec3& maxi, const glm::vec3& minu) {
	boundings[0] = maxi;
	boundings[1] = minu;
}

BoxVolume::~BoxVolume() {}


bool BoxVolume::intersect(const Ray& r) const {
	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	/** The sinalDirection is a precomputed value on constructor
	*  When the box position is greater than ray origin, so we need to swap the tmax and tmin
	*  The sinal direction help to calc directly or inverted, without need to check and swap after calculation
	*  This is an optimization
	*/
	tmin = (boundings[r.signalDirection_[0]].x - r.origin_.x) * r.invdirection_.x;
	tmax = (boundings[1 - r.signalDirection_[0]].x - r.origin_.x) * r.invdirection_.x;
	tymin = (boundings[r.signalDirection_[1]].y - r.origin_.y) * r.invdirection_.y;
	tymax = (boundings[1 - r.signalDirection_[1]].y - r.origin_.y) * r.invdirection_.y;

	//If the tmin is greater than max or the tmax is less than min, the ray doesn't instersetc the box
	if((tmin > tymax) || (tymin > tmax))
		return false;

	//Update the min and max value to compare with the z values
	if(tymin > tmin) tmin = tymin;
	if(tymax < tmax) tmax = tymax;

	tzmin = (boundings[r.signalDirection_[2]].z - r.origin_.z) * r.invdirection_.z;
	tzmax = (boundings[1 - r.signalDirection_[2]].z - r.origin_.z) * r.invdirection_.z;

	//If the tmin is greater than max or the tmax is less than min, the ray doesn't instersetc the box
	if((tmin > tzmax) || (tzmin > tmax)) return false;

	//Uncomment these two lines if you need to know the close and distant instersection points
	//if(tzmin > tmin) tmin = tzmin;
	//if(tzmax < tmax)tmax = tzmax;

	return true;
}
