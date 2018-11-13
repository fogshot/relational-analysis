#include "BlockManager.h"
#include "InstructionVisitor.h"
#include "llvm/IR/CFG.h"
#include "src/domains/EqualityDomain.h"

namespace bra {
    void BlockManager::analyse(Function &function) {
        for (auto bbIt = function.begin(); bbIt != function.end(); bbIt++) {
            DEBUG_OUTPUT(bbIt->getName());
            workList.push(&(*bbIt));
//            stateMap.insert({std::shared_ptr<BasicBlock>(&(*bbIt)), std::shared_ptr<State>(new State())});
        }

//        while (!workList.empty()) {
//            std::shared_ptr<BasicBlock> block = std::shared_ptr<BasicBlock>(workList.peek());
//            std::shared_ptr<AbstractDomain> domain;
//
//            const pred_range &allPredecessors = predecessors(block.get());
//
//            std::vector<std::shared_ptr<AbstractDomain>> predecessorDomains;
//            for (BasicBlock *pred : allPredecessors) {
//                std::shared_ptr<BasicBlock> sharedPtrPred = std::shared_ptr<BasicBlock>(pred);
//                std::shared_ptr<State> predecessorState = stateMap[sharedPtrPred];
//                std::shared_ptr<AbstractDomain> predecessorDomain = predecessorState->getDomains()[0];
//                predecessorDomains.push_back(predecessorDomain);
//            }
//
//            std::shared_ptr<AbstractDomain> lub = domain->leastUpperBound(predecessorDomains);
//
//            InstructionVisitor instructionVisitor(lub, stateMap.find(block)->second);
//            instructionVisitor.visit(*workList.pop());
//            std::shared_ptr<State> stateAfter = instructionVisitor.getState();
//            stateMap.at(block) = stateAfter;
//        }
    }
}
