#ifndef _SV_PHONG_H
#define _SV_PHONG_H

#include "Material.hpp"
#include "SV_Lambertian.hpp"
#include "SV_GlossySpecular.hpp"

class SV_Phong: public Material {
	public:

		SV_Phong(void);

		SV_Phong(const SV_Phong& p);

		virtual Material*
		clone(void) const;

		SV_Phong&
		operator= (const SV_Phong& rhs);

		~SV_Phong(void);

		void
		set_ka(const float k);

		void
		set_kd(const float k);

		void
		set_ks(const float k);

		void
		set_exp (const float exp);

		void
		set_cd(Texture* t_ptr);

		void
		set_cs(Texture* t_ptr);

		virtual RGBColor
		shade(ShadeRec& sr);

        virtual RGBColor
        area_light_shade(ShadeRec& sr);

	private:

		SV_Lambertian*		ambient_brdf;
		SV_Lambertian*		diffuse_brdf;
		SV_GlossySpecular*	specular_brdf;
};


// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection
// is diffuse reflection

inline void
SV_Phong::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}

// this also sets Lambertian::kd, but for a different Lambertian object

inline void
SV_Phong::set_kd (const float kd) {
	diffuse_brdf->set_kd(kd);
}


// this sets GlossySpecular::ks

inline void
SV_Phong::set_ks (const float ks) {
	specular_brdf->set_ks(ks);
}

// this sets GlossySpecular::ks

inline void
SV_Phong::set_exp (const float exp) {
	specular_brdf->set_exp(exp);
}

inline void
SV_Phong::set_cd(Texture* t_ptr) {
	ambient_brdf->set_cd(t_ptr);
	diffuse_brdf->set_cd(t_ptr);
}

inline void
SV_Phong::set_cs(Texture* t_ptr) {
    specular_brdf->set_cs(t_ptr);
}

#endif // SV_PHONG_H
