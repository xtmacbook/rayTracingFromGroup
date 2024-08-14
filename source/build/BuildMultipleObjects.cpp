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

void buildMultipleObjects(World* pWorld) {
	vp.set_hres(300);
	vp.set_vres(300);
	vp.set_pixel_size(1.0);
	
	tracer_ptr = new MultipleObjects(this); 
	
	background_color = RGBColor(0);
	
	// use access functions to set centre and radius
	
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_center(0, -25, 0);
	sphere_ptr->set_radius(80);
	sphere_ptr->set_color(1, 0, 0);  // red
	add_object(sphere_ptr);

	// use constructor to set centre and radius 
	
	sphere_ptr = new Sphere(Point3D(0, 30, 0), 400);
	sphere_ptr->set_color(1, 1, 0);	// yellow
	add_object(sphere_ptr);
	
	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 1));
	plane_ptr->set_color(0.0, 0.3, 0.0);	// dark green
	add_object(plane_ptr);
}