#include "Reflective.hpp"
#include "../Tracers/Tracer.hpp"

Reflective::Reflective()
    : Phong()
    , reflective_brdf(new PerfectSpecular())
{}

Reflective::Reflective(const Reflective& refl)
    : Phong(refl) {
    if(refl.reflective_brdf){
        reflective_brdf = refl.reflective_brdf->clone();
    }
    else{
        reflective_brdf = new PerfectSpecular();
    }       
}

Reflective* Reflective::clone() const {
    return (new Reflective(*this));
}

Reflective* Reflective::clone(RGBColor new_color) const{
    Reflective* clone_ = new Reflective(*this);
    clone_->set_cr(new_color);
    clone_->set_cd(new_color);
    return clone_;
}

Reflective& Reflective::operator=(const Reflective& rhs){
    if(this == &rhs){
        return (*this);
    }
    Phong::operator=(rhs);
    if(rhs.reflective_brdf){
        reflective_brdf = rhs.reflective_brdf->clone();
    }
    else{
        reflective_brdf = new PerfectSpecular();
    }           
}

void Reflective::set_kr(const float k){
    if(reflective_brdf){
        reflective_brdf->set_kr(k);
    }
}

void Reflective::set_cr(const RGBColor c){
    reflective_brdf->set_cr(c);
}   

void Reflective::set_cr(const float r, const float g, const float b){
    reflective_brdf->set_cr(RGBColor(r, g, b));
}   

void Reflective::set_cr(const float a){
    reflective_brdf->set_cr(RGBColor(a));
}   

/*
    equal (24.3)
*/
RGBColor Reflective::shade(ShadeRec& sr){
    RGBColor L(Phong::shade(sr));
    Vector3D wo = -sr.ray.d;
    Vector3D wi;
    RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
    Ray reflective_ray(sr.hit_point, wi);

    L += fr * sr.w.tracer_ptr->trace_ray(reflective_ray, sr.depth+1)
         *(sr.normal*wi); 
    
    return L;
}

RGBColor
Reflective::path_shade(ShadeRec& sr) {
	Vector3D 	wo = -sr.ray.d;
	Vector3D 	wi;
	float 		pdf;
	RGBColor 	fr = reflective_brdf->sample_f(sr, wo, wi, pdf);
	Ray 		reflected_ray(sr.hit_point, wi);

	return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf);
}

RGBColor Reflective::global_shade(ShadeRec& sr)
{
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
