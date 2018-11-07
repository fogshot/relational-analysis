//===----------------------------------------------------------------------===//
//
// Implementation of lib/Analysis/RelationalAnalysis/src/common/Representative.h
// A constant has a specific int value
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_CONSTANT_H
#define LLVM_CONSTANT_H


class Constant {
public:
    Constant(int value);
private:
    int value;
};


#endif //LLVM_CONSTANT_H
