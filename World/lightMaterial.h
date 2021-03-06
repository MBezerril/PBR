#pragma once
#include "material.h"
class LightMaterial : public Material
{
public:
	LightMaterial(glm::vec3 c, float intensity);
	glm::vec3 getBRDF(IntersectionRecord &intersection_record) const;
	float getEmitance(IntersectionRecord &intersection_record) const;

protected:
	float intensity_;
};