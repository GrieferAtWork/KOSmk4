/* HASH CRC-32:0xd570c5a */
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
#ifndef __local_wexecl_defined
#if defined(__CRT_HAVE_wexecv) || defined(__CRT_HAVE__wexecv)
#define __local_wexecl_defined 1
#include <parts/redirect-exec.h>
/* Dependency: "wexecv" */
#ifndef ____localdep_wexecv_defined
#define ____localdep_wexecv_defined 1
#ifdef __CRT_HAVE_wexecv
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_wexecv,(__WCHAR_TYPE__ const *__restrict __path, __TWARGV),wexecv,(__path,____TWARGV))
#elif defined(__CRT_HAVE__wexecv)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_wexecv,(__WCHAR_TYPE__ const *__restrict __path, __TWARGV),_wexecv,(__path,____TWARGV))
#else /* LIBC: wexecv */
#undef ____localdep_wexecv_defined
#endif /* wexecv... */
#endif /* !____localdep_wexecv_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wexecl) __ATTR_SENTINEL __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(wexecl))(__WCHAR_TYPE__ const *__restrict __path,
                                                     __WCHAR_TYPE__ const *__args,
                                                     ... /*, (wchar_t *)NULL*/) {
#line 85 "kos/src/libc/magic/parts.wchar.process.c"
	__REDIRECT_EXECL(__WCHAR_TYPE__, __localdep_wexecv, __path, __args)
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_wexecv || __CRT_HAVE__wexecv */
#endif /* !__local_wexecl_defined */
