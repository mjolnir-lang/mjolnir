#pragma once

#include "mj/ast/MjFunction.hpp"
#include "mj/ast/MjMember.hpp"


// Sequential parsing
// Concurrent parsing

// A method, or a member funtion, is a function that belongs to a type.
// Shared methods are really just functions with type scope.
class MjMethod : public MjMember, public MjFunction {
private:
    MjScope scope_;
    MjType &owner_; // The type that owns the member
    MjType &const_return_type_; // The method return type when called from a 'const' context
    bool is_const_callable_; // The method may be called on a 'const' owner with no change to the type
    bool is_virtual_;
    bool is_mutable_; // The method does not inherit the 'const'-ness of its owner (does not apply to references)
public:
    static const MjMethod NONE;


    MjMethod(
        const MjToken &name,
        bool is_virtual,
        bool is_mutable,
        bool is_const_callable
    ) {}
};
