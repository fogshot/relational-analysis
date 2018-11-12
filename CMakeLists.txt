add_llvm_loadable_module(llvm-ra
        src/BasicRelationalAnalysisPass.cpp
        src/InstructionVisitor.cpp
        src/domains/EqualityDomain.cpp
        src/common/Representative.cpp
        src/common/RepresentativeHasher.cpp
        src/common/Constant.cpp
        src/common/Variable.cpp
        src/common/State.cpp
        src/BbWorklist.cpp
        src/BlockManager.cpp

        PLUGIN_TOOL
        opt
        )
