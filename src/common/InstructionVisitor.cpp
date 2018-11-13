#include <string>
#include <llvm/IR/BasicBlock.h>
#include "InstructionVisitor.h"

using namespace llvm;
using namespace bra;

std::shared_ptr<State> InstructionVisitor::getState() {
    return state;
}

InstructionVisitor::InstructionVisitor(std::shared_ptr<AbstractDomain> startDomain,
                                       std::shared_ptr<State> state) : state(std::move(state)),
                                                                       startDomain(std::move(startDomain)) {}

void InstructionVisitor::visit(BasicBlock &bb) {
    DEBUG_OUTPUT(std::string(YELLOW)
                         +"Visiting \"" + bb.getName() + "\"" + std::string(NO_COLOR));
    globalDebugOutputTabLevel++;
    InstVisitor::visit(bb);
    globalDebugOutputTabLevel--;
}

void InstructionVisitor::visit(Instruction &inst) {
    DEBUG_OUTPUT("inst(" + std::string(inst.getOpcodeName()) + ")");
    globalDebugOutputTabLevel++;
    InstVisitor::visit(inst);
    globalDebugOutputTabLevel--;
}

void InstructionVisitor::visitAdd(BinaryOperator &inst) {
    DEBUG_OUTPUT(std::string(GREEN)
                         +inst.getName() + std::string(NO_COLOR));
}

void InstructionVisitor::visitSub(BinaryOperator &inst) {
}