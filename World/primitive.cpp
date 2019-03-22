#include "primitive.h"

Primitive::Primitive(const Material *mat) : obj_mat{ mat } {
}

Primitive::Primitive(void) {
	obj_mat = new Material(glm::vec3(0, 0, 0));
}

Primitive::~Primitive(void) {
}

glm::vec3 Primitive::getColor(IntersectionRecord & intersection_record) const {
	return obj_mat->getColor(intersection_record);
}

glm::vec3 Primitive::getBRDF(IntersectionRecord & intersection_record) const {
	return glm::vec3();
}

float Primitive::getEmitance(IntersectionRecord & intersection_record) const {
	return obj_mat->getEmitance(intersection_record);
}


