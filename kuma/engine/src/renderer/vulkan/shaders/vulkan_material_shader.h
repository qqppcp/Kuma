#pragma once

#include "renderer/vulkan/vulkan_types.inl"
#include "renderer/renderer_types.inl"

// struct vulkan_material_shader {
//     // vertex, fragment
//     vulkan_shader_stage stages[MATERIAL_SHADER_STAGE_COUNT];
//
//     VkDescriptorPool global_descriptor_pool;
//     VkDescriptorSetLayout global_descriptor_set_layout;
//
//     // One descriptor set per frame - max 3 for triple-buffering.
//     VkDescriptorSet global_descriptor_sets[3];
//
//     // Global uniform object.
//     global_uniform_object global_ubo;
//
//     // Global uniform buffer.
//     vulkan_buffer global_uniform_buffer;
//     
//     VkDescriptorPool object_descriptor_pool;
//     VkDescriptorSetLayout object_descriptor_set_layout;
//     // Object uniform buffers.
//     vulkan_buffer object_uniform_buffer;
//     // TODO: manage a free list of some kind here instead.
//     u32 object_uniform_buffer_index;
//
//     texture_use sampler_uses[VULKAN_MATERIAL_SHADER_SAMPLER_COUNT];
//     
//     // TODO: make dynamic
//     vulkan_material_shader_instance_state instance_states[VULKAN_MAX_MATERIAL_COUNT];
//     
//     vulkan_pipeline pipeline;
//
// };

class vulkan_material_shader_object
{
public:
    b8 create(vulkan_context* context);
    void destroy(vulkan_context* context);
    void use(vulkan_context* context);
    void update_global_state(vulkan_context* context, const global_uniform_object& update_data, f32 delta_time);
    void update_object(vulkan_context* context, geometry_render_data data);
    b8 acquire_resources(vulkan_context* context, material* material);
    void release_resources(vulkan_context* context, material* material);

    vulkan_material_shader_object() = default;
    ~vulkan_material_shader_object() = default;
private:
    vulkan_material_shader m_shader;
};
