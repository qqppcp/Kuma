﻿#pragma once

#include "renderer/vulkan/vulkan_types.inl"
#include "renderer/renderer_types.inl"

b8 vulkan_ui_shader_create(vulkan_context* context, vulkan_ui_shader* out_shader);

void vulkan_ui_shader_destroy(vulkan_context* context, struct vulkan_ui_shader* shader);

void vulkan_ui_shader_use(vulkan_context* context, struct vulkan_ui_shader* shader);

void vulkan_ui_shader_update_global_state(vulkan_context* context, struct vulkan_ui_shader* shader, f32 delta_time);

void vulkan_ui_shader_set_model(vulkan_context* context, struct vulkan_ui_shader* shader, mat4 model);
void vulkan_ui_shader_apply_material(vulkan_context* context, struct vulkan_ui_shader* shader, material* material);

b8 vulkan_ui_shader_acquire_resources(vulkan_context* context, struct vulkan_ui_shader* shader, material* material);
void vulkan_ui_shader_release_resources(vulkan_context* context, struct vulkan_ui_shader* shader, material* material);