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
/*!replace_with_include <fenv.h>*/
#ifndef _I386_KOS_BITS_CRT_FENV_H
#define _I386_KOS_BITS_CRT_FENV_H 1

#include <__stdinc.h>

#include <hybrid/__bitfield.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

#define __fexcept_t __UINT16_TYPE__

#define __femode_t __femode_t
typedef struct {
	__UINT16_TYPE__ __control_word;
	__UINT16_TYPE__ __glibc_reserved;
	__UINT32_TYPE__ __mxcsr;
} __femode_t;

/* Type representing floating-point environment.
 * This  structure corresponds to  the layout of  the block written by
 * the `fstenv' instruction and has additional fields for the contents
 * of the MXCSR register as written by the `stmxcsr' instruction.
 * HINT: Under KOS, this structure also exists as `struct sfpuenv' */
struct __fenv_struct {
	__UINT16_TYPE__       __control_word;        /* struct sfpuenv::fe_fcw (Set of `FCW_*') */
	__UINT16_TYPE__       __glibc_reserved1;     /* ... */
	__UINT16_TYPE__       __status_word;         /* struct sfpuenv::fe_fsw (Set of `FSW_*') */
	__UINT16_TYPE__       __glibc_reserved2;     /* ... */
	__UINT16_TYPE__       __tags;                /* struct sfpuenv::fe_ftw (Set of `FTW_*') */
	__UINT16_TYPE__       __glibc_reserved3;     /* ... */
	__UINT32_TYPE__       __eip;                 /* struct sfpuenv::fe_fip */
	__UINT16_TYPE__       __cs_selector;         /* struct sfpuenv::fe_fcs */
	__HYBRID_BITFIELD16_T __opcode : 11;         /* struct sfpuenv::fe_fop */
	__HYBRID_BITFIELD16_T __glibc_reserved4 : 5; /* ... */
	__UINT32_TYPE__       __data_offset;         /* struct sfpuenv::fe_fdp */
	__UINT16_TYPE__       __data_selector;       /* struct sfpuenv::fe_fds */
	__UINT16_TYPE__       __glibc_reserved5;     /* ... */
#ifdef __x86_64__
	__UINT32_TYPE__       __mxcsr; /* Not actually found in `struct sfpuenv' */
#endif /* __x86_64__ */
};

__DECL_END
#endif /* __CC__ */

#define __FE_DFL_ENV    (__CCAST(struct __fenv_struct const *)-1) /* If the default argument is used we use this value. */
#define __FE_NOMASK_ENV (__CCAST(struct __fenv_struct const *)-2) /* Floating-point environment where none of the exception is masked. */
#define __FE_DFL_MODE   ((__femode_t const *)-1)

#endif /* !_I386_KOS_BITS_CRT_FENV_H */
