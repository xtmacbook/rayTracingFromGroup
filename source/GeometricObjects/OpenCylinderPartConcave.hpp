#ifndef OPENCYLINDERPARTCONCAVE_H
#define OPENCYLINDERPARTCONCAVE_H


#include "GeometricObject.hpp"
#include "../Utilities/ShadeRec.hpp"

class OpenCylinderPartConcave : public GeometricObject {

public:

	OpenCylinderPartConcave(void);

	OpenCylinderPartConcave(const double bottom, const double top, const double radius,
		const double _phi_min, const double _phi_max);

	OpenCylinderPartConcave(const OpenCylinderPartConcave& c);

	virtual OpenCylinderPartConcave* clone(void) const;

	OpenCylinderPartConcave& operator= (const OpenCylinderPartConcave& rhs);

	virtual ~OpenCylinderPartConcave(void);

	virtual bool hit(const Ray& ray, float& t, ShadeRec& sr) const;

	virtual bool shadow_hit(const Ray& ray, float& t) const;

	virtual BBox get_bounding_box(void);

protected:

	double		y0;				// bottom y value
	double		y1;				// top y value
	double		radius;			// radius
	double		inv_radius;  	// one over the radius
	double      phi_min;        // minimum phi value
	double      phi_max;        // maximum phi value
};

#endif // OPENCYLINDERPARTCONCAVE_H
