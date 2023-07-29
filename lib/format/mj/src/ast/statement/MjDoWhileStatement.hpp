#pragma once

#include "mj/ast/MjExpression.hpp"
#include "mj/ast/MjStatement.hpp"


// A 'do-while' statement is a structured unit of conditional execution.
//
// do $statement while ($condition) while_block
class MjDoWhileStatement : public MjStatement {
private:
    MjBlockStatement &do_block_;
    MjBlockStatement &while_block_;
    MjExpression &condition_;
public:


    MjDoWhileStatement(
        MjExpression &condition,
        MjBlockStatement &do_block,
        MjBlockStatement &while_block
    ) :
        do_block_(do_block),
        while_block_(while_block),
        condition_(condition)
    {}


    MjStatementType statement_type() const {
        return MjStatementType::DO_WHILE;
    }


    bool is_deterministic() const {
        return false;
    }


    MjBlockStatement &do_block() {
        return do_block_;
    }


    const MjBlockStatement &do_block() const {
        return do_block_;
    }


    MjBlockStatement &while_block() {
        return while_block_;
    }


    const MjBlockStatement &while_block() const {
        return while_block_;
    }


    MjExpression &condition() {
        return condition_;
    }


    const MjExpression &condition() const {
        return condition_;
    }
};
