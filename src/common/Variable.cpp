//
// Created by Peter-Benedikt von Niebelschütz on 07.11.18.
//

#include "Variable.h"
#include "Constant.h"

using namespace basic_relational_abstractions;

Variable::Variable(const std::string &name) : name(name) {};

bool Variable::operator<(const Variable& other) const {
    return name < other.name;
}

bool Variable::operator==(const Variable& other) const {
    return name == other.name;
}

bool Variable::operator<(const Constant& other) const {
    return false;
}

bool Variable::operator==(const Constant& other) const {
    return false;
}