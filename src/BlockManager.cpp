#include "BlockManager.h"
#include "InstructionVisitor.h"
#include "llvm/IR/CFG.h"
#include "domains/EqualityDomain.h"

namespace bra {
    void bra::BlockManager::analyse(Function &function) {
        for (BasicBlock &bb : function) {
            workList.push(&bb);
            std::shared_ptr<State> state;
            stateMap[std::shared_ptr<BasicBlock>(&bb)] = state;
        }

        while (!workList.empty()) {
            std::shared_ptr<BasicBlock> block = std::shared_ptr<BasicBlock>(workList.peek());
            std::shared_ptr<AbstractDomain> domain;

            const pred_range &allPredecessors = predecessors(block.get());

            std::vector<std::shared_ptr<AbstractDomain>> predecessorDomains;
            for (BasicBlock *pred : allPredecessors) {
                std::shared_ptr<BasicBlock> sharedPtrPred = std::shared_ptr<BasicBlock>(pred);
                std::shared_ptr<State> predecessorState = stateMap[sharedPtrPred];
                std::shared_ptr<AbstractDomain> predecessorDomain = predecessorState->getDomains()[0];
                predecessorDomains.push_back(predecessorDomain);
            }

            std::shared_ptr<AbstractDomain> lub = domain->leastUpperBound(predecessorDomains);

            InstructionVisitor instructionVisitor(lub, stateMap.find(block)->second);
            instructionVisitor.visit(*workList.pop());
            std::shared_ptr<State> stateAfter = instructionVisitor.getState();
            stateMap.at(block) = stateAfter;
        }
    }
}
