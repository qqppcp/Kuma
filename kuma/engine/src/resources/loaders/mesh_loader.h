#pragma once

#include "systems/resource_system.h"

class mesh_loader : public resource_loader
{
public:
    mesh_loader();
    virtual b8 load(const char* name, void* params, resource* out_resource) override;
    virtual void unload(resource* resource) override;
};
