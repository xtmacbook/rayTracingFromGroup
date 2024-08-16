#pragma once

#include "Phong.hpp"
#include "../BRDF/GlossySpecular.hpp"

class GlossyReflectorMaterial : public Phong {
public:
    
    GlossyReflectorMaterial();

    void set_samples(const int num_samples,float exp);

    void set_kr(const float kr);

	void set_cr(const RGBColor& c);

    void set_cr(const float r, const float g, const float b);

    void set_exponent(float exp);

    virtual RGBColor 	shade(ShadeRec& s);
    
    virtual RGBColor area_light_shade(ShadeRec&sr);
private:
    GlossySpecular*  glossy_reflector_ptr = nullptr;
};