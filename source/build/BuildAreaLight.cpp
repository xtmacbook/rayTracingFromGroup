

#include "../World/World.hpp"

#include "../Light/EnvironmentLight.hpp"
#include "../Light/Directional.hpp"
#include "../Light/AreaLight.hpp"

#include "../Tracers/AreaLightingTracer.hpp"
#include "../Cameras/Pinhole.hpp"

#include "../Materials/Matte.hpp"
#include "../Materials/Reflective.hpp"
#include "../Materials/Emissive.hpp"

#include "../GeometricObjects/Sphere.hpp"
#include "../GeometricObjects/Cylinder.hpp"
#include "../GeometricObjects/ConcaveSphere.hpp"

#include "../GeometricObjects/Plane.hpp"
#include "../GeometricObjects/Box.hpp"
#include "../GeometricObjects/Rectangle.hpp"


void buildAreadLight(World* pWorld) {
			
	int num_samples = 100;   	

	pWorld->vp.set_hres(600);	  		
	pWorld->vp.set_vres(600);
	pWorld->vp.set_samples(num_samples);
	
	pWorld->background_color = black;
	
	pWorld->tracer_ptr = new AreaLightingTracer(pWorld);
		
	MultiJittered* sampler_ptr = new MultiJittered(num_samples);
	
	float width = 4.0;				// for Figure 18.4(a) & (b)
	float height = 4.0;
	Point3D center(0.0, 7.0, -7.0);	// center of each area light (rectangular, disk, and spherical)
	Point3D p0(-0.5 * width, center.y - 0.5 * height, center.z);
	Vector3D a(width, 0.0, 0.0);
	Vector3D b(0.0, height, 0.0);
	Normal normal(0, 0, 1);
	
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->scale_radiance(40.0);
	emissive_ptr->set_ce(white);
	

	Rectangle* rectangle_ptr = new Rectangle(p0, a, b, normal);
	rectangle_ptr->set_casts_shadows(false);
	rectangle_ptr->set_material(emissive_ptr);
	rectangle_ptr->set_sampler(sampler_ptr);
	pWorld->add_object(rectangle_ptr);

	
	AreaLight* area_light_ptr = new AreaLight;
	area_light_ptr->set_object(rectangle_ptr);
	area_light_ptr->set_shadows(true);
	pWorld->add_light(area_light_ptr);
	

	Pinhole* camera = new Pinhole;
	camera->set_eye(-20, 10, 20);
	camera->set_lookat(0, 2, 0); 	
	camera->set_view_distance(1080);          
	camera->compute_uvw();     
	pWorld->set_camera(camera);

	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.25); 
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(0.4, 0.7, 0.4);     // green
	

	float box_width 	= 1.0; 		// x dimension
	float box_depth 	= 1.0; 		// z dimension
	float box_height 	= 4.5; 		// y dimension
	float gap			= 3.0; 

	Box* box_ptr0 = new Box(Point3D(- 1.5 * gap - 2.0 * box_width, 0.0, -0.5 * box_depth), 
							Point3D(-1.5 * gap  - box_width, box_height, 0.5 * box_depth)); 
	box_ptr0->set_material(matte_ptr1);
	pWorld->add_object(box_ptr0);
	
	Box* box_ptr1 = new Box(Point3D(- 0.5 * gap - box_width, 0.0, -0.5 * box_depth), 
							Point3D(-0.5 * gap, box_height, 0.5 * box_depth)); 
	box_ptr1->set_material(matte_ptr1->clone());
	pWorld->add_object(box_ptr1);
		
	Box* box_ptr2 = new Box(Point3D(0.5 * gap, 0.0, -0.5 * box_depth), 
							Point3D(0.5 * gap + box_width, box_height, 0.5 * box_depth));
	box_ptr2->set_material(matte_ptr1->clone());
	pWorld->add_object(box_ptr2);
	
	Box* box_ptr3 = new Box(Point3D(1.5 * gap + box_width, 0.0, -0.5 * box_depth), 
							Point3D(1.5 * gap + 2.0 * box_width, box_height, 0.5 * box_depth));
	box_ptr3->set_material(matte_ptr1->clone());
	pWorld->add_object(box_ptr3);

	/*box_ptr0->set_casts_shadows(false);
	box_ptr1->set_casts_shadows(false);*/

	// ground plane
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.1); 
	matte_ptr2->set_kd(0.90);
	matte_ptr2->set_cd(white);

	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0)); 
	plane_ptr->set_material(matte_ptr2);
	pWorld->add_object(plane_ptr);

}
