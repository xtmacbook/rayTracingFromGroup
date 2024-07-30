#pragma once
    
#include "../World/World.hpp"   
#include "../Utilities/RGBColor.hpp"
#include "../Utilities/ShadeRec.hpp"

class Material{
public:
    Material();
    Material(const Material& material);
    virtual Material* clone(void) const = 0;
    virtual ~Material();

    //without the shade, we can only render object with a constant color.
    virtual RGBColor shade(ShadeRec& sr);
    virtual RGBColor area_light_shade(ShadeRec& sr);
    virtual RGBColor path_shade(ShadeRec& sr);

    virtual RGBColor get_Le(ShadeRec& sr) const;

    Material& operator= (const Material& rhs);

	bool is_casted_shadows()const;
	void set_casted_shadows(bool);

protected:

    bool m_be_casted_on_it; //whether a material has shadows cast on it
};