#pragma once

#include "mj/ast/MjMember.hpp"
#include "mj/ast/MjVariable.hpp"


/// @brief An MjProperty, or a member variable, is an MjVariable that belongs to an MjType.
// Shared properties are really just variables with type scope.
class MjMemberVariable : public MjMember, public MjVariable {
private:
    const MjComment &comment_;    // The comment associated with the variable
    const MjToken &name_;    // The variable name
    const MjType &type_;         // The variable type
    List<const MjToken *> definition_; // The temporary sequence of tokens that make the definition
    MjStorage storage_;            // The data of the variable
    u64 address_;          // The absolute address of the variable storage
    bool is_literal_;      // The memory will not be modified
    bool is_safe_;      // The memory may be be modified even when const
    bool is_reference_;    // The variable is a reference (storage is indeterminant)
    bool is_alias_;        // The variable is a reference (storage is not needed)
    MjType &owner; // The type that owns the member
    u32 offset; // offset relative to owner data
    bool is_mutable_; // The property does not inherit the 'const'-ness of its owner (does not apply to references)
public:


    MjMemberVariable(
        const MjToken &name,
        const MjType &type,
        MjComment &comment,
        MjType &owner,
        u32 offset,
        bool is_mutable,
        bool is_safe,
        bool is_reference,
        bool is_alias
    ) :
        name_(name),
        type_(type),
        comment_(comment),
        storage_(type.size()),
        owner(owner),
        offset(offset),
        is_mutable_(is_mutable),
        is_safe_(is_safe),
        is_reference_(is_reference),
        is_alias_(is_alias)
    {}


    ~MjMemberVariable() = default;


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
    u64 address() const {
        return address_;
    }


    // The memory may be be modified even when const
    bool is_mutable() const {
        return is_mutable_;
    }

    // The memory will not be modified
    bool is_literal() const {
        return is_literal_;
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
