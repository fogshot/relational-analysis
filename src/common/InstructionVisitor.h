#ifndef LLVM_BRAINSTRUCTIONVISITOR_H
#define LLVM_BRAINSTRUCTIONVISITOR_H

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

        /// Binary Operators
        void visitAdd(BinaryOperator &I);

        void visitSub(BinaryOperator &I);

//        void visitMul(BinaryOperator &I);
//
//        void visitURem(BinaryOperator &I);
//
//        void visitSRem(BinaryOperator &I);
//
//        void visitUDiv(BinaryOperator &I);
//
//        void visitSDiv(BinaryOperator &I);
//
//        void visitAnd(BinaryOperator &I);
//
//        void visitOr(BinaryOperator &I);
//
//        void visitXor(BinaryOperator &I);
//
//        void visitShl(Instruction &I);
//
//        void visitLShr(Instruction &I);
//
//        void visitAShr(Instruction &I);
    };
}

#endif //LLVM_BRAINSTRUCTIONVISITOR_H
