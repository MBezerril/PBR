#pragma once
#include <glm\glm.hpp>

class Material
{
public:
	Material();
	virtual ~Material();
	glm::vec3 getColor();
};

