#pragma once

#include "systems/resource_system.h"

class material_loader : public resource_loader
{
public:
    material_loader();
    virtual b8 load(const char* name, void* params, resource* out_resource) override;
    virtual void unload(resource* resource) override;
};
