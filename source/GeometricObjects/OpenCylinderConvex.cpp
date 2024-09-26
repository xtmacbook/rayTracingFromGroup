
#include "OpenCylinderConvex.hpp"


OpenCylinderConvex::OpenCylinderConvex(void)
	: 	GeometricObject(),
		y0(-1.0),
		y1(1.0),
		radius(1.0),
		inv_radius(1.0)
{}

OpenCylinderConvex::OpenCylinderConvex(const double bottom, const double top, const double r)
	:  	GeometricObject(),
		y0(bottom),
		y1(top),
		radius(r),
		inv_radius(1.0 / radius)
{}


OpenCylinderConvex::OpenCylinderConvex(const OpenCylinderConvex& c)
	: 	GeometricObject(c),
		y0(c.y0),
		y1(c.y1),
		radius(c.radius),
		inv_radius(c.inv_radius)
{}


OpenCylinderConvex*
OpenCylinderConvex::clone(void) const {
	return (new OpenCylinderConvex (*this));
}


OpenCylinderConvex&
OpenCylinderConvex::operator= (const OpenCylinderConvex& rhs)
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	y0 			= rhs.y0;
	y1 			= rhs.y1;
	radius 		= rhs.radius;
	inv_radius 	= rhs.inv_radius;

	return (*this) ;
}


OpenCylinderConvex::~OpenCylinderConvex(void) {}


// ---------------------------------------------------------------- get_bounding_box

BBox
OpenCylinderConvex::get_bounding_box(void) {
	double delta = 0.000001;

	return (BBox(0 - radius - delta, 0 + radius + delta,
                         y0 - delta,         y1 + delta,
				 0 - radius - delta, 0 + radius + delta));
}


// ----------------------------------------------------------------------------- hit
// The code reverses the normal when the ray hits the inside surface, allows both
// sides to be shaded, but completely messes up transparency.

bool
OpenCylinderConvex::hit(const Ray& ray, float& tmin, ShadeRec& sr) const {

	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;

	double a = dx * dx + dz * dz;
	double b = 2.0 * (ox * dx + oz * dz);
	double c = ox * ox + oz * oz - radius * radius;
	double disc = b * b - 4.0 * a * c ;


	if (disc < 0.0)
		return(false);
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root

		if (t > kEpsilon) {
			double yhit = oy + t * dy;

			if (yhit > y0 && yhit < y1) {
				tmin = t;
				sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);

# if 0 // Convex doesn't need this

				// test for hitting from inside

				if (-ray.d * sr.normal < 0.0) {
					sr.normal = -sr.normal;
				}

# endif // 0
				sr.local_hit_point = ray.o + tmin * ray.d;

				return (true);
			}
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) {
			double yhit = oy + t * dy;

			if (yhit > y0 && yhit < y1) {
				tmin = t;
				sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);

# if 0 // Convex doesn't need this

				// test for hitting from inside

				if (-ray.d * sr.normal < 0.0) {
					sr.normal = -sr.normal;
				}

# endif // 0

				sr.local_hit_point = ray.o + tmin * ray.d;

				return (true);
			}
		}
	}

	return (false);
}


// ----------------------------------------------------------------------------- shadow_hit
// The code reverses the normal when the ray hits the inside surface, allows both
// sides to be shaded, but completely messes up transparency.

bool
OpenCylinderConvex::shadow_hit(const Ray& ray, float& tmin) const {

	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;

	double a = dx * dx + dz * dz;
	double b = 2.0 * (ox * dx + oz * dz);
	double c = ox * ox + oz * oz - radius * radius;
	double disc = b * b - 4.0 * a * c ;


	if (disc < 0.0)
		return(false);
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root

		if (t > kEpsilon) {
			double yhit = oy + t * dy;

			if (yhit > y0 && yhit < y1) {
				tmin = t;

				return (true);
			}
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) {
			double yhit = oy + t * dy;

			if (yhit > y0 && yhit < y1) {
				tmin = t;

				return (true);
			}
		}
	}

	return (false);
}
