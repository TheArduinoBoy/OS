#pragma once

#include <stdint.h>

#include "Paging.h"
#include "PageMapIndex.h"
#include "PageFrameAllocator.h"

#include "../memory.h"

#include "../../util/utils.h"

class PageTableManager {
    public:
        PageTableManager(PageTable* PML4Address);
        void mapMemory(void* vmem, void* pmem, UtilClasses utils);
    private:
        PageTable* PML4Address;
};