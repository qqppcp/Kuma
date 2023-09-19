#include "loader_utils.h"

#include "core/kmemory.h"
#include "core/logger.h"
#include "core/kstring.h"

b8 resource_unload(resource* resource, memory_tag tag) {
    if (!resource) {
        KWARN("resource_unload called with nullptr for resource.");
        return false;
    }

    if (resource->full_path) {
        u32 path_length = string_length(resource->full_path);
        if (path_length) {
            KMemory::free(resource->full_path, sizeof(char) * path_length + 1, MEMORY_TAG_STRING);
        }
    }

    if (resource->data) {
        KMemory::free(resource->data, resource->data_size, tag);
        resource->data = 0;
        resource->data_size = 0;
        resource->loader_id = INVALID_ID;
    }

    return true;
}