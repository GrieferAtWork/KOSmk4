/* Copyright (c) 2019-2025 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_ASM_CPU_CPUID_H
#define _I386_KOS_ASM_CPU_CPUID_H 1

#include <hybrid/typecore.h>

/* CPU flags. FORMAT: CPUID_<INPUT_EAX(in HEX)><OUTPUT_E?X>_<NAME>  */

/* cpuid #1 feature bits (https://en.wikipedia.org/wiki/CPUID#EAX.3D1:_Processor_Info_and_Feature_Bits) */
#define CPUID_1A_STEPPING_M      __UINT32_C(0x0000000f) /* Stepping ID */
#define CPUID_1A_STEPPING_S      0                      /* Shift for `CPUID_1A_STEPPING_M' */
#define CPUID_1A_MODEL_M         __UINT32_C(0x000000f0) /* Model ID */
#define CPUID_1A_MODEL_S         4                      /* Shift for `CPUID_1A_MODEL_M' */
#define CPUID_1A_FAMILY_M        __UINT32_C(0x00000f00) /* Family ID */
#define CPUID_1A_FAMILY_S        8                      /* Shift for `CPUID_1A_FAMILY_M' */
#define CPUID_1A_PROCTYPE_M      __UINT32_C(0x00003000) /* Processor Type */
#define CPUID_1A_PROCTYPE_S      12                     /* Shift for `CPUID_1A_PROCTYPE_M' */
#define CPUID_1A_EXMODEL_M       __UINT32_C(0x000f0000) /* Extended Model ID */
#define CPUID_1A_EXMODEL_S       16                     /* Shift for `CPUID_1A_EXMODEL_M' */
#define CPUID_1A_EXFAMILY_M      __UINT32_C(0x0ff00000) /* Extended Family ID */
#define CPUID_1A_EXFAMILY_S      20                     /* Shift for `CPUID_1A_EXFAMILY_M' */


