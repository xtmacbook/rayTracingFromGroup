#ifndef _SV_GLOSSYREFLECTOR_H
#define _SV_GLOSSYREFLECTOR_H


#include "SV_Phong.hpp"
#include "SV_GlossySpecular.hpp"

class Texture;

class SV_GlossyReflector: public SV_Phong {
	public:

		SV_GlossyReflector(void);

		SV_GlossyReflector(const SV_GlossyReflector& gr);

		SV_GlossyReflector&
		operator= (const SV_GlossyReflector& rhs);

		virtual SV_GlossyReflector*
		clone(void) const;

		~SV_GlossyReflector(void);

		void
		set_kr(const float k);

		void
		set_cr(Texture* t_ptr);

		void
		set_exponent(const float e);

		void
		set_samples(const int num_samples, const float exp);

		virtual RGBColor
		shade(ShadeRec& s);

        virtual RGBColor
        area_light_shade(ShadeRec& sr);

	private:

		SV_GlossySpecular* glossy_specular_brdf;
};


inline void
SV_GlossyReflector::set_kr(const float k) {
	glossy_specular_brdf->set_ks(k);
}

inline void
SV_GlossyReflector::set_cr(Texture* t_ptr) {
	glossy_specular_brdf->set_cs(t_ptr);

}

inline void
SV_GlossyReflector::set_exponent(const float e) {
	glossy_specular_brdf->set_exp(e);
}

inline void
SV_GlossyReflector::set_samples(const int num_samples, const float exp) {
	glossy_specular_brdf->set_samples(num_samples, exp);
}

#endif // SV_GLOSSYREFLECTOR_H
