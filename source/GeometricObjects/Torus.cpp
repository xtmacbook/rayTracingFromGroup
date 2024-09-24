#include "Torus.hpp"
#include "../Utilities/Maths.hpp"
Torus::Torus(void)
	: GeometricObject(),
	swr(2.0),
	tr(0.5),
	bbox(-swr - tr, swr+tr, -tr, tr, -swr-tr, swr + tr)
{
}

Torus::Torus(const double _a, const double _b)
	: GeometricObject(),
	swr(_a),
	tr(_b),
	bbox(-swr - tr, swr + tr, -tr, tr, -swr - tr, swr + tr)
{
}

Torus* Torus::clone(void) const {
	return (new Torus(*this));
}

Torus::Torus(const Torus& torus)
	: GeometricObject(torus),
	swr(torus.swr),
	tr(torus.tr),
	bbox(torus.bbox)
{}

Torus& Torus::operator = (Torus& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);

	swr = rhs.swr;
	tr = rhs.tr;
	bbox = rhs.bbox;

	return (*this);
}

//------------------------------------------------------------------ FindNormal
// Find the normal vector at the specified position
// This works because the torus is defined by a single implicit equation

Normal Torus::compute_normal(const Point3D& p) const {
	Normal normal;
	double param_squared = swr * swr + tr * tr;

	double x = p.x;
	double y = p.y;
	double z = p.z;
	double sum_squared = x * x + y * y + z * z;

	normal.x = 4.0 * x * (sum_squared - param_squared);
	normal.y = 4.0 * y * (sum_squared - param_squared + 2.0 * swr * swr);
	normal.z = 4.0 * z * (sum_squared - param_squared);
	normal.normalize();

	return (normal);
}


bool Torus::hit(const Ray& ray, float& tmin, ShadeRec& sr) const {
	if (!bbox.hit(ray))
		return (false);

	double x1 = ray.o.x; double y1 = ray.o.y; double z1 = ray.o.z;
	double d1 = ray.d.x; double d2 = ray.d.y; double d3 = ray.d.z;

	double coeffs[5];	// coefficient array for the quartic equation
	double roots[4];	// solution array for the quartic equation

	// define the coefficients of the quartic equation

	double sum_d_sqrd = d1 * d1 + d2 * d2 + d3 * d3;
	double e = x1 * x1 + y1 * y1 + z1 * z1 - swr * swr - tr * tr;
	double f = x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_sqrd = 4.0 * swr * swr;

	coeffs[0] = e * e - four_a_sqrd * (tr * tr - y1 * y1); 	// constant term
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
	coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
	coeffs[3] = 4.0 * sum_d_sqrd * f;
	coeffs[4] = sum_d_sqrd * sum_d_sqrd;  					// coefficient of t^4

	// find roots of the quartic equation

	int num_real_roots = SolveQuartic(coeffs, roots);

	bool	intersected = false;
	double 	t = kHugeValue;

	if (num_real_roots == 0)  // ray misses the torus
		return(false);

	// find the smallest root greater than kEpsilon, if any
	// the roots array is not sorted

	for (int j = 0; j < num_real_roots; j++)
		if (roots[j] > kEpsilon) {
			intersected = true;
			if (roots[j] < t)
				t = roots[j];
		}

	if (!intersected)
		return (false);

	tmin = t;
	sr.local_hit_point = ray.o + t * ray.d;
	sr.normal = compute_normal(sr.local_hit_point);

	return (true);
}
bool Torus::shadow_hit(const Ray& ray, float& tmin) const {
	if (!bbox.hit(ray))
		return (false);

	double x1 = ray.o.x; double y1 = ray.o.y; double z1 = ray.o.z;
	double d1 = ray.d.x; double d2 = ray.d.y; double d3 = ray.d.z;

	double coeffs[5];	// coefficient array for the quartic equation
	double roots[4];	// solution array for the quartic equation

	// define the coefficients of the quartic equation

	double sum_d_sqrd = d1 * d1 + d2 * d2 + d3 * d3;
	double e = x1 * x1 + y1 * y1 + z1 * z1 - swr * swr - tr * tr;
	double f = x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_sqrd = 4.0 * swr * swr;

	coeffs[0] = e * e - four_a_sqrd * (tr * tr - y1 * y1); 	// constant term
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
	coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
	coeffs[3] = 4.0 * sum_d_sqrd * f;
	coeffs[4] = sum_d_sqrd * sum_d_sqrd;  					// coefficient of t^4

	// find roots of the quartic equation

	int num_real_roots = SolveQuartic(coeffs, roots);

	bool	intersected = false;
	double 	t = kHugeValue;

	if (num_real_roots == 0)  // ray misses the torus
		return(false);

	// find the smallest root greater than kEpsilon, if any
	// the roots array is not sorted

	for (int j = 0; j < num_real_roots; j++)
		if (roots[j] > kEpsilon) {
			intersected = true;
			if (roots[j] < t)
				t = roots[j];
		}

	if (!intersected)
		return (false);

	tmin = t;

	return (true);
}


