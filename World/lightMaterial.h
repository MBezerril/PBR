#pragma once
#include "material.h"
class LightMaterial : public Material
{
public:
	LightMaterial(glm::vec3 c, float intensity);
	glm::vec3 getColor(IntersectionRecord &intersection_record) const;
	float getEmitance(IntersectionRecord &intersection_record) const;

protected:
	float intensity_;
};