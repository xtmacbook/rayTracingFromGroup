#ifndef OPENCYLINDERCONCAVE_H
#define OPENCYLINDERCONCAVE_H


#include "GeometricObject.hpp"
#include "../Utilities/ShadeRec.hpp"

class OpenCylinderConcave : public GeometricObject {

public:

	OpenCylinderConcave(void);

	OpenCylinderConcave(const double bottom, const double top, const double radius);

	OpenCylinderConcave(const OpenCylinderConcave& c);

	virtual OpenCylinderConcave* clone(void) const;

	OpenCylinderConcave& operator= (const OpenCylinderConcave& rhs);

	virtual ~OpenCylinderConcave(void);

	virtual bool hit(const Ray& ray, float& t, ShadeRec& sr) const;

	virtual bool shadow_hit(const Ray& ray, float& t) const;

	virtual BBox get_bounding_box(void);

protected:

	double		y0;				// bottom y value
	double		y1;				// top y value
	double		radius;			// radius
	double		inv_radius;  	// one over the radius
};

#endif // OPENCYLINDERCONCAVE_H
