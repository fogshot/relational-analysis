#include <string>
#include "Representative.h"
#include "Constant.h"
#include "Variable.h"
#include "../util.h"
#include "ClassType.h"

using namespace bra;
enum class ClassType;

Constant::Constant(int value) : value(value) {}

int Constant::getValue() const {
    return value;
}

bra::ClassType Constant::getClassType() const{
    return bra::ClassType::Constant;
}

std::string Constant::toString() const {
    return std::to_string(value);
}

std::ostream &bra::operator<<(std::ostream &stream, const std::shared_ptr<Constant> con) {
    return stream << con->toString();
}

size_t Constant::hash() const {
    return std::hash<int>{}(getValue());
}
