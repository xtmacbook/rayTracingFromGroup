#include "EnvironmentLight.hpp"
#include "../Samplers/Sampler.hpp"
#include "../Utilities/ShadeRec.hpp"
#include "../World/World.hpp"
#include "../Materials/Material.hpp"

void EnvironmentLight::set_sampler(Sampler* s_ptr)
{
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
	sampler_ptr = s_ptr;
	sampler_ptr->map_samples_to_hemisphere(1);
}

Vector3D EnvironmentLight::get_direction(ShadeRec& sr)
{
	w = sr.normal;
	v = Vector3D(0.0034, 1.0, 0.00071) ^ w;
	u = v ^ w;

	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;

	return wi;
}

RGBColor EnvironmentLight::L(ShadeRec& sr)
{
	return materia_ptr->get_Le(sr);
}

bool EnvironmentLight::in_shadow(const Ray& shadowRay, const ShadeRec& sr) const
{
	float t;
	int num_objects = sr.w.objects.size();
	for (int j = 0; j < num_objects; j++) {
		if (sr.w.objects[j]->shadow_hit(shadowRay, t)) {
			return true;
		}
	}
	return false;
}

//p(f)
float EnvironmentLight::pdf(const ShadeRec& sr) const
{
	float ndotwi = sr.normal * wi;
	return  ndotwi / PI;
}

Light* EnvironmentLight::clone() const
{
	return new EnvironmentLight(*this);
}
