#include "gtest/gtest.h"
#include "../src/domains/EqualityDomain.h"
#include "../src/common/Constant.h"
#include "../src/common/Variable.h"

using namespace llvm;
using namespace bra;
using namespace std;

TEST(EqTest, testEmptyEqualityDomain) {
    EqualityDomain eqd;
    ASSERT_EQ(eqd.toString(), "EqualityDomain (\n\tforwardMap {}\n  -> backwardMap {}");
}
