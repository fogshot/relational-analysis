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

InstructionVisitor::InstructionVisitor(std::vector<std::shared_ptr<AbstractDomain>> startDomains,
                                       std::shared_ptr<State> state) : state(state), startDomains(startDomains) {}

void InstructionVisitor::visit(BasicBlock &bb) {
    DEBUG_OUTPUT(std::string(PURPLE)
                         +"Visiting \"" + bb.getName().str() + "\":");
    DEBUG_OUTPUT("State: " + state->toString());
    DEBUG_OUTPUT("Start Domains:");
    for (auto dom : startDomains) {
        DEBUG_OUTPUT(std::string(PURPLE)
                             +"  " + dom->toString() + std::string(NO_COLOR));
    }

    globalDebugOutputTabLevel++;
    state->willVisit();
    InstVisitor::visit(bb);
    globalDebugOutputTabLevel--;

    // TODO implement update thingy!!!


    DEBUG_OUTPUT(std::string(GREEN)
                         +"State after: " + state->toString() + std::string(NO_COLOR));
}

std::map<Value *, std::shared_ptr<Variable>> InstructionVisitor::valueMap;

void InstructionVisitor::visit(Instruction &inst) {
    DEBUG_OUTPUT(instToString(inst));
    static int tempVarCounter = 0;

    // Discover any previously unknown temporary Variables
    if (inst.getValueID() == TEMPORARY_VAR_ID) {
        if (valueMap.find(&inst) == valueMap.end()) {
            // Does not yet exist
            valueMap.insert({&inst, std::make_shared<Variable>("%" + std::to_string(tempVarCounter++), true)});
        }
    }

    // Actually visit instruction
    globalDebugOutputTabLevel++;
    InstVisitor::visit(inst);
//    DEBUG_OUTPUT(std::string(YELLOW) + state->toString() + std::string(NO_COLOR));
    for (auto dom : startDomains) {
        DEBUG_OUTPUT(std::string(GREEN)
                             +"  " + dom->toString() + std::string(NO_COLOR));
    }
    globalDebugOutputTabLevel--;
}

std::shared_ptr<Representative> InstructionVisitor::helperParseOperand(Value *val) {
    if (ConstantInt::classof(val)) {
        int value = reinterpret_cast<ConstantInt *>(val)->getSExtValue();
        return std::make_shared<Constant>(value);
    }

    return helperParseVariable(val);
}

std::shared_ptr<Variable> InstructionVisitor::helperParseVariable(Value *val) {
    std::shared_ptr<Variable> result;

    if (val->getValueID() == TEMPORARY_VAR_ID) {
        auto itP = valueMap.find(val);
        if (itP != valueMap.end()) {
            result = itP->second;
        } else {
            DEBUG_ERR("VISIT ADD ENCOUNTERED TEMPORARY VARIABLE NOT IN VALUEMAP!!!");
        }
    } else {
        result = std::make_shared<Variable>(val->getName());
    }

    return result;
}

void InstructionVisitor::visitAdd(BinaryOperator &inst) {
    std::shared_ptr<Variable> destination = helperParseVariable(&inst);
    std::shared_ptr<Representative> arg1 = helperParseOperand(inst.getOperand(0));
    std::shared_ptr<Representative> arg2 = helperParseOperand(inst.getOperand(1));

    // TODO generify this code since its the same for all visit* impls
    for (auto domIt = startDomains.begin(); domIt < startDomains.end(); domIt++) {
        domIt->get()->transform_add(destination, arg1, arg2);
    }
}


void InstructionVisitor::visitStoreInst(StoreInst &inst) {
    std::shared_ptr<Variable> destination = helperParseVariable(inst.getOperand(1));
    std::shared_ptr<Representative> arg1 = helperParseOperand(inst.getOperand(0));

    // TODO generify this code since its the same for all visit* impls
    for (auto domIt = startDomains.begin(); domIt < startDomains.end(); domIt++) {
        domIt->get()->transform_store(destination, arg1);
    }
}

void InstructionVisitor::visitLoadInst(LoadInst &inst) {
    std::shared_ptr<Variable> destination = helperParseVariable(&inst);
    std::shared_ptr<Representative> arg1 = helperParseOperand(inst.getOperand(0));

    // TODO generify this code since its the same for all visit* impls
    for (auto domIt = startDomains.begin(); domIt < startDomains.end(); domIt++) {
        domIt->get()->transform_load(destination, arg1);
    }
}

void InstructionVisitor::visitAllocaInst(AllocaInst &inst) {
    DEBUG_OUTPUT(std::string(GREEN)
                         +"UNIMPLEMENTED "
                         + std::string(NO_COLOR));
}

void InstructionVisitor::visitReturnInst(ReturnInst &inst) {
    DEBUG_OUTPUT(std::string(GREEN)
                         +"UNIMPLEMENTED "
                         + std::string(NO_COLOR));
}

std::string InstructionVisitor::instToString(Instruction &inst) {
    // inst.getName() return variable name (if any)
    std::string instName = inst.getName().str();
    std::string result;

    if (!instName.empty()) {
        result = "%" + instName + " = ";
    } else {
        auto itP = valueMap.find(&inst);
        if (itP != valueMap.end()) {
            result = "%" + itP->second->getName() + " = ";
        }
    }
    result += std::string(inst.getOpcodeName());

    for (auto it = inst.op_begin(); it != inst.op_end(); it++) {
        std::string operatorRep;
        if (ConstantInt::classof(it->get())) {
            operatorRep = "'" + std::to_string(reinterpret_cast<ConstantInt *>(it->get())->getSExtValue()) + "'";
        } else {
            std::string operatorName = it->get()->getName().str();
            if (!operatorName.empty()) {
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