#pragma once

#include "mj/ast/MjStatement.hpp"


// A 'do' statement is a structured unit of conditional execution.
//
// do $statement
class MjDoStatement : public MjStatement {
private:
    MjBlockStatement &block_;
public:


    MjDoStatement(MjBlockStatement &block) : block_(block) {}


    MjStatementType statement_type() const {
        return MjStatementType::DO;
    }


    bool is_deterministic() const {
        return false;
    }


    MjBlockStatement &block() {
        return block_;
    }


    const MjBlockStatement &block() const {
        return block_;
    }
};