/* TODO: Add more info (s.a. `Vol. 2A   3-213') */
/*[[[begin]]]*/
#define CPUID_1D_FPU             __UINT32_C(0x00000001) /* [bit(EDX:0)] Onboard x87 FPU. */
#define CPUID_1D_VME             __UINT32_C(0x00000002) /* [bit(EDX:1)] Virtual 8086 mode extensions (such as VIF, VIP, PIV). */
#define CPUID_1D_DE              __UINT32_C(0x00000004) /* [bit(EDX:2)] Debugging extensions (CR4 bit 3). */
#define CPUID_1D_PSE             __UINT32_C(0x00000008) /* [bit(EDX:3)] Page Size Extension (allow 4MiB pages). */
#define CPUID_1D_TSC             __UINT32_C(0x00000010) /* [bit(EDX:4)] Time Stamp Counter. */
#define CPUID_1D_MSR             __UINT32_C(0x00000020) /* [bit(EDX:5)] Model-specific registers. */
#define CPUID_1D_PAE             __UINT32_C(0x00000040) /* [bit(EDX:6)] Physical Address Extension. */
#define CPUID_1D_MCE             __UINT32_C(0x00000080) /* [bit(EDX:7)] Machine Check Exception. */
#define CPUID_1D_CX8             __UINT32_C(0x00000100) /* [bit(EDX:8)] CMPXCHG8B (compare-and-swap) instruction. */
#define CPUID_1D_APIC            __UINT32_C(0x00000200) /* [bit(EDX:9)] Onboard Advanced Programmable Interrupt Controller. */
/*      CPUID_1D_                __UINT32_C(0x00000400)  * [bit(EDX:10)] RESERVED. */
#define CPUID_1D_SEP             __UINT32_C(0x00000800) /* [bit(EDX:11)] SYSENTER and SYSEXIT instructions. */
#define CPUID_1D_MTRR            __UINT32_C(0x00001000) /* [bit(EDX:12)] Memory Type Range Registers. */
#define CPUID_1D_PGE             __UINT32_C(0x00002000) /* [bit(EDX:13)] Page Global Enable bit in CR4. */
#define CPUID_1D_MCA             __UINT32_C(0x00004000) /* [bit(EDX:14)] Machine check architecture. */
#define CPUID_1D_CMOV            __UINT32_C(0x00008000) /* [bit(EDX:15)] Conditional move and FCMOV instructions. */
#define CPUID_1D_PAT             __UINT32_C(0x00010000) /* [bit(EDX:16)] Page Attribute Table. */
#define CPUID_1D_PSE36           __UINT32_C(0x00020000) /* [bit(EDX:17)] 36-bit page size extension. */
#define CPUID_1D_PSN             __UINT32_C(0x00040000) /* [bit(EDX:18)] Processor Serial Number. */
#define CPUID_1D_CLFSH           __UINT32_C(0x00080000) /* [bit(EDX:19)] CLFLUSH instruction (SSE2). */
/*      CPUID_1D_                __UINT32_C(0x00100000)  * [bit(EDX:20)] RESERVED. */
#define CPUID_1D_DS              __UINT32_C(0x00200000) /* [bit(EDX:21)] Debug store: save trace of executed jumps. */
#define CPUID_1D_ACPI            __UINT32_C(0x00400000) /* [bit(EDX:22)] Onboard thermal control MSRs for ACPI. */
#define CPUID_1D_MMX             __UINT32_C(0x00800000) /* [bit(EDX:23)] MMX instructions. */
#define CPUID_1D_FXSR            __UINT32_C(0x01000000) /* [bit(EDX:24)] FXSAVE, FXRESTOR instructions, CR4 bit 9. */
#define CPUID_1D_SSE             __UINT32_C(0x02000000) /* [bit(EDX:25)] SSE instructions (a.k.a. Katmai New Instructions). */
#define CPUID_1D_SSE2            __UINT32_C(0x04000000) /* [bit(EDX:26)] SSE2 instructions. */
#define CPUID_1D_SS              __UINT32_C(0x08000000) /* [bit(EDX:27)] CPU cache supports self-snoop. */
#define CPUID_1D_HTT             __UINT32_C(0x10000000) /* [bit(EDX:28)] Hyper-threading. */
#define CPUID_1D_TM              __UINT32_C(0x20000000) /* [bit(EDX:29)] Thermal monitor automatically limits temperature. */
#define CPUID_1D_IA64            __UINT32_C(0x40000000) /* [bit(EDX:30)] IA64 processor emulating x86. */
#define CPUID_1D_PBE             __UINT32_C(0x80000000) /* [bit(EDX:31)] Pending Break Enable (PBE# pin) wakeup support. */
#define CPUID_1C_SSE3            __UINT32_C(0x00000001) /* [bit(ECX:0)] Prescott New Instructions-SSE3 (PNI). */
#define CPUID_1C_PCLMULQDQ       __UINT32_C(0x00000002) /* [bit(ECX:1)] PCLMULQDQ support. */
#define CPUID_1C_DTES64          __UINT32_C(0x00000004) /* [bit(ECX:2)] 64-bit debug store (edx bit 21). */
#define CPUID_1C_MONITOR         __UINT32_C(0x00000008) /* [bit(ECX:3)] MONITOR and MWAIT instructions (SSE3). */
#define CPUID_1C_DS_CPL          __UINT32_C(0x00000010) /* [bit(ECX:4)] CPL qualified debug store. */
#define CPUID_1C_VMX             __UINT32_C(0x00000020) /* [bit(ECX:5)] Virtual Machine eXtensions. */
#define CPUID_1C_SMX             __UINT32_C(0x00000040) /* [bit(ECX:6)] Safer Mode Extensions (LaGrande). */
#define CPUID_1C_EST             __UINT32_C(0x00000080) /* [bit(ECX:7)] Enhanced SpeedStep. */
#define CPUID_1C_TM2             __UINT32_C(0x00000100) /* [bit(ECX:8)] Thermal Monitor 2. */
#define CPUID_1C_SSSE3           __UINT32_C(0x00000200) /* [bit(ECX:9)] Supplemental SSE3 instructions. */
#define CPUID_1C_CNXT_ID         __UINT32_C(0x00000400) /* [bit(ECX:10)] L1 Context ID. */
#define CPUID_1C_SDBG            __UINT32_C(0x00000800) /* [bit(ECX:11)] Silicon Debug interface. */
#define CPUID_1C_FMA             __UINT32_C(0x00001000) /* [bit(ECX:12)] Fused multiply-add (FMA3). */
#define CPUID_1C_CX16            __UINT32_C(0x00002000) /* [bit(ECX:13)] CMPXCHG16B instruction. */
#define CPUID_1C_XTPR            __UINT32_C(0x00004000) /* [bit(ECX:14)] Can disable sending task priority messages. */
#define CPUID_1C_PDCM            __UINT32_C(0x00008000) /* [bit(ECX:15)] Perfmon & debug capability. */
/*      CPUID_1C_                __UINT32_C(0x00010000)  * [bit(ECX:16)] RESERVED. */
#define CPUID_1C_PCID            __UINT32_C(0x00020000) /* [bit(ECX:17)] Process context identifiers (CR4 bit 17). */
#define CPUID_1C_DCA             __UINT32_C(0x00040000) /* [bit(ECX:18)] Direct cache access for DMA writes[12][13]. */
#define CPUID_1C_SSE4_1          __UINT32_C(0x00080000) /* [bit(ECX:19)] SSE4.1 instructions. */
#define CPUID_1C_SSE4_2          __UINT32_C(0x00100000) /* [bit(ECX:20)] SSE4.2 instructions. */
#define CPUID_1C_X2APIC          __UINT32_C(0x00200000) /* [bit(ECX:21)] x2APIC support. */
#define CPUID_1C_MOVBE           __UINT32_C(0x00400000) /* [bit(ECX:22)] MOVBE instruction (big-endian). */
#define CPUID_1C_POPCNT          __UINT32_C(0x00800000) /* [bit(ECX:23)] POPCNT instruction. */
#define CPUID_1C_TSC_DEADLINE    __UINT32_C(0x01000000) /* [bit(ECX:24)] APIC supports one-shot operation using a TSC deadline value. */
#define CPUID_1C_AES             __UINT32_C(0x02000000) /* [bit(ECX:25)] AES instruction set. */
#define CPUID_1C_XSAVE           __UINT32_C(0x04000000) /* [bit(ECX:26)] XSAVE, XRESTOR, XSETBV, XGETBV. */
#define CPUID_1C_OSXSAVE         __UINT32_C(0x08000000) /* [bit(ECX:27)] XSAVE enabled by OS. */
#define CPUID_1C_AVX             __UINT32_C(0x10000000) /* [bit(ECX:28)] Advanced Vector Extensions. */
#define CPUID_1C_F16C            __UINT32_C(0x20000000) /* [bit(ECX:29)] F16C (half-precision) FP support. */
#define CPUID_1C_RDRAND          __UINT32_C(0x40000000) /* [bit(ECX:30)] RDRAND (on-chip random number generator) support. */
#define CPUID_1C_HYPERVISOR      __UINT32_C(0x80000000) /* [bit(ECX:31)] Running on a hypervisor (always 0 on a real CPU, but also with some hypervisors). */

