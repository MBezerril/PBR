#include "ray.h"

Ray::Ray( void )
{}

Ray::Ray( const glm::vec3 &origin,
          const glm::vec3 &direction ) :
        origin_{ origin },
        direction_{ direction }
{
	invdirection_ = 1.0f / direction_;
	signalDirection_ = glm::bvec3{ (invdirection_.x < 0), (invdirection_.y < 0), (invdirection_.z < 0) };
}

