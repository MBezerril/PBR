#include "DistanceMaterial.h"

DistanceMaterial::DistanceMaterial() {

}

DistanceMaterial::~DistanceMaterial() {

}

glm::vec3 DistanceMaterial::getColor(IntersectionRecord & intersection_record) const{
	
	return glm::vec3(intersection_record.t_, intersection_record.t_, intersection_record.t_);
}
