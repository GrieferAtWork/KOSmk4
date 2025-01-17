/* HASH CRC-32:0xee8b9e7 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getchar16_defined
#define __local_getchar16_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#include <features.h>
#if defined(__LOCAL_stdin) && ((defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fgetwc) || (defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$getwc) || (defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fgetwc_unlocked) || (defined(__CRT_HAVE_getwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$getwc_unlocked))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fgetc16_defined
#define __local___localdep_fgetc16_defined
#if defined(__CRT_HAVE_fgetwc_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT_DOS(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getwc_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_DOS$getwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT_DOS(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc)
__CREDIRECT_DOS(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_DOS$getwc)
__CREDIRECT_DOS(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc_unlocked)
__CREDIRECT_DOS(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_DOS$getwc_unlocked)
__CREDIRECT_DOS(__ATTR_INOUT(1),__WINT16_TYPE__,__NOTHROW_CB_NCX,__localdep_fgetc16,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#else /* ... */
#undef __local___localdep_fgetc16_defined
#endif /* !... */
#endif /* !__local___localdep_fgetc16_defined */
__LOCAL_LIBC(getchar16) __WINT16_TYPE__
__NOTHROW_CB_NCX(__LIBDCALL __LIBC_LOCAL_NAME(getchar16))(void) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fgetc16)(__LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getchar16_defined
#define __local___localdep_getchar16_defined
#define __localdep_getchar16 __LIBC_LOCAL_NAME(getchar16)
#endif /* !__local___localdep_getchar16_defined */
#else /* __LOCAL_stdin && ((__CRT_HAVE_fgetwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fgetwc || (__CRT_HAVE_getwc && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$getwc || (__CRT_HAVE_fgetwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$fgetwc_unlocked || (__CRT_HAVE_getwc_unlocked && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$getwc_unlocked) */
#undef __local_getchar16_defined
#endif /* !__LOCAL_stdin || ((!__CRT_HAVE_fgetwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fgetwc && (!__CRT_HAVE_getwc || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$getwc && (!__CRT_HAVE_fgetwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$fgetwc_unlocked && (!__CRT_HAVE_getwc_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$getwc_unlocked) */
#endif /* !__local_getchar16_defined */
