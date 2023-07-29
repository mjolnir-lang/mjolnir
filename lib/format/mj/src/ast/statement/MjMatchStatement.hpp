#pragma once

#include "mj/ast/MjExpression.hpp"
#include "mj/ast/MjStatement.hpp"


struct MjWhenStatement {
    MjExpression &condition;
    MjStatement &statement;
};


class MjMatchStatement : public MjStatement {
private:
    Vector<MjWhenStatement> matches_;
    MjExpression &expression_;
public:


    MjMatchStatement()
    {}


    MjStatementType statement_type() const {
        return MjStatementType::MATCH;
    }
};
