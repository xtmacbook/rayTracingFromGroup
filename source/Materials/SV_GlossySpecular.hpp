#ifndef _SV_GLOSSYSPECULAR_H
#define _SV_GLOSSYSPECULAR_H

// this implements glossy specular reflection for direct and indirect illumination

#include "../BRDF/BRDF.hpp"
#include "../Texture/ConstantColor.hpp"

class SV_GlossySpecular: public BRDF {
	public:

		SV_GlossySpecular(void);

		~SV_GlossySpecular(void);

		virtual SV_GlossySpecular*
		clone(void) const;

		virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

		virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

		virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;

		void
		set_ks(const float ks);

		void
		set_exp(const float exp);

		void
		set_cs(Texture* t_ptr);

		void
		set_sampler(Sampler* sp, const float exp);   			// any type of sampling

		void
		set_samples(const int num_samples, const float exp); 	// multi jittered sampling

		void
		set_normal(const Normal& n);


	private:

		float		ks;
		Texture* 	cs;			    // specular color
		float		exp; 		    // specular exponent
		Sampler*	sampler_ptr;    // for use in sample_f
};


inline void
SV_GlossySpecular::set_ks(const float k) {
	ks = k;
}

inline void
SV_GlossySpecular::set_exp(const float e) {
	exp= e;
}


inline void
SV_GlossySpecular::set_cs(Texture* t_ptr) {
	cs = t_ptr;
}

#endif // SV_GLOSSYSPECULAR_H
