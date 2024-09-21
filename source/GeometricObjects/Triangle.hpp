#pragma once

#include "GeometricObject.hpp"
#include "../Utilities/Maths.hpp"

class Triangle : public GeometricObject {
public:
    Point3D v0, v1, v2;
    Normal normal;

    Triangle();
    Triangle(const Point3D& a, const Point3D& b, const Point3D& c, Material* material_p = nullptr); 
    Triangle(const Point3D& a, const Point3D& b, const Point3D& c, const bool reverse_normal);

    Triangle(const Triangle& triangle);
    Triangle& operator=(const Triangle& rhs);
    Triangle* clone() const;

    void compute_normal();

    void compute_normal(const bool reverse_normal);

    virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const; 
    virtual bool shadow_hit(const Ray& ray, float& tmin) const;
    virtual BBox get_bounding_box() const;
};