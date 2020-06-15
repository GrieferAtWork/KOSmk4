/* HASH CRC-32:0x4ea03863 */
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
#ifndef __local_getchar32_defined
#define __local_getchar32_defined 1
#include <__crt.h>
#if !defined(__NO_STDSTREAMS) && ((defined(__CRT_HAVE_fgetwc) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fgetwc) || (defined(__CRT_HAVE_getwc) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$getwc))
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fgetc32 from parts.uchar.stdio */
#ifndef __local___localdep_fgetc32_defined
#define __local___localdep_fgetc32_defined 1
#if defined(__CRT_HAVE_fgetwc) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetc32,(__FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_KOS$fgetwc)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetc32,(__FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_getwc) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetc32,(__FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_KOS$getwc)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetc32,(__FILE *__restrict __stream),getwc,(__stream))
#else /* ... */
#undef __local___localdep_fgetc32_defined
#endif /* !... */
#endif /* !__local___localdep_fgetc32_defined */
__NAMESPACE_LOCAL_END
#include <local/stdstreams.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getchar32) __WINT_TYPE__
(__LIBKCALL __LIBC_LOCAL_NAME(getchar32))(void) __THROWS(...) {
	return __localdep_fgetc32(__LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getchar32_defined
#define __local___localdep_getchar32_defined 1
#define __localdep_getchar32 __LIBC_LOCAL_NAME(getchar32)
#endif /* !__local___localdep_getchar32_defined */
#else /* !__NO_STDSTREAMS && ((__CRT_HAVE_fgetwc && (__SIZEOF_WCHAR_T__ == 4) && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$fgetwc || (__CRT_HAVE_getwc && (__SIZEOF_WCHAR_T__ == 4) && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$getwc) */
#undef __local_getchar32_defined
#endif /* __NO_STDSTREAMS || ((!__CRT_HAVE_fgetwc || !(__SIZEOF_WCHAR_T__ == 4) || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$fgetwc && (!__CRT_HAVE_getwc || !(__SIZEOF_WCHAR_T__ == 4) || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$getwc) */
#endif /* !__local_getchar32_defined */
