#ifndef _SV_EMISSIVE_H
#define _SV_EMISSIVE_H

#include "Material.hpp"
#include "../Texture/ConstantColor.hpp"

class SV_Emissive: public Material {
	private:

		float		ls;		// radiance scaling factor
		Texture* 	ce;		// color

	public:

		// constructors, set functions, etc ...

		SV_Emissive(void);

		SV_Emissive(const SV_Emissive& em);

		virtual Material*
		clone(void) const;

		SV_Emissive&
		operator= (const SV_Emissive& rhs);

		~SV_Emissive(void);

		void
		scale_radiance(const float _ls);

		void
		set_ce(Texture* t_ptr);

		virtual RGBColor
		get_Le(ShadeRec& sr) const;

		virtual RGBColor
		area_light_shade(ShadeRec& sr);

		virtual RGBColor
		path_shade(ShadeRec& sr);

		virtual RGBColor
		global_shade(ShadeRec& sr);
};


inline void
SV_Emissive::scale_radiance(const float l) {
	ls = l;
}

inline void
SV_Emissive::set_ce(Texture* t_ptr) {
	ce = t_ptr;
}

#endif // SV_EMISSIVE_H
