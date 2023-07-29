#pragma once

#include "mj/ast/MjStatement.hpp"


class MjContinueStatement : public MjStatement {
private:
    u32 depth_;
public:


    MjContinueStatement(u32 depth) : depth_(depth) {}


    MjStatementType statement_type() const {
        return MjStatementType::CONTINUE;
    }


    u32 depth() const {
        return depth_;
    }


    bool is_deterministic() const {
        return true;
    }
};
