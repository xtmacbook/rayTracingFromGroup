#pragma once


#ifndef  _ORTHOGRAPHIC_H_
#define _ORTHOGRAPHIC_H_

#include "Camera.hpp"

class Orthographic : public Camera{
public:
    Orthographic(Point3D eye_p = Point3D(0, 0, 1), Point3D lookat = Point3D(0, 0, -1));
    void render_scene(World& w);
};

#endif