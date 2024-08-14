#pragma once

#include "Phong.hpp"
#include "../BRDF/GlossySpecular.hpp"

class GlossyReflectorMaterial : public Phong {
public:
    
    void set_samples(const int num_samples,float exp);

    void set_kr(const float kr);

    void set_exponent(float exp);

    virtual RGBColor area_light_shade(ShadeRec&sr);
private:
    GlossySpecular*  glossy_reflector_ptr = nullptr;
};