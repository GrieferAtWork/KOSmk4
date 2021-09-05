/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __LOCAL_unicode_utf8seqlen
#ifdef __utf8_seqlen_defined
#define __LOCAL_unicode_utf8seqlen unicode_utf8seqlen
#else /* __utf8_seqlen_defined */
#include <__crt.h>
#include <hybrid/typecore.h>
#ifdef __utf8_seqlen_defined
#define __LOCAL_unicode_utf8seqlen unicode_utf8seqlen
#else /* __utf8_seqlen_defined */
#ifdef __CRT_HAVE_unicode_utf8seqlen
#ifndef __NO_ASMNAME
__LIBC __UINT8_TYPE__ const __LOCAL_unicode_utf8seqlen[256] __CASMNAME("unicode_utf8seqlen");
#define __LOCAL_unicode_utf8seqlen __LOCAL_unicode_utf8seqlen
#else /* !__NO_ASMNAME */
#define __utf8_seqlen_defined      1
__LIBC __UINT8_TYPE__ const unicode_utf8seqlen[256] __CASMNAME_SAME("unicode_utf8seqlen");
#define __LOCAL_unicode_utf8seqlen unicode_utf8seqlen
#endif /* __NO_ASMNAME */
#elif defined(__cplusplus)
#define __LOCAL_unicode_utf8seqlen (__LOCAL_unicode_utf8seqlen_p())
__ATTR_VISIBILITY("hidden")
__ATTR_FORCEINLINE __ATTR_UNUSED __UINT8_TYPE__ const *(__LOCAL_unicode_utf8seqlen_p)(void) {
	__ATTR_VISIBILITY("hidden")
	static __LOCAL_LIBC_CONST_DATA_SECTION(unicode_utf8seqlen)
	__UINT8_TYPE__ const __unicode_utf8seqlen_p[256] =
#include "utf8-seqlen.h"
	;
	return __unicode_utf8seqlen_p;
}
#else /* ... */
#define __LOCAL_unicode_utf8seqlen unicode_utf8seqlen
__LOCAL_LIBC_CONST_DATA(unicode_utf8seqlen)
__UINT8_TYPE__ const unicode_utf8seqlen[256] =
#include "utf8-seqlen.h"
;
#endif /* !... */
#endif /* !__utf8_seqlen_defined */
#endif /* !__utf8_seqlen_defined */
#endif /* !__LOCAL_unicode_utf8seqlen */
