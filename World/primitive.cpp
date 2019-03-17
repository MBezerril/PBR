#include "primitive.h"

Primitive::Primitive(Material mat) {
	obj_mat = mat;
}

Primitive::Primitive(void) {
}

Primitive::~Primitive(void) {
}

glm::vec3 Primitive::getColor(IntersectionRecord & intersection_record) const {
	return obj_mat.getColor(intersection_record);
}

glm::vec3 Primitive::getBRDF(IntersectionRecord & intersection_record) const {
	return glm::vec3();
}

glm::vec3 Primitive::getEmitance(IntersectionRecord & intersection_record) const {
	return glm::vec3();
}


