#ifndef OPENCYLINDERCONVEX_H
#define OPENCYLINDERCONVEX_H


#include "GeometricObject.hpp"
#include "../Utilities/ShadeRec.hpp"

class OpenCylinderConvex : public GeometricObject {

public:

	OpenCylinderConvex(void);

	OpenCylinderConvex(const double bottom, const double top, const double radius);

	OpenCylinderConvex(const OpenCylinderConvex& c);

	virtual OpenCylinderConvex* clone(void) const;

	OpenCylinderConvex& operator= (const OpenCylinderConvex& rhs);

	virtual ~OpenCylinderConvex(void);

	virtual bool hit(const Ray& ray, float& t, ShadeRec& sr) const;

	virtual bool shadow_hit(const Ray& ray, float& t) const;

	virtual BBox get_bounding_box(void);

protected:

	double		y0;				// bottom y value
	double		y1;				// top y value
	double		radius;			// radius
	double		inv_radius;  	// one over the radius
};

#endif // OPENCYLINDERCONVEX_H
