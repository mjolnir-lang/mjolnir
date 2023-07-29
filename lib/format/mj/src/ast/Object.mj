#pragma once

#include "mj/ast/MjType.hpp"
#include "mj/ast/MjStorage.hpp"


/// An MjObject is an association of a type with storage.
/// This is used for compile time emulation and execution.
class MjObject {
public:


    // Return the type information.
    virtual const MjType &type() const = 0;


    // Return the type information.
    u32 size() const {
        return type().size();
    }


    // Return the type information.
    u32 alignment() const {
        return type().alignment();
    }


    // Return the storage
    virtual MjStorage &storage() = 0;


    // Return the storage
    virtual const MjStorage &storage() const = 0;
};
