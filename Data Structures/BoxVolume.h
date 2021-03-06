#pragma once
#include "../Rays/ray.h"
class BoxVolume
{
public:
	//Constructors and destructors
	BoxVolume(const glm::vec3& minu, const glm::vec3& maxi);
	~BoxVolume();

	//Functions
	bool intersect(const Ray& r) const;
	glm::vec3 boundings[2] = { glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f } };
	glm::vec3 getCenter() const { return center_; };

	//Overloaded operators
	BoxVolume operator + (BoxVolume const& obj);

private:
	glm::vec3 center_{ 0.0f, 0.0f, 0.0f };
};