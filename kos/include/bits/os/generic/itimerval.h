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
/*!replace_with_include <bits/os/itimerval.h>*/
#ifndef _BITS_OS_KOS_ITIMERVAL_H
#define _BITS_OS_KOS_ITIMERVAL_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/timeval.h>
#include <bits/types.h>

#define __OFFSET_ITIMERVAL_INTERVAL   0
#define __OFFSET_ITIMERVAL_VALUE      __SIZEOF_TIMEVAL
#define __SIZEOF_ITIMERVAL            (__SIZEOF_TIMEVAL * 2)
#define __OFFSET_ITIMERVAL32_INTERVAL 0
#define __OFFSET_ITIMERVAL32_VALUE    __SIZEOF_TIMEVAL32
#define __SIZEOF_ITIMERVAL32          (__SIZEOF_TIMEVAL32 * 2)
#define __OFFSET_ITIMERVAL64_INTERVAL 0
#define __OFFSET_ITIMERVAL64_VALUE    __SIZEOF_TIMEVAL64
#define __SIZEOF_ITIMERVAL64          (__SIZEOF_TIMEVAL64 * 2)

#ifdef __CC__
__SYSDECL_BEGIN
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("itimerval")
#pragma push_macro("it_interval")
#pragma push_macro("it_value")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef itimerval
#undef it_interval
#undef it_value

struct itimerval /*[PREFIX(it_)]*/ {
	struct timeval it_interval;
	struct timeval it_value;
};

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define _ITIMERVAL_MATCHES_ITIMERVAL64 1
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */

#ifdef __USE_TIME64
#if (defined(__USE_TIME_BITS64) || defined(_ITIMERVAL_MATCHES_ITIMERVAL64)) && defined(__USE_STRUCT64_MACRO)
#define itimerval64 itimerval
#else /* (__USE_TIME_BITS64 || _ITIMERVAL_MATCHES_ITIMERVAL64) && __USE_STRUCT64_MACRO */
#define __itimerval64 itimerval64
#endif /* (!__USE_TIME_BITS64 && !_ITIMERVAL_MATCHES_ITIMERVAL64) || !__USE_STRUCT64_MACRO */
#endif /* __USE_TIME64 */

#if (defined(__USE_TIME_BITS64) || defined(_ITIMERVAL_MATCHES_ITIMERVAL64)) && defined(__USE_STRUCT64_MACRO)
#define __itimerval64 itimerval
#else /* (__USE_TIME_BITS64 || _ITIMERVAL_MATCHES_ITIMERVAL64) && __USE_STRUCT64_MACRO */
struct __itimerval64 /*[NAME(itimerval64)][PREFIX(it_)]*/ {
	struct __timeval64 it_interval;
	struct __timeval64 it_value;
};
#endif /* (!__USE_TIME_BITS64 && !_ITIMERVAL_MATCHES_ITIMERVAL64) || !__USE_STRUCT64_MACRO */

#ifdef __USE_KOS
#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define itimerval32 itimerval
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#define __itimerval32 itimerval32
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* __USE_KOS */

#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __itimerval32 itimerval
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
struct __itimerval32 /*[NAME(itimerval32)][PREFIX(it_)]*/ {
	struct __timeval32 it_interval;
	struct __timeval32 it_value;
};
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("it_value")
#pragma pop_macro("it_interval")
#pragma pop_macro("itimerval")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_ITIMERVAL_H */
