//
// Created by vanessa on 11/13/18.
//

#include <memory>
#include "../util.h"
#include "Variable.h"
#include "Constant.h"


#ifndef LLVM_COMPARE_H
#define LLVM_COMPARE_H

namespace bra {

    struct Compare {
        bool operator()(const std::shared_ptr<Variable> lVarPtr, const std::shared_ptr<Variable> rVarPtr){
            bool b = lVarPtr->getName() < rVarPtr->getName();
            DEBUG_OUTPUT("\n---COMPREARE VAR-VAR\n");
            DEBUG_OUTPUT(lVarPtr->getName() +" < "+ rVarPtr->getName() + " = " + std::to_string(b) + "\n");
            std::string sa = "ab";
            std::string sb = "bb";
            DEBUG_OUTPUT("b < a = " + std::to_string(sb < sa) + "\n");
            return b;
        }

        //methods below not needed now since we only want to compare variables
        bool operator()(const std::shared_ptr<Constant> lConstPtr, const std::shared_ptr<Constant> rConstPtr){
            return lConstPtr->getValue() < rConstPtr->getValue();
        }

        bool operator()(const std::shared_ptr<Variable> varPtr, const std::shared_ptr<Constant> constPtr){
            return false;
        }

        bool operator()(const std::shared_ptr<Constant> constPtr, const std::shared_ptr<Variable> varPtr){
            return true;
        }
    };

}

#endif //LLVM_COMPARE_H
