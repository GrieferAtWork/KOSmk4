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
/* (#) Portability: EMX kLIBC     (/libc/include/fpu_control.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/fpu_control.h) */
/* (#) Portability: libc4/5       (/include/fpu_control.h) */
#ifndef _I386_KOS_FPU_CONTROL_H
#define _I386_KOS_FPU_CONTROL_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <asm/intrin-fpu.h>

/* Interrupts */
#define _FPU_MASK_IM 0x01
#define _FPU_MASK_DM 0x02
#define _FPU_MASK_ZM 0x04
#define _FPU_MASK_OM 0x08
#define _FPU_MASK_UM 0x10
#define _FPU_MASK_PM 0x20

/* Precision */
#define _FPU_EXTENDED 0x300
#define _FPU_DOUBLE   0x200
#define _FPU_SINGLE   0x000

/* Rounding */
#define _FPU_RC_NEAREST 0x000
#define _FPU_RC_DOWN    0x400
#define _FPU_RC_UP      0x800
#define _FPU_RC_ZERO    0xc00

/* Reserved bits in FPU control word */
#define _FPU_RESERVED 0xf0c0

#define _FPU_DEFAULT 0x137f /* Default FPU control word */
#define _FPU_IEEE    0x137f /* IEEE-compliant FPU control word. */

#ifdef __CC__
__SYSDECL_BEGIN

/* Control word type */
typedef __UINT16_TYPE__ fpu_control_t;

/* Access hardware FPU control word. */
#define _FPU_GETCW(cw) (void)((cw) = __fnstcw())
#define _FPU_SETCW(cw) __fldcw(cw)

/* >> __fpu_control(3)
 * Control word set during startup of old linux applications. */
#if !defined(__fpu_control) && defined(__CRT_HAVE___fpu_control)
__CSDECLARE(,fpu_control_t,__fpu_control)
#define __fpu_control __fpu_control
#endif /* !__fpu_control && __CRT_HAVE___fpu_control */

/* >> __setfpucw(3)
 * Function called by old linux applications to set `__fpu_control()'. */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,__setfpucw,(fpu_control_t __ctrl),(__ctrl))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_FPU_CONTROL_H */
