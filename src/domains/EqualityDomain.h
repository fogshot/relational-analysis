//
// Created by vanessa on 11/7/18.
//

#ifndef EQUALITYDOMAIN_H
#define EQUALITYDOMAIN_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "../common/AbstractDomain.h"
#include "../common/Representative.h"
#include "../common/Variable.h"
#include "../common/Constant.h"
#include "../common/RepresentativeHasher.h"

namespace bra {
    class EqualityDomain : public AbstractDomain {
    public:
        EqualityDomain();

        friend std::ostream &operator<<(std::ostream &, const EqualityDomain &);

        void add() override;

        void move() override;

        std::shared_ptr<AbstractDomain> leastUpperBound(std::vector<std::shared_ptr<AbstractDomain>> domains) override;

        std::shared_ptr<AbstractDomain> bottom() override;

    //protected:
        //assignment transforms
        void transformUnkownAssignment(const std::shared_ptr<Variable>);

        void transformConstantAssignment(const std::shared_ptr<Variable>, const std::shared_ptr<Constant>);

        void transformVariableAssignment(const std::shared_ptr<Variable>, const std::shared_ptr<Variable>);

    private:
        std::unordered_map<std::shared_ptr<Representative>,
                std::shared_ptr<std::unordered_set<std::shared_ptr<Variable>>>,
                std::hash<std::shared_ptr<Representative>>> forwardMap;
        std::unordered_map<std::shared_ptr<Variable>, std::shared_ptr<Representative>, std::hash<std::shared_ptr<Variable>>> backwardMap;

        void addVariableToEquivalenceClass(const std::shared_ptr<Representative>, const std::shared_ptr<Variable>);

        void removeVariableFromEquivalenceClass(const std::shared_ptr<Representative>,
                                                const std::shared_ptr<Variable>);
    };

}

#endif //EQUALITYDOMAIN_H
