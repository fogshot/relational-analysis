add_llvm_loadable_module(llvm-ra
        src/BasicRelationalAnalysisPass.cpp
        src/common/Representative.cpp
        src/common/Constant.cpp
        src/common/Variable.cpp

        PLUGIN_TOOL
        opt
        )