#pragma once

#include "mj/ast/MjExpression.hpp"
#include "mj/ast/MjStatement.hpp"
#include "mj/ast/MjToken.hpp"


// return $value;
class MjReturnStatement : public MjStatement {
private:
    MjExpression value_;
public:


    MjReturnStatement(
        MjExpression value
    ) :
        value_(value)
    {}


    MjStatementType statement_type() const {
        return MjStatementType::RETURN;
    }


    bool is_deterministic() const {
        return false;
    }


    const MjExpression &value() const {
        return value_;
    }
};
