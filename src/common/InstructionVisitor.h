#ifndef LLVM_BRAINSTRUCTIONVISITOR_H
#define LLVM_BRAINSTRUCTIONVISITOR_H

#include <llvm/IR/Instruction.h>
#include <llvm/IR/InstVisitor.h>
#include <llvm/IR/BasicBlock.h>
#include "State.h"
#include "src/util.h"
#include "src/domains/EqualityDomain.h"

using namespace llvm;

namespace bra {
    struct InstructionVisitor : public InstVisitor<InstructionVisitor> {
        std::shared_ptr<State> state;
        std::shared_ptr<AbstractDomain> startDomain;

        void visit(BasicBlock &bb);
        void visit(Instruction &inst);

        InstructionVisitor(std::shared_ptr<AbstractDomain> startDomain, std::shared_ptr<State> state);

        std::shared_ptr<State> getState();

        // TODO: implement all Operators
        void visitAllocaInst(AllocaInst &);
        void visitStoreInst(StoreInst &);
        void visitLoadInst(LoadInst &);
        void visitAdd(BinaryOperator &);

        void visitReturnInst(ReturnInst &);

    private:
        // helps with naming of temporary variables
        static int tempVarCounter;
        // This map helps identify temporary variables without name
        std::map<Value*, std::shared_ptr<Variable>> valueMap;
        std::string instToString(Instruction &);
    };
}

#endif //LLVM_BRAINSTRUCTIONVISITOR_H
