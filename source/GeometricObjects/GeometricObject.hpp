#pragma once

#include "../Utilities/Point3D.hpp"
#include "../Utilities/Ray.hpp"
#include "../Utilities/ShadeRec.hpp"
#include "../GeometricObjects/BBox.hpp"
					
class GeometricObject {	
public:	
	GeometricObject(Material* material_p = NULL);
	GeometricObject(const GeometricObject& object);		// copy constructor
	virtual GeometricObject* clone(void) const = 0;		// virtual copy constructor
	virtual ~GeometricObject ();						// destructor
		
	virtual bool hit(const Ray& ray, float& t, ShadeRec& s) const = 0; 	
	virtual bool shadow_hit(const Ray& ray, float& tmin) const;											 

	virtual void set_material(Material* material_p);
	Material* get_material() const;

	virtual BBox get_bounding_box() const; 
	virtual void add_object(GeometricObject* object_ptr);
	
	virtual Normal get_normal() const; 
	virtual Normal get_normal(const Point3D& p) const;

	/**
	 * for this object as object of area light geometry
	 */
	virtual Point3D sample();
    virtual float pdf(const ShadeRec& sr);

	bool is_casts_shadows()const;
	void set_casts_shadows(bool);

protected:
	mutable Material* material_ptr;
	GeometricObject& operator= (const GeometricObject& rhs);

	bool m_casts_shadows; //whether this object casts shadows
};