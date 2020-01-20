/* HASH CRC-32:0xecc3fc98 */
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
#ifndef __local_mempmovedownc_defined
#define __local_mempmovedownc_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <hybrid/host.h>
/* Dependency: "mempmovedown" from "string" */
#ifndef ____localdep_mempmovedown_defined
#define ____localdep_mempmovedown_defined 1
#ifdef __fast_mempmovedown_defined
/* Same as `memmovedown', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES') */
#define __localdep_mempmovedown (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedown))
#elif defined(__CRT_HAVE_mempmovedown)
/* Same as `memmovedown', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmovedown,(__dst,__src,__n_bytes))
#else /* LIBC: mempmovedown */
#include <local/string/mempmovedown.h>
/* Same as `memmovedown', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES') */
#define __localdep_mempmovedown (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedown))
#endif /* mempmovedown... */
#endif /* !____localdep_mempmovedown_defined */

/* Dependency: "mempmovedownw" from "string" */
#ifndef ____localdep_mempmovedownw_defined
#define ____localdep_mempmovedownw_defined 1
#ifdef __fast_mempmovedownw_defined
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST <= SRC || !N_WORDS') */
#define __localdep_mempmovedownw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownw))
#elif defined(__CRT_HAVE_mempmovedownw)
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST <= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovedownw,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),mempmovedownw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_mempmovew)
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST <= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovedownw,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),mempmovew,(__dst,__src,__n_words))
#else /* LIBC: mempmovedownw */
#include <local/string/mempmovedownw.h>
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST <= SRC || !N_WORDS') */
#define __localdep_mempmovedownw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownw))
#endif /* mempmovedownw... */
#endif /* !____localdep_mempmovedownw_defined */

/* Dependency: "mempmovedownl" from "string" */
#ifndef ____localdep_mempmovedownl_defined
#define ____localdep_mempmovedownl_defined 1
#ifdef __fast_mempmovedownl_defined
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST <= SRC || !N_DWORDS') */
#define __localdep_mempmovedownl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownl))
#elif defined(__CRT_HAVE_mempmovedownl)
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST <= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovedownl,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),mempmovedownl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_mempmovel)
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST <= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovedownl,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),mempmovel,(__dst,__src,__n_dwords))
#else /* LIBC: mempmovedownl */
#include <local/string/mempmovedownl.h>
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST <= SRC || !N_DWORDS') */
#define __localdep_mempmovedownl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownl))
#endif /* mempmovedownl... */
#endif /* !____localdep_mempmovedownl_defined */

/* Dependency: "mempmovedownq" from "string" */
#ifndef ____localdep_mempmovedownq_defined
#define ____localdep_mempmovedownq_defined 1
#ifdef __fast_mempmovedownq_defined
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST <= SRC || !N_QWORDS') */
#define __localdep_mempmovedownq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownq))
#elif defined(__CRT_HAVE_mempmovedownq)
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST <= SRC || !N_QWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovedownq,(/*aligned(8)*/ void *__restrict __dst, /*aligned(8)*/ void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmovedownq,(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_mempmoveq)
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST <= SRC || !N_QWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovedownq,(/*aligned(8)*/ void *__restrict __dst, /*aligned(8)*/ void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmoveq,(__dst,__src,__n_qwords))
#else /* LIBC: mempmovedownq */
#include <local/string/mempmovedownq.h>
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST <= SRC || !N_QWORDS') */
#define __localdep_mempmovedownq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownq))
#endif /* mempmovedownq... */
#endif /* !____localdep_mempmovedownq_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memmovedownc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE') */
__LOCAL_LIBC(mempmovedownc) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempmovedownc))(void *__dst,
                                                           void const *__src,
                                                           __SIZE_TYPE__ __elem_count,
                                                           __SIZE_TYPE__ __elem_size) {
#line 2495 "kos/src/libc/magic/string.c"
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (__elem_size) {

	case 1:
		return __localdep_mempmovedown(__dst, __src, __elem_count);

	case 2:
		return __localdep_mempmovedownw(__dst, __src, __elem_count);

	case 4:
		return __localdep_mempmovedownl(__dst, __src, __elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return __localdep_mempmovedownq(__dst, __src, __elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return __localdep_mempmovedown(__dst, __src, __elem_count * __elem_size);
}

__NAMESPACE_LOCAL_END
#endif /* !__local_mempmovedownc_defined */
