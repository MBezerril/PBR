#ifndef ORTHOGRAPHIC_CAMERA_H_
#define ORTHOGRAPHIC_CAMERA_H_

#include "camera.h"
#include "../Rays/ray.h"

class OrthographicCamera : public Camera
{
public:

    OrthographicCamera( void );

    OrthographicCamera( const float min_x,
                        const float max_x,
                        const float min_y,
                        const float max_y,
                        const glm::ivec2 &resolution,
                        const glm::vec3 &position,
                        const glm::vec3 &up_vector,
                        const glm::vec3 &look_at );

    Ray getWorldSpaceRay( const glm::vec2 &pixel_coord ) const;

    float min_x_;

    float max_x_;

    float min_y_;

    float max_y_;

};

#endif /* ORTHOGRAPHIC_CAMERA_H_ */

