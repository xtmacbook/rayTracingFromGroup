#ifndef SMOOTHUVMESHTRIANGLE_H
#define SMOOTHUVMESHTRIANGLE_H

#include "SmoothMeshTriangle.hpp"

class SmoothUVMeshTriangle : public SmoothMeshTriangle {
public:

	SmoothUVMeshTriangle(void);

	SmoothUVMeshTriangle(Mesh* _meshPtr, const int i0, const int i1, const int i2);

	virtual SmoothUVMeshTriangle* clone(void) const;

	SmoothUVMeshTriangle(const SmoothUVMeshTriangle& fmt);

	virtual ~SmoothUVMeshTriangle(void);

	SmoothUVMeshTriangle& operator= (const SmoothUVMeshTriangle& rhs);

	virtual	bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;

	virtual	bool shadow_hit(const Ray& ray, float& tmin) const;

protected:

	Normal interpolate_normal(const float beta, const float gamma) const;
};

#endif // SMOOTHUVMESHTRIANGLE_H
