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
#ifndef _STDDEF_H
#define _STDDEF_H 1

#ifdef _CXX_STDONLY_CSTDDEF
#ifdef __CXX_SYSTEM_HEADER
#undef _STDDEF_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "ctype.h" after "cctype" */
#ifndef __ptrdiff_t_defined
#define __ptrdiff_t_defined 1
__NAMESPACE_STD_USING_TYPE(ptrdiff_t)
#endif /* !__ptrdiff_t_defined */
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING_TYPE(size_t)
#endif /* !__size_t_defined */
#ifndef __max_align_t_defined
#define __max_align_t_defined 1
__NAMESPACE_STD_USING_TYPE(max_align_t)
#endif /* !__max_align_t_defined */
#undef _CXX_STDONLY_CSTDDEF
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CSTDDEF */

#include "__stdinc.h"
#include <features.h>
#include <hybrid/typecore.h>
#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

__SYSDECL_BEGIN

#ifndef __MAX_ALIGN_TYPE__
#define __MAX_ALIGN_TYPE__ __LONGDOUBLE
#endif /* !__MAX_ALIGN_TYPE__ */

#ifdef __CC__
__NAMESPACE_STD_BEGIN

#ifndef __std_ptrdiff_t_defined
#define __std_ptrdiff_t_defined 1
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif /* !__std_ptrdiff_t_defined */

#ifndef __std_size_t_defined
#define __std_size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__std_size_t_defined */

#ifndef __std_max_align_t_defined
#define __std_max_align_t_defined 1
typedef __MAX_ALIGN_TYPE__ max_align_t;
#endif /* !__std_max_align_t_defined */

#ifdef __cplusplus
#ifdef __USE_ISOCXX11
#ifndef __std_nullptr_t_defined
#define __std_nullptr_t_defined 1
#if defined(__COMPILER_HAVE_CXX_DECLTYPE) && defined(__COMPILER_HAVE_CXX_NULLPTR)
typedef decltype(nullptr) nullptr_t;
#else /* __COMPILER_HAVE_CXX_DECLTYPE && __COMPILER_HAVE_CXX_NULLPTR */
typedef void *nullptr_t; /* Ugly fallback... */
#endif /* !__COMPILER_HAVE_CXX_DECLTYPE || !__COMPILER_HAVE_CXX_NULLPTR */
#endif /* !__std_nullptr_t_defined */
#endif /* __USE_ISOCXX11 */
#endif /* __cplusplus */

__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#ifndef __ptrdiff_t_defined
#define __ptrdiff_t_defined 1
__NAMESPACE_STD_USING_TYPE(ptrdiff_t)
#endif /* !__ptrdiff_t_defined */
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING_TYPE(size_t)
#endif /* !__size_t_defined */
#ifndef __max_align_t_defined
#define __max_align_t_defined 1
__NAMESPACE_STD_USING_TYPE(max_align_t)
#endif /* !__max_align_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __wchar_t_defined
#define __wchar_t_defined 1
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#endif /* __CC__ */

#ifndef offsetof
#define offsetof(s, m) __builtin_offsetof(s, m)
#endif /* !offsetof */

#ifdef __USE_KOS
#define offsetafter(s, m)               __COMPILER_OFFSETAFTER(s, m)
#define container_of(ptr, type, member) __COMPILER_CONTAINER_OF(ptr, type, member)
#endif /* __USE_KOS */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

__SYSDECL_END

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CSTDDEF 1
#undef _STDDEF_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CSTDDEF */
#endif /* !_STDDEF_H */
