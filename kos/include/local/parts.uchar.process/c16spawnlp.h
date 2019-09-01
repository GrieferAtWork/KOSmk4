/* HASH 0x2d566d63 */
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
#ifndef __local_c16spawnlp_defined
#if ((defined(__CRT_HAVE_wspawnvp) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE__wspawnvp) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_wspawnvp) || defined(__CRT_HAVE_DOS$_wspawnvp))
#define __local_c16spawnlp_defined 1
#include <parts/redirect-exec.h>
/* Dependency: "c16spawnvp" from "parts.uchar.process" */
#ifndef ____localdep_c16spawnvp_defined
#define ____localdep_c16spawnvp_defined 1
#if defined(__CRT_HAVE_wspawnvp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_c16spawnvp,(int __mode, __CHAR16_TYPE__ const *__restrict __path, __T16ARGV),wspawnvp,(__mode,__path, ___argv))
#elif defined(__CRT_HAVE__wspawnvp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_c16spawnvp,(int __mode, __CHAR16_TYPE__ const *__restrict __path, __T16ARGV),_wspawnvp,(__mode,__path, ___argv))
#elif defined(__CRT_HAVE_DOS$_wspawnvp)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_c16spawnvp,(int __mode, __CHAR16_TYPE__ const *__restrict __path, __T16ARGV),_wspawnvp,(__mode,__path, ___argv))
#elif defined(__CRT_HAVE_DOS$_wspawnvp)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_c16spawnvp,(int __mode, __CHAR16_TYPE__ const *__restrict __path, __T16ARGV),_wspawnvp,(__mode,__path, ___argv))
#else /* LIBC: c16spawnvp */
#undef ____localdep_c16spawnvp_defined
#endif /* c16spawnvp... */
#endif /* !____localdep_c16spawnvp_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16spawnlp) __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(c16spawnlp))(int __mode,
                                                         __CHAR16_TYPE__ const *__restrict __file,
                                                         __CHAR16_TYPE__ const *__args,
                                                         ... /*, (char16_t *)NULL*/) {
#line 213 "kos/src/libc/magic/parts.uchar.process.c"
	__REDIRECT_SPAWNL(__CHAR16_TYPE__, __localdep_c16spawnvp, __mode, __file, __args)
}
__NAMESPACE_LOCAL_END
#endif /* ((defined(__CRT_HAVE_wspawnvp) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE__wspawnvp) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_wspawnvp) || defined(__CRT_HAVE_DOS$_wspawnvp)) */
#endif /* !__local_c16spawnlp_defined */
