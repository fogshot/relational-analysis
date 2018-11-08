//
// Created by Peter-Benedikt von Niebelschütz on 08.11.18.
//

#ifndef LLVM_BLOCKMANAGER_H
#define LLVM_BLOCKMANAGER_H

#include "BbWorklist.h"

namespace bra {
    class BlockManager {
    private:
        bra::BbWorkList worklist;
    public:
        void analyse(Function &function);
    };
}


#endif //LLVM_BLOCKMANAGER_H
