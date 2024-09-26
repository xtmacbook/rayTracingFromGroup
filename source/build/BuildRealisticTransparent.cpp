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
#include "../GeometricObjects/GlassOfWater.hpp"

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
	dielectric_ptr->set_cf_in(0.3, 0.5, 0.3);
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

void buildTransparentCube(World* pWorld)
{
	pWorld->background_color = white;

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(2.5, 2.5, 24);
	pinhole_ptr->set_lookat(2.5, 2.5, 0);
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

	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_ks(0.2);
	dielectric_ptr->set_exp(2000.0);
	dielectric_ptr->set_eta_in(1.5);
	dielectric_ptr->set_eta_out(1.0);
	dielectric_ptr->set_cf_in(0.9, 0.6, 0.7);
	dielectric_ptr->set_cf_out(1.0);

	Box* box_ptr = new Box(Point3D(2, 2, 5), Point3D(3, 3,10), dielectric_ptr);
	pWorld->add_object(box_ptr);

	Checker3D* check_texture = new Checker3D();
	check_texture->set_size(4.0);
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
	if (1)
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

void buildGlassOfWater(World* pWorld)
{
	int num_samples = 16;

	pWorld->vp.set_hres(600);
	pWorld->vp.set_vres(600);
	pWorld->vp.set_samples(num_samples);
	pWorld->vp.set_max_depth(10);
	pWorld->background_color = RGBColor(0.5);
	pWorld->tracer_ptr = new Whitted(pWorld);

	AmbientLight* ambient_ptr = new AmbientLight;
	ambient_ptr->scale_radiance(0.5);
	pWorld->set_ambient_light(ambient_ptr);


	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(5, 6, 10);   
	pinhole_ptr->set_lookat(0, 1, 0);
	pinhole_ptr->set_view_distance(2000.0); // for a, c
	pinhole_ptr->compute_uvw();
	pWorld->set_camera(pinhole_ptr);


	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(40, 50, 30);
	light_ptr1->scale_radiance(3.0);
	light_ptr1->set_shadows(true); // a: false; c: true
	pWorld->add_light(light_ptr1);


	// materials for the glass of water
	// glass-air boundary
	RGBColor glass_color(0.65, 1, 0.75);
	RGBColor water_color(1, 0.25, 1);

	Dielectric* glass_ptr = new Dielectric;
	glass_ptr->set_eta_in(1.50);			// glass
	glass_ptr->set_eta_out(1.0);			// air
	glass_ptr->set_cf_in(glass_color);
	glass_ptr->set_cf_out(white);

	// water-air boundary
	Dielectric* water_ptr = new Dielectric;
	water_ptr->set_eta_in(1.33);			// water
	water_ptr->set_eta_out(1.0);			// air
	water_ptr->set_cf_in(water_color);
	water_ptr->set_cf_out(white);

	// water-glass boundary
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_eta_in(1.33); 		// water
	dielectric_ptr->set_eta_out(1.50); 		// glass
	dielectric_ptr->set_cf_in(water_color);
	dielectric_ptr->set_cf_out(glass_color);

	// Define the GlassOfWater object
	// The parameters below are the default values, but using the constructor that
	// takes these as arguments makes it easier to experiment with different values

	float height = 2.0;
	float inner_radius = 0.9;
	float wall_thickness = 0.1;
	float base_thickness = 0.3;
	float water_height = 1.5;
	float meniscus_radius = 0.1;

	GlassOfWater* glass_of_water_ptr = new GlassOfWater(height,
		inner_radius,
		wall_thickness,
		base_thickness,
		water_height,
		meniscus_radius);

	glass_of_water_ptr->set_glass_air_material(glass_ptr);
	glass_of_water_ptr->set_water_air_material(water_ptr);
	glass_of_water_ptr->set_water_glass_material(dielectric_ptr);
	pWorld->add_object(glass_of_water_ptr);

	// define the straw
	Matte* matte_ptr = new Matte;
	matte_ptr->set_cd(1, 1, 0);
	matte_ptr->set_ka(0.25);
	matte_ptr->set_kd(0.65);

	auto straw = new OpenCylinder(-1.2, 1.7, 0.05);
	straw->set_casts_shadows(true);
	Instance* straw_ptr = new Instance(straw);
	straw_ptr->set_material(matte_ptr);
	straw_ptr->rotate_z(40);
	straw_ptr->translate(0, 1.25, 0);
	pWorld->add_object(straw_ptr);

	// ground plane
	Phong* phong_ptr2 = new Phong;
	phong_ptr2->set_ka(0.4);
	phong_ptr2->set_kd(0.8);
	phong_ptr2->set_cd(0.5, 0.5, 1.0);
	phong_ptr2->set_ks(0.5);
	//	phong_ptr2->set_cs(1.0, 1.0, 0.0);
	phong_ptr2->set_exp(50.0);

	Plane* plane_ptr = new Plane(Point3D(0, -0.01, 0), Normal(0, 1, 0));
	plane_ptr->set_material(phong_ptr2);
	pWorld->add_object(plane_ptr);
}

void BuildRealisticTransparent(World* pWorld) {

	int num_samples = 16;

	pWorld->vp.set_hres(300);
	pWorld->vp.set_vres(300);
	pWorld->vp.set_samples(num_samples);
	pWorld->vp.set_max_depth(4); 
	pWorld->background_color = black;
	pWorld->tracer_ptr = new Whitted(pWorld);

	AmbientLight* ambient_ptr = new AmbientLight;
	ambient_ptr->scale_radiance(0.25);
	pWorld->set_ambient_light(ambient_ptr);

	//addFlatSurface(pWorld);
	//addRSphere(pWorld);
	//addMeshObj(pWorld);
	buildTransparentCube(pWorld);

}

