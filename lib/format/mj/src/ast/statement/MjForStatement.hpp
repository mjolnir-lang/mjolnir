#pragma once

#include "mj/ast/MjExpression.hpp"
#include "mj/ast/MjStatement.hpp"


class MjForStatement : public MjStatement {
private:
    MjStatement &statement_;
    MjBlockStatement &block_;
    MjExpression &expression_;
    MjExpression &condition_;
public:


    MjForStatement(
        MjExpression &expression,
        MjExpression &condition,
        MjStatement &statement,
        MjBlockStatement &block
    ) :
        statement_(statement),
        condition_(condition),
        block_(block),
        expression_(expression)
    {}


    MjStatementType statement_type() const {
        return MjStatementType::FOR;
    }


    bool is_deterministic() const {
        return false;
    }


    MjStatement &statement() {
        return statement_;
    }


    const MjStatement &statement() const {
        return statement_;
    }


    MjBlockStatement &block() {
        return block_;
    }


    const MjBlockStatement &block() const {
        return block_;
    }


    MjExpression &expression() {
        return expression_;
    }


    const MjExpression &expression() const {
        return expression_;
    }
};
