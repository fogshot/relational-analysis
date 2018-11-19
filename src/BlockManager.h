//
// Created by Peter-Benedikt von Niebelschütz on 08.11.18.
//

#ifndef LLVM_BLOCKMANAGER_H
#define LLVM_BLOCKMANAGER_H

#include <map>
#include "src/common/BbWorklist.h"
#include "src/common/State.h"
#include "src/common/BbSorter.h"

namespace bra {
    class BlockManager {
    public:
        void analyse(Function &function);

    private:
        BbWorkList workList;
        std::map<BasicBlock *, std::shared_ptr<State>, BbSorter> stateMap;
    };
}


#endif //LLVM_BLOCKMANAGER_H