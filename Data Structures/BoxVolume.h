#pragma once
#include "../Rays/ray.h"
class BoxVolume
{
public:
	BoxVolume(const glm::vec3& maxi, const glm::vec3& minu);
	~BoxVolume();
	bool intersect(const Ray& r) const;
private:
	glm::vec3 boundings[2];
};