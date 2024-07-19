#pragma once

#include "Sampler.hpp"

class Regular : public Sampler{
public:
    Regular(int samples = 1, int sets = 50);
    virtual Sampler* clone() const;
    virtual void generate_samples();
};