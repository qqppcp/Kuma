#pragma once

#include "systems/resource_system.h"

class text_loader : public resource_loader
{
public:
    text_loader();
    virtual b8 load(const char* name, void* params, resource* out_resource) override;
    virtual void unload(resource* resource) override;
};