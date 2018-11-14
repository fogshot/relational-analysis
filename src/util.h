//
// Created by Dominik Horn on 07.11.18.
//

#ifndef GLOBAL_VARS
#define GLOBAL_VARS
static int globalDebugOutputTabLevel = 0;
#endif

#ifndef BASICRA_UTIL_H
#define BASICRA_UTIL_H

#include <llvm/Support/raw_ostream.h>
#include <string>

// Enable debug output
#define DEBUG

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"
#define NO_COLOR "\033[0m"

#ifdef DEBUG
#define DEBUG_ERR(text) llvm::errs() << RED << "ERROR: " << text << NO_COLOR << "\n"
#define DEBUG_OUTPUT(text) llvm::errs() << std::string(2*globalDebugOutputTabLevel, ' ') << text << "\n"
#else
#define DEBUG_ERR(text)
#define DEBUG_OUTPUT(text)
#endif
#define STD_OUTPUT(text) llvm::errs() << text << "\n"


#endif //LLVM_UTIL_H
