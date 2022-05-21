/* HASH CRC-32:0x4e2b9ef0 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strtoimax_l_defined
#define __local_strtoimax_l_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strtoimax_defined
#define __local___localdep_strtoimax_defined
#ifdef __CRT_HAVE_strtoimax
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto32) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto32,(__nptr,__endptr,__base))
#elif __SIZEOF_INTMAX_T__ == 8
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strto64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoimax __NAMESPACE_LOCAL_TYPEHAX(__INTMAX_TYPE__(__LIBCCALL*)(char const *__restrict,char **,__STDC_INT_AS_UINT_T),__INTMAX_TYPE__(__LIBCCALL&)(char const *__restrict,char **,__STDC_INT_AS_UINT_T),strto64)
#elif __SIZEOF_INTMAX_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strto32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoimax __NAMESPACE_LOCAL_TYPEHAX(__INTMAX_TYPE__(__LIBCCALL*)(char const *__restrict,char **,__STDC_INT_AS_UINT_T),__INTMAX_TYPE__(__LIBCCALL&)(char const *__restrict,char **,__STDC_INT_AS_UINT_T),strto32)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/inttypes/strtoimax.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoimax __LIBC_LOCAL_NAME(strtoimax)
#endif /* !... */
#endif /* !__local___localdep_strtoimax_defined */
__LOCAL_LIBC(strtoimax_l) __ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __INTMAX_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtoimax_l))(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_strtoimax)(__nptr, __endptr, __base);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtoimax_l_defined
#define __local___localdep_strtoimax_l_defined
#define __localdep_strtoimax_l __LIBC_LOCAL_NAME(strtoimax_l)
#endif /* !__local___localdep_strtoimax_l_defined */
#endif /* !__local_strtoimax_l_defined */