/*      CPUID_7D_                __UINT32_C(0x00000001)  * [bit(0)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00000002)  * [bit(1)] RESERVED. */
#define CPUID_7D_AVX512_4VNNIW   __UINT32_C(0x00000004) /* [bit(2)] AVX-512 4-register Neural Network Instructions. */
#define CPUID_7D_AVX512_4FMAPS   __UINT32_C(0x00000008) /* [bit(3)] AVX-512 4-register Multiply Accumulation Single precision. */
/*      CPUID_7D_                __UINT32_C(0x00000010)  * [bit(4)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00000020)  * [bit(5)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00000040)  * [bit(6)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00000080)  * [bit(7)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00000100)  * [bit(8)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00000200)  * [bit(9)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00000400)  * [bit(10)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00000800)  * [bit(11)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00001000)  * [bit(12)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00002000)  * [bit(13)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00004000)  * [bit(14)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00008000)  * [bit(15)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00010000)  * [bit(16)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00020000)  * [bit(17)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00040000)  * [bit(18)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00080000)  * [bit(19)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00100000)  * [bit(20)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00200000)  * [bit(21)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00400000)  * [bit(22)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x00800000)  * [bit(23)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x01000000)  * [bit(24)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x02000000)  * [bit(25)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x04000000)  * [bit(26)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x08000000)  * [bit(27)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x10000000)  * [bit(28)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x20000000)  * [bit(29)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x40000000)  * [bit(30)] RESERVED. */
/*      CPUID_7D_                __UINT32_C(0x80000000)  * [bit(31)] RESERVED. */
#define CPUID_7C_PREFETCHWT1     __UINT32_C(0x00000001) /* [bit(0)] PREFETCHWT1 instruction. */
#define CPUID_7C_AVX512VBMI      __UINT32_C(0x00000002) /* [bit(1)] AVX-512 Vector Bit Manipulation Instructions. */
#define CPUID_7C_UMIP            __UINT32_C(0x00000004) /* [bit(2)] User-mode Instruction Prevention. */
#define CPUID_7C_PKU             __UINT32_C(0x00000008) /* [bit(3)] Memory Protection Keys for User-mode pages. */
#define CPUID_7C_OSPKE           __UINT32_C(0x00000010) /* [bit(4)] PKU enabled by OS. */
/*      CPUID_7C_                __UINT32_C(0x00000020)  * [bit(5)] RESERVED. */
#define CPUID_7C_AVX512VBMI2     __UINT32_C(0x00000040) /* [bit(6)] AVX-512 Vector Bit Manipulation Instructions 2. */
/*      CPUID_7C_                __UINT32_C(0x00000080)  * [bit(7)] RESERVED. */
#define CPUID_7C_GFNI            __UINT32_C(0x00000100) /* [bit(8)] Galois Field instructions. */
#define CPUID_7C_VAES            __UINT32_C(0x00000200) /* [bit(9)] AES instruction set (VEX-256/EVEX). */
#define CPUID_7C_VPCLMULQDQ      __UINT32_C(0x00000400) /* [bit(10)] CLMUL instruction set (VEX-256/EVEX). */
#define CPUID_7C_AVX512VNNI      __UINT32_C(0x00000800) /* [bit(11)] AVX-512 Vector Neural Network Instructions. */
#define CPUID_7C_AVX512BITALG    __UINT32_C(0x00001000) /* [bit(12)] AVX-512 BITALG instructions. */
/*      CPUID_7C_                __UINT32_C(0x00002000)  * [bit(13)] RESERVED. */
#define CPUID_7C_AVX512VPOPCNTDQ __UINT32_C(0x00004000) /* [bit(14)] AVX-512 Vector Population Count D/Q. */
/*      CPUID_7C_                __UINT32_C(0x00008000)  * [bit(15)] RESERVED. */
/*      CPUID_7C_                __UINT32_C(0x00010000)  * [bit(16)] RESERVED. */
#define CPUID_7C_MAWAU           __UINT32_C(0x003e0000) /* [bit(17...21)] The value of userspace MPX Address-Width Adjust used by
                                 __UINT32_C(          )  *                the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode. */
