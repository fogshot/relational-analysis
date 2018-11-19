//
// Created by Dominik Horn on 19.11.18.
//

#include <llvm/Pass.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Analysis/CFGPrinter.h>
//#include <llvm/Support/GraphWriter.h>
#include "DotPrinter.h"
#include "src/util.h"

using namespace llvm;

namespace bra {
    void DotPrinter::writeCFGToDotFile(Function &F) {
    std::string Filename = ("cfg." + F.getName() + ".dot").str();
    errs() << "Writing '" << Filename << "'...";

    std::error_code EC;
    raw_fd_ostream File(Filename, EC, sys::fs::F_Text);

    if (!EC)
        WriteGraph(File, (const Function *) &F, false);
    else
        errs() << "  error opening file for writing!";
    errs() << "\n";
}

    void DotPrinter::print(Function &F) {
        DEBUG_OUTPUT("PRINTING!!!");
        writeCFGToDotFile(F);
    }
}


