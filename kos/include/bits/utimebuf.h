/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _BITS_UTIMEBUF_H
#define _BITS_UTIMEBUF_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime

struct utimbuf {
	__TM_TYPE(time) actime;  /* Access time. */
	__TM_TYPE(time) modtime; /* Modification time. */
};

#if __TM_SIZEOF(TIME) <= 4
#define __utimbuf64  __utimbuf_alt
#define __utimbuf32  utimbuf
#else /* __TM_SIZEOF(TIME) <= 4 */
#define __utimbuf64  utimbuf
#define __utimbuf32  __utimbuf_alt
#endif /* __TM_SIZEOF(TIME) > 4 */

#ifdef __USE_TIME64
#if __TM_SIZEOF(TIME) <= 4
#define __utimbuf_alt utimbuf64
#else /* __TM_SIZEOF(TIME) <= 4 */
#define utimbuf64     utimbuf
#endif /* __TM_SIZEOF(TIME) > 4 */
#endif /* __USE_TIME64 */

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#if defined(__USE_TIME64) && __TM_SIZEOF(TIME) <= 4
#define utimbuf64     utimbuf
#else /* __USE_TIME64 && __TM_SIZEOF(TIME) <= 4 */
#define __utimbuf_alt utimbuf
#endif /* !__USE_TIME64 || __TM_SIZEOF(TIME) > 4 */
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
struct __utimbuf_alt {
#if __TM_SIZEOF(TIME) <= 4
	__time64_t      actime;  /* Access time. */
	__time64_t      modtime; /* Modification time. */
#else /* __TM_SIZEOF(TIME) <= 4 */
	__time32_t      actime;  /* Access time. */
	__time32_t      modtime; /* Modification time. */
#endif /* __TM_SIZEOF(TIME) > 4 */
};
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__SYSDECL_END
#endif /* __CC__ */


#endif /* !_BITS_UTIMEBUF_H */