#define CPUID_7C_RDPID           __UINT32_C(0x00400000) /* [bit(22)] Read Processor ID. */
/*      CPUID_7C_                __UINT32_C(0x00800000)  * [bit(23)] RESERVED. */
/*      CPUID_7C_                __UINT32_C(0x01000000)  * [bit(24)] RESERVED. */
/*      CPUID_7C_                __UINT32_C(0x02000000)  * [bit(25)] RESERVED. */
/*      CPUID_7C_                __UINT32_C(0x04000000)  * [bit(26)] RESERVED. */
/*      CPUID_7C_                __UINT32_C(0x08000000)  * [bit(27)] RESERVED. */
/*      CPUID_7C_                __UINT32_C(0x10000000)  * [bit(28)] RESERVED. */
/*      CPUID_7C_                __UINT32_C(0x20000000)  * [bit(29)] RESERVED. */
#define CPUID_7C_SGX_LC          __UINT32_C(0x40000000) /* [bit(30)] SGX Launch Configuration. */
/*      CPUID_7C_                __UINT32_C(0x80000000)  * [bit(31)] RESERVED. */
#define CPUID_7B_FSGSBASE        __UINT32_C(0x00000001) /* [bit(0)] Access to base of %fs and %gs. */
#define CPUID_7B_IA32_TSC_ADJUST __UINT32_C(0x00000002) /* [bit(1)] IA32_TSC_ADJUST. */
#define CPUID_7B_SGX             __UINT32_C(0x00000004) /* [bit(2)] Software Guard Extensions. */
#define CPUID_7B_BMI1            __UINT32_C(0x00000008) /* [bit(3)] Bit Manipulation Instruction Set 1. */
#define CPUID_7B_HLE             __UINT32_C(0x00000010) /* [bit(4)] Transactional Synchronization Extensions. */
#define CPUID_7B_AVX2            __UINT32_C(0x00000020) /* [bit(5)] Advanced Vector Extensions 2. */
/*      CPUID_7B_                __UINT32_C(0x00000040)  * [bit(6)] RESERVED. */
#define CPUID_7B_SMEP            __UINT32_C(0x00000080) /* [bit(7)] Supervisor-Mode Execution Prevention. */
#define CPUID_7B_BMI2            __UINT32_C(0x00000100) /* [bit(8)] Bit Manipulation Instruction Set 2. */
#define CPUID_7B_ERMS            __UINT32_C(0x00000200) /* [bit(9)] Enhanced REP MOVSB/STOSB. */
#define CPUID_7B_INVPCID         __UINT32_C(0x00000400) /* [bit(10)] INVPCID instruction. */
#define CPUID_7B_RTM             __UINT32_C(0x00000800) /* [bit(11)] Transactional Synchronization Extensions. */
#define CPUID_7B_PQM             __UINT32_C(0x00001000) /* [bit(12)] Platform Quality of Service Monitoring. */
#define CPUID_7B_FPU             __UINT32_C(0x00002000) /* [bit(13)] CS and FPU DS deprecated. */
#define CPUID_7B_MPX             __UINT32_C(0x00004000) /* [bit(14)] Intel MPX (Memory Protection Extensions). */
#define CPUID_7B_PQE             __UINT32_C(0x00008000) /* [bit(15)] Platform Quality of Service Enforcement. */
#define CPUID_7B_AVX512F         __UINT32_C(0x00010000) /* [bit(16)] AVX-512 Foundation. */
#define CPUID_7B_AVX512DQ        __UINT32_C(0x00020000) /* [bit(17)] AVX-512 Doubleword and Quadword Instructions. */
#define CPUID_7B_RDSEED          __UINT32_C(0x00040000) /* [bit(18)] RDSEED instruction. */
#define CPUID_7B_ADX             __UINT32_C(0x00080000) /* [bit(19)] Intel ADX (Multi-Precision Add-Carry Instruction Extensions). */
#define CPUID_7B_SMAP            __UINT32_C(0x00100000) /* [bit(20)] Supervisor Mode Access Prevention. */
#define CPUID_7B_AVX512IFMA      __UINT32_C(0x00200000) /* [bit(21)] AVX-512 Integer Fused Multiply-Add Instructions. */
#define CPUID_7B_PCOMMIT         __UINT32_C(0x00400000) /* [bit(22)] PCOMMIT instruction. */
#define CPUID_7B_CLFLUSHOPT      __UINT32_C(0x00800000) /* [bit(23)] CLFLUSHOPT instruction. */
#define CPUID_7B_CLWB            __UINT32_C(0x01000000) /* [bit(24)] CLWB instruction. */
#define CPUID_7B_INTEL_PT        __UINT32_C(0x02000000) /* [bit(25)] Intel Processor Trace. */
#define CPUID_7B_AVX512PF        __UINT32_C(0x04000000) /* [bit(26)] AVX-512 Prefetch Instructions. */
#define CPUID_7B_AVX512ER        __UINT32_C(0x08000000) /* [bit(27)] AVX-512 Exponential and Reciprocal Instructions. */
#define CPUID_7B_AVX512CD        __UINT32_C(0x10000000) /* [bit(28)] AVX-512 Conflict Detection Instructions. */
#define CPUID_7B_SHA             __UINT32_C(0x20000000) /* [bit(29)] Intel SHA extensions. */
#define CPUID_7B_AVX512BW        __UINT32_C(0x40000000) /* [bit(30)] AVX-512 Byte and Word Instructions. */
#define CPUID_7B_AVX512VL        __UINT32_C(0x80000000) /* [bit(31)] AVX-512 Vector Length Extensions. */


