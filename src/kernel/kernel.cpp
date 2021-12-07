#include "kernel.h"

extern "C" int _start(BootInfo* bootinfo){
    UtilClasses utils = initlize(bootinfo);
    Print print = utils.print;
    PageFrameAllocator pageFrameAloc = utils.pageFrameAlloc;

    print.print("RAM: ");
    print.print(intToString(((pageFrameAloc.GetFreeRAM() / 1024) / 1024 + (pageFrameAloc.GetUsedRAM() / 1024) / 1024 + (pageFrameAloc.GetReservedRAM() / 1024) / 1024)));
    print.println("MB");
    print.print("Free RAM: ");
    print.print(intToString((pageFrameAloc.GetFreeRAM() / 1024) / 1024));
    print.println("MB");
    print.print("Reserved RAM: ");
    print.print(intToString((pageFrameAloc.GetReservedRAM() / 1024) / 1024));
    print.println("MB");

    PageTable* PML4 = (PageTable*) pageFrameAloc.RequestPage();
    memoryset(PML4, 0, 0x1000);
    PageTableManager pageManager(PML4);

    uint64_t mapEntries = (uint64_t) bootinfo->mMapSize / bootinfo->mMapDescSize;
    uint64_t fbBase = (uint64_t) bootinfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t) bootinfo->framebuffer->BufferSize + 0x1000;

    for(uint64_t t = 0; t < getMemorySize(bootinfo->mMap, mapEntries, bootinfo->mMapDescSize); t += 0x1000)
        pageManager.mapMemory((void*) t, (void*) t, utils);
    // for(uint64_t t = fbBase; t < fbBase + fbSize; t += 4096)
    //     pageManager.mapMemory((void*) t, (void*)t, utils);
    // asm("mov %0, %%cr3" : : "r"(PML4));

    print.println("Successfuly loaded PageTableManager");

    while(1);
    return 0;
}