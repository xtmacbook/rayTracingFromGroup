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

void buildHorizontalPlane(World *pWorld){
	pWorld->vp.set_hres(800);
	pWorld->vp.set_vres(800);
	pWorld->vp.set_pixel_size(1.0);

	Pinhole* pinhole_ptr = new Pinhole(Point3D(0, 50, 100), Point3D(0, 0, -500));
	pinhole_ptr->set_view_distance(400);
	pinhole_ptr->set_up(Vector3D(1, 1, 0));
	pinhole_ptr->compute_uvw();
	pWorld->camera = pinhole_ptr;

	pWorld->tracer_ptr = new MultipleObjects(this);
	
	pWorld->background_color = RGBColor(1);

	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
	plane_ptr->set_color(1, 0.0, 0.0);
	pWorld->add_object(plane_ptr);

	Sphere* sphere_ptr = new Sphere(Point3D(0, 0, 0), 20);
	sphere_ptr->set_color(1, 1, 0);	// yellow
	pWorld->add_object(sphere_ptr);
}