/* HASH CRC-32:0xa139d1b9 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _MONETARY_H
#define _MONETARY_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined 1
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifdef __CRT_HAVE_strfmon
__LIBC __ATTR_NONNULL((1, 3)) __ATTR_LIBC_STRFMON(3, 4) ssize_t __NOTHROW_NCX(__VLIBCCALL strfmon)(char *__restrict __s, size_t __maxsize, char const *__restrict __format, ...) __CASMNAME_SAME("strfmon");
#endif /* strfmon... */
#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_strfmon_l
__LIBC __ATTR_NONNULL((1, 4)) __ATTR_LIBC_STRFMON(4, 5) ssize_t __NOTHROW_NCX(__VLIBCCALL strfmon_l)(char *__restrict __s, size_t __maxsize, __locale_t __loc, const char *__restrict __format, ...) __CASMNAME_SAME("strfmon_l");
#elif defined(__CRT_HAVE___strfmon_l) && !defined(__NO_ASMNAME)
__LIBC __ATTR_NONNULL((1, 4)) __ATTR_LIBC_STRFMON(4, 5) ssize_t __NOTHROW_NCX(__VLIBCCALL strfmon_l)(char *__restrict __s, size_t __maxsize, __locale_t __loc, const char *__restrict __format, ...) __CASMNAME("__strfmon_l");
#endif /* strfmon_l... */
#endif /* __USE_XOPEN2K8 */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_MONETARY_H */
