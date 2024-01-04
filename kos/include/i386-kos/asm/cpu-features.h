/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_ASM_CPU_FEATURES_H
#define _I386_KOS_ASM_CPU_FEATURES_H 1

#include <hybrid/typecore.h>

/* Layout of a X86 CPU feature word. */
#define X86_FEATURE_TYP_CPUID 0x00000000 /* [mask(X86_FEATURE_TYPMASK)] CPUID feature check */
#define X86_FEATURE_TYP_MISC  0x10000000 /* [mask(X86_FEATURE_TYPMASK)] Misc feature check. */
#define X86_FEATURE_TYP_CONST 0x20000000 /* [mask(X86_FEATURE_TYPMASK)] Constant feature check. */

#define X86_FEATURE_EAXMASK 0x8fffff80 /* CPUID index (value for EAX) */
#define X86_FEATURE_REGMASK 0x00000060 /* CPUID result register (0=EAX,1=ECX,2=EDX,3=EBX) */
#define X86_FEATURE_BITMASK 0x0000001f /* CPUID result bit index (== CTZ(MASK)) */
#define X86_FEATURE_TYPMASK 0x70000000 /* Feature type mask */
#define X86_FEATURE_GETEAX(x) (((x) & 0x80000000) | (((x) & 0x0fffff80) >> 7))
#define X86_FEATURE_GETREG(x) (((x) & 0x60) >> 5)
#define X86_FEATURE_GETBIT(x) ((x) & 0x1f)
#define _X86_FEATURE_A(eax, bit) ((eax) & 0x80000000 | ((eax) & 0x1fffff) << 7 | (bit) | 0x00)
#define _X86_FEATURE_C(eax, bit) ((eax) & 0x80000000 | ((eax) & 0x1fffff) << 7 | (bit) | 0x20)
#define _X86_FEATURE_D(eax, bit) ((eax) & 0x80000000 | ((eax) & 0x1fffff) << 7 | (bit) | 0x40)
#define _X86_FEATURE_B(eax, bit) ((eax) & 0x80000000 | ((eax) & 0x1fffff) << 7 | (bit) | 0x60)
#define X86_FEATURE(eax, reg, bit) _X86_FEATURE_##reg(eax, bit)

/************************************************************************/
/* List of known (named) x86 features.                                  */
/************************************************************************/

#define X86_FEAT_486    (X86_FEATURE_TYP_MISC | 0x00000001)  /* Are we running on a 486? */
#define X86_FEAT_CPUID  X86_FEAT_486                         /* Is the `cpuid' instruction supported? */
#define X86_FEAT_INVLPG X86_FEAT_486                         /* Is the `invlpg' instruction supported? */
#define X86_FEAT_FALSE  (X86_FEATURE_TYP_CONST | 0x00000000) /* Always false */
#define X86_FEAT_TRUE   (X86_FEATURE_TYP_CONST | 0x00000001) /* Always true */

