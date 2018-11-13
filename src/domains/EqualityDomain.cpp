//
// Created by vanessa on 11/7/18.
//

#include <algorithm>
#include <utility>
#include <string>
#include "EqualityDomain.h"
#include "../util.h"

namespace bra {
    //constructor
    EqualityDomain::EqualityDomain() {}

    //function definitions
    void EqualityDomain::transformUnkownAssignment(const std::shared_ptr<Variable> variable) {
        // Do nothing (Single static assignment)
    };

    void EqualityDomain::transformConstantAssignment(const std::shared_ptr<Variable> variable,
                                                     const std::shared_ptr<Constant> constant) {
        this->addVariableToEquivalenceClass(constant, variable);
    }

    void EqualityDomain::transformVariableAssignment(const std::shared_ptr<Variable> variable,
                                                     const std::shared_ptr<Variable> assignedValue) {
        // TODO: implement
    }

    void EqualityDomain::addVariableToEquivalenceClass(const std::shared_ptr<Representative> eqRepr,
                                                       const std::shared_ptr<Variable> var) {
        auto itForward = forwardMap.find(eqRepr);
        std::shared_ptr<std::unordered_set<std::shared_ptr<Variable>>> eqClass;
        if (itForward != forwardMap.end()) {
            eqClass = itForward->second;
            eqClass->insert(var);
        } else {
            eqClass = std::shared_ptr<std::unordered_set<std::shared_ptr<Variable>>>(
                    new std::unordered_set<std::shared_ptr<Variable>>());
            eqClass->insert(var);
            forwardMap.insert({eqRepr, eqClass});
        }

        auto itBackward = backwardMap.find(var);
        if (itBackward != backwardMap.end()) {
            itBackward->second = eqRepr;
        } else {
            backwardMap.insert({var, eqRepr});
        }
    }

    void EqualityDomain::removeVariableFromEquivalenceClass(const std::shared_ptr<Representative> eqRepr,
                                                            const std::shared_ptr<Variable> variable) {
        std::shared_ptr<std::unordered_set<std::shared_ptr<Variable>>> eqClass = forwardMap.find(eqRepr)->second;
        eqClass->erase(std::find(eqClass->begin(), eqClass->end(), variable));
        if (eqClass->empty()) {
            forwardMap.erase(eqRepr);
        } else if (eqRepr == variable) {
            const std::shared_ptr<Variable> &repr = eqClass->begin().operator*();
            forwardMap.erase(eqRepr);
            forwardMap.insert({repr, eqClass});
            for (const std::shared_ptr<Variable> &eqMember : *eqClass) {
                auto it = backwardMap.find(eqMember);
                if (it != backwardMap.end()) {
                    // TODO:
                    it->second = repr;
                } else {
                    backwardMap.insert({eqMember, repr});
                }
            }
        }
    }

    std::ostream &operator<<(std::ostream &stream, const EqualityDomain &dom) {
        stream << "EQ: {";
        for (auto const &pair: dom.forwardMap) {
            stream << "(" << pair.first << ": {";

            std::unordered_set<std::__1::shared_ptr<bra::Variable>, std::hash<std::__1::shared_ptr<bra::Variable>>, std::__1::equal_to<std::__1::shared_ptr<bra::Variable>>, std::__1::allocator<std::__1::shared_ptr<bra::Variable>>>::iterator var;
            for (var = pair.second->begin(); var != pair.second->end(); var++) {
                stream << *var;

                if (std::next(var) != pair.second->end()) {
                    stream << ", ";
                }
            }

            stream << "}), ";
        }


        return stream << "}";
    }

    void EqualityDomain::add() {

    }

    void EqualityDomain::move() {

    }

    std::shared_ptr<AbstractDomain> EqualityDomain::bottom() {
        return std::shared_ptr<EqualityDomain>();
    }

    std::shared_ptr<AbstractDomain>
    EqualityDomain::leastUpperBound(std::vector<std::shared_ptr<AbstractDomain>> domains) {
        // TODO implement for real
        return std::shared_ptr<EqualityDomain>();
    }
}