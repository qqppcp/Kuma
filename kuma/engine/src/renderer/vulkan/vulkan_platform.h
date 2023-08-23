#pragma once

#include "defines.h"
#include <vector>
#include "containers/alloc.h"

struct platform_state;
struct vulkan_context;

b8 platform_create_vulkan_surface(struct vulkan_context* context);

/**
 * Appends the names of required extensions for this platform to
 * the name_darray, which should be created and passed in.
 */
void platform_get_required_extension_names(std::vector<const char*, MyAllc<const char*> >& name_array);