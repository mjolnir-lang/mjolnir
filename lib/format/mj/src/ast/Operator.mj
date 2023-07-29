#pragma once

#include "mj/ast/MjToken.hpp"


struct MjOperator {
    static const MjOperator SCOPE; // _::_
    static const MjOperator INC; // _++
    static const MjOperator DEC; // _--
    static const MjOperator CALL; // _(_)
    static const MjOperator SUBSCRIPT; // _[_]
    static const MjOperator DOT; // _._
    static const MjOperator PTR; // _->_
    static const MjOperator PRE_INC; // ++_
    static const MjOperator PRE_DEC; // --_
    static const MjOperator INV; // ~_
    static const MjOperator NOT; // !_
    static const MjOperator POS; // +_
    static const MjOperator NEG; // -_
    static const MjOperator REF; // &_
    static const MjOperator DEREF; // *_
    static const MjOperator CAST; // (_)_
    static const MjOperator MUL; // _*_
    static const MjOperator DIV; // _/_
    static const MjOperator MOD; // _%_
    static const MjOperator ADD; // _+_
    static const MjOperator SUB; // _-_
    static const MjOperator LSL; // _<<_
    static const MjOperator ASR; // _>>_
    static const MjOperator LSR; // _>>>_
    static const MjOperator LES; // _<_
    static const MjOperator GTR; // _>_
    static const MjOperator LEQ; // _<=_
    static const MjOperator GEQ; // _>=_
    static const MjOperator EQU; // _==_
    static const MjOperator NEQ; // _!=_
    static const MjOperator AND; // _&_
    static const MjOperator XOR; // _^_
    static const MjOperator OR; // _|_
    static const MjOperator LAND; // _&&_
    static const MjOperator LXOR; // _^^_
    static const MjOperator LOR; // _||_
    static const MjOperator SET; // _=_
    static const MjOperator MUL_SET; // _*=_
    static const MjOperator DIV_SET; // _/=_
    static const MjOperator MOD_SET; // _%=_
    static const MjOperator ADD_SET; // _+=_
    static const MjOperator SUB_SET; // _-=_
    static const MjOperator LSL_SET; // _>>=_
    static const MjOperator ASR_SET; // _<<=_
    static const MjOperator LSR_SET; // _>>>=_
    static const MjOperator AND_SET; // _&=_
    static const MjOperator XOR_SET; // _^=_
    static const MjOperator OR_SET; // _|=_
    static const MjOperator TERNARY; // _?_:_
    static const MjOperator COMMA; // _,_

    const MjToken &name; // The operator name
    const u32 lbp;       // The left hand operand binding power
    const u32 rbp;       // The right hand operand binding power


    MjOperator(
        const MjToken &name,
        u32 lbp,
        u32 rbp
    ) :
        name(name),
        lbp(lbp),
        rbp(rbp)
    {}
};
