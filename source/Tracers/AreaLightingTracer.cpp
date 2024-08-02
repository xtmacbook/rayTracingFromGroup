#include "AreaLightingTracer.hpp"
#include "../World/World.hpp"
#include "../Utilities/ShadeRec.hpp"
#include "../Materials/Material.hpp"

AreaLightingTracer::AreaLightingTracer(World* world_ptr_r):
    Tracer(world_ptr_r)
{}

RGBColor AreaLightingTracer::trace_ray(const Ray& ray) const{
    ShadeRec sr(world_ptr->hit_objects(ray));
    if(sr.hit_an_object){
        sr.ray = ray;

        //the differ from the RayCast::trace_ray by calling material_ptr::area_light_shader instead of material_ptr::shader
        return (sr.material_ptr->area_light_shade(sr));
    }
    else{
        return (world_ptr->background_color);
    }
}

RGBColor AreaLightingTracer::trace_ray(const Ray ray, const int depth) const{
    ShadeRec sr(world_ptr->hit_objects(ray));
    if(sr.hit_an_object){
        sr.ray = ray;
        return (sr.material_ptr->area_light_shade(sr));
    }
    else{
        return (world_ptr->background_color);
    }
}

RGBColor AreaLightingTracer::trace_ray(const Ray ray, float& tmin, const int depth) const{
    ShadeRec sr(world_ptr->hit_objects(ray));
    if(sr.hit_an_object){
        sr.ray = ray;
        return (sr.material_ptr->area_light_shade(sr));
    }
    else{
        return (world_ptr->background_color);
    }
}