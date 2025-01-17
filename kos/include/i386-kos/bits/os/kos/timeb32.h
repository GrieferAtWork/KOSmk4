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
#ifndef _I386_KOS_BITS_OS_KOS_TIMEB32_H
#define _I386_KOS_BITS_OS_KOS_TIMEB32_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef timebx32
#pragma push_macro("timebx32")
#define __PRIVATE_DID_PUSH_TIMEBX32
#endif /* timebx32 */
#ifdef timebx32_64
#pragma push_macro("timebx32_64")
#define __PRIVATE_DID_PUSH_TIMEBX32_64
#endif /* timebx32_64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/*[[[autogen:wrap3264_x32_and_x32_64(
	linkIf:    "defined(__i386__) && !defined(__x86_64__)",
	name:      "timeb",
	name32:    "timebx32",
	name64:    "timebx32_64",
	altname64: "__timebx32_64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_TIME64)",
	link64If:  "defined(__USE_TIME_BITS64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef timebx32
#undef timebx32_64
#if !defined(__i386__) || defined(__x86_64__)
#define timebx32    __timebx32
#define timebx32_64 __timebx32_64
#else /* !__i386__ || __x86_64__ */
#include <features.h>
#ifdef __USE_TIME_BITS64
/* Configure:
 *   - `timebx32_64' as `timeb'
 *   - `timebx32' as `__timeb32' */
#define timebx32      __timeb32
#define timebx32_64   timeb
#define __timebx32    __timeb32
#define __timebx32_64 timeb
#define __timeb32     __timeb32
#define __timeb_alt   __timeb32
#ifdef __USE_KOS
#define timeb32 __timeb32
#endif /* !__USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_STRUCT64_MACRO
#define timeb64   timeb
#define __timeb64 timeb
#else /* __USE_STRUCT64_MACRO */
#define __timebx32_64_alt timeb64
#define __timeb64         timeb64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_TIME64 */
#define __timeb64 timeb
#endif /* !__USE_TIME64 */

#define __OFFSET_TIMEB_TIME     __OFFSET_TIMEBX32_64_TIME
#define __OFFSET_TIMEB_MILLITM  __OFFSET_TIMEBX32_64_MILLITM
#define __OFFSET_TIMEB_TIMEZONE __OFFSET_TIMEBX32_64_TIMEZONE
#define __OFFSET_TIMEB_DSTFLAG  __OFFSET_TIMEBX32_64_DSTFLAG
#define __SIZEOF_TIMEB          __SIZEOF_TIMEBX32_64
#define __ALIGNOF_TIMEB         __ALIGNOF_TIMEBX32_64

#else /* __USE_TIME_BITS64 */
/* Configure:
 *   - `timebx32_64' as `timeb64' or `__timeb64'
 *   - `timebx32' as `timeb' */
#define timebx32   timeb
#define __timeb32  timeb
#define __timebx32 timeb
#ifdef __USE_KOS
#define timeb32 timeb
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#define __timebx32_64 timeb64
#define timebx32_64   timeb64
#define __timeb64     timeb64
#define __timeb_alt   timeb64
#else /* __USE_TIME64 */
#define __timebx32_64 __timeb64
#define timebx32_64   __timeb64
#define __timeb64     __timeb64
#define __timeb_alt   __timeb64
#endif /* !__USE_TIME64 */

#define __OFFSET_TIMEB_TIME     __OFFSET_TIMEBX32_TIME
#define __OFFSET_TIMEB_MILLITM  __OFFSET_TIMEBX32_MILLITM
#define __OFFSET_TIMEB_TIMEZONE __OFFSET_TIMEBX32_TIMEZONE
#define __OFFSET_TIMEB_DSTFLAG  __OFFSET_TIMEBX32_DSTFLAG
#define __SIZEOF_TIMEB          __SIZEOF_TIMEBX32
#define __ALIGNOF_TIMEB         __ALIGNOF_TIMEBX32

#endif /* !__USE_TIME_BITS64 */

