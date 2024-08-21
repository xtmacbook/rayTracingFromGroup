#pragma once

#include "Tracer.hpp"

//for specular-to-specular light transport

class Whitted : public Tracer {
    public:
    Whitted(World* world_ptr_ = nullptr);

	virtual RGBColor trace_ray(const Ray& ray) const;
	virtual RGBColor trace_ray(const Ray ray, const int depth) const;
	virtual RGBColor trace_ray(const Ray ray, float& tmin, const int depth) const;
};