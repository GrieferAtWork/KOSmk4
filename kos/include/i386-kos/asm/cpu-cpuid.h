/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_ASM_CPU_CPUID_H
#define _I386_KOS_ASM_CPU_CPUID_H 1

/* CPU flags. FORMAT: CPUID_<INPUT_EAX(in HEX)><OUTPUT_E?X>_<NAME>  */

/* cpuid #1 feature bits (https://en.wikipedia.org/wiki/CPUID#EAX.3D1:_Processor_Info_and_Feature_Bits) */
#define CPUID_1A_STEPPING_M      0x0000000f /* Stepping ID */
#define CPUID_1A_STEPPING_S               0 /* Shift for `CPUID_1A_STEPPING_M' */
#define CPUID_1A_MODEL_M         0x000000f0 /* Model ID */
#define CPUID_1A_MODEL_S                  4 /* Shift for `CPUID_1A_MODEL_M' */
#define CPUID_1A_FAMILY_M        0x00000f00 /* Family ID */
#define CPUID_1A_FAMILY_S                 8 /* Shift for `CPUID_1A_FAMILY_M' */
#define CPUID_1A_PROCTYPE_M      0x00003000 /* Processor Type */
#define CPUID_1A_PROCTYPE_S              12 /* Shift for `CPUID_1A_PROCTYPE_M' */
#define CPUID_1A_EXMODEL_M       0x000f0000 /* Extended Model ID */
#define CPUID_1A_EXMODEL_S               16 /* Shift for `CPUID_1A_EXMODEL_M' */
#define CPUID_1A_EXFAMILY_M      0x0ff00000 /* Extended Family ID */
#define CPUID_1A_EXFAMILY_S              20 /* Shift for `CPUID_1A_EXFAMILY_M' */


/* TODO: Add more info (s.a. `Vol. 2A   3-213') */

