#ifndef INTERSECTION_RECORD_H_
#define INTERSECTION_RECORD_H_

#include <glm/glm.hpp>

struct IntersectionRecord
{
    float t_;
	float emitance_;
	glm::vec3 position_;
	glm::vec3 normal_;
	glm::vec3 color_; //Do not erase this variable to keep the Ray tracing and path tracing working(Not used in path tracer)
};

#endif /* INTERSECTION_RECORD_H_ */

