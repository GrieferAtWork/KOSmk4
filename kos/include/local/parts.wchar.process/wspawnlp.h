/* HASH CRC-32:0xb9b633d1 */
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
#ifndef __local_wspawnlp_defined
#if defined(__CRT_HAVE_wspawnvp) || defined(__CRT_HAVE__wspawnvp)
#define __local_wspawnlp_defined 1
#include <parts/redirect-exec.h>
/* Dependency: "wspawnvp" */
#ifndef ____localdep_wspawnvp_defined
#define ____localdep_wspawnvp_defined 1
#if defined(__CRT_HAVE_wspawnvp)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_wspawnvp,(int __mode, __WCHAR_TYPE__ const *__restrict __file, __TWARGV),wspawnvp,(__mode,__file,____TWARGV))
#elif defined(__CRT_HAVE__wspawnvp)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_wspawnvp,(int __mode, __WCHAR_TYPE__ const *__restrict __file, __TWARGV),_wspawnvp,(__mode,__file,____TWARGV))
#else /* LIBC: wspawnvp */
#undef ____localdep_wspawnvp_defined
#endif /* wspawnvp... */
#endif /* !____localdep_wspawnvp_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wspawnlp) __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(wspawnlp))(int __mode,
                                                       __WCHAR_TYPE__ const *__restrict __file,
                                                       __WCHAR_TYPE__ const *__args,
                                                       ... /*, (wchar_t *)NULL*/) {
#line 126 "kos/src/libc/magic/parts.wchar.process.c"
	__REDIRECT_SPAWNLP(__WCHAR_TYPE__, __localdep_wspawnvp, __mode, __file, __args)
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_wspawnvp) || defined(__CRT_HAVE__wspawnvp) */
#endif /* !__local_wspawnlp_defined */
