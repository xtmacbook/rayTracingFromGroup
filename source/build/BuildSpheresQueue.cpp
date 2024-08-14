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

void buildSpheresQueue(World* pWorld){
    pWorld->vp.set_vres(800);
    pWorld->vp.set_hres(800);
    pWorld->vp.set_pixel_size(1);
    pWorld->background_color = RGBColor(1);
    pWorld->tracer_ptr = new MultipleObjects(this);

    ThinLens* thin = new ThinLens(Point3D(0, 100, 0), Point3D(0, 0, -100));
    thin->set_sampler(new Jittered(100));
    thin->set_view_distance(120);
    thin->set_focal_dist(130);
    thin->set_lens_radius(1);
    thin->compute_uvw();
    pWorld->camera = thin;

    //Plane* plane_pt = new Plane(Point3D(0), Normal(0, 1, 0));
    //plane_pt->set_color(RGBColor(0));
    //add_object(plane_pt);

    Sphere* sphere_pt;
    for(int i = 0; i < 3; i++){
        sphere_pt = new Sphere(Point3D(-150 + i*i*200, 0, -80-140*i), 60);

		float ka = rand_float();
		float kd = rand_float();

		RGBColor yellow(1, 1, 0);										// yellow
		// spheres
		Matte* matte_ptr = new Matte;
		matte_ptr->set_ka(ka);
		matte_ptr->set_kd(kd);
		matte_ptr->set_cd(yellow);
        sphere_pt->set_material(matte_ptr);

        pWorld->add_object(sphere_pt);
    }
}