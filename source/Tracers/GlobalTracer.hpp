#pragma once

#ifndef _GLOBAL_RACER_H
#define _GLOBAL_RACER_H

#include "Tracer.hpp"


class World;

class GlobalTrace : public Tracer {
public:
	GlobalTrace();
	GlobalTrace(World* world_ptr);

	virtual RGBColor trace_ray(const Ray ray, const int depth) const;
	virtual RGBColor trace_ray(const Ray ray, float& tmin, const int depth) const;
};

#endif // !_PATHTRACER_H
