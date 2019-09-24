/* HASH CRC-32:0x376c0a3c */
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
#ifndef __local_c16mempcpy_defined
#define __local_c16mempcpy_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "mempcpyw" from "string" */
#ifndef ____localdep_mempcpyw_defined
#define ____localdep_mempcpyw_defined 1
#if defined(__fast_mempcpyw_defined)
/* Same as `memcpyw', but return `DST+N_WORDS', rather than `DST' */
#define __localdep_mempcpyw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyw))
#elif defined(__CRT_HAVE_mempcpyw)
/* Same as `memcpyw', but return `DST+N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),mempcpyw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `memcpyw', but return `DST+N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmempcpy,(__dst,__src,__n_words))
#else /* LIBC: mempcpyw */
#include <local/string/mempcpyw.h>
/* Same as `memcpyw', but return `DST+N_WORDS', rather than `DST' */
#define __localdep_mempcpyw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyw))
#endif /* mempcpyw... */
#endif /* !____localdep_mempcpyw_defined */

/* Dependency: "mempcpyl" from "string" */
#ifndef ____localdep_mempcpyl_defined
#define ____localdep_mempcpyl_defined 1
#if defined(__fast_mempcpyl_defined)
/* Same as `memcpyl', but return `DST+N_DWORDS', rather than `DST' */
#define __localdep_mempcpyl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyl))
#elif defined(__CRT_HAVE_mempcpyl)
/* Same as `memcpyl', but return `DST+N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),mempcpyl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `memcpyl', but return `DST+N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmempcpy,(__dst,__src,__n_dwords))
#else /* LIBC: mempcpyl */
#include <local/string/mempcpyl.h>
/* Same as `memcpyl', but return `DST+N_DWORDS', rather than `DST' */
#define __localdep_mempcpyl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyl))
#endif /* mempcpyl... */
#endif /* !____localdep_mempcpyl_defined */

/* Dependency: "mempcpy" from "string" */
#ifndef ____localdep_mempcpy_defined
#define ____localdep_mempcpy_defined 1
#if defined(__fast_mempcpy_defined)
/* Same as `memcpy', but return `DST+N_BYTES', rather than `DST' */
#define __localdep_mempcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))
#elif defined(__CRT_HAVE_mempcpy)
/* Same as `memcpy', but return `DST+N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#else /* LIBC: mempcpy */
#include <local/string/mempcpy.h>
/* Same as `memcpy', but return `DST+N_BYTES', rather than `DST' */
#define __localdep_mempcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpy))
#endif /* mempcpy... */
#endif /* !____localdep_mempcpy_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16mempcpy) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c16mempcpy))(__CHAR16_TYPE__ *__restrict __dst,
                                                        __CHAR16_TYPE__ const *__restrict __src,
                                                        __SIZE_TYPE__ __num_chars) {
#line 811 "kos/src/libc/magic/wchar.c"
#if 2 == 2
	return (__CHAR16_TYPE__ *)__localdep_mempcpyw(__dst, __src, __num_chars);
#elif 2 == 4
	return (__CHAR16_TYPE__ *)__localdep_mempcpyl(__dst, __src, __num_chars);
#else
	return (__CHAR16_TYPE__ *)__localdep_mempcpy(__dst, __src, __num_chars * sizeof(__CHAR16_TYPE__));
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16mempcpy_defined */
