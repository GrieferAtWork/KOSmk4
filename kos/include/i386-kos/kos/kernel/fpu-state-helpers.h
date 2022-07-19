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
#ifndef _I386_KOS_KOS_KERNEL_FPU_STATE_HELPERS_H
#define _I386_KOS_KOS_KERNEL_FPU_STATE_HELPERS_H 1

#include <hybrid/host.h>

#include <asm/cpu-flags.h>
#include <bits/types.h>

#include <libc/string.h>

#include "fpu-sstate.h"

#ifdef __x86_64__
#include "fpu-state32.h"
#include "fpu-state64.h"
#include "fpu-state-helperscc.h"
#else /* __x86_64__ */
#include "fpu-state32.h"
#endif /* !__x86_64__ */

#ifdef __CC__
__DECL_BEGIN

/* Compress an old-style FTW into a new-style FTWX */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __uint8_t
__NOTHROW(fpustate_ftw2ftwx)(__uint16_t __ftw) {
	unsigned int __i;
	__uint8_t __res = 0;
	for (__i = 0; __i < 8; ++__i) {
		if ((__ftw & FTW_MASK(__i)) != FTW_EMPTY(__i))
			__res |= 1 << __i;
	}
	return __res;
}

#ifdef __cplusplus
extern "C++" {
#define fpustate_ftwx2ftw_long_double fpustate_ftwx2ftw
#define fpustate_ftwx2ftw_float80     fpustate_ftwx2ftw
#endif /* __cplusplus */

/* Decompress a new-style FTWX into an old-style FTW */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((2)) __uint16_t
__NOTHROW(fpustate_ftwx2ftw_long_double)(__uint8_t __ftw, union ieee854_long_double const __sti[8]) {
	unsigned int __i;
	__uint16_t __res = 0;
	for (__i = 0; __i < 8; ++__i) {
		if (__ftw & (1 << __i)) {
			/* s.a. `Table 3-45' in the Intel developer manual */
			if (__sti[__i].ieee_nan.exponent == 0x7fff) {
				/* Special */
				__res |= FTW_SPEC(__i);
			} else if (__sti[__i].ieee_nan.exponent == 0) {
				if (__sti[__i].ieee_nan.mantissa1 == 0 &&
				    __sti[__i].ieee_nan.mantissa0 == 0 &&
					__sti[__i].ieee_nan.one == 0) {
					__res |= FTW_ZERO(__i); /* Fraction all 0's (and j == 0) */
				} else {
					__res |= FTW_SPEC(__i);
				}
			} else if (__sti[__i].ieee_nan.one == 0) {
				__res |= FTW_SPEC(__i);
			} else {
				__res |= FTW_VALID(__i);
			}
		} else {
			__res |= FTW_EMPTY(__i);
		}
	}
	return __res;
}

/* Decompress a new-style FTWX into an old-style FTW */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((2)) __uint16_t
__NOTHROW(fpustate_ftwx2ftw_float80)(__uint8_t __ftw, union ieee854_float80 const __sti[8]) {
	unsigned int __i;
	__uint16_t __res = 0;
	for (__i = 0; __i < 8; ++__i) {
		if (__ftw & (1 << __i)) {
			/* s.a. `Table 3-45' in the Intel developer manual */
			if (__sti[__i].ieee_nan.exponent == 0x7fff) {
				/* Special */
				__res |= FTW_SPEC(__i);
			} else if (__sti[__i].ieee_nan.exponent == 0) {
				if (__sti[__i].ieee_nan.mantissa1 == 0 &&
				    __sti[__i].ieee_nan.mantissa0 == 0 &&
					__sti[__i].ieee_nan.one == 0) {
					__res |= FTW_ZERO(__i); /* Fraction all 0's (and j == 0) */
				} else {
					__res |= FTW_SPEC(__i);
				}
			} else if (__sti[__i].ieee_nan.one == 0) {
				__res |= FTW_SPEC(__i);
			} else {
				__res |= FTW_VALID(__i);
			}
		} else {
			__res |= FTW_EMPTY(__i);
		}
	}
	return __res;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */


__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW(xfpustate_to_sfpustate)(struct xfpustate const *__restrict self,
                                  struct sfpustate *__restrict result) {
	unsigned int i;
	result->fs_fcw = self->fx_fcw;
	result->fs_fsw = self->fx_fsw;
	result->fs_ftw = self->fx_ftw;
	result->fs_fip = self->fx_fip;
	result->fs_fcs = 0;
	result->fs_fop = self->fx_fop & 0x07ff;
	result->fs_fdp = self->fx_fdp;
	result->fs_fds = 0;
	for (i = 0; i < 8; ++i) {
		__libc_memcpy(&result->fs_regs[i], &self->fx_regs[i], 10);
	}
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW(sfpustate_to_xfpustate)(struct sfpustate const *__restrict self,
                                  struct xfpustate *__restrict result) {
	__libc_memset(result, 0, sizeof(struct xfpustate));
	unsigned int i;
	result->fx_fcw = self->fs_fcw;
	result->fx_fsw = self->fs_fsw;
	result->fx_ftw = self->fs_ftw;
	result->fx_fop = self->fs_fop & 0x07ff;
	result->fx_fip = self->fs_fip;
	result->fx_fdp = self->fs_fdp;
	for (i = 0; i < 8; ++i)
		__libc_memcpy(&result->fx_regs[i], &self->fs_regs[i], 10);
}



__DECL_END
#endif /* __CC__ */




#endif /* !_I386_KOS_KOS_KERNEL_FPU_STATE_HELPERS_H */
