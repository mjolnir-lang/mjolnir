# Architectures

This library contains all supported target platform architectures.

Each module provides the necessary compiler front/back-end extentions
and CPU registers and assembly instructions needed for high level
inline assembly analysis.

Every module represents a distinct Instruction Set Architecture (ISA).

ARM has many revisions of its ISA.

Every processor maps to exactly one ISA, and may have more than one core.

Every target has at least one processor.

Information about each platform addressing, peripherals, ISA, cores, and such should be exposed to the compiler
in the target platfor configuration.

This will allow cross compilation, analysis, and simulation of any architecture.

The compiler will download and compile the target platform extention and link against it at runtime
as needed.
