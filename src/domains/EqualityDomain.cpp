#include <algorithm>
#include <utility>
#include <string>
#include <memory>
#include <iostream>
#include <tuple>
#include <sstream>
#include "../common/ClassType.h"
#include "EqualityDomain.h"
#include "../util.h"
#include "../common/RepresentativeCompare.h"

namespace bra {
    EqualityDomain::EqualityDomain() {}

    /// Implementation of visitor interface
    void EqualityDomain::transform_add(std::shared_ptr<Variable> destination, std::shared_ptr<Representative> arg1,
                                       std::shared_ptr<Representative> arg2) {
        /// Try whether or not we're lucky and have 2 constants being added
        if (arg1->getClassType() == ClassType::Constant && arg2->getClassType() == ClassType::Constant) {
            int result = ((Constant *) arg1.get())->getValue() + ((Constant *) arg2.get())->getValue();
            transformConstantAssignment(destination, std::make_shared<Constant>(result));
        } else {
            /// Try whether or not we can resolve both variables to constants. Otherwise this is a non trivial case
            std::shared_ptr<Constant> const1 = getConstantIfResolvable(arg1);
            std::shared_ptr<Constant> const2 = getConstantIfResolvable(arg2);

            if (const1 != nullptr && const2 != nullptr) {
                int result = const1->getValue() + const2->getValue();
                transformConstantAssignment(destination, std::make_shared<Constant>(result));
            } else {
                // TODO: implement non trivial av + b (if possible) -> unkown assignment for now
                transformUnkownAssignment(destination);
            }

        }
    }

    void EqualityDomain::transform_store(std::shared_ptr<Variable> destination, std::shared_ptr<Representative> arg1) {
        if (arg1->getClassType() == ClassType::Constant) {
            std::shared_ptr<Constant> con = std::static_pointer_cast<Constant>(arg1);
            transformConstantAssignment(destination, con);
        } else if (arg1->getClassType() == ClassType::Variable) {
            std::shared_ptr<Variable> var = std::static_pointer_cast<Variable>(arg1);
            transformVariableAssignment(destination, var);
        }
    }

    void EqualityDomain::transform_load(std::shared_ptr<Variable> destination, std::shared_ptr<Representative> arg1) {
        // Equal handeling as far as we are concerned
        transform_store(destination, arg1);
    }


    //function definitions
    void EqualityDomain::transformUnkownAssignment(const std::shared_ptr<Variable> variable) {
        // Do nothing (Single static assignment)
        DEBUG_OUTPUT(std::string(YELLOW)
                             +"[" + variable->toString() + " <- ?]#" + std::string(NO_COLOR));
    }

    void EqualityDomain::transformConstantAssignment(const std::shared_ptr<Variable> variable,
                                                     const std::shared_ptr<Constant> constant) {
        DEBUG_OUTPUT(std::string(YELLOW)
                             +"[" + variable->toString() + " <- '" + constant->toString() + "']#" +
                             std::string(NO_COLOR));
        this->addConstantAssignmentToEquivalenceClass(constant, variable);
    }

    void EqualityDomain::transformVariableAssignment(const std::shared_ptr<Variable> variable,
                                                     const std::shared_ptr<Variable> assignedValue) {
        DEBUG_OUTPUT(std::string(YELLOW)
                             +"[" + variable->toString() + " <- " + assignedValue->toString() + "]#" +
                             std::string(NO_COLOR));
        return this->addVariableAssignmentToEquivalenceClass(assignedValue, variable);
    }

    void EqualityDomain::addConstantAssignmentToEquivalenceClass(const std::shared_ptr<Representative> eqRepr,
                                                                 const std::shared_ptr<Variable> var) {
        removeVariableFromEquivalenceClass(var);
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
        std::shared_ptr<std::set<std::shared_ptr<Variable>, RepresentativeCompare>> eqClass; //shared_ptr on set (=equality class)

        if (itForward != forwardMap.end()) {
            // go through forwardMap if not empty
            eqClass = itForward->second; // get eq class
            auto varIt = eqClass->find(var);
            if (varIt == eqClass->end()) {
                eqClass->insert(var); // add variable to eq class
            }
        } else {
            // No EQ class found
            std::set<std::shared_ptr<Variable>, RepresentativeCompare> newSet;
            newSet.insert(var);
            eqClass = std::make_shared<std::set<std::shared_ptr<Variable>, RepresentativeCompare>>(newSet);
            forwardMap.insert({eqRepr, eqClass}); // insert tuple to map
        }
    }

