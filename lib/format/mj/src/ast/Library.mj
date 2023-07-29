#pragma once

#include "mj/ast/MjScope.hpp"


/// @brief An `MjLibrary` is a collection of `MjModule` objects which are
/// tightly coupled and are bound to the same import scope and API version.
class MjLibrary {
private:
    MjScope scope_;
    const Path &path_;
public:


    MjLibrary(
        const Path &path
    ) :
        path_(path)
    {}


    const Path &path() const {
        return path_;
    }


    const MjScope &scope() const {
        return scope_;
    }
};
