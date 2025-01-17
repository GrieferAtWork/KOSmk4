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
#ifndef _I386_KOS_BITS_OS_KOS_TIMEB64_H
#define _I386_KOS_BITS_OS_KOS_TIMEB64_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef timebx64
#pragma push_macro("timebx64")
#define __PRIVATE_DID_PUSH_TIMEBX64
#endif /* timebx64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/*[[[autogen:wrap3264_x64(
	linkIf:    "defined(__x86_64__)",
	name:      "timeb",
	name64:    "timebx64",
	altname64: "__timebx64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_TIME64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef timebx64
#ifndef __x86_64__
#define timebx64 __timebx64
#else /* !__x86_64__ */
#include <features.h>
#define __OFFSET_TIMEB_TIME       __OFFSET_TIMEBX64_TIME
#define __OFFSET_TIMEB_MILLITM    __OFFSET_TIMEBX64_MILLITM
#define __OFFSET_TIMEB_TIMEZONE   __OFFSET_TIMEBX64_TIMEZONE
#define __OFFSET_TIMEB_DSTFLAG    __OFFSET_TIMEBX64_DSTFLAG
#define __SIZEOF_TIMEB            __SIZEOF_TIMEBX64
#define __ALIGNOF_TIMEB           __ALIGNOF_TIMEBX64
#define __OFFSET_TIMEB32_TIME     __OFFSET_TIMEBX64_TIME
#define __OFFSET_TIMEB32_MILLITM  __OFFSET_TIMEBX64_MILLITM
#define __OFFSET_TIMEB32_TIMEZONE __OFFSET_TIMEBX64_TIMEZONE
#define __OFFSET_TIMEB32_DSTFLAG  __OFFSET_TIMEBX64_DSTFLAG
#define __SIZEOF_TIMEB32          __SIZEOF_TIMEBX64
#define __ALIGNOF_TIMEB32         __ALIGNOF_TIMEBX64
#define __OFFSET_TIMEB64_TIME     __OFFSET_TIMEBX64_TIME
#define __OFFSET_TIMEB64_MILLITM  __OFFSET_TIMEBX64_MILLITM
#define __OFFSET_TIMEB64_TIMEZONE __OFFSET_TIMEBX64_TIMEZONE
#define __OFFSET_TIMEB64_DSTFLAG  __OFFSET_TIMEBX64_DSTFLAG
#define __SIZEOF_TIMEB64          __SIZEOF_TIMEBX64
#define __ALIGNOF_TIMEB64         __ALIGNOF_TIMEBX64
#define timebx64                  timeb
#define __timebx64                timeb
#define __timeb32                 timeb
#define __timeb_alt               timeb
#define _TIMEB_MATCHES_TIMEB64 1
#ifdef __USE_KOS
#define timeb32 timeb
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_STRUCT64_MACRO
#define timeb64   timeb
#define __timeb64 timeb
#else /* __USE_STRUCT64_MACRO */
#define __timebx64_alt timeb64
#define __timeb64      timeb64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_TIME64 */
#define __timeb64 timeb
#endif /* !__USE_TIME64 */
#define __timeb_defined
#endif /* __x86_64__ */
/*[[[end]]]*/

#define __OFFSET_TIMEBX64_TIME     0
#define __OFFSET_TIMEBX64_MILLITM  8
#define __OFFSET_TIMEBX64_TIMEZONE 10
#define __OFFSET_TIMEBX64_DSTFLAG  12
#define __SIZEOF_TIMEBX64          16
#define __ALIGNOF_TIMEBX64         __ALIGNOF_INT64__

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

/* timeb for x86_64 */
struct timebx64 /*[PREFIX()]*/ {
	__INT64_TYPE__  time;     /* Seconds since epoch, as from `time'. */
	__UINT16_TYPE__ millitm;  /* Additional milliseconds. */
	__INT16_TYPE__  timezone; /* Minutes west of GMT. */
	__INT16_TYPE__  dstflag;  /* Nonzero if Daylight Savings Time used. */
	__INT16_TYPE__  __tb_pad; /* ... */
};

#ifdef __timebx64_alt
struct __timebx64_alt {
	__INT64_TYPE__  time;     /* Seconds since epoch, as from `time'. */
	__UINT16_TYPE__ millitm;  /* Additional milliseconds. */
	__INT16_TYPE__  timezone; /* Minutes west of GMT. */
	__INT16_TYPE__  dstflag;  /* Nonzero if Daylight Savings Time used. */
	__INT16_TYPE__  __tb_pad; /* ... */
};
#undef __timebx64_alt
#endif /* __timebx64_alt */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("dstflag")
#pragma pop_macro("timezone")
#pragma pop_macro("millitm")
#pragma pop_macro("time")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef timebx64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_TIMEBX64
#undef __PRIVATE_DID_PUSH_TIMEBX64
#pragma pop_macro("timebx64")
#endif /* __PRIVATE_DID_PUSH_TIMEBX64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_KOS_TIMEB64_H */
