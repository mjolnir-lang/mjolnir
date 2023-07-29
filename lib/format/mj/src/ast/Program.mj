#pragma once

#include "mj/ast/MjModule.hpp"
#include "mj/ast/MjFreeFunction.hpp"

#include "std/File.hpp"



/// @brief A Program is an executable without a platform.
/// It lists dependencies and has a startup and a main function.
class MjProgram {
private:
    String name_;
    List<MjModule> modules_;
    MjFreeFunction startup_function_;
    MjFreeFunction main_function_;
public:


    MjProgram(
        StringView name
    ) :
        name_(name)
    {
        //add_builtins()
    }


    void export_source(const Path &path) {

        // Write module dependencies.
        //for (MjModule &mod : scope.modules) {
        //    mod.save(obj);
        //}

        // Write types.

        // Write identifiers.

        // Write data.
        //for (const String &line : obj) {
            //
        //}
    }
};
