#include "GlossySpecular.hpp"
#include "../Utilities/Constants.hpp"
#include "../Samplers/MultiJittered.hpp"

GlossySpecular::GlossySpecular(float kd_, float exp_, RGBColor cd_):
    BRDF(),
    ks(kd_),
    exp(exp_),
    cs(cd_)
{}

GlossySpecular::GlossySpecular(const GlossySpecular& lamb):
    BRDF(lamb),
    ks(lamb.ks),
    exp(lamb.exp),
    cs(lamb.cs)
{}

GlossySpecular* GlossySpecular::clone() const{
    return (new GlossySpecular(*this));
}

GlossySpecular& GlossySpecular::operator=(const GlossySpecular& rhs){
    if(this == &rhs){
        return (*this);
    }
    BRDF::operator=(rhs);
    ks = rhs.ks;
    exp = rhs.exp;
    cs = rhs.cs;
    return (*this);
}

void GlossySpecular::set_exp(const float exp_){
    this->exp = exp_;
}

float GlossySpecular::get_exp() const{
    return exp;
}
float GlossySpecular::get_ks() const
{
    return ks;
}

void GlossySpecular::set_ks(const float ks)
{
    this->ks = ks;
}

RGBColor GlossySpecular::get_cs() const
{
    return cs;
}

void GlossySpecular::set_cs(const RGBColor cs)
{
    this->cs = cs;
}

void GlossySpecular::set_cs(const float r, const float g, const float b)
{
	cs.r = r; cs.g = g; cs.b = b;
}

RGBColor GlossySpecular::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const{
    RGBColor L;
    float ndotwi = sr.normal*wi;
    Vector3D r(-wi + 2.0*sr.normal*ndotwi);
    float rdotwo = r*wo;
    if(rdotwo > 0.0){
        L = cs*ks*pow(rdotwo, exp); //cd is for making specular hightlights a different color from that of the lights
    }
    return (L);
}

RGBColor GlossySpecular::rho(const ShadeRec& sr, const Vector3D& wo) const{
    return (black);
}

void GlossySpecular::set_sampler(const int num_samples, const float exp)
{
	sampler_ptr = new MultiJittered(num_samples);
	sampler_ptr->map_samples_to_hemisphere(exp);
}
/* because there are no delta function in this integrand ,we have to estimate its value using Monte Carlo integration */
RGBColor GlossySpecular::sample_f(const ShadeRec& sr, Vector3D& wo, Vector3D& wi, float& pdf) const
{
    float ndotwo = sr.normal * wo;

    Vector3D mirror_reflect_dir = -wo + 2.0 * sr.normal * ndotwo;

    Vector3D w = mirror_reflect_dir;
    Vector3D u = Vector3D(0.00424, 1.0, 0.00764) ^ w;
    u.normalize();
    Vector3D v = u ^ w;

    Point3D sp = sampler_ptr->sample_hemisphere();
    wi = sp.x * u + sp.y * v + sp.z * w; //reflected ray direction

    if (sr.normal * wi < 0.0)
        wi = -sp.x * u + sp.y * v + sp.z * w;

    float phone_lobe = pow(mirror_reflect_dir * wi, exp);

    pdf = phone_lobe * (sr.normal * wi);

    return (ks * cs * phone_lobe); 

}
