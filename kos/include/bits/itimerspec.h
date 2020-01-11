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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_ITIMERSPEC_H
#define _BITS_ITIMERSPEC_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/timespec.h>
#include <bits/types.h>

#define __OFFSET_ITIMERSPEC_INTERVAL   0
#define __OFFSET_ITIMERSPEC_VALUE      __SIZEOF_TIMESPEC
#define __SIZEOF_ITIMERSPEC            (__SIZEOF_TIMESPEC * 2)
#define __OFFSET_ITIMERSPEC32_INTERVAL 0
#define __OFFSET_ITIMERSPEC32_VALUE    __SIZEOF_TIMESPEC32
#define __SIZEOF_ITIMERSPEC32          (__SIZEOF_TIMESPEC32 * 2)
#define __OFFSET_ITIMERSPEC64_INTERVAL 0
#define __OFFSET_ITIMERSPEC64_VALUE    __SIZEOF_TIMESPEC64
#define __SIZEOF_ITIMERSPEC64          (__SIZEOF_TIMESPEC64 * 2)

#ifdef __CC__
__SYSDECL_BEGIN
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("itimerspec")
#pragma push_macro("it_interval")
#pragma push_macro("it_value")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef itimerspec
#undef it_interval
#undef it_value

#ifndef __itimerspec_defined
#define __itimerspec_defined 1
struct itimerspec /*[PREFIX(it_)]*/ {
	struct timespec it_interval;
	struct timespec it_value;
};
#endif /* !__itimerspec_defined */

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define _ITIMERSPEC_MATCHES_ITIMERSPEC64 1
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */

#ifdef __USE_TIME64
#ifndef __itimerspec64_defined
#define __itimerspec64_defined 1
#if (defined(__USE_TIME_BITS64) || defined(_ITIMERSPEC_MATCHES_ITIMERSPEC64)) && defined(__USE_STRUCT64_MACRO)
#define itimerspec64 itimerspec
#else /* (__USE_TIME_BITS64 || _ITIMERSPEC_MATCHES_ITIMERSPEC64) && __USE_STRUCT64_MACRO */
#define __itimerspec64 itimerspec64
#endif /* (!__USE_TIME_BITS64 && !_ITIMERSPEC_MATCHES_ITIMERSPEC64) || !__USE_STRUCT64_MACRO */
#endif /* !__itimerspec64_defined */
#endif /* __USE_TIME64 */

#if (defined(__USE_TIME_BITS64) || defined(_ITIMERSPEC_MATCHES_ITIMERSPEC64)) && defined(__USE_STRUCT64_MACRO)
#define __itimerspec64 itimerspec
#else /* (__USE_TIME_BITS64 || _ITIMERSPEC_MATCHES_ITIMERSPEC64) && __USE_STRUCT64_MACRO */
struct __itimerspec64 /*[NAME(itimerspec64)][PREFIX(it_)]*/ {
	struct __timespec64 it_interval;
	struct __timespec64 it_value;
};
#endif /* (!__USE_TIME_BITS64 && !_ITIMERSPEC_MATCHES_ITIMERSPEC64) || !__USE_STRUCT64_MACRO */

#ifdef __USE_KOS
#ifndef __itimerspec32_defined
#define __itimerspec32_defined 1
#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define itimerspec32 itimerspec
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#define __itimerspec32 itimerspec32
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__itimerspec32_defined */
#endif /* __USE_KOS */

#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __itimerspec32 itimerspec
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
struct __itimerspec32 /*[NAME(itimerspec32)][PREFIX(it_)]*/ {
	struct __timespec32 it_interval;
	struct __timespec32 it_value;
};
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("it_value")
#pragma pop_macro("it_interval")
#pragma pop_macro("itimerspec")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BITS_ITIMERSPEC_H */
