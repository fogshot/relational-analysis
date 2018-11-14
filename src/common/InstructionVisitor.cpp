#include <string>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Value.h>
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
    DEBUG_OUTPUT(std::string(GREEN)
                         +"Visiting \"" + bb.getName() + "\"" + std::string(NO_COLOR));
    globalDebugOutputTabLevel++;
    InstVisitor::visit(bb);
    globalDebugOutputTabLevel--;
}

void InstructionVisitor::visit(Instruction &inst) {
    // TODO: debug output that should be removed (just to have some sort of indication for missing instruction visit hooks)
    DEBUG_OUTPUT(std::string(YELLOW)
                         +"inst(" + std::string(inst.getOpcodeName()) + ")" + std::string(NO_COLOR));

    globalDebugOutputTabLevel++;
    InstVisitor::visit(inst);
    globalDebugOutputTabLevel--;
}

void InstructionVisitor::visitAdd(BinaryOperator &inst) {
    DEBUG_OUTPUT(std::string(GREEN)
                         +instToString(inst)
                         + std::string(NO_COLOR));
}

void InstructionVisitor::visitAllocaInst(AllocaInst &inst) {
    DEBUG_OUTPUT(std::string(GREEN)
                         +instToString(inst)
                         + std::string(NO_COLOR));
}

void InstructionVisitor::visitStoreInst(StoreInst &inst) {
    DEBUG_OUTPUT(std::string(GREEN)
                         +instToString(inst)
                         + std::string(NO_COLOR));
}

void InstructionVisitor::visitLoadInst(LoadInst &inst) {
    DEBUG_OUTPUT(std::string(GREEN)
                         +instToString(inst)
                         + std::string(NO_COLOR));
}


void InstructionVisitor::visitReturnInst(ReturnInst &inst) {
    DEBUG_OUTPUT(std::string(GREEN)
                         +instToString(inst)
                         + std::string(NO_COLOR));
}

std::string InstructionVisitor::instToString(Instruction &inst) {
    // inst.getName() return variable name (if any)
    std::string instName = inst.getName().str();
    std::string result = (instName != "" ? "%"
                                           + instName
                                         :
                          "{"
                          + std::to_string(inst.getValueID())
                          + "}")
                         + " = "
                         + inst.getOpcodeName();
    for (auto it = inst.op_begin(); it != inst.op_end(); it++) {
        std::string operatorRep = "";
        if (ConstantInt::classof(it->get())) {
            operatorRep = "'" + std::to_string(reinterpret_cast<ConstantInt *>(it->get())->getSExtValue()) + "'";
        } else {
            std::string operatorName = it->get()->getName().str();
            if (operatorName != "") {
                operatorRep = "%" + operatorName;
            } else {
                operatorRep = "{" + std::to_string(it->get()->getValueID()) + "}";
//                for (auto valIt = it->getUser()->op_begin(); valIt != it->getUser()->op_end(); valIt++) {
//                    operatorRep += instToString(valIt->get());
//                }
            }
        }


        result += " " + operatorRep;
    }

    return result;
}