/* HASH CRC-32:0x34b191a7 */
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
#ifndef __local_wget_current_dir_name_defined
#if (defined(__CRT_HAVE_wgetcwd) || defined(__CRT_HAVE__wgetcwd))
#define __local_wget_current_dir_name_defined 1
/* Dependency: "wgetcwd" from "parts.wchar.unistd" */
#ifndef ____localdep_wgetcwd_defined
#define ____localdep_wgetcwd_defined 1
#if defined(__CRT_HAVE_wgetcwd)
/* >> wgetcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `wchdir(2)' */
__CREDIRECT(,__WCHAR_TYPE__ *,__NOTHROW_RPC,__localdep_wgetcwd,(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),wgetcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE__wgetcwd)
/* >> wgetcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `wchdir(2)' */
__CREDIRECT(,__WCHAR_TYPE__ *,__NOTHROW_RPC,__localdep_wgetcwd,(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),_wgetcwd,(__buf,__bufsize))
#else /* LIBC: wgetcwd */
#undef ____localdep_wgetcwd_defined
#endif /* wgetcwd... */
#endif /* !____localdep_wgetcwd_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wget_current_dir_name) __ATTR_WUNUSED __ATTR_MALLOC __WCHAR_TYPE__ *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wget_current_dir_name))(void) {
#line 1131 "kos/src/libc/magic/unistd.c"
	return __localdep_wgetcwd(__NULLPTR, 0);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_wgetcwd) || defined(__CRT_HAVE__wgetcwd)) */
#endif /* !__local_wget_current_dir_name_defined */
