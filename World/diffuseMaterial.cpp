#include "diffuseMaterial.h"

glm::vec3 DiffuseMaterial::getRadiance(IntersectionRecord & intersection_record) const {
	return color / pi_value;
}

glm::vec3 DiffuseMaterial::getEmitance(IntersectionRecord & intersection_record) const {
	return glm::vec3();
}
