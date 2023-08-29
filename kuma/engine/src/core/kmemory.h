#pragma once

#include "defines.h"
#include "memory/dynamic_allocator.h"

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

/** @brief The configuration for the memory system. */
typedef struct memory_system_configuration {
    /** @brief The total memory size in byes used by the internal allocator for this system. */
    u64 total_alloc_size;
} memory_system_configuration;

class KAPI KMemory
{
public:
    static  b8 memory_system_initialize(memory_system_configuration config);
    static  void memory_system_shutdown();
    static  void* allocate(u64 size, memory_tag tag);
    static  void free(void* block, u64 size, memory_tag tag);
    static  void* zero_memory(void* block, u64 size);
    static  void* copy_memory(void* dest, const void* source, u64 size);
    static  void* set_memory(void* dest, i32 value, u64 size);
    static  char* get_memory_usage_str();
    static  u64 get_memory_alloc_count();

    struct memory_stats {
        u64 total_allocated;
        u64 tagged_allocations[MEMORY_TAG_MAX_TAGS];
    };

    struct memory_system_state {
        memory_system_configuration config;
        struct memory_stats stats;
        u64 alloc_count;
        u64 allocator_memory_requirement;
        dynamic_allocator allocator;
        void* allocator_block;
    } ;
    
    static memory_system_state* state_ptr;
private:
};