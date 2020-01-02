/* HASH CRC-32:0xbf9944f5 */
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
#ifndef __local_c32get_current_dir_name_defined
#if defined(__CRT_HAVE_wgetcwd) || defined(__CRT_HAVE__wgetcwd)
#define __local_c32get_current_dir_name_defined 1
/* Dependency: "wgetcwd" from "parts.wchar.unistd" */
#ifndef ____localdep_c32getcwd_defined
#define ____localdep_c32getcwd_defined 1
#if defined(__CRT_HAVE_wgetcwd) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `c32chdir(2)' */
__CREDIRECT(,__CHAR32_TYPE__ *,__NOTHROW_RPC,__localdep_c32getcwd,(__CHAR32_TYPE__ *__buf, __SIZE_TYPE__ __bufsize),wgetcwd,(__buf,__bufsize))
#else /* LIBC: wgetcwd */
#undef ____localdep_c32getcwd_defined
#endif /* c32getcwd... */
#endif /* !____localdep_c32getcwd_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32get_current_dir_name) __ATTR_MALLOC __ATTR_WUNUSED __CHAR32_TYPE__ *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(c32get_current_dir_name))(void) {
#line 1131 "kos/src/libc/magic/unistd.c"
	return __localdep_c32getcwd(__NULLPTR, 0);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_wgetcwd || __CRT_HAVE__wgetcwd */
#endif /* !__local_c32get_current_dir_name_defined */
