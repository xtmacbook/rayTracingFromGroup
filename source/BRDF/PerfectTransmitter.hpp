#pragma once

#ifndef  _PERFECTTRANSMITTER_H_
#define _PERFECTTRANSMITTER_H_

#include "BTDF.hpp"


class PerfectTransmitter : public BTDF {
public:

	PerfectTransmitter(void);

	PerfectTransmitter(const PerfectTransmitter& pt);

	virtual PerfectTransmitter* clone(void);

	~PerfectTransmitter(void);

	PerfectTransmitter& operator= (const PerfectTransmitter& rhs);

	void set_kt(const float k);

	void set_ior(const float eta);

	/*
	tests for total internal reflection
	*/
	bool tir(const ShadeRec& sr) const;

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	/*
		this computes the direction wt for perfect transmission
		and returns the transmission coefficient
		this is only called when there is no total internal reflection
	*/

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

private:
	/*
		index of refraction = c/v  (c : light speed that in perfect vacuum,and the v is light speed in the medium)
	*/
	float	kt;			// transmission coefficient
	float	ior;		// relative index of refraction
};

#endif
