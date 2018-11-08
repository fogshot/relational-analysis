#include <llvm/IR/BasicBlock.h>
#include "InstructionVisitor.h"

using namespace llvm;

void bra::InstructionVisitor::visit(BasicBlock &bb) {
    BasicBlock::InstListType &instructionList = bb.getInstList();
    BasicBlock::InstListType::iterator it;
    for (it = instructionList.begin(); it != instructionList.end(); ++it) {
        DEBUG_OUTPUT(it->getName().str());
    }
}

bra::State bra::InstructionVisitor::getState() const {
    return state;
}

void bra::InstructionVisitor::setStartDomain() {
    // TODO PNI: implement
}
