
#include "../World/World.hpp"

#include "../Light/EnvironmentLight.hpp"
#include "../Light/Directional.hpp"
#include "../Light/AmbientOccluderLight.hpp"
#include "../Light/AreaLight.hpp"

#include "../Tracers/AreaLightingTracer.hpp"
#include "../Tracers/RayCast.hpp"
#include "../Tracers/PathTracer.hpp"

#include "../Cameras/Pinhole.hpp"

#include "../Materials/Matte.hpp"
#include "../Materials/Reflective.hpp"
#include "../Materials/Emissive.hpp"

#include "../GeometricObjects/Sphere.hpp"
#include "../GeometricObjects/Cylinder.hpp"
#include "../GeometricObjects/ConcaveSphere.hpp"
#include "../GeometricObjects/Rectangle.hpp"

#include "../GeometricObjects/Plane.hpp"
#include "../GeometricObjects/Box.hpp"

void buildCornellBox(World* pWorld) {
	
	int num_samples = 10000;		// for Figure 26.7(a)

	pWorld->vp.set_hres(300);
	pWorld->vp.set_vres(300);
	pWorld->vp.set_samples(num_samples);
	pWorld->vp.set_max_depth(10);

	pWorld->background_color = black;

	pWorld->tracer_ptr = new PathTrace(pWorld);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(27.6, 27.4, -80.0);
	pinhole_ptr->set_lookat(27.6, 27.4, 0.0);
	pinhole_ptr->set_view_distance(400);
	pinhole_ptr->compute_uvw();
	pWorld->set_camera(pinhole_ptr);


	Point3D p0;
	Vector3D a, b;
	Normal normal;

	// box dimensions
	double width = 55.28;   	// x direction
	double height = 54.88;  	// y direction
	double depth = 55.92;	// z direction


	// the ceiling light - doesn't need samples

	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->set_ce(1.0, 0.73, 0.4);
	emissive_ptr->scale_radiance(100);

	p0 = Point3D(21.3, height - 0.001, 22.7);
	a = Vector3D(0.0, 0.0, 10.5);
	b = Vector3D(13.0, 0.0, 0.0);
	normal = Normal(0.0, -1.0, 0.0);
	Rectangle* light_ptr = new Rectangle(p0, a, b, normal);
	light_ptr->set_material(emissive_ptr);
	pWorld->add_object(light_ptr);


	// left wall

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.0);
	matte_ptr1->set_kd(0.6);
	matte_ptr1->set_cd(0.57, 0.025, 0.025);	 // red
	matte_ptr1->set_sampler(new MultiJittered(num_samples,83));

	p0 = Point3D(width, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(-1.0, 0.0, 0.0);
	Rectangle* left_wall_ptr = new Rectangle(p0, a, b, normal);
	left_wall_ptr->set_material(matte_ptr1);
	pWorld->add_object(left_wall_ptr);


	// right wall

	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.0);
	matte_ptr2->set_kd(0.6);
	matte_ptr2->set_cd(0.37, 0.59, 0.2);	 // green   from Photoshop
	matte_ptr2->set_sampler(new MultiJittered(num_samples,83));

	p0 = Point3D(0.0, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(1.0, 0.0, 0.0);
	Rectangle* right_wall_ptr = new Rectangle(p0, a, b, normal);
	right_wall_ptr->set_material(matte_ptr2);
	pWorld->add_object(right_wall_ptr);


	// back wall

	Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(0.0);
	matte_ptr3->set_kd(0.6);
	matte_ptr3->set_cd(1.0);	 // white
	matte_ptr3->set_sampler(new MultiJittered(num_samples,83));

	p0 = Point3D(0.0, 0.0, depth);
	a = Vector3D(width, 0.0, 0.0);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(0.0, 0.0, -1.0);
	Rectangle* back_wall_ptr = new Rectangle(p0, a, b, normal);
	back_wall_ptr->set_material(matte_ptr3);
	pWorld->add_object(back_wall_ptr);


	// floor
	p0 = Point3D(0.0, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(width, 0.0, 0.0);
	normal = Normal(0.0, 1.0, 0.0);
	Rectangle* floor_ptr = new Rectangle(p0, a, b, normal);
	floor_ptr->set_material(matte_ptr3);
	pWorld->add_object(floor_ptr);


	// ceiling
	p0 = Point3D(0.0, height, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(width, 0.0, 0.0);
	normal = Normal(0.0, -1.0, 0.0);
	Rectangle* ceiling_ptr = new Rectangle(p0, a, b, normal);
	ceiling_ptr->set_material(matte_ptr3);
	pWorld->add_object(ceiling_ptr);


	// the two boxes defined as 5 rectangles each

	// top
	p0 = Point3D(13.0, 16.5, 6.5);
	a = Vector3D(-4.8, 0.0, 16.0);
	b = Vector3D(16.0, 0.0, 4.9);
	normal = Normal(0.0, 1.0, 0.0);
	Rectangle* short_top_ptr = new Rectangle(p0, a, b, normal);
	short_top_ptr->set_material(matte_ptr3);
	pWorld->add_object(short_top_ptr);


	// side 1
	p0 = Point3D(13.0, 0.0, 6.5);
	a = Vector3D(-4.8, 0.0, 16.0);
	b = Vector3D(0.0, 16.5, 0.0);
	Rectangle* short_side_ptr1 = new Rectangle(p0, a, b);
	short_side_ptr1->set_material(matte_ptr3);
	pWorld->add_object(short_side_ptr1);


	// side 2
	p0 = Point3D(8.2, 0.0, 22.5);
	a = Vector3D(15.8, 0.0, 4.7);
	Rectangle* short_side_ptr2 = new Rectangle(p0, a, b);
	short_side_ptr2->set_material(matte_ptr3);
	pWorld->add_object(short_side_ptr2);


	// side 3
	p0 = Point3D(24.2, 0.0, 27.4);
	a = Vector3D(4.8, 0.0, -16.0);
	Rectangle* short_side_ptr3 = new Rectangle(p0, a, b);
	short_side_ptr3->set_material(matte_ptr3);
	pWorld->add_object(short_side_ptr3);


	// side 4
	p0 = Point3D(29.0, 0.0, 11.4);
	a = Vector3D(-16.0, 0.0, -4.9);
	Rectangle* short_side_ptr4 = new Rectangle(p0, a, b);
	short_side_ptr4->set_material(matte_ptr3);
	pWorld->add_object(short_side_ptr4);




	// tall box
	// top
	p0 = Point3D(42.3, 33.0, 24.7);
	a = Vector3D(-15.8, 0.0, 4.9);
	b = Vector3D(4.9, 0.0, 15.9);
	normal = Normal(0.0, 1.0, 0.0);
	Rectangle* tall_top_ptr = new Rectangle(p0, a, b, normal);
	tall_top_ptr->set_material(matte_ptr3);
	pWorld->add_object(tall_top_ptr);


	// side 1
	p0 = Point3D(42.3, 0.0, 24.7);
	a = Vector3D(-15.8, 0.0, 4.9);
	b = Vector3D(0.0, 33.0, 0.0);
	Rectangle* tall_side_ptr1 = new Rectangle(p0, a, b);
	tall_side_ptr1->set_material(matte_ptr3);
	pWorld->add_object(tall_side_ptr1);


	// side 2
	p0 = Point3D(26.5, 0.0, 29.6);
	a = Vector3D(4.9, 0.0, 15.9);
	Rectangle* tall_side_ptr2 = new Rectangle(p0, a, b);
	tall_side_ptr2->set_material(matte_ptr3);
	pWorld->add_object(tall_side_ptr2);


	// side 3
	p0 = Point3D(31.4, 0.0, 45.5);
	a = Vector3D(15.8, 0.0, -4.9);
	Rectangle* tall_side_ptr3 = new Rectangle(p0, a, b);
	tall_side_ptr3->set_material(matte_ptr3);
	pWorld->add_object(tall_side_ptr3);


	// side 4

	p0 = Point3D(47.2, 0.0, 40.6);
	a = Vector3D(-4.9, 0.0, -15.9);
	Rectangle* tall_side_ptr4 = new Rectangle(p0, a, b);
	tall_side_ptr4->set_material(matte_ptr3);
	pWorld->add_object(tall_side_ptr4);
}