#pragma once

#ifndef _PATHTRACER_H
#define _PATHTRACER_H

#include "Tracer.hpp"

/**
 * 
 * rendering scene with area light source.This mean that pure path tracing 
   can't be used  with point and directional lights,as there are no light surfaces for the rays to hit
   With the exception of environment lights,light sources are usually small compared to other objects in a scene.
   In this situation,path tracing is particularly inefficient because the fraction of ray paths through a scene 
   that actually hit a light source surface will be small
 */

class World;

class PathTrace : public Tracer {
public:
	PathTrace();
	PathTrace(World* _world_ptr);
	virtual ~PathTrace();

	void set_world_ptr(World* world_ptr_);
	World* get_world_ptr() const;

	virtual RGBColor trace_ray(const Ray& ray) const;
	virtual RGBColor trace_ray(const Ray ray, const int depth) const;
	virtual RGBColor trace_ray(const Ray ray, float& tmin, const int depth) const;

protected:
	World* world_ptr;
};

#endif // !_PATHTRACER_H
