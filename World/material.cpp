#include "material.h"

Material::Material(glm::vec3 c) : color{ c } {
}

Material::Material() {
}


Material::~Material() {
}

glm::vec3 Material::getBRDF(IntersectionRecord & intersection_record) const {
	return color/pi_value;
}

float Material::getEmitance(IntersectionRecord & intersection_record) const {
	return 0;
}





