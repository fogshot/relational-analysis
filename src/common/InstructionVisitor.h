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

        /// Math operations
        void visitAdd(BinaryOperator &);

        void visitFadd(BinaryOperator &);

        void visitSub(BinaryOperator &);

        void visitFSub(BinaryOperator &);

        void visitMul(BinaryOperator &);

        void visitFMul(BinaryOperator &);

        void visitUDiv(BinaryOperator &);

        void visitSDiv(BinaryOperator &);

        void visitFDiv(BinaryOperator &);

        void visitURem(BinaryOperator &);

        void visitSRem(BinaryOperator &);

        void visitFRem(BinaryOperator &);

        /// Memory operations
        void visitStoreInst(StoreInst &);

        void visitLoadInst(LoadInst &);

        // TODO: implement all other Operators (see Instruction.def and already implemented ops for reference)
    private:
        // helps with naming of temporary variables
        int tempVarCounter;
        // This map helps identify temporary variables without name
        std::map<Value *, std::shared_ptr<Variable>> valueMap;

        std::string instToString(Instruction &);

        /// Helper functions for visitor interface impl
        std::shared_ptr<Variable> helperParseVariable(Value *);

        std::shared_ptr<Representative> helperParseOperand(Value *val);
    };
}

#endif //LLVM_BRAINSTRUCTIONVISITOR_H
