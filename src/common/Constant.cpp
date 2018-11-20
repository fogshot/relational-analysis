#include <string>
#include "Representative.h"
#include "Constant.h"
#include "Variable.h"
#include "../util.h"
#include "ClassType.h"

enum class ClassType;

namespace bra {
    Constant::Constant(int value) : value(value) {}

    int Constant::getValue() const {
        return value;
    }

    ClassType Constant::getClassType() const {
        return ClassType::Constant;
    }

    std::string Constant::toString() const {
        return std::to_string(value);
    }

    std::string Constant::toDotString() const {
        return toString();
    }

    std::ostream &operator<<(std::ostream &stream, const std::shared_ptr<Constant> con) {
        return stream << con->toString();
    }

    size_t Constant::hash() const {
        return std::hash<int>{}(getValue());
    }
}
