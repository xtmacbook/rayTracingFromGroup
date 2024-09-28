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
#include "../GeometricObjects/TorusPartConvex.hpp"
#include "../GeometricObjects/FishBowl.hpp"

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

void fishFlow(World* pWorld)
{
    int num_samples = 16;

    pWorld->vp.set_hres(600);
    pWorld->vp.set_vres(600);
    pWorld->vp.set_samples(num_samples);
    pWorld->vp.set_max_depth(15);
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

    
    FishBowl * pBowl = new FishBowl(1.0,0.1,3,4,20.0);
    

    // ground plane
    Checker3D* check_texture = new Checker3D();
    check_texture->set_size(4.0);
    check_texture->set_color1(0.5, 0.5, 0.5);
    check_texture->set_color2(1.0, 1.0, 1.0);
    SV_Matte* check_matte(new SV_Matte);
    check_matte->set_ka(0.25);
    check_matte->set_kd(0.75);
    check_matte->set_cd(check_texture);

    Rectangle* rectangle_ptr = new Rectangle(Point3D(-20, 0, -100), Vector3D(0, 0, 120), Vector3D(40, 0, 0));
    rectangle_ptr->set_material(check_matte);
    pWorld->add_object(rectangle_ptr);
    
    
}


void buildFishBlows(World* pWorld) {

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

    fishFlow(pWorld);
}
