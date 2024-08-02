#pragma once
#include "../GeometricObjects/ConcaveSphere.hpp"
#include "../Light/EnvironmentLight.hpp"

void World::build(void){
    vp.hres = 400;
    vp.vres = 400;
    vp.set_pixel_size(1);
    vp.set_gamma(1);
    background_color = black;
    tracer_ptr = new RayCast(this);

    int num_samples = 64;

    Emissive* emissive_ptr = new Emissive;
    emissive_ptr->set_ce(1.0, 1.0, 0.5);
    emissive_ptr->scale_radiance(1.0);

    ConcaveSphere* sphere_ptr = new ConcaveSphere;
    sphere_ptr->set_radius(1000000.0);
    sphere_ptr->set_material(emissive_ptr);
    sphere_ptr->set_casts_shadows(false);
    add_object(sphere_ptr);

    EnvironmentLight* light_ptr = new EnvironmentLight;
    light_ptr->set_material(emissive_ptr);
    light_ptr->set_sampler(new MultiJittered(num_samples));
    light_ptr->set_shadows(true);
    add_light(light_ptr);

    Pinhole* pin = new Pinhole(Point3D(0, 0, 100), Point3D(0, 0, -100));
    pin->set_view_distance(100);
    set_camera(pin);

    ambient_ptr = new AmbientLight;

    Sphere* sphere = new Sphere(Point3D(0, 0, 0), 50);
    Matte* matte = new Matte;
    sphere->set_material(matte);
    add_object(sphere);
}