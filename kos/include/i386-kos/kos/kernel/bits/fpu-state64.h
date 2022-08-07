/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_KOS_KERNEL_BITS_FPU_STATE64_H
#define _I386_KOS_KOS_KERNEL_BITS_FPU_STATE64_H 1

#include <__stdinc.h>

#include <bits/types.h>

#include <ieee754.h>

#include "fpu-sstate.h"

__SYSDECL_BEGIN

#ifdef __x86_64__
#define OFFSET_XFPUSTATE_FCW        OFFSET_XFPUSTATE64_FCW
#define OFFSET_XFPUSTATE_FSW        OFFSET_XFPUSTATE64_FSW
#define OFFSET_XFPUSTATE_FTW        OFFSET_XFPUSTATE64_FTW
#define OFFSET_XFPUSTATE_FOP        OFFSET_XFPUSTATE64_FOP
#define OFFSET_XFPUSTATE_FIP        OFFSET_XFPUSTATE64_FIP
#define OFFSET_XFPUSTATE_FDP        OFFSET_XFPUSTATE64_FDP
#define OFFSET_XFPUSTATE_MXCSR      OFFSET_XFPUSTATE64_MXCSR
#define OFFSET_XFPUSTATE_MXCSR_MASK OFFSET_XFPUSTATE64_MXCSR_MASK
#define OFFSET_XFPUSTATE_ST         OFFSET_XFPUSTATE64_ST
#define OFFSET_XFPUSTATE_ST0        OFFSET_XFPUSTATE64_ST0
#define OFFSET_XFPUSTATE_ST1        OFFSET_XFPUSTATE64_ST1
#define OFFSET_XFPUSTATE_ST2        OFFSET_XFPUSTATE64_ST2
#define OFFSET_XFPUSTATE_ST3        OFFSET_XFPUSTATE64_ST3
#define OFFSET_XFPUSTATE_ST4        OFFSET_XFPUSTATE64_ST4
#define OFFSET_XFPUSTATE_ST5        OFFSET_XFPUSTATE64_ST5
#define OFFSET_XFPUSTATE_ST6        OFFSET_XFPUSTATE64_ST6
#define OFFSET_XFPUSTATE_ST7        OFFSET_XFPUSTATE64_ST7
#define OFFSET_XFPUSTATE_MM         OFFSET_XFPUSTATE64_MM
#define OFFSET_XFPUSTATE_MM0        OFFSET_XFPUSTATE64_MM0
#define OFFSET_XFPUSTATE_MM1        OFFSET_XFPUSTATE64_MM1
#define OFFSET_XFPUSTATE_MM2        OFFSET_XFPUSTATE64_MM2
#define OFFSET_XFPUSTATE_MM3        OFFSET_XFPUSTATE64_MM3
#define OFFSET_XFPUSTATE_MM4        OFFSET_XFPUSTATE64_MM4
#define OFFSET_XFPUSTATE_MM5        OFFSET_XFPUSTATE64_MM5
#define OFFSET_XFPUSTATE_MM6        OFFSET_XFPUSTATE64_MM6
#define OFFSET_XFPUSTATE_MM7        OFFSET_XFPUSTATE64_MM7
#define OFFSET_XFPUSTATE_XMM        OFFSET_XFPUSTATE64_XMM
#define OFFSET_XFPUSTATE_XMM0       OFFSET_XFPUSTATE64_XMM0
#define OFFSET_XFPUSTATE_XMM1       OFFSET_XFPUSTATE64_XMM1
#define OFFSET_XFPUSTATE_XMM2       OFFSET_XFPUSTATE64_XMM2
#define OFFSET_XFPUSTATE_XMM3       OFFSET_XFPUSTATE64_XMM3
#define OFFSET_XFPUSTATE_XMM4       OFFSET_XFPUSTATE64_XMM4
#define OFFSET_XFPUSTATE_XMM5       OFFSET_XFPUSTATE64_XMM5
#define OFFSET_XFPUSTATE_XMM6       OFFSET_XFPUSTATE64_XMM6
#define OFFSET_XFPUSTATE_XMM7       OFFSET_XFPUSTATE64_XMM7
#define OFFSET_XFPUSTATE_XMM8       OFFSET_XFPUSTATE64_XMM8
#define OFFSET_XFPUSTATE_XMM9       OFFSET_XFPUSTATE64_XMM9
#define OFFSET_XFPUSTATE_XMM10      OFFSET_XFPUSTATE64_XMM10
#define OFFSET_XFPUSTATE_XMM11      OFFSET_XFPUSTATE64_XMM11
#define OFFSET_XFPUSTATE_XMM12      OFFSET_XFPUSTATE64_XMM12
#define OFFSET_XFPUSTATE_XMM13      OFFSET_XFPUSTATE64_XMM13
#define OFFSET_XFPUSTATE_XMM14      OFFSET_XFPUSTATE64_XMM14
#define OFFSET_XFPUSTATE_XMM15      OFFSET_XFPUSTATE64_XMM15
#define SIZEOF_XFPUSTATE            SIZEOF_XFPUSTATE64
#define ALIGNOF_XFPUSTATE           ALIGNOF_XFPUSTATE64
#define xfpustate64                 xfpustate