#define CPUID_1D_FPU             0x00000001 /* [bit(EDX:0)] Onboard x87 FPU. */
#define CPUID_1D_VME             0x00000002 /* [bit(EDX:1)] Virtual 8086 mode extensions (such as VIF, VIP, PIV). */
#define CPUID_1D_DE              0x00000004 /* [bit(EDX:2)] Debugging extensions (CR4 bit 3). */
#define CPUID_1D_PSE             0x00000008 /* [bit(EDX:3)] Page Size Extension (allow 4MiB pages). */
#define CPUID_1D_TSC             0x00000010 /* [bit(EDX:4)] Time Stamp Counter. */
#define CPUID_1D_MSR             0x00000020 /* [bit(EDX:5)] Model-specific registers. */
#define CPUID_1D_PAE             0x00000040 /* [bit(EDX:6)] Physical Address Extension. */
#define CPUID_1D_MCE             0x00000080 /* [bit(EDX:7)] Machine Check Exception. */
#define CPUID_1D_CX8             0x00000100 /* [bit(EDX:8)] CMPXCHG8 (compare-and-swap) instruction. */
#define CPUID_1D_APIC            0x00000200 /* [bit(EDX:9)] Onboard Advanced Programmable Interrupt Controller. */
/*      CPUID_1D_                0x00000400 /* [bit(EDX:10)] RESERVED. */
#define CPUID_1D_SEP             0x00000800 /* [bit(EDX:11)] SYSENTER and SYSEXIT instructions. */
#define CPUID_1D_MTRR            0x00001000 /* [bit(EDX:12)] Memory Type Range Registers. */
#define CPUID_1D_PGE             0x00002000 /* [bit(EDX:13)] Page Global Enable bit in CR4. */
#define CPUID_1D_MCA             0x00004000 /* [bit(EDX:14)] Machine check architecture. */
#define CPUID_1D_CMOV            0x00008000 /* [bit(EDX:15)] Conditional move and FCMOV instructions. */
#define CPUID_1D_PAT             0x00010000 /* [bit(EDX:16)] Page Attribute Table. */
#define CPUID_1D_PSE_36          0x00020000 /* [bit(EDX:17)] 36-bit page size extension. */
#define CPUID_1D_PSN             0x00040000 /* [bit(EDX:18)] Processor Serial Number. */
#define CPUID_1D_CLFSH           0x00080000 /* [bit(EDX:19)] CLFLUSH instruction (SSE2). */
/*      CPUID_1D_                0x00100000 /* [bit(EDX:20)] RESERVED. */
#define CPUID_1D_DS              0x00200000 /* [bit(EDX:21)] Debug store: save trace of executed jumps. */
#define CPUID_1D_ACPI            0x00400000 /* [bit(EDX:22)] Onboard thermal control MSRs for ACPI. */
#define CPUID_1D_MMX             0x00800000 /* [bit(EDX:23)] MMX instructions. */
#define CPUID_1D_FXSR            0x01000000 /* [bit(EDX:24)] FXSAVE, FXRESTOR instructions, CR4 bit 9. */
#define CPUID_1D_SSE             0x02000000 /* [bit(EDX:25)] SSE instructions (a.k.a. Katmai New Instructions). */
#define CPUID_1D_SSE2            0x04000000 /* [bit(EDX:26)] SSE2 instructions. */
#define CPUID_1D_SS              0x08000000 /* [bit(EDX:27)] CPU cache supports self-snoop. */
#define CPUID_1D_HTT             0x10000000 /* [bit(EDX:28)] Hyper-threading. */
#define CPUID_1D_TM              0x20000000 /* [bit(EDX:29)] Thermal monitor automatically limits temperature. */
#define CPUID_1D_IA64            0x40000000 /* [bit(EDX:30)] IA64 processor emulating x86. */
#define CPUID_1D_PBE             0x80000000 /* [bit(EDX:31)] Pending Break Enable (PBE# pin) wakeup support. */
#define CPUID_1C_SSE3            0x00000001 /* [bit(ECX:0)] Prescott New Instructions-SSE3 (PNI). */
#define CPUID_1C_PCLMULQDQ       0x00000002 /* [bit(ECX:1)] PCLMULQDQ support. */
#define CPUID_1C_DTES64          0x00000004 /* [bit(ECX:2)] 64-bit debug store (edx bit 21). */
#define CPUID_1C_MONITOR         0x00000008 /* [bit(ECX:3)] MONITOR and MWAIT instructions (SSE3). */
#define CPUID_1C_DS_CPL          0x00000010 /* [bit(ECX:4)] CPL qualified debug store. */
#define CPUID_1C_VMX             0x00000020 /* [bit(ECX:5)] Virtual Machine eXtensions. */
#define CPUID_1C_SMX             0x00000040 /* [bit(ECX:6)] Safer Mode Extensions (LaGrande). */
#define CPUID_1C_EST             0x00000080 /* [bit(ECX:7)] Enhanced SpeedStep. */
#define CPUID_1C_TM2             0x00000100 /* [bit(ECX:8)] Thermal Monitor 2. */
#define CPUID_1C_SSSE3           0x00000200 /* [bit(ECX:9)] Supplemental SSE3 instructions. */
#define CPUID_1C_CNXT_ID         0x00000400 /* [bit(ECX:10)] L1 Context ID. */
#define CPUID_1C_SDBG            0x00000800 /* [bit(ECX:11)] Silicon Debug interface. */
#define CPUID_1C_FMA             0x00001000 /* [bit(ECX:12)] Fused multiply-add (FMA3). */
#define CPUID_1C_CX16            0x00002000 /* [bit(ECX:13)] CMPXCHG16B instruction. */
#define CPUID_1C_XTPR            0x00004000 /* [bit(ECX:14)] Can disable sending task priority messages. */
#define CPUID_1C_PDCM            0x00008000 /* [bit(ECX:15)] Perfmon & debug capability. */
/*      CPUID_1C_                0x00010000 /* [bit(ECX:16)] RESERVED. */
#define CPUID_1C_PCID            0x00020000 /* [bit(ECX:17)] Process context identifiers (CR4 bit 17). */
#define CPUID_1C_DCA             0x00040000 /* [bit(ECX:18)] Direct cache access for DMA writes[12][13]. */
#define CPUID_1C_SSE4_1          0x00080000 /* [bit(ECX:19)] SSE4.1 instructions. */
#define CPUID_1C_SSE4_2          0x00100000 /* [bit(ECX:20)] SSE4.2 instructions. */
#define CPUID_1C_X2APIC          0x00200000 /* [bit(ECX:21)] x2APIC support. */
#define CPUID_1C_MOVBE           0x00400000 /* [bit(ECX:22)] MOVBE instruction (big-endian). */
#define CPUID_1C_POPCNT          0x00800000 /* [bit(ECX:23)] POPCNT instruction. */
#define CPUID_1C_TSC_DEADLINE    0x01000000 /* [bit(ECX:24)] APIC supports one-shot operation using a TSC deadline value. */
#define CPUID_1C_AES             0x02000000 /* [bit(ECX:25)] AES instruction set. */
#define CPUID_1C_XSAVE           0x04000000 /* [bit(ECX:26)] XSAVE, XRESTOR, XSETBV, XGETBV. */
#define CPUID_1C_OSXSAVE         0x08000000 /* [bit(ECX:27)] XSAVE enabled by OS. */
#define CPUID_1C_AVX             0x10000000 /* [bit(ECX:28)] Advanced Vector Extensions. */
#define CPUID_1C_F16C            0x20000000 /* [bit(ECX:29)] F16C (half-precision) FP support. */
#define CPUID_1C_RDRND           0x40000000 /* [bit(ECX:30)] RDRAND (on-chip random number generator) support. */
#define CPUID_1C_HYPERVISOR      0x80000000 /* [bit(ECX:31)] Running on a hypervisor (always 0 on a real CPU, but also with some hypervisors). */

