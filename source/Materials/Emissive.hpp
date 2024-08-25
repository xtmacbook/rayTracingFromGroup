#pragma once

#include "Material.hpp"

/**
 * first because the area light ,so add this class
 * 
 * Le depend on location and direction,but to keep the simple .we consider spatially invariant,isotropic emissive materials.
   Also assume that emissive materials don't reflect or transmit light so that when a primary or secondary ray hits 
   a self-emissive object,no further rays are generated.

 */

class Emissive : public Material {
private:
    float ls;
    RGBColor ce;

public:
    Emissive(const float ls_ = 1, const RGBColor ce_ = RGBColor(1));
    Emissive(const Emissive& emissive);
    Emissive& operator=(const Emissive& rhs);
    Emissive* clone() const;

    void scale_radiance(const float ls_);
    void set_ce(const float r, const float g, const float b);
    void set_ce(const float a);
    void set_ce(const RGBColor ce_);

    virtual RGBColor get_Le(ShadeRec& sr) const;

    /**
     * allows us to use the missive material with other tracers 
       such as RayCast and thereby to render emissive objects in scenes without shading with them
     */
    virtual RGBColor shade(ShadeRec& sr);
    virtual RGBColor area_light_shade(ShadeRec& sr);
    virtual RGBColor path_shade(ShadeRec& sr);
};