#include "FresnelSpecular.hpp"


// -------------------------------------------------------------- set_kr

FresnelReflector::FresnelReflector(void)
	: BRDF(),
	kr(0.0),
	cr(1.0)
{
}

FresnelReflector::~FresnelReflector(void)
{
}

FresnelReflector* FresnelReflector::clone(void) const
{
	return (new FresnelReflector(*this));
}

void
FresnelReflector::set_kr(const float k) {
	kr = k;
}


// -------------------------------------------------------------- set_cr

void
FresnelReflector::set_cr(const RGBColor& c) {
	cr = c;
}


// ---------------------------------------------------------------- set_cr

void
FresnelReflector::set_cr(const float r, const float g, const float b) {
	cr.r = r; cr.g = g; cr.b = b;
}


// ---------------------------------------------------------------- set_cr

void
FresnelReflector::set_cr(const float c) {
	cr.r = c; cr.g = c; cr.b = c;
}

RGBColor FresnelReflector::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	return (black);
}

RGBColor FresnelReflector::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wr) const
{
	float ndotwo = sr.normal * wo;
	wr = -wo + 2.0 * sr.normal * ndotwo;
	return (fresnel(sr) * white / fabs(sr.normal * wr));
}

RGBColor FresnelReflector::rho(const ShadeRec& sr, const Vector3D& wo) const
{
	return (black);
}

float FresnelReflector::fresnel(const ShadeRec& sr) const
{
	Normal normal(sr.normal);
	float ndotd = -normal * sr.ray.d;
	float eta;

	if (ndotd < 0.0) {
		normal = -normal;
		eta = eta_out / eta_in;
	}
	else
		eta = eta_in / eta_out;

	float cos_theta_i = -normal * sr.ray.d;
	float temp = 1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta);
	float cos_theta_t = sqrt(1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta));
	float r_parallel = (eta * cos_theta_i - cos_theta_t) / (eta * cos_theta_i + cos_theta_t);
	float r_perpendicular = (cos_theta_i - eta * cos_theta_t) / (cos_theta_i + eta * cos_theta_t);
	float kr = 0.5 * (r_parallel * r_parallel + r_perpendicular * r_perpendicular);

	return (kr);
}


// -------------------------------------------------------------- set_eta_in

void
FresnelReflector::set_eta_in(const float ei) {
	eta_in = ei;
}


// -------------------------------------------------------------- set_eta_out

void
FresnelReflector::set_eta_out(const float eo) {
	eta_out = eo;
}