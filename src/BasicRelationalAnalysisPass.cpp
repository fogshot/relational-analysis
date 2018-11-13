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

#include <string>
#include <sstream>
#include <llvm/ADT/Statistic.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/Pass.h>
#include <llvm/Support/raw_ostream.h>
#include "util.h"
#include "src/BlockManager.h"
#include "domains/EqualityDomain.h"
#include "common/Representative.h"
#include "common/Variable.h"
#include "common/Constant.h"

using namespace llvm;
using namespace std;

namespace bra {
    struct BasicRelationalAnalysisPass : public FunctionPass {
        static char ID; // Pass identification, replacement for typeid
        BasicRelationalAnalysisPass() : FunctionPass(ID) {}

    private:
        typedef FunctionPass super;
    public:
        bool runOnFunction(Function &F) override {
            // Obtain a block manager

            // TODO: TMP TEST CODE
            std::stringstream ss;
            EqualityDomain dom;
            Variable *varX = new Variable("x");
            Variable *varY = new Variable("y");
            Variable *varZ = new Variable("z");

            Constant *three = new Constant(3);
            Constant *four = new Constant(4);

            shared_ptr<Variable> varXPtr = shared_ptr<Variable>(varX);
            shared_ptr<Variable> varYPtr = shared_ptr<Variable>(varY);
            shared_ptr<Variable> varZPtr = shared_ptr<Variable>(varZ);

            shared_ptr<Constant> threePtr = shared_ptr<Constant>(three);
            shared_ptr<Constant> fourPtr = shared_ptr<Constant>(four);

            dom.transformConstantAssignment(varXPtr, threePtr);
            dom.transformConstantAssignment(varYPtr, threePtr);
            dom.transformConstantAssignment(varZPtr, fourPtr);
            ss << dom;
            DEBUG_OUTPUT(string(YELLOW)
                                 +ss.str() + string(NO_COLOR));

            BlockManager blockManager;

            // Analyse current function
            blockManager.analyse(F);

            // This is an analysis pass and never modifies any code
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

    char BasicRelationalAnalysisPass::ID = 0;
    /// cmd-option-name, description (--help), onlyCFG, analysisPass
    static RegisterPass<BasicRelationalAnalysisPass> X("basicra", "Basic Relational Analysis Pass", false, true);
}
