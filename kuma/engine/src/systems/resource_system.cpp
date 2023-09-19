#include "resource_system.h"

#include "core/logger.h"
#include "core/kstring.h"

// Known resource loaders.
#include "containers/darray.h"
#include "resources/loaders/text_loader.h"
#include "resources/loaders/binary_loader.h"
#include "resources/loaders/image_loader.h"
#include "resources/loaders/material_loader.h"
#include "resources/loaders/shader_loader.h"
#include "resources/loaders/mesh_loader.h"

resource_system::resource_system_state* resource_system::state_ptr = 0;

b8 resource_system::initialize(u64* memory_requirement, void* state, resource_system_config config)
{
    if (config.max_loader_count == 0) {
        KFATAL("resource_system_initialize failed because config.max_loader_count==0.");
        return false;
    }

    *memory_requirement = sizeof(resource_system_state);

    if (!state) {
        return true;
    }

    state_ptr = static_cast<resource_system_state*>(state);
    state_ptr->config = config;

    state_ptr->loader_num = 0;
    for (int i = 0; i < 32; i++)
    {
        state_ptr->registered_loaders[i] = nullptr;
    }
    
    // NOTE: Auto-register known loader types here.
    auto _text_loader     = new text_loader;
    auto _binary_loader   = new binary_loader;
    auto _image_loader    = new image_loader;
    auto _material_loader = new material_loader;
    auto _shader_loader   = new shader_loader;
    auto _mesh_loader     = new mesh_loader;
    register_loader(_text_loader);
    register_loader(_binary_loader);
    register_loader(_image_loader);
    register_loader(_material_loader);
    register_loader(_shader_loader);
    register_loader(_mesh_loader);

    KINFO("Resource system initialized with base path '%s'.", config.asset_base_path);

    return true;
}

void resource_system::shutdown(void* state)
{
    if (state_ptr) {
        
        state_ptr = 0;
    }
}

b8 resource_system::register_loader(resource_loader* loader)
{
    if (state_ptr) {
        
        // Ensure no loaders for the given type already exist
        for (u32 i = 0; i < 32; ++i) {
            resource_loader* l = state_ptr->registered_loaders[i];
            if (l && l->id != INVALID_ID) {
                if (l->type == loader->type) {
                    KERROR("resource_system_register_loader - Loader of type %d already exists and will not be registered.", loader->type);
                    return false;
                } else if (loader->custom_type && string_length(loader->custom_type) > 0 && strings_equali(l->custom_type, loader->custom_type)) {
                    KERROR("resource_system_register_loader - Loader of custom type %s already exists and will not be registered.", loader->custom_type);
                    return false;
                }
            }
        }
        for (u32 i = 0; i < 32; ++i) {
            resource_loader* l = state_ptr->registered_loaders[i];
            if (l && l->id == INVALID_ID)
            {
                l = loader;
                l->id = i;
                KTRACE("Loader registered.");
                return true;
            }
        }
        
        loader->id = state_ptr->loader_num;
        state_ptr->registered_loaders[loader->id] = loader;
        state_ptr->loader_num++;
    }

    for (int i = 0; i < state_ptr->loader_num;++i)
    {
        auto l = state_ptr->registered_loaders[i];
        b8 s = l->type == RESOURCE_TYPE_MESH;
    }
    return false;
}

b8 resource_system::load(const char* name, resource_type type, void* params, resource* out_resource)
{
    if (state_ptr && type != RESOURCE_TYPE_CUSTOM) {
        // Select loader.
        u32 count = state_ptr->config.max_loader_count;
        for (u32 i = 0; i < 32; ++i) {
            resource_loader* l = state_ptr->registered_loaders[i];
            if (l && l->id != INVALID_ID && l->type == type) {
                return load(name, l, params, out_resource);
            }
        }
    }

    out_resource->loader_id = INVALID_ID;
    KERROR("resource_system_load - No loader for type %d was found.", type);
    return false;
}

b8 resource_system::load_custom(const char* name, const char* custom_type, void* params, resource* out_resource)
{
    if (state_ptr && custom_type && string_length(custom_type) > 0) {
        // Select loader.
        u32 count = state_ptr->config.max_loader_count;
        for (u32 i = 0; i < 32; ++i) {
            resource_loader* l = state_ptr->registered_loaders[i];
            if (l && l->id != INVALID_ID && l->type == RESOURCE_TYPE_CUSTOM && strings_equali(l->custom_type, custom_type)) {
                return load(name, l, params, out_resource);
            }
        }
    }

    out_resource->loader_id = INVALID_ID;
    KERROR("resource_system_load_custom - No loader for type %s was found.", custom_type);
    return false;
}

void resource_system::unload(resource* resource)
{
    if (state_ptr && resource) {
        if (resource->loader_id != INVALID_ID) {
            resource_loader* l = state_ptr->registered_loaders[resource->loader_id];
            if (l->id != INVALID_ID) {
                l->unload(resource);
            }
        }
    }
}

const char* resource_system::get_base_path()
{
    if (state_ptr) {
        return state_ptr->config.asset_base_path;
    }

    KERROR("resource_system_base_path called before initialization, returning empty string.");
    return "";
}

b8 resource_system::load(const char* name, resource_loader* loader, void* params, resource* out_resource)
{
    if (!name || !loader || !out_resource) {
        if (out_resource) {
            out_resource->loader_id = INVALID_ID;
        }
        return false;
    }

    out_resource->loader_id = loader->id;
    return loader->load(name, params, out_resource);
}
