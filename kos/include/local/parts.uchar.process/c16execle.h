/* HASH CRC-32:0xacb23df0 */
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
#ifndef __local_c16execle_defined
#if (defined(__CRT_HAVE_wexecve) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE__wexecve) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_wexecve)
#define __local_c16execle_defined 1
#include <parts/redirect-exec.h>
/* Dependency: "c16execve" from "parts.uchar.process" */
#ifndef ____localdep_c16execve_defined
#define ____localdep_c16execve_defined 1
#if defined(__CRT_HAVE_wexecve) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c16execve,(__CHAR16_TYPE__ const *__restrict __path, __T16ARGV, __T16ENVP),wexecve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__wexecve) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c16execve,(__CHAR16_TYPE__ const *__restrict __path, __T16ARGV, __T16ENVP),_wexecve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$_wexecve)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c16execve,(__CHAR16_TYPE__ const *__restrict __path, __T16ARGV, __T16ENVP),_wexecve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$_wexecve)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c16execve,(__CHAR16_TYPE__ const *__restrict __path, __T16ARGV, __T16ENVP),_wexecve,(__path,___argv,___envp))
#else /* LIBC: c16execve */
#undef ____localdep_c16execve_defined
#endif /* c16execve... */
#endif /* !____localdep_c16execve_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16execle) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(c16execle))(__CHAR16_TYPE__ const *__restrict __path,
                                                        __CHAR16_TYPE__ const *__args,
                                                        ... /*, (char16_t *)NULL, char16_t **environ*/) {
#line 133 "kos/src/libc/magic/parts.uchar.process.c"
	__REDIRECT_EXECLE(__CHAR16_TYPE__, __localdep_c16execve, __path, __args)
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_HAVE_wexecve && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE__wexecve && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$_wexecve */
#endif /* !__local_c16execle_defined */
