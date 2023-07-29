# Introduction to Armv8 architecture and architecture profiles

The Armv8 architecture has several different profiles. These profiles are variants of the architecture that target different markets and use cases. The Armv8-M architecture is one of these architecture profiles.

Arm defines three architecture profiles: Application (A), Real-time (R), and Microcontroller (M).

## The A profile

- Supports the AArch64 or AArch32 Execution states
- Supports the A64, A32, and T32 instruction sets
- Supports a Virtual Memory System Architecture (VMSA) based on a Memory Management Unit (MMU)

## The R profile

- Supports the AArch64 or AArch32 Execution states
- Supports the A64, or A32 and T32 instruction sets
- Supports a Protected Memory System Architecture (PMSA) with optional support for VMSA at stage 1

## The M profile

- Implements a programmers’ model designed for low-latency interrupt processing, with hardware stacking of registers and support for writing interrupt handlers in high-level languages
- Supports the T32 instruction set
- Supports a Protected Memory System Architecture (PMSA)

## Baseline and Mainline

The Armv8-M architecture contains a baseline architecture feature set and supports several optional extensions to Armv8-M.

- Armv8-M Baseline: The simplest Armv8-M implementation, without any of the optional extensions, is a Baseline implementation.
- Armv8-M Main Extension: An Armv8-M implementation with the Main Extension is also referred to as a Mainline implementation. The Armv8-M Mainline implementation is the Armv8-M Baseline plus the Main Extension.

All Armv8-M implementations, both Baseline and Mainline, are compatible with Armv6-M. However, only Armv8-M Mainline implementations are compatible with Armv7-M.

## Extensions

The Armv8-M architecture supports various optional extensions. The key optional extensions and their abbreviations include the following:

- M - Main Extension
- FP - Floating-point Extension. Enables support for the floating-point unit in an implementation.
- MVE - M-Profile Vector Extension. Enables support for the features that are provided by the Armv8.1 M-Profile Vector Extension (MVE). Armv8-M MVE is also referred to as Arm Helium Technology for Armv8-M.
- MPU - Memory Protection Unit. Enables support for the Memory Protection Unit in an implementation.
- DSP - Digital Signal Processing Extension. Enables a range of instructions for digital signal processing in an implementation.
- DB - Debug Extension. Enables additional debug features in an implementation.
- S - Security Extension. The Armv8-M Security Extension is also referred as TrustZone Technology for Arm Cortex-M processors.
- RAS - Reliability, Availability, and Serviceability Extension. Enables RAS support in an implementation.

## Architecture

The details of the architecture used by Cortex-M processors are defined in the Armv8-M Architecture Reference Manual. For Armv8-M processors, the Armv8-M Architecture Reference Manual provides the specification of the programmer’s model, instruction set, exception model, security architecture and debug architectures. The set of rules outlined in the Armv8-M Architecture Reference Manual outlines the behaviors of each instruction and the support available for debug tools, but not the details of how the processors are implemented.

## Micro-architecture

Each Cortex-M processor has its own implementation level details. For example, the number of pipeline stage, the architectural features supported, the bus protocol used on the processor. High level specifications of the processors are detailed in Technical Reference Manuals. For example, the Cortex-M33 Technical Reference Manual provides the details of the Cortex-M33 processor. Refer to the Cortex-M33 Technical Reference Manual for more details.

## Procedure Call Standard for Arm Architecture (AAPCS)

When a function is written using assembly language and needs to interact with other C codes, there is a range of requirements that need to be followed to allow the interface between software functions to work. These requirements are captured in the Procedure Call Standard for Arm Architecture (AAPCS). Some of the main areas covered by the AAPCS are as follows:

### Register usage in function calls

    Defines the registers that are termed as Caller-saved and Callee-saved. For example, a function call should retain the values in R4-R11. If these registers need to be changed during function call execution, then they should be saved and restored before ending the function call.

### Passing parameters to functions

    The AAPCS defines the registers to use to pass parameters to function calls. The exact registers that are used depends on the number and size of the parameters being passed. For example, in a simple case where there are two integer parameters being passed to a function, then the AAPCS defines that the R0 and R1 registers could be used to pass the two parameters.

