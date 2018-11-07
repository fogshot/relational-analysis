add_llvm_loadable_module(llvm-ra
        src/BasicRelationalAnalysisPass.cpp
        src/common/AbstractDomain.cpp

        PLUGIN_TOOL
        opt
        )