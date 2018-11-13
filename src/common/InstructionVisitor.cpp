#include <string>
#include <llvm/IR/BasicBlock.h>
#include "InstructionVisitor.h"

using namespace llvm;
using namespace bra;

std::shared_ptr<State> InstructionVisitor::getState() {
    return state;
}

InstructionVisitor::InstructionVisitor(std::shared_ptr<AbstractDomain> startDomain,
        std::shared_ptr<State> state) : state(std::move(state)), startDomain(std::move(startDomain)) {}

void InstructionVisitor::visit(Instruction &inst) {
    InstVisitor::visit(inst);
    DEBUG_OUTPUT("   " + inst.getName().str());
}

void InstructionVisitor::visit(BasicBlock &bb) {
    InstVisitor::visit(bb);
}
