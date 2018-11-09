#ifndef LLVM_BRAINSTRUCTIONVISITOR_H
#define LLVM_BRAINSTRUCTIONVISITOR_H

#include <llvm/IR/InstVisitor.h>
#include <llvm/IR/BasicBlock.h>
#include "common/State.h"
#include "util.h"
#include "domains/EqualityDomain.h"

using namespace llvm;

namespace bra {
    struct InstructionVisitor : public InstVisitor<InstructionVisitor> {
        std::shared_ptr<State> state;
        // TODO add field to keep least upper bound of predecessor Domain
        std::shared_ptr<AbstractDomain> startDomain;
        void visit(BasicBlock &bb);

        InstructionVisitor(std::shared_ptr<AbstractDomain> startDomain, std::shared_ptr<State> state);

        std::shared_ptr<State> getState();
    };
}

#endif //LLVM_BRAINSTRUCTIONVISITOR_H
