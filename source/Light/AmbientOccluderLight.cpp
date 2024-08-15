#include "AmbientOccluderLight.hpp"
#include "../Samplers/MultiJittered.hpp"
#include "../Utilities/ShadeRec.hpp"
#include "../World/World.hpp"
#include "../Window/Window.hpp"
#include "../GeometricObjects/GeometricObject.hpp"

AmbientOccluderLight::AmbientOccluderLight()
    : u(0)
    , v(0)
    , w(0)
    , sampler_ptr(new Regular(1)) {
    sampler_ptr->map_samples_to_hemisphere(1);
}
AmbientOccluderLight::AmbientOccluderLight(const AmbientOccluderLight& amb)
    : u(amb.u)
    , v(amb.v)
    , w(amb.w) {
    if(amb.sampler_ptr){
        sampler_ptr = amb.sampler_ptr->clone();
    }
    else{
        sampler_ptr = new Regular(1);
    }
    sampler_ptr->map_samples_to_hemisphere(1);
}

AmbientOccluderLight& AmbientOccluderLight::operator=(const AmbientOccluderLight& rhs){
    if(this == &rhs){
        return (*this);
    }    
    Light::operator=(rhs);
    u = rhs.u;
    v = rhs.v;
    w = rhs.w;
    if(rhs.sampler_ptr){
        sampler_ptr = rhs.sampler_ptr->clone();
    }
    else{
        sampler_ptr = new MultiJittered(4);
    }
    sampler_ptr->map_samples_to_hemisphere(1);
    return (*this);
}

AmbientOccluderLight* AmbientOccluderLight::clone() const {
    return (new AmbientOccluderLight(*this));
}

void AmbientOccluderLight::set_sampler(Sampler* s_ptr){
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }
    sampler_ptr = s_ptr;
    sampler_ptr->map_samples_to_hemisphere(1);
}

void AmbientOccluderLight::set_min_amount(float r, float g, float b){
    min_amount = RGBColor(r, g, b);
}

void AmbientOccluderLight::set_min_amount(float a){
    min_amount = RGBColor(a);
}

void AmbientOccluderLight::set_min_amount(RGBColor min){
    min_amount = min;
}

Vector3D AmbientOccluderLight::get_direction(ShadeRec& sr){
    Point3D sp = sampler_ptr->sample_hemisphere();
    return (sp.x*u + sp.y*v + sp.z*w);
}

bool AmbientOccluderLight::in_shadow(const Ray& ray, const ShadeRec& sr) const{
    float t;
    int num_objects = sr.w.objects.size();
    for(int j = 0; j < num_objects; j++){
        if(sr.w.objects[j]->shadow_hit(ray, t)){
            return true;
        }
    }
    return false;
}

RGBColor AmbientOccluderLight::L(ShadeRec& sr){
    w = sr.normal;
    v = w ^ Vector3D(0.00072, 1.0, 0.0034);
    v.normalize();
    u = v ^ w;
    Ray shadow_ray;
    shadow_ray.o = sr.hit_point;
    shadow_ray.d = get_direction(sr);
    if(in_shadow(shadow_ray, sr)){
        return (min_amount*ls*color);
    }
    else{
        return (ls*color);
    }
}