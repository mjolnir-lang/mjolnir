#pragma once

#include "mj/ast/MjStatement.hpp"
#include "mj/ast/MjExpression.hpp"
#include "mj/ast/MjToken.hpp"


// yield $value;
class MjYieldStatement : public MjStatement {
private:
    MjExpression &value_;
public:


    MjYieldStatement(
        MjExpression &value
    ) :
        value_(value)
    {}


    MjStatementType statement_type() const {
        return MjStatementType::YIELD;
    }


    bool is_deterministic() const {
        return false;
    }


    const MjExpression &value() const {
        return value_;
    }
};
