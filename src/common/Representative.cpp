#include "Representative.h"
#include "../util.h"

using namespace bra;

Representative::Representative() {}

bool Representative::operator<(const Representative &other) const {
    // Fallback, should never be called anyways but must be implemented since this is a library
    return false;
}

bool Representative::operator==(const Representative &other) const {
    // Fallback, should never be called anyways but must be implemented since this is a library
    return false;
}

std::ostream &bra::operator<<(std::ostream &stream, const Representative &repr) {
    return stream << repr.toString();
}

std::ostream &bra::operator<<(std::ostream &stream, const std::shared_ptr<Representative> &reprPtr) {
    return stream << reprPtr->toString();
}
