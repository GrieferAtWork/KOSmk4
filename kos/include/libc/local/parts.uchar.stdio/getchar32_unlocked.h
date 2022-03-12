/* HASH CRC-32:0x7907b108 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getchar32_unlocked_defined
#define __local_getchar32_unlocked_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#if defined(__LOCAL_stdin) && ((defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fgetwc_unlocked) || (defined(__CRT_HAVE_getwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$getwc_unlocked) || (defined(__CRT_HAVE__getwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_getwc_nolock) || (defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fgetwc_nolock))
#include <hybrid/typecore.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fgetc32_unlocked_defined
#define __local___localdep_fgetc32_unlocked_defined
#if defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_KOS$fgetwc_unlocked)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_KOS$getwc_unlocked)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),_getwc_nolock,(__stream))
#elif defined(__CRT_HAVE_KOS$_getwc_nolock)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),_getwc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_KOS$_fgetwc_nolock)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__WINT32_TYPE__,__THROWING,__localdep_fgetc32_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#else /* ... */
#undef __local___localdep_fgetc32_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fgetc32_unlocked_defined */
__LOCAL_LIBC(getchar32_unlocked) __WINT32_TYPE__
(__LIBKCALL __LIBC_LOCAL_NAME(getchar32_unlocked))(void) __THROWS(...) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fgetc32_unlocked)(__LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getchar32_unlocked_defined
#define __local___localdep_getchar32_unlocked_defined
#define __localdep_getchar32_unlocked __LIBC_LOCAL_NAME(getchar32_unlocked)
#endif /* !__local___localdep_getchar32_unlocked_defined */
#else /* __LOCAL_stdin && ((__CRT_HAVE_fgetwc_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$fgetwc_unlocked || (__CRT_HAVE_getwc_unlocked && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$getwc_unlocked || (__CRT_HAVE__getwc_nolock && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_getwc_nolock || (__CRT_HAVE__fgetwc_nolock && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_fgetwc_nolock) */
#undef __local_getchar32_unlocked_defined
#endif /* !__LOCAL_stdin || ((!__CRT_HAVE_fgetwc_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$fgetwc_unlocked && (!__CRT_HAVE_getwc_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$getwc_unlocked && (!__CRT_HAVE__getwc_nolock || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_getwc_nolock && (!__CRT_HAVE__fgetwc_nolock || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_fgetwc_nolock) */
#endif /* !__local_getchar32_unlocked_defined */
