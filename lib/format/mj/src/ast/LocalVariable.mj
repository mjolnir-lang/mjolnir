#pragma once

#include "mj/ast/MjVariable.hpp"


/// @brief An `MjLocalVariable` is an `MjVariable` that belongs to a function scope.
class MjLocalVariable : public MjVariable {
protected:
    const MjComment &comment_;    // The comment associated with the variable
    const MjToken &name_;    // The variable name
    const MjType &type_;         // The variable type
    List<const MjToken *> definition_; // The temporary sequence of tokens that make the definition
    MjStorage storage_;            // The data of the variable
    u32 offset_;          // The absolute address of the variable storage
    bool is_safe_;      // The memory may be be modified even when const
    bool is_reference_;    // The variable is a reference (storage is indeterminant)
    bool is_alias_;        // The variable is a reference (storage is not needed)
public:


    MjLocalVariable(
        const MjToken &name,
        const MjType &type,
        MjComment &comment,
        bool is_safe,
        bool is_reference,
        bool is_alias
    ) :
        name_(name),
        type_(type),
        comment_(comment),
        storage_(type.size()),
        is_safe_(is_safe),
        is_reference_(is_reference),
        is_alias_(is_alias)
    {}


    // The comment associated with the variable
    const MjComment &comment() const {
        return comment_;
    }


    // The variable name
    const MjToken &name() const {
        return name_;
    }


    // The variable type
    const MjType &type() const {
        return type_;
    }


    // The temporary sequence of tokens that make the definition
    const List<const MjToken *> &definition() const {
        return definition_;
    }


    // The data of the variable
    const MjStorage &storage() const {
        return storage_;
    }


    // The absolute address of the variable storage
    u64 offset() const {
        return offset_;
    }


    // The memory may be be modified even when const
    bool is_safe() const {
        return is_safe_;
    }


    // The variable is a reference (storage is indeterminant)
    bool is_reference() const {
        return is_reference_;
    }


    // The variable is a reference (storage is not needed)
    bool is_alias() const {
        return is_alias_;
    }
};
