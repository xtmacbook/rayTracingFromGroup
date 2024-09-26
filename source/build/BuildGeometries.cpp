
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
#include "../GeometricObjects/Annulus.hpp"
#include "../GeometricObjects/Torus.hpp"
#include "../GeometricObjects/OpenCylinderConcave.hpp"
#include "../GeometricObjects/OpenCylinderConvex.hpp"
#include "../GeometricObjects/OpenCylinderPartConvex.hpp"


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



GeometricObject* tran(GeometricObject* obj,const Point3D&t,float s,const Point3D& r)
{
	Instance* instance_ptr = new Instance;
	instance_ptr->set_object(obj);
	instance_ptr->set_material(obj->get_material());
	instance_ptr->scale(s);
	instance_ptr->translate(t);
	return instance_ptr;
}

void addTestGeometries(World* pWorld)
{
	float ka = 0.25;
	float kd = 0.75;
	Matte* matte_ptr = new Matte;
	matte_ptr->set_ka(ka);
	matte_ptr->set_kd(kd);
	matte_ptr->set_cd(dark_green);

	/*Annulus* pGeoemtry = new Annulus(Point3D(0.0, 1.3, 0.0), Normal(0.0, 0.0, 1.0), 1, 2);
	 pGeoemtry->set_material(matte_ptr);
	pWorld->add_object(pGeoemtry); */
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*Torus* pTorus = new Torus(1,0.3);
	pTorus->set_material(matte_ptr);
	Instance* pGeoemtry = new Instance;
	pGeoemtry->set_object(pTorus);
	pGeoemtry->rotate_z(30.0);
	pGeoemtry->rotate_x(30.0);
	pGeoemtry->set_material(matte_ptr);
	pWorld->add_object(pGeoemtry);*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*Cylinder* pCylinder = new Cylinder(0,2,0.8);
	Instance* pGeoemtry = new Instance;
	pGeoemtry->set_object(pCylinder);
	pGeoemtry->rotate_z(30.0);
	pGeoemtry->rotate_x(30.0);
	pGeoemtry->set_material(matte_ptr);
	pWorld->add_object(pGeoemtry);*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*OpenCylinderConcave* pOpenCylinderConcave = new OpenCylinderConcave();
	pOpenCylinderConcave->set_material(matte_ptr);
	Instance* pGeoemtry0 = new Instance;
	pGeoemtry0->set_object(pOpenCylinderConcave);
	pGeoemtry0->set_material(matte_ptr);
	pGeoemtry0->rotate_z(30.0);
	pGeoemtry0->rotate_x(30.0);

	OpenCylinderConvex* pOpenCylinderConvex = new OpenCylinderConvex();
	pOpenCylinderConvex->set_material(matte_ptr);
	Instance* pGeoemtry1 = new Instance;
	pGeoemtry1->set_material(matte_ptr);
	pGeoemtry1->set_object(pOpenCylinderConvex);
	pGeoemtry1->rotate_z(30.0);
	pGeoemtry1->rotate_x(30.0);
	pGeoemtry1->translate(3,0.0,3.0);

	pWorld->add_object(pGeoemtry0);
	pWorld->add_object(pGeoemtry1);*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*OpenCylinderPartConvex* pOpenCylinderPartConvex = new OpenCylinderPartConvex(0,1,3,60.0,120.0);
	pOpenCylinderPartConvex->set_material(matte_ptr);
	Instance* pGeoemtry1 = new Instance;
	pGeoemtry1->set_material(matte_ptr);
	pGeoemtry1->set_object(pOpenCylinderPartConvex);
	pGeoemtry1->rotate_z(30.0);
	pGeoemtry1->rotate_x(30.0);
	pWorld->add_object(pGeoemtry1);*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////

}

void buildGometries(World* pWorld)
{
	int num_samples = 16;

	pWorld->vp.set_hres(600);
	pWorld->vp.set_vres(400);
	pWorld->vp.set_samples(num_samples);
	pWorld->vp.set_max_depth(4);
	pWorld->background_color = black;
	pWorld->tracer_ptr = new Whitted(pWorld);

	AmbientLight* ambient_ptr = new AmbientLight;
	ambient_ptr->scale_radiance(0.25);
	pWorld->set_ambient_light(ambient_ptr);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0.0, 3.0, 40);
	pinhole_ptr->set_lookat(0.0, 0.0, 0);
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

	addTestGeometries(pWorld);

	Checker3D* check_texture = new Checker3D();
	check_texture->set_size(2.0);
	check_texture->set_color1(0.5, 0.5, 0.5);
	check_texture->set_color2(1.0, 1.0, 1.0);
	SV_Matte* check_matte(new SV_Matte);
	check_matte->set_ka(0.25);
	check_matte->set_kd(0.75);
	check_matte->set_cd(check_texture);

	Rectangle* rectangle_ptr = new Rectangle(Point3D(-20, -1, -100), Vector3D(0, 0, 120), Vector3D(40, 0, 0));
	rectangle_ptr->set_material(check_matte);
	pWorld->add_object(rectangle_ptr);
}
