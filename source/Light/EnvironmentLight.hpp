#pragma once

#include "../Utilities/Vector3D.hpp"
#include "../Utilities/RGBColor.hpp"
#include "../Utilities/Ray.hpp"
#include "Light.hpp"

class ShadeRec;
class Sampler;
class Material;

class EnvironmentLight: public Light{
public:

    //virtual float G(const ShadeRec& sr) const;
    void set_sampler(Sampler * s_ptr);

	virtual Vector3D get_direction(ShadeRec& sr) ; //return the direction of the incoming light at a hit point
	virtual RGBColor L(ShadeRec& sr); // return the incident radiance at a hit point
	virtual bool in_shadow(const Ray& shadowRay, const ShadeRec& sr) const;
	virtual float pdf(const ShadeRec& sr) const;

	virtual Light* clone() const;

	void set_material(Material* material);

private:
	Vector3D u, v, w;
	Sampler* sampler_ptr = nullptr;
	Vector3D wi;
	Material* materia_ptr = nullptr;
};