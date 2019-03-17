#pragma once
#include "material.h"
class DiffuseMaterial : public Material
{
public:
	virtual glm::vec3 getRadiance(IntersectionRecord &intersection_record) const;
	virtual glm::vec3 getEmitance(IntersectionRecord &intersection_record) const;
};