#ifndef _SV_REFLECTIVE_H
#define _SV_REFLECTIVE_H

#include "SV_Phong.hpp"
#include "SV_PerfectSpecular.hpp"

class SV_Reflective: public SV_Phong {
	public:

		SV_Reflective(void);

		SV_Reflective(const SV_Reflective& rm);

		SV_Reflective&
		operator= (const SV_Reflective& rhs);

		virtual SV_Reflective*
		clone(void) const;

		~SV_Reflective(void);

		void
		set_kr(const float k);

		void
		set_cr(Texture* t_ptr);

		virtual RGBColor
		shade(ShadeRec& s);

        virtual RGBColor
        path_shade(ShadeRec& sr);

        virtual RGBColor
        global_shade(ShadeRec& sr);
	private:

		SV_PerfectSpecular* reflective_brdf;
};


// ---------------------------------------------------------------- set_kr

inline void
SV_Reflective::set_kr(const float k) {
	reflective_brdf->set_kr(k);
}


// ---------------------------------------------------------------- set_cr

inline void
SV_Reflective::set_cr(Texture* t_ptr) {
	reflective_brdf->set_cr(t_ptr);

}


#endif // SV_REFLECTIVE_H
