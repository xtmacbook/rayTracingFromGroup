#pragma once

#include "Compound.hpp"
#include "Mesh.hpp"
#ifndef __GRID__
#define __GRID__

#include "../Utilities/ShadeRec.hpp"


class Grid : public Compound {
public:

	Grid(void);

	Grid(Mesh* _mesh_ptr);

	virtual Grid* clone(void) const;

	Grid(const Grid& rg);

	Grid& operator= (const Grid& rhs);

	virtual ~Grid(void);

	virtual BBox get_bounding_box(void);
#if 1
	void read_flat_triangles(char* file_name);

	void read_smooth_triangles(const char* file_name);
#endif // 0
#if 1
	void read_flat_uv_triangles(char* file_name);

	void read_smooth_uv_triangles(char* file_name);
#endif // 0

	void tessellate_flat_sphere(const int horizontal_steps, const int vertical_steps);

	void tessellate_smooth_sphere(const int horizontal_steps, const int vertical_steps);

	void tessellate_flat_horn(const int horizontal_steps, const int vertical_steps);

	void tessellate_flat_bezier_patches(const int horizontal_steps, const int vertical_steps,
		float vertices[306][3], int patches[32][16], const int patches_num);
	// tessellate utah teapot

	void tessellate_flat_rotational_sweeping(const int horizontal_steps, const int vertical_steps,
		Point2D* ctrl_points, const int ctrl_points_num, const bool reverse_normal);

	virtual bool hit(const Ray& ray, float& tmin, ShadeRec& sr) const;

	virtual bool shadow_hit(const Ray& ray, float& tmin) const;

	void setup_cells(void);
#if 1
	void reverse_mesh_normals(void);
#endif // 0
	void store_material(Material* material, const int index);

private:

	std::vector<GeometricObject*>	cells;			// grid of cells
	int							nx, ny, nz;    	// number of cells in the x, y, and z directions
	BBox						bbox;			// bounding box
	Mesh* mesh_ptr;		// holds triangle data
	bool						reverse_normal;	// some PLY files have normals that point inwards

	Point3D find_min_bounds(void);

	Point3D find_max_bounds(void);

	void read_ply_file(const char* file_name, const int triangle_type);

	void read_uv_ply_file(char* file_name, const int triangle_type);
#if 1
	void compute_mesh_normals(void);
#endif // 0
};

#if 1
// ------------------------------------------------------------------------------ reverse_mesh_normals

inline void
Grid::reverse_mesh_normals(void) {
	reverse_normal = true;
}
#endif // 0

// ------------------------------------------------------------------------------ store_material
// stores the material in the specified object
// this is called from the Rosette and Archway classes, which inherit from Grid

inline void
Grid::store_material(Material* material_ptr, const int index) {
	objects[index]->set_material(material_ptr);
}

#endif









