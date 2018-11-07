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


#endif //LLVM_UTIL_H
