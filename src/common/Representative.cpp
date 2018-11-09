#include "Representative.h"

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
