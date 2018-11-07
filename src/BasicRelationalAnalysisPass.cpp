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
#include "llvm/IR/BasicBlock.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "util.h"

using namespace llvm;

namespace {
    // Hello - The first implementation, without getAnalysisUsage.
    struct BasicRelationalAnalysisPass : public FunctionPass {
        static char ID; // Pass identification, replacement for typeid
        BasicRelationalAnalysisPass() : FunctionPass(ID) {}

       bool runOnFunction(Function &F) override {
            STD_OUTPUT("Hello World!");
            F.getBasicBlockList();
            return false;
        }
    };
}

char BasicRelationalAnalysisPass::ID = 0;
/// cmd-option-name, description (--help), onlyCFG, analysisPass
static RegisterPass<BasicRelationalAnalysisPass> X("basicra", "Basic Relational Analysis Pass", false, true);