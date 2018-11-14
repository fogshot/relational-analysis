//
// Created by vanessa on 11/7/18.
//

#ifndef EQUALITYDOMAIN_H
#define EQUALITYDOMAIN_H

#include <iostream>
#include <unordered_map>
#include <set>
#include <memory>
#include "../common/AbstractDomain.h"
#include "../common/Representative.h"
#include "../common/Variable.h"
#include "../common/Constant.h"
#include "../common/RepresentativeHasher.h"
#include "../common/Compare.h"

namespace bra {
    class EqualityDomain : public AbstractDomain {
    public:
        EqualityDomain();
        ~EqualityDomain();

        friend std::ostream &operator<<(std::ostream &, const EqualityDomain &);

        std::string toString() const override;

        std::shared_ptr<AbstractDomain> leastUpperBound(std::vector<std::shared_ptr<AbstractDomain>> domains) override;

        std::shared_ptr<AbstractDomain> bottom() override;

        //protected:
        //assignment transforms
        void transformUnkownAssignment(const std::shared_ptr<Variable>);

        void transformConstantAssignment(const std::shared_ptr<Variable>, const std::shared_ptr<Constant>);

        void transformVariableAssignment(const std::shared_ptr<Variable>, const std::shared_ptr<Variable>);

    private:
        std::unordered_map<std::shared_ptr<Representative>,
                std::shared_ptr<std::set<std::shared_ptr<Variable>, bra::Compare>>,
                std::hash<std::shared_ptr<Representative>>> forwardMap;
        std::unordered_map<std::shared_ptr<Variable>, std::shared_ptr<Representative>, std::hash<std::shared_ptr<Variable>>> backwardMap;

        void insertConstantIntoForwardMap(const std::shared_ptr<Representative>, const std::shared_ptr<Variable>);
        void insertConstantIntoBackwardMap(const std::shared_ptr<Representative>, const std::shared_ptr<Variable>);
        void insertVariableIntoMaps(const std::shared_ptr<Variable>, const std::shared_ptr<Variable>);

        void addConstantAssignmentToEquivalenceClass(const std::shared_ptr<Representative>, const std::shared_ptr<Variable>);
        void addVariableAssignmentToEquivalenceClass(const std::shared_ptr<Variable>, const std::shared_ptr<Variable>);

        void removeTemporaryVariablesfromEquivalenceClass();
        void removeVariableFromEquivalenceClass(const std::shared_ptr<Variable>);
    };

}

#endif //EQUALITYDOMAIN_H
