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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_CPUID_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_CPUID_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pertask.h>

#include <asm/cpu-cpuid.h>

DECL_BEGIN

#define CPU_FEATURE_FNONE    0x0000
#ifndef __x86_64__
#define CPU_FEATURE_FCPUID   0x0001 /* The `cpuid' instruction is supported. */
#define CPU_FEATURE_FI486    0x0001 /* The cpu is an i486. */
#endif /* !__x86_64__ */
#define CPU_FEATURE_FDIDINIT 0x8000 /* Features have been initialized. */



#define OFFSET_CPUID_0A          0
#define OFFSET_CPUID_80000000A   4
#define OFFSET_CPUID_1A          8
#define OFFSET_CPUID_1B          12
#define OFFSET_CPUID_1D          16
#define OFFSET_CPUID_1C          20
#define OFFSET_CPUID_7D          24
#define OFFSET_CPUID_7C          28
#define OFFSET_CPUID_7B          32
#define OFFSET_CPUID_80000001C   36
#define OFFSET_CPUID_80000001D   40
#define OFFSET_CPUID_0B          44
#define OFFSET_CPUID_0D          48
#define OFFSET_CPUID_0C          52
#define OFFSET_CPUID_80000002A   60
#define OFFSET_CPUID_80000002B   64
#define OFFSET_CPUID_80000002C   68
#define OFFSET_CPUID_80000002D   72
#define OFFSET_CPUID_80000003A   76
#define OFFSET_CPUID_80000003B   80
#define OFFSET_CPUID_80000003C   84
#define OFFSET_CPUID_80000003D   88
#define OFFSET_CPUID_80000004A   92
#define OFFSET_CPUID_80000004B   96
#define OFFSET_CPUID_80000004C   100
#define OFFSET_CPUID_80000004D   104
#define SIZEOF_CPUID_CPUINFO     112


#ifdef __CC__

struct cpuinfo {
	union ATTR_PACKED {
		u32           ci_0a;           /* [const][== cpuid(0).EAX] */
		u32           ci_bleaf_max;    /* [const][== cpuid(0).EAX] Max supported basic cpuid leaf number. */
	};
	union ATTR_PACKED {
		u32           ci_80000000a;    /* [const][== cpuid(0x80000000).EAX] */
		u32           ci_eleaf_max;    /* [const][== cpuid(0x80000000).EAX] Max supported basic cpuid leaf number */
	};
	union ATTR_PACKED {
		u32           ci_1a;           /* [const][== cpuid(1).EAX] Processor info... */
		struct ATTR_PACKED {
			unsigned int ci_version : 12;
		};
		struct ATTR_PACKED {
			unsigned int ci_stepping : 4;
			unsigned int ci_model : 4;
			unsigned int ci_family : 4;
			unsigned int ci_processor_type : 4;
			unsigned int ci_extended_model : 4;
			unsigned int ci_extended_family : 8;
			unsigned int __ci_pad0 : 4;
		};
	};
	u32               ci_1b;           /* [const][== cpuid(1).EBX] Processor info... */
	u32               ci_1d;           /* [const][== cpuid(1).EDX] Set of `CPUID_1D_*' */
	u32               ci_1c;           /* [const][== cpuid(1).ECX] Set of `CPUID_1C_*' */
	u32               ci_7d;           /* [const][== cpuid(7,0).EDX] Set of `CPUID_7D_*' */
	u32               ci_7c;           /* [const][== cpuid(7,0).ECX] Set of `CPUID_7C_*' */
	u32               ci_7b;           /* [const][== cpuid(7,0).EBX] Set of `CPUID_7B_*' */
	u32               ci_80000001c;    /* [const][== cpuid(0x80000001).ECX] Set of `CPUID_80000001C_*' */
	u32               ci_80000001d;    /* [const][== cpuid(0x80000001).EDX] Set of `CPUID_80000001D_*' */
	union ATTR_PACKED {
		struct ATTR_PACKED {
			u32       ci_0b;           /* [const][== cpuid(0).EBX] */
			u32       ci_0d;           /* [const][== cpuid(0).EDX] */
			u32       ci_0c;           /* [const][== cpuid(0).ECX] */
		};
		char          ci_vendorid[12]; /* [const][== cpuid(0).EBX~EDX~ECX] Vendor ID */
	};
	char            __ci_zero1[4];     /* [const][== 0] */
	union ATTR_PACKED {
		struct ATTR_PACKED {
			u32       ci_80000002a;    /* [const][== cpuid(0x80000002).EAX] */
			u32       ci_80000002b;    /* [const][== cpuid(0x80000002).EBX] */
			u32       ci_80000002c;    /* [const][== cpuid(0x80000002).ECX] */
			u32       ci_80000002d;    /* [const][== cpuid(0x80000002).EDX] */
			u32       ci_80000003a;    /* [const][== cpuid(0x80000003).EAX] */
			u32       ci_80000003b;    /* [const][== cpuid(0x80000003).EBX] */
			u32       ci_80000003c;    /* [const][== cpuid(0x80000003).ECX] */
			u32       ci_80000003d;    /* [const][== cpuid(0x80000003).EDX] */
			u32       ci_80000004a;    /* [const][== cpuid(0x80000004).EAX] */
			u32       ci_80000004b;    /* [const][== cpuid(0x80000004).EBX] */
			u32       ci_80000004c;    /* [const][== cpuid(0x80000004).ECX] */
			u32       ci_80000004d;    /* [const][== cpuid(0x80000004).EDX] */
		};
		char          ci_brand[48];    /* [const][== cpuid(0x80000002...0x80000004).EAX~EBX~ECX~EDX] Brand string. */
	};
	char            __ci_zero2[4];     /* [const][== 0] */
};

