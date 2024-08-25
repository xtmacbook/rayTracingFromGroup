#include "SV_Emissive.hpp"

SV_Emissive::SV_Emissive (void)
	:	Material()
{}


SV_Emissive::SV_Emissive(const SV_Emissive& em)
	: 	Material(em)
{}


Material*
SV_Emissive::clone(void) const {
	return (new SV_Emissive(*this));
}

SV_Emissive&
SV_Emissive::operator= (const SV_Emissive& rhs) {
	if (this == &rhs)
		return (*this);

	Material::operator=(rhs);

	return (*this);
}

SV_Emissive::~SV_Emissive(void) {
}

RGBColor
SV_Emissive::get_Le(ShadeRec& sr) const {
    return (ls * (ce->get_color(sr)));
}


RGBColor
SV_Emissive::area_light_shade(ShadeRec& sr) {
	if (-sr.normal * sr.ray.d > 0.0)
		return (ls * (ce->get_color(sr)));
	else
		return (black);
}


RGBColor
SV_Emissive::path_shade(ShadeRec& sr) {
	if (-sr.normal * sr.ray.d > 0.0)
		return (ls * (ce->get_color(sr)));
	else
		return (black);
}

RGBColor
SV_Emissive::global_shade(ShadeRec& sr) {
    if (sr.depth == 1) {
        return (black);
    }
	if (-sr.normal * sr.ray.d > 0.0)
		return (ls * (ce->get_color(sr)));
	else
		return (black);
}