/*      CPUID_7D_                0x00000001 /* [bit(0)] RESERVED. */
/*      CPUID_7D_                0x00000002 /* [bit(1)] RESERVED. */
#define CPUID_7D_AVX512_4VNNIW   0x00000004 /* [bit(2)] AVX-512 4-register Neural Network Instructions. */
#define CPUID_7D_AVX512_4FMAPS   0x00000008 /* [bit(3)] AVX-512 4-register Multiply Accumulation Single precision. */
/*      CPUID_7D_                0x00000010 /* [bit(4)] RESERVED. */
/*      CPUID_7D_                0x00000020 /* [bit(5)] RESERVED. */
/*      CPUID_7D_                0x00000040 /* [bit(6)] RESERVED. */
/*      CPUID_7D_                0x00000080 /* [bit(7)] RESERVED. */
/*      CPUID_7D_                0x00000100 /* [bit(8)] RESERVED. */
/*      CPUID_7D_                0x00000200 /* [bit(9)] RESERVED. */
/*      CPUID_7D_                0x00000400 /* [bit(10)] RESERVED. */
/*      CPUID_7D_                0x00000800 /* [bit(11)] RESERVED. */
/*      CPUID_7D_                0x00001000 /* [bit(12)] RESERVED. */
/*      CPUID_7D_                0x00002000 /* [bit(13)] RESERVED. */
/*      CPUID_7D_                0x00004000 /* [bit(14)] RESERVED. */
/*      CPUID_7D_                0x00008000 /* [bit(15)] RESERVED. */
/*      CPUID_7D_                0x00010000 /* [bit(16)] RESERVED. */
/*      CPUID_7D_                0x00020000 /* [bit(17)] RESERVED. */
/*      CPUID_7D_                0x00040000 /* [bit(18)] RESERVED. */
/*      CPUID_7D_                0x00080000 /* [bit(19)] RESERVED. */
/*      CPUID_7D_                0x00100000 /* [bit(20)] RESERVED. */
/*      CPUID_7D_                0x00200000 /* [bit(21)] RESERVED. */
/*      CPUID_7D_                0x00400000 /* [bit(22)] RESERVED. */
/*      CPUID_7D_                0x00800000 /* [bit(23)] RESERVED. */
/*      CPUID_7D_                0x01000000 /* [bit(24)] RESERVED. */
/*      CPUID_7D_                0x02000000 /* [bit(25)] RESERVED. */
/*      CPUID_7D_                0x04000000 /* [bit(26)] RESERVED. */
/*      CPUID_7D_                0x08000000 /* [bit(27)] RESERVED. */
/*      CPUID_7D_                0x10000000 /* [bit(28)] RESERVED. */
/*      CPUID_7D_                0x20000000 /* [bit(29)] RESERVED. */
/*      CPUID_7D_                0x40000000 /* [bit(30)] RESERVED. */
/*      CPUID_7D_                0x80000000 /* [bit(31)] RESERVED. */
#define CPUID_7C_PREFETCHWT1     0x00000001 /* [bit(0)] PREFETCHWT1 instruction. */
#define CPUID_7C_AVX512VBMI      0x00000002 /* [bit(1)] AVX-512 Vector Bit Manipulation Instructions. */
#define CPUID_7C_UMIP            0x00000004 /* [bit(2)] User-mode Instruction Prevention. */
#define CPUID_7C_PKU             0x00000008 /* [bit(3)] Memory Protection Keys for User-mode pages. */
#define CPUID_7C_OSPKE           0x00000010 /* [bit(4)] PKU enabled by OS. */
/*      CPUID_7C_                0x00000020 /* [bit(5)] RESERVED. */
#define CPUID_7C_AVX512VBMI2     0x00000040 /* [bit(6)] AVX-512 Vector Bit Manipulation Instructions 2. */
/*      CPUID_7C_                0x00000080 /* [bit(7)] RESERVED. */
#define CPUID_7C_GFNI            0x00000100 /* [bit(8)] Galois Field instructions. */
#define CPUID_7C_VAES            0x00000200 /* [bit(9)] AES instruction set (VEX-256/EVEX). */
#define CPUID_7C_VPCLMULQDQ      0x00000400 /* [bit(10)] CLMUL instruction set (VEX-256/EVEX). */
#define CPUID_7C_AVX512VNNI      0x00000800 /* [bit(11)] AVX-512 Vector Neural Network Instructions. */
#define CPUID_7C_AVX512BITALG    0x00001000 /* [bit(12)] AVX-512 BITALG instructions. */
/*      CPUID_7C_                0x00002000 /* [bit(13)] RESERVED. */
#define CPUID_7C_AVX512VPOPCNTDQ 0x00004000 /* [bit(14)] AVX-512 Vector Population Count D/Q. */
/*      CPUID_7C_                0x00008000 /* [bit(15)] RESERVED. */
/*      CPUID_7C_                0x00010000 /* [bit(16)] RESERVED. */
#define CPUID_7C_MAWAU           0x003e0000 /* [bit(17...21)] The value of userspace MPX Address-Width Adjust used by
                                             *                the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode. */
