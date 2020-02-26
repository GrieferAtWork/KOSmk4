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
#ifndef _BITS_UTIMBUF_H
#define _BITS_UTIMBUF_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#define __OFFSET_UTIMBUF_ACTIME     0
#define __OFFSET_UTIMBUF_MODTIME    __TM_SIZEOF(TIME)
#define __SIZEOF_UTIMBUF            (__TM_SIZEOF(TIME) * 2)
#define __OFFSET_UTIMBUF32_ACTIME   0
#define __OFFSET_UTIMBUF32_MODTIME  __SIZEOF_TIME32_T__
#define __SIZEOF_UTIMBUF32          (__SIZEOF_TIME32_T__ * 2)
#define __OFFSET_UTIMBUF64_ACTIME   0
#define __OFFSET_UTIMBUF64_MODTIME  __SIZEOF_TIME64_T__
#define __SIZEOF_UTIMBUF64          (__SIZEOF_TIME64_T__ * 2)

#ifdef __CC__
__SYSDECL_BEGIN
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime

#ifndef __utimbuf_defined
#define __utimbuf_defined 1
struct utimbuf /*[PREFIX()]*/ {
	__TM_TYPE(time) actime;  /* Access time. */
	__TM_TYPE(time) modtime; /* Modification time. */
};
#endif /* !__utimbuf_defined */

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define _UTIMBUF_MATCHES_UTIMBUF64 1
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */

#ifdef __USE_TIME64
#ifndef __utimbuf64_defined
#define __utimbuf64_defined 1
#if (defined(__USE_TIME_BITS64) || defined(_UTIMBUF_MATCHES_UTIMBUF64)) && defined(__USE_STRUCT64_MACRO)
#define utimbuf64 utimbuf
#else /* (__USE_TIME_BITS64 || _UTIMBUF_MATCHES_UTIMBUF64) && __USE_STRUCT64_MACRO */
#define __utimbuf64 utimbuf64
#endif /* (!__USE_TIME_BITS64 && !_UTIMBUF_MATCHES_UTIMBUF64) || !__USE_STRUCT64_MACRO */
#endif /* !__utimbuf64_defined */
#endif /* __USE_TIME64 */

#if (defined(__USE_TIME_BITS64) || defined(_UTIMBUF_MATCHES_UTIMBUF64)) && defined(__USE_STRUCT64_MACRO)
#define __utimbuf64 utimbuf
#else /* (__USE_TIME_BITS64 || _UTIMBUF_MATCHES_UTIMBUF64) && __USE_STRUCT64_MACRO */
struct __utimbuf64 /*[NAME(utimbuf64)][PREFIX()]*/ {
	__time64_t actime;  /* Access time. */
	__time64_t modtime; /* Modification time. */
};
#endif /* (!__USE_TIME_BITS64 && !_UTIMBUF_MATCHES_UTIMBUF64) || !__USE_STRUCT64_MACRO */

#ifdef __USE_KOS
#ifndef __utimbuf32_defined
#define __utimbuf32_defined 1
#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define utimbuf32 utimbuf
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#define __utimbuf32 utimbuf32
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* !__utimbuf32_defined */
#endif /* __USE_KOS */

#if !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __utimbuf32 utimbuf
#else /* !__USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
struct __utimbuf32 /*[NAME(utimbuf32)][PREFIX()]*/ {
	__time32_t actime;  /* Access time. */
	__time32_t modtime; /* Modification time. */
};
#endif /* __USE_TIME_BITS64 && __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__SYSDECL_END
#endif /* __CC__ */


#endif /* !_BITS_UTIMBUF_H */
