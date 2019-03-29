#include "lightMaterial.h"

LightMaterial::LightMaterial(glm::vec3 c, float intensity) {
	 intensity_ = intensity;
	 color = c;
}

glm::vec3 LightMaterial::getBRDF(IntersectionRecord & intersection_record) const {
	return color / pi_value;
}

float LightMaterial::getEmitance(IntersectionRecord & intersection_record) const {
	return intensity_;
}
