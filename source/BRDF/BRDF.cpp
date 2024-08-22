#include "BRDF.hpp"

BRDF::BRDF():
    sampler_ptr(nullptr)
{}

BRDF::BRDF(const BRDF& brdf)
    : sampler_ptr(nullptr) {
    if(brdf.sampler_ptr){
        sampler_ptr = brdf.sampler_ptr->clone();
    }
}
    
BRDF::BRDF(Sampler* sampler):
    sampler_ptr(sampler)
{}

BRDF& BRDF::operator=(const BRDF& rhs){
    if(this == &rhs){
        return *this;
    }
    if(rhs.sampler_ptr != nullptr){
        sampler_ptr = rhs.sampler_ptr->clone();
    }
    sampler_ptr = nullptr;
    return (*this);
}

BRDF::~BRDF(){
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = nullptr;
    }
}

void BRDF::set_sampler(Sampler* sampler){
    sampler_ptr = sampler;
}

Sampler* BRDF::get_sampler() const {
    return sampler_ptr;
}

RGBColor BRDF::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const{
    return black;
}

RGBColor BRDF::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const{
    return black;
}

RGBColor BRDF::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const{
    return black;
}
    
RGBColor BRDF::rho(const ShadeRec& sr, const Vector3D& wo) const{
    return black;
}