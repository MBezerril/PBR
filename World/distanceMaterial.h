#pragma once
#include "d:\UFPB\2018-2\Tópicos Especiais em Computação\PBR\World\material.h"
class DistanceMaterial : public Material
{
public:
	DistanceMaterial();
	virtual ~DistanceMaterial();
	glm::vec3 getColor(IntersectionRecord &intersection_record);
};

