#pragma once

#include "mj/ast/MjScope.hpp"

#include "std/Path.hpp"


// Modules participate in the module dependency graph for compilation order.
// They are built from source files and object files.
// Modules also declare their platform requirements.
class MjModule {
private:
    const MjToken &name_;
    MjModule *parent_;              // The parent scope
    Vector<MjModule *> modules_;      // Used to keep track of which modules have been imported
    Vector<MjBasicType *> basic_types_;     // Defined types
    Vector<MjTemplate *> templates_;  // Defined templates (generic types)
    Vector<MjFunction *> functions_;  // The free functions
    Vector<MjOperator *> operators_;  // The operator overloads
public:


    MjModule(
        const MjToken &name
    ) :
        name_(name)
    {}


    const MjToken &name() const {
        return name_;
    }


    /// @brief Return the list of member variables defined by the type.
    const Vector<MjModule *> &modules() const {
        return modules_;
    }


    /// @brief Return the list of member variables defined by the type.
    const Vector<MjBasicType *> &basic_types() const {
        return basic_types_;
    }


    /// @brief Return the list of methods defined by the type.
    const Vector<MjFunction *> &functions() const {
        return functions_;
    }


    /// @brief Return the list of operators defined by the type.
    const Vector<MjTemplate *> &templates() const {
        return templates_;
    }


    /// @brief Return the list of operators defined by the type.
    const Vector<MjOperator *> &operators() const {
        return operators_;
    }


    const MjScope &shared() const {
        ;
    }
};
