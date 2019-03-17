#include "material.h"

Material::Material(glm::vec3 c) : color{c} {
}

Material::Material(){
}


Material::~Material() {
}

glm::vec3 Material::getRadiance(IntersectionRecord & intersection_record) const {
	return glm::vec3();
}

glm::vec3 Material::getEmitance(IntersectionRecord & intersection_record) const {
	return glm::vec3();
}

glm::vec3 Material::getColor(IntersectionRecord & intersection_record) const {
	return color;
}




