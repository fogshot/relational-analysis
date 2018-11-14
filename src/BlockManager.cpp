#include "BlockManager.h"
#include "common/InstructionVisitor.h"
#include "llvm/IR/CFG.h"
#include "domains/EqualityDomain.h"
#include <llvm/Support/raw_ostream.h>
#include <iostream>
#include "util.h"

using namespace std;
using namespace llvm;

namespace bra {
    void bra::BlockManager::analyse(Function &function) {
        for (BasicBlock &bb : function) {
            workList.push(&bb);

            // TODO: move code to State factory
            State *state = new State();
            shared_ptr<EqualityDomain> eqPtr = shared_ptr<EqualityDomain>(new EqualityDomain());
            state->addDomain(eqPtr);
            stateMap.insert({&bb, shared_ptr<State>(state)});
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

            std::vector<std::shared_ptr<AbstractDomain>> predecessorDomains;
            for (BasicBlock *pred : allPredecessors) {
				std::shared_ptr<State> predecessorState = stateMap[pred];
                std::shared_ptr<AbstractDomain> predecessorDomain = predecessorState->getDomains()[0];
                predecessorDomains.push_back(predecessorDomain);
            }

            std::shared_ptr<AbstractDomain> lub = domain->leastUpperBound(predecessorDomains);

			std::shared_ptr<State> stateBefore = stateMap.find(block)->second
            InstructionVisitor instructionVisitor(lub, stateBefore);
            instructionVisitor.visit(*workList.pop());
            std::shared_ptr<State> stateAfter = instructionVisitor.getState();
            stateMap.at(block) = stateAfter;

            // if state after is different from state before, reappend all children of this BB to the workList!
            if (stateAfter.operator* != stateBefore.operator*) {
				for (BasicBlock *succ : successors(block)) {
					if (!workList.find(succ))
						workList.push(succ);
				}
			}
        }
    }
}
