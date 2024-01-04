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
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: DJGPP         (/include/stddef.h) */
/* (#) Portability: DragonFly BSD (/include/stddef.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/stddef.h) */
/* (#) Portability: FreeBSD       (/include/stddef.h) */
/* (#) Portability: MSVC          (/include/stddef.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/stddef.h) */
/* (#) Portability: NetBSD        (/include/stddef.h) */
/* (#) Portability: OpenBSD       (/include/stddef.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/stddef.h) */
/* (#) Portability: PDCLib        (/include/stddef.h) */
/* (#) Portability: Windows Kits  (/ucrt/stddef.h) */
/* (#) Portability: diet libc     (/include/stddef.h) */
/* (#) Portability: libcmini      (/include/stddef.h) */
/* (#) Portability: musl libc     (/include/stddef.h) */
#ifndef _STDDEF_H
#define _STDDEF_H 1

#ifdef _CXX_STDONLY_CSTDDEF
#ifdef __CXX_SYSTEM_HEADER
#undef _STDDEF_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "ctype.h" after "cctype" */
#ifndef __ptrdiff_t_defined
#define __ptrdiff_t_defined
__NAMESPACE_STD_USING(ptrdiff_t)
#endif /* !__ptrdiff_t_defined */
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __max_align_t_defined
#define __max_align_t_defined
__NAMESPACE_STD_USING(max_align_t)
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
#define __std_ptrdiff_t_defined
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif /* !__std_ptrdiff_t_defined */

#ifndef __std_size_t_defined
#define __std_size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__std_size_t_defined */

#ifndef __std_max_align_t_defined
#define __std_max_align_t_defined
typedef __MAX_ALIGN_TYPE__ max_align_t;
#endif /* !__std_max_align_t_defined */

#ifdef __cplusplus
#ifdef __USE_ISOCXX11
#ifndef __std_nullptr_t_defined
#define __std_nullptr_t_defined
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
#define __ptrdiff_t_defined
__NAMESPACE_STD_USING(ptrdiff_t)
#endif /* !__ptrdiff_t_defined */
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __max_align_t_defined
#define __max_align_t_defined
__NAMESPACE_STD_USING(max_align_t)
#endif /* !__max_align_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#endif /* __CC__ */

#ifndef offsetof
#define offsetof(s, m) __builtin_offsetof(s, m)
#endif /* !offsetof */

#ifdef __USE_KOS
/* Disable warnings about using `offsetof()' in c++ on structures that use
 * inheritance. The standards normally don't  allow this, but the KOS  abi
 * relies  on-, and requires that such uses  behave the same as though the
 * super-class appeared as  the first  member of the  sub-class, like  so:
 * >> struct a {
 * >>     int a_field;
 * >> };
 * >> struct b: a {
 * >>     int b_field;
 * >> };
 * >> struct c {
 * >>     struct a _super;
 * >>     int b_field;
 * >> };
 * In  this example, the  KOS ABI requires  that `struct b' and `struct c'
 * be binary-compatible. - The warning  we're suppressing here comes  into
 * play when someone  does `offsetof(struct b, a_field)'.  Here, GCC  will
 * warn  about the  fact that the  C standard doesn't  require the offsets
 * of members of base classes to be constant (and in the case of multiple-
 * inheritance, they actually aren't), however since the KOS ABI  requires
 * that in the case of  single-inheritance, offsets of a super-class  must
 * be equivalent to what can be  seen in `struct c', such warnings  become
 * meaningless.
 *
 * As such, we disable the relevant  warning if we're compiling code  for
 * KOS in c++-mode, the caller has _KOS_SOURCE enabled (thus stating that
 * they want to take advantage of KOS-specific behavior and  extensions),
 * and includes <stddef.h> (to get access to `offsetof(3)').
 */
#if defined(__KOS__) && defined(__cplusplus)
__pragma_GCC_diagnostic_ignored(Winvalid_offsetof)
#endif /* __KOS__ && __cplusplus */

#define offsetafter(s, m)               __COMPILER_OFFSETAFTER(s, m)
#define container_of(ptr, type, member) __COMPILER_CONTAINER_OF(ptr, type, member)
#define lengthof(arr)                   __COMPILER_LENOF(arr)

#define sizeof_field(s, m) sizeof(((s *)0)->m)
#ifdef __COMPILER_HAVE_TYPEOF
#define typeof_field(s, m) __typeof__(((s *)0)->m)
#endif /* __COMPILER_HAVE_TYPEOF */
#endif /* __USE_KOS */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

__SYSDECL_END

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CSTDDEF
#undef _STDDEF_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CSTDDEF */
#endif /* !_STDDEF_H */
