#!/bin/bash

# Script to run all VSA on all test c-programs.
# Please specify the path to llvm and clang in the environment variables
# LLVM_BUILD_PATH.

# color definitions
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac

while :; do
    case $1 in
        -t) flag1="TEST"
        ;;
        *) break
    esac
    shift
done

if [ "$flag1" = "TEST" ]; then
    printf "${RED} TEST CAPABILITY NOT IMPLEMENTED ${NC}\n"
    exit
else
    EXE_FILE_NAME=llvm-ra
    EXE=$EXE_FILE_NAME.so

    # for some reason mac build chain spews out .dylib files instead of .so
    if [ $machine = "Mac" ]
    then
        printf "${YELLOW} Detected Mac platform -> Applying dylib fix ${NC}\n"
        EXE=$EXE_FILE_NAME.dylib
    fi
    PASS=basicra
fi

# if one argument passed: only analyze the passed program
if [ $# == 1 ] ; then
    ARRAY=($1)
else # run all samples
    ARRAY=($(ls -d *.c))
fi


# if no folder is existent
mkdir -p build

# for all c-files...
for f in ${ARRAY[*]};
do
    # ... print file name
    echo "###############################################################################"
    echo $(pwd)/$f
    # ... clean up for old run
    rm -f build/$f.out
    rm -f build/$f-opt.bc
    # ... compile
    printf "${BLUE} Compiling to llvm IR using clang... ${NC}\n"
    $LLVM_BUILD_PATH/bin/clang -O0 -emit-llvm $f -Xclang -disable-O0-optnone -c -o build/$f.bc
    # ... run mem2reg optimization
    # printf "${BLUE} Optimizing using mem2reg... ${NC}\n"
    # $LLVM_BUILD_PATH/bin/opt -mem2reg < build/$f.bc > build/$f-opt.bc
    # ... disassemble optimized file
    # printf "${BLUE} Disassemble optimized file... ${NC}\n"
    # $LLVM_BUILD_PATH/bin/llvm-dis build/$f-opt.bc
	printf "${BLUE} Disassemble file... ${NC}\n"
    $LLVM_BUILD_PATH/bin/llvm-dis build/$f.bc
    # ... run VSA
    printf "${BLUE} Running $PASS ${NC}\n"
    $LLVM_BUILD_PATH/bin/opt -load $LLVM_BUILD_PATH/lib/$EXE -$PASS < build/$f.bc > /dev/null 2> >(tee build/$f.out >&2)
#    $LLVM_BUILD_PATH/bin/opt -load $LLVM_BUILD_PATH/lib/$EXE -$PASS < build/$f-opt.bc > /dev/null 2> >(tee build/$f.out >&2)
    cp -n build/$f.out build/$f.ref
done

#printf "\nTEST SUMMARY:\n"
#for f in ${ARRAY[*]};
#do
#    if cmp build/$f.out build/$f.ref; then
#        # ... success
#        printf "Run: ${GREEN}$f${NC}\n"
#    else
#        # ... failure
#        printf "Run: ${RED}$f${NC}\n"
#    fi
#done
#printf "\n"
