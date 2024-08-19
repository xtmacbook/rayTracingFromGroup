
#include "GlossyReflectorMaterial.hpp"
#include "../Tracers/Tracer.hpp"

GlossyReflector::GlossyReflector()
{
    glossy_reflector_ptr = new GlossySpecular;
}

/// @brief 
 /// @param num_samples 
 /// @param exp 
 void GlossyReflector::set_samples(const int num_samples, float exp)
{
    glossy_reflector_ptr->set_sampler(num_samples,exp);
}

void GlossyReflector::set_kr(const float kr)
{
    glossy_reflector_ptr->set_ks(kr);
}

void GlossyReflector::set_cr(const RGBColor& c)
{
    glossy_reflector_ptr->set_cs(c);
}

void GlossyReflector::set_cr(const float r, const float g, const float b)
{
    glossy_reflector_ptr->set_cs(r, g, b);
}

void GlossyReflector::set_exponent(float exp)
{
    glossy_reflector_ptr->set_exp(exp);
}

RGBColor GlossyReflector::shade(ShadeRec& sr) {
	RGBColor L(Phong::shade(sr));  // direct illumination

	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	float    pdf;
	RGBColor fr = glossy_reflector_ptr->sample_f(sr, wo, wi, pdf);
	Ray reflected_ray(sr.hit_point, wi);

	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf;

	return (L);
}

RGBColor GlossyReflector::area_light_shade(ShadeRec &sr)
{
    RGBColor L (Phong::area_light_shade(sr));
    
    Vector3D wo(-sr.ray.d);
    Vector3D wi;
    float pdf;

    RGBColor fr(glossy_reflector_ptr->sample_f(sr,wo,wi,pdf));

    Ray reflected_ray(sr.hit_point,wi);

    L +=fr *  sr.w.tracer_ptr->trace_ray(reflected_ray,sr.depth + 1) *(sr.normal* wi) / pdf;

    return L;
}
