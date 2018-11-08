#ifndef LLVM_BRAINSTRUCTIONVISITOR_H
#define LLVM_BRAINSTRUCTIONVISITOR_H

#include <llvm/IR/InstVisitor.h>
#include <llvm/IR/BasicBlock.h>
#include "common/State.h"
#include "util.h"

using namespace llvm;

namespace bra {
    struct InstructionVisitor : public InstVisitor<InstructionVisitor> {
        State state;
        // TODO add field to keep least upper bound of predecessor Domain
        // EqualityDomain startDomain;
        void visit(BasicBlock &bb);
        State getState() const;
        void setStartDomain(/*EqualityDomain domain*/);
    };
}

#endif //LLVM_BRAINSTRUCTIONVISITOR_H
