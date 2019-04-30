#ifndef RAY_H_
#define RAY_H_

#include <glm/glm.hpp>

class Ray
{
public:

    Ray( void );

    Ray( const glm::vec3 &origin,
         const glm::vec3 &direction );

    glm::vec3 origin_{ 0.0f, 0.0f, 0.0f };

    glm::vec3 direction_{ 0.0f, 0.0f, -1.0f };
    glm::vec3 invdirection_{ 0.0f, 0.0f, 0.0f };
<<<<<<< HEAD
    glm::ivec3 signalDirection_{ 0, 0, 0 };
=======
    glm::bvec3 signalDirection_{ false, false, false };
>>>>>>> c68eefe950ec4d3664fc741270b86dd9f5539a98
};

#endif /* RAY_H_ */

