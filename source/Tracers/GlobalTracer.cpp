#include "GlobalTracer.hpp"

#include "../World/World.hpp"
#include "../Materials/Material.hpp"

GlobalTrace::GlobalTrace():Tracer()
{
}

GlobalTrace::GlobalTrace(World* world_ptr)
	: Tracer(world_ptr)
{
}

RGBColor GlobalTrace::trace_ray(const Ray ray, const int depth) const
{
	if (depth > world_ptr->vp.max_depth)
		return (black);
	else {
		ShadeRec sr(world_ptr->hit_objects(ray));

		if (sr.hit_an_object) {
			sr.depth = depth;
			sr.ray = ray;

			return (sr.material_ptr->global_shade(sr));
		}
		else
			return (world_ptr->background_color);
	}
}

RGBColor GlobalTrace::trace_ray(const Ray ray, float& tmin, const int depth) const
{
	if (depth > world_ptr->vp.max_depth)
		return (black);
	else {
		ShadeRec sr(world_ptr->hit_objects(ray));

		if (sr.hit_an_object) {
			sr.depth = depth;
			sr.ray = ray;
			tmin = sr.t;     // required for colored transparency
			return (sr.material_ptr->global_shade(sr));
		}
		else {
			tmin = kHugeValue;
			return (world_ptr->background_color);
		}
	}
}
