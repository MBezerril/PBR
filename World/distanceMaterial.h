#pragma once
#include "d:\UFPB\2018-2\T�picos Especiais em Computa��o\PBR\World\material.h"
class DistanceMaterial : public Material
{
public:
	DistanceMaterial();
	virtual ~DistanceMaterial();
	glm::vec3 getColor(IntersectionRecord &intersection_record) const;
};

