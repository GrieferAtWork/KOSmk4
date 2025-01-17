/* HASH CRC-32:0x13597e3e */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: DragonFly BSD (/include/printf.h) */
/* (#) Portability: FreeBSD       (/include/printf.h) */
/* (#) Portability: GNU C Library (/include/printf.h) */
/* (#) Portability: GNU Hurd      (/usr/include/printf.h) */
/* (#) Portability: libc6         (/include/printf.h) */
/* (#) Portability: mintlib       (/include/printf.h) */
/* (#) Portability: uClibc        (/include/printf.h) */
#ifndef _PRINTF_H
#define _PRINTF_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/typecore.h>
#include <bits/crt/printf_info.h>

#ifdef __USE_GLIBC_BLOAT
#include <stdarg.h>
#endif /* __USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef __std_FILE_defined
#define __std_FILE_defined
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __FILE_defined
#define __FILE_defined
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#endif /* !__CXX_SYSTEM_HEADER */

/* Function types (NOT POINTERS) from `<bits/crt/printf_info.h>' */
typedef __printf_function printf_function;
typedef __printf_arginfo_size_function printf_arginfo_size_function;
typedef __printf_arginfo_function printf_arginfo_function;
typedef __printf_va_arg_function printf_va_arg_function;

/* >> register_printf_specifier(3), register_printf_function(3)
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(,int,__NOTHROW_NCX,register_printf_specifier,(__STDC_INT_AS_UINT_T __spec, printf_function *__func, printf_arginfo_size_function *__arginfo),(__spec,__func,__arginfo))
/* >> register_printf_specifier(3), register_printf_function(3)
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(,int,__NOTHROW_NCX,register_printf_function,(__STDC_INT_AS_UINT_T __spec, printf_function *__func, printf_arginfo_function *__arginfo),(__spec,__func,__arginfo))
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,register_printf_modifier,(__WCHAR32_TYPE__ const *__str),(__str))
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,register_printf_type,(printf_va_arg_function *__fct),(__fct))
__CDECLARE_OPT(__ATTR_OUTS(3, 2) __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,parse_printf_format,(char const *__restrict __fmt, size_t __n, int *__restrict __argtypes),(__fmt,__n,__argtypes))



/************************************************************************/
/* BUILT-IN PRINTF FUNCTIONS (that aren't linked by default)            */
/************************************************************************/

__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,printf_size,(__FILE *__restrict __fp, struct printf_info const *__info, void const *const *__restrict __args),(__fp,__info,__args))
__CDECLARE_OPT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_NCX,printf_size_info,(struct printf_info const *__restrict __info, size_t __n, int *__restrict __argtypes),(__info,__n,__argtypes))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PRINTF_H */
