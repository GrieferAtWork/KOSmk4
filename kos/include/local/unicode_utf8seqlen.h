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
#ifndef __local_utf8_seqlen_defined
#define __local_utf8_seqlen_defined 1
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifdef __utf8_seqlen_defined
#ifdef __cplusplus
using ::unicode_utf8seqlen;
#else /* __cplusplus */
#define __LOCAL_utf8_seqlen  unicode_utf8seqlen
#endif /* !__cplusplus */
#elif defined(__CRT_HAVE_utf8_seqlen)
#ifdef __cplusplus
__LIBC __UINT8_TYPE__ const unicode_utf8seqlen[256];
#elif !defined(__NO_ASMNAME)
__LIBC __UINT8_TYPE__ const __LIBC_LOCAL_NAME(unicode_utf8seqlen)[256] __ASMNAME("unicode_utf8seqlen");
#else
#define __utf8_seqlen_defined 1
__LIBC __UINT8_TYPE__ const unicode_utf8seqlen[256];
#define __LOCAL_utf8_seqlen  unicode_utf8seqlen
#endif
#else
__LOCAL_LIBC_CONST_DATA(unicode_utf8seqlen) __UINT8_TYPE__ const __LIBC_LOCAL_NAME(unicode_utf8seqlen)[256] =
#include "utf8-seqlen.h"
;
#endif
__NAMESPACE_LOCAL_END
#endif /* !__local_utf8_seqlen_defined */
