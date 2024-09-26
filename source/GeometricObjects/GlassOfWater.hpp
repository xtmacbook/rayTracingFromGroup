#ifndef __GLASS_OF_WATER__
#define __GLASS_OF_WATER__


#include "Compound.hpp"

class GlassOfWater : public Compound 

{
public:

	GlassOfWater(void);

	GlassOfWater(const double _height,
		const float _inner_radius,
		const float _wall_thickness,
		const float _base_thickness,
		const float _water_height,
		const float _meniscus_radius);

	GlassOfWater(const GlassOfWater& gw);

	virtual GlassOfWater* clone(void) const;

	virtual GlassOfWater& operator= (const GlassOfWater& rhs);

	virtual ~GlassOfWater(void);

	void build_components(void);

	void set_glass_air_material(Material* m_ptr);

	void set_water_air_material(Material* m_ptr);

	void set_water_glass_material(Material* m_ptr);

protected:

	float		height;  			// total height
	float 		inner_radius;		// inner radius of glass, outer radius of water
	float 		wall_thickness;		// thickness of the glass wall
	float		base_thickness;		// thickness of the glass base
	float 		water_height;		// height of water from bottom of glass base on (x, z) plane
	float 		meniscus_radius;
};

#endif
