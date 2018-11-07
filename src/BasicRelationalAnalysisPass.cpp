//
// Created by Peter-Benedikt von Niebelschütz on 06.11.18.
//

//===----------------------------------------------------------------------===//
//
// This file implements the entry point for our Basic Relational Analysis Pass,
// which is capable of finding equality relations between multiple variables
// and/or constants.
//
//===----------------------------------------------------------------------===//

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "util.h"

using namespace llvm;

namespace {
    struct BasicRelationalAnalysisPass : public FunctionPass {
        static char ID; // Pass identification, replacement for typeid
        BasicRelationalAnalysisPass() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
            STD_OUTPUT("Hello World!");
            F.getBasicBlockList();
            return false;
        }

        void getAnalysisUsage(AnalysisUsage &AU) const override {
            // This Pass is pure analysis => No modification => Preserves all
            AU.setPreservesAll();
        }

        void releaseMemory() override {
            // TODO: release Memory once applicable (analysis result)
        }
    };
}

char BasicRelationalAnalysisPass::ID = 0;
/// cmd-option-name, description (--help), onlyCFG, analysisPass
static RegisterPass<BasicRelationalAnalysisPass> X("basicra", "Basic Relational Analysis Pass", false, true);