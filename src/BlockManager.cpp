#include "BlockManager.h"
#include "common/InstructionVisitor.h"
#include "llvm/IR/CFG.h"
#include "domains/EqualityDomain.h"
#include <llvm/Support/raw_ostream.h>
#include <iostream>
#include "util.h"

using namespace llvm;

namespace bra {
    void bra::BlockManager::analyse(Function &function) {
        for (BasicBlock &bb : function) {
            /// Visit each BB at least once
            workList.push(&bb);

            /// Initialize a State for each BB
            std::shared_ptr<State> st = std::make_shared<State>(
                    std::vector<std::shared_ptr<AbstractDomain>>({std::make_shared<EqualityDomain>()})
            );
            stateMap.insert({&bb, st});
        }


        // TODO remove this debug output loop
        for (auto it = stateMap.begin(); it != stateMap.end(); it++) {
            string resultString;

            std::vector<std::shared_ptr<AbstractDomain>> domains = it->second->getDomains();
            for (auto domIt = domains.begin(); domIt != domains.end(); domIt++) {
                resultString += domIt->get()->toString();
            }

            DEBUG_OUTPUT(string(BLUE)
                                 +"BasicBlock: (" + it->first->getName().str()
                                 + ") -> State: (" + to_string(it->second->getVisits()) + ", "
                                 + resultString + ")" + string(NO_COLOR)
            );
        }
        DEBUG_OUTPUT(string(BLUE)
                             +workList.toString() + string(NO_COLOR));

        while (!workList.empty()) {
            auto block = workList.peek();
            // TODO make this domain agnostic
            std::shared_ptr<AbstractDomain> domain = make_shared<EqualityDomain>();

            const pred_range &allPredecessors = predecessors(block);

            // TODO: this breaks when multiple domains exist per state
            std::vector<std::shared_ptr<AbstractDomain>> predecessorDomains;
            for (BasicBlock *pred : allPredecessors) {
                std::shared_ptr<State> predecessorState = stateMap[pred];
                auto arr = predecessorState->getDomains();
                std::shared_ptr<AbstractDomain> predecessorDomain = arr[0];
                predecessorDomains.push_back(predecessorDomain);
            }

            /// Calculate least upper bounds to obtain starting state for this BB
            std::shared_ptr<AbstractDomain> lub = domain->leastUpperBound(predecessorDomains);

            // TODO: *stateBefore == *stateAfter
            std::shared_ptr<State> stateBefore = stateMap.find(block)->second;
            InstructionVisitor instructionVisitor(lub, stateBefore);
            instructionVisitor.visit(*workList.pop());
            std::shared_ptr<State> stateAfter = instructionVisitor.getState();
            stateMap.at(block) = stateAfter;

            // if state after is different from state before, reappend all children of this BB to the workList!
//            if (!(*stateAfter == *stateBefore) {
//                for (BasicBlock *succ : successors(block)) {
//                    if (!workList.find(succ))
//                        workList.push(succ);
//                }
//            }
        }
    }
}
