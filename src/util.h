//
// Created by Dominik Horn on 07.11.18.
//

#ifndef BASICRA_UTIL_H
#define BASICRA_UTIL_H

#define DEBUG

#ifdef DEBUG
#define DEBUG_OUTPUT(text) errs() << text << "\n"
#else
#define DEBUG_OUTPUT(text)
#endif
#define STD_OUTPUT(text) errs() << text << "\n"

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"
#define NO_COLOR "\033[0m"

#endif //LLVM_UTIL_H