#define SIZEOF_FPUSTATE  SIZEOF_FPUSTATE64
#define ALIGNOF_FPUSTATE ALIGNOF_FPUSTATE64
#define fpustate64       fpustate
#define fpustate_isssave fpustate64_isssave
#define fpustate_isxsave fpustate64_isxsave
#endif /* __x86_64__ */

#define OFFSET_XFPUSTATE64_FCW        0
#define OFFSET_XFPUSTATE64_FSW        2
#define OFFSET_XFPUSTATE64_FTW        4
#define OFFSET_XFPUSTATE64_FOP        6
#define OFFSET_XFPUSTATE64_FIP        8
#define OFFSET_XFPUSTATE64_FDP        16
#define OFFSET_XFPUSTATE64_MXCSR      24
#define OFFSET_XFPUSTATE64_MXCSR_MASK 28
#define OFFSET_XFPUSTATE64_ST(i)      (32 + (i) * 16)
#define OFFSET_XFPUSTATE64_ST0        32  /* [FIELD(fx_regs[0])] */
#define OFFSET_XFPUSTATE64_ST1        48  /* [FIELD(fx_regs[1])] */
#define OFFSET_XFPUSTATE64_ST2        64  /* [FIELD(fx_regs[2])] */
#define OFFSET_XFPUSTATE64_ST3        80  /* [FIELD(fx_regs[3])] */
#define OFFSET_XFPUSTATE64_ST4        96  /* [FIELD(fx_regs[4])] */
#define OFFSET_XFPUSTATE64_ST5        112 /* [FIELD(fx_regs[5])] */
#define OFFSET_XFPUSTATE64_ST6        128 /* [FIELD(fx_regs[6])] */
#define OFFSET_XFPUSTATE64_ST7        144 /* [FIELD(fx_regs[7])] */
#define OFFSET_XFPUSTATE64_MM(i)      (32 + (i) * 16)
#define OFFSET_XFPUSTATE64_MM0        32  /* [FIELD(fx_regs[0])] */
#define OFFSET_XFPUSTATE64_MM1        48  /* [FIELD(fx_regs[1])] */
#define OFFSET_XFPUSTATE64_MM2        64  /* [FIELD(fx_regs[2])] */
#define OFFSET_XFPUSTATE64_MM3        80  /* [FIELD(fx_regs[3])] */
#define OFFSET_XFPUSTATE64_MM4        96  /* [FIELD(fx_regs[4])] */
#define OFFSET_XFPUSTATE64_MM5        112 /* [FIELD(fx_regs[5])] */
#define OFFSET_XFPUSTATE64_MM6        128 /* [FIELD(fx_regs[6])] */
#define OFFSET_XFPUSTATE64_MM7        144 /* [FIELD(fx_regs[7])] */
#define OFFSET_XFPUSTATE64_XMM(i)     (160 + (i) * 16)
#define OFFSET_XFPUSTATE64_XMM0       160 /* [FIELD(fx_xmm[0])] */
#define OFFSET_XFPUSTATE64_XMM1       176 /* [FIELD(fx_xmm[1])] */
#define OFFSET_XFPUSTATE64_XMM2       192 /* [FIELD(fx_xmm[2])] */
#define OFFSET_XFPUSTATE64_XMM3       208 /* [FIELD(fx_xmm[3])] */
#define OFFSET_XFPUSTATE64_XMM4       224 /* [FIELD(fx_xmm[4])] */
#define OFFSET_XFPUSTATE64_XMM5       240 /* [FIELD(fx_xmm[5])] */
#define OFFSET_XFPUSTATE64_XMM6       256 /* [FIELD(fx_xmm[6])] */
#define OFFSET_XFPUSTATE64_XMM7       272 /* [FIELD(fx_xmm[7])] */
#define OFFSET_XFPUSTATE64_XMM8       288 /* [FIELD(fx_xmm[8])] */
#define OFFSET_XFPUSTATE64_XMM9       304 /* [FIELD(fx_xmm[9])] */
#define OFFSET_XFPUSTATE64_XMM10      320 /* [FIELD(fx_xmm[10])] */
#define OFFSET_XFPUSTATE64_XMM11      336 /* [FIELD(fx_xmm[11])] */
#define OFFSET_XFPUSTATE64_XMM12      352 /* [FIELD(fx_xmm[12])] */
#define OFFSET_XFPUSTATE64_XMM13      368 /* [FIELD(fx_xmm[13])] */
#define OFFSET_XFPUSTATE64_XMM14      384 /* [FIELD(fx_xmm[14])] */
#define OFFSET_XFPUSTATE64_XMM15      400 /* [FIELD(fx_xmm[15])] */
#define SIZEOF_XFPUSTATE64            512
#define ALIGNOF_XFPUSTATE64           16
#ifdef __CC__
struct __ATTR_ALIGNED(ALIGNOF_XFPUSTATE64) xfpustate64 /*[PREFIX(fx_)]*/ {
	/* FPU context structure, as described here:
	 *   - http://asm.inightmare.org/opcodelst/index.php?op=FXSAVE
	 *   - http://x86.renejeschke.de/html/file_module_x86_id_128.html */
	__u16                     fx_fcw;        /* Floating point control word. (Set of `FCW_*') */
	__u16                     fx_fsw;        /* Floating point status word. (Set of `FSW_*') */
	__u8                      fx_ftw;        /* Compressed floating point tag word. (0 << i: FTW_EMPTY(i), 1 << i: FTW_(VALID|ZERO|SPEC)(i) (based on actually loaded value)) */
	__u8                    __fx_pad1;       /* ... */
	__u16                     fx_fop;        /* Lower 11-bit f.p. opcode. */
	__u64                     fx_fip;        /* FPU instruction pointer. */
	__u64                     fx_fdp;        /* FPU data pointer. */
	__u32                     fx_mxcsr;      /* MXCSR (SSE only) (Set of `MXCSR_') */
	__u32                     fx_mxcsr_mask; /* MXCSR mask (SSE only) (Set of `MXCSR_', used to identify available features -- 11.6.6) */
	union ieee854_long_double fx_regs[8];    /* ST(i) / MMi */
	union ieee854_long_double fx_xmm[16];    /* XMMi */
	__u8                    __fx_pad4[96];
};
#endif /* __CC__ */


#define SIZEOF_FPUSTATE64   512
#define ALIGNOF_FPUSTATE64  16
#ifdef __CC__
#undef f_ssave
#undef f_xsave
struct __ATTR_ALIGNED(ALIGNOF_FPUSTATE64) fpustate64 /*[PREFIX(f_)]*/ {
	union {
		struct sfpustate   f_ssave; /* State saved by `fsave' / `fnsave' */
		struct xfpustate64 f_xsave; /* State saved by `fxsave' */
	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_f_kind
#define f_ssave _f_kind.f_ssave
#define f_xsave _f_kind.f_xsave
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	;
};
#define fpustate64_isssave(self) ((self)->f_ssave.__fs_pad2 == 0xffff)
#define fpustate64_isxsave(self) ((self)->f_ssave.__fs_pad2 != 0xffff)
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_KOS_KERNEL_BITS_FPU_STATE64_H */
