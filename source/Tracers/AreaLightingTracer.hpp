#pragma once

#include "Tracer.hpp"

class AreaLightingTracer : public Tracer {
public:
    AreaLightingTracer(World* world_ptr_ = NULL);

	virtual RGBColor trace_ray(const Ray& ray) const;
	virtual RGBColor trace_ray(const Ray ray, const int depth) const;
	virtual RGBColor trace_ray(const Ray ray, float& tmin, const int depth) const;
};