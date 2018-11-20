#ifndef LLVM_BLOCKMANAGER_H
#define LLVM_BLOCKMANAGER_H

#include <map>
#include "src/common/BbWorklist.h"
#include "src/common/State.h"
#include "src/common/BbSorter.h"

namespace bra {
    class BlockManager {
    public:
        void analyse(Function &function);

        // TODO: querying based on name is probably not a good idea generally
        std::shared_ptr<State> getStateForBBName(std::string bbName) const;
    private:
        BbWorkList workList;
        std::map<BasicBlock *, std::shared_ptr<State>, BbSorter> basicBlock2StateMap;
        shared_ptr<std::map<Value *, std::shared_ptr<Variable>>> pValue2TempVariableMap;
    };
}


#endif //LLVM_BLOCKMANAGER_H