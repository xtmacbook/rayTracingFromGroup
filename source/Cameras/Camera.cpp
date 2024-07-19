#include "Camera.hpp"

Camera::Camera(Point3D eye_p, Point3D lookat):
    eye(eye_p),
    look_at(lookat),
    up(0, 1, 0),
    exposure_time(1)
{}

Camera::~Camera()
{}

void Camera::compute_uvw(){
    w = eye - look_at;
    w.normalize();
    u = up ^ w;
    u.normalize();
    v = w ^ u;
}

void Camera::set_eye(const Point3D eye_p){
    eye = eye_p;
}

void Camera::set_eye(const float x, const float y, const float z){
    eye = Point3D(x, y, z);
}

Point3D Camera::get_eye() const{
    return eye;
}

void Camera::set_lookat(const Point3D lookat){
    look_at = lookat;
}

void Camera::set_lookat(const float x, const float y, const float z){
    look_at = Point3D(x, y, z);
}

Point3D Camera::get_lookat() const{
    return look_at;
}

void Camera::set_up(const Vector3D up_d){
    up = up_d;
}

Vector3D Camera::get_up() const{
    return up;
}

void Camera::set_exposure_time(const float exposure_t){
    exposure_time = exposure_t;
}

float Camera::get_exposure_time() const{
    return exposure_time;
}