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
#ifndef _STDARG_H
#define _STDARG_H 1

#include "__stdinc.h"
#if defined(_CXX_CSTDARG) && !defined(__CXX_SYSTEM_HEADER)
/* Import all symbols into the global namespace when re-including "stdarg.h" after "cstdarg" */
#ifndef __va_list_defined
#define __va_list_defined 1
__NAMESPACE_STD_USING(va_list)
#endif /* !__va_list_defined */
#else /* _CXX_CSTDARG && !__CXX_SYSTEM_HEADER */
#include <features.h>

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __std_va_list_defined
#define __std_va_list_defined 1
__NAMESPACE_STD_BEGIN
typedef __builtin_va_list va_list;
__NAMESPACE_STD_END
#endif /* !__std_va_list_defined */
#ifndef __CXX_SYSTEM_HEADER
#ifndef __va_list_defined
#define __va_list_defined 1
__NAMESPACE_STD_USING(va_list)
#endif /* !__va_list_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#define va_start  __builtin_va_start
#define __va_copy __builtin_va_copy
#define va_end    __builtin_va_end
#define va_arg    __builtin_va_arg

#if defined(__USE_ISOC99) || \
   (defined(__STDC_VERSION__) && (__STDC_VERSION__+0 >= 199900L)) || \
   (defined(__cplusplus) && (__cplusplus+0 >= 201103L))
#define va_copy   __builtin_va_copy
#endif
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_CXX_CSTDARG || __CXX_SYSTEM_HEADER */
#endif /* !_STDARG_H */
