#pragma once

#include "stddef.h"

#include "../util/utils.h"

#include "../graphics/print.h"

#include "../memory/paging/PageFrameAllocator.h"
#include "../memory/paging/PageMapIndex.h"
#include "../memory/paging/Paging.h"
#include "../memory/paging/PageTableManager.h"

struct BootInfo {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
};

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

UtilClasses initlize(BootInfo* bootinfo) {
    Print print(bootinfo->framebuffer, bootinfo->psf1_Font);
    print.setCursor(0, 0);
    print.println("Hello, Kernel World!");

    uint64_t mMapEntries = bootinfo->mMapSize / bootinfo->mMapDescSize;
    PageFrameAllocator pageFrameAlloca = PageFrameAllocator();
    pageFrameAlloca.ReadEFIMemoryMap(bootinfo->mMap, bootinfo->mMapSize, bootinfo->mMapDescSize);

    uint64_t kernelSize  = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

    pageFrameAlloca.LockPages(&_KernelStart, kernelPages);

    return {print, pageFrameAlloca};
}