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

            std::shared_ptr<State> state = stateMap.find(block)->second;
            InstructionVisitor instructionVisitor(lub, state);
            instructionVisitor.visit(*workList.pop());

            if (state->wasUpdatedOnLastVisit()) {
                // Reappend all children of bb
                for (BasicBlock *succ : successors(block)) {
                    if (!workList.find(succ)) {
                        workList.push(succ);
                    }
                }
            }

            for (const auto &d : state->getDomains()) {
                // TODO implement comparator for the set that dereferences the shared_ptr
                DEBUG_OUTPUT(string(BLUE)
                                     +d->listInvariants() + string(NO_COLOR));
            }
        }
    }
}
