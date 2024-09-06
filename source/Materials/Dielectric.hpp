#ifndef _DIELECTRIC_H
#define _DIELECTRIC_H


#include "Phong.hpp"
#include "../BRDF/FresnelTransmitter.hpp"
#include "../BRDF/FresnelSpecular.hpp"

class Dielectric : public Phong
{
public:

	Dielectric(void);

	Dielectric(const Dielectric& dm);

	Dielectric& operator= (const Dielectric& rhs);

	virtual Dielectric* clone(void) const;

	~Dielectric(void);

	void set_eta_in(const float ei);

	void set_eta_out(const float eo);

	void set_cf_in(const RGBColor& ci);

	void set_cf_in(const float ri, const float gi, const float bi);

	void set_cf_in(const float ci);

	void set_cf_out(const RGBColor& co);

	void set_cf_out(const float ro, const float go, const float bo);

	void set_cf_out(const float co);

	virtual RGBColor shade(ShadeRec& s);

private:

	RGBColor 			cf_in;			// interior filter color
	RGBColor 			cf_out;			// exterior filter color

	FresnelReflector* fresnel_brdf;
	FresnelTransmitter* fresnel_btdf;
};


#endif // DIELECTRIC_H
