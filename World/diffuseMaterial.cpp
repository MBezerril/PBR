#include "diffuseMaterial.h"

glm::vec3 DiffuseMaterial::getRadiance(IntersectionRecord & intersection_record) const {
	return glm::vec3();
}

glm::vec3 DiffuseMaterial::getEmitance(IntersectionRecord & intersection_record) const {
	return glm::vec3();
}
