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
/*!replace_with_include <bits/os/timeb.h>*/
#ifndef _BITS_OS_KOS_TIMEB_H
#define _BITS_OS_KOS_TIMEB_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#define __OFFSET_TIMEB_TIME       0
#define __OFFSET_TIMEB_MILLITM    __SIZEOF_TIME_T__
#define __OFFSET_TIMEB_TIMEZONE   (__SIZEOF_TIME_T__ + 2)
#define __OFFSET_TIMEB_DSTFLAG    (__SIZEOF_TIME_T__ + 4)
#define __SIZEOF_TIMEB            (__SIZEOF_TIME_T__ + 8)
#define __OFFSET_TIMEB32_TIME     0
#define __OFFSET_TIMEB32_MILLITM  __SIZEOF_TIME32_T__
#define __OFFSET_TIMEB32_TIMEZONE (__SIZEOF_TIME32_T__ + 2)
#define __OFFSET_TIMEB32_DSTFLAG  (__SIZEOF_TIME32_T__ + 4)
#define __SIZEOF_TIMEB32          (__SIZEOF_TIME32_T__ + 8)
#define __OFFSET_TIMEB64_TIME     0
#define __OFFSET_TIMEB64_MILLITM  __SIZEOF_TIME64_T__
#define __OFFSET_TIMEB64_TIMEZONE (__SIZEOF_TIME64_T__ + 2)
#define __OFFSET_TIMEB64_DSTFLAG  (__SIZEOF_TIME64_T__ + 4)
#define __SIZEOF_TIMEB64          (__SIZEOF_TIME64_T__ + 8)

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("timeb")
#pragma push_macro("time")
#pragma push_macro("millitm")
#pragma push_macro("timezone")
#pragma push_macro("dstflag")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef timeb
#undef time
#undef millitm
#undef timezone
#undef dstflag

struct timeb /*[PREFIX()]*/ {
	__time_t        time;     /* Seconds since epoch, as from `time'. */
	__UINT16_TYPE__ millitm;  /* Additional milliseconds. */
	__INT16_TYPE__  timezone; /* Minutes west of GMT. */
	__INT16_TYPE__  dstflag;  /* Nonzero if Daylight Savings Time used. */
	__INT16_TYPE__  __tb_pad; /* ... */
};

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define _TIMEB_MATCHES_TIMEB64 1
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */

#ifdef __USE_TIME64
#if (defined(__USE_TIME_BITS64) || defined(_TIMEB_MATCHES_TIMEB64)) && defined(__USE_STRUCT64_MACRO)
#define timeb64 timeb
#else /* (__USE_TIME_BITS64 || _TIMEB_MATCHES_TIMEB64) && __USE_STRUCT64_MACRO */
#define __timeb64 timeb64
#endif /* (!__USE_TIME_BITS64 && !_TIMEB_MATCHES_TIMEB64) || !__USE_STRUCT64_MACRO */
#endif /* __USE_TIME64 */

#if (defined(__USE_TIME_BITS64) || defined(_TIMEB_MATCHES_TIMEB64)) && defined(__USE_STRUCT64_MACRO)
#define __timeb64 timeb
#else /* (__USE_TIME_BITS64 || _TIMEB_MATCHES_TIMEB64) && __USE_STRUCT64_MACRO */
struct __timeb64 /*[NAME(timeb64)][PREFIX()]*/ {
	__time64_t      time;     /* Seconds since epoch, as from `time'. */
	__UINT16_TYPE__ millitm;  /* Additional milliseconds. */
	__INT16_TYPE__  timezone; /* Minutes west of GMT. */
	__INT16_TYPE__  dstflag;  /* Nonzero if Daylight Savings Time used. */
	__INT16_TYPE__  __tb_pad; /* ... */
};
#endif /* (!__USE_TIME_BITS64 && !_TIMEB_MATCHES_TIMEB64) || !__USE_STRUCT64_MACRO */

#ifdef __USE_KOS
#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define timeb32 timeb
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#define __timeb32 timeb32
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* __USE_KOS */

#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __timeb32 timeb
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
struct __timeb32 /*[NAME(timeb32)][PREFIX()]*/ {
	__time32_t      time;     /* Seconds since epoch, as from `time'. */
	__UINT16_TYPE__ millitm;  /* Additional milliseconds. */
	__INT16_TYPE__  timezone; /* Minutes west of GMT. */
	__INT16_TYPE__  dstflag;  /* Nonzero if Daylight Savings Time used. */
	__INT16_TYPE__  __tb_pad; /* ... */
};
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("dstflag")
#pragma pop_macro("timezone")
#pragma pop_macro("millitm")
#pragma pop_macro("time")
#pragma pop_macro("timeb")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_TIMEB_H */
