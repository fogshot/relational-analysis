#ifndef BBWORKLIST
#define BBWORKLIST

#include "llvm/IR/BasicBlock.h"
#include <queue>
#include <set>

using namespace llvm;

namespace bra {

    class BbWorkList {

    public:
        void push(BasicBlock *bb);

        BasicBlock *peek();

        BasicBlock *pop();

        bool empty();

    private:
        std::queue<BasicBlock *> worklist;
        std::set<BasicBlock *> inWorklist;
    };
}

#endif