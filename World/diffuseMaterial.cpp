#include "diffuseMaterial.h"

DiffuseMaterial::DiffuseMaterial(glm::vec3 c) {
	color = c;
}

glm::vec3 DiffuseMaterial::getBRDF(IntersectionRecord & intersection_record) const {
	return color / pi_value;
}

float DiffuseMaterial::getEmitance(IntersectionRecord & intersection_record) const {
	return 0;
}