### Stack alignment

    If an assembly function needs to call a C function, it should ensure that the current selected stack pointer points to a doubleword-aligned address location.

For more details, see Procedure Call Standard for Arm Architecture.

## Arm C Language Extensions (ACLE)

The Arm architecture includes features that go beyond the set of operations available to C/C++ programmers. The intention of the Arm C Language Extensions (ACLE) is to allow the creation of applications and middleware code that is portable across compilers and across Arm architecture variants while fully utilizing the advanced features of the Arm architecture.

The ACLE standardizes the intrinsics to access Arm instructions which do not map directly to C operators generally either for optimal implementation of algorithms or for accessing special system-level features. The ACLE incorporates some language extensions introduced in the GCC C compiler. The ACLE extends some of the guarantees of C, allowing assumptions to be made in source code beyond those permitted by Standard C.

The ACLE provides details on supported intrinsics, predefined macros, and attributes. Refer to the Arm C Language Extensions for more detailed explanations and information about corresponding architecture features.

## Operational modes and states

The Armv8-M architecture has two operating states and two operating modes. Along with these operating modes and states, the Armv8-M architecture supports privileged and unprivileged access levels. The privileged access level can access all resources in the processor, while the unprivileged access level means some memory regions are inaccessible and a few operations cannot be used.

### Operating states

The two operating states provided by Armv8-M are as follows:

#### Thumb state

    If the processor is running the software program code (Thumb instructions), it is in Thumb state. Armv8-M-based processors do not support A32 instruction set and there is no Arm state.

#### Debug state

    When the processor is halted, for example by a debugger or by hitting a breakpoint, it enters Debug state and stops executing instructions.

Debug state is only used for debugging operations. In Debug state, processor execution is halted and no instructions can be executed by processor. This state is entered by a halt request from the debugger, or by debug events generated from debug components in the processor. This state allows the debugger to access or change the processor register values, peripheral registers, and system memory.

### Operating modes

The two operating modes provided by Armv8-M are as follows:

#### Thread mode

    When executing application code, the processor can be either in privileged access level or unprivileged access level. This is controlled by the special-purpose CONTROL register. Refer to Registers for more information about special-purpose registers. On reset, the processor enters privileged Thread mode in Thumb state. When the processor is executing in Thread mode, it has an option to switch to using a separate banked Stack Pointer (SP). 

#### Handler mode

    When executing an exception handler such as Interrupt Service Routine (ISR), the processor will be in handler mode. When in handler mode, the processor always has privileged access level. 

**Note:** By default, the Cortex-M processors start in privileged Thread mode and in Thumb state. In many simple applications, there is no need to use the unprivileged Thread model and the banked SP at all.

## Privileged and unprivileged execution

In privileged execution, software can use all instructions and has access to all resources. Privileged software can write to the CONTROL register to change from privileged to unprivileged for software execution in Thread mode. However, it cannot switch itself back from unprivileged to privileged.

Within a single security state, only a transition to handler mode can change from unprivileged to privileged execution. In unprivileged mode, software has limited access to instructions that change processor state. It cannot access the system timer, NVIC, or System Control Block, and has restricted access to memory or peripherals that are marked with privileged access only.

The separation of privileged and unprivileged execution allows system designers to give different permissions to different parts of the system. For example, critical sections like the OS kernel can be privileged, while user application tasks are unprivileged. Besides the differences in memory access permissions and access to several special instructions, the programmers’ model of privileged access level and unprivileged access level are almost the same.

## Secure and Non-secure states

When the optional Security Extension is implemented in a processor, there are two new states, the Secure state and the Non-Secure state. The existing thread and handler modes are duplicated between the two security states:

### Secure state

    When the processor is in Secure privileged state, it can access all resources. When the core is in Secure state, it can access both Secure and Non-secure memory. If the Security Extension is implemented in an Armv8-M-based processor, then the processor starts up in Secure, privileged, thread mode. 

