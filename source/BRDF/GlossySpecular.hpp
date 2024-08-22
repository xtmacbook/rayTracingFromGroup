#pragma once

#ifndef  _GLOSSYSPECULAR_H_
#define _GLOSSYSPECULAR_H_

#include "BRDF.hpp"

/**
 * Specular reflection
 */
class GlossySpecular : public BRDF{
public:
    GlossySpecular(float kd_ = 0.0, float exp_ = 0.0, RGBColor cd_ = RGBColor(0));
    GlossySpecular(const GlossySpecular& lamb);
    virtual GlossySpecular* clone() const;
    GlossySpecular& operator=(const GlossySpecular& rhs);
    float get_exp() const;
    void set_exp(const float exp_);

    float get_ks() const;
    void set_ks(const float ks);

    RGBColor get_cs() const;
    void set_cs(const RGBColor cs);
	void set_cs(const float r, const float g, const float b);

    virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
    virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

    /*
    add for glossy reflection
    */
    void set_sampler(const int num_samples, const float exp);
	RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const override; // add for glossy reflection



protected:
    float exp;
    float ks;
    RGBColor cs;
};
#endif