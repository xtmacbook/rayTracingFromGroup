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
#include "../GeometricObjects/Instance.hpp"
#include "../GeometricObjects/ConcaveSphere.hpp"

// Lights
#include "../Light/Directional.hpp"
#include "../Light/PointLight.hpp"
#include "../Light/AmbientOccluderLight.hpp"
#include "../Light/AreaLight.hpp"

// Samplers
#include "../Samplers/MultiJittered.hpp"
#include "../Samplers/NRooks.hpp"

// tracers
#include "../Tracers/RayCast.hpp"
#include "../Tracers/AreaLightingTracer.hpp"

#include "../Tracers/Whitted.hpp"

// Cameras
#include "../Cameras/Pinhole.hpp"
#include "../Cameras/Orthographic.hpp"
#include "../Cameras/ThinLens.hpp"
#include "../Cameras/FishEye.hpp"

// Materials
#include "../Materials/Matte.hpp"
#include "../Materials/Phong.hpp"
#include "../Materials/Emissive.hpp"
#include "../Materials/Reflective.hpp"
#include "../Materials/Transparent.hpp"
#include "../Materials/Dielectric.hpp"
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

void addMeshObj(World* pWorld)
{
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(2.5, 5.5, 24);
	pinhole_ptr->set_lookat(2.5, 3, 0);
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

	std::string fileName = getDataPath() + "ply/dragon.ply"; 	    // 10000 triangles

	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_ks(0.2);
	dielectric_ptr->set_exp(2000.0);
	dielectric_ptr->set_eta_in(1.6);
	dielectric_ptr->set_eta_out(1.0);
	dielectric_ptr->set_cf_in(0.3,0.5,0.3);
	dielectric_ptr->set_cf_out(0.2, 0.4, 0.6);

	float ka = 0.25;
	float kd = 0.75;
	Matte* matte_ptr = new Matte;
	matte_ptr->set_ka(ka);
	matte_ptr->set_kd(kd);
	matte_ptr->set_cd(dark_green);

	Material* bunyMaterial = dielectric_ptr;

	Grid* bunny_ptr = new Grid(new Mesh);
	bunny_ptr->reverse_mesh_normals();				// you must use this for the 10K model
	bunny_ptr->read_smooth_triangles(fileName.c_str());		// read PLY file
	bunny_ptr->set_material(bunyMaterial);
	bunny_ptr->setup_cells();

	Instance* instance_ptr = new Instance;
	instance_ptr->set_object(bunny_ptr);
	instance_ptr->set_material(bunyMaterial);
	instance_ptr->scale(10.0);
	instance_ptr->translate(2.5, 1.5, 0.0);
	pWorld->add_object(instance_ptr);
}

void addRSphere(World* pWorld)
{
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
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_ks(0.2);
	dielectric_ptr->set_exp(2000.0);
	dielectric_ptr->set_eta_in(1.6);
	dielectric_ptr->set_eta_out(1.0);
	dielectric_ptr->set_cf_in(1.0);
	dielectric_ptr->set_cf_out(1.0);
	Sphere* dieSphere = new Sphere(Point3D(3, 3.5, 0), 1);
	dieSphere->set_material(dielectric_ptr);
	pWorld->add_object(dieSphere);

	// red sphere
	Reflective* reflective_ptr = new Reflective;
	reflective_ptr->set_ka(0.3);
	reflective_ptr->set_kd(0.3);
	reflective_ptr->set_cd(red);
	reflective_ptr->set_ks(0.2);
	reflective_ptr->set_exp(2000.0);
	reflective_ptr->set_kr(0.25);

	Sphere* redSphere = new Sphere(Point3D(4, 4, -6), 1.2);
	redSphere->set_material(reflective_ptr);
	pWorld->add_object(redSphere);
}

void addFlatSurface(World* pWorld)
{
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(30, 50, 80);
	light_ptr1->scale_radiance(4.5);
	light_ptr1->set_shadows(true);
	pWorld->add_light(light_ptr1);

	// point light
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(-30, 50, 80);
	light_ptr2->scale_radiance(4.5);
	light_ptr2->set_shadows(true);
	pWorld->add_light(light_ptr2);

	Point3D eye(0.0, 0.0, 40);
	Point3D lookAt(0.0, 0.0, 0);
	FishEyeCamera* pFishCamera = new FishEyeCamera(eye, lookAt);
	pFishCamera->set_view_distance(240.0); //
	pFishCamera->compute_uvw();
	pFishCamera->set_psi_max(10);
	pWorld->set_camera(pFishCamera);

	float ka = 0.25;
	float kd = 0.75;
	Matte* matte_ptr = new Matte;
	matte_ptr->set_ka(ka);
	matte_ptr->set_kd(kd);
	matte_ptr->set_cd(dark_green);

	Material* transparentMaterial = nullptr;
	if(1)
	{
		Transparent* glass_ptr = new Transparent;
		glass_ptr->set_ks(0.2);
		glass_ptr->set_exp(2000.0);
		glass_ptr->set_ior(1.1);
		glass_ptr->set_kr(0.1);
		glass_ptr->set_kt(0.9);
		transparentMaterial = glass_ptr;
	}
	else
	{
		Dielectric* dielectric_ptr = new Dielectric;
		dielectric_ptr->set_ks(0.2);
		dielectric_ptr->set_exp(2000.0);
		dielectric_ptr->set_eta_in(1.5);
		dielectric_ptr->set_eta_out(1.0);
		dielectric_ptr->set_cf_in(1.0);
		dielectric_ptr->set_cf_out(1.0);
		transparentMaterial = dielectric_ptr;
	}
	

	Cylinder* cylinder = new Cylinder(0.001, 0.002, 5.0);
	cylinder->set_material(transparentMaterial);
	Instance* instance_ptr = new Instance;
	instance_ptr->set_object(cylinder);
	instance_ptr->rotate_x(90.0);
	pWorld->add_object(instance_ptr);
}

void BuildRealisticTransparent(World* pWorld) {
	
	int num_samples = 16;

	pWorld->vp.set_hres(300);
	pWorld->vp.set_vres(300);
	pWorld->vp.set_samples(num_samples);
	pWorld->vp.set_max_depth(6);
	pWorld->background_color = black;
	pWorld->tracer_ptr = new Whitted(pWorld);

	AmbientLight* ambient_ptr = new AmbientLight;
	ambient_ptr->scale_radiance(0.25);
	pWorld->set_ambient_light(ambient_ptr);

	//addFlatSurface(pWorld);
	//addRSphere(pWorld);
	addMeshObj(pWorld);

	Checker3D* check_texture = new Checker3D();
	check_texture->set_size(2.0);
	check_texture->set_color1(0.5, 0.5, 0.5);
	check_texture->set_color2(1.0, 1.0, 1.0);
	SV_Matte* check_matte(new SV_Matte);
	check_matte->set_ka(0.25);
	check_matte->set_kd(0.75);
	check_matte->set_cd(check_texture);

	Rectangle* rectangle_ptr = new Rectangle(Point3D(-20, 1.3, -100), Vector3D(0, 0, 120), Vector3D(40, 0, 0));
	rectangle_ptr->set_material(check_matte);
	pWorld->add_object(rectangle_ptr);
}

 