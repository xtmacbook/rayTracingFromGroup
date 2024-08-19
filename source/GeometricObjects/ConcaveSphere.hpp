

#ifndef  _CONCAVESPHERE_H_
#define _CONCAVESPHERE_H_

#include "GeometricObject.hpp"
class Sampler;

class ConcaveSphere : public GeometricObject {

public:

	ConcaveSphere(void);
	ConcaveSphere(Point3D center, double r);

	ConcaveSphere(const ConcaveSphere& sphere);

	ConcaveSphere& operator= (const ConcaveSphere& sphere);

	virtual GeometricObject* clone(void) const ;		// virtual copy constructor


	void set_center(const Point3D& c);

	void set_center(const double x, const double y, const double z);

	void set_radius(const double r);

	virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const;

	virtual bool shadow_hit(const Ray& ray, double& tmin) const;

	// the following functions are used when the sphere is a light source

	virtual void set_sampler(Sampler* sampler);

	virtual Point3D sample(void);

	virtual Normal get_normal(const Point3D& p);

	virtual float pdf(ShadeRec& sr);

	virtual BBox get_bounding_box() const;

private:

	Point3D 	center;   			// center coordinates as a point
	double 		radius;				// the radius

	float			area;			// for spherical lights
	float			inv_area;		// for spherical lights
	Sampler* sampler_ptr;	// for spherical lights

	static const double kEpsilon;   // for shadows and secondary rays
};

#endif