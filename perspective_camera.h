#ifndef PERSPECTIVE_CAMERA_H_
#define PERSPECTIVE_CAMERA_H_

#include "camera.h"
#include "ray.h"

class PerspectiveCamera : public Camera
{
public:

	PerspectiveCamera( void );

	PerspectiveCamera( const float min_x,
                        const float max_x,
                        const float min_y,
                        const float max_y,
                        const glm::ivec2 &resolution,
                        const glm::vec3 &position,
                        const glm::vec3 &up_vector,
                        const glm::vec3 &look_at,
						const float depth_view_distance);

    Ray getWorldSpaceRay( const glm::vec2 &pixel_coord ) const;

    float min_x_;

    float max_x_;

    float min_y_;

    float max_y_;

	float depth_view_distance_;

};

#endif /* PERSPECTIVE_CAMERA_H_ */

