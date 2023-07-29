#pragma once

#include "mj/ast/MjTemplate.hpp"


class MjFunctionTemplate : public MjTemplate {


    MjFunctionTemplate(
        List<MjType> params
    ) :
        MjTemplate(name)
    {}
};