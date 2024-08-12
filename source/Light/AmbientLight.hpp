#pragma once

#include "Light.hpp"

class AmbientLight: public Light {
public:
    AmbientLight();   							
    AmbientLight(const AmbientLight& a); 					 
    virtual Light* clone() const;	
    AmbientLight& operator= (const AmbientLight& rhs);									
    virtual ~AmbientLight();
            
    void scale_radiance(const float b);

    void set_color(const float c);
    void set_color(const RGBColor& c);
    void set_color(const float r, const float g, const float b); 
    
    virtual Vector3D get_direction(ShadeRec& s); 
    
    /* 
    
    From equal(14.1): The incident radiance L_{i} is : L_{i} = l_{s} * c_{l}
    which is independent of p and w_{i}.
    
    The reflected radiance is :  L_{o} = rho * L_{i} 
    
    */
    virtual RGBColor L(ShadeRec& s); 

    virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

protected:
    float		ls;
    RGBColor	color;
};