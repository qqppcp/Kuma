#pragma once

#include "resources/resource_types.h"


class resource_loader
{
public:
    virtual b8 load(const char* name, void* params, resource* out_resource) = 0;
    virtual void unload(resource* resource) = 0;
    u32 id;
    resource_type type;
    const char* custom_type;
    const char* type_path;
};

struct resource_system_config
{
    u32 max_loader_count;
    // The relative base path for assets.
    char* asset_base_path;
};
class KAPI resource_system
{
public:
    static b8 initialize(u64* memory_requirement, void* state, resource_system_config config);
    static void shutdown(void* state);
    static b8 register_loader(resource_loader* loader);
    static b8 load(const char* name, resource_type type, void* params, resource* out_resource);
    static b8 load_custom(const char* name, const char* custom_type, void* params, resource* out_resource);
    static void unload(resource* resource);
    static const char* get_base_path();

    struct resource_system_state {
        resource_system_config config;
        resource_loader* registered_loaders[32];
        u8 loader_num;
    };
    static resource_system_state* state_ptr;

private:
    static b8 load(const char* name, resource_loader* loader, void* params, resource* out_resource);
};