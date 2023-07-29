#pragma once

#include "mj/ast/MjVariable.hpp"


enum class MjMemberType : u8 {
    TYPE,
    VARIABLE,
    METHOD,
    TEMPLATE,
};


/// @brief An MjMember is an MjVariable associated with an offset within a parent type.
class MjMember {
public:


    virtual ~MjMember() = default;


    /// @brief This is the kind of member.
    /// @return 
    virtual MjMemberType member_type() = 0;


    /// @brief This is either the offset of the member within a type instance or the offset of the method pointer in the vtable.
    /// @return 
    virtual u32 member_offset() const = 0;
};
