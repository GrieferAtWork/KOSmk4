/* HASH CRC-32:0xb16559c8 */
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
#ifndef __local_wexecle_defined
#if defined(__CRT_HAVE_wexecve) || defined(__CRT_HAVE__wexecve)
#define __local_wexecle_defined 1
#include <parts/redirect-exec.h>
/* Dependency: "wexecve" */
#ifndef ____localdep_wexecve_defined
#define ____localdep_wexecve_defined 1
#if defined(__CRT_HAVE_wexecve)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_wexecve,(__WCHAR_TYPE__ const *__restrict __path, __TWARGV, __TWENVP),wexecve,(__path,____TWARGV,____TWENVP))
#elif defined(__CRT_HAVE__wexecve)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_wexecve,(__WCHAR_TYPE__ const *__restrict __path, __TWARGV, __TWENVP),_wexecve,(__path,____TWARGV,____TWENVP))
#else /* LIBC: wexecve */
#undef ____localdep_wexecve_defined
#endif /* wexecve... */
#endif /* !____localdep_wexecve_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wexecle) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(wexecle))(__WCHAR_TYPE__ const *__restrict __path,
                                                      __WCHAR_TYPE__ const *__args,
                                                      ... /*, (wchar_t *)NULL, wchar_t **environ*/) {
#line 89 "kos/src/libc/magic/parts.wchar.process.c"
	__REDIRECT_EXECLE(__WCHAR_TYPE__, __localdep_wexecve, __path, __args)
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_wexecve) || defined(__CRT_HAVE__wexecve) */
#endif /* !__local_wexecle_defined */
