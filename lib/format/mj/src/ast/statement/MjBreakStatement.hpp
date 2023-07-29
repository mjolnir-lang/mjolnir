#pragma once

#include "mj/ast/MjStatement.hpp"


class MjBreakStatement : public MjStatement {
private:
    u32 depth_;
public:


    MjBreakStatement(u32 depth) : depth_(depth) {}


    MjStatementType statement_type() const {
        return MjStatementType::BREAK;
    }


    bool is_deterministic() const {
        return false;
    }


    u32 depth() const {
        return depth_;
    }
};
