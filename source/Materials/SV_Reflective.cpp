
#include "SV_Reflective.hpp"
#include "../Light/Light.hpp"
#include "../Tracers/Tracer.hpp"

SV_Reflective::SV_Reflective (void)
	:	SV_Phong(),
		reflective_brdf(new SV_PerfectSpecular)
{}


SV_Reflective::SV_Reflective(const SV_Reflective& rm)
	: 	SV_Phong(rm) {

	if(rm.reflective_brdf)
		reflective_brdf = rm.reflective_brdf->clone();
	else
		reflective_brdf = NULL;
}


SV_Reflective&
SV_Reflective::operator= (const SV_Reflective& rhs) {
	if (this == &rhs)
		return (*this);

	SV_Phong::operator=(rhs);

	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}

	if (rhs.reflective_brdf)
		reflective_brdf = rhs.reflective_brdf->clone();

	return (*this);
}



SV_Reflective*
SV_Reflective::clone(void) const {
	return (new SV_Reflective(*this));
}

SV_Reflective::~SV_Reflective(void) {
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}
}


RGBColor
SV_Reflective::shade(ShadeRec& sr) {
	RGBColor L(SV_Phong::shade(sr));  // direct illumination

	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
	Ray reflected_ray(sr.hit_point, wi);

	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi);

	return (L);
}


// ------------------------------------------------------------------------------------ path_shade

RGBColor
SV_Reflective::path_shade(ShadeRec& sr) {
	Vector3D 	wo = -sr.ray.d;
	Vector3D 	wi;
	float 		pdf;
	RGBColor 	fr = reflective_brdf->sample_f(sr, wo, wi, pdf);
	Ray 		reflected_ray(sr.hit_point, wi);

	return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf);
}


// ------------------------------------------------------------------------------------ global_shade

RGBColor
SV_Reflective::global_shade(ShadeRec& sr) {
	Vector3D 	wo = -sr.ray.d;
	Vector3D 	wi;
	float 		pdf;
	RGBColor 	fr = reflective_brdf->sample_f(sr, wo, wi, pdf);
	Ray 		reflected_ray(sr.hit_point, wi);

	if (sr.depth == 0) {
        return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 2) * (sr.normal * wi) / pdf);
	}
	else {
        return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf);
	}
}

