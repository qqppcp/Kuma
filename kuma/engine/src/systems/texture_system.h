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

    static texture_system_state* state_ptr;
    
private:
    static b8 create_default_textures(texture_system_state* state);
    static void destroy_default_textures(texture_system_state* state);
    static b8 load_texture(const char* texture_name, texture* t);
    static void destroy_texture(texture* t);
};