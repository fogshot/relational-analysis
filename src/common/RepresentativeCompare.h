//
// Created by vanessa on 11/16/18.
//

#include <memory>
#include "ClassType.h"

#ifndef LLVM_REPRESENTATIVECOMPARE_H
#define LLVM_REPRESENTATIVECOMPARE_H

namespace bra{

    struct RepresentativeCompare{
        inline bool operator()(const std::shared_ptr<Representative> lhs, const std::shared_ptr<Representative> rhs) const {
            auto lType = lhs->getClassType();
            auto rType = rhs->getClassType();

            // Same type, order by attribute.
            if (lType == rType) {
                if (lType == ClassType::Variable) {
                    const std::shared_ptr<Variable> lhsCast = std::static_pointer_cast<Variable>(lhs);
                    const std::shared_ptr<Variable> rhsCast = std::static_pointer_cast<Variable>(rhs);
                    return lhsCast->getName() < rhsCast->getName();
                }
                if (lType == ClassType::Constant) {
                    const std::shared_ptr<Constant> lhsCast = std::static_pointer_cast<Constant>(lhs);
                    const std::shared_ptr<Constant> rhsCast = std::static_pointer_cast<Constant>(rhs);
                    return lhsCast->getValue() < rhsCast->getValue();
                }
            }
            // Different type, order Constant first
            return lType == ClassType::Constant;
        }
    };

}



#endif //LLVM_REPRESENTATIVECOMPARE_H
