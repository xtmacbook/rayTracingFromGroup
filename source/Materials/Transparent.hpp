#pragma once

#ifndef  _TRANSPARENT_H_
#define _TRANSPARENT_H_

#include "Phong.hpp"

class PerfectSpecular;
class PerfectTransmitter;

class Transparent : public Phong {
public:

public:

	Transparent(void);

	Transparent(const Transparent& tm);

	Transparent& operator= (const Transparent& rhs);

	virtual Transparent* clone(void) const;

	~Transparent(void);

	void set_kr(const float k);

	void set_cr(const RGBColor& c);

	void set_cr(const float r, const float g, const float b);

	void set_cr(const float c);

	void set_kt(const float k);

	void set_ior(const float i); //set 

	virtual RGBColor shade(ShadeRec& s);

private:

	PerfectSpecular* reflective_brdf;
	PerfectTransmitter* specular_btdf;
};

#endif