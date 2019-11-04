/* HASH CRC-32:0xdda9f60 */
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
#ifndef __local_wspawnl_defined
#if defined(__CRT_HAVE_wspawnv) || defined(__CRT_HAVE__wspawnv)
#define __local_wspawnl_defined 1
#include <parts/redirect-exec.h>
/* Dependency: "wspawnv" */
#ifndef ____localdep_wspawnv_defined
#define ____localdep_wspawnv_defined 1
#ifdef __CRT_HAVE_wspawnv
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_wspawnv,(int __mode, __WCHAR_TYPE__ const *__restrict __path, __TWARGV),wspawnv,(__mode,__path,____TWARGV))
#elif defined(__CRT_HAVE__wspawnv)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_wspawnv,(int __mode, __WCHAR_TYPE__ const *__restrict __path, __TWARGV),_wspawnv,(__mode,__path,____TWARGV))
#else /* LIBC: wspawnv */
#undef ____localdep_wspawnv_defined
#endif /* wspawnv... */
#endif /* !____localdep_wspawnv_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wspawnl) __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(wspawnl))(int __mode,
                                                      __WCHAR_TYPE__ const *__restrict __path,
                                                      __WCHAR_TYPE__ const *__args,
                                                      ... /*, (wchar_t *)NULL*/) {
#line 116 "kos/src/libc/magic/parts.wchar.process.c"
	__REDIRECT_SPAWNL(__WCHAR_TYPE__, __localdep_wspawnv, __mode, __path, __args)
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_wspawnv) || defined(__CRT_HAVE__wspawnv) */
#endif /* !__local_wspawnl_defined */
