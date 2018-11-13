//
// Created by vanessa on 11/13/18.
//

#include <memory>
#include "Variable.h"
#include "Constant.h"


#ifndef LLVM_COMPARE_H
#define LLVM_COMPARE_H

namespace bra {

    struct Compare {
        bool operator()(const std::shared_ptr<Variable> &lVarPtr, const std::shared_ptr<Variable> &rVarPtr){
            return lVarPtr->getName() < rVarPtr->getName();
        }

        //methods below not needed now
        bool operator()(const std::shared_ptr<Constant> &lConstPtr, const std::shared_ptr<Constant> &rConstPtr){
            return lConstPtr->getValue() < rConstPtr->getValue();
        }

        bool operator()(const std::shared_ptr<Variable> &varPtr, const std::shared_ptr<Constant> &constPtr){
            return false;
        }

        bool operator()(const std::shared_ptr<Constant> &constPtr, const std::shared_ptr<Variable> &varPtr){
            return true;
        }
    };

}

#endif //LLVM_COMPARE_H
