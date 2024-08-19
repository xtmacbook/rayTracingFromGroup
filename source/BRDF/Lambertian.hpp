#pragma once

#ifndef  _LAMBERTIAN_H_
#define _LAMBERTIAN_H_

#include "BRDF.hpp"

//lambertian reflectance is () : the incident radiance is scatted equally in all  directions
class Lambertian : public BRDF{
public:
    Lambertian(float kd_ = 0.0, RGBColor cd_ = RGBColor(0.0));
    Lambertian(const Lambertian& lamb);
    virtual Lambertian* clone() const;
    Lambertian& operator=(const Lambertian& rhs);

    float get_kd() const;
    void set_kd(const float kd);

    RGBColor get_cd() const;
    void set_cd(const RGBColor cd);

    virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
    virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

protected:
    float kd; //diffuse reflection cofficient
    RGBColor cd; //diffuse color
};
#endif