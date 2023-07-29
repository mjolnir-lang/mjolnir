#pragma once

#include "mj/ast/MjStatement.hpp"
#include "mj/ast/MjOperator.hpp"
#include "mj/ast/MjType.hpp"

#include "std/Vector.hpp"


// An expression is a structured unit of evaluation.
struct MjExpression : public MjStatement {
protected:
    Vector<MjExpression> terms_; // The terms of the expression
    const MjOperator &op_;          // The operator of the expression
    bool is_deterministic_ = false; // If true, the expression is deterministic
public:


    MjExpression(
        const MjOperator &op
    ) :
        op_(op)
    {}
public:


    const MjType &type() const {
        return op_.type();
    }


    MjStatementType statement_type() const {
        return MjStatementType::EXPRESSION;
    }


    bool is_deterministic() const {
        return is_deterministic_;
    }


    const MjExpression &reduce() const {
        return *this;
    }


    const MjExpression &evaluate() const {
        return *this;
    }
};
