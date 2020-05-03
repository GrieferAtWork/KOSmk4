/* HASH CRC-32:0x2b8b7213 */
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
#ifndef __local_wcsrtombs_defined
#define __local_wcsrtombs_defined 1
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "wcrtomb" from "wchar" */
#ifndef ____localdep_wcrtomb_defined
#define ____localdep_wcrtomb_defined 1
#ifdef __CRT_HAVE_wcrtomb
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcrtomb,(char *__restrict __str, __WCHAR_TYPE__ __wc, __mbstate_t *__mbs),wcrtomb,(__str,__wc,__mbs))
#else /* LIBC: wcrtomb */
#include <local/wchar/wcrtomb.h>
#define __localdep_wcrtomb (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcrtomb))
#endif /* wcrtomb... */
#endif /* !____localdep_wcrtomb_defined */

/* Dependency: "mempcpy" from "string" */
#ifndef ____localdep_mempcpy_defined
#define ____localdep_mempcpy_defined 1
#ifdef __fast_mempcpy_defined
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
#define __localdep_mempcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))
#elif defined(__CRT_HAVE_mempcpy)
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* LIBC: mempcpy */
#include <local/string/mempcpy.h>
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
#define __localdep_mempcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpy))
#endif /* mempcpy... */
#endif /* !____localdep_mempcpy_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcsrtombs) __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsrtombs))(char *__dst,
                                                       __WCHAR_TYPE__ const **__restrict __psrc,
                                                       __SIZE_TYPE__ __dstlen,
                                                       __mbstate_t *__mbs) {
#line 332 "kos/src/libc/magic/wchar.c"
	__SIZE_TYPE__ __result = 0;
	__WCHAR_TYPE__ const *__src = *__psrc;
	while (__dstlen) {
		__SIZE_TYPE__ __error;
		char __buf[8];
		__error = __localdep_wcrtomb(__buf, *__src, __mbs);
		if (!__error)
			break;
		if (__error == (__SIZE_TYPE__)-1)
			return (__SIZE_TYPE__)-1; /* EILSEQ */
		if (__error > __dstlen)
			break;
		__dst = (char *)__localdep_mempcpy(__dst, __buf, __error);
		__result += __error;
		__dstlen -= __error;
		++__src;
	}
	*__psrc = __src;
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcsrtombs_defined */
