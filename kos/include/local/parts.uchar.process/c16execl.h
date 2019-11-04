/* HASH CRC-32:0xa81d83da */
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
#ifndef __local_c16execl_defined
#if (defined(__CRT_HAVE_wexecv) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE__wexecv) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_wexecv)
#define __local_c16execl_defined 1
#include <parts/redirect-exec.h>
/* Dependency: "c16execv" from "parts.uchar.process" */
#ifndef ____localdep_c16execv_defined
#define ____localdep_c16execv_defined 1
#if defined(__CRT_HAVE_wexecv) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_c16execv,(__CHAR16_TYPE__ const *__restrict __path, __T16ARGV),wexecv,(__path, ___argv))
#elif defined(__CRT_HAVE__wexecv) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_c16execv,(__CHAR16_TYPE__ const *__restrict __path, __T16ARGV),_wexecv,(__path, ___argv))
#elif defined(__CRT_HAVE_DOS$_wexecv)
__CREDIRECT_DOS(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_c16execv,(__CHAR16_TYPE__ const *__restrict __path, __T16ARGV),_wexecv,(__path, ___argv))
#elif defined(__CRT_HAVE_DOS$_wexecv)
__CREDIRECT_DOS(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_c16execv,(__CHAR16_TYPE__ const *__restrict __path, __T16ARGV),_wexecv,(__path, ___argv))
#else /* LIBC: c16execv */
#undef ____localdep_c16execv_defined
#endif /* c16execv... */
#endif /* !____localdep_c16execv_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16execl) __ATTR_SENTINEL __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(c16execl))(__CHAR16_TYPE__ const *__restrict __path,
                                                       __CHAR16_TYPE__ const *__args,
                                                       ... /*, (char16_t *)NULL*/) {
#line 97 "kos/src/libc/magic/parts.uchar.process.c"
	__REDIRECT_EXECL(__CHAR16_TYPE__, __localdep_c16execv, __path, __args)
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_wexecv) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE__wexecv) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_wexecv) */
#endif /* !__local_c16execl_defined */
