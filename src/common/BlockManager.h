//
// Created by Peter-Benedikt von Niebelschütz on 08.11.18.
//

#ifndef LLVM_BLOCKMANAGER_H
#define LLVM_BLOCKMANAGER_H

#include <map>
#include "BbWorklist.h"
#include "State.h"

namespace bra {
    class BlockManager {
    private:
        BbWorkList workList;
        std::map<std::shared_ptr<BasicBlock>, std::shared_ptr<State>> stateMap;
    public:
        void analyse(Function &function);
    };
}


#endif //LLVM_BLOCKMANAGER_H
