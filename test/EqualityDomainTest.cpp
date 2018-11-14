#include "gtest/gtest.h"
#include "../src/domains/EqualityDomain.h"

using namespace llvm;
using namespace bra;
using namespace std;

TEST(EqTest, testTransformConstantAssignment) {
    unique_ptr<EqualityDomain> eqd = make_unique<EqualityDomain>();
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Constant> c42 = make_shared<Constant>(42);
    eqd->transformConstantAssignment(x, c42);
    eqd->toString();
}
