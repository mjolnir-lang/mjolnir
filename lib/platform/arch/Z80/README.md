# Zilog 80 Instruction Set Architecture (Z80 ISA)

Mjolnir Code
Mjolnir AST
Mjolnir IR

Z80 Assembly Code
Z80 Assembly AST
Z80 Machine Code

## Assembler/Disassembler

Translates between Z80 machine code and Z80 assembly AST.

## Compiler/Decompiler

Compiler/Decompiler back-end for the Mjolnir compiler front-end.

Translates Mjolnir IR into Z80 assembly AST.

## Printer/Parser

Prints Z80 assembly AST.

## Instruction Notation Summary

| Notation | Description |
| --- | --- |
| `r` | Identifies any of the registers `A`, `B`, `C`, `D`, `E`, `H`, or `L` |
| `(HL)` | Identifies the contents of the memory location, whose address is specified by the contents of the register pair `HL` |
| `(IX+d)` | Identifies the contents of the memory location, whose address is specified by the contents of the Index register pair `IX` plus the signed displacement `d` |
| `(IY+d)` | Identifies the contents of the memory location, whose address is specified by the contents of the Index register pair `IY` plus the signed displacement `d` |
| `n` | Identifies a one-byte unsigned integer expression in the range (0 to 255) |
| `nn` | Identifies a two-byte unsigned integer expression in the range (0 to 65535) |
| `d` | Identifies a one-byte signed integer expression in the range ( -128 to +127) |
| `b` | Identifies a one-bit expression in the range (0 to 7). The most-significant bit to the left is bit 7 and the least-significant bit to the right is bit 0 |
| `e` | Identifies a one-byte signed integer expression in the range (-126 to +129) for relative jump offset from current location |
| `cc` | Identifies the status of the Flag Register as any of (`NZ`, `Z`, `NC`, `C`, `PO`, `PE`, `P`, or `M`) for the conditional jumps, calls, and return instructions
| `qq` | Identifies any of the register pairs `BC`, `DE`, `HL` or `AF` |
| `ss` | Identifies any of the register pairs `BC`, `DE`, `HL` or `SP` |
| `pp` | Identifies any of the register pairs `BC`, `DE`, `IX` or `SP` |
| `rr` | Identifies any of the register pairs `BC`, `DE`, `IY` or `SP` |
| `s` | Identifies any of `r`, `n`, `(HL)`, `(IX+d)` or `(IY+d)` |
| `m` | Identifies any of `r`, `(HL)`, `(IX+d)` or `(IY+d)` |
