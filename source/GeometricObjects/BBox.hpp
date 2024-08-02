#pragma once

#include "../Utilities/Ray.hpp"
#include "../Utilities/Constants.hpp"

class BBox{
public:
    BBox(Point3D p0_ = Point3D(0), Point3D p1_ = Point3D(0));

	BBox(const double x0, const double x1,
		const double y0, const double y1,
		const double z0, const double z1);

    BBox(const BBox& bbox);
    virtual BBox* clone() const;
    BBox& operator= (const BBox& rhs);
    virtual ~BBox();

    virtual bool hit(const Ray& ray) const;
    virtual bool inside(const Point3D p) const;

    Point3D p0;
    Point3D p1;
};