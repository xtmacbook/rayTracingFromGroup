#include "PerfectTransmitter.hpp"

bool PerfectTransmitter::tir(const ShadeRec& sr) const
{
	Vector3D wo(-sr.ray.d);
	float cos_thetai = sr.normal * wo;
	float eta = ior;

	if (cos_thetai < 0.0)
		eta = 1.0 / eta;

	return (1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta) < 0.0);
}

RGBColor PerfectTransmitter::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	return (black);
}

RGBColor PerfectTransmitter::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const
{
	Normal n(sr.normal);
	float cos_thetai = n * wo;
	float eta = ior;

	if (cos_thetai < 0.0) {			// transmitted ray is outside     
		cos_thetai = -cos_thetai;
		n = -n;  					// reverse direction of normal
		eta = 1.0 / eta; 			// invert ior 
	}

	float temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta);
	float cos_theta2 = sqrt(temp);
	wt = -wo / eta - (cos_theta2 - cos_thetai / eta) * n;

	return (kt / (eta * eta) * white / fabs(sr.normal * wt));
}


/*
 Do you know why?
We can now look at some images. The scene I'll use contains a reflective and a transparent sphere with a checkerboard rectangle, two point lights, and a direc- tional light.
Figure 27.12 is a view of the spheres looking vertically down to show their relative locations.
Listing 27.5 shows how to construct the transparent sphere.
A problem with transparency is that we often don't have an intuitive idea of what the images should look like. Therefore,
when you ray trace a new transparent object type, how can you tell if the images are correct? It's always a good idea to start with n = 1.
Although that's not physically correct, the lack of refraction will immediately tell you if the rays are going through the object correctly.
If that's not happening, you can fix any problems at this
Figure 27.12. A reflective and a trans parent sphere.

*/

RGBColor PerfectTransmitter::rho(const ShadeRec& sr, const Vector3D& wo) const
{
	return (black);
}

PerfectTransmitter::PerfectTransmitter(void) :BTDF(), kt(0.0), ior(1.0)
{
}

PerfectTransmitter::PerfectTransmitter(const PerfectTransmitter& pt) : BTDF(pt), kt(pt.kt), ior(pt.ior)
{
}

PerfectTransmitter* PerfectTransmitter::clone(void)
{
	return (new PerfectTransmitter(*this));
}

PerfectTransmitter::~PerfectTransmitter(void)
{
}

PerfectTransmitter& PerfectTransmitter::operator=(const PerfectTransmitter& rhs)
{
	if (this == &rhs)
		return (*this);

	kt = rhs.kt;
	ior = rhs.ior;

	return (*this);
}

void PerfectTransmitter::set_kt(const float k)
{
	kt = k;
}

void PerfectTransmitter::set_ior(const float eta)
{
	ior = eta;
}

