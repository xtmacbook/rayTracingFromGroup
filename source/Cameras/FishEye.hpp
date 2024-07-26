#pragma once

#include "Camera.hpp"
#include "../World/World.hpp"

class FishEyeCamera : public Camera {
public:
    FishEyeCamera(Point3D eye_p = Point3D(0, 0, 1), Point3D lookat = Point3D(0, 0, -1));

    void set_view_distance(const float dist);
    float get_distance_from_vp() const;

    void set_zoom(const float zoom);
    float get_zoom() const;

    void set_psi_max(float);

    virtual void render_scene(World& w);

protected:
    float m_distanceWithViewPlane; // Distance from view-plane
    float zoom; // Zoom factor
    double m_psi_max;

    virtual Vector3D ray_direction(const Point2D& pixel_point,int hres,int vres,float s,float&r_squared) const;
};