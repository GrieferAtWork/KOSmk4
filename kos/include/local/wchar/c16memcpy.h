/* HASH CRC-32:0x616d4084 */
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
#ifndef __local_c16memcpy_defined
#define __local_c16memcpy_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "memcpyw" from "string" */
#ifndef ____localdep_memcpyw_defined
#define ____localdep_memcpyw_defined 1
#if defined(__fast_memcpyw_defined)
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpyw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyw))
#elif defined(__CRT_HAVE_memcpyw)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),memcpyw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 2)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmemcpy,(__dst,__src,__n_words))
#else /* LIBC: memcpyw */
#include <local/string/memcpyw.h>
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpyw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyw))
#endif /* memcpyw... */
#endif /* !____localdep_memcpyw_defined */

/* Dependency: "memcpyl" from "string" */
#ifndef ____localdep_memcpyl_defined
#define ____localdep_memcpyl_defined 1
#if defined(__fast_memcpyl_defined)
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpyl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyl))
#elif defined(__CRT_HAVE_memcpyl)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),memcpyl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 4)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmemcpy,(__dst,__src,__n_dwords))
#else /* LIBC: memcpyl */
#include <local/string/memcpyl.h>
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpyl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyl))
#endif /* memcpyl... */
#endif /* !____localdep_memcpyl_defined */

/* Dependency: "memcpy" from "string" */
#ifndef ____localdep_memcpy_defined
#define ____localdep_memcpy_defined 1
#if defined(__fast_memcpy_defined)
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))
#elif defined(__CRT_HAVE_memcpy)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* LIBC: memcpy */
#include <local/string/memcpy.h>
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))
#endif /* memcpy... */
#endif /* !____localdep_memcpy_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16memcpy) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c16memcpy))(__CHAR16_TYPE__ *__restrict __dst,
                                                       __CHAR16_TYPE__ const *__restrict __src,
                                                       __SIZE_TYPE__ __num_chars) {
#line 271 "kos/src/libc/magic/wchar.c"
#if 2 == 2
	return (__CHAR16_TYPE__ *)__localdep_memcpyw(__dst, __src, __num_chars);
#elif 2 == 4
	return (__CHAR16_TYPE__ *)__localdep_memcpyl(__dst, __src, __num_chars);
#else
	return (__CHAR16_TYPE__ *)__localdep_memcpy(__dst, __src, __num_chars * sizeof(__CHAR16_TYPE__));
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16memcpy_defined */
