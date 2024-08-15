#pragma once

#include "../World/World.hpp"

#include "../Light/EnvironmentLight.hpp"
#include "../Light/Directional.hpp"
#include "../light/AmbientLight.hpp"

#include "../Tracers/AreaLightingTracer.hpp"
#include "../Cameras/Pinhole.hpp"

#include "../Materials/Matte.hpp"
#include "../Materials/Reflective.hpp"
#include "../Materials/Emissive.hpp"

#include "../GeometricObjects/Sphere.hpp"
#include "../GeometricObjects/Cylinder.hpp"
#include "../GeometricObjects/ConcaveSphere.hpp"

#include "../GeometricObjects/Plane.hpp"
#include "../GeometricObjects/Box.hpp"

void initObj(World&world)
{
	float ka = 0.25;
	float kd = 0.75;

	//init object
	/*float radius = 23.0;
	Sphere* sphere_ptr1 = new Sphere(Point3D(38, radius, -25), radius);
	sphere_ptr1->set_material(reflective_ptr1);
	world.add_object(sphere_ptr1);*/


	// orange non-reflective sphere

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.45);
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(0.75, 0.25, 0);   // orange

	Sphere* sphere_ptr2 = new Sphere(Point3D(-7, 10, 42), 20);
	sphere_ptr2->set_material(matte_ptr1);
	world.add_object(sphere_ptr2);


	// sphere on top of box

	Reflective* reflective_ptr2 = new Reflective;
	reflective_ptr2->set_ka(0.35);
	reflective_ptr2->set_kd(0.75);
	reflective_ptr2->set_cd(black);
	reflective_ptr2->set_ks(0.0);		// default value
	reflective_ptr2->set_exp(1.0);		// default value, but irrelevant in this case
	reflective_ptr2->set_kr(0.75);
	reflective_ptr2->set_cr(white);

	Sphere* sphere_ptr3 = new Sphere(Point3D(-30, 59, 35), 20);
	sphere_ptr3->set_material(reflective_ptr2);
	world.add_object(sphere_ptr3);


	// cylinder

	Reflective* reflective_ptr3 = new Reflective;
	reflective_ptr3->set_ka(0.35);
	reflective_ptr3->set_kd(0.5);
	reflective_ptr3->set_cd(0, 0.5, 0.75);   // cyan
	reflective_ptr3->set_ks(0.2);
	reflective_ptr3->set_exp(100.0);
	reflective_ptr3->set_kr(0.75);
	reflective_ptr3->set_cr(white);

	double bottom = 0.0;
	double top = 85;
	double cylinder_radius = 22;
	Cylinder* cylinder_ptr = new Cylinder(bottom, top, cylinder_radius);
	cylinder_ptr->set_material(reflective_ptr3);
	world.add_object(cylinder_ptr);


	// box
	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.15);
	matte_ptr2->set_kd(0.5);
	matte_ptr2->set_cd(0.75, 1.0, 0.75);   // light green

	Box* box_ptr = new Box(Point3D(-35, 0, -110), Point3D(-25, 60, 65));
	box_ptr->set_material(matte_ptr2);
	world.add_object(box_ptr);


	Plane* plane = new Plane(Point3D(0), Normal(0, 1, 0));
	plane->set_material(matte_ptr2->clone(white));
	world.add_object(plane);
}

void buildEnvirOnmentLight(World*pWorld){
	
	int num_samples = 64;

    //init vp
	pWorld->vp.set_hres(600);
	pWorld->vp.set_vres(400);
	pWorld->vp.set_samples(num_samples);

	pWorld->background_color = black;

    //init tracer------------------------------------------------------------------------
	pWorld->tracer_ptr = new AreaLightingTracer(pWorld);

	//init camera ------------------------------------------------------------------------
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(75, 40, 100);
	pinhole_ptr->set_lookat(-10, 39, 0);
	pinhole_ptr->set_view_distance(360);
	pinhole_ptr->compute_uvw();
	pWorld->set_camera(pinhole_ptr);

    //init light ------------------------------------------------------------------------
	AmbientLight* ambient_ptr = new AmbientLight;
	ambient_ptr->scale_radiance(0.5);
	pWorld->set_ambient_light(ambient_ptr);

	//Regular* sampler_ptr = new Regular(num_samples);
	////MultiJittered* sampler_ptr = new MultiJittered();
	//AmbientOccluderLight* occluder_ptr = new AmbientOccluderLight;
	//occluder_ptr->scale_radiance(0.5);
	//occluder_ptr->set_min_amount(0.3);
	//occluder_ptr->set_sampler(sampler_ptr);
	//set_ambient_light(occluder_ptr);

    Emissive* emissive_ptr = new Emissive;
    emissive_ptr->set_ce(1.0, 1.0, 1.0);
    emissive_ptr->scale_radiance(1.0);

    ConcaveSphere* sphere_ptr = new ConcaveSphere;
    sphere_ptr->set_radius(1000000.0);
    sphere_ptr->set_material(emissive_ptr);
    sphere_ptr->set_casts_shadows(false);
    pWorld->add_object(sphere_ptr);

    EnvironmentLight* light_ptr = new EnvironmentLight;
    light_ptr->set_material(emissive_ptr);
    light_ptr->set_sampler(new MultiJittered(num_samples));
    light_ptr->set_shadows(true);
	pWorld->add_light(light_ptr);


	Directional* light_ptr1 = new Directional();
	light_ptr1->set_direction(Vector3D(20, 150, 125));
	light_ptr1->scale_radiance(4.0);
	light_ptr1->set_shadows(true);				// for Figure 16.1(b)
	pWorld->add_light(light_ptr1);

	//init objects ------------------------------------------------------------------------
	initObj(*pWorld);
}