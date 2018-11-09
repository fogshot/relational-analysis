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

size_t Representative::operator()(const Representative &) const {
    // Fallback, should never be called anyways but must be implemented since this is a library
    return 0;
}