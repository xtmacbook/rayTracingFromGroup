
#include "SV_GlossySpecular.hpp"
#include "../Samplers/MultiJittered.hpp"
#include "../Utilities/Constants.hpp"

SV_GlossySpecular::SV_GlossySpecular(void)
	: 	BRDF(),
        ks(0.0),
		cs(new ConstantColor(white)),
		sampler_ptr(NULL)
{}


SV_GlossySpecular::~SV_GlossySpecular(void) {}


SV_GlossySpecular*
SV_GlossySpecular::clone (void) const {
	return (new SV_GlossySpecular(*this));
}


// this allows any type of sampling to be specified in the build functions

void
SV_GlossySpecular::set_sampler(Sampler* sp, const float exp) {
	sampler_ptr = sp;
	sampler_ptr->map_samples_to_hemisphere(exp);
}


// this sets up multi-jittered sampling using the number of samples

void
SV_GlossySpecular::set_samples(const int num_samples, const float exp) {
	sampler_ptr = new MultiJittered(num_samples);
	sampler_ptr->map_samples_to_hemisphere(exp);
}


// no sampling here: just use the Phong formula
// this is used for direct illumination only

RGBColor
SV_GlossySpecular::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	RGBColor 	L;
	float 		ndotwi = sr.normal * wi;
	Vector3D 	r(-wi + 2.0 * sr.normal * ndotwi); // mirror reflection direction
	float 		rdotwo = r * wo;

	if (rdotwo > 0.0)
		L = ks * (cs->get_color(sr)) * pow(rdotwo, exp);

	return (L);
}


// this is used for indirect illumination

RGBColor
SV_GlossySpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {

	float ndotwo = sr.normal * wo;
	Vector3D r = -wo + 2.0 * sr.normal * ndotwo;     // direction of mirror reflection

	Vector3D w = r;
	Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w;
	u.normalize();
	Vector3D v = u ^ w;

	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;			// reflected ray direction

	if (sr.normal * wi < 0.0) 						// reflected ray is below tangent plane
		wi = -sp.x * u - sp.y * v + sp.z * w;

	float phong_lobe = pow(r * wi, exp);
	pdf = phong_lobe * (sr.normal * wi);

	return (ks * (cs->get_color(sr)) * phong_lobe);
}

RGBColor
SV_GlossySpecular::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return (black);
}

