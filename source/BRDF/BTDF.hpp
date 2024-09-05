#pragma once

#ifndef  _BTDF_H_
#define _BTDF_H_

#include "../Samplers/Sampler.hpp"
#include "../Utilities/Vector3D.hpp"
#include "../Utilities/ShadeRec.hpp"

class BTDF {
public:

	BTDF(void);

	BTDF(const BTDF& btdf);

	virtual BTDF* clone(void) = 0;

	BTDF& operator= (const BTDF& rhs);

	virtual ~BTDF(void);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;
};

#endif