#pragma once

#ifndef  _BRDF_H_
#define _BRDF_H_

#include "../Samplers/Sampler.hpp"
#include "../Utilities/Vector3D.hpp"
#include "../Utilities/ShadeRec.hpp"



class BRDF{
public:
    BRDF();
    BRDF(const BRDF& brdf);
    BRDF(Sampler* sampler);
    BRDF& operator=(const BRDF& rhs);
    virtual BRDF* clone() const = 0;

    virtual ~BRDF();

    void set_sampler(Sampler* sampler);
    Sampler* get_sampler() const;

    /**
     * return the BRDF value,unless it contains a delta function
     * 
     */
    virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

    /** 
        This function is used to compute the direction of reflected rays for simulating reflective materials
        and diffuse-diffuse light transport.
        The reflected rays directions are computed by sampling the BRDF. That why contains a pointer to a
        sample object.

        The return value is reflected radiance "rho" value (table 13.1)
    */
    virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;
    virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
    virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

protected:
    Sampler* sampler_ptr;
};

#endif