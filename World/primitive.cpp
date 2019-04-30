#include "primitive.h"

Primitive::Primitive(const Material *mat) : obj_mat{ mat } {
}

Primitive::Primitive(void) {
	obj_mat = new Material(glm::vec3(0, 0, 0));
}

<<<<<<< HEAD
Primitive::~Primitive(void){
=======
Primitive::~Primitive(void) {
>>>>>>> c68eefe950ec4d3664fc741270b86dd9f5539a98
}

glm::vec3 Primitive::getBRDF(IntersectionRecord & intersection_record) const {
	return obj_mat->getBRDF(intersection_record);
}

float Primitive::getEmitance(IntersectionRecord & intersection_record) const {
	return obj_mat->getEmitance(intersection_record);
}


