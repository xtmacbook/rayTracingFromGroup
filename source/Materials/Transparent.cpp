#include "Transparent.hpp"

#include "../BRDF/PerfectSpecular.hpp"
#include "../BRDF/PerfectTransmitter.hpp"

#include "../Tracers/Tracer.hpp"

Transparent::Transparent(void) : Phong(),
reflective_brdf(new PerfectSpecular),
specular_btdf(new PerfectTransmitter)
{
}

Transparent::Transparent(const Transparent& tm) : Phong(tm) {

	if (tm.reflective_brdf)
		reflective_brdf = tm.reflective_brdf->clone();
	else
		reflective_brdf = nullptr;

	if (tm.specular_btdf)
		specular_btdf = tm.specular_btdf->clone();
	else
		specular_btdf = nullptr;
}

Transparent& Transparent::operator=(const Transparent& rhs)
{
	if (this == &rhs)
		return (*this);

	Phong::operator=(rhs);

	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = nullptr;
	}

	if (rhs.reflective_brdf)
		reflective_brdf = rhs.reflective_brdf->clone();

	if (specular_btdf) {
		delete specular_btdf;
		specular_btdf = nullptr;
	}

	if (rhs.specular_btdf)
		specular_btdf = rhs.specular_btdf->clone();

	return (*this);
}

Transparent* Transparent::clone(void) const
{
	return (new Transparent(*this));
}

Transparent::~Transparent(void)
{
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = nullptr;
	}
	if (specular_btdf) {
		delete specular_btdf;
		specular_btdf = nullptr;
	}
}

void Transparent::set_kr(const float k)
{
	reflective_brdf->set_kr(k);
}

void Transparent::set_cr(const RGBColor& c)
{
	reflective_brdf->set_cr(c);
}

void Transparent::set_cr(const float r, const float g, const float b)
{
	reflective_brdf->set_cr(RGBColor(r, g, b));
}

void Transparent::set_cr(const float c)
{
	reflective_brdf->set_cr(c);
}

void Transparent::set_kt(const float k)
{
	specular_btdf->set_kt(k);
}

void Transparent::set_ior(const float i)
{
	specular_btdf->set_ior(i);
}

RGBColor Transparent::shade(ShadeRec& sr)
{
	RGBColor L(Phong::shade(sr));  // direct illumination

	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);    // computes wi
	Ray reflected_ray(sr.hit_point, wi);

	if (specular_btdf->tir(sr)) { // test total internal reflection
		L += sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);
		// kr = 1.0
	}
	else {
		Vector3D wt;
		RGBColor ft = specular_btdf->sample_f(sr, wo, wt); // computes wt
		Ray transmitted_ray(sr.hit_point, wt);

		L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1)
			* fabs(sr.normal * wi);
		L += ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, sr.depth + 1)
			* fabs(sr.normal * wt);
	}

	return (L);
}
