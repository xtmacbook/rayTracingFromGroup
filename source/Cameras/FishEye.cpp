#include "FishEye.hpp"

#include "../Utilities/Constants.hpp"
#include "../Utilities/Point3D.hpp"
#include "../Utilities/Vector3D.hpp"
#include "../Utilities/Debug.hpp"
#include <math.h>
#include "../Utilities/util.hpp"

FishEyeCamera::FishEyeCamera(Point3D eye_p, Point3D lookat):
    Camera(eye_p, lookat),
    m_distanceWithViewPlane(1),
    zoom(1)
{}

void FishEyeCamera::set_view_distance(const float dist){
    m_distanceWithViewPlane = dist;
}

float FishEyeCamera::get_distance_from_vp() const{
    return m_distanceWithViewPlane;
}

void FishEyeCamera::set_zoom(const float zoom){
    this->zoom = zoom;
}

float FishEyeCamera::get_zoom() const{
    return zoom;
}

void FishEyeCamera::set_psi_max(float psi)
{
	m_psi_max = psi;
}

void FishEyeCamera::render_scene(World& w){

	debug_print("FishEyeCamera rendering.\n");
    RGBColor L;
    ViewPlane* vp = &w.vp;
    Ray ray;
    Point2D sp;
    Point2D pp;
    int depth = 0;
	int n = (int)sqrt(vp->num_samples);

    w.openWindow(vp->hres, vp->vres);
    vp->m_pixelSize /= zoom;
    ray.o = eye;
	    
	// TIME MANAGER
	struct timespec start_processing;
	struct timespec start_displaying;
	struct timespec now;
	clock_gettime( &start_processing);
	float time_displaying = 0;

	debug_print("Joining entering 2d-for.\n");
    for (int r = 0; r < vp->vres; r++) {	
		for (int c = 0; c <= vp->hres; c++) {					

			// PROCESSING STUFF	
			// ANTI ALIASING
			L = black;
			debug_print("Getting anti aliasing samples.\n");
			for (int p = 0; p < n; p++) {
				for (int q = 0; q < n; q++) {
					pp.x = vp->m_pixelSize * (c - 0.5 * vp->hres + (q + 0.5) / n);
					pp.y = vp->m_pixelSize * (r - 0.5 * vp->vres + (p + 0.5) / n);
					float r_squared;
					ray.d = ray_direction(pp,vp->hres,vp->vres,vp->m_pixelSize, r_squared);
					if(r_squared)
						L += w.tracer_ptr->trace_ray(ray, depth);
				}
			}
			debug_print("Anti aliasing samples get.\n");
			L /= vp->num_samples;
					
			clock_gettime( &start_displaying); 			
			
			// DISPLAYING STUFF
			w.display_pixel(r, c, L);
			w.window->update();
			if(!w.window->isOpen()){
				return;
			}

            // TIME MANAGER
			clock_gettime( &now); 			
			time_displaying += (now.tv_sec - start_displaying.tv_sec);
			time_displaying += (now.tv_nsec - start_displaying.tv_nsec)/1000000000.0;
		}	
	}
	printf("\r\nRendering completed.\nTotal processing time: %.4f seconds.\nTotal displaying time: %.4f seconds.\n", 
		(now.tv_sec - start_processing.tv_sec)+((now.tv_nsec - start_processing.tv_nsec)/1000000000.0) - time_displaying, time_displaying);
	while(w.window->isOpen()){
		w.window->update();
	}	
}

Vector3D FishEyeCamera::ray_direction(const Point2D& pixel_point, int hres, int vres, float s, float& r_squared) const {
    
	Point2D pn(2.0 / (s * hres) * pixel_point.x, 2.0 / (s * vres) * pixel_point.y);
	r_squared = pn.x * pn.x + pn.y * pn.y;

	if (r_squared <= 1.0)
	{
		float r = sqrt(r_squared);
		float psi = r * m_psi_max * PI_ON_180;
		float sin_psi = sin(psi);
		float cos_psi = cos(psi);

		float sin_alpha = pn.y / r;
		float cos_alpha = pn.x / r;

		Vector3D dir = sin_psi * cos_alpha * u + sin_psi * sin_alpha * v - cos_psi * w;

		return dir;
	}

    return Vector3D(0.0);
}