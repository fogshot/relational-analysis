//===----------------------------------------------------------------------===//
//
// This class defines the representative of an entry in the domain map.
// Possible subclasses: constant, variable
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_REPRESENTATIVE_H
#define LLVM_REPRESENTATIVE_H

namespace bra {

    class Representative {
    public:
        Representative();
        virtual ~Representative() {}

        virtual bool operator<(const Representative&) const;
        virtual bool operator==(const Representative&) const;
    };

}

#endif //LLVM_REPRESENTATIVE_H
