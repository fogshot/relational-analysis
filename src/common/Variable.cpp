//
// Created by Peter-Benedikt von Niebelschütz on 07.11.18.
//

#include <string>
#include "Variable.h"
#include "Constant.h"
#include "../util.h"
#include "ClassType.h"

using namespace bra;

Variable::Variable(const std::string &name) : name(name), isTemporaryVariable(false) {}

Variable::Variable(const std::string &name, const bool isTemporary) : name(name), isTemporaryVariable(isTemporary) {}

bool Variable::operator<(const std::shared_ptr<Variable> other) const {
    DEBUG_OUTPUT("\nVAR COMPARE <!!!!\n");
    return name < other->name;
}

bool Variable::operator==(const std::shared_ptr<Variable> other) const {
    DEBUG_OUTPUT("\nVAR COMPARE ==!!!!\n");
    return name == other->name;
}

bool Variable::operator<(const std::shared_ptr<Constant> other) const {
    //Variables always greater than constants
    return false;
}

bool Variable::operator==(const std::shared_ptr<Constant> other) const {
    //Variables never equal to constants
    return false;
}

const std::string &Variable::getName() const {
    return name;
}

bra::ClassType Variable::getClassType() const {
    return ClassType::Variable;
}

std::string Variable::toString() const {
    return name;
}

std::ostream &bra::operator<<(std::ostream &stream, const std::shared_ptr<Variable> var) {
    return stream << var->toString();
}

size_t Variable::hash() const {
    return std::hash<std::string>{}(getName());
}

bool Variable::getIsTemporaryVariable() const {
    return isTemporaryVariable;
}
