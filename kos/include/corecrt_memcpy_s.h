/* HASH CRC-32:0x95d6b905 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Windows Kits (/ucrt/corecrt_memcpy_s.h) */
#ifndef _CORECRT_MEMCPY_S_H
#define _CORECRT_MEMCPY_S_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <corecrt.h>
#include <errno.h>
#include <vcruntime_string.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */

#ifndef __memcpy_s_defined
#define __memcpy_s_defined
#ifdef __CRT_HAVE_memcpy_s
__CDECLARE(__ATTR_INS(3, 4) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_NCX,memcpy_s,(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength),(__dst,__dstlength,__src,__srclength))
#else /* __CRT_HAVE_memcpy_s */
#include <libc/local/string/memcpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpy_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) __errno_t __NOTHROW_NCX(__LIBCCALL memcpy_s)(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy_s))(__dst, __dstlength, __src, __srclength); })
#endif /* !__CRT_HAVE_memcpy_s */
#endif /* !__memcpy_s_defined */
#ifndef __memmove_s_defined
#define __memmove_s_defined
#ifdef __CRT_HAVE_memmove_s
__CDECLARE(__ATTR_INS(3, 4) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_NCX,memmove_s,(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength),(__dst,__dstlength,__src,__srclength))
#else /* __CRT_HAVE_memmove_s */
#include <libc/local/string/memmove_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memmove_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) __errno_t __NOTHROW_NCX(__LIBCCALL memmove_s)(void *__dst, rsize_t __dstlength, void const *__src, rsize_t __srclength) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmove_s))(__dst, __dstlength, __src, __srclength); })
#endif /* !__CRT_HAVE_memmove_s */
#endif /* !__memmove_s_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_CORECRT_MEMCPY_S_H */