/* Basic CPU feature flags (Set of `CPU_FEATURE_F*') */
DATDEF ATTR_PERCPU u16 const thiscpu_x86_cpufeatures;

/* [valid_if(cpu_basic_features & CPU_FEATURE_FCPUID)]
 * NOTE: When `CPU_FEATURE_FCPUID' isn't set, all members are ZERO-initialized.
 * Information gathered from `cpuid' */
DATDEF ATTR_PERCPU struct cpuinfo const thiscpu_x86_cpuid;
#define CURRENT_X86_CPUID PERCPU(thiscpu_x86_cpuid)


DATDEF u16 const x86_bootcpu_cpufeatures;
DATDEF struct cpuinfo const x86_bootcpu_cpuid;

#endif /* __CC__ */


/* Feature test macros. */
#ifndef __x86_64__
#define X86_HAVE_I486                  (x86_bootcpu_cpufeatures & CPU_FEATURE_FI486)
#define X86_HAVE_CPUID                 (x86_bootcpu_cpufeatures & CPU_FEATURE_FCPUID)
#else /* !__x86_64__ */
#define X86_HAVE_I486                  1 /* 64-bit mode _requires_ a 486+ */
#define X86_HAVE_CPUID                 1 /* 64-bit mode _requires_ `cpuid' support */
#define X86_ALWAYS_HAVE_CPUID          1 /* 64-bit mode _requires_ `cpuid' support */
#endif /* __x86_64__ */
#define X86_HAVE_FPU                   (x86_bootcpu_cpuid.ci_1d & CPUID_1D_FPU)
#define X86_HAVE_FXSR                  (x86_bootcpu_cpuid.ci_1d & CPUID_1D_FXSR)
#define X86_HAVE_SSE                   (x86_bootcpu_cpuid.ci_1d & CPUID_1D_SSE)
#define X86_HAVE_PAGE_GLOBAL_BIT       (x86_bootcpu_cpuid.ci_1d & CPUID_1D_PGE)
#define X86_HAVE_PAGE_ATTRIBUTE_TABLE  (x86_bootcpu_cpuid.ci_1d & CPUID_1D_PAT)
#define X86_HAVE_INSTR_INVLPG          X86_HAVE_I486 /* ... INVLPG is an instruction available since the i486 ... */
#define X86_HAVE_INSTR_INVPCID         (x86_bootcpu_cpuid.ci_7b & CPUID_7B_INVPCID)
#define X86_HAVE_EXECUTE_DISABLE       (x86_bootcpu_cpuid.ci_80000001d & CPUID_80000001D_NX)
#define X86_HAVE_SYSENTER              (x86_bootcpu_cpuid.ci_1d & CPUID_1D_SEP)
#define X86_HAVE_CMPXCHG8B             (x86_bootcpu_cpuid.ci_1d & CPUID_1D_CX8)
#ifdef __x86_64__
#define X86_HAVE_FSGSBASE              (x86_bootcpu_cpuid.ci_7b & CPUID_7B_FSGSBASE)
#define X86_HAVE_CMPXCHG16B            (x86_bootcpu_cpuid.ci_1c & CPUID_1C_CX16)
#define X86_HAVE_SYSCALL               (x86_bootcpu_cpuid.ci_80000001d & CPUID_80000001D_SYSCALL)
#define X86_HAVE_2MIB_PAGES            1 /* Always available! (and also assumed to be by code below!) */
#define X86_HAVE_4MIB_PAGES            0 /* 32-bit only feature */
#define X86_HAVE_1GIB_PAGES            (x86_bootcpu_cpuid.ci_80000001d & CPUID_80000001D_PSE)
#define X86_HAVE_PAE                   0 /* 32-bit only feature */
#else /* __x86_64__ */
#define X86_HAVE_FSGSBASE              0 /* 64-bit only feature */
#define X86_HAVE_CMPXCHG16B            0 /* 64-bit only feature */
#define X86_HAVE_SYSCALL               0 /* 64-bit only feature */
#define X86_HAVE_2MIB_PAGES            0 /* 64-bit only feature */
#define X86_HAVE_4MIB_PAGES            (x86_bootcpu_cpuid.ci_1d & CPUID_1D_PSE)
#define X86_HAVE_1GIB_PAGES            0 /* 64-bit only feature */
#define X86_HAVE_PAE                   (x86_bootcpu_cpuid.ci_1d & CPUID_1D_PAE)
#endif /* !__x86_64__ */


/* Same as above, but for the current CPU (whereas
 * the macros above are only for the boot CPU) */
#define X86_THISCPU_HAVE_SYSENTER      (CURRENT_X86_CPUID.ci_1d & CPUID_1D_SEP)
#ifdef __x86_64__
#define X86_THISCPU_HAVE_SYSCALL       (CURRENT_X86_CPUID.ci_80000001d & CPUID_80000001D_SYSCALL)
#else /* __x86_64__ */
#define X86_THISCPU_HAVE_SYSCALL       0 /* 64-bit only feature */
#endif /* !__x86_64__ */



DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_CPUID_H */
