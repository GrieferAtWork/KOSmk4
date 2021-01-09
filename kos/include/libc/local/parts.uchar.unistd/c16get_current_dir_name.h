/* HASH CRC-32:0x50469a6f */
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
#ifndef __local_c16get_current_dir_name_defined
#define __local_c16get_current_dir_name_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_wgetcwd) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wgetcwd) || (defined(__CRT_HAVE__wgetcwd) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wgetcwd)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16getcwd from parts.uchar.unistd */
#ifndef __local___localdep_c16getcwd_defined
#define __local___localdep_c16getcwd_defined 1
#if defined(__CRT_HAVE_wgetcwd) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,__CHAR16_TYPE__ *,__NOTHROW_RPC,__localdep_c16getcwd,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_DOS$wgetcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT_DOS(,__CHAR16_TYPE__ *,__NOTHROW_RPC,__localdep_c16getcwd,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE__wgetcwd) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,__CHAR16_TYPE__ *,__NOTHROW_RPC,__localdep_c16getcwd,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),_wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_DOS$_wgetcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT_DOS(,__CHAR16_TYPE__ *,__NOTHROW_RPC,__localdep_c16getcwd,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),_wgetcwd,(__buf,__bufsize))
#else /* ... */
#undef __local___localdep_c16getcwd_defined
#endif /* !... */
#endif /* !__local___localdep_c16getcwd_defined */
__LOCAL_LIBC(c16get_current_dir_name) __ATTR_MALLOC __ATTR_WUNUSED __CHAR16_TYPE__ *
__NOTHROW_RPC(__LIBDCALL __LIBC_LOCAL_NAME(c16get_current_dir_name))(void) {
	return __localdep_c16getcwd(__NULLPTR, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16get_current_dir_name_defined
#define __local___localdep_c16get_current_dir_name_defined 1
#define __localdep_c16get_current_dir_name __LIBC_LOCAL_NAME(c16get_current_dir_name)
#endif /* !__local___localdep_c16get_current_dir_name_defined */
#else /* (__CRT_HAVE_wgetcwd && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wgetcwd || (__CRT_HAVE__wgetcwd && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_wgetcwd */
#undef __local_c16get_current_dir_name_defined
#endif /* (!__CRT_HAVE_wgetcwd || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wgetcwd && (!__CRT_HAVE__wgetcwd || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_wgetcwd */
#endif /* !__local_c16get_current_dir_name_defined */
