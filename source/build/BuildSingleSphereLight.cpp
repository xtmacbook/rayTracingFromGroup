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

void buildSingleSphereLight(World* pWorld) {
     pWorld->vp.hres = 400;
     pWorld->vp.vres = 400;
     pWorld->vp.set_pixel_size(1);
     pWorld->vp.set_gamma(1);
     pWorld->vp.set_samples(1);
     pWorld->background_color = black;
     pWorld->tracer_ptr = new RayCast(pWorld);

    Pinhole* pin = new Pinhole(Point3D(0, 0, 100), Point3D(0, 0, -100));
    pin->set_view_distance(100);
    pWorld->set_camera(pin);

    auto pAmLight = new AmbientLight;
    pAmLight->scale_radiance(1.0);

    pWorld->ambient_ptr = pAmLight;
    Sphere* sphere = new Sphere(Point3D(0, 0, 0), 50);
    Matte* matte = new Matte;
    sphere->set_material(matte);
    pWorld->add_object(sphere);
}