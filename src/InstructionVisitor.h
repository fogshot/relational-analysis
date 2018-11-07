//
// Created by Dominik Horn on 07.11.18.
//

#ifndef LLVM_BRAINSTRUCTIONVISITOR_H
#define LLVM_BRAINSTRUCTIONVISITOR_H

#include <llvm/IR/InstVisitor.h>
#include <llvm/IR/BasicBlock.h>
#include "common/State.h"

using namespace llvm;

namespace basic_relational_abstractions {

    class InstructionVisitor : public InstVisitor<InstructionVisitor, void> {

    private:
        /// State map is used to keep track of states for each basic block
        /// TODO: rename
        std::map<BasicBlock, State> stateMap;
    };

}

#endif //LLVM_BRAINSTRUCTIONVISITOR_H
