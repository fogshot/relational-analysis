add_llvm_loadable_module(llvm-ra
        src/BasicRelationalAnalysisPass.cpp
        src/InstructionVisitor.cpp
        src/domains/EqualityDomain.cpp
        src/common/Representative.cpp
        src/common/Constant.cpp
        src/common/Variable.cpp
        src/common/State.cpp

        PLUGIN_TOOL
        opt
        )