    void EqualityDomain::insertConstantIntoBackwardMap(const std::shared_ptr<Representative> eqRepr,
                                                       const std::shared_ptr<Variable> var) {
        auto itBackward = backwardMap.find(var);
        if (itBackward != backwardMap.end()) {
            // if variable is already in map -> overwrite value
            const RepresentativeCompare c;
            if (!c.operator()(itBackward->second, eqRepr)) {
                itBackward->second = eqRepr;
            }
        } else {
            // otherwise add new pair
            backwardMap.insert({var, eqRepr});
        }
    }

    void EqualityDomain::insertVariableIntoMaps(const std::shared_ptr<Variable> var1,
                                                const std::shared_ptr<Variable> var2) {
        std::shared_ptr<std::set<std::shared_ptr<Variable>, RepresentativeCompare>> eqClass;

        // Find existing repr var if any
        auto itBackward = backwardMap.find(var1);
        auto itBackward2 = backwardMap.find(var2);
        std::shared_ptr<Representative> reprVar = nullptr;
        std::shared_ptr<Variable> varToAdd = nullptr;
        if (itBackward != backwardMap.end()) {
            reprVar = itBackward->second;
            varToAdd = var2;
        } else if (itBackward2 != backwardMap.end()) {
            // TODO: this is probably wrong (ask @vanessa)
            reprVar = itBackward2->second;
            varToAdd = var1;
        }

        if (reprVar != nullptr) {
            removeVariableFromEquivalenceClass(varToAdd);

            // if there is an existing entry -> look for representative in forwardMap to obtain eqClass
            auto itForward = forwardMap.find(reprVar);
            if (reprVar->getClassType() == ClassType::Constant) { // Constant case
                addConstantAssignmentToEquivalenceClass(reprVar, varToAdd); // treat like a constant
            } else {
                // Insert into eq class in forwardMap
                eqClass = itForward->second;

                auto varIt = eqClass->find(varToAdd);
                if (varIt == eqClass->end()) {
                    // simply insert
                    eqClass->insert(varToAdd);

                    // Update representative for equality class in both maps
                    std::shared_ptr<Representative> newRepr = *eqClass->begin();
                    forwardMap.erase(reprVar);
                    forwardMap.insert({newRepr, eqClass});
                    for (auto it : *eqClass) {
                        backwardMap.erase(it);
                        backwardMap.insert({it, newRepr});
                    }
                }
            }
        } else {
            // Insert new eqClass into forward map
            std::set<std::shared_ptr<Variable>, RepresentativeCompare> newSet;
            newSet.insert(var1);
            newSet.insert(var2);
            std::shared_ptr<Representative> newRepr = std::shared_ptr<Representative>(*newSet.begin());
            auto eqClass = std::make_shared<std::set<std::shared_ptr<Variable>, RepresentativeCompare>>(newSet);
            forwardMap.insert({newRepr, eqClass}); //insert tuple to map

            // Insert into backward map
            for (auto it : *eqClass) {
                backwardMap.insert({it, newRepr});
            }
        }
    }

    /// This is the purge() implementation. For now it is not invoked (debug purposes)
    void EqualityDomain::removeTemporaryVariablesfromEquivalenceClass() {
        Variable *varPtr;
        for (const auto &it : backwardMap) { //iterate through backwardMap
            if (it.first.get()->isTemporaryVariable()) { //if key is a temporary variable -> remove
                varPtr = it.first.get();
                std::shared_ptr<Variable> varShPtr(varPtr);
                removeVariableFromEquivalenceClass(varShPtr);
            }
        }
    }

