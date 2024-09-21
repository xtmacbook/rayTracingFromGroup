#include "MeshTriangle.hpp"

MeshTriangle::MeshTriangle(Mesh* mesh_ptr_, const int i0, const int i1, const int i2)
    : GeometricObject()
    , index0(i0)
    , index1(i1)
    , index2(i2) 
    , normal(0) 
    , mesh_ptr(mesh_ptr_)
{}

MeshTriangle::MeshTriangle(const MeshTriangle& mesh_triangle)
    : GeometricObject(mesh_triangle)
    , index0(mesh_triangle.index0)
    , index1(mesh_triangle.index1)
    , index2(mesh_triangle.index2)
    , normal(mesh_triangle.normal) {
    if(mesh_triangle.mesh_ptr){
        mesh_ptr = mesh_triangle.mesh_ptr->clone();
    }
    else{
        mesh_ptr = nullptr;
    }
}

MeshTriangle& MeshTriangle::operator=(const MeshTriangle& rhs) {
    if(this == &rhs){
        return (*this);
    }
    GeometricObject::operator=(rhs);
    index0 = rhs.index0;
    index1 = rhs.index1;
    index2 = rhs.index2;
    normal = rhs.normal;
    if(mesh_ptr){
        delete mesh_ptr;
        mesh_ptr = nullptr;
    }
    if(rhs.mesh_ptr){
        mesh_ptr = rhs.mesh_ptr->clone();
    }
    return (*this);
}

MeshTriangle::~MeshTriangle(){
    if(mesh_ptr){
        delete mesh_ptr;
        mesh_ptr = nullptr;
    }
}

void MeshTriangle::set_mesh_ptr(Mesh* mesh_ptr_){
    mesh_ptr = mesh_ptr_;
}

Mesh* MeshTriangle::get_mesh_ptr() const{
    return mesh_ptr;
}

Normal MeshTriangle::get_normal() const {
    return normal;
}

void MeshTriangle::compute_normal(const bool reverse_normal){
    normal =  (mesh_ptr->vertices[index1] - mesh_ptr->vertices[index0]) 
            ^ (mesh_ptr->vertices[index2] - mesh_ptr->vertices[index0]);
    normal.normalize();
    if(reverse_normal){
        normal = -normal;
    }
}

bool MeshTriangle::shadow_hit(const Ray& ray, float& tmin) const
{
    Point3D v0(mesh_ptr->vertices[index0]);
    Point3D v1(mesh_ptr->vertices[index1]);
    Point3D v2(mesh_ptr->vertices[index2]);

    double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
    double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
    double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

    double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
    double q = g * i - e * k, s = e * j - f * i;

    double inv_denom = 1.0 / (a * m + b * q + c * s);

    double e1 = d * m - b * n - c * p;
    double beta = e1 * inv_denom;

    if (beta < 0.0)
        return (false);

    double r = r = e * l - h * i;
    double e2 = a * n + d * q + c * r;
    double gamma = e2 * inv_denom;

    if (gamma < 0.0)
        return (false);

    if (beta + gamma > 1.0)
        return (false);

    double e3 = a * p - b * r + d * s;
    double t = e3 * inv_denom;

    if (t < kEpsilon)
        return (false);

    tmin = t;

    return (true);
}

BBox MeshTriangle::get_bounding_box() const {
    double delta = 0.0001;
    Point3D v1(mesh_ptr->vertices[index0]);
    Point3D v2(mesh_ptr->vertices[index1]);
    Point3D v3(mesh_ptr->vertices[index2]);

    return (BBox(Point3D(min(min(v1.x, v2.x), v3.x) - delta,
                         min(min(v1.y, v2.y), v3.y) - delta,
                         min(min(v1.z, v2.z), v3.z) - delta),
                 Point3D(max(max(v1.x, v2.x), v3.x) + delta,
                         max(max(v1.y, v2.y), v3.y) + delta,
                         max(max(v1.z, v2.z), v3.z) + delta)));
}

float MeshTriangle::interpolate_u(const float beta, const float gamma) const {
    return((1 - beta - gamma) * mesh_ptr->u[index0]
        + beta * mesh_ptr->u[index1]
        + gamma * mesh_ptr->u[index2]);
}

float MeshTriangle::interpolate_v(const float beta, const float gamma) const {
    return((1 - beta - gamma) * mesh_ptr->v[index0]
        + beta * mesh_ptr->v[index1]
        + gamma * mesh_ptr->v[index2]);
}