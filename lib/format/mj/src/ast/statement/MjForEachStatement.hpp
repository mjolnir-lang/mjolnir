#pragma once

#include "mj/ast/MjExpression.hpp"
#include "mj/ast/MjStatement.hpp"


class MjForEachStatement : public MjStatement {
private:
    MjStatement &statement_;
    MjBlockStatement &block_;
    MjExpression &expression_;
public:


    MjForEachStatement(
        MjExpression &expression,
        MjStatement &statement,
        MjBlockStatement &block
    ) :
        statement_(statement),
        block_(block),
        expression_(expression)
    {}


    MjStatementType statement_type() const {
        return MjStatementType::FOR_EACH;
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
