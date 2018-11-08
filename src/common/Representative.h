//===----------------------------------------------------------------------===//
//
// This class defines the representative of an entry in the domain map.
// Possible subclasses: constant, variable
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_REPRESENTATIVE_H
#define LLVM_REPRESENTATIVE_H

namespace basic_relational_abstractions {

    class Representative {
    public:
        Representative();
        virtual ~Representative() {}

        virtual bool operator<(const Representative&) const {
            return false;
        }

        virtual bool operator==(const Representative&) const {
            return false;
        }
    };

}

#endif //LLVM_REPRESENTATIVE_H
