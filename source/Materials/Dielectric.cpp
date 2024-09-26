#include "Dielectric.hpp"
#include "../Tracers/Tracer.hpp"

Dielectric::Dielectric(void)
    : Phong(),
    fresnel_brdf(new FresnelReflector),
    fresnel_btdf(new FresnelTransmitter)
{
}

Dielectric::Dielectric(const Dielectric& dm) : Phong(dm) {

    if (dm.fresnel_brdf)
        fresnel_brdf = dm.fresnel_brdf->clone();
    else
        fresnel_brdf = nullptr;

    if (dm.fresnel_btdf)
        fresnel_btdf = dm.fresnel_btdf->clone();
    else
        fresnel_btdf = nullptr;

    cf_in = dm.cf_in;
    cf_out = dm.cf_out;
}

Dielectric& Dielectric::operator=(const Dielectric& rhs)
{
    if (this == &rhs)
        return (*this);

    Phong::operator=(rhs);

    if (fresnel_brdf) {
        delete fresnel_brdf;
        fresnel_brdf = nullptr;
    }

    if (rhs.fresnel_brdf)
        fresnel_brdf = rhs.fresnel_brdf->clone();

    if (fresnel_btdf) {
        delete fresnel_btdf;
        fresnel_btdf = nullptr;
    }

    if (rhs.fresnel_btdf)
        fresnel_btdf = rhs.fresnel_btdf->clone();

    cf_in = rhs.cf_in;
    cf_out = rhs.cf_out;

    return (*this);
}

Dielectric* Dielectric::clone(void) const
{
    return (new Dielectric(*this));
}

Dielectric::~Dielectric(void)
{
    if (fresnel_brdf) {
        delete fresnel_brdf;
        fresnel_brdf = NULL;
    }
    if (fresnel_btdf) {
        delete fresnel_btdf;
        fresnel_btdf = NULL;
    }
}

void Dielectric::set_eta_in(const float ei)
{
    fresnel_brdf->set_eta_in(ei);
    fresnel_btdf->set_eta_in(ei);
}

void Dielectric::set_eta_out(const float eo)
{
    fresnel_brdf->set_eta_out(eo);
    fresnel_btdf->set_eta_out(eo);
}

void Dielectric::set_cf_in(const RGBColor& ci)
{
    cf_in = ci;
}

void Dielectric::set_cf_in(const float ri, const float gi, const float bi)
{
    cf_in.r = ri; cf_in.g = gi; cf_in.b = bi;
}

void Dielectric::set_cf_in(const float ci)
{
    cf_in.r = ci; cf_in.g = ci; cf_in.b = ci;
}

void Dielectric::set_cf_out(const RGBColor& co)
{
    cf_out = co;
}

void Dielectric::set_cf_out(const float ro, const float go, const float bo)
{
    cf_out.r = ro; cf_out.g = go; cf_out.b = bo;
}

void Dielectric::set_cf_out(const float co)
{
    cf_out.r = co; cf_out.g = co; cf_out.b = co;
}

RGBColor Dielectric::shade(ShadeRec& sr)
{
    RGBColor L(Phong::shade(sr));

    Vector3D 	wi;
    Vector3D 	wo(-sr.ray.d);
    RGBColor 	fr = fresnel_brdf->sample_f(sr, wo, wi);  	// computes wi
    Ray 		reflected_ray(sr.hit_point, wi);
    float 		t = .0;
    RGBColor 	Lr, Lt;
    float 		ndotwi = sr.normal * wi;

    if (fresnel_btdf->tir(sr)) {								// total internal reflection
        if (ndotwi < 0.0) {
            // reflected ray is inside

            Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
            L += cf_in.powc(t) * Lr;   						// inside filter color
        }
        else {
            // reflected ray is outside

            Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);   // kr = 1
            L += cf_out.powc(t) * Lr;   					// outside filter color
        }
    }
    else { 													// no total internal reflection
        Vector3D wt;
        RGBColor ft = fresnel_btdf->sample_f(sr, wo, wt);  	// computes wt
        Ray transmitted_ray(sr.hit_point, wt);
        float ndotwt = sr.normal * wt;

        if (ndotwi < 0.0) {
            // reflected ray is inside

            Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi);
            L += cf_in.powc(t) * Lr;     					// inside filter color

            // transmitted ray is outside

            Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt);
            L += cf_out.powc(t) * Lt;   					// outside filter color
        }
        else {
            // reflected ray is outside

            Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi);
            L += cf_out.powc(t) * Lr;						// outside filter color

            // transmitted ray is inside

            Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt);
            L += cf_in.powc(t) * Lt; 						// inside filter color
        }
    }

    return (L);
}
