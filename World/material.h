#pragma once
#include <glm\glm.hpp>
#include "../Rays/intersection_record.h"

class Material {

public:
	Material();
	Material(glm::vec3 c);
	virtual ~Material();
	virtual glm::vec3 getBRDF(IntersectionRecord &intersection_record) const;
	virtual float getEmitance(IntersectionRecord &intersection_record) const;
	glm::vec3 getColor(IntersectionRecord &intersection_record) const;

protected:
	const float pi_value = 3.14159265359f;
	glm::vec3 color;
};

