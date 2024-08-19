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
#include "../Materials/SV_Reflective.hpp"
#include "../Materials/SV_PlaneChecker.hpp"

// utilities
#include "../Utilities/Vector3D.hpp"
#include "../Utilities/Point2D.hpp"
#include "../Utilities/Point3D.hpp"
#include "../Utilities/Normal.hpp"
#include "../Utilities/Maths.hpp"
#include "../Materials/GlossyReflectorMaterial.hpp"

void buildGlossy(World *pWorld){
	int num_samples = 256;   // use 1 for testing!

	pWorld->vp.set_hres(600);
	pWorld->vp.set_vres(400);
	pWorld->vp.set_samples(num_samples);
	pWorld->vp.set_max_depth(10);

	pWorld->tracer_ptr = new Whitted(pWorld);

	pWorld->background_color = black;

	AmbientOccluderLight* ambient_occluder_ptr = new AmbientOccluderLight;
	ambient_occluder_ptr->set_sampler(new MultiJittered(num_samples));
	ambient_occluder_ptr->set_min_amount(0.5);
	pWorld->set_ambient_light(ambient_occluder_ptr);


	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(100, 45, 100);
	pinhole_ptr->set_lookat(-10, 35, 0);
	pinhole_ptr->set_view_distance(400);
	pinhole_ptr->compute_uvw();
	pWorld->set_camera(pinhole_ptr);


	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(150, 250, -150);
	light_ptr2->scale_radiance(1.5);
	light_ptr2->set_shadows(true);
	pWorld->add_light(light_ptr2);

	float exp = 100.00;

	GlossyReflector* glossy_ptr1 = new GlossyReflector;
	glossy_ptr1->set_samples(num_samples, 100.0);
	glossy_ptr1->set_ka(0.2);
	glossy_ptr1->set_kd(0.3);
	glossy_ptr1->set_ks(0.4);
	glossy_ptr1->set_exp(exp);
	glossy_ptr1->set_cd(1.0, 1.0, 0.3);	 // orange
	glossy_ptr1->set_kr(0.7);
	glossy_ptr1->set_exponent(exp);
	glossy_ptr1->set_cr(1.0, 0.75, 0.5);  // orange

	Sphere* sphere_ptr1 = new Sphere(Point3D(38, 20, -24), 20);
	sphere_ptr1->set_material(glossy_ptr1);
	pWorld->add_object(sphere_ptr1);


	// ground plane

	SV_PlaneChecker* sv_plane_checker_left_ptr = new SV_PlaneChecker;
	sv_plane_checker_left_ptr->set_size(20.0);
	sv_plane_checker_left_ptr->set_line_width(2);
	sv_plane_checker_left_ptr->set_color1(new ConstantColor(RGBColor(0.5)));
	sv_plane_checker_left_ptr->set_color2(new ConstantColor(RGBColor(0.5)));
	sv_plane_checker_left_ptr->set_line_color(new ConstantColor(RGBColor(0.2)));

	SV_Reflective* reflective_ptr1 = new SV_Reflective;
	reflective_ptr1->set_ka(0.4);               // ambient reflection, ka=0.4
	reflective_ptr1->set_kd(0.8);               // diffuse reflection, kd=0.8
	reflective_ptr1->set_cd(sv_plane_checker_left_ptr);    	// light green
	reflective_ptr1->set_ks(0.5);               // specular reflection, ks=0.5
	reflective_ptr1->set_exp(50.0);             // 50.0
	reflective_ptr1->set_kr(0.1);              // indirect, mirror reflection, kr=0.75
	reflective_ptr1->set_cr(new ConstantColor(white)); 	        // default color is (0.5, 0.5, 1.0)



	Plane* plane_ptr = new Plane(Point3D(0, 0.01, 0), Normal(0, 1, 0));
	plane_ptr->set_material(reflective_ptr1);
	pWorld->add_object(plane_ptr);
}
