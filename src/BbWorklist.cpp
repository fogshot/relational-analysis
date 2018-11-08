#include "BbWorklist.h"
#include "common/State.h"

using namespace llvm;
namespace bra {

    void BbWorkList::push(BasicBlock *bb) {
        if (inWorklist.find(bb) == inWorklist.end()) {
            worklist.push(bb);
            inWorklist.insert(bb);
        }
    }

    BasicBlock *BbWorkList::pop() {
        auto temp = worklist.front();
        inWorklist.erase(temp);
        worklist.pop();
        return temp;
    }

    BasicBlock *BbWorkList::peek() { return worklist.front(); }

    bool BbWorkList::empty() { return worklist.empty(); }
}