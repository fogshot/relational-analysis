#include "Representative.h"

using namespace bra;

Representative::Representative() {}

bool Representative::operator<(const Representative &other) const {
    // Fallback, should never be called anyways
    return false;
}

bool Representative::operator==(const Representative &other) const {
    // Fallback, should never be called anyways
    return false;
}