/* HASH CRC-32:0x7ca14db3 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__wgetcwd_dbg_defined
#if defined(__CRT_HAVE_c16getcwd) || defined(__CRT_HAVE_DOS$_wgetcwd) || defined(__CRT_HAVE_wgetcwd) || defined(__CRT_HAVE__wgetcwd)
#define __local__wgetcwd_dbg_defined 1
/* Dependency: "c16getcwd" from "parts.uchar.unistd" */
#ifndef ____localdep_c16getcwd_defined
#define ____localdep_c16getcwd_defined 1
#if defined(__CRT_HAVE_wgetcwd) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `c16chdir(2)' */
__CREDIRECT(,__CHAR16_TYPE__ *,__NOTHROW_RPC,__localdep_c16getcwd,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE_DOS$_wgetcwd)
/* >> c16getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `c16chdir(2)' */
__CREDIRECT_DOS(,__CHAR16_TYPE__ *,__NOTHROW_RPC,__localdep_c16getcwd,(__CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),_wgetcwd,(__buf,__bufsize))
#else /* LIBC: wgetcwd */
#undef ____localdep_c16getcwd_defined
#endif /* c16getcwd... */
#endif /* !____localdep_c16getcwd_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_wgetcwd_dbg) __ATTR_WUNUSED __WCHAR16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wgetcwd_dbg))(__WCHAR16_TYPE__ *__buf,
                                                          __STDC_INT_AS_SIZE_T __buflen,
                                                          int __block_type,
                                                          char const *__filename,
                                                          int __line) {
#line 488 "kos/src/libc/magic/crtdbg.c"
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return (__WCHAR16_TYPE__ *)__localdep_c16getcwd((__CHAR16_TYPE__ *)__buf, __buflen);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_c16getcwd || __CRT_HAVE_DOS$_wgetcwd || __CRT_HAVE_wgetcwd || __CRT_HAVE__wgetcwd */
#endif /* !__local__wgetcwd_dbg_defined */
