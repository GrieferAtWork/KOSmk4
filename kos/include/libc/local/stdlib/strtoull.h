/* HASH CRC-32:0x8e77eec1 */
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
#ifndef __local_strtoull_defined
#define __local_strtoull_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strtou32_defined
#define __local___localdep_strtou32_defined
#ifdef __CRT_HAVE_strtou32
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && __SIZEOF_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && __SIZEOF_LONG_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && __SIZEOF_LONG_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtouq) && __SIZEOF_LONG_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_INTMAX_T__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtou32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtou32 __LIBC_LOCAL_NAME(strtou32)
#endif /* !... */
#endif /* !__local___localdep_strtou32_defined */
#ifndef __local___localdep_strtou64_defined
#define __local___localdep_strtou64_defined
#ifdef __CRT_HAVE_strtou64
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && __SIZEOF_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && __SIZEOF_LONG_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && __SIZEOF_LONG_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtouq) && __SIZEOF_LONG_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_INTMAX_T__ == 8
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtou64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtou64 __LIBC_LOCAL_NAME(strtou64)
#endif /* !... */
#endif /* !__local___localdep_strtou64_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strtoull) __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtoull))(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __localdep_strtou32)(__nptr, __endptr, __base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __localdep_strtou64)(__nptr, __endptr, __base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtoull_defined
#define __local___localdep_strtoull_defined
#define __localdep_strtoull __LIBC_LOCAL_NAME(strtoull)
#endif /* !__local___localdep_strtoull_defined */
#endif /* !__local_strtoull_defined */
