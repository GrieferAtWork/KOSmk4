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
/* (#) Portability: Cygwin (/newlib/libc/include/sys/_intsup.h) */
/* (#) Portability: Newlib (/newlib/libc/include/sys/_intsup.h) */
#ifndef _SYS__INTSUP_H
#define _SYS__INTSUP_H 1

#include <features.h> /* Keep this #include here! (for API compatibility) */

#include <hybrid/typecore.h> /* __XXX_IS_YYY__ */

#include <bits/crt/inttypes.h> /* __SCAxxx_PREFIX */


#ifdef __INTPTR_TYPE_IS_LONG_LONG__
#define _INTPTR_EQ_LONGLONG
#elif defined(__INTPTR_TYPE_IS_LONG__)
#define _INTPTR_EQ_LONG
#elif defined(__INTPTR_TYPE_IS_INT__)
#define _INTPTR_EQ_INT
#elif defined(__INTPTR_TYPE_IS_SHORT__)
#define _INTPTR_EQ_SHORT
#endif /* ... */

#ifdef __INT32_TYPE_IS_LONG__
#define _INT32_EQ_LONG
#elif defined(__INT32_TYPE_IS_INT__)
/* #define _INT32_EQ_INT */ /* Not defined in original header. */
#endif /* ... */

/* scanf() prefix strings */
#ifdef __SCA1_PREFIX
#define __INT8 __SCA1_PREFIX
#endif /* __SCA1_PREFIX */
#ifdef __SCA2_PREFIX
#define __INT16 __SCA2_PREFIX
#endif /* __SCA2_PREFIX */
#ifdef __SCA4_PREFIX
#define __INT32 __SCA4_PREFIX
#endif /* __SCA4_PREFIX */
#ifdef __SCA8_PREFIX
#define __INT64 __SCA8_PREFIX
#endif /* __SCA8_PREFIX */
#ifdef __SCAF1_PREFIX
#define __FAST8 __SCAF1_PREFIX
#endif /* __SCAF1_PREFIX */
#ifdef __SCAF2_PREFIX
#define __FAST16 __SCAF2_PREFIX
#endif /* __SCAF2_PREFIX */
#ifdef __SCAF4_PREFIX
#define __FAST32 __SCAF4_PREFIX
#endif /* __SCAF4_PREFIX */
#ifdef __SCAF8_PREFIX
#define __FAST64 __SCAF8_PREFIX
#endif /* __SCAF8_PREFIX */
#ifdef __SCAL1_PREFIX
#define __LEAST8 __SCAL1_PREFIX
#endif /* __SCAL1_PREFIX */
#ifdef __SCAL2_PREFIX
#define __LEAST16 __SCAL2_PREFIX
#endif /* __SCAL2_PREFIX */
#ifdef __SCAL4_PREFIX
#define __LEAST32 __SCAL4_PREFIX
#endif /* __SCAL4_PREFIX */
#ifdef __SCAL8_PREFIX
#define __LEAST64 __SCAL8_PREFIX
#endif /* __SCAL8_PREFIX */


#endif /* !_SYS__INTSUP_H */
