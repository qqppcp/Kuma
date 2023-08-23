#pragma once

#include "defines.h"

typedef enum memory_tag {
    // For temporary use. Should be assigned one of the below or have a new tag created.
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_LINEAR_ALLOCATOR,
    MEMORY_TAG_DARRAY,
    MEMORY_TAG_DICT,
    MEMORY_TAG_RING_QUEUE,
    MEMORY_TAG_BST,
    MEMORY_TAG_STRING,
    MEMORY_TAG_APPLICATION,
    MEMORY_TAG_JOB,
    MEMORY_TAG_TEXTURE,
    MEMORY_TAG_MATERIAL_INSTANCE,
    MEMORY_TAG_RENDERER,
    MEMORY_TAG_GAME,
    MEMORY_TAG_TRANSFORM,
    MEMORY_TAG_ENTITY,
    MEMORY_TAG_ENTITY_NODE,
    MEMORY_TAG_SCENE,

    MEMORY_TAG_MAX_TAGS
} memory_tag;

class KAPI KMemory
{
public:
    static  void memory_system_initialize(u64* memory_requirement, void* state);
    static  void memory_system_shutdown(void* state);
    static  void* allocate(u64 size, memory_tag tag);
    static  void free(void* block, u64 size, memory_tag tag);
    static  void* zero_memory(void* block, u64 size);
    static  void* copy_memory(void* dest, const void* source, u64 size);
    static  void* set_memory(void* dest, i32 value, u64 size);
    static  char* get_memory_usage_str();
    static  u64 get_memory_alloc_count();

private:
    struct memory_stats;
    //static memory_stats stats;
};