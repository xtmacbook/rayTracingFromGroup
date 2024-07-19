#include "PointLight.hpp"
#include "../Utilities/ShadeRec.hpp"
#include "../World/World.hpp"

PointLight::PointLight(Vector3D location_, float ls_, RGBColor color_, bool shadows_):
    Ambient(),
    location(location_)
{
    this->scale_radiance(ls_);
    this->set_shadows(shadows_);
    this->set_color(color_);
}

PointLight::PointLight(PointLight& point):
    Ambient(point),
    location(point.get_location())
{}

Vector3D PointLight::get_location() const{
    return location;
}

void PointLight::set_location(const Vector3D location_){
    location = location_;
}

void PointLight::set_location(const float x, const float y, const float z){
    location = Vector3D(x, y, z);
}

Vector3D PointLight::get_direction(ShadeRec& sr){
    return ((location - sr.hit_point).hat());
}

RGBColor PointLight::L(ShadeRec& sr){
    return (ls * color);
}

bool PointLight::in_shadow(const Ray& ray, const ShadeRec& sr) const{
    float t;
    int num_objects = sr.w.objects.size();
    float d = Point3D(location.x, location.y, location.z).distance(ray.o);

    for(int j = 0; j < num_objects; j++){
        if(sr.w.objects[j]->shadow_hit(ray, t) && t < d){
            return true;
        }
    }
    return false;
}