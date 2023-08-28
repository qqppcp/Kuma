#pragma once

#include "defines.h"
#include "containers/hashtable.h"

#include "resources/resource_types.h"

#define DEFAULT_MATERIAL_NAME "default"

// typedef enum texture_use {
//     TEXTURE_USE_UNKNOWN = 0x00,
//     TEXTURE_USE_MAP_DIFFUSE = 0x01
// } texture_use;
//
// typedef struct texture_map {
//     texture* texture;
//     texture_use use;
// } texture_map;
//
// #define MATERIAL_NAME_MAX_LENGTH 256
// typedef struct material {
//     u32 id;
//     u32 generation;
//     u32 internal_id;
//     char name[MATERIAL_NAME_MAX_LENGTH];
//     vec4 diffuse_colour;
//     texture_map diffuse_map;
// } material;

struct material_system_config {
    u32 max_material_count;
};

class material_system
{
public:
    static b8 initialize(u64* memory_requirement, void* state, material_system_config config);
    static void shutdown(void* state);
    /**
     * \brief load material config (not material system config) from file
     * and config.name = file name or the reflect name in file
     * \param name file name
     * \return material pointer
     */
    static material* acquire_by_name(const char* name);
    static material* acquire_from_config(material_config config);
    static void release_by_name(const char* name);
    static material* get_default_material();

    struct material_system_state {
        material_system_config config;

        material default_material;

        // Array of registered materials.
        material* registered_materials;

        // Hashtable for material lookups.
        hashtable registered_material_table;
    };

    struct material_reference {
        u64 reference_count;
        u32 handle;
        b8 auto_release;
    };

    static material_system_state* state_ptr;

private:
    static b8 create_default_material(material_system_state* state);
    static b8 load_material(material_config config, material* m);
    static void destroy_material(material* m);

};
