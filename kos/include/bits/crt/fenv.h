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
#ifndef _BITS_CRT_FENV_H
#define _BITS_CRT_FENV_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

__SYSDECL_BEGIN

/*[[[enum]]]*/
#ifdef __CC__
enum {
	FE_INVALID   = 0x01, /* == FSW_IE */
	__FE_DENORM  = 0x02, /* == FSW_DE */
	FE_DIVBYZERO = 0x04, /* == FSW_ZE */
	FE_OVERFLOW  = 0x08, /* == FSW_OE */
	FE_UNDERFLOW = 0x10, /* == FSW_UE */
	FE_INEXACT   = 0x20  /* == FSW_PE */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define FE_INVALID   FE_INVALID   /* == FSW_IE */
#define __FE_DENORM  __FE_DENORM  /* == FSW_DE */
#define FE_DIVBYZERO FE_DIVBYZERO /* == FSW_ZE */
#define FE_OVERFLOW  FE_OVERFLOW  /* == FSW_OE */
#define FE_UNDERFLOW FE_UNDERFLOW /* == FSW_UE */
#define FE_INEXACT   FE_INEXACT   /* == FSW_PE */
#else /* __COMPILER_PREFERR_ENUMS */
#define FE_INVALID   0x01 /* == FSW_IE */
#define __FE_DENORM  0x02 /* == FSW_DE */
#define FE_DIVBYZERO 0x04 /* == FSW_ZE */
#define FE_OVERFLOW  0x08 /* == FSW_OE */
#define FE_UNDERFLOW 0x10 /* == FSW_UE */
#define FE_INEXACT   0x20 /* == FSW_PE */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

#define FE_ALL_EXCEPT \
	(FE_INEXACT | FE_DIVBYZERO | FE_UNDERFLOW | FE_OVERFLOW | FE_INVALID)


/*[[[enum]]]*/
#ifdef __CC__
enum {
	FE_TONEAREST  = 0x0000, /* round() */
	FE_DOWNWARD   = 0x0001, /* floor() */
	FE_UPWARD     = 0x0002, /* ceil() */
	FE_TOWARDZERO = 0x0003  /* trunc() */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define FE_TONEAREST  FE_TONEAREST  /* == FCW_RC_NEAREST */
#define FE_DOWNWARD   FE_DOWNWARD   /* == FCW_RC_DOWN */
#define FE_UPWARD     FE_UPWARD     /* == FCW_RC_UP */
#define FE_TOWARDZERO FE_TOWARDZERO /* == FCW_RC_TRUNC */
#else /* __COMPILER_PREFERR_ENUMS */
#define FE_TONEAREST  0x0000 /* == FCW_RC_NEAREST */
#define FE_DOWNWARD   0x0001 /* == FCW_RC_DOWN */
#define FE_UPWARD     0x0002 /* == FCW_RC_UP */
#define FE_TOWARDZERO 0x0003 /* == FCW_RC_TRUNC */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


#ifdef __CC__
typedef __UINTPTR_TYPE__ __fexcept_t;
struct __fenv_struct {
	__UINTPTR_TYPE__ __opaque[64];
};
#endif /* __CC__ */

#define FE_DFL_ENV      (__CCAST(struct __fenv_struct const *)-1) /* If the default argument is used we use this value. */
#define __FE_NOMASK_ENV (__CCAST(struct __fenv_struct const *)-2) /* Floating-point environment where none of the exception is masked. */
#ifdef __USE_GNU
#define FE_NOMASK_ENV   (__CCAST(struct __fenv_struct const *)-2) /* Floating-point environment where none of the exception is masked. */
#endif /* __USE_GNU */


__SYSDECL_END

#endif /* !_BITS_CRT_FENV_H */
