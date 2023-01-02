/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: EMX kLIBC     (/libc/include/fpu_control.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/fpu_control.h) */
/* (#) Portability: libc4/5       (/include/fpu_control.h) */
#ifndef _ARM_KOS_FPU_CONTROL_H
#define _ARM_KOS_FPU_CONTROL_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

/* Interrupts */
#define _FPU_MASK_IM 0x00000100 /* invalid operation */
#define _FPU_MASK_ZM 0x00000200 /* divide by zero */
#define _FPU_MASK_OM 0x00000400 /* overflow */
#define _FPU_MASK_UM 0x00000800 /* underflow */
#define _FPU_MASK_PM 0x00001000 /* inexact */

#define _FPU_MASK_NZCV   0xf0000000 /* NZCV flags */
#define _FPU_MASK_RM     0x00c00000 /* rounding mode */
#define _FPU_MASK_EXCEPT 0x00001f1f /* all exception flags */

/* Reserved bits in FPU control word */
#define _FPU_RESERVED 0x00086060
#define _FPU_DEFAULT  0x00000000                  /* Default FPU control word */
#define _FPU_IEEE     (_FPU_DEFAULT | 0x00001f00) /* IEEE-compliant FPU control word. */

#ifdef __CC__
__SYSDECL_BEGIN

/* Control word type */
typedef __UINT32_TYPE__ fpu_control_t;

/* >> __fpu_control(3)
 * Control word set during startup of old linux applications. */
#if !defined(__fpu_control) && defined(__CRT_HAVE___fpu_control)
__CSDECLARE(,fpu_control_t,__fpu_control)
#define __fpu_control __fpu_control
#endif /* !__fpu_control && __CRT_HAVE___fpu_control */

/* Access hardware FPU control word. */
#ifdef __SOFTFP__
#define _FPU_GETCW(cw) __asm__ __volatile__("mrc p10, 7, %0, cr1, cr0, 0" : "=r" (cw))  /* fmrx %0, fpscr. */
#define _FPU_SETCW(cw) __asm__ __volatile__("mcr p10, 7, %0, cr1, cr0, 0" : : "r" (cw)) /* fmxr fpscr, %0.  */
#else /* __SOFTFP__ */
#define _FPU_GETCW(cw) __asm__ __volatile__("vmrs %0, fpscr" : "=r" (cw))
#define _FPU_SETCW(cw) __asm__ __volatile__("vmsr fpscr, %0" : : "r" (cw))
#endif /* !__SOFTFP__ */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_ARM_KOS_FPU_CONTROL_H */
