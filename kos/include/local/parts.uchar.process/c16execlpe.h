/* HASH CRC-32:0xc254a0ad */
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
#ifndef __local_c16execlpe_defined
#if (defined(__CRT_HAVE_wexecvpe) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE__wexecvpe) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_wexecvpe)
#define __local_c16execlpe_defined 1
#include <parts/redirect-exec.h>
/* Dependency: "c16execvpe" from "parts.uchar.process" */
#ifndef ____localdep_c16execvpe_defined
#define ____localdep_c16execvpe_defined 1
#if defined(__CRT_HAVE_wexecvpe) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c16execvpe,(__CHAR16_TYPE__ const *__restrict __path, __T16ARGV, __T16ENVP),wexecvpe,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__wexecvpe) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c16execvpe,(__CHAR16_TYPE__ const *__restrict __path, __T16ARGV, __T16ENVP),_wexecvpe,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$_wexecvpe)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c16execvpe,(__CHAR16_TYPE__ const *__restrict __path, __T16ARGV, __T16ENVP),_wexecvpe,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$_wexecvpe)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c16execvpe,(__CHAR16_TYPE__ const *__restrict __path, __T16ARGV, __T16ENVP),_wexecvpe,(__path,___argv,___envp))
#else /* LIBC: c16execvpe */
#undef ____localdep_c16execvpe_defined
#endif /* c16execvpe... */
#endif /* !____localdep_c16execvpe_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16execlpe) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(c16execlpe))(__CHAR16_TYPE__ const *__restrict __file,
                                                         __CHAR16_TYPE__ const *__args,
                                                         ... /*, (char16_t *)NULL, char16_t **environ*/) {
#line 148 "kos/src/libc/magic/parts.uchar.process.c"
	__REDIRECT_EXECLE(__CHAR16_TYPE__, __localdep_c16execvpe, __file, __args)
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_HAVE_wexecvpe && __SIZEOF_WCHAR_T__ == 2) || (__CRT_HAVE__wexecvpe && __SIZEOF_WCHAR_T__ == 2) || __CRT_HAVE_DOS$_wexecvpe */
#endif /* !__local_c16execlpe_defined */