    void EqualityDomain::removeVariableFromEquivalenceClass(const std::shared_ptr<Variable> var) {
        auto bwmIt = backwardMap.find(var);
        if (bwmIt == backwardMap.end())
            return;

        //look for representative and remove from backwardMap
        std::shared_ptr<Representative> eqRepr = bwmIt->second;
        backwardMap.erase(var);

        //erase from forwardMap
        std::shared_ptr<std::set<std::shared_ptr<Variable>, RepresentativeCompare>> eqClass = forwardMap.find(
                eqRepr)->second;//find respective eq class

        eqClass->erase(var);
        if (eqClass->empty()) {//if this was last element in set -> remove from map
            forwardMap.erase(eqRepr);
        } else if (eqRepr ==
                   var) { //if current repr is not in the eqClass anymore -> replace with first element in eqClass
            const std::shared_ptr<Variable> &repr = eqClass->begin().operator*();
            forwardMap.erase(eqRepr);
            forwardMap.insert({repr, eqClass});
            for (const std::shared_ptr<Variable> &eqMember : *eqClass) {
                auto it = backwardMap.find(eqMember);
                if (it != backwardMap.end()) {
                    it->second = repr;
                } else {
                    backwardMap.insert({eqMember, repr});
                }
            }
        }
    }

    /// Helper
    std::shared_ptr<Constant> EqualityDomain::getConstantIfResolvable(std::shared_ptr<Representative> rep) const {
        if (rep->getClassType() == ClassType::Variable) {
            // Try to resolve variable
            auto var = std::static_pointer_cast<Variable>(rep);

            // Search for variable in backwardMap:
            auto it = backwardMap.find(var);
            if (it != backwardMap.end()) {
                // Check if it->second is a constant. if it is, return that and else null_ptr
                if (it->second->getClassType() == ClassType::Constant) {
                    return std::static_pointer_cast<Constant>(it->second);
                }
            }
        } else if (rep->getClassType() == ClassType::Constant) {
            return std::static_pointer_cast<Constant>(rep);
        }

        // Otherwise we can't resolve to constant

        return nullptr;
    }

    /**
     * Return the set of Variables in this domain
     * @return a vector containing shared pointers to the variables in this domain
     */
    std::vector<std::shared_ptr<Variable>> EqualityDomain::getAllVariables() {
        std::vector<std::shared_ptr<Variable>> res;

        for (auto &it : backwardMap) {
            res.push_back(it.first);
        }

        return res;
    }

    /// Human readable output (f.e. DEBUG)
    std::ostream &operator<<(std::ostream &stream, const EqualityDomain &dom) {
        stream << dom.toString();
        return stream;
    }

    /**
     * Construct a string representation of this domain
     *
     * @return the string representing this domain
     */
    std::string EqualityDomain::toString() const {
        std::string ret = "{";
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

        // TODO remove this debug code
//        ret += "} <-> {";
//        for (auto pairIt = this->backwardMap.begin(); pairIt != this->backwardMap.end(); pairIt++) {
//            ret += "(" + pairIt->first->toString() + ", " + pairIt->second->toString() + ")";
//            if (std::next(pairIt) != this->backwardMap.end()) {
//                ret += ", ";
//            }
//        }
        return ret + "}";
    }

    /**
     * Return a domain representing the bottom lattice, i.e. a domain that contains no information on equalities
     *
     * @return the constructed domain
     */
    std::shared_ptr<AbstractDomain> EqualityDomain::bottom() {
        // TODO make this a static method somehow
        return std::make_shared<EqualityDomain>();
    }

    bool EqualityDomain::isBottom() {
        return backwardMap.size() == 0 && forwardMap.size() == 0;
    }

    ClassType EqualityDomain::getClassType() {
        return ClassType::EqualityDomain;
    }

    /**
     * copy a given AbstractDomain and return a reference to it. The given Domain will be cast to EqualityDomain first.
     * @param other an AbstractDomain to copy
     * @return a shared pointer to the copied domain
     */
    std::shared_ptr<AbstractDomain> EqualityDomain::copyEQ(std::shared_ptr<AbstractDomain> other) {
        // TODO
        // - does it make sense to copy an abstract domain here? The code below expects an equalitydomain
        // - this should be a static method
        // - does this method really need to return a shared_ptr?
        std::shared_ptr<EqualityDomain> dom = std::static_pointer_cast<EqualityDomain>(other);
        std::shared_ptr<EqualityDomain> copy = std::make_shared<EqualityDomain>();
        copy->backwardMap = dom->backwardMap;
        copy->forwardMap = dom->forwardMap;
        for (auto it = copy->forwardMap.begin(); it != copy->forwardMap.end(); it++) {
            /// Copy constructor
            std::shared_ptr<std::set<std::shared_ptr<Variable>, RepresentativeCompare>> cop = std::make_shared<std::set<std::shared_ptr<Variable>, RepresentativeCompare>>();
            for (auto varp : *it->second) {
                cop->insert(varp);
            }
            it->second = cop;
        }
        return std::static_pointer_cast<AbstractDomain>(copy);
    }