#define CPUID_7C_RDPID           0x00400000 /* [bit(22)] Read Processor ID. */
/*      CPUID_7C_                0x00800000 /* [bit(23)] RESERVED. */
/*      CPUID_7C_                0x01000000 /* [bit(24)] RESERVED. */
/*      CPUID_7C_                0x02000000 /* [bit(25)] RESERVED. */
/*      CPUID_7C_                0x04000000 /* [bit(26)] RESERVED. */
/*      CPUID_7C_                0x08000000 /* [bit(27)] RESERVED. */
/*      CPUID_7C_                0x10000000 /* [bit(28)] RESERVED. */
/*      CPUID_7C_                0x20000000 /* [bit(29)] RESERVED. */
#define CPUID_7C_SGX_LC          0x40000000 /* [bit(30)] SGX Launch Configuration. */
/*      CPUID_7C_                0x80000000 /* [bit(31)] RESERVED. */
#define CPUID_7B_FSGSBASE        0x00000001 /* [bit(0)] Access to base of %fs and %gs. */
#define CPUID_7B_IA32_TSC_ADJUST 0x00000002 /* [bit(1)] IA32_TSC_ADJUST. */
#define CPUID_7B_SGX             0x00000004 /* [bit(2)] Software Guard Extensions. */
#define CPUID_7B_BMI1            0x00000008 /* [bit(3)] Bit Manipulation Instruction Set 1. */
#define CPUID_7B_HLE             0x00000010 /* [bit(4)] Transactional Synchronization Extensions. */
#define CPUID_7B_AVX2            0x00000020 /* [bit(5)] Advanced Vector Extensions 2. */
/*      CPUID_7B_                0x00000040 /* [bit(6)] RESERVED. */
#define CPUID_7B_SMEP            0x00000080 /* [bit(7)] Supervisor-Mode Execution Prevention. */
#define CPUID_7B_BMI2            0x00000100 /* [bit(8)] Bit Manipulation Instruction Set 2. */
#define CPUID_7B_ERMS            0x00000200 /* [bit(9)] Enhanced REP MOVSB/STOSB. */
#define CPUID_7B_INVPCID         0x00000400 /* [bit(10)] INVPCID instruction. */
#define CPUID_7B_RTM             0x00000800 /* [bit(11)] Transactional Synchronization Extensions. */
#define CPUID_7B_PQM             0x00001000 /* [bit(12)] Platform Quality of Service Monitoring. */
#define CPUID_7B_FPU             0x00002000 /* [bit(13)] CS and FPU DS deprecated. */
#define CPUID_7B_MPX             0x00004000 /* [bit(14)] Intel MPX (Memory Protection Extensions). */
#define CPUID_7B_PQE             0x00008000 /* [bit(15)] Platform Quality of Service Enforcement. */
#define CPUID_7B_AVX512F         0x00010000 /* [bit(16)] AVX-512 Foundation. */
#define CPUID_7B_AVX512DQ        0x00020000 /* [bit(17)] AVX-512 Doubleword and Quadword Instructions. */
#define CPUID_7B_RDSEED          0x00040000 /* [bit(18)] RDSEED instruction. */
#define CPUID_7B_ADX             0x00080000 /* [bit(19)] Intel ADX (Multi-Precision Add-Carry Instruction Extensions). */
#define CPUID_7B_SMAP            0x00100000 /* [bit(20)] Supervisor Mode Access Prevention. */
#define CPUID_7B_AVX512IFMA      0x00200000 /* [bit(21)] AVX-512 Integer Fused Multiply-Add Instructions. */
#define CPUID_7B_PCOMMIT         0x00400000 /* [bit(22)] PCOMMIT instruction. */
#define CPUID_7B_CLFLUSHOPT      0x00800000 /* [bit(23)] CLFLUSHOPT instruction. */
#define CPUID_7B_CLWB            0x01000000 /* [bit(24)] CLWB instruction. */
#define CPUID_7B_INTEL_PT        0x02000000 /* [bit(25)] Intel Processor Trace. */
#define CPUID_7B_AVX512PF        0x04000000 /* [bit(26)] AVX-512 Prefetch Instructions. */
#define CPUID_7B_AVX512ER        0x08000000 /* [bit(27)] AVX-512 Exponential and Reciprocal Instructions. */
#define CPUID_7B_AVX512CD        0x10000000 /* [bit(28)] AVX-512 Conflict Detection Instructions. */
#define CPUID_7B_SHA             0x20000000 /* [bit(29)] Intel SHA extensions. */
#define CPUID_7B_AVX512BW        0x40000000 /* [bit(30)] AVX-512 Byte and Word Instructions. */
#define CPUID_7B_AVX512VL        0x80000000 /* [bit(31)] AVX-512 Vector Length Extensions. */


