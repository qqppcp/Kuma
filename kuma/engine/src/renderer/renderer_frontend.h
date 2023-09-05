#pragma once

#include "renderer_types.inl"

struct shader;
struct shader_uniform;

struct static_mesh_data;
struct platform_state;



b8 renderer_system_initialize(u64* memory_requirement, void* state, const char* application_name);
void renderer_system_shutdown(void* state);

void renderer_on_resized(u16 width, u16 height);

b8 renderer_draw_frame(render_packet* packet);

// HACK: this should not be exposed outside the engine.
KAPI void renderer_set_view(mat4 view, vec3 view_position);

void renderer_texture_create(const u8* pixels, struct texture* texture);

void renderer_texture_destroy(struct texture* texture);

/**
 * @brief Creates a new writeable texture with no data written to it.
 *
 * @param t A pointer to the texture to hold the resources.
 */
void renderer_texture_create_writeable(texture* t);

/**
 * @brief Resizes a texture. There is no check at this level to see if the
 * texture is writeable. Internal resources are destroyed and re-created at
 * the new resolution. Data is lost and would need to be reloaded.
 * 
 * @param t A pointer to the texture to be resized.
 * @param new_width The new width in pixels.
 * @param new_height The new height in pixels.
 */
void renderer_texture_resize(texture* t, u32 new_width, u32 new_height);

/**
 * @brief Writes the given data to the provided texture.
 *
 * @param t A pointer to the texture to be written to. NOTE: Must be a writeable texture.
 * @param offset The offset in bytes from the beginning of the data to be written.
 * @param size The number of bytes to be written.
 * @param pixels The raw image data to be written.
 */
void renderer_texture_write_data(texture* t, u32 offset, u32 size, const u8* pixels);


b8 renderer_create_geometry(geometry* geometry, u32 vertex_size, u32 vertex_count, const void* vertices, u32 index_size, u32 index_count, const void* indices);
void renderer_destroy_geometry(geometry* geometry);

b8 renderer_renderpass_id(const char* name, u8* out_renderpass_id);
b8 renderer_shader_create(struct shader* s, u8 renderpass_id, u8 stage_count, const char** stage_filenames, shader_stage* stages);
void renderer_shader_destroy(struct shader* s);
b8 renderer_shader_initialize(struct shader* s);
b8 renderer_shader_use(struct shader* s);
b8 renderer_shader_bind_globals(struct shader* s);
b8 renderer_shader_bind_instance(struct shader* s, u32 instance_id);
b8 renderer_shader_apply_globals(struct shader* s);
b8 renderer_shader_apply_instance(struct shader* s, b8 needs_update);
b8 renderer_shader_acquire_instance_resources(struct shader* s, texture_map** maps, u32* out_instance_id);
b8 renderer_shader_release_instance_resources(struct shader* s, u32 instance_id);
b8 renderer_set_uniform(struct shader* s, struct shader_uniform* uniform, const void* value);

/**
 * @brief Acquires internal resources for the given texture map.
 *
 * @param map A pointer to the texture map to obtain resources for.
 * @return True on success; otherwise false.
 */
b8 renderer_texture_map_acquire_resources(struct texture_map* map);

/**
 * @brief Releases internal resources for the given texture map.
 *
 * @param map A pointer to the texture map to release resources from.
 */
void renderer_texture_map_release_resources(struct texture_map* map);