    /**
     * Construct the least upper bound w.r.t. the join operation for a given set of domains
     *
     * @param domains the domains to join
     * @return a domain representing the least upper bound of the input domains
     */
    std::shared_ptr<AbstractDomain>
    EqualityDomain::leastUpperBound(std::vector<std::shared_ptr<AbstractDomain>> domains) {
        // TODO make this a static method somehow
        if (domains.size() == 0) {
            return bottom();
        }

        // Use associativity
        // TODO: refactor into copyEQDom function -> copy constructor??
        std::shared_ptr<AbstractDomain> res = copyEQ(domains[0]);
        for (auto domIt = ++domains.begin(); domIt != domains.end(); domIt++) {
            res = leastUpperBound(res, *domIt);
        }

        return res;
    }

    /**
     * Construct the least upper bound w.r.t. the join operation for a given set of domains
     *
     * @param domains the domains to join
     * @return a domain representing the least upper bound of the input domains
     */
    std::shared_ptr<AbstractDomain>
    EqualityDomain::leastUpperBound(std::shared_ptr<AbstractDomain> d1, std::shared_ptr<AbstractDomain> d2) {
        // TODO refactor, this method is too complex
        // TODO make this a static method somehow
        if (d1->getClassType() != ClassType::EqualityDomain || d2->getClassType() != ClassType::EqualityDomain) {
            // TODO: probably should throw runtime error
            DEBUG_ERR("Can not calculate leastUpperBounds of non equality domains");
            return d1->bottom();
        }

        std::shared_ptr<EqualityDomain> dom1 = std::static_pointer_cast<EqualityDomain>(d1);
        std::shared_ptr<EqualityDomain> dom2 = std::static_pointer_cast<EqualityDomain>(d2);

        if (d1->isBottom()) return copyEQ(d2);
        if (d2->isBottom()) return copyEQ(d1);

        // Step 1: find all variables
        std::vector<std::shared_ptr<Variable>> variables1 = dom1->getAllVariables();
        std::vector<std::shared_ptr<Variable>> variables2 = dom2->getAllVariables();
        std::set<std::shared_ptr<Variable>> variables(variables1.begin(), variables1.end());
        variables.insert(variables2.begin(), variables2.end());

        // Step 2: find pairs (t1,t2) of eqClass representatives for each variable and group variables with matching pairs together
        std::map<std::tuple<std::shared_ptr<Representative>, std::shared_ptr<Representative>>, std::shared_ptr<std::set<std::shared_ptr<Variable>, RepresentativeCompare>>, RepresentativeCompare> t1t2Mapping;
        for (std::shared_ptr<Variable> var : variables) {
            auto t1It = dom1->backwardMap.find(var);
            auto t2It = dom2->backwardMap.find(var);

            std::shared_ptr<Representative> t1 =
                    t1It == dom1->backwardMap.end() ? std::static_pointer_cast<Representative>(var) : t1It->second;
            std::shared_ptr<Representative> t2 =
                    t2It == dom2->backwardMap.end() ? std::static_pointer_cast<Representative>(var) : t2It->second;

            std::tuple<std::shared_ptr<Representative>, std::shared_ptr<Representative>> tuple = std::make_tuple(t1,
                                                                                                                 t2);
            std::shared_ptr<std::set<std::shared_ptr<Variable>, RepresentativeCompare>> vars;
            auto varsIt = t1t2Mapping.find(tuple);
            if (varsIt == t1t2Mapping.end()) {
                vars = std::make_shared<std::set<std::shared_ptr<Variable>, RepresentativeCompare>>();
                t1t2Mapping.insert({tuple, vars});
            } else {
                vars = varsIt->second;
            }
            vars->insert(var);
        }

        // Step 3: filter tautology classes (t_5 = t_5)
        // NOTE: before continuing to read this code, buckle up, place your monitor out of punching range and
        // make sure to wear your eye protecting glasses: This code WILL cause suffering and pain
        // TODO: prettify/help ._.
        label:
        for (auto it : t1t2Mapping) {
            std::shared_ptr<Representative> t1 = std::get<0>(it.first);
            std::shared_ptr<Representative> t2 = std::get<1>(it.first);

            if (t1->getClassType() == ClassType::Constant && t2->getClassType() == ClassType::Constant) {
                std::shared_ptr<Constant> c1 = std::static_pointer_cast<Constant>(t1);
                std::shared_ptr<Constant> c2 = std::static_pointer_cast<Constant>(t2);

                if (c1->getValue() == c2->getValue())
                    continue;
            }

            if (it.second->size() == 1) {
                t1t2Mapping.erase(it.first);
                goto label;
            }
        }


        // Step 4: generate new Domain with equality classes from those pairs
        // TODO: use bottom() to generate new domain
        std::shared_ptr<EqualityDomain> resDom = std::make_shared<EqualityDomain>();
        for (auto it = t1t2Mapping.begin(); it != t1t2Mapping.end(); it++) {
            // Find representative (either both are the same constant, or a new repr has to be chosen)
            std::shared_ptr<std::set<std::shared_ptr<Variable>, RepresentativeCompare>> eqClass = it->second;
            std::shared_ptr<Representative> newRepr = chooseRepr(it->first, *eqClass);

            resDom->forwardMap.insert({newRepr, eqClass});
            for (auto var : *eqClass) {
                resDom->backwardMap.insert({var, newRepr});
            }
        }


        return resDom;
    }

