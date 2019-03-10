#pragma once
#include <glm\glm.hpp>
#include "../Rays/intersection_record.h"

class Material
{
public:
	Material();
	virtual ~Material();
	glm::vec3 getColor(IntersectionRecord &intersection_record);
};

