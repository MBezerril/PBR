#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include <memory>

#include "../Rays/ray.h"
#include "../Rays/intersection_record.h"
#include "../Data Structures/boxVolume.h"
#include "material.h"

class Primitive {

public:

	typedef std::unique_ptr< Primitive > PrimitiveUniquePtr;

	Primitive(void);

	Primitive(const Material* mat);
	
	virtual ~Primitive(void);

	virtual bool intersect(const Ray &ray,
		IntersectionRecord &intersection_record) const = 0;

	virtual glm::vec3 getBRDF(IntersectionRecord &intersection_record) const;

	virtual float getEmitance(IntersectionRecord &intersection_record) const;

	glm::vec3 getCenter() const { return boundingBox.getCenter(); } ;

	BoxVolume boundingBox{ glm::vec3{0,0,0}, glm::vec3{ 0,0,0 } };

protected:
	const Material *obj_mat;



};

#endif /* PRIMITIVE_H_ */

