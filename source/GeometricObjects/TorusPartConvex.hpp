#ifndef TORUSPARTCONVEX_H
#define TORUSPARTCONVEX_H


#include "GeometricObject.hpp"
#include "../Utilities/ShadeRec.hpp"

class TorusPartConvex : public GeometricObject {
public:

	TorusPartConvex(void);

	TorusPartConvex(const double _a, const double _b,
		const double _phi1, const double _phi2,
		const double _theta1, const double _theta2);

	virtual TorusPartConvex* clone(void) const;

	TorusPartConvex(const TorusPartConvex& torus);

	virtual ~TorusPartConvex(void);

	TorusPartConvex& operator= (TorusPartConvex& rhs);

	Normal compute_normal(const Point3D& p) const;

	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;

	virtual bool shadow_hit(const Ray& ray, double& tmin) const;

private:

	double 		a;	 	// swept radius
	double		b;	 	// tube radius
	double      phi1;   // azimuth angle
	double      phi2;
	double      theta1; // polar angle
	double      theta2;
	BBox		bbox;	// the bounding box
};

#endif // TORUSPARTCONVEX_H
