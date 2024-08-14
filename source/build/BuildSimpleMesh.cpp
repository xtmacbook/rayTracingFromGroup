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

void buildSimpleMesh(World* pWorld) {
	int num_samples = 16;
	
	pWorld->vp.set_hres(400);      
	pWorld->vp.set_vres(400);    
	pWorld->vp.set_samples(num_samples);	
	
	pWorld->tracer_ptr = new RayCast(pWorld);
	
	pWorld->background_color = black;

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(Point3D(100, 50, 90));
	pinhole_ptr->set_lookat(Point3D(0, -0.5, 0));
	pinhole_ptr->set_view_distance(16000);  	
	pinhole_ptr->compute_uvw();     
	pWorld->set_camera(pinhole_ptr);
		
	Directional* directional_ptr = new Directional;
	directional_ptr->set_direction(Point3D(0.75, 1, -0.15));     
	directional_ptr->scale_radiance(4.5);
	pWorld->add_light(directional_ptr);
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.1); 
	matte_ptr1->set_kd(0.75);   
	matte_ptr1->set_cd(RGBColor(0.1, 0.5, 1.0));
	 	
	char* file_name;
	strcpy(file_name, "TwoTriangles.ply");
	Grid* grid_ptr = new Grid(new Mesh);
	grid_ptr->read_flat_triangles(file_name);		// for Figure 23.7(a)
//	grid_ptr->read_smooth_triangles(file_name);		// for Figure 23.7(b)
	grid_ptr->set_material(matte_ptr1);   
	grid_ptr->setup_cells();
	pWorld->add_object(grid_ptr);
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_cd(RGBColor(1, 0.9, 0.6));
	matte_ptr2->set_ka(0.25); 
	matte_ptr2->set_kd(0.4);
		
	Plane* plane_ptr1 = new Plane(Point3D(0, -2.0, 0), Normal(0, 1, 0));  
	plane_ptr1->set_material(matte_ptr2);
	pWorld->add_object(plane_ptr1);
}