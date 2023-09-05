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

typedef struct material_shader_uniform_locations {
    u16 projection;
    u16 view;
    u16 ambient_colour;
    u16 view_position;
    u16 shininess;
    u16 diffuse_colour;
    u16 diffuse_texture;
    u16 specular_texture;
    u16 normal_texture;
    u16 model;
    u16 render_mode;
} material_shader_uniform_locations;

typedef struct ui_shader_uniform_locations {
    u16 projection;
    u16 view;
    u16 diffuse_colour;
    u16 diffuse_texture;
    u16 model;
} ui_shader_uniform_locations;

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
    
    /**
     * @brief Applies global-level data for the material shader id.
     * 
     * @param shader_id The identifier of the shader to apply globals for.
     * @param projection A constant pointer to a projection matrix.
     * @param view A constant pointer to a view matrix.
     * @param ambient_colour The ambient colour of the scene.
     * @param view_position The camera position.
     * @param render_mode The render mode.
     * @return True on success; otherwise false.
     */
    static b8 apply_global(u32 shader_id, const mat4* projection, const mat4* view, const vec4* ambient_colour, const vec3* view_position, u32 render_mode);

    /**
     * @brief Applies instance-level material data for the given material.
     *
     * @param m A pointer to the material to be applied.
     * @return True on success; otherwise false.
     */
    static b8 apply_instance(material* m);

    /**
     * @brief Applies local-level material data (typically just model matrix).
     *
     * @param m A pointer to the material to be applied.
     * @param model A constant pointer to the model matrix to be applied.
     * @return True on success; otherwise false.
     */
    static b8 apply_local(material* m, const mat4* model);
    
    struct material_system_state {
        material_system_config config;

        material default_material;

        // Array of registered materials.
        material* registered_materials;

        // Hashtable for material lookups.
        hashtable registered_material_table;
        
        // Known locations for the material shader.
        material_shader_uniform_locations material_locations;
        u32 material_shader_id;

        // Known locations for the UI shader.
        ui_shader_uniform_locations ui_locations;
        u32 ui_shader_id;
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