#define CPUID_80000001C_LAHF_LM       __UINT32_C(0x00000001) /* [bit(0)] LAHF/SAHF in long mode. */
#define CPUID_80000001C_CMP_LEGACY    __UINT32_C(0x00000002) /* [bit(1)] Hyperthreading not valid. */
#define CPUID_80000001C_SVM           __UINT32_C(0x00000004) /* [bit(2)] Secure Virtual Machine. */
#define CPUID_80000001C_EXTAPIC       __UINT32_C(0x00000008) /* [bit(3)] Extended APIC space. */
#define CPUID_80000001C_CR8_LEGACY    __UINT32_C(0x00000010) /* [bit(4)] CR8 in 32-bit mode. */
#define CPUID_80000001C_ABM           __UINT32_C(0x00000020) /* [bit(5)] Advanced bit manipulation (lzcnt and popcnt). */
#define CPUID_80000001C_SSE4A         __UINT32_C(0x00000040) /* [bit(6)] SSE4a. */
#define CPUID_80000001C_MISALIGNSSE   __UINT32_C(0x00000080) /* [bit(7)] Misaligned SSE mode. */
#define CPUID_80000001C_3DNOWPREFETCH __UINT32_C(0x00000100) /* [bit(8)] PREFETCH and PREFETCHW instructions. */
#define CPUID_80000001C_OSVW          __UINT32_C(0x00000200) /* [bit(9)] OS Visible Workaround. */
#define CPUID_80000001C_IBS           __UINT32_C(0x00000400) /* [bit(10)] Instruction Based Sampling. */
#define CPUID_80000001C_XOP           __UINT32_C(0x00000800) /* [bit(11)] XOP instruction set. */
#define CPUID_80000001C_SKINIT        __UINT32_C(0x00001000) /* [bit(12)] SKINIT/STGI instructions. */
#define CPUID_80000001C_WDT           __UINT32_C(0x00002000) /* [bit(13)] Watchdog timer. */
/*      CPUID_80000001C_              __UINT32_C(0x00004000)  * [bit(14)] RESERVED. */
#define CPUID_80000001C_LWP           __UINT32_C(0x00008000) /* [bit(15)] Light Weight Profiling[23]. */
#define CPUID_80000001C_FMA4          __UINT32_C(0x00010000) /* [bit(16)] 4 operands fused multiply-add. */
#define CPUID_80000001C_TCE           __UINT32_C(0x00020000) /* [bit(17)] Translation Cache Extension. */
/*      CPUID_80000001C_              __UINT32_C(0x00040000)  * [bit(18)] RESERVED. */
#define CPUID_80000001C_NODEID_MSR    __UINT32_C(0x00080000) /* [bit(19)] NodeID MSR. */
/*      CPUID_80000001C_              __UINT32_C(0x00100000)  * [bit(20)] RESERVED. */
#define CPUID_80000001C_TBM           __UINT32_C(0x00200000) /* [bit(21)] Trailing Bit Manipulation. */
#define CPUID_80000001C_TOPOEXT       __UINT32_C(0x00400000) /* [bit(22)] Topology Extensions. */
#define CPUID_80000001C_PERFCTR_CORE  __UINT32_C(0x00800000) /* [bit(23)] Core performance counter extensions. */
#define CPUID_80000001C_PERFCTR_NB    __UINT32_C(0x01000000) /* [bit(24)] NB performance counter extensions. */
/*      CPUID_80000001C_              __UINT32_C(0x02000000)  * [bit(25)] RESERVED. */
#define CPUID_80000001C_DBX           __UINT32_C(0x04000000) /* [bit(26)] Data breakpoint extensions. */
#define CPUID_80000001C_PERFTSC       __UINT32_C(0x08000000) /* [bit(27)] Performance TSC. */
#define CPUID_80000001C_PCX_L2I       __UINT32_C(0x10000000) /* [bit(28)] L2I perf counter extensions. */
/*      CPUID_80000001C_              __UINT32_C(0x20000000)  * [bit(29)] RESERVED. */
/*      CPUID_80000001C_              __UINT32_C(0x40000000)  * [bit(30)] RESERVED. */
/*      CPUID_80000001C_              __UINT32_C(0x80000000)  * [bit(31)] RESERVED. */
#define CPUID_80000001D_FPU           CPUID_1D_FPU           /* [bit(0)] Onboard x87 FPU. */
#define CPUID_80000001D_VME           CPUID_1D_VME           /* [bit(1)] Virtual mode extensions (VIF). */
#define CPUID_80000001D_DE            CPUID_1D_DE            /* [bit(2)] Debugging extensions (CR4 bit 3). */
#define CPUID_80000001D_PSE           CPUID_1D_PSE           /* [bit(3)] Page Size Extension (allow 4MiB pages). */
#define CPUID_80000001D_TSC           CPUID_1D_TSC           /* [bit(4)] Time Stamp Counter. */
#define CPUID_80000001D_MSR           CPUID_1D_MSR           /* [bit(5)] Model-specific registers. */
#define CPUID_80000001D_PAE           CPUID_1D_PAE           /* [bit(6)] Physical Address Extension. */
#define CPUID_80000001D_MCE           CPUID_1D_MCE           /* [bit(7)] Machine Check Exception. */
#define CPUID_80000001D_CX8           CPUID_1D_CX8           /* [bit(8)] CMPXCHG8B (compare-and-swap) instruction. */
#define CPUID_80000001D_APIC          CPUID_1D_APIC          /* [bit(9)] Onboard Advanced Programmable Interrupt Controller. */
/*      CPUID_80000001D_              __UINT32_C(0x00000400)  * [bit(10)] RESERVED. */
#define CPUID_80000001D_SYSCALL       __UINT32_C(0x00000800) /* [bit(11)] SYSCALL and SYSRET instructions. */
#define CPUID_80000001D_MTRR          CPUID_1D_MTRR          /* [bit(12)] Memory Type Range Registers. */
#define CPUID_80000001D_PGE           CPUID_1D_PGE           /* [bit(13)] Page Global Enable bit in CR4. */
#define CPUID_80000001D_MCA           CPUID_1D_MCA           /* [bit(14)] Machine check architecture. */
#define CPUID_80000001D_CMOV          CPUID_1D_CMOV          /* [bit(15)] Conditional move and FCMOV instructions. */
#define CPUID_80000001D_PAT           CPUID_1D_PAT           /* [bit(16)] Page Attribute Table. */
#define CPUID_80000001D_PSE36         CPUID_1D_PSE36         /* [bit(17)] 36-bit page size extension (for 4MiB pages). */
/*      CPUID_80000001D_              __UINT32_C(0x00040000)  * [bit(18)] RESERVED. */
#define CPUID_80000001D_MP            __UINT32_C(0x00080000) /* [bit(19)] Multiprocessor Capable. */
#define CPUID_80000001D_NX            __UINT32_C(0x00100000) /* [bit(20)] NX bit. */
/*      CPUID_80000001D_              __UINT32_C(0x00200000)  * [bit(21)] RESERVED. */
#define CPUID_80000001D_MMXEXT        __UINT32_C(0x00400000) /* [bit(22)] Extended MMX. */
#define CPUID_80000001D_MMX           CPUID_1D_MMX           /* [bit(23)] MMX instructions. */
#define CPUID_80000001D_FXSR          CPUID_1D_FXSR          /* [bit(24)] FXSAVE, FXRSTOR instructions, CR4 bit 9. */
#define CPUID_80000001D_FXSR_OPT      __UINT32_C(0x02000000) /* [bit(25)] FXSAVE/FXRSTOR optimizations. */
#define CPUID_80000001D_PDPE1GB       __UINT32_C(0x04000000) /* [bit(26)] Gibabyte pages. */
#define CPUID_80000001D_RDTSCP        __UINT32_C(0x08000000) /* [bit(27)] RDTSCP instruction. */
/*      CPUID_80000001D_              __UINT32_C(0x10000000)  * [bit(28)] RESERVED. */
#define CPUID_80000001D_LM            __UINT32_C(0x20000000) /* [bit(29)] Long mode. */
#define CPUID_80000001D_3DNOWEXT      __UINT32_C(0x40000000) /* [bit(30)] Extended 3DNow. */
#define CPUID_80000001D_3DNOW         __UINT32_C(0x80000000) /* [bit(31)] 3DNow!. */
#define CPUID_80000007D_INVARIANT_TSC __UINT32_C(0x00000100) /* [bit(EDX:8)] The TSC's increment speed is invariant. */
/*[[[end]]]*/



#endif /* !_I386_KOS_ASM_CPU_CPUID_H */
