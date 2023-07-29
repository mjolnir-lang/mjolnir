#pragma once

#include "mj/ast/MjFunction.hpp"


/// @brief An `MjFunction` is an `MjCode` object associated with a name and an `MjFunctionType`.
class MjFreeFunction : public MjFunction {
protected:
    const MjToken &name_;  // The function name
    const MjFunctionType &type_;       // The function type
    Vector<MjFunctionParameter *> parameters_;
    MjComment &comment_; // The comment associated with the function
    List<const MjToken &> tokens_; // The temporary sequence of tokens that make the definition
    bool is_deterministic_;
    bool is_expression_;

    union {
        MjBlockStatement statement_;
        MjExpression expression_;
    };
public:


    MjFreeFunction(
        const MjToken &name,
        const MjFunctionType &type,
        Vector<MjFunctionParameter *> parameters,
        bool is_deterministic
    ) :
        name_(name),
        type_(type),
        is_deterministic_(is_deterministic)
    {}


    // The comment associated with the variable
    const MjComment &comment() const {
        return comment_;
    }


    // The variable name
    const MjToken &name() const {
        return name_;
    }


    // The variable type
    const MjFunctionType &type() const {
        return type_;
    }


    // The temporary sequence of tokens that make the definition
    const List<const MjToken *> &tokens() const {
        return tokens_;
    }
};

