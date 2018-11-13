add_llvm_loadable_module(llvm-ra
        src/BasicRelationalAnalysisPass.cpp
        src/BlockManager.cpp
        src/common/InstructionVisitor.cpp
        src/domains/EqualityDomain.cpp
        src/common/Representative.cpp
        src/common/RepresentativeHasher.cpp
        src/common/Constant.cpp
        src/common/Variable.cpp
        src/common/State.cpp
        src/common/BbWorklist.cpp

        PLUGIN_TOOL
        opt
        )
