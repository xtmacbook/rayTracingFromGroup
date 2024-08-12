#include "AmbientLight.hpp"

AmbientLight::AmbientLight ()
	: 	Light(),
		ls(1.0),
		color(1.0)			
{}

AmbientLight::AmbientLight (const AmbientLight& a)
	: 	Light(a),
		ls(a.ls),
		color(a.color) 		
{}

Light* AmbientLight::clone() const {
	return (new AmbientLight(*this));
}	

AmbientLight& AmbientLight::operator= (const AmbientLight& rhs) {
	if (this == &rhs)
		return (*this);
			
	Light::operator= (rhs);
	
	ls 		= rhs.ls;
	color 	= rhs.color;
	
	return (*this);
}

AmbientLight::~AmbientLight () {}

Vector3D AmbientLight::get_direction(ShadeRec& s) {
	return (Vector3D(0.0));
}

RGBColor AmbientLight::L(ShadeRec& sr) {	
    return (ls * color);
}

void AmbientLight::scale_radiance(const float b) { 
	ls = b;
}

void AmbientLight::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}

void AmbientLight::set_color(const RGBColor& c) {
	color = c;
}

void AmbientLight::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}

bool AmbientLight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	return false;
}
