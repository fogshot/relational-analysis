#include "Representative.h"
#include "../util.h"

namespace bra {

    Representative::Representative() {}

    bool Representative::operator<(const std::shared_ptr<Representative> other) const {
        // Fallback, should never be called anyways but must be implemented since this is a library
        return false;
    }

    bool Representative::operator==(const std::shared_ptr<Representative> other) const {
        // Fallback, should never be called anyways but must be implemented since this is a library
        return false;
    }

    std::ostream &operator<<(std::ostream &stream, const std::shared_ptr<Representative> repr) {
        return stream << repr->toString();
    }

/*
inline bool operator<(const Representative& lhs, const Representative& rhs){
    auto lType = lhs.getClassType();
    auto rType = rhs.getClassType();

    // Same type, order by attribute.
    if (lType == rType) {
        if (lType == ClassType::Variable) {
            const auto& lhsCast = dynamic_cast<const Variable&>(lhs);
            const auto& rhsCast = dynamic_cast<const Variable&>(rhs);
            return lhsCast.getName() < rhsCast.name;
        }
        if (lType == ClassType::Constant) {
            const auto& lhsCast = dynamic_cast<const Constant&>(lhs);
            const auto& rhsCast = dynamic_cast<const Constant&>(rhs);
            return lhsCast.getValue() < rhsCast.getValue();
        }
    }
    // Different type, order Constant first
    return lType == ClassType::Constant;
}*/

}