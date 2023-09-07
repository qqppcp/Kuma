#pragma once

#include "containers/hashtable.h"
#include "renderer/renderer_types.inl"

#define DEFAULT_TEXTURE_NAME "default"
#define DEFAULT_DIFFUSE_TEXTURE_NAME "default_DIFF"
#define DEFAULT_SPECULAR_TEXTURE_NAME "default_SPEC"
#define DEFAULT_NORMAL_TEXTURE_NAME "default_NORM"

struct texture_system_config {
    u32 max_texture_count;
};

// typedef struct texture {
//     u32 id;
//     u32 width;
//     u32 height;
//     u8 channel_count;
//     b8 has_transparency;
//     u32 generation;
//     char name[TEXTURE_NAME_MAX_LENGTH];
//     void* internal_data;
// } texture;

class texture_system
{
public:
    static  b8 initialize(u64* memory_requirement, void* state, texture_system_config config);
    static  void shutdown(void* state);

    /**
     * @brief Use texture name(ie. file name) to acquire texture handle
     * @param name texture name
     * @param auto_release decide to release by release func when reference minus to 0 if set true 
     * @return texture pointer
     */
    static texture* acquire_by_name(const char* name, b8 auto_release);
    static void release_by_name(const char* name);
    static texture* get_default_texture();
    static texture* get_default_diffuse_texture();
    static texture* get_default_specular_texture();
    static texture* get_default_normal_texture();
    static texture* acquire_cube(const char* name, b8 auto_release);

    static texture* aquire_writeable(const char* name, u32 width, u32 height, u8 channel_count, b8 has_transparency);
    static texture* wrap_internal(const char* name, u32 width, u32 height, u8 channel_count, b8 has_transparency, b8 is_writeable, b8 register_texture, void* internal_data);
    static b8 set_internal(texture* t, void* internal_data);
    static b8 resize(texture* t, u32 width, u32 height, b8 regenerate_internal_data);
    static b8 load_texture(const char* texture_name, texture* t);

    struct texture_system_state {
        texture_system_config config;
        texture default_texture;
        texture default_diffuse_texture;
        texture default_specular_texture;
        texture default_normal_texture;

        // Array of registered textures.
        texture* registered_textures;

        // Hashtable for texture lookups.
        hashtable registered_texture_table;
    };
    struct texture_reference {
        u64 reference_count;
        u32 handle;
        b8 auto_release;
    };

    // Also used as result_data from job.
    struct texture_load_params {
        char* resource_name;
        texture* out_texture;
        texture temp_texture;
        u32 current_generation;
        resource image_resource;
    };


    static texture_system_state* state_ptr;
    
private:
    static void texture_load_job_success(void* params);
    static void texture_load_job_fail(void* params);
    static b8 texture_load_job_start(void* params, void* result_data);
    static b8 create_default_textures(texture_system_state* state);
    static void destroy_default_textures(texture_system_state* state);
    static void destroy_texture(texture* t);
    static b8 process_texture_reference(const char* name, texture_type type, i8 reference_diff, b8 auto_release, b8 skip_load, u32* out_texture_id);
    static b8 load_cube_textures(const char* name, const char texture_names[6][TEXTURE_NAME_MAX_LENGTH], texture* t);
};