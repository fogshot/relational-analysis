#include "BlockManager.h"
#include "common/InstructionVisitor.h"
#include "llvm/IR/CFG.h"
#include "domains/EqualityDomain.h"
#include <llvm/Support/raw_ostream.h>
#include <iostream>
#include "util.h"
#include "common/ClassType.h"

using namespace llvm;

namespace bra {
    void bra::BlockManager::analyse(Function &function) {
        // Visit each BB at least once
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
            // TODO: tmp output string
            DEBUG_OUTPUT(std::string(GREEN)
                                 +workList.toString() + std::string(NO_COLOR));

            /// Least Upper bounds (starting domains) for each visit
            std::vector<std::shared_ptr<AbstractDomain>> lubs;

            auto preds = predecessors(block);
            if (preds.begin() == preds.end()) {
                // TODO: add all other domains aswell
                lubs.push_back(std::make_shared<EqualityDomain>());
            } else {
                /// Group all domains from all predecessors based on classType
                std::map<ClassType, std::shared_ptr<std::vector<std::shared_ptr<AbstractDomain>>>> domMap;
                for (BasicBlock *pred : preds) {
                    for (auto dom : stateMap[pred]->getDomains()) {
                        auto domIt = domMap.find(dom->getClassType());
                        std::shared_ptr<std::vector<std::shared_ptr<AbstractDomain>>> domList;
                        if (domIt == domMap.end()) {
                            domList = std::make_shared<std::vector<std::shared_ptr<AbstractDomain>>>();
                            domList->push_back(dom);
                            domMap.insert({dom->getClassType(), domList});
                        } else {
                            domList = domIt->second;
                            domList->push_back(dom);
                        }
                    }
                }

                /// Calculate LUB for each domain group (== aggregate using LUB)
                for (auto domMapIt = domMap.begin(); domMapIt != domMap.end(); domMapIt++) {
                    std::vector<std::shared_ptr<AbstractDomain>> domainList = *domMapIt->second.get();
                    lubs.push_back((domainList[0])->leastUpperBound(domainList));
                }
            }

            std::shared_ptr<State> state = stateMap.find(block)->second;
            InstructionVisitor instructionVisitor(lubs, state);
            instructionVisitor.visit(*workList.pop());

            if (state->wasUpdatedOnLastVisit()) {
                // Reappend all children of bb
                DEBUG_OUTPUT(std::string(GREEN)
                                     +"reappending children" + std::string(NO_COLOR));
                DEBUG_OUTPUT(std::string(GREEN)
                                     +"  " + workList.toString() + std::string(NO_COLOR));
                for (BasicBlock *succ : successors(block)) {
                    if (!workList.find(succ)) {
                        workList.push(succ);
                    }
                }
                DEBUG_OUTPUT(std::string(GREEN)
                                     +"  " + workList.toString() + std::string(NO_COLOR));
            }

            for (const auto &d : state->getDomains()) {
                // TODO implement comparator for the set that dereferences the shared_ptr
                DEBUG_OUTPUT(string(BLUE)
                                     +d->listInvariants() + string(NO_COLOR));
            }
        }

        /// Print out analysis result
        DEBUG_OUTPUT(string(BLUE)
                             +"-------------------------------Analysis Result----------------------------------" +
                             string(NO_COLOR));
        for (auto it = stateMap.begin(); it != stateMap.end(); it++) {
            DEBUG_OUTPUT(it->first->getName().str() + ":");
            for (const auto &d : it->second->getDomains()) {
                // TODO implement comparator for the set that dereferences the shared_ptr
                DEBUG_OUTPUT("  "
                             + d->toString());
            }
        }
        DEBUG_OUTPUT(string(BLUE)
                             +"--------------------------------------------------------------------------------" +
                             string(NO_COLOR));
    }
}
