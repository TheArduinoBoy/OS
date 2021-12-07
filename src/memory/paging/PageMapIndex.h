#pragma once

#include <stdint.h>

class PageMapIndex {
    public:
        PageMapIndex(uint64_t virtualAddress);
        uint64_t getPDP() { return PDP_i; }
        uint64_t getPD () { return PD_i;  }
        uint64_t getPT () { return PT_i;  }
        uint64_t getP  () { return P_i;   }
    private:
        uint64_t PDP_i;
        uint64_t PD_i ;
        uint64_t PT_i ;
        uint64_t P_i  ;
};