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

void buildGlossy(World *pWorld){
	int num_samples = 16;
	
	pWorld->vp.set_hres(600);
	pWorld->vp.set_vres(400);
	pWorld->vp.set_samples(num_samples);
	
	pWorld->tracer_ptr = new RayCast(pWorld);
			
	AmbientLight* ambient_ptr = new AmbientLight;
	ambient_ptr->scale_radiance(0.01);
	pWorld->set_ambient_light(ambient_ptr);
	
	float a = 0.75;
	pWorld->background_color = RGBColor(0.0, 0.3 * a, 0.25 * a);  // torquise
			
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(Point3D(1, 1, -6)); 
	pinhole_ptr->set_lookat(Point3D(0, 0, 0));  
	pinhole_ptr->set_view_distance(360);		
	pinhole_ptr->compute_uvw(); 
	pWorld->set_camera(pinhole_ptr);
	
	Directional* light_ptr1 = new Directional;	// for Figure 15.8(a)
	light_ptr1->set_direction(15, 15, 2.5); 
	light_ptr1->scale_radiance(2.0);	
//	add_light(light_ptr1);
	
	PointLight* light_ptr2 = new PointLight;	// for Figure 15.8(b)
	light_ptr2->set_location(Vector3D(15, 15, 2.5)); 
	light_ptr2->scale_radiance(2.0);	
	pWorld->add_light(light_ptr2);
	
	
	Phong* phong_ptr1 = new Phong;			
	phong_ptr1->set_ka(0.25); 
	phong_ptr1->set_kd(0.75);
	phong_ptr1->set_cd(RGBColor(0.75, 0.75, 0));  	// dark yellow
	phong_ptr1->set_ks(0.25);
	phong_ptr1->set_exp(50);
	
	Phong* phong_ptr2 = new Phong;			
	phong_ptr2->set_ka(0.45); 
	phong_ptr2->set_kd(0.75);
	phong_ptr2->set_cd(RGBColor(0.75, 0.25, 0));   	// orange
	phong_ptr2->set_ks(0.25);
	phong_ptr2->set_exp(500);
		
	Matte* matte_ptr5 = new Matte;			
	matte_ptr5->set_ka(0.20); 
	matte_ptr5->set_kd(0.97);	
	matte_ptr5->set_cd(white);  
	
	// spheres
	Sphere* sphere_ptr1 = new Sphere(Point3D(0.0, 0.0, 4.2), 2.3);
	sphere_ptr1->set_material(phong_ptr1);
	pWorld->add_object(sphere_ptr1);
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(3.7, 0.0, 6.2), 2);
	sphere_ptr2->set_material(phong_ptr2);     
	pWorld->add_object(sphere_ptr2);

	Sphere* sphere_ptr3 = new Sphere(Point3D(-6.0, 0.0, 6.2), 2);
	sphere_ptr3->set_material(phong_ptr2);
	pWorld->add_object(sphere_ptr3);

	// ground plane
	Plane* plane_ptr = new Plane(Point3D(0,-2,0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr5);
	pWorld->add_object(plane_ptr);
}