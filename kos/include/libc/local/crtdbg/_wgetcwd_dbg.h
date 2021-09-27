/* HASH CRC-32:0x13ec4a54 */
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
#ifndef __local__wgetcwd_dbg_defined
#define __local__wgetcwd_dbg_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_wgetcwd) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wgetcwd) || (defined(__CRT_HAVE__wgetcwd) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wgetcwd)
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16getcwd_defined
#define __local___localdep_c16getcwd_defined
#if defined(__CRT_HAVE_wgetcwd) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(,__CHAR16_TYPE__ *,__NOTHROW_RPC,__localdep_c16getcwd,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_DOS$wgetcwd)
__CREDIRECT_DOS(,__CHAR16_TYPE__ *,__NOTHROW_RPC,__localdep_c16getcwd,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE__wgetcwd) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(,__CHAR16_TYPE__ *,__NOTHROW_RPC,__localdep_c16getcwd,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),_wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_DOS$_wgetcwd)
__CREDIRECT_DOS(,__CHAR16_TYPE__ *,__NOTHROW_RPC,__localdep_c16getcwd,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),_wgetcwd,(__buf,__bufsize))
#else /* ... */
#undef __local___localdep_c16getcwd_defined
#endif /* !... */
#endif /* !__local___localdep_c16getcwd_defined */
__LOCAL_LIBC(_wgetcwd_dbg) __ATTR_WUNUSED __WCHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_wgetcwd_dbg))(__WCHAR16_TYPE__ *__buf, __STDC_INT_AS_SIZE_T __buflen, int __block_type, char const *__filename, int __line) {
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return (__WCHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_c16getcwd)((__CHAR16_TYPE__ *)__buf, __buflen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wgetcwd_dbg_defined
#define __local___localdep__wgetcwd_dbg_defined
#define __localdep__wgetcwd_dbg __LIBC_LOCAL_NAME(_wgetcwd_dbg)
#endif /* !__local___localdep__wgetcwd_dbg_defined */
#else /* (__CRT_HAVE_wgetcwd && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wgetcwd || (__CRT_HAVE__wgetcwd && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_wgetcwd */
#undef __local__wgetcwd_dbg_defined
#endif /* (!__CRT_HAVE_wgetcwd || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wgetcwd && (!__CRT_HAVE__wgetcwd || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_wgetcwd */
#endif /* !__local__wgetcwd_dbg_defined */
