
#include "Disk.hpp"
#include "OpenCylinderConvex.hpp"
#include "OpenCylinderConcave.hpp"
#include "Annulus.hpp"
#include "Instance.hpp"
#include "TorusPartConcave.hpp"
#include "GlassOfWater.hpp"


// ------------------------------------------------------------------------------ default constructor

GlassOfWater::GlassOfWater(void)
	: Compound(),
	height(2.0),
	inner_radius(0.9),
	wall_thickness(0.1),
	base_thickness(0.3),
	water_height(1.5),
	meniscus_radius(0.1)
{
	build_components();
}


GlassOfWater::GlassOfWater(const double _height,
	const float _inner_radius,
	const float _wall_thickness,
	const float _base_thickness,
	const float _water_height,
	const float _meniscus_radius)
	: Compound(),
	height(_height),
	inner_radius(_inner_radius),
	wall_thickness(_wall_thickness),
	base_thickness(_base_thickness),
	water_height(_water_height),
	meniscus_radius(_meniscus_radius)
{
	build_components();
}


GlassOfWater::GlassOfWater(const GlassOfWater& gw)
	: Compound(gw),
	height(gw.height),
	inner_radius(gw.inner_radius),
	wall_thickness(gw.wall_thickness),
	base_thickness(gw.base_thickness),
	water_height(gw.water_height),
	meniscus_radius(gw.meniscus_radius)
{}


GlassOfWater*
GlassOfWater::clone(void) const {
	return(new GlassOfWater(*this));
}


GlassOfWater&
GlassOfWater::operator= (const GlassOfWater& rhs) {
	if (this == &rhs)
		return (*this);

	Compound::operator=(rhs);

	height = rhs.height;
	inner_radius = rhs.inner_radius;
	wall_thickness = rhs.wall_thickness;
	base_thickness = rhs.base_thickness;
	water_height = rhs.water_height;
	meniscus_radius = rhs.meniscus_radius;

	return (*this);
}


GlassOfWater::~GlassOfWater(void) {}

void
GlassOfWater::build_components(void) {
	// build the glass parts

	objects.push_back(new Annulus(Point3D(0, height, 0), 						// rim at top
		Normal(0, 1, 0),
		inner_radius,
		inner_radius + wall_thickness));

	// bottom of glass
	objects.push_back(new Disk(Point3D(0), Normal(0, -1, 0), inner_radius + wall_thickness));

	objects.push_back(new OpenCylinderConcave(water_height + meniscus_radius, // inner curved surface of glass
		height,
		inner_radius));

	objects.push_back(new OpenCylinderConvex(0, 								// outer curved surface of glass
		height,
		inner_radius + wall_thickness));


	// build the water parts

	objects.push_back(new Disk(Point3D(0, water_height, 0), Normal(0, 1, 0),					// top of water
		inner_radius - meniscus_radius
	));


	objects.push_back(new Disk(Point3D(0, base_thickness, 0), Normal(0, -1, 0), 					// bottom of water
		inner_radius
	));


	objects.push_back(new OpenCylinderConvex(base_thickness,					// curved surface of water
		water_height + meniscus_radius,
		inner_radius));


	// build the meniscus: we need an instance for this

	Instance* meniscus_ptr = new Instance(new TorusPartConcave(inner_radius - meniscus_radius,
		meniscus_radius,
		0, 360,			// azimuth angle - phi - range
		270, 360));		// polar angle - theta - range
	meniscus_ptr->translate(0, water_height + meniscus_radius, 0);
	objects.push_back(meniscus_ptr);
}


// ------------------------------------------------------------------------------ set_glass_air_material

void
GlassOfWater::set_glass_air_material(Material* m_ptr) {
	for (int j = 0; j < 4; j++)
		objects[j]->set_material(m_ptr);
}

// ------------------------------------------------------------------------------ set_water_air_material

void
GlassOfWater::set_water_air_material(Material* m_ptr) {
	objects[4]->set_material(m_ptr);	// top of water
	objects[7]->set_material(m_ptr);   	// meniscus
}


// ------------------------------------------------------------------------------ set_water_glass_material

void
GlassOfWater::set_water_glass_material(Material* m_ptr) {
	for (int j = 5; j < 7; j++)
		objects[j]->set_material(m_ptr);
}





