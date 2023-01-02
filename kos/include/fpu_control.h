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
#ifndef _FPU_CONTROL_H
#define _FPU_CONTROL_H 1

#include <__stdinc.h>

#if 0 /* To-be overwritten by arch-specific headers */
#include <__crt.h>
#ifdef __CC__
__SYSDECL_BEGIN

typedef NATIVE_FPU_CONTROL_WORD_TYPE fpu_control_t;

/* Access hardware FPU control word. */
#define _FPU_GETCW(cw) (void)((cw) = NATIVE_FPU_CONTROL_WORD)
#define _FPU_SETCW(cw) (void)(NATIVE_FPU_CONTROL_WORD = (cw))

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
#endif

#endif /* !_FPU_CONTROL_H */
