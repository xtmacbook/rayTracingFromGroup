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

// utilities
#include "../Utilities/Vector3D.hpp"
#include "../Utilities/Point2D.hpp"
#include "../Utilities/Point3D.hpp"
#include "../Utilities/Normal.hpp"
#include "../Utilities/Maths.hpp"

void buildShadows(World* pWorld) {
	int num_samples = 16;
	
	pWorld->vp.set_hres(600);	  		
	pWorld->vp.set_vres(400);
	pWorld->vp.set_samples(num_samples);
	
	pWorld->background_color = RGBColor(15.0/255.0, 2.0/255.0, 47.0/255.0);

	pWorld->tracer_ptr = new RayCast(pWorld);
			
	Pinhole* camera_ptr = new Pinhole;
	camera_ptr->set_eye(Point3D(2, 2.5, 15));
	camera_ptr->set_lookat(Point3D(0 + 3, 2.5, 0));
	camera_ptr->set_view_distance(700);    
	camera_ptr->compute_uvw(); 
	pWorld->set_camera(camera_ptr);
	
	Directional* light_ptr1 = new Directional();
	light_ptr1->set_direction(Vector3D(200, 150, 125)); 
	light_ptr1->scale_radiance(4.0);
	light_ptr1->set_shadows(true);				// for Figure 16.1(b)
	pWorld->add_light(light_ptr1);
		
	PointLight* light_ptr2 = new PointLight();
	light_ptr2->set_location(Vector3D(-12, 15, 30)); 
	light_ptr2->scale_radiance(4.0);
	light_ptr2->set_shadows(true);				// for Figure 16.1(b)
	pWorld->add_light(light_ptr2);
		
	// sphere	
	Matte* matte_ptr1 = new Matte();			
	matte_ptr1->set_ka(0.3); 
	matte_ptr1->set_kd(0.3);
	matte_ptr1->set_cd(RGBColor(1, 0, 0)); 
	
	Sphere*	sphere_ptr1 = new Sphere(Point3D(0.0, 2.4, 0), 1.5); 
	sphere_ptr1->set_material(matte_ptr1);
	pWorld->add_object(sphere_ptr1);
	// box
	
	Matte* matte_ptr2 = new Matte();			
	matte_ptr2->set_ka(0.2); 
	matte_ptr2->set_kd(0.3);
	matte_ptr2->set_cd(RGBColor(0,1,0));
							
	Box* box_ptr1 = new Box(Point3D(5.4, -0.5, -3), Point3D(7.5-5.4, 4.75+0.5, 0.60+3.0));
	box_ptr1->set_material(matte_ptr2);
	pWorld->add_object(box_ptr1);
	// triangle
	
	Matte* matte_ptr3 = new Matte();			
	matte_ptr3->set_ka(0.35); 
	matte_ptr3->set_kd(0.50);
	matte_ptr3->set_cd(RGBColor(0, 0, 1));      // cyan

	Triangle* triangle_ptr1 = new Triangle(	Point3D(1.5, -0.5, 1.8), 		// front
											Point3D(7.5, -0.5, -9.00), 		// back
											Point3D(2.35, 5.8, 1.4));		// top									
	triangle_ptr1->set_material(matte_ptr3);        
	pWorld->add_object(triangle_ptr1);
	// cylinder
	
	float bottom 	= -0.5;
	float top 		= 1.0;
	float radius 	= 1.0;

	Cylinder* cylinder_ptr = new Cylinder(bottom, top, radius);
	cylinder_ptr->set_material(matte_ptr2->clone());
	pWorld->add_object(cylinder_ptr);
	// ground plane

	Matte* matte_ptr4 = new Matte();			
	matte_ptr4->set_ka(0.1); 
	matte_ptr4->set_kd(0.2);
	matte_ptr4->set_cd(white);
	
	Plane* plane_ptr = new Plane(Point3D(0, -0.5, 0), Normal(0.0, 1, 0.0));
	plane_ptr->set_material(matte_ptr4);
	pWorld->add_object(plane_ptr);
}