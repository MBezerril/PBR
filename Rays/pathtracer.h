#ifndef PATHTRACER_H_
#define PATHTRACER_H_

#include <sstream>
#include <iomanip>
#include <cmath>

#include "../Cameras/camera.h"
#include "../World/scene.h"
#include "../Cameras/buffer.h"

class PathTracer
{
public:

	PathTracer( Camera &camera,
               const Scene &scene,
               const glm::vec3 background_color,
               Buffer &buffer, int samples );

    void integrate( void );

private:

    const Camera &camera_;

    const Scene &scene_;

    glm::dvec3 background_color_;

    Buffer &buffer_;

	int samples_;

	glm::vec3 L(const Ray &ray, int depth);

};

#endif /* PATHTRACER_H_ */

