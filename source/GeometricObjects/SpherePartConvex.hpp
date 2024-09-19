#ifndef SPHEREPARTCONVEX_H
#define SPHEREPARTCONVEX_H


#include "GeometricObject.hpp"
#include "../Utilities/ShadeRec.hpp"

class SpherePartConvex : public GeometricObject {
public:

	Point3D 	center;   			// center coordinates
	double 		radius;				// sphere radius
	double 		phi_min;			// minimum azimiuth angle in degrees measured counter clockwise from the +ve z axis
	double 		phi_max;			// maximum azimiuth angle in degrees measured counter clockwise from the +ve z axis
	double 		theta_min;			// minimum polar angle in degrees measured down from the +ve y axis
	double 		theta_max;			// maximum polar angle in degrees measured down from the +ve y axis

	double		cos_theta_min;		// stored to avoid repeated calculations
	double		cos_theta_max;		// stored to avoid repeated calculations

public:

	SpherePartConvex(void);

	SpherePartConvex(const Point3D 	c,
		const double 	r,
		const double 	azimuth_min,	// in degrees
		const double 	azimuth_max,	// in degrees
		const double 	polar_min,		// in degrees measured from top
		const double 	polar_max);		// in degrees measured from top

	SpherePartConvex(const Point3D c, const double radius);

	virtual SpherePartConvex* clone(void) const;

	SpherePartConvex(const SpherePartConvex& cp);

	virtual ~SpherePartConvex(void);

	SpherePartConvex& operator= (const SpherePartConvex& rhs);

	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;

	virtual bool shadow_hit(const Ray& ray, double& tmin) const;
};

#endif // SPHEREPARTCONVEX_H