    std::shared_ptr<Representative>
    EqualityDomain::chooseRepr(std::tuple<std::shared_ptr<Representative>, std::shared_ptr<Representative>> tuple,
                               std::set<std::shared_ptr<Variable>, RepresentativeCompare> eqClass) {
        std::shared_ptr<Representative> repr1 = std::get<0>(tuple);
        std::shared_ptr<Representative> repr2 = std::get<1>(tuple);

        if (repr1->getClassType() == ClassType::Constant && repr2->getClassType() == ClassType::Constant) {
            std::shared_ptr<Constant> c1 = std::static_pointer_cast<Constant>(repr1);
            std::shared_ptr<Constant> c2 = std::static_pointer_cast<Constant>(repr2);

            // TODO: reimplement comparator and use that
            if (c1->getValue() == c2->getValue()) {
                return std::static_pointer_cast<Representative>(c1);
            }
        }

        // Choose a repr from eqClass
        return std::static_pointer_cast<Representative>(*eqClass.begin());
    }

    /**
     * Construct a string containing all the equivalence classes (vlg. Invariants) of the domain
     *
     * @return the constructed string
     */
    std::string EqualityDomain::listInvariants() const {
        std::string ret = "Invariants: ";

        const auto &end = forwardMap.cend();
        for (auto it = forwardMap.cbegin(); it != end; ++it) {
            set<shared_ptr<Representative>> eqClass;
            eqClass.insert(it->first);
            for (auto it2 = it->second->begin(); it2 != it->second->end(); ++it2) {
                eqClass.insert(*it2);
            }
            shared_ptr<Invariant> invariant = std::make_shared<Invariant>(eqClass);
            ret += invariant->toString();
            auto current = it;
            auto next = ++current;
            if (next != (end)) {
                ret += ", ";
            }
        }

        return ret;
    }

    std::string EqualityDomain::dotPrintableInvariantsList() const {
        std::string ret = "|{Invariants:";
        for (auto it = forwardMap.cbegin(); it != forwardMap.cend(); it++) {
            ret += "}|{" + it->first->toDotString();
            auto eqIt = it->second->begin();
            if (it->first->getClassType() == ClassType::Variable) {
                eqIt = std::next(eqIt);
            }
            for (; eqIt != it->second->end(); eqIt++) {
                std::shared_ptr<Variable> var = std::static_pointer_cast<Variable>(*eqIt);
                ret += " = " + var->toDotString();
            }
        }

        return ret + "}";
    }
}