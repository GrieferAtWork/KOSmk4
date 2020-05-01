/* HASH CRC-32:0x91102e5b */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wexeclpe_defined
#if defined(__CRT_HAVE_wexecvpe) || defined(__CRT_HAVE__wexecvpe)
#define __local_wexeclpe_defined 1
#include <__crt.h>
#include <parts/redirect-exec.h>
/* Dependency: "wexecvpe" */
#ifndef ____localdep_wexecvpe_defined
#define ____localdep_wexecvpe_defined 1
#ifdef __CRT_HAVE_wexecvpe
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_wexecvpe,(__WCHAR_TYPE__ const *__restrict __file, __TWARGV, __TWENVP),wexecvpe,(__file,____TWARGV,____TWENVP))
#elif defined(__CRT_HAVE__wexecvpe)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_wexecvpe,(__WCHAR_TYPE__ const *__restrict __file, __TWARGV, __TWENVP),_wexecvpe,(__file,____TWARGV,____TWENVP))
#else /* LIBC: wexecvpe */
#undef ____localdep_wexecvpe_defined
#endif /* wexecvpe... */
#endif /* !____localdep_wexecvpe_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wexeclpe) __ATTR_NONNULL((1)) __ATTR_SENTINEL_O(1) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(wexeclpe))(__WCHAR_TYPE__ const *__restrict __file,
                                                       __WCHAR_TYPE__ const *__args,
                                                       ... /*, (wchar_t *)NULL, wchar_t **environ*/) {
#line 100 "kos/src/libc/magic/parts.wchar.process.c"
	__REDIRECT_EXECLE(__WCHAR_TYPE__, __localdep_wexecvpe, __file, __args)
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_wexecvpe || __CRT_HAVE__wexecvpe */
#endif /* !__local_wexeclpe_defined */
