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
/*!replace_with_include <kos/kernel/fpu-state-helperscc.h>*/
#ifndef _I386_KOS_KOS_KERNEL_BITS_FPU_STATE_HELPERSCC_H
#define _I386_KOS_KOS_KERNEL_BITS_FPU_STATE_HELPERSCC_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#include <bits/types.h>

#include <libc/string.h>

#include "fpu-state32.h"
#include "fpu-state64.h"

#ifdef __CC__
__DECL_BEGIN

#if (SIZEOF_XFPUSTATE32 != SIZEOF_XFPUSTATE64) || (SIZEOF_XFPUSTATE32 != 512)
#error "These should be identical, and both be equal to `512'!"
#endif /* ... */
#if (OFFSET_XFPUSTATE32_MXCSR != OFFSET_XFPUSTATE64_MXCSR)
#error "These should be identical"
#endif /* ... */

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(xfpustate64_assign_xfpustate32)(struct xfpustate64 *__restrict __self,
                                              struct xfpustate32 const *__restrict __data) {
	/* Copy data leading up the IP/DP pointers */
	__libc_memcpy(__self, __data, OFFSET_XFPUSTATE32_FIP);
	/* The IP/DP pointers were changed between i386/x86_64 */
	__self->fx_fip = __data->fx_fip;
	__self->fx_fdp = __data->fx_fdp;
	/* Copy remaining data one-on-one, but stop after XMM register #7
	 * In  32-bit mode, only  8 XMM registers  are available, so when
	 * converting the FPU  state structure, leave  64-bit mode's  XMM
	 * register #8-#15 unchanged. */
	__libc_memcpy((__byte_t *)__self + OFFSET_XFPUSTATE64_MXCSR,
	              (__byte_t const *)__data + OFFSET_XFPUSTATE32_MXCSR,
	              OFFSET_XFPUSTATE32_XMM(8) - OFFSET_XFPUSTATE32_MXCSR);
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(xfpustate64_to_xfpustate32)(struct xfpustate64 const *__restrict __self,
                                          struct xfpustate32 *__restrict __result) {
	__libc_memcpy(__result, __self, SIZEOF_XFPUSTATE32);
	__result->fx_fip  = (__uint32_t)__self->fx_fip;
	__result->fx_fcs  = 0;
	__result->fx_fdp  = (__uint32_t)__self->fx_fdp;
	__result->fx_fds  = 0;
	__result->__fx_pad2 = 0;
	__result->__fx_pad3 = 0;
}


#ifdef __x86_64__
#define xfpustate_assign_xfpustate32 xfpustate64_assign_xfpustate32
#define xfpustate_to_xfpustate32     xfpustate64_to_xfpustate32
#else /* __x86_64__ */
#define xfpustate64_assign_xfpustate xfpustate64_assign_xfpustate32
#define xfpustate64_to_xfpustate     xfpustate64_to_xfpustate32
#endif /* !__x86_64__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_KERNEL_BITS_FPU_STATE_HELPERSCC_H */
