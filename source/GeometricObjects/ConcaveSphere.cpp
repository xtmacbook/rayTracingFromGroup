
#include "ConcaveSphere.hpp"
#include "../Samplers/Sampler.hpp"


const double ConcaveSphere::kEpsilon = 0.001;


 void ConcaveSphere::set_center(const Point3D& c) {
	center = c;
}

 void ConcaveSphere::set_center(const double x, const double y, const double z) {
	center.x = x;
	center.y = y;
	center.z = z;
}

 void ConcaveSphere::set_radius(const double r) {
	radius = r;
}

ConcaveSphere::ConcaveSphere(void)
	: 	GeometricObject(),
		center(0.0),
		radius(1.0),
		area(4*PI),
		inv_area(1.0 / area)
{}


ConcaveSphere::ConcaveSphere(Point3D c, double r)
	: 	GeometricObject(),
		center(c),
		radius(r),
		area(4*PI*r*r),
		inv_area(1.0 / area)
{}


ConcaveSphere::ConcaveSphere (const ConcaveSphere& sphere)
	: 	GeometricObject(sphere),
		center(sphere.center),
		radius(sphere.radius)
{}




ConcaveSphere&
ConcaveSphere::operator= (const ConcaveSphere& rhs)
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	center 	= rhs.center;
	radius	= rhs.radius;

	return (*this);
}

GeometricObject* ConcaveSphere::clone(void) const
{
	return (new ConcaveSphere(*this));
}


bool
ConcaveSphere::hit(const Ray& ray, float& tmin, ShadeRec& sr) const {
	double 		t;
	Vector3D	temp 	= ray.o - center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;

	if (disc < 0.0)
		return(false);
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root

		if (t > kEpsilon) {
			tmin = t;
			sr.normal 	 = (temp + t * ray.d) / radius;
#if 1 // reverse normal for Concave
			sr.normal = -sr.normal;
#endif // 0
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) {
			tmin = t;
			sr.normal   = (temp + t * ray.d) / radius;
#if 1 // reverse normal for Concave
			sr.normal = -sr.normal;
#endif // 0
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		}
	}

	return (false);
}



bool
ConcaveSphere::shadow_hit(const Ray& ray, double& tmin) const {
	double 		t;
	Vector3D	temp 	= ray.o - center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;

	if (disc < 0.0)
		return(false);
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root

		if (t > kEpsilon) {
			tmin = t;
			return (true);
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) {
			tmin = t;
			return (true);
		}
	}

	return (false);
}


void
ConcaveSphere::set_sampler(Sampler* sampler) {
	sampler_ptr = sampler;
	sampler_ptr->map_samples_to_hemisphere(1);
}


// ---------------------------------------------------------------- sample
// returns a sample point on the rectangle

Point3D
ConcaveSphere::sample(void) {

	Point3D sample_point = sampler_ptr->sample_hemisphere();

	return (center + sample_point*radius);
}


Normal
ConcaveSphere::get_normal(const Point3D& p) {
    Normal nor = sample() - center;
    nor.normalize();
	return (nor);
}


float
ConcaveSphere::pdf(ShadeRec& sr) {
	return (inv_area);
}

BBox ConcaveSphere::get_bounding_box() const
{
	double delta = 0.000001;

	return (BBox(center.x - radius - delta, center.x + radius + delta,
		center.y - radius - delta, center.y + radius + delta,
		center.z - radius - delta, center.z + radius + delta));
}

