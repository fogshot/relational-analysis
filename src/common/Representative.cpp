#include "Representative.h"
#include "../util.h"

namespace bra {

    Representative::Representative() {}

    std::ostream &operator<<(std::ostream &stream, const std::shared_ptr<Representative> repr) {
        return stream << repr->toString();
    }

    inline bool operator==(const Representative& repr1, const Representative& repr2) {
        return repr1.operator==(repr2);
    }
}