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
#include "../Utilities/util.hpp"

void buildBuildBox(World*pWorld){
	// view plane
	pWorld->vp.set_hres(800);
	pWorld->vp.set_vres(800);
	pWorld->vp.set_pixel_size(1);
	pWorld->vp.set_sampler(new Jittered(4));

	pWorld->background_color = black;

	//Ambient* ambient_ptr = new Ambient;
	//ambient_ptr->set_ls(1);
	//set_ambient_light(ambient_ptr);

	pWorld->tracer_ptr = new RayCast(pWorld);

	ThinLens* pinhole_ptr = new ThinLens(Point3D(10, 60, 60), Point3D(0, -10, -100));
	pinhole_ptr->set_view_distance(100);
	pinhole_ptr->set_sampler(new Jittered(100, 100));
	pinhole_ptr->set_lens_radius(0);
	pinhole_ptr->set_focal_dist(60);
	pinhole_ptr->compute_uvw();
	pWorld->set_camera(pinhole_ptr);

	PointLight* point_light = new PointLight(Vector3D(10, 20, 50), 4);
	pWorld->add_light(point_light);

    //Directional* directional_light = new Directional(Vector3D(0, 0.7, 1), 3.5);
    //add_light(directional_light);

    Box* box;
    Plane* plane;
    Sphere* sphere;
	Triangle* triangle;
	Disk* disk;
	OpenCylinder* openc;
	Cylinder* cylinder;

	float ka = 0.25;
	float kd = 0.75;

	Matte* matte = new Matte;
	matte->set_ka(ka);
	matte->set_kd(kd);
	matte->set_cd(yellow);

	cylinder = new Cylinder(0, 25, 15);
	cylinder->set_material(matte->clone(red));
	pWorld->add_object(cylinder);

	cylinder = cylinder->clone();
	cylinder->set_y1(45);
	cylinder->set_material(matte->clone(green));
	pWorld->add_object(cylinder);

    plane = new Plane(Point3D(0), Normal(0, 1, 0));
    plane->set_material(matte->clone(brown));
	pWorld->add_object(plane);

	// triangle = new Triangle(Point3D(-20, 0, 0), Point3D(20, 0, 25), Point3D(0, 50, 0));
	// triangle->set_material(matte->clone(red));
	// add_object(triangle);
}