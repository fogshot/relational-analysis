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
            State* state = new State();
            shared_ptr<EqualityDomain> eqPtr = shared_ptr<EqualityDomain>();
            state->addDomain(eqPtr);
            stateMap.insert({&bb, shared_ptr<State>(state)});
        }

        // TODO remove this debug output loop
        for (const auto &e : stateMap) {
            string domains;
            for (const auto &dom : e.second->getDomains()) {
                domains += dom->toString();
            }

            DEBUG_OUTPUT(string(BLUE)
                                 +"BasicBlock: (" + e.first->getName().str()
                                 + ") -> State: (" + to_string(e.second->getVisits()) + ", "
                                 + domains + ")" + string(NO_COLOR)
            );
        }
        DEBUG_OUTPUT(string(BLUE) + workList.toString() + string(NO_COLOR));

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

            DEBUG_OUTPUT(string(RED)
                                 +string("DEBUG marker") + string(NO_COLOR));
            // FIXME this causes a segfault, use empty eq-domain for now
            std::shared_ptr<AbstractDomain> lub = domain->leastUpperBound(predecessorDomains);
            // std::shared_ptr<AbstractDomain> lub = make_shared<EqualityDomain>();
            DEBUG_OUTPUT(string(GREEN)
                                 +string("DEBUG marker") + string(NO_COLOR));

            InstructionVisitor instructionVisitor(lub, stateMap.find(block)->second);
            instructionVisitor.visit(*workList.pop());
            std::shared_ptr<State> stateAfter = instructionVisitor.getState();
            stateMap.at(block) = stateAfter;
        }
    }
}