#define __OFFSET_TIMEB32_TIME     __OFFSET_TIMEBX32_TIME
#define __OFFSET_TIMEB32_MILLITM  __OFFSET_TIMEBX32_MILLITM
#define __OFFSET_TIMEB32_TIMEZONE __OFFSET_TIMEBX32_TIMEZONE
#define __OFFSET_TIMEB32_DSTFLAG  __OFFSET_TIMEBX32_DSTFLAG
#define __SIZEOF_TIMEB32          __SIZEOF_TIMEBX32
#define __ALIGNOF_TIMEB32         __ALIGNOF_TIMEBX32
#define __OFFSET_TIMEB64_TIME     __OFFSET_TIMEBX32_64_TIME
#define __OFFSET_TIMEB64_MILLITM  __OFFSET_TIMEBX32_64_MILLITM
#define __OFFSET_TIMEB64_TIMEZONE __OFFSET_TIMEBX32_64_TIMEZONE
#define __OFFSET_TIMEB64_DSTFLAG  __OFFSET_TIMEBX32_64_DSTFLAG
#define __SIZEOF_TIMEB64          __SIZEOF_TIMEBX32_64
#define __ALIGNOF_TIMEB64         __ALIGNOF_TIMEBX32_64

#define __timeb_defined
#endif /* __i386__ && !__x86_64__*/
/*[[[end]]]*/

#define __OFFSET_TIMEBX32_TIME        0
#define __OFFSET_TIMEBX32_MILLITM     4
#define __OFFSET_TIMEBX32_TIMEZONE    6
#define __OFFSET_TIMEBX32_DSTFLAG     8
#define __SIZEOF_TIMEBX32             12
#define __ALIGNOF_TIMEBX32            __ALIGNOF_INT32__
#define __OFFSET_TIMEBX32_64_TIME     0
#define __OFFSET_TIMEBX32_64_MILLITM  8
#define __OFFSET_TIMEBX32_64_TIMEZONE 10
#define __OFFSET_TIMEBX32_64_DSTFLAG  12
#define __SIZEOF_TIMEBX32_64          16
#define __ALIGNOF_TIMEBX32_64         __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("time")
#pragma push_macro("millitm")
#pragma push_macro("timezone")
#pragma push_macro("dstflag")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef time
#undef millitm
#undef timezone
#undef dstflag

/* 32-bit timeb for i386 */
struct timebx32 /*[PREFIX()]*/ {
	__INT32_TYPE__  time;     /* Seconds since epoch, as from `time'. */
	__UINT16_TYPE__ millitm;  /* Additional milliseconds. */
	__INT16_TYPE__  timezone; /* Minutes west of GMT. */
	__INT16_TYPE__  dstflag;  /* Nonzero if Daylight Savings Time used. */
	__INT16_TYPE__  __tb_pad; /* ... */
};

/* 64-bit timeb for i386 */
struct timebx32_64 /*[PREFIX()]*/ {
	__INT64_TYPE__  time;     /* Seconds since epoch, as from `time'. */
	__UINT16_TYPE__ millitm;  /* Additional milliseconds. */
	__INT16_TYPE__  timezone; /* Minutes west of GMT. */
	__INT16_TYPE__  dstflag;  /* Nonzero if Daylight Savings Time used. */
	__INT16_TYPE__  __tb_pad; /* ... */
};

#ifdef __timebx32_64_alt
struct __timebx32_64_alt {
	__INT64_TYPE__  time;     /* Seconds since epoch, as from `time'. */
	__UINT16_TYPE__ millitm;  /* Additional milliseconds. */
	__INT16_TYPE__  timezone; /* Minutes west of GMT. */
	__INT16_TYPE__  dstflag;  /* Nonzero if Daylight Savings Time used. */
	__INT16_TYPE__  __tb_pad; /* ... */
};
#undef __timebx32_64_alt
#endif /* __timebx32_64_alt */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("dstflag")
#pragma pop_macro("timezone")
#pragma pop_macro("millitm")
#pragma pop_macro("time")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef timebx32
#undef timebx32_64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_TIMEBX32_64
#undef __PRIVATE_DID_PUSH_TIMEBX32_64
#pragma pop_macro("timebx32_64")
#endif /* __PRIVATE_DID_PUSH_TIMEBX32_64 */
#ifdef __PRIVATE_DID_PUSH_TIMEBX32
#undef __PRIVATE_DID_PUSH_TIMEBX32
#pragma pop_macro("timebx32")
#endif /* __PRIVATE_DID_PUSH_TIMEBX32 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_KOS_TIMEB32_H */
