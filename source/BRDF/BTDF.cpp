#include "BTDF.hpp"

BTDF::BTDF(void)
{
}

BTDF::BTDF(const BTDF& btdf)
{
}

BTDF* BTDF::clone(void)
{
	return nullptr;
}

BTDF& BTDF::operator=(const BTDF& rhs)
{
	if (this == &rhs)
		return (*this);

	return (*this);
}

BTDF::~BTDF(void)
{
}

RGBColor BTDF::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	return (black);
}

RGBColor BTDF::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const
{
	return (black);
}

RGBColor BTDF::rho(const ShadeRec& sr, const Vector3D& wo) const
{
	return (black);
}
