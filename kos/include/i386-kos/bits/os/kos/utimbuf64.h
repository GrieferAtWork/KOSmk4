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
#ifndef _I386_KOS_BITS_OS_KOS_UTIMBUF64_H
#define _I386_KOS_BITS_OS_KOS_UTIMBUF64_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef utimbufx64
#pragma push_macro("utimbufx64")
#define __PRIVATE_DID_PUSH_UTIMBUFX64
#endif /* utimbufx64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/*[[[autogen:wrap3264_x64(
	linkIf:    "defined(__x86_64__)",
	name:      "utimbuf",
	name64:    "utimbufx64",
	altname64: "__utimbufx64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_TIME64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef utimbufx64
#ifndef __x86_64__
#define utimbufx64 __utimbufx64
#else /* !__x86_64__ */
#include <features.h>
#define __OFFSET_UTIMBUF_ACTIME    __OFFSET_UTIMBUFX64_ACTIME
#define __OFFSET_UTIMBUF_MODTIME   __OFFSET_UTIMBUFX64_MODTIME
#define __SIZEOF_UTIMBUF           __SIZEOF_UTIMBUFX64
#define __ALIGNOF_UTIMBUF          __ALIGNOF_UTIMBUFX64
#define __OFFSET_UTIMBUF32_ACTIME  __OFFSET_UTIMBUFX64_ACTIME
#define __OFFSET_UTIMBUF32_MODTIME __OFFSET_UTIMBUFX64_MODTIME
#define __SIZEOF_UTIMBUF32         __SIZEOF_UTIMBUFX64
#define __ALIGNOF_UTIMBUF32        __ALIGNOF_UTIMBUFX64
#define __OFFSET_UTIMBUF64_ACTIME  __OFFSET_UTIMBUFX64_ACTIME
#define __OFFSET_UTIMBUF64_MODTIME __OFFSET_UTIMBUFX64_MODTIME
#define __SIZEOF_UTIMBUF64         __SIZEOF_UTIMBUFX64
#define __ALIGNOF_UTIMBUF64        __ALIGNOF_UTIMBUFX64
#define utimbufx64                 utimbuf
#define __utimbufx64               utimbuf
#define __utimbuf32                utimbuf
#define __utimbuf_alt              utimbuf
#define _UTIMBUF_MATCHES_UTIMBUF64 1
#ifdef __USE_KOS
#define utimbuf32 utimbuf
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_STRUCT64_MACRO
#define utimbuf64   utimbuf
#define __utimbuf64 utimbuf
#else /* __USE_STRUCT64_MACRO */
#define __utimbufx64_alt utimbuf64
#define __utimbuf64      utimbuf64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_TIME64 */
#define __utimbuf64 utimbuf
#endif /* !__USE_TIME64 */
#define __utimbuf_defined
#endif /* __x86_64__ */
/*[[[end]]]*/

#define __OFFSET_UTIMBUFX64_ACTIME  0
#define __OFFSET_UTIMBUFX64_MODTIME 8
#define __SIZEOF_UTIMBUFX64         16
#define __ALIGNOF_UTIMBUFX64        __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime

/* utimbuf for x86_64 */
struct utimbufx64 /*[PREFIX()]*/ {
	__INT64_TYPE__ actime;  /* Access time. */
	__INT64_TYPE__ modtime; /* Modification time. */
};

#ifdef __utimbufx64_alt
struct __utimbufx64_alt {
	__INT64_TYPE__ actime;  /* Access time. */
	__INT64_TYPE__ modtime; /* Modification time. */
};
#undef __utimbufx64_alt
#endif /* __utimbufx64_alt */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef utimbufx64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_UTIMBUFX64
#undef __PRIVATE_DID_PUSH_UTIMBUFX64
#pragma pop_macro("utimbufx64")
#endif /* __PRIVATE_DID_PUSH_UTIMBUFX64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_KOS_UTIMBUF64_H */
