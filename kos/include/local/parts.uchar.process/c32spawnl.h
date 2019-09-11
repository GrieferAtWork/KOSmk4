/* HASH 0x12996375 */
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
#ifndef __local_c32spawnl_defined
#if ((defined(__CRT_HAVE_wspawnv) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE__wspawnv) && __SIZEOF_WCHAR_T__ == 4))
#define __local_c32spawnl_defined 1
#include <parts/redirect-exec.h>
/* Dependency: "c32spawnv" from "parts.uchar.process" */
#ifndef ____localdep_c32spawnv_defined
#define ____localdep_c32spawnv_defined 1
#if defined(__CRT_HAVE_wspawnv) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnv,(int __mode, __CHAR32_TYPE__ const *__restrict __path, __T32ARGV),wspawnv,(__mode,__path, ___argv))
#elif defined(__CRT_HAVE__wspawnv) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnv,(int __mode, __CHAR32_TYPE__ const *__restrict __path, __T32ARGV),_wspawnv,(__mode,__path, ___argv))
#else /* LIBC: c32spawnv */
#undef ____localdep_c32spawnv_defined
#endif /* c32spawnv... */
#endif /* !____localdep_c32spawnv_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32spawnl) __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(c32spawnl))(int __mode,
                                                        __CHAR32_TYPE__ const *__restrict __path,
                                                        __CHAR32_TYPE__ const *__args,
                                                        ... /*, (char32_t *)NULL*/) {
#line 208 "kos/src/libc/magic/parts.uchar.process.c"
	__REDIRECT_SPAWNL(__CHAR32_TYPE__, __localdep_c32spawnv, __mode, __path, __args)
}
__NAMESPACE_LOCAL_END
#endif /* ((defined(__CRT_HAVE_wspawnv) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE__wspawnv) && __SIZEOF_WCHAR_T__ == 4)) */
#endif /* !__local_c32spawnl_defined */
