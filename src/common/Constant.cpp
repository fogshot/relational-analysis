//
// Created by Peter-Benedikt von Niebelschütz on 07.11.18.
//

#include "Constant.h"
#include "Variable.h"

using namespace bra;

Constant::Constant(int value) : value(value) {}

bool Constant::operator<(const Constant& other) const {
    return value < other.value;
}

bool Constant::operator==(const Constant& other) const {
    return value == other.value;
}

bool Constant::operator<(const Variable& other) const {
    return false;
}

bool Constant::operator==(const Variable& other) const {
    return false;
}