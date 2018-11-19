//
// Created by Dominik Horn on 19.11.18.
//

#ifndef LLVM_DOTPRINTER_H
#define LLVM_DOTPRINTER_H

#include <llvm/IR/Function.h>

namespace bra {
    class DotPrinter {
    public:
        // TODO: tmp
        void print(llvm::Function &);

        void writeCFGToDotFile(llvm::Function &);
    };
}


#endif //LLVM_DOTPRINTER_H
