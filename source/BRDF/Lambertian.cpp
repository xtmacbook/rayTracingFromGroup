#include "Lambertian.hpp"

Lambertian::Lambertian(float kd_, RGBColor cd_):
    BRDF(),
    kd(kd_),
    cd(cd_)
{}

Lambertian::Lambertian(const Lambertian& lamb):
    BRDF(lamb),
    kd(lamb.kd),
    cd(lamb.cd)
{}

Lambertian* Lambertian::clone() const{
    return (new Lambertian(*this));
}

Lambertian& Lambertian::operator=(const Lambertian& rhs){
    if(this == &rhs){
        return (*this);
    }
    BRDF::operator=(rhs);
    kd = rhs.kd;
    cd = rhs.cd;
    return (*this);
}

float Lambertian::get_kd() const{
    return kd;
}

void Lambertian::set_kd(const float kd){
    this->kd = kd;
}

RGBColor Lambertian::get_cd() const{
    return cd;
}

void Lambertian::set_cd(const RGBColor cd){
    this->cd = cd;
}

void Lambertian::set_sampler(Sampler* s_ptr)
{
    sampler_ptr = s_ptr;
    sampler_ptr->map_samples_to_hemisphere(1);
}

/**
 * f = rho / pi
 */
RGBColor Lambertian::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const{
    
    return (kd * cd * invPI);
}

RGBColor Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const{
    return (kd * cd);
}

RGBColor Lambertian::sample_f(const ShadeRec& sr, Vector3D& wo, Vector3D& wi, float& pdf) const
{
    Vector3D w = sr.normal;
    Vector3D v = Vector3D(0.0034,1.0,0.0071) ^ w;
    v.normalize();
    Vector3D u = w ^ w;

    Point3D sp = sampler_ptr->sample_hemisphere();
    wi = sp.x * u + sp.y * v + sp.z * w;
    wi.normalize();

    pdf = sr.normal * wi * invPI;

    return (kd * kd * invPI);
}
