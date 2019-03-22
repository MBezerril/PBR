#pragma once
#include "material.h"
class DiffuseMaterial : public Material
{
public:
	DiffuseMaterial(glm::vec3 c);
	glm::vec3 getBRDF(IntersectionRecord &intersection_record) const;
	float getEmitance(IntersectionRecord &intersection_record) const;
};