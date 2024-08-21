#include "Phong.hpp"

#include "../World/World.hpp"
#include "../Light/Light.hpp"

Phong::Phong(Lambertian* ambient_brdf_, Lambertian* diffuse_brdf_, GlossySpecular* specular_brdf_):
    Material()
{
    ambient_brdf = ambient_brdf_;
    diffuse_brdf = diffuse_brdf_;
    specular_brdf = specular_brdf_;
    if(ambient_brdf_ == nullptr){
        ambient_brdf = new Lambertian();
    }
    if(diffuse_brdf_ == nullptr){
        diffuse_brdf = new Lambertian();
    }
    if(specular_brdf_ == nullptr){
        specular_brdf = new GlossySpecular();
    }
}

Phong::Phong(const Phong& m):
    Material(m)
{   
    if(m.ambient_brdf){
        ambient_brdf = m.ambient_brdf->clone();
    }
    else{
        ambient_brdf = new Lambertian;
    }

    if(m.diffuse_brdf){
        diffuse_brdf = m.diffuse_brdf->clone();
    }
    else{
        diffuse_brdf = new Lambertian;
    }

    if(m.specular_brdf){
        specular_brdf = m.specular_brdf->clone();
    }
    else{
        specular_brdf = new GlossySpecular;
    }
}

Phong* Phong::clone() const{
    return (new Phong(*this));
}

Phong* Phong::clone(RGBColor new_color) const {
    Phong* new_pong = new Phong(*this);
    new_pong->set_cd(new_color);
    return (new_pong);
}

Phong& Phong::operator=(const Phong& rhs){
    if(this == &rhs){
        return (*this);
    }
    Material::operator=(rhs);
    if(ambient_brdf && rhs.ambient_brdf){
        delete ambient_brdf;
        ambient_brdf = rhs.ambient_brdf->clone();
    }
    if(diffuse_brdf && rhs.diffuse_brdf){
        delete diffuse_brdf;
        diffuse_brdf = rhs.diffuse_brdf->clone();
    }
    if(specular_brdf && rhs.specular_brdf){
        delete specular_brdf;
        specular_brdf = rhs.specular_brdf->clone();
    }
    return(*this);
}

Phong::~Phong(){
    if(ambient_brdf){
        delete ambient_brdf;
        ambient_brdf = nullptr;
    }

    if(diffuse_brdf){
        delete diffuse_brdf;
        diffuse_brdf = nullptr;
    }

    if(specular_brdf){
        delete specular_brdf;
        specular_brdf = nullptr;
    }
}

Lambertian* Phong::get_ambient_brdf() const{
    return ambient_brdf;
}

void Phong::set_ambient_brdf(Lambertian* ambient_brdf_){
    if(ambient_brdf_ != nullptr)
        ambient_brdf = ambient_brdf_;
}

Lambertian* Phong::get_diffuse_brdf() const{
    return diffuse_brdf;
}

void Phong::set_diffuse_brdf(Lambertian* diffuse_brdf_){
    if(diffuse_brdf_ != nullptr)
        diffuse_brdf = diffuse_brdf_;
}


GlossySpecular* Phong::get_specular_brdf() const{
    return specular_brdf;
}

void Phong::set_specular_brdf(GlossySpecular* specular_brdf_){
    if(specular_brdf_ != nullptr)
        specular_brdf = specular_brdf_;
}

void Phong::set_ka(const float k){
    ambient_brdf->set_kd(k);
}

void Phong::set_kd(const float k){
    diffuse_brdf->set_kd(k);
}

void Phong::set_ks(const float k){
    specular_brdf->set_ks(k);
}

void Phong::set_cd(const RGBColor& c){
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
    specular_brdf->set_cs(c);
}   

void Phong::set_cd(const float r, const float g, const float b){
    ambient_brdf->set_cd(RGBColor(r, g, b));
    diffuse_brdf->set_cd(RGBColor(r, g, b));
    specular_brdf->set_cs(RGBColor(r, g, b));
}   

void Phong::set_cd(const float a){
    ambient_brdf->set_cd(RGBColor(a));
    diffuse_brdf->set_cd(RGBColor(a));
    specular_brdf->set_cs(RGBColor(a));
}   

void Phong::set_scd(const RGBColor& c)
{
	specular_brdf->set_cs(c);
}

void Phong::set_exp(const float exp_){
    specular_brdf->set_exp(exp_);
}


RGBColor Phong::shade(ShadeRec& sr){
	Vector3D 	wo 			= -sr.ray.d;
	RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int 		num_lights	= sr.w.lights.size();
	
	for (int j = 0; j < num_lights; j++) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);    
		float ndotwi = sr.normal * wi;
	
		if (ndotwi > 0.0) { // hit point toward the light
        	bool in_shadow = false;
            if(sr.w.lights[j]->get_shadows()){
                Ray shadowRay(sr.hit_point, wi);  //constructs the shadow ray and test if the hit point is in shadow
                in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
            }
            if(!in_shadow){
                L += (	diffuse_brdf->f(sr, wo, wi) + 
				    	specular_brdf->f(sr, wo, wi)) * sr.w.lights[j]->L(sr) * ndotwi;
            }
        }
    }
	
	return (L);
}

RGBColor Phong::area_light_shade(ShadeRec& sr){
    Vector3D 	wo 			= -sr.ray.d;
	RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int 		num_lights	= sr.w.lights.size();
	
	for (int j = 0; j < num_lights; j++) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);    
		float ndotwi = sr.normal * wi;
	
		if (ndotwi > 0.0) {
        	bool in_shadow = false;
            if(sr.w.lights[j]->get_shadows()){
                Ray shadowRay(sr.hit_point, wi);
                in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
            }
            if(!in_shadow){
                L += (	diffuse_brdf->f(sr, wo, wi) + 
				    	specular_brdf->f(sr, wo, wi)) * sr.w.lights[j]->L(sr) * ndotwi
                        *sr.w.lights[j]->G(sr)*ndotwi / sr.w.lights[j]->pdf(sr);
            }
        }
    }
	
	return (L);
}