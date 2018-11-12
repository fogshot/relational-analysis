//===----------------------------------------------------------------------===//
//
// This class defines the representative of an entry in the domain map.
// Possible subclasses: constant, variable
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_REPRESENTATIVE_H
#define LLVM_REPRESENTATIVE_H

#include <functional>
#include <iostream>
#include <stddef.h>
#include <string>
#include <memory>

namespace bra {
    class Representative {
    public:
        Representative();

        virtual ~Representative() {};

        virtual bool operator<(const Representative &) const;

        virtual bool operator==(const Representative &) const;

        virtual size_t hash() const = 0;

        virtual std::string toString() const = 0;

        friend std::ostream &operator<<(std::ostream &, const Representative &);
        friend std::ostream &operator<<(std::ostream &, const std::shared_ptr<Representative> &);

        int id = 0;
    };

}

#endif //LLVM_REPRESENTATIVE_H
