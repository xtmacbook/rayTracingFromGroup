#include "PathTracer.hpp"
#include "../World/World.hpp"
#include "../Materials/Material.hpp"

PathTrace::PathTrace():Tracer()
{
}

PathTrace::PathTrace(World* world_ptr):Tracer(world_ptr)
{
}

RGBColor PathTrace::trace_ray(const Ray ray, const int depth) const
{
	if (depth > world_ptr->vp.max_depth)
		return (black);

	ShadeRec sr(world_ptr->hit_objects(ray));
	if (sr.hit_an_object)
	{
		sr.depth = depth;
		sr.ray = ray;

		return (sr.material_ptr->path_shade(sr));
	}
	return world_ptr->background_color;
}

RGBColor PathTrace::trace_ray(const Ray ray, float& tmin, const int depth) const
{
	if (depth > world_ptr->vp.max_depth)
		return (black);
	else {
		ShadeRec sr(world_ptr->hit_objects(ray));

		if (sr.hit_an_object) {
			sr.depth = depth;
			sr.ray = ray;
			tmin = sr.t;     // required for colored transparency
			return (sr.material_ptr->path_shade(sr));
		}
		else {
			tmin = kHugeValue;
			return (world_ptr->background_color);
		}
	}
}
