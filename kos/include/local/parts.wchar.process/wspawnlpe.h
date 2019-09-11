/* HASH 0x7de1356b */
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
#ifndef __local_wspawnlpe_defined
#if (defined(__CRT_HAVE_wspawnvpe) || defined(__CRT_HAVE__wspawnvpe))
#define __local_wspawnlpe_defined 1
#include <parts/redirect-exec.h>
/* Dependency: "wspawnvpe" */
#ifndef ____localdep_wspawnvpe_defined
#define ____localdep_wspawnvpe_defined 1
#if defined(__CRT_HAVE_wspawnvpe)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_wspawnvpe,(int __mode, __WCHAR_TYPE__ const *__restrict __file, __TWARGV, __TWENVP),wspawnvpe,(__mode,__file,____TWARGV,____TWENVP))
#elif defined(__CRT_HAVE__wspawnvpe)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_wspawnvpe,(int __mode, __WCHAR_TYPE__ const *__restrict __file, __TWARGV, __TWENVP),_wspawnvpe,(__mode,__file,____TWARGV,____TWENVP))
#else /* LIBC: wspawnvpe */
#undef ____localdep_wspawnvpe_defined
#endif /* wspawnvpe... */
#endif /* !____localdep_wspawnvpe_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wspawnlpe) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(wspawnlpe))(int __mode,
                                                        __WCHAR_TYPE__ const *__restrict __file,
                                                        __WCHAR_TYPE__ const *__args,
                                                        ... /*, (wchar_t *)NULL, wchar_t **environ*/) {
#line 131 "kos/src/libc/magic/parts.wchar.process.c"
	__REDIRECT_SPAWNLPE(__WCHAR_TYPE__, __localdep_wspawnvpe, __mode, __file, __args)
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_wspawnvpe) || defined(__CRT_HAVE__wspawnvpe)) */
#endif /* !__local_wspawnlpe_defined */
