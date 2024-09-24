#pragma once

#include "GeometricObject.hpp"
#include "BBox.hpp"

class Torus : public GeometricObject {
public:
    Torus(void);

    Torus(const double _a, const double _b);


    Torus(const Torus& torus);
    Torus& operator=(Torus& rhs);

    virtual Torus* clone(void) const;
    
    Normal compute_normal(const Point3D& p) const;

    bool hit(const Ray& ray, float& t, ShadeRec& s) const;

    virtual bool shadow_hit(const Ray& ray, float& tmin) const;
protected:

    double 		swr;	 	// swept radius
    double		tr;	 	// tube radius

    BBox bbox;
};
