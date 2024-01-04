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
#ifndef _I386_KOS_BITS_OS_KOS_UTIMBUF32_H
#define _I386_KOS_BITS_OS_KOS_UTIMBUF32_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef utimbufx32
#pragma push_macro("utimbufx32")
#define __PRIVATE_DID_PUSH_UTIMBUFX32
#endif /* utimbufx32 */
#ifdef utimbufx32_64
#pragma push_macro("utimbufx32_64")
#define __PRIVATE_DID_PUSH_UTIMBUFX32_64
#endif /* utimbufx32_64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/*[[[autogen:wrap3264_x32_and_x32_64(
	linkIf:    "defined(__i386__) && !defined(__x86_64__)",
	name:      "utimbuf",
	name32:    "utimbufx32",
	name64:    "utimbufx32_64",
	altname64: "__utimbufx32_64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_TIME64)",
	link64If:  "defined(__USE_TIME_BITS64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef utimbufx32
#undef utimbufx32_64
#if !defined(__i386__) || defined(__x86_64__)
#define utimbufx32    __utimbufx32
#define utimbufx32_64 __utimbufx32_64
#else /* !__i386__ || __x86_64__ */
#include <features.h>
#ifdef __USE_TIME_BITS64
/* Configure:
 *   - `utimbufx32_64' as `utimbuf'
 *   - `utimbufx32' as `__utimbuf32' */
#define utimbufx32      __utimbuf32
#define utimbufx32_64   utimbuf
#define __utimbufx32    __utimbuf32
#define __utimbufx32_64 utimbuf
#define __utimbuf32     __utimbuf32
#define __utimbuf_alt   __utimbuf32
#ifdef __USE_KOS
#define utimbuf32 __utimbuf32
#endif /* !__USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_STRUCT64_MACRO
#define utimbuf64   utimbuf
#define __utimbuf64 utimbuf
#else /* __USE_STRUCT64_MACRO */
#define __utimbufx32_64_alt utimbuf64
#define __utimbuf64         utimbuf64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_TIME64 */
#define __utimbuf64 utimbuf
#endif /* !__USE_TIME64 */

#define __OFFSET_UTIMBUF_ACTIME  __OFFSET_UTIMBUFX32_64_ACTIME
#define __OFFSET_UTIMBUF_MODTIME __OFFSET_UTIMBUFX32_64_MODTIME
#define __SIZEOF_UTIMBUF         __SIZEOF_UTIMBUFX32_64
#define __ALIGNOF_UTIMBUF        __ALIGNOF_UTIMBUFX32_64

#else /* __USE_TIME_BITS64 */
/* Configure:
 *   - `utimbufx32_64' as `utimbuf64' or `__utimbuf64'
 *   - `utimbufx32' as `utimbuf' */
#define utimbufx32   utimbuf
#define __utimbuf32  utimbuf
#define __utimbufx32 utimbuf
#ifdef __USE_KOS
#define utimbuf32 utimbuf
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#define __utimbufx32_64 utimbuf64
#define utimbufx32_64   utimbuf64
#define __utimbuf64     utimbuf64
#define __utimbuf_alt   utimbuf64
#else /* __USE_TIME64 */
#define __utimbufx32_64 __utimbuf64
#define utimbufx32_64   __utimbuf64
#define __utimbuf64     __utimbuf64
#define __utimbuf_alt   __utimbuf64
#endif /* !__USE_TIME64 */

#define __OFFSET_UTIMBUF_ACTIME  __OFFSET_UTIMBUFX32_ACTIME
#define __OFFSET_UTIMBUF_MODTIME __OFFSET_UTIMBUFX32_MODTIME
#define __SIZEOF_UTIMBUF         __SIZEOF_UTIMBUFX32
#define __ALIGNOF_UTIMBUF        __ALIGNOF_UTIMBUFX32

#endif /* !__USE_TIME_BITS64 */

#define __OFFSET_UTIMBUF32_ACTIME  __OFFSET_UTIMBUFX32_ACTIME
#define __OFFSET_UTIMBUF32_MODTIME __OFFSET_UTIMBUFX32_MODTIME
#define __SIZEOF_UTIMBUF32         __SIZEOF_UTIMBUFX32
#define __ALIGNOF_UTIMBUF32        __ALIGNOF_UTIMBUFX32
#define __OFFSET_UTIMBUF64_ACTIME  __OFFSET_UTIMBUFX32_64_ACTIME
#define __OFFSET_UTIMBUF64_MODTIME __OFFSET_UTIMBUFX32_64_MODTIME
#define __SIZEOF_UTIMBUF64         __SIZEOF_UTIMBUFX32_64
#define __ALIGNOF_UTIMBUF64        __ALIGNOF_UTIMBUFX32_64

#define __utimbuf_defined
#endif /* __i386__ && !__x86_64__*/
/*[[[end]]]*/

#define __OFFSET_UTIMBUFX32_ACTIME      0
#define __OFFSET_UTIMBUFX32_MODTIME     4
#define __SIZEOF_UTIMBUFX32             8
#define __ALIGNOF_UTIMBUFX32            __ALIGNOF_INT32__
#define __OFFSET_UTIMBUFX32_64_ACTIME   0
#define __OFFSET_UTIMBUFX32_64_MODTIME  8
#define __SIZEOF_UTIMBUFX32_64          16
#define __ALIGNOF_UTIMBUFX32_64         __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime

/* 32-bit utimbuf for i386 */
struct utimbufx32 /*[PREFIX()]*/ {
	__INT32_TYPE__ actime;  /* Access time. */
	__INT32_TYPE__ modtime; /* Modification time. */
};

/* 64-bit utimbuf for i386 */
struct utimbufx32_64 /*[PREFIX()]*/ {
	__INT64_TYPE__ actime;  /* Access time. */
	__INT64_TYPE__ modtime; /* Modification time. */
};

#ifdef __utimbufx32_64_alt
struct __utimbufx32_64_alt {
	__INT64_TYPE__ actime;  /* Access time. */
	__INT64_TYPE__ modtime; /* Modification time. */
};
#undef __utimbufx32_64_alt
#endif /* __utimbufx32_64_alt */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef utimbufx32
#undef utimbufx32_64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_UTIMBUFX32_64
#undef __PRIVATE_DID_PUSH_UTIMBUFX32_64
#pragma pop_macro("utimbufx32_64")
#endif /* __PRIVATE_DID_PUSH_UTIMBUFX32_64 */
#ifdef __PRIVATE_DID_PUSH_UTIMBUFX32
#undef __PRIVATE_DID_PUSH_UTIMBUFX32
#pragma pop_macro("utimbufx32")
#endif /* __PRIVATE_DID_PUSH_UTIMBUFX32 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_KOS_UTIMBUF32_H */
