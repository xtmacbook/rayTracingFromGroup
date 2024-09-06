#ifndef _FRESNELREFLECTOR_H
#define _FRESNELREFLECTOR_H



// this implements perfect specular reflection for indirect illumination
// with reflective materials

#include "BRDF.hpp"

class FresnelReflector : public BRDF
{
public:

	FresnelReflector(void);

	~FresnelReflector(void);

	virtual FresnelReflector* clone(void) const;

	void set_kr(const float k);

	void set_eta_in(const float ei);

	void set_eta_out(const float eo);

	void set_cr(const RGBColor& c);

	void set_cr(const float r, const float g, const float b);

	void set_cr(const float c);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wr) const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

	virtual float fresnel(const ShadeRec& sr) const;
private:

	float		kr;			// reflection coefficient
	RGBColor 	cr;			// the reflection colour
	float		eta_in;
	float		eta_out;
};


#endif // FRESNELREFLECTOR_H
