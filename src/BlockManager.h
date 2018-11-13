//
// Created by Peter-Benedikt von Niebelschütz on 08.11.18.
//

#ifndef LLVM_BLOCKMANAGER_H
#define LLVM_BLOCKMANAGER_H

#include <map>
#include "BbWorklist.h"
#include "common/State.h"

namespace bra {
    class BlockManager {
    private:
        bra::BbWorkList workList;
        std::map<BasicBlock *, std::shared_ptr<State>> stateMap;
    public:
        void analyse(Function &function);
    };
}


#endif //LLVM_BLOCKMANAGER_H
