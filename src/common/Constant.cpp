//
// Created by Peter-Benedikt von Niebelschütz on 07.11.18.
//

#include <string>
#include "Constant.h"
#include "Variable.h"
#include "../util.h"

using namespace bra;

Constant::Constant(int value) : value(value) {}

bool Constant::operator<(const Constant &other) const {
    return value < other.value;
}

bool Constant::operator==(const Constant &other) const {
    return value == other.value;
}

bool Constant::operator<(const Variable &other) const {
    return false;
}

bool Constant::operator==(const Variable &other) const {
    return false;
}

int Constant::getValue() const {
    return value;
}

std::string Constant::toString() const {
    return std::to_string(value);
}

std::ostream &bra::operator<<(std::ostream &stream, const Constant &constant) {
    return stream << constant.toString();
}

std::ostream &bra::operator<<(std::ostream &stream, const std::shared_ptr<Constant> &constantPtr) {
    return stream << constantPtr->toString();
}

size_t Constant::hash() const {
    return std::hash<int>{}(getValue());
}