/*[[[deemon
import * from deemon;
local inside = false;
local knownFeatures: {string...} = HashSet();
local features: {(string, int, string, int, string)...} = [];
local FEATURE_CTZ: {int: int} = {
	0x00000001 : 0,  0x00000002 : 1,  0x00000004 : 2,  0x00000008 : 3,
	0x00000010 : 4,  0x00000020 : 5,  0x00000040 : 6,  0x00000080 : 7,
	0x00000100 : 8,  0x00000200 : 9,  0x00000400 : 10, 0x00000800 : 11,
	0x00001000 : 12, 0x00002000 : 13, 0x00004000 : 14, 0x00008000 : 15,
	0x00010000 : 16, 0x00020000 : 17, 0x00040000 : 18, 0x00080000 : 19,
	0x00100000 : 20, 0x00200000 : 21, 0x00400000 : 22, 0x00800000 : 23,
	0x01000000 : 24, 0x02000000 : 25, 0x04000000 : 26, 0x08000000 : 27,
	0x10000000 : 28, 0x20000000 : 29, 0x40000000 : 30, 0x80000000 : 31
};
for (local l: File.open("cpu-cpuid.h")) {
	l = l.strip();
	if (l == "/" "*[[[begin]]]*" "/")
		inside = true;
	if (l == "/" "*[[[end]]]*" "/")
		inside = false;
	if (!inside)
		continue;
	local index, register, name, mask, comment;
	try {
		index, register, name, mask, comment =
			l.scanf(" # define CPUID_%[^ACDB]%[^_]_%[^ ] __UINT32_C( %[^)]) %[^]")...;
		index = int(index, 16);
		if (register !in "ACDB")
			continue;
		if (name in knownFeatures)
			continue;
		mask = int(mask.strip());
		mask = FEATURE_CTZ[mask];
	} catch (...) {
		continue;
	}
	comment = comment.strip();
	if (comment.startswith("/" "*") && comment.endswith("*" "/"))
		comment = comment[2:-2].strip();
	while (comment.startswith("[")) {
		local e = comment.find("]");
		if (e < 0)
			break;
		comment = comment[e+1:].lstrip();
	}
	comment = comment.rstrip(".").rstrip();
	knownFeatures.insert(name);
	features.append((name, index, register, mask, comment));
}
local longestFeatureName = features.each[0].length > ...;
for (local name, index, register, mask, comment: features) {
	print("#define X86_FEAT_", name, " " * (longestFeatureName - #name), " X86_FEATURE(",
		index.hex(8), ", ", register, ", ", str(mask).rjust(2), ")"),;
	if (comment)
		print(" /" "* ", comment, " *" "/"),;
	print;
}
]]]*/
#define X86_FEAT_FPU             X86_FEATURE(0x00000001, D,  0) /* Onboard x87 FPU */
#define X86_FEAT_VME             X86_FEATURE(0x00000001, D,  1) /* Virtual 8086 mode extensions (such as VIF, VIP, PIV) */
#define X86_FEAT_DE              X86_FEATURE(0x00000001, D,  2) /* Debugging extensions (CR4 bit 3) */
#define X86_FEAT_PSE             X86_FEATURE(0x00000001, D,  3) /* Page Size Extension (allow 4MiB pages) */
#define X86_FEAT_TSC             X86_FEATURE(0x00000001, D,  4) /* Time Stamp Counter */
#define X86_FEAT_MSR             X86_FEATURE(0x00000001, D,  5) /* Model-specific registers */
#define X86_FEAT_PAE             X86_FEATURE(0x00000001, D,  6) /* Physical Address Extension */
#define X86_FEAT_MCE             X86_FEATURE(0x00000001, D,  7) /* Machine Check Exception */
#define X86_FEAT_CX8             X86_FEATURE(0x00000001, D,  8) /* CMPXCHG8B (compare-and-swap) instruction */
#define X86_FEAT_APIC            X86_FEATURE(0x00000001, D,  9) /* Onboard Advanced Programmable Interrupt Controller */
#define X86_FEAT_SEP             X86_FEATURE(0x00000001, D, 11) /* SYSENTER and SYSEXIT instructions */
#define X86_FEAT_MTRR            X86_FEATURE(0x00000001, D, 12) /* Memory Type Range Registers */
#define X86_FEAT_PGE             X86_FEATURE(0x00000001, D, 13) /* Page Global Enable bit in CR4 */
#define X86_FEAT_MCA             X86_FEATURE(0x00000001, D, 14) /* Machine check architecture */
#define X86_FEAT_CMOV            X86_FEATURE(0x00000001, D, 15) /* Conditional move and FCMOV instructions */
#define X86_FEAT_PAT             X86_FEATURE(0x00000001, D, 16) /* Page Attribute Table */
#define X86_FEAT_PSE36           X86_FEATURE(0x00000001, D, 17) /* 36-bit page size extension */
#define X86_FEAT_PSN             X86_FEATURE(0x00000001, D, 18) /* Processor Serial Number */
#define X86_FEAT_CLFSH           X86_FEATURE(0x00000001, D, 19) /* CLFLUSH instruction (SSE2) */
#define X86_FEAT_DS              X86_FEATURE(0x00000001, D, 21) /* Debug store: save trace of executed jumps */
#define X86_FEAT_ACPI            X86_FEATURE(0x00000001, D, 22) /* Onboard thermal control MSRs for ACPI */
#define X86_FEAT_MMX             X86_FEATURE(0x00000001, D, 23) /* MMX instructions */
#define X86_FEAT_FXSR            X86_FEATURE(0x00000001, D, 24) /* FXSAVE, FXRESTOR instructions, CR4 bit 9 */
#define X86_FEAT_SSE             X86_FEATURE(0x00000001, D, 25) /* SSE instructions (a.k.a. Katmai New Instructions) */
#define X86_FEAT_SSE2            X86_FEATURE(0x00000001, D, 26) /* SSE2 instructions */
#define X86_FEAT_SS              X86_FEATURE(0x00000001, D, 27) /* CPU cache supports self-snoop */
#define X86_FEAT_HTT             X86_FEATURE(0x00000001, D, 28) /* Hyper-threading */
#define X86_FEAT_TM              X86_FEATURE(0x00000001, D, 29) /* Thermal monitor automatically limits temperature */
#define X86_FEAT_IA64            X86_FEATURE(0x00000001, D, 30) /* IA64 processor emulating x86 */
#define X86_FEAT_PBE             X86_FEATURE(0x00000001, D, 31) /* Pending Break Enable (PBE# pin) wakeup support */
#define X86_FEAT_SSE3            X86_FEATURE(0x00000001, C,  0) /* Prescott New Instructions-SSE3 (PNI) */
#define X86_FEAT_PCLMULQDQ       X86_FEATURE(0x00000001, C,  1) /* PCLMULQDQ support */
#define X86_FEAT_DTES64          X86_FEATURE(0x00000001, C,  2) /* 64-bit debug store (edx bit 21) */
#define X86_FEAT_MONITOR         X86_FEATURE(0x00000001, C,  3) /* MONITOR and MWAIT instructions (SSE3) */
#define X86_FEAT_DS_CPL          X86_FEATURE(0x00000001, C,  4) /* CPL qualified debug store */
#define X86_FEAT_VMX             X86_FEATURE(0x00000001, C,  5) /* Virtual Machine eXtensions */
#define X86_FEAT_SMX             X86_FEATURE(0x00000001, C,  6) /* Safer Mode Extensions (LaGrande) */
#define X86_FEAT_EST             X86_FEATURE(0x00000001, C,  7) /* Enhanced SpeedStep */
#define X86_FEAT_TM2             X86_FEATURE(0x00000001, C,  8) /* Thermal Monitor 2 */
#define X86_FEAT_SSSE3           X86_FEATURE(0x00000001, C,  9) /* Supplemental SSE3 instructions */
#define X86_FEAT_CNXT_ID         X86_FEATURE(0x00000001, C, 10) /* L1 Context ID */
#define X86_FEAT_SDBG            X86_FEATURE(0x00000001, C, 11) /* Silicon Debug interface */
#define X86_FEAT_FMA             X86_FEATURE(0x00000001, C, 12) /* Fused multiply-add (FMA3) */
#define X86_FEAT_CX16            X86_FEATURE(0x00000001, C, 13) /* CMPXCHG16B instruction */
#define X86_FEAT_XTPR            X86_FEATURE(0x00000001, C, 14) /* Can disable sending task priority messages */
#define X86_FEAT_PDCM            X86_FEATURE(0x00000001, C, 15) /* Perfmon & debug capability */
#define X86_FEAT_PCID            X86_FEATURE(0x00000001, C, 17) /* Process context identifiers (CR4 bit 17) */
#define X86_FEAT_DCA             X86_FEATURE(0x00000001, C, 18) /* Direct cache access for DMA writes[12][13] */
#define X86_FEAT_SSE4_1          X86_FEATURE(0x00000001, C, 19) /* SSE4.1 instructions */
#define X86_FEAT_SSE4_2          X86_FEATURE(0x00000001, C, 20) /* SSE4.2 instructions */
#define X86_FEAT_X2APIC          X86_FEATURE(0x00000001, C, 21) /* x2APIC support */
#define X86_FEAT_MOVBE           X86_FEATURE(0x00000001, C, 22) /* MOVBE instruction (big-endian) */
#define X86_FEAT_POPCNT          X86_FEATURE(0x00000001, C, 23) /* POPCNT instruction */
#define X86_FEAT_TSC_DEADLINE    X86_FEATURE(0x00000001, C, 24) /* APIC supports one-shot operation using a TSC deadline value */
#define X86_FEAT_AES             X86_FEATURE(0x00000001, C, 25) /* AES instruction set */
#define X86_FEAT_XSAVE           X86_FEATURE(0x00000001, C, 26) /* XSAVE, XRESTOR, XSETBV, XGETBV */
#define X86_FEAT_OSXSAVE         X86_FEATURE(0x00000001, C, 27) /* XSAVE enabled by OS */
#define X86_FEAT_AVX             X86_FEATURE(0x00000001, C, 28) /* Advanced Vector Extensions */
#define X86_FEAT_F16C            X86_FEATURE(0x00000001, C, 29) /* F16C (half-precision) FP support */
#define X86_FEAT_RDRAND          X86_FEATURE(0x00000001, C, 30) /* RDRAND (on-chip random number generator) support */
#define X86_FEAT_HYPERVISOR      X86_FEATURE(0x00000001, C, 31) /* Running on a hypervisor (always 0 on a real CPU, but also with some hypervisors) */
#define X86_FEAT_AVX512_4VNNIW   X86_FEATURE(0x00000007, D,  2) /* AVX-512 4-register Neural Network Instructions */
#define X86_FEAT_AVX512_4FMAPS   X86_FEATURE(0x00000007, D,  3) /* AVX-512 4-register Multiply Accumulation Single precision */
#define X86_FEAT_PREFETCHWT1     X86_FEATURE(0x00000007, C,  0) /* PREFETCHWT1 instruction */
#define X86_FEAT_AVX512VBMI      X86_FEATURE(0x00000007, C,  1) /* AVX-512 Vector Bit Manipulation Instructions */
#define X86_FEAT_UMIP            X86_FEATURE(0x00000007, C,  2) /* User-mode Instruction Prevention */
#define X86_FEAT_PKU             X86_FEATURE(0x00000007, C,  3) /* Memory Protection Keys for User-mode pages */
#define X86_FEAT_OSPKE           X86_FEATURE(0x00000007, C,  4) /* PKU enabled by OS */
#define X86_FEAT_AVX512VBMI2     X86_FEATURE(0x00000007, C,  6) /* AVX-512 Vector Bit Manipulation Instructions 2 */
#define X86_FEAT_GFNI            X86_FEATURE(0x00000007, C,  8) /* Galois Field instructions */
#define X86_FEAT_VAES            X86_FEATURE(0x00000007, C,  9) /* AES instruction set (VEX-256/EVEX) */
#define X86_FEAT_VPCLMULQDQ      X86_FEATURE(0x00000007, C, 10) /* CLMUL instruction set (VEX-256/EVEX) */
#define X86_FEAT_AVX512VNNI      X86_FEATURE(0x00000007, C, 11) /* AVX-512 Vector Neural Network Instructions */
#define X86_FEAT_AVX512BITALG    X86_FEATURE(0x00000007, C, 12) /* AVX-512 BITALG instructions */
#define X86_FEAT_AVX512VPOPCNTDQ X86_FEATURE(0x00000007, C, 14) /* AVX-512 Vector Population Count D/Q */
#define X86_FEAT_RDPID           X86_FEATURE(0x00000007, C, 22) /* Read Processor ID */
#define X86_FEAT_SGX_LC          X86_FEATURE(0x00000007, C, 30) /* SGX Launch Configuration */
#define X86_FEAT_FSGSBASE        X86_FEATURE(0x00000007, B,  0) /* Access to base of %fs and %gs */
#define X86_FEAT_IA32_TSC_ADJUST X86_FEATURE(0x00000007, B,  1) /* IA32_TSC_ADJUST */
#define X86_FEAT_SGX             X86_FEATURE(0x00000007, B,  2) /* Software Guard Extensions */
#define X86_FEAT_BMI1            X86_FEATURE(0x00000007, B,  3) /* Bit Manipulation Instruction Set 1 */
#define X86_FEAT_HLE             X86_FEATURE(0x00000007, B,  4) /* Transactional Synchronization Extensions */
#define X86_FEAT_AVX2            X86_FEATURE(0x00000007, B,  5) /* Advanced Vector Extensions 2 */
#define X86_FEAT_SMEP            X86_FEATURE(0x00000007, B,  7) /* Supervisor-Mode Execution Prevention */
#define X86_FEAT_BMI2            X86_FEATURE(0x00000007, B,  8) /* Bit Manipulation Instruction Set 2 */
#define X86_FEAT_ERMS            X86_FEATURE(0x00000007, B,  9) /* Enhanced REP MOVSB/STOSB */
#define X86_FEAT_INVPCID         X86_FEATURE(0x00000007, B, 10) /* INVPCID instruction */
#define X86_FEAT_RTM             X86_FEATURE(0x00000007, B, 11) /* Transactional Synchronization Extensions */
#define X86_FEAT_PQM             X86_FEATURE(0x00000007, B, 12) /* Platform Quality of Service Monitoring */
#define X86_FEAT_MPX             X86_FEATURE(0x00000007, B, 14) /* Intel MPX (Memory Protection Extensions) */
#define X86_FEAT_PQE             X86_FEATURE(0x00000007, B, 15) /* Platform Quality of Service Enforcement */
#define X86_FEAT_AVX512F         X86_FEATURE(0x00000007, B, 16) /* AVX-512 Foundation */
#define X86_FEAT_AVX512DQ        X86_FEATURE(0x00000007, B, 17) /* AVX-512 Doubleword and Quadword Instructions */
#define X86_FEAT_RDSEED          X86_FEATURE(0x00000007, B, 18) /* RDSEED instruction */
#define X86_FEAT_ADX             X86_FEATURE(0x00000007, B, 19) /* Intel ADX (Multi-Precision Add-Carry Instruction Extensions) */
#define X86_FEAT_SMAP            X86_FEATURE(0x00000007, B, 20) /* Supervisor Mode Access Prevention */
#define X86_FEAT_AVX512IFMA      X86_FEATURE(0x00000007, B, 21) /* AVX-512 Integer Fused Multiply-Add Instructions */
#define X86_FEAT_PCOMMIT         X86_FEATURE(0x00000007, B, 22) /* PCOMMIT instruction */
#define X86_FEAT_CLFLUSHOPT      X86_FEATURE(0x00000007, B, 23) /* CLFLUSHOPT instruction */
#define X86_FEAT_CLWB            X86_FEATURE(0x00000007, B, 24) /* CLWB instruction */
#define X86_FEAT_INTEL_PT        X86_FEATURE(0x00000007, B, 25) /* Intel Processor Trace */
#define X86_FEAT_AVX512PF        X86_FEATURE(0x00000007, B, 26) /* AVX-512 Prefetch Instructions */
#define X86_FEAT_AVX512ER        X86_FEATURE(0x00000007, B, 27) /* AVX-512 Exponential and Reciprocal Instructions */
#define X86_FEAT_AVX512CD        X86_FEATURE(0x00000007, B, 28) /* AVX-512 Conflict Detection Instructions */
#define X86_FEAT_SHA             X86_FEATURE(0x00000007, B, 29) /* Intel SHA extensions */
#define X86_FEAT_AVX512BW        X86_FEATURE(0x00000007, B, 30) /* AVX-512 Byte and Word Instructions */
#define X86_FEAT_AVX512VL        X86_FEATURE(0x00000007, B, 31) /* AVX-512 Vector Length Extensions */
#define X86_FEAT_LAHF_LM         X86_FEATURE(0x80000001, C,  0) /* LAHF/SAHF in long mode */
#define X86_FEAT_CMP_LEGACY      X86_FEATURE(0x80000001, C,  1) /* Hyperthreading not valid */
#define X86_FEAT_SVM             X86_FEATURE(0x80000001, C,  2) /* Secure Virtual Machine */
#define X86_FEAT_EXTAPIC         X86_FEATURE(0x80000001, C,  3) /* Extended APIC space */
#define X86_FEAT_CR8_LEGACY      X86_FEATURE(0x80000001, C,  4) /* CR8 in 32-bit mode */
#define X86_FEAT_ABM             X86_FEATURE(0x80000001, C,  5) /* Advanced bit manipulation (lzcnt and popcnt) */
#define X86_FEAT_SSE4A           X86_FEATURE(0x80000001, C,  6) /* SSE4a */
#define X86_FEAT_MISALIGNSSE     X86_FEATURE(0x80000001, C,  7) /* Misaligned SSE mode */
#define X86_FEAT_3DNOWPREFETCH   X86_FEATURE(0x80000001, C,  8) /* PREFETCH and PREFETCHW instructions */
#define X86_FEAT_OSVW            X86_FEATURE(0x80000001, C,  9) /* OS Visible Workaround */
#define X86_FEAT_IBS             X86_FEATURE(0x80000001, C, 10) /* Instruction Based Sampling */
#define X86_FEAT_XOP             X86_FEATURE(0x80000001, C, 11) /* XOP instruction set */
#define X86_FEAT_SKINIT          X86_FEATURE(0x80000001, C, 12) /* SKINIT/STGI instructions */
#define X86_FEAT_WDT             X86_FEATURE(0x80000001, C, 13) /* Watchdog timer */
#define X86_FEAT_LWP             X86_FEATURE(0x80000001, C, 15) /* Light Weight Profiling[23] */
#define X86_FEAT_FMA4            X86_FEATURE(0x80000001, C, 16) /* 4 operands fused multiply-add */
#define X86_FEAT_TCE             X86_FEATURE(0x80000001, C, 17) /* Translation Cache Extension */
#define X86_FEAT_NODEID_MSR      X86_FEATURE(0x80000001, C, 19) /* NodeID MSR */
#define X86_FEAT_TBM             X86_FEATURE(0x80000001, C, 21) /* Trailing Bit Manipulation */
#define X86_FEAT_TOPOEXT         X86_FEATURE(0x80000001, C, 22) /* Topology Extensions */
#define X86_FEAT_PERFCTR_CORE    X86_FEATURE(0x80000001, C, 23) /* Core performance counter extensions */
#define X86_FEAT_PERFCTR_NB      X86_FEATURE(0x80000001, C, 24) /* NB performance counter extensions */
#define X86_FEAT_DBX             X86_FEATURE(0x80000001, C, 26) /* Data breakpoint extensions */
#define X86_FEAT_PERFTSC         X86_FEATURE(0x80000001, C, 27) /* Performance TSC */
#define X86_FEAT_PCX_L2I         X86_FEATURE(0x80000001, C, 28) /* L2I perf counter extensions */
#define X86_FEAT_SYSCALL         X86_FEATURE(0x80000001, D, 11) /* SYSCALL and SYSRET instructions */
#define X86_FEAT_MP              X86_FEATURE(0x80000001, D, 19) /* Multiprocessor Capable */
#define X86_FEAT_NX              X86_FEATURE(0x80000001, D, 20) /* NX bit */
#define X86_FEAT_MMXEXT          X86_FEATURE(0x80000001, D, 22) /* Extended MMX */
#define X86_FEAT_FXSR_OPT        X86_FEATURE(0x80000001, D, 25) /* FXSAVE/FXRSTOR optimizations */
#define X86_FEAT_PDPE1GB         X86_FEATURE(0x80000001, D, 26) /* Gibabyte pages */
#define X86_FEAT_RDTSCP          X86_FEATURE(0x80000001, D, 27) /* RDTSCP instruction */
#define X86_FEAT_LM              X86_FEATURE(0x80000001, D, 29) /* Long mode */
#define X86_FEAT_3DNOWEXT        X86_FEATURE(0x80000001, D, 30) /* Extended 3DNow */
#define X86_FEAT_3DNOW           X86_FEATURE(0x80000001, D, 31) /* 3DNow! */
#define X86_FEAT_INVARIANT_TSC   X86_FEATURE(0x80000007, D,  8) /* The TSC's increment speed is invariant */
/*[[[end]]]*/


#endif /* !_I386_KOS_ASM_CPU_FEATURES_H */
