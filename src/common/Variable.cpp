//
// Created by Peter-Benedikt von Niebelschütz on 07.11.18.
//

#include <string>
#include "Variable.h"
#include "Constant.h"
#include "../util.h"

using namespace bra;

Variable::Variable(const std::string &name) : name(name) {};

bool Variable::operator<(const Variable &other) const {
    return name < other.name;
}

bool Variable::operator==(const Variable &other) const {
    return name == other.name;
}

bool Variable::operator<(const Constant &other) const {
    return false;
}

bool Variable::operator==(const Constant &other) const {
    return false;
}

const std::string &Variable::getName() const {
    return name;
}

std::string Variable::toString() const {
    return name;
}

std::ostream &bra::operator<<(std::ostream &stream, const Variable &var) {
    return stream << var.toString();
}


std::ostream &bra::operator<<(std::ostream &stream, const std::shared_ptr<Variable> &varPtr) {
    return stream << varPtr->toString();
}

size_t Variable::hash() const {
    return std::hash<std::string>{}(getName());
}
