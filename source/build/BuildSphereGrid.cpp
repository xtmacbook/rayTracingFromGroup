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
#include "../Cameras/FishEye.hpp"

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

void buildSphereGrid(World* pWorld){
    // view plane
	pWorld->vp.set_hres(800);
	pWorld->vp.set_vres(800);
	pWorld->vp.set_pixel_size(1);
	pWorld->vp.set_sampler(new NRooks(4));

	pWorld->background_color = black;

	AmbientLight* ambient_ptr = new AmbientLight;
	ambient_ptr->scale_radiance(1);
	pWorld->set_ambient_light(ambient_ptr);

	pWorld->tracer_ptr = new RayCast(pWorld);

 	RGBColor yellow(1, 1, 0);
	RGBColor brown(0.71, 0.40, 0.16);
	RGBColor dark_green(0.0, 0.41, 0.41);
	RGBColor orange(1, 0.75, 0);
	RGBColor green(0, 0.6, 0.3);
	RGBColor light_green(0.65, 1, 0.30);
	RGBColor dark_yellow(0.61, 0.61, 0);
    RGBColor blue(0, 0, 1);
	RGBColor light_purple(0.65, 0.3, 1);
	RGBColor dark_purple(0.5, 0, 1);

	ThinLens* pinhole_ptr = new ThinLens(Point3D(0, 0, 4), Point3D(0, 0, -1));
	pinhole_ptr->set_view_distance(1000);
	pinhole_ptr->set_sampler(new Jittered(100, 100));
	pinhole_ptr->set_lens_radius(0);
	pinhole_ptr->set_focal_dist(60);
	pinhole_ptr->compute_uvw();
	pWorld->set_camera(pinhole_ptr);

	PointLight* point_light = new PointLight(Vector3D(10, 20, 3), 6);
	pWorld->add_light(point_light);

    int num_spheres = 1000;
    float volume = 0.1 / num_spheres;
    float radius = pow(0.75*volume/3.1415, 0.33);
    Grid* grid_ptr = new Grid;
    for(int i = 0; i < num_spheres; i++){
        Phong* matte_ptr = new Phong;
        matte_ptr->set_ka(0.25);
        matte_ptr->set_kd(0.75);
		matte_ptr->set_ks(0.5);
        matte_ptr->set_cd(RGBColor(rand_float(), rand_float(), rand_float()));

        Sphere* sphere_ptr = new Sphere;
        sphere_ptr->set_radius(radius);
        sphere_ptr->set_center(Point3D(1.0 - 2.0*rand_float(), 1.0 - 2.0*rand_float(), 1.0 - 2.0*rand_float()));
        sphere_ptr->set_material(matte_ptr);

        grid_ptr->add_object(sphere_ptr);
    }
    grid_ptr->setup_cells();
	pWorld->add_object(grid_ptr);
}