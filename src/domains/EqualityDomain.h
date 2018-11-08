//
// Created by vanessa on 11/7/18.
//

#ifndef EQUALITYDOMAIN_H
#define EQUALITYDOMAIN_H

#include "../common/AbstractDomain.h"
#include "../common/Representative.h"
#include "../common/Variable.h"
#include "../common/Constant.h"
#include <vector>
#include <map>


namespace basic_relational_abstractions {

    class EqualityDomain : AbstractDomain {

    public:

        EqualityDomain();

    protected:
        //assignment transforms
        void transform_unknown_assignment(Variable);

        void transform_constant_assignment(Variable,Constant);

        void transform_variable_assignment(Variable,Variable);

    private:
        std::map<Representative, std::vector<Variable>> forwardMap;
        std::map<Variable, Representative> backwardMap;

    };

}

#endif //EQUALITYDOMAIN_H
