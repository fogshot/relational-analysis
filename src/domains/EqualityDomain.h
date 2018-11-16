//
// Created by vanessa on 11/7/18.
//

#ifndef EQUALITYDOMAIN_H
#define EQUALITYDOMAIN_H

#include <iostream>
#include <unordered_map>
#include <set>
#include <memory>
#include <map>
#include "../common/AbstractDomain.h"
#include "../common/Representative.h"
#include "../common/Variable.h"
#include "../common/Constant.h"
#include "../common/Invariant.h"
#include "../common/RepresentativeHasher.h"
#include "../common/RepresentativeCompare.h"

namespace bra {
    class EqualityDomain : public AbstractDomain {
    public:
        std::string toString() const override;

        std::string listInvariants() const override;

        std::shared_ptr<AbstractDomain> leastUpperBound(std::vector<std::shared_ptr<AbstractDomain>> domains) override;

        std::shared_ptr<AbstractDomain> bottom() override;

        /// Implementation of AbstractDomain virtual functions
        bool transform_add(std::shared_ptr<Variable> destination, std::shared_ptr<Representative> arg1,
                           std::shared_ptr<Representative> arg2) override;

        bool transform_store(std::shared_ptr<Variable> destination, std::shared_ptr<Representative> arg1) override;

        bool transform_load(std::shared_ptr<Variable> destination, std::shared_ptr<Representative> arg1) override;

        /// Friend helper for stream output
        friend std::ostream &operator<<(std::ostream &, const EqualityDomain &);

        // TODO:
        //protected:
        bool transformUnkownAssignment(std::shared_ptr<Variable>);

        bool transformConstantAssignment(std::shared_ptr<Variable>, std::shared_ptr<Constant>);

        bool transformVariableAssignment(std::shared_ptr<Variable>, std::shared_ptr<Variable>);


    private:
        std::unordered_map<std::shared_ptr<Representative>,
                std::shared_ptr<std::set<std::shared_ptr<Variable>, RepresentativeCompare>>,
                std::hash<std::shared_ptr<Representative>>> forwardMap;

        std::map<std::shared_ptr<Variable>, std::shared_ptr<Representative>, RepresentativeCompare> backwardMap;

        bool insertConstantIntoForwardMap(std::shared_ptr<Representative>, std::shared_ptr<Variable>);

        bool insertConstantIntoBackwardMap(std::shared_ptr<Representative>, std::shared_ptr<Variable>);

        bool insertVariableIntoMaps(std::shared_ptr<Variable>, std::shared_ptr<Variable>);

        bool
        addConstantAssignmentToEquivalenceClass(std::shared_ptr<Representative>, std::shared_ptr<Variable>);

        bool addVariableAssignmentToEquivalenceClass(std::shared_ptr<Variable>, std::shared_ptr<Variable>);

        // TODO decide what to do about this (for now) dead code
        void removeTemporaryVariablesfromEquivalenceClass();

        void removeVariableFromEquivalenceClass(std::shared_ptr<Variable>);

        /// Helper
        std::shared_ptr<Constant> getConstantIfResolvable(std::shared_ptr<Representative>) const;
    };

}

#endif //EQUALITYDOMAIN_H
