//
// Created by Peter-Benedikt von Niebelschütz on 08.11.18.
//

#include "BlockManager.h"
#include "InstructionVisitor.h"

namespace bra {
    void bra::BlockManager::analyse(Function &function) {
        InstructionVisitor instructionVisitor;
        std::map<BasicBlock, State> stateMap;
        for (BasicBlock &bb : function) {
            // TODO replace list with worklist
            worklist.push(&bb);
        }
        while (!worklist.empty()) {
            // TODO PNI get least upper bound of predecessor domains
            // EqualityDomain domain;
            // domain.getLeastUpperBound();

            instructionVisitor.visit(*worklist.pop());
            State state = instructionVisitor.getState();
        }
    }
}

