#pragma once

#include "mj/ast/MjToken.hpp"


/// @brief An `MjComment` is a source code annotation attatched to AST objects.
class MjComment {
private:
    String &text_;
    //String &brief;
    //String &params;
    //String &returns;
    bool is_documentation_;
public:


    MjComment(
        String &text
    ) :
        text_(text)
    {}


    bool is_documentation() const {
        return is_documentation_;
    }


    StringView text() const {
        return text_;
    }
};
