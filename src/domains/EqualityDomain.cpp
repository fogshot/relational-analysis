//
// Created by vanessa on 11/7/18.
//

#include <algorithm>
#include <utility>
#include <string>
#include <memory>
#include <iostream>
#include "../common/ClassType.h"
#include "EqualityDomain.h"
#include "../util.h"

namespace bra {
    //constructor and Destructor
    EqualityDomain::EqualityDomain() = default;

    EqualityDomain::~EqualityDomain() = default;

    //function definitions
    void EqualityDomain::transformUnkownAssignment(const std::shared_ptr<Variable> variable) {
        // Do nothing (Single static assignment)
    }

    void EqualityDomain::transformConstantAssignment(const std::shared_ptr<Variable> variable,
                                                     const std::shared_ptr<Constant> constant) {
        this->addConstantAssignmentToEquivalenceClass(constant, variable);

    }

    void EqualityDomain::transformVariableAssignment(const std::shared_ptr<Variable> variable,
                                                     const std::shared_ptr<Variable> assignedValue) {
        this->addVariableAssignmentToEquivalenceClass(assignedValue, variable);
    }

    void EqualityDomain::addConstantAssignmentToEquivalenceClass(const std::shared_ptr<Representative> eqRepr,
                                                                 const std::shared_ptr<Variable> var) {
        insertConstantIntoForwardMap(eqRepr, var);
        insertConstantIntoBackwardMap(eqRepr, var);
    }

    void EqualityDomain::addVariableAssignmentToEquivalenceClass(const std::shared_ptr<Variable> eqRepr,
                                                                 const std::shared_ptr<Variable> var) {
        insertVariableIntoMaps(eqRepr, var);
    }

    void EqualityDomain::insertConstantIntoForwardMap(const std::shared_ptr<Representative> eqRepr,
                                                      const std::shared_ptr<Variable> var) {
        auto itForward = forwardMap.find(eqRepr); //iterator for forwardMap
        std::shared_ptr<std::set<std::shared_ptr<Variable>, Compare>> eqClass; //shared_ptr on set (=equality class)

        if (itForward != forwardMap.end()) { //go through forwardMap if not empty
            eqClass = itForward->second; //get eq class
            eqClass->insert(var); // add variable to eq class
        } else { //eq class is empty
            std::set<std::shared_ptr<Variable>, Compare> newSet;
            newSet.insert(var);
            eqClass = std::make_shared<std::set<std::shared_ptr<Variable>, Compare>>(newSet);
            forwardMap.insert({eqRepr, eqClass}); //insert tuple to map
        }
    }

    void EqualityDomain::insertConstantIntoBackwardMap(const std::shared_ptr<Representative> eqRepr,
                                                       const std::shared_ptr<Variable> var) {
        auto itBackward = backwardMap.find(var);
        if (itBackward != backwardMap.end()) { //if variable is already in map -> overwrite value
            itBackward->second = eqRepr;
        } else { //otherwise add new pair
            backwardMap.insert({var, eqRepr});
        }
    }

    void EqualityDomain::insertVariableIntoMaps(const std::shared_ptr<Variable> eqReprVar,
                                                const std::shared_ptr<Variable> var) {

        std::shared_ptr<std::set<std::shared_ptr<Variable>, Compare>> eqClass;
        //eqReprVar = std::dynamic_pointer_cast<std::shared_ptr<Variable>> (eqRepr);
        //look for existing assignment in backwardMap
        auto itBackward = backwardMap.find(eqReprVar);

        if (itBackward != backwardMap.end()) { //if there is an existing entry -> look for representative in forwardMap
            auto newReprVar = itBackward->second;
            auto itForward = forwardMap.find(newReprVar);
            if (newReprVar->getClassType() == ClassType::Constant) { //Constant case
                addConstantAssignmentToEquivalenceClass(newReprVar, var); //treat like a constant
            } else {
                //insert into eq class in forwardMap
                eqClass = itForward->second;
                eqClass->insert(var);
                std::shared_ptr<Representative> newRepr = *eqClass->begin();
                forwardMap.erase(newRepr);
                forwardMap.insert({newRepr, eqClass});
                //insert into backwardMap
                //for(std::set<std::shared_ptr<Variable>, Compare>::iterator it = *eqClass->begin(); it != *eqClass->end(); it++){
                //    backwardMap.erase(it);
                //    backwardMap.insert({it,newRepr});
                //}
                for (auto it : *eqClass) {
                    backwardMap.erase(it);
                    backwardMap.insert({it, newRepr});
                }
            }
        } else {//no entry yet -> only insert the variables
            std::set<std::shared_ptr<Variable>, Compare> newSet;
            newSet.insert(var);
            newSet.insert(eqReprVar);
            std::shared_ptr<Representative> key = std::shared_ptr<Representative>(*newSet.begin());
            auto eqClass = std::make_shared<std::set<std::shared_ptr<Variable>, Compare>>(newSet);
            forwardMap.insert({key, eqClass}); //insert tuple to map
        }
    }

    void EqualityDomain::removeVariableFromEquivalenceClass(const std::shared_ptr<Representative> eqRepr,
                                                            const std::shared_ptr<Variable> variable) {
        std::shared_ptr<std::set<std::shared_ptr<Variable>, Compare>> eqClass = forwardMap.find(eqRepr)->second;
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
        stream << dom.toString();
        return stream;
    }

    std::string EqualityDomain::toString() const {
        std::string ret = "EqualityDomain (\n\tforwardMap {";
        for (auto tmp = this->forwardMap.begin(); tmp != this->forwardMap.end(); tmp++) {
            ret += "(" + (tmp->first->toString()) + ": {";
            for (auto var = tmp->second->begin(); var != tmp->second->end(); var++) {
                ret += (*var)->toString();
                if (std::next(var) != tmp->second->end()) {
                    ret += ", ";
                }
            }
            ret += "})";
            if (std::next(tmp) != this->forwardMap.end()) {
                ret += ", ";
            }
        }
        ret += "}\n  -> backwardMap {";
        for (auto pairIt = this->backwardMap.begin(); pairIt != this->backwardMap.end(); pairIt++) {
            ret += "(" + pairIt->first->toString() + ", " + pairIt->second->toString() + ")";
            if (std::next(pairIt) != this->backwardMap.end()) {
                ret += ", ";
            }
        }
        return ret + "}";
    }

    std::shared_ptr<AbstractDomain> EqualityDomain::bottom() {
        return std::make_shared<EqualityDomain>();
    }

    std::shared_ptr<AbstractDomain>
    EqualityDomain::leastUpperBound(std::vector<std::shared_ptr<AbstractDomain>> domains) {
        // TODO implement for real
        return std::make_shared<EqualityDomain>();
    }
}