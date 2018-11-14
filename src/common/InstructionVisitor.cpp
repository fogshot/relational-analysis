#include <string>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Value.h>
#include <sstream>
#include "InstructionVisitor.h"

using namespace llvm;
using namespace bra;

std::shared_ptr<State> InstructionVisitor::getState() {
    return state;
}

InstructionVisitor::InstructionVisitor(std::shared_ptr<AbstractDomain> startDomain,
                                       std::shared_ptr<State> state) : state(std::move(state)),
                                                                       startDomain(std::move(startDomain)),
                                                                       tempVarCounter(0),
                                                                       valueMap(
                                                                               std::map<Value *, std::shared_ptr<Variable>>()) {}

void InstructionVisitor::visit(BasicBlock &bb) {
    DEBUG_OUTPUT(std::string(GREEN)
                         +"Visiting \"" + bb.getName().str() + "\"" + std::string(NO_COLOR));
    globalDebugOutputTabLevel++;
    InstVisitor::visit(bb);
    globalDebugOutputTabLevel--;
}

void InstructionVisitor::visit(Instruction &inst) {
    // TODO: debug output that should be removed (just to have some sort of indication for missing instruction visit hooks)
//    DEBUG_OUTPUT(std::string(YELLOW)
//                         +"inst(" + std::string(inst.getOpcodeName()) + ")" + std::string(NO_COLOR));

    // Discover any previously unknown temporary Variables
    if (inst.getValueID() == 54) {
        if (valueMap.find(&inst) == valueMap.end()) {
            // Does not yet exist
            valueMap.insert({&inst, std::make_shared<Variable>(std::to_string(tempVarCounter++))});
        }
    }

    // Actually visit instruction
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
    std::string result;

    if (instName != "") {
        result = "%" + instName + " = ";
    } else {
        auto itP = valueMap.find(&inst);
        if (itP != valueMap.end()) {
            result = "%" + itP->second->getName() + " = ";
        }
    }
    result += std::string(inst.getOpcodeName());

    for (auto it = inst.op_begin(); it != inst.op_end(); it++) {
        std::string operatorRep = "";
        if (ConstantInt::classof(it->get())) {
            operatorRep = "'" + std::to_string(reinterpret_cast<ConstantInt *>(it->get())->getSExtValue()) + "'";
        } else {
            std::string operatorName = it->get()->getName().str();
            if (operatorName != "") {
                operatorRep = "%" + operatorName;
            } else {
                auto itP = valueMap.find(it->get());
                if (itP != valueMap.end()) {
                    operatorRep = "%" + itP->second->getName();
                } else {
                    std::stringstream ss;
                    ss << it->get();
                    std::string name = ss.str();
                    operatorRep = "{" + std::to_string(it->get()->getValueID()) + ", " + name + "}";
                }
            }
        }


        result += " " + operatorRep;
    }

    return result;
}