/* HASH CRC-32:0x60931de8 */
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
#ifndef __local_getchar16_unlocked_defined
#define __local_getchar16_unlocked_defined 1
#include <__crt.h>
#if ((defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fgetwc_unlocked) || (defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_fgetwc_nolock)) && !defined(__NO_STDSTREAMS)
#include <hybrid/typecore.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fgetc16_unlocked_defined
#define __local___localdep_fgetc16_unlocked_defined 1
#if defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetc16_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc_unlocked)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetc16_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetc16_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_DOS$_fgetwc_nolock)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,__localdep_fgetc16_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#else /* ... */
#undef __local___localdep_fgetc16_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fgetc16_unlocked_defined */
__NAMESPACE_LOCAL_END
#include <libc/local/stdstreams.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getchar16_unlocked) __WINT_TYPE__
(__LIBDCALL __LIBC_LOCAL_NAME(getchar16_unlocked))(void) __THROWS(...) {
	return __localdep_fgetc16_unlocked(__LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getchar16_unlocked_defined
#define __local___localdep_getchar16_unlocked_defined 1
#define __localdep_getchar16_unlocked __LIBC_LOCAL_NAME(getchar16_unlocked)
#endif /* !__local___localdep_getchar16_unlocked_defined */
#else /* ((__CRT_HAVE_fgetwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fgetwc_unlocked || (__CRT_HAVE__fgetwc_nolock && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_fgetwc_nolock) && !__NO_STDSTREAMS */
#undef __local_getchar16_unlocked_defined
#endif /* ((!__CRT_HAVE_fgetwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fgetwc_unlocked && (!__CRT_HAVE__fgetwc_nolock || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_fgetwc_nolock) || __NO_STDSTREAMS */
#endif /* !__local_getchar16_unlocked_defined */
