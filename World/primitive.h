#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include <memory>

#include "../Rays/ray.h"
#include "../Rays/intersection_record.h"
#include "material.h"

class Primitive {

public:

	typedef std::unique_ptr< Primitive > PrimitiveUniquePtr;

	Primitive(Material mat);

	Primitive(void);

	virtual ~Primitive(void);

	virtual bool intersect(const Ray &ray,
		IntersectionRecord &intersection_record) const = 0;

	glm::vec3 getColor(IntersectionRecord &intersection_record) const;

	virtual glm::vec3 getBRDF(IntersectionRecord &intersection_record) const;

	virtual glm::vec3 getEmitance(IntersectionRecord &intersection_record) const;

protected:
	Material obj_mat;
};

#endif /* PRIMITIVE_H_ */

