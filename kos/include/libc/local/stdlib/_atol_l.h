/* HASH CRC-32:0x45f44dbe */
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
#ifndef __local__atol_l_defined
#define __local__atol_l_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strtol_l from stdlib */
#ifndef __local___localdep_strtol_l_defined
#define __local___localdep_strtol_l_defined 1
#ifdef __CRT_HAVE_strtol_l
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtol_l)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto32_l) && __SIZEOF_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto32_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto64_l) && __SIZEOF_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoimax_l) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoimax_l) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,__localdep_strtol_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strto32_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtol_l (*(long(__LIBCCALL *)(char const *__restrict, char **, __STDC_INT_AS_UINT_T, __locale_t))&__LIBC_LOCAL_NAME(strto32_l))
#elif __SIZEOF_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strto64_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtol_l (*(long(__LIBCCALL *)(char const *__restrict, char **, __STDC_INT_AS_UINT_T, __locale_t))&__LIBC_LOCAL_NAME(strto64_l))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtol_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtol_l __LIBC_LOCAL_NAME(strtol_l)
#endif /* !... */
#endif /* !__local___localdep_strtol_l_defined */
__LOCAL_LIBC(_atol_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_atol_l))(char const *__restrict __nptr, __locale_t __locale) {
	return __localdep_strtol_l(__nptr, __NULLPTR, 10, __locale);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__atol_l_defined
#define __local___localdep__atol_l_defined 1
#define __localdep__atol_l __LIBC_LOCAL_NAME(_atol_l)
#endif /* !__local___localdep__atol_l_defined */
#endif /* !__local__atol_l_defined */
