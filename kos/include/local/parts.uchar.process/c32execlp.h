/* HASH CRC-32:0x2a9d5a24 */
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
#ifndef __local_c32execlp_defined
#if (defined(__CRT_HAVE_wexecvp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE__wexecvp) && __SIZEOF_WCHAR_T__ == 4)
#define __local_c32execlp_defined 1
#include <parts/redirect-exec.h>
/* Dependency: "c32execvp" from "parts.uchar.process" */
#ifndef ____localdep_c32execvp_defined
#define ____localdep_c32execvp_defined 1
#if defined(__CRT_HAVE_wexecvp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_c32execvp,(__CHAR32_TYPE__ const *__restrict __path, __T32ARGV),wexecvp,(__path, ___argv))
#elif defined(__CRT_HAVE__wexecvp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_c32execvp,(__CHAR32_TYPE__ const *__restrict __path, __T32ARGV),_wexecvp,(__path, ___argv))
#else /* LIBC: c32execvp */
#undef ____localdep_c32execvp_defined
#endif /* c32execvp... */
#endif /* !____localdep_c32execvp_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32execlp) __ATTR_SENTINEL __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(c32execlp))(__CHAR32_TYPE__ const *__restrict __file,
                                                        __CHAR32_TYPE__ const *__args,
                                                        ... /*, (char32_t *)NULL*/) {
#line 121 "kos/src/libc/magic/parts.uchar.process.c"
	__REDIRECT_EXECL(__CHAR32_TYPE__, __localdep_c32execvp, __file, __args)
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_wexecvp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE__wexecvp) && __SIZEOF_WCHAR_T__ == 4) */
#endif /* !__local_c32execlp_defined */