#define CPUID_80000001C_LAHF_LM       0x00000001 /* [bit(0)] LAHF/SAHF in long mode. */
#define CPUID_80000001C_CMP_LEGACY    0x00000002 /* [bit(1)] Hyperthreading not valid. */
#define CPUID_80000001C_SVM           0x00000004 /* [bit(2)] Secure Virtual Machine. */
#define CPUID_80000001C_EXTAPIC       0x00000008 /* [bit(3)] Extended APIC space. */
#define CPUID_80000001C_CR8_LEGACY    0x00000010 /* [bit(4)] CR8 in 32-bit mode. */
#define CPUID_80000001C_ABM           0x00000020 /* [bit(5)] Advanced bit manipulation (lzcnt and popcnt). */
#define CPUID_80000001C_SSE4A         0x00000040 /* [bit(6)] SSE4a. */
#define CPUID_80000001C_MISALIGNSSE   0x00000080 /* [bit(7)] Misaligned SSE mode. */
#define CPUID_80000001C_3DNOWPREFETCH 0x00000100 /* [bit(8)] PREFETCH and PREFETCHW instructions. */
#define CPUID_80000001C_OSVW          0x00000200 /* [bit(9)] OS Visible Workaround. */
#define CPUID_80000001C_IBS           0x00000400 /* [bit(10)] Instruction Based Sampling. */
#define CPUID_80000001C_XOP           0x00000800 /* [bit(11)] XOP instruction set. */
#define CPUID_80000001C_SKINIT        0x00001000 /* [bit(12)] SKINIT/STGI instructions. */
#define CPUID_80000001C_WDT           0x00002000 /* [bit(13)] Watchdog timer. */
/*      CPUID_80000001C_              0x00004000 /* [bit(14)] RESERVED. */
#define CPUID_80000001C_LWP           0x00008000 /* [bit(15)] Light Weight Profiling[23]. */
#define CPUID_80000001C_FMA4          0x00010000 /* [bit(16)] 4 operands fused multiply-add. */
#define CPUID_80000001C_TCE           0x00020000 /* [bit(17)] Translation Cache Extension. */
/*      CPUID_80000001C_              0x00040000 /* [bit(18)] RESERVED. */
#define CPUID_80000001C_NODEID_MSR    0x00080000 /* [bit(19)] NodeID MSR. */
/*      CPUID_80000001C_              0x00100000 /* [bit(20)] RESERVED. */
#define CPUID_80000001C_TBM           0x00200000 /* [bit(21)] Trailing Bit Manipulation. */
#define CPUID_80000001C_TOPOEXT       0x00400000 /* [bit(22)] Topology Extensions. */
#define CPUID_80000001C_PERFCTR_CORE  0x00800000 /* [bit(23)] Core performance counter extensions. */
#define CPUID_80000001C_PERFCTR_NB    0x01000000 /* [bit(24)] NB performance counter extensions. */
/*      CPUID_80000001C_              0x02000000 /* [bit(25)] RESERVED. */
#define CPUID_80000001C_DBX           0x04000000 /* [bit(26)] Data breakpoint extensions. */
#define CPUID_80000001C_PERFTSC       0x08000000 /* [bit(27)] Performance TSC. */
#define CPUID_80000001C_PCX_L2I       0x10000000 /* [bit(28)] L2I perf counter extensions. */
/*      CPUID_80000001C_              0x20000000 /* [bit(29)] RESERVED. */
/*      CPUID_80000001C_              0x40000000 /* [bit(30)] RESERVED. */
/*      CPUID_80000001C_              0x80000000 /* [bit(31)] RESERVED. */
#define CPUID_80000001D_FPU           0x00000001 /* [bit(0)] Onboard x87 FPU. */
#define CPUID_80000001D_VME           0x00000002 /* [bit(1)] Virtual mode extensions (VIF). */
#define CPUID_80000001D_DE            0x00000004 /* [bit(2)] Debugging extensions (CR4 bit 3). */
#define CPUID_80000001D_PSE           0x00000008 /* [bit(3)] Page Size Extension (allow 4MiB pages). */
#define CPUID_80000001D_TSC           0x00000010 /* [bit(4)] Time Stamp Counter. */
#define CPUID_80000001D_MSR           0x00000020 /* [bit(5)] Model-specific registers. */
#define CPUID_80000001D_PAE           0x00000040 /* [bit(6)] Physical Address Extension. */
#define CPUID_80000001D_MCE           0x00000080 /* [bit(7)] Machine Check Exception. */
#define CPUID_80000001D_CX8           0x00000100 /* [bit(8)] CMPXCHG8 (compare-and-swap) instruction. */
#define CPUID_80000001D_APIC          0x00000200 /* [bit(9)] Onboard Advanced Programmable Interrupt Controller. */
/*      CPUID_80000001D_              0x00000400 /* [bit(10)] RESERVED. */
#define CPUID_80000001D_SYSCALL       0x00000800 /* [bit(11)] SYSCALL and SYSRET instructions. */
#define CPUID_80000001D_MTRR          0x00001000 /* [bit(12)] Memory Type Range Registers. */
#define CPUID_80000001D_PGE           0x00002000 /* [bit(13)] Page Global Enable bit in CR4. */
#define CPUID_80000001D_MCA           0x00004000 /* [bit(14)] Machine check architecture. */
#define CPUID_80000001D_CMOV          0x00008000 /* [bit(15)] Conditional move and FCMOV instructions. */
#define CPUID_80000001D_PAT           0x00010000 /* [bit(16)] Page Attribute Table. */
#define CPUID_80000001D_PSE36         0x00020000 /* [bit(17)] 36-bit page size extension (for 4MiB pages). */
/*      CPUID_80000001D_              0x00040000 /* [bit(18)] RESERVED. */
#define CPUID_80000001D_MP            0x00080000 /* [bit(19)] Multiprocessor Capable. */
#define CPUID_80000001D_NX            0x00100000 /* [bit(20)] NX bit. */
/*      CPUID_80000001D_              0x00200000 /* [bit(21)] RESERVED. */
#define CPUID_80000001D_MMXEXT        0x00400000 /* [bit(22)] Extended MMX. */
#define CPUID_80000001D_MMX           0x00800000 /* [bit(23)] MMX instructions. */
#define CPUID_80000001D_FXSR          0x01000000 /* [bit(24)] FXSAVE, FXRSTOR instructions, CR4 bit 9. */
#define CPUID_80000001D_FXSR_OPT      0x02000000 /* [bit(25)] FXSAVE/FXRSTOR optimizations. */
#define CPUID_80000001D_PDPE1GB       0x04000000 /* [bit(26)] Gibabyte pages. */
#define CPUID_80000001D_RDTSCP        0x08000000 /* [bit(27)] RDTSCP instruction. */
/*      CPUID_80000001D_              0x10000000 /* [bit(28)] RESERVED. */
#define CPUID_80000001D_LM            0x20000000 /* [bit(29)] Long mode. */
#define CPUID_80000001D_3DNOWEXT      0x40000000 /* [bit(30)] Extended 3DNow. */
#define CPUID_80000001D_3DNOW         0x80000000 /* [bit(31)] 3DNow!. */


#endif /* !_I386_KOS_ASM_CPU_CPUID_H */
