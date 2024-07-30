#include "../Cameras/FishEye.hpp"
void World::build(void) 
{
    vp.set_hres(600);
	vp.set_vres(400);
	vp.set_pixel_size(1);
	vp.set_gamma(1.0);
	vp.set_samples(1);
	
	Point3D eye(7.5, 4, 10);
	Point3D lookAt(-1, 3.7, 0);
	FishEyeCamera* pFishCamera = new FishEyeCamera(eye,lookAt);
    pFishCamera->set_psi_max(90.0);
	pFishCamera->set_view_distance(340);
	pFishCamera->compute_uvw();
	pFishCamera->set_psi_max(60.0);
	set_camera(pFishCamera);

	background_color = black;
	tracer_ptr = new RayCast(this);
	
	PointLight* light_ptr2 = new PointLight;	// for Figure 15.8(b)
	light_ptr2->set_location(Vector3D(15, 15, 2.5));
	light_ptr2->scale_radiance(2.0);
	add_light(light_ptr2);

	Directional* light_ptr1 = new Directional;	// for Figure 15.8(a)
	light_ptr1->set_direction(15, 15, 2.5);
	light_ptr1->scale_radiance(2.0);
	add_light(light_ptr1);

	RGBColor green(0, 0.6, 0.3);									// green
	float ka = 0.25;
	float kd = 0.75;
	Matte* matte_ptr32 = new Matte;
	matte_ptr32->set_ka(ka);
	matte_ptr32->set_kd(kd);
	matte_ptr32->set_cd(green);
	Sphere* sphere_ptr32 = new Sphere(Point3D(3.85, 2.3, -2.55), 2.3);
	sphere_ptr32->set_material(matte_ptr32);							//  green
	add_object(sphere_ptr32);


	Phong* phong_ptr2 = new Phong;
	phong_ptr2->set_ka(0.45);
	phong_ptr2->set_kd(0.75);
	phong_ptr2->set_cd(RGBColor(0.75, 0.25, 0));   	// orange
	phong_ptr2->set_ks(0.25);
	phong_ptr2->set_exp(500);
	Sphere* sphere_ptr2 = new Sphere(Point3D(-0.7, 1, 4.2), 2);
	sphere_ptr2->set_material(phong_ptr2);
	add_object(sphere_ptr2);
}
