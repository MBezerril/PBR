#include "lightMaterial.h"

LightMaterial::LightMaterial(float intensity) {
	 intensity_ = intensity;
}

glm::vec3 LightMaterial::getBRDF(IntersectionRecord & intersection_record) const {
	return color / pi_value;
}

float LightMaterial::getEmitance(IntersectionRecord & intersection_record) const {
	return 1.0f;
}
