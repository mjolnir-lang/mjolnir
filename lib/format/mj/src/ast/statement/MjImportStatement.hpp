#pragma once

#include "mj/ast/MjStatement.hpp"
#include "mj/ast/MjModule.hpp"


class MjImportStatement : public MjStatement {
private:
    MjModule module_;
public:


    MjImportStatement(
        MjModule module
    ) :
        module_(module)
    {}


    MjStatementType statement_type() const {
        return MjStatementType::IMPORT;
    }


    bool is_deterministic() const {
        return false;
    }


    const MjModule &module() const {
        return module_;
    }
};
