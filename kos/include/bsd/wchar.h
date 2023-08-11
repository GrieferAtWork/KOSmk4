/* HASH CRC-32:0xe4f264c1 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: libbsd (/include/bsd/wchar.h) */
#ifndef _BSD_WCHAR_H
#define _BSD_WCHAR_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <wchar.h>

#ifdef __CC__
__SYSDECL_BEGIN

#if !defined(__fgetwln_defined) && defined(__CRT_HAVE_fgetwln)
#define __fgetwln_defined
/* >> fgetwln(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2),wchar_t *,__NOTHROW_NCX,fgetwln,(FILE *__restrict __stream, __SIZE_TYPE__ *__restrict __lenp),(__stream,__lenp))
#endif /* !__fgetwln_defined && __CRT_HAVE_fgetwln */
#ifndef __wcslcat_defined
#define __wcslcat_defined
#ifdef __CRT_HAVE_wcslcat
/* >> wcslcat(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcslcat,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __bufsize),(__dst,__src,__bufsize))
#else /* __CRT_HAVE_wcslcat */
#include <libc/local/wchar/wcslcat.h>
/* >> wcslcat(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslcat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcslcat)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslcat))(__dst, __src, __bufsize); })
#endif /* !__CRT_HAVE_wcslcat */
#endif /* !__wcslcat_defined */
#ifndef __wcslcpy_defined
#define __wcslcpy_defined
#ifdef __CRT_HAVE_wcslcpy
/* >> wcslcpy(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcslcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __bufsize),(__dst,__src,__bufsize))
#else /* __CRT_HAVE_wcslcpy */
#include <libc/local/wchar/wcslcpy.h>
/* >> wcslcpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcslcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslcpy))(__dst, __src, __bufsize); })
#endif /* !__CRT_HAVE_wcslcpy */
#endif /* !__wcslcpy_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BSD_WCHAR_H */
