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
#include "../GeometricObjects/ConcaveSphere.hpp"
#include "../GeometricObjects/Torus.hpp"
#include "../GeometricObjects/Instance.hpp"
#include "../GeometricObjects/TorusPartConcave.hpp"


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
#include "../Materials/SV_Matte.hpp"

// utilities
#include "../Utilities/Vector3D.hpp"
#include "../Utilities/Point2D.hpp"
#include "../Utilities/Point3D.hpp"
#include "../Utilities/Normal.hpp"
#include "../Utilities/Maths.hpp"
#include "../Utilities/util.hpp"


#include <memory>
#include "../Texture/Checker3D.hpp"

/*

regardless of the value of n, no rays transmitted through the sphere are totally internally reflected when they hit the sphere from the inside.
We therefore have the following result: no total internal reflection occurs from inside a sphere when the sphere is ray traced from the outside.
This means that all rays that enter the sphere bring back some radiance from the scene through their external transmitted rays, 
even if it's just the background color. 
*/


void addSphere(World* pWorld)
{
	// transparent sphere
	Transparent* glass_ptr = new Transparent;
	glass_ptr->set_ks(0.2);
	glass_ptr->set_exp(2000.0);
	glass_ptr->set_ior(0.75);
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
}

void addConcaveSphere(World* pWorld)
{
	Transparent* glass_ptr = new Transparent;
	glass_ptr->set_ks(0.2);
	glass_ptr->set_exp(2000.0);
	glass_ptr->set_ior(1.1);
	glass_ptr->set_kr(0.1);
	glass_ptr->set_kt(0.9);


	Matte* matte = new Matte;
	float ka = 0.25;
	float kd = 0.75;
	matte->set_ka(ka);
	matte->set_kd(kd);
	matte->set_cd(yellow);

	Point3D modelPos(4, 4, -8);
	Torus* pTransparentSphere = new Torus(2,0.5);
	pTransparentSphere->set_material(matte);
	Instance* instance_ptr = new Instance;
	instance_ptr->set_object(pTransparentSphere);
	instance_ptr->rotate_z(60.0);
	instance_ptr->rotate_y(30.0);
	//instance_ptr->scale(0.3);
	instance_ptr->translate(modelPos);

	pWorld->add_object(instance_ptr);
}

void buildTransparent1(World* pWorld) {
	int num_samples = 16;

	pWorld->vp.set_hres(300);
	pWorld->vp.set_vres(300);
	pWorld->vp.set_samples(num_samples);
    pWorld->vp.set_max_depth(5);
	pWorld->background_color =  black;
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


	//addSphere(pWorld);
	addConcaveSphere(pWorld);

	Checker3D* check_texture = new Checker3D();
	check_texture->set_size(1.0);
	check_texture->set_color1(0.5, 0.5, 0.5);
	check_texture->set_color2(1.0, 1.0, 1.0); 
	SV_Matte* check_matte(new SV_Matte);
	check_matte->set_ka(0.25);
	check_matte->set_kd(0.75);
	check_matte->set_cd(check_texture);

	Rectangle* rectangle_ptr = new Rectangle(Point3D(-20, 2.3, -100), Vector3D(0, 0, 120), Vector3D(40, 0, 0));
	rectangle_ptr->set_material(check_matte);
	pWorld->add_object(rectangle_ptr);
}

#define TYPE 4

void buildTransparent(World* pWorld)
{
	int num_samples = 1;

	pWorld->vp.set_hres(300);
	pWorld->vp.set_vres(300);
	pWorld->vp.set_samples(num_samples);
	pWorld->tracer_ptr = new RayCast(pWorld);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 10, 20);
	pinhole_ptr->set_lookat(0, 0, 0);
	pinhole_ptr->set_view_distance(500);
	pinhole_ptr->compute_uvw();
	pWorld->set_camera(pinhole_ptr);

	Directional* light_ptr = new Directional;
	light_ptr->set_direction(-10, 20, 20);
	light_ptr->scale_radiance(3.0);
	light_ptr->set_shadows(false);
	pWorld->add_light(light_ptr);

	ConstantColor* cc_ptr = new ConstantColor;
	cc_ptr->set_color(0.0, 1.0, 0.0);

	SV_Matte* matte_ptr = new SV_Matte;
	matte_ptr->set_ka(0.25);
	matte_ptr->set_kd(0.75);
	matte_ptr->set_cd(cc_ptr);

#if TYPE == 0
	Disk* disk_ptr = new Disk(Point3D(0, 0, 0), Normal(0, 0, 1),2);
	disk_ptr->set_material(matte_ptr);
	pWorld->add_object(disk_ptr);
#endif // TYPE

#if TYPE == 1
	Annulus* annulus_ptr = new Annulus(Point3D(0, 0, 0), Normal(0, 0, 1), 1, 2);
	annulus_ptr->set_material(matte_ptr);
	add_object(annulus_ptr);
#endif // TYPE

#if TYPE == 2
	OpenCylinderConvex* oclinder_convex_ptr = new OpenCylinderConvex(-2, 2, 2);
	oclinder_convex_ptr->set_material(matte_ptr);
	add_object(oclinder_convex_ptr);
#endif // TYPE

#if TYPE == 3
	OpenCylinderConcave* oclinder_concave_ptr = new OpenCylinderConcave(-2, 2, 2);
	oclinder_concave_ptr->set_material(matte_ptr);
	add_object(oclinder_concave_ptr);
#endif // TYPE

#if TYPE == 4
	Torus* torus_ptr = new Torus(2, 0.5);
	torus_ptr->set_material(matte_ptr);
	pWorld->add_object(torus_ptr);
#endif // TYPE

#if TYPE == 5
	TorusPart* tp_ptr = new TorusPart(2.0, 0.5, 0.0, 270.0, 90.0, 360.0);
	tp_ptr->set_material(matte_ptr);
	add_object(tp_ptr);
#endif // TYPE

#if TYPE == 6
	TorusPartConcave* tpc_ptr = new TorusPartConcave(2.0, 0.5, 0.0, 360.0, 270.0, 360.0);
	tpc_ptr->set_material(matte_ptr);
	pWorld->add_object(tpc_ptr);
#endif // TYPE
}
