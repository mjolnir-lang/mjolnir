#pragma once

#include "mj/ast/MjExpression.hpp"
#include "mj/ast/MjStatement.hpp"


// A 'while' statement is a structured unit of conditional execution.
//
// while (CONDITION) STATEMENT
class MjWhileStatement : public MjStatement {
private:
    MjBlockStatement block_;
    MjExpression &condition_;
public:


    MjWhileStatement(
        MjExpression &condition,
        MjBlockStatement block
    ) :
        block_(block),
        condition_(condition)
    {}


    MjStatementType statement_type() const {
        return MjStatementType::WHILE;
    }


    bool is_deterministic() const {
        return false;
    }


    const MjExpression &condition() const {
        return condition_;
    }


    const MjBlockStatement &block() const {
        return block_;
    }
};
