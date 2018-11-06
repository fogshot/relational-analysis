//
// Created by Peter-Benedikt von Niebelschütz on 06.11.18.
//

//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
    // Hello - The first implementation, without getAnalysisUsage.
    struct BasicRelationalAnalysisPass : public FunctionPass {
        static char ID; // Pass identification, replacement for typeid
        BasicRelationalAnalysisPass() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
            errs() << "Hello World!" << "\n";
            F.getBasicBlockList();
            return false;
        }
    };
}

char BasicRelationalAnalysisPass::ID = 0;
static RegisterPass<BasicRelationalAnalysisPass> X("basicra", "Basic Relational Analysis Pass", false, true);