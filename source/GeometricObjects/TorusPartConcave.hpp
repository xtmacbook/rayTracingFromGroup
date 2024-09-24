#ifndef TORUSPARTCONCAVE_H
#define TORUSPARTCONCAVE_H


#include "GeometricObject.hpp"
#include "../Utilities/ShadeRec.hpp"

class TorusPartConcave : public GeometricObject {
public:

	TorusPartConcave(void);

	TorusPartConcave(const double _a, const double _b,
		const double _phi1, const double _phi2,
		const double _theta1, const double _theta2);

	virtual TorusPartConcave*
		clone(void) const;

	TorusPartConcave(const TorusPartConcave& torus);

	virtual ~TorusPartConcave(void);

	TorusPartConcave& operator= (TorusPartConcave& rhs);

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


#endif // TORUSPARTCONCAVE_H