### Non-secure state

    When the processor is in Non-secure privileged state, it can gain access to resources subject to security access permissions defined by Secure software (SAU and IDAU). When the core is in Non-secure state, it can only access Non-secure memory. If the Security Extension is not implemented in an Armv8-M-based processor, then there is no Secure state and the processor starts up in Non-secure privileged thread mode.

Note that Security states and privilege modes are orthogonal to each other. Both Secure and Non-Secure state supports privileged and unprivileged levels.

More details on Secure and Non-secure states along with privilege level and operating modes are available in the Armv8-M Security Extension User Guide.

## Registers

Arm is a load/store architecture. When processing data, the processor loads the data into a register from memory, performs data processing operations, and then optionally stores the result back into memory. Armv8-M supports 32-bit registers which enables 32-bit data processing. There are various types of registers supported in the Armv8-M architecture to enable 32-bit data processing. If the Floating-point (FP) or Digital Signal Processing (DSP) extensions are included, then there are some operations that can perform 64-bit data processing.

The various types of registers within the Armv8-M architecture include the following:

- General-purpose registers
- Special-purpose registers
- Memory-mapped registers

The following sections describe each of these different types of registers available within the Armv8-M Architecture.

## Registers in the register bank

There are sixteen 32-bit registers in the register bank, referred to R0-R15. R0-R12 are general-purpose registers used by most of the instructions. R13-R15 have designated usage.

### R0-R12

Registers R0 to R12 are general-purpose registers. The first eight (R0-R7) are also called low registers. Due to the limited number of bits in instruction opcodes, many 16-bit instructions can only access the low registers. The high registers (R8-R12) can be used with 32-bit instructions and with some 16-bit instructions like the MOV instruction. The initial values of R0 to R12 are UNKNOWN out of reset.

### R13, Stack Pointer (SP)

R13 is the Stack Pointer (SP). It is used for accessing the stack memory, for example with PUSH and POP instructions. When the processor pushes new data onto the stack, it decrements the stack pointer and then writes the data to the memory location. Physically, there can be either two or four different stack pointers.

If the Security Extension is not implemented, then there are two stack pointers:

Main stack pointer, commonly referred to as MSP or SP_Main
    The MSP is the default stack pointer used at reset, and is used for all exception handling.
Process stack pointer, commonly referred as PSP or SP_Process
    The PSP is the alternative stack pointer that can only be used in thread mode, and is usually used for application tasks of the operating system (OS).

Stack pointer selection is determined by the special register called CONTROL. The SPSEL field in the CONTROL register can be programmed to select between stack pointers for thread mode stack operations as follows:

    Set SPSEL to 0 to select MSP.
    Set SPSEL to 1 to select PSP.

In normal program execution, only one of these stack pointers will be active. Though both MSP and PSP are 32-bit registers, the lowest two bits of the stack pointers are always zero, and writes to these two bits are ignored. The stack memory operations such as PUSH and POP are always 32-bit. Refer to Stack memory for more information about PUSH and POP operations with stack memory.

If an operating system is used, the stack for each of the application threads will be separated from each other. The PSP enables application threads to switch contexts without affecting the stack used by privileged code. The stack selected on an exception return is based on the SPSEL bit in the EXC_RETURN payload value which is automatically stacked on exception entry. This is shown in the following diagram:

**Warning:**

    Software must never place any data below the current stack pointer position. Stacking on exception entry can occur at any time (for example, in response to an interrupt) and can overwrite any data below the stack pointer.

If the Security Extension is implemented in a system, then there are four stack pointers:

    Main Stack Pointer for Non-secure state (MSP_NS)
    Process Stack Pointer for Non-secure state (PSP_NS)
    Main Stack Pointer for Secure state (MSP_S)
    Process Stack Pointer for Secure state (PSP_S)

The stack pointers are banked when the Security Extension is implemented. In both Secure and Non-secure states, the processor implements the main stack and the process stack, with a pointer for each held in independent registers.
The \_S and \_NS suffixes identify whether the stack pointer is for the Secure state or Non-secure state.

The following table shows which stack pointer is banked between Secure and Non-secure states:

Stack Pointer

Secure State

Non-secure State

Main Stack Pointer

MSP_S

MSP_NS

Process Stack Pointer

PSP_S

PSP_NS
