#include "PageTableManager.h"

PageTableManager::PageTableManager(PageTable* PML4Address) {
    this->PML4Address = PML4Address;
}

void PageTableManager::mapMemory(void* vmem, void* pmem, UtilClasses utils) {
    PageFrameAllocator pageFrameAloc = utils.pageFrameAlloc;
    PageMapIndex indexer((uint64_t) vmem);
    
    PageDirEntry PDE = PML4Address->entries[indexer.getPDP()];
    PageTable* PDP;
    if(!PDE.Present) {
        PDP = (PageTable*) pageFrameAloc.RequestPage();
        memoryset(PDP, 0, 0x1000);
        PDE.Address = (uint64_t) PDP >> 12;
        PDE.Present = true;
        PDE.RW = true;
        PML4Address->entries[indexer.getPDP()] = PDE;
    } 
    else PDP = (PageTable*) ((uint64_t) PDE.Address << 12);

    PDE = PDP->entries[indexer.getPD()];
    PageTable* PD;
    if(!PDE.Present) { 
        PD = (PageTable*) pageFrameAloc.RequestPage();
        memoryset(PD, 0, 0x1000);
        PDE.Address = (uint64_t) PD >> 12;
        PDE.Present = true;
        PDE.RW = true;
        PDP->entries[indexer.getPD()] = PDE;
    } else PD = (PageTable*) ((uint64_t) PDE.Address << 12);

    PDE = PDP->entries[indexer.getPT()];
    PageTable* PT;
    if(!PDE.Present) { 
        PT = (PageTable*) pageFrameAloc.RequestPage();
        memoryset(PT, 0, 0x1000);
        PDE.Address = (uint64_t) PT >> 12;
        PDE.Present = true;
        PD->entries[indexer.getPT()] = PDE;
    } else PT = (PageTable*) ((uint64_t) PDE.Address << 12);

    PDE = PT->entries[indexer.getP()];
    PDE.Address = (uint64_t) pmem >> 12;
    PDE.Present = true;
    PDE.RW = true;
    PT->entries[indexer.getP()] = PDE;
}