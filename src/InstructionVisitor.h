#ifndef LLVM_BRAINSTRUCTIONVISITOR_H
#define LLVM_BRAINSTRUCTIONVISITOR_H

#include <llvm/IR/InstVisitor.h>
#include <llvm/IR/BasicBlock.h>
#include "common/State.h"
#include "util.h"

using namespace llvm;

namespace bra {
    struct InstructionVisitor : public InstVisitor<InstructionVisitor> {
        /// State map is used to keep track of states for each basic block
        /// TODO: rename
        std::map<BasicBlock, State> stateMap;
        void visit(BasicBlock &bb);
    };
}

#endif //LLVM_BRAINSTRUCTIONVISITOR_H
