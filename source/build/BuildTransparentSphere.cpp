#pragma once
#include "../World/World.hpp"
#include "../Utilities/Constants.hpp"

// Window
#include "../Window/Window.hpp"
#include "../Window/Window-THREAD.hpp"
#include "../Window/Window-NOTHREAD.hpp"

// geometric objects
#include "../GeometricObjects/Plane.hpp"
#include "../GeometricObjects/Sphere.hpp"
#include "../GeometricObjects/Box.hpp"
#include "../GeometricObjects/Triangle.hpp"
#include "../GeometricObjects/Disk.hpp"
#include "../GeometricObjects/OpenCylinder.hpp"
#include "../GeometricObjects/Cylinder.hpp"
#include "../GeometricObjects/Grid.hpp"
#include "../GeometricObjects/SmoothMeshTriangle.hpp"
#include "../GeometricObjects/FlatMeshTriangle.hpp"
#include "../GeometricObjects/Rectangle.hpp"

// Lights
#include "../Light/Directional.hpp"
#include "../Light/PointLight.hpp"
#include "../Light/AmbientOccluderLight.hpp"
#include "../Light/AreaLight.hpp"

// Samplers
#include "../Samplers/MultiJittered.hpp"
#include "../Samplers/NRooks.hpp"

// tracers
//#include "../Tracers/MultipleObjects.hpp"
//#include "../Tracers/Sinusoid.hpp"
#include "../Tracers/RayCast.hpp"
#include "../Tracers/AreaLightingTracer.hpp"

#include "../Tracers/Whitted.hpp"

// Cameras
#include "../Cameras/Pinhole.hpp"
#include "../Cameras/Orthographic.hpp"
#include "../Cameras/ThinLens.hpp"

// Materials
#include "../Materials/Matte.hpp"
#include "../Materials/Phong.hpp"
#include "../Materials/Emissive.hpp"
#include "../Materials/Reflective.hpp"
#include "../Materials/Transparent.hpp"

// utilities
#include "../Utilities/Vector3D.hpp"
#include "../Utilities/Point2D.hpp"
#include "../Utilities/Point3D.hpp"
#include "../Utilities/Normal.hpp"
#include "../Utilities/Maths.hpp"

void buildTransparentSpere(World* pWorld) {
	int num_samples = 16;

	pWorld->vp.set_hres(300);
	pWorld->vp.set_vres(300);
	pWorld->vp.set_samples(num_samples);
	pWorld->vp.set_max_depth(4);			// for Figure 27.13(a)
	//	vp.set_max_depth(4);			// for Figure 27.13(b)
	//	vp.set_max_depth(6);			// for Figure 27.13(c)

	pWorld->background_color = RGBColor(0.0, 0.3, 0.25);

	pWorld->tracer_ptr = new Whitted(pWorld);

	AmbientLight* ambient_ptr = new AmbientLight;
	ambient_ptr->scale_radiance(0.25);
	pWorld->set_ambient_light(ambient_ptr);

	Pinhole* pinhole_ptr = new Pinhole;


	pinhole_ptr->set_eye(3.5, 5.5, 40);
	pinhole_ptr->set_lookat(3.5, 4, 0);
	pinhole_ptr->set_view_distance(2400.0);
	pinhole_ptr->compute_uvw();
	pWorld->set_camera(pinhole_ptr);


	// point light

	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(30, 50, 10);
	light_ptr1->scale_radiance(4.5);
	light_ptr1->set_shadows(true);
	pWorld->add_light(light_ptr1);


	// point light

	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(-30, 50, 10);
	light_ptr2->scale_radiance(4.5);
	light_ptr2->set_shadows(true);
	pWorld->add_light(light_ptr2);


	// transparent sphere

	Transparent* glass_ptr = new Transparent;
	glass_ptr->set_ks(0.2);
	glass_ptr->set_exp(2000.0);
	glass_ptr->set_ior(0.8);
	glass_ptr->set_kr(0.1);
	glass_ptr->set_kt(0.9);

	Sphere* pTransparentSphere = new Sphere(Point3D(3, 3.5, 0), 1);
	pTransparentSphere->set_material(glass_ptr);
	pWorld->add_object(pTransparentSphere);


	// red sphere

	Reflective* reflective_ptr = new Reflective;
	reflective_ptr->set_ka(0.3);
	reflective_ptr->set_kd(0.3);
	reflective_ptr->set_cd(red);
	reflective_ptr->set_ks(0.2);
	reflective_ptr->set_exp(2000.0);
	reflective_ptr->set_kr(0.25);

	Sphere* sphere_ptr2 = new Sphere(Point3D(4, 4, -6), 1.2);
	sphere_ptr2->set_material(reflective_ptr);
	pWorld->add_object(sphere_ptr2);


	Phong* phong_ptr2 = new Phong;
	phong_ptr2->set_ka(0.4);
	phong_ptr2->set_kd(0.8);
	phong_ptr2->set_cd(0.5, 0.5, 1.0);
	phong_ptr2->set_ks(0.5);
	//	phong_ptr2->set_cs(1.0, 1.0, 0.0);
	phong_ptr2->set_exp(50.0);


	// rectangle

	Rectangle* rectangle_ptr = new Rectangle(Point3D(-20, 2.3, -100), Vector3D(0, 0, 120), Vector3D(40, 0, 0));
	rectangle_ptr->set_material(phong_ptr2);
	pWorld->add_object(rectangle_ptr);
}

/*
	﻿
In Figure 27.13(a), with max_depth = 2, why does the scene appear slightly darker when seen through the transparent sphere?
. In Figure 7.13(b), with max_depth = 4, what is the dark disk near the middle of the red sphere? What has happened to it in Figure 27.13(c), where max_depth = 5?

In Figure 27.13(b) and (c), a faint image of the checkers is visible in the top part of the transparent sphere,
and a faint image of the red sphere is also visible.How are these formed?

*/