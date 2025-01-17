/* HASH CRC-32:0xd9a72bb0 */
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
#ifndef __local_atoi_defined
#define __local_atoi_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strto32_defined
#define __local___localdep_strto32_defined
#ifdef __CRT_HAVE_strto32
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,__localdep_strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && __SIZEOF_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,__localdep_strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && __SIZEOF_LONG_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,__localdep_strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && __SIZEOF_LONG_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,__localdep_strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtoq) && __SIZEOF_LONG_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,__localdep_strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && __SIZEOF_INTMAX_T__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,__localdep_strto32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strto32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strto32 __LIBC_LOCAL_NAME(strto32)
#endif /* !... */
#endif /* !__local___localdep_strto32_defined */
#ifndef __local___localdep_strto64_defined
#define __local___localdep_strto64_defined
#ifdef __CRT_HAVE_strto64
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && __SIZEOF_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && __SIZEOF_LONG_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && __SIZEOF_LONG_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtoq) && __SIZEOF_LONG_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && __SIZEOF_INTMAX_T__ == 8
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strto64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strto64 __LIBC_LOCAL_NAME(strto64)
#endif /* !... */
#endif /* !__local___localdep_strto64_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(atoi) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(atoi))(char const *__restrict __nptr) {
#if __SIZEOF_INT__ <= 4
	return (int)(__NAMESPACE_LOCAL_SYM __localdep_strto32)(__nptr, __NULLPTR, 10);
#else /* __SIZEOF_INT__ <= 4 */
	return (int)(__NAMESPACE_LOCAL_SYM __localdep_strto64)(__nptr, __NULLPTR, 10);
#endif /* __SIZEOF_INT__ > 4 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_atoi_defined
#define __local___localdep_atoi_defined
#define __localdep_atoi __LIBC_LOCAL_NAME(atoi)
#endif /* !__local___localdep_atoi_defined */
#endif /* !__local_atoi_defined */
