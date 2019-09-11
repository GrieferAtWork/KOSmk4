/* HASH 0xeecfb523 */
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
#ifndef __local_c32spawnle_defined
#if ((defined(__CRT_HAVE_wspawnve) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE__wspawnve) && __SIZEOF_WCHAR_T__ == 4))
#define __local_c32spawnle_defined 1
#include <parts/redirect-exec.h>
/* Dependency: "c32spawnve" from "parts.uchar.process" */
#ifndef ____localdep_c32spawnve_defined
#define ____localdep_c32spawnve_defined 1
#if defined(__CRT_HAVE_wspawnve) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)) __ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnve,(int __mode, __CHAR32_TYPE__ const *__restrict __path, __T32ARGV, __T32ENVP),wspawnve,(__mode,__path, ___argv, ___envp))
#elif defined(__CRT_HAVE__wspawnve) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)) __ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnve,(int __mode, __CHAR32_TYPE__ const *__restrict __path, __T32ARGV, __T32ENVP),_wspawnve,(__mode,__path, ___argv, ___envp))
#else /* LIBC: c32spawnve */
#undef ____localdep_c32spawnve_defined
#endif /* c32spawnve... */
#endif /* !____localdep_c32spawnve_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32spawnle) __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(c32spawnle))(int __mode,
                                                         __CHAR32_TYPE__ const *__restrict __path,
                                                         __CHAR32_TYPE__ const *__args,
                                                         ... /*, (char32_t *)NULL, char32_t **environ*/) {
#line 243 "kos/src/libc/magic/parts.uchar.process.c"
	__REDIRECT_SPAWNLE(__CHAR32_TYPE__, __localdep_c32spawnve, __mode, __path, __args)
}
__NAMESPACE_LOCAL_END
#endif /* ((defined(__CRT_HAVE_wspawnve) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE__wspawnve) && __SIZEOF_WCHAR_T__ == 4)) */
#endif /* !__local_c32spawnle_defined */
