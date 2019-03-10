#include "material.h"


Material::Material() {
}


Material::~Material() {
}

glm::vec3 Material::getColor(IntersectionRecord & intersection_record) {
	return glm::vec3(0, 0, 0);
}

