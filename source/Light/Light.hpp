#pragma once

#include "../Utilities/Vector3D.hpp"
#include "../Utilities/RGBColor.hpp"
#include "../Utilities/Ray.hpp"

class ShadeRec;

class Light{
public:
    Light(const bool shadows_ = false);
    Light(const Light& light);
    Light& operator=(const Light& rhs);
    virtual Light* clone() const = 0;
    virtual ~Light();

    bool get_shadows() const;
    void set_shadows(const bool shadows_);

    virtual Vector3D get_direction(ShadeRec& sr) = 0; //return the direction of the incoming light at a hit point
    virtual RGBColor L(ShadeRec& sr) = 0; // return the incident radiance at a hit point

    virtual float G(const ShadeRec& sr) const;
    virtual float pdf(const ShadeRec& sr) const;

    virtual bool in_shadow(const Ray& shadowRay, const ShadeRec& sr) const;

protected:
    bool shadows;
};