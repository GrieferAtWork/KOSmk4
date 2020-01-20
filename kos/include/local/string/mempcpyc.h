/* HASH CRC-32:0x73917070 */
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
#ifndef __local_mempcpyc_defined
#define __local_mempcpyc_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <hybrid/host.h>
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

/* Dependency: "mempcpyw" from "string" */
#ifndef ____localdep_mempcpyw_defined
#define ____localdep_mempcpyw_defined 1
#ifdef __fast_mempcpyw_defined
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
#define __localdep_mempcpyw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyw))
#elif defined(__CRT_HAVE_mempcpyw)
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyw,(/*aligned(2)*/ void *__restrict __dst, /*aligned(2)*/ void const *__restrict __src, __SIZE_TYPE__ __n_words),mempcpyw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyw,(/*aligned(2)*/ void *__restrict __dst, /*aligned(2)*/ void const *__restrict __src, __SIZE_TYPE__ __n_words),wmempcpy,(__dst,__src,__n_words))
#else /* LIBC: mempcpyw */
#include <local/string/mempcpyw.h>
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
#define __localdep_mempcpyw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyw))
#endif /* mempcpyw... */
#endif /* !____localdep_mempcpyw_defined */

/* Dependency: "mempcpyl" from "string" */
#ifndef ____localdep_mempcpyl_defined
#define ____localdep_mempcpyl_defined 1
#ifdef __fast_mempcpyl_defined
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
#define __localdep_mempcpyl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyl))
#elif defined(__CRT_HAVE_mempcpyl)
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyl,(/*aligned(4)*/ void *__restrict __dst, /*aligned(4)*/ void const *__restrict __src, __SIZE_TYPE__ __n_dwords),mempcpyl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyl,(/*aligned(4)*/ void *__restrict __dst, /*aligned(4)*/ void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmempcpy,(__dst,__src,__n_dwords))
#else /* LIBC: mempcpyl */
#include <local/string/mempcpyl.h>
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
#define __localdep_mempcpyl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyl))
#endif /* mempcpyl... */
#endif /* !____localdep_mempcpyl_defined */

/* Dependency: "mempcpyq" from "string" */
#ifndef ____localdep_mempcpyq_defined
#define ____localdep_mempcpyq_defined 1
#ifdef __fast_mempcpyq_defined
/* Same as `memcpyq', but return `DST + N_QWORDS', rather than `DST' */
#define __localdep_mempcpyq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyq))
#elif defined(__CRT_HAVE_mempcpyq)
/* Same as `memcpyq', but return `DST + N_QWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyq,(/*aligned(8)*/ void *__restrict __dst, /*aligned(8)*/ void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempcpyq,(__dst,__src,__n_qwords))
#else /* LIBC: mempcpyq */
#include <local/string/mempcpyq.h>
/* Same as `memcpyq', but return `DST + N_QWORDS', rather than `DST' */
#define __localdep_mempcpyq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyq))
#endif /* mempcpyq... */
#endif /* !____localdep_mempcpyq_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
__LOCAL_LIBC(mempcpyc) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempcpyc))(void *__restrict __dst,
                                                      void const *__restrict __src,
                                                      __SIZE_TYPE__ __elem_count,
                                                      __SIZE_TYPE__ __elem_size) {
#line 2448 "kos/src/libc/magic/string.c"
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (__elem_size) {

	case 1:
		return __localdep_mempcpy(__dst, __src, __elem_count);

	case 2:
		return __localdep_mempcpyw(__dst, __src, __elem_count);

	case 4:
		return __localdep_mempcpyl(__dst, __src, __elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return __localdep_mempcpyq(__dst, __src, __elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return __localdep_mempcpy(__dst, __src, __elem_count * __elem_size);
}

__NAMESPACE_LOCAL_END
#endif /* !__local_mempcpyc_defined */
