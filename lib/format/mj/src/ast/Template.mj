#pragma once

#include "mj/ast/MjComment.hpp"
#include "mj/ast/MjType.hpp"

#include "mj/ast/MjScope.hpp"


/// @brief There are three kinds of template parameters, type, non-type, and template
enum class MjTemplateParameterType : u8 {
    TYPE,
    VARIABLE,
    TEMPLATE,
};


/// @brief An `MjTemplateParameter` is a parameter of a template definition.
class MjTemplateParameter {
public:


    virtual ~MjTemplateParameter() = default;


    virtual MjTemplateParameterType template_parameter_type() const = 0;
};


/// @brief An `MjTypeTemplateParameter` is a template parameter of type type.
class MjTypeTemplateParameter {
private:
    const MjType &type_;
public:


    ~MjTypeTemplateParameter() = default;


    MjTemplateParameterType template_parameter_type() const {
        return MjTemplateParameterType::TYPE;
    }
};


/// @brief An `MjTemplateArgument` is an argument of a template instantiation or specialization.
class MjTemplateArgument {
public:


    virtual ~MjTemplateArgument() = default;


    virtual MjTemplateParameterType template_parameter_type() const = 0;
};


class MjTemplateName {
private:
    const MjToken &identifier_;
    const Vector<const MjTemplateParameter *> template_parameters_;
public:


    MjTemplateName(
        const MjToken &identifier,
        Vector<const MjTemplateParameter *> template_parameters
    ) :
        identifier_(identifier),
        template_parameters_(template_parameters)
    {}


    const Vector<const MjTemplateParameter *> template_parameters() const {
        return template_parameters_;
    }
};


/// A type consists of a type declaraction and a type definition.
class MjTemplate {
private:

    // Documentation
    MjComment comment_;     // The type documentation comment

    // Tokenization
    const MjToken &name_;        // The type identifier sequence (TODO)

    // Parametrization
    MjTemplate &generic_;     // The generic type or 'None' if not generic
    //generics;    // The generic type parameters of the type or 'None' if not generic
    //generic_contracts; // The required constraints on the generic type parameters derived from the definition
    // generic methods may be explicit or use most specific equivalence for type paramters
    //specializations; // The specializations of this generic type

    // sum<T>(T &a, T &b);
    // sum<u32>(7.4f, 12); // -> <u32>
    // sum(3f32, 10u64);   // -> <f32>

    // Type System Hierarchy
    //base;        // The base type or 'None' if base
    //derived;     // The derived types

    // Members
    // shared;  // static members (variables, functions, types)
    // members; // member variables
    // methods; // member functions (operators)
    // types;   // member types
    // friends; // permissive declarations
    // private;
    // public;
    // permitted; // friends
    // partners; // friends
    // protected;
    // namespace;
    // exposed; // unscoped definitions (inverse of 'friends')

    // First Pass Representation
    // declaration; // The type declaration
public:


    MjTemplate(
        const MjToken &name
    ) :
        name_(name)
    {}


    MjType &specialize() {
        // look for existing definition
        // validate constraints
        // detect most permissive type
        // generate new type
        MjType self;
        return self;
    }
};
