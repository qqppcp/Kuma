﻿#pragma once

#include "defines.h"
#include "core/kmemory.h"
#include "resources/resource_types.h"

struct resource_loader;

b8 resource_unload(resource* resource, memory_tag tag);