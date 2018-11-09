#include "Representative.h"

using namespace basic_relational_abstractions;

Representative::Representative() {}

bool Representative::operator<(const Representative &other) const {
    // Fallback, should never be called anyways
    return false;
}

bool Representative::operator==(const Representative &other) const {
    // Fallback, should never be called anyways
    return false;
}