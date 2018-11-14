//
// Created by Peter-Benedikt von Niebelschütz on 07.11.18.
//

#include <string>
#include "Representative.h"
#include "Constant.h"
#include "Variable.h"
#include "../util.h"
#include "ClassType.h"

using namespace bra;
enum class ClassType;

Constant::Constant(int value) : value(value) {}

bool Constant::operator<(const Constant &other) const {
    return value < other.value;
}

bool Constant::operator==(const Constant &other) const {
    return value == other.value;
}

bool Constant::operator<(const Variable &other) const {
    //Constants always less than variables
    return true;
}

bool Constant::operator==(const Variable &other) const {
    //Constants never equal to variables
    return false;
}

int Constant::getValue() const {
    return value;
}

bra::ClassType Constant::getClassType() const{
    return bra::ClassType::Constant;
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
