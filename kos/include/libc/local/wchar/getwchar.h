/* HASH CRC-32:0x5aa85002 */
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
#ifndef __local_getwchar_defined
#define __local_getwchar_defined 1
#include <__crt.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc))
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fgetwc_defined
#define __local___localdep_fgetwc_defined 1
#ifdef __CRT_HAVE_fgetwc
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetwc,(__FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_getwc)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetwc,(__FILE *__restrict __stream),getwc,(__stream))
#else /* ... */
#undef __local___localdep_fgetwc_defined
#endif /* !... */
#endif /* !__local___localdep_fgetwc_defined */
__NAMESPACE_LOCAL_END
#include <libc/local/stdstreams.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getwchar) __WINT_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(getwchar))(void) __THROWS(...) {
	return __localdep_fgetwc(__LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getwchar_defined
#define __local___localdep_getwchar_defined 1
#define __localdep_getwchar __LIBC_LOCAL_NAME(getwchar)
#endif /* !__local___localdep_getwchar_defined */
#else /* !__NO_STDSTREAMS && (__CRT_HAVE_fgetwc || __CRT_HAVE_getwc) */
#undef __local_getwchar_defined
#endif /* __NO_STDSTREAMS || (!__CRT_HAVE_fgetwc && !__CRT_HAVE_getwc) */
#endif /* !__local_getwchar_defined */
