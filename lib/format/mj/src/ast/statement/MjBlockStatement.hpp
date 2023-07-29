#pragma once

#include "mj/ast/MjStatement.hpp"


class MjBlockStatement : public MjStatement {
private:
    Vector<MjStatement *> statements_;
public:


    MjBlockStatement() {}


    MjStatementType statement_type() const {
        return MjStatementType::BLOCK;
    }


    Vector<MjStatement *> &statements() {
        return statements_;
    }


    bool is_deterministic() const {
        return false;
    }


    const Vector<MjStatement *> &statements() const {
        return statements_;
    }
};
