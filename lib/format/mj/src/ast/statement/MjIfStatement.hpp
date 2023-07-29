#pragma once

#include "mj/ast/MjExpression.hpp"
#include "mj/ast/MjStatement.hpp"
#include "mj/ast/MjToken.hpp"


// An 'if' statement is a structured unit of conditional execution.
//
// if ($condition) $statement else $else_statement
class MjIfStatement : public MjStatement {
private:
    MjStatement &init_statement_;
    MjExpression condition_;
    MjBlockStatement if_block_;
    MjBlockStatement else_block_;
public:


    MjIfStatement(
        MjStatement &init_statement,
        MjExpression condition,
        MjBlockStatement if_block,
        MjBlockStatement else_block
    ) :
        init_statement_(init_statement),
        condition_(condition),
        if_block_(if_block),
        else_block_(else_block)
    {}


    MjStatementType statement_type() const {
        return MjStatementType::IF;
    }


    bool is_deterministic() const {
        return false;
    }


    const MjExpression &condition() const {
        return condition_;
    }


    const MjBlockStatement &if_block() const {
        return if_block_;
    }


    const MjBlockStatement &else_block() const {
        return else_block_;
    }
};
