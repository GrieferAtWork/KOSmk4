/* HASH CRC-32:0xdbcff630 */
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
#ifndef __local_mempmoveupc_defined
#define __local_mempmoveupc_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <hybrid/host.h>

#include <hybrid/host.h>
/* Dependency: "mempmoveup" from "string" */
#ifndef ____localdep_mempmoveup_defined
#define ____localdep_mempmoveup_defined 1
#ifdef __fast_mempmoveup_defined
/* Same as `memmoveup', but return `DST + N_BYTES', rather than `DST' (assumes that `DST >= SRC || !N_BYTES') */
#define __localdep_mempmoveup (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveup))
#elif defined(__CRT_HAVE_mempmoveup)
/* Same as `memmoveup', but return `DST + N_BYTES', rather than `DST' (assumes that `DST >= SRC || !N_BYTES') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmoveup,(__dst,__src,__n_bytes))
#else /* LIBC: mempmoveup */
#include <local/string/mempmoveup.h>
/* Same as `memmoveup', but return `DST + N_BYTES', rather than `DST' (assumes that `DST >= SRC || !N_BYTES') */
#define __localdep_mempmoveup (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveup))
#endif /* mempmoveup... */
#endif /* !____localdep_mempmoveup_defined */

/* Dependency: "mempmoveupw" from "string" */
#ifndef ____localdep_mempmoveupw_defined
#define ____localdep_mempmoveupw_defined 1
#ifdef __fast_mempmoveupw_defined
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST >= SRC || !N_WORDS') */
#define __localdep_mempmoveupw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupw))
#elif defined(__CRT_HAVE_mempmoveupw)
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST >= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempmoveupw,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),mempmoveupw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_mempmovew)
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST >= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempmoveupw,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),mempmovew,(__dst,__src,__n_words))
#else /* LIBC: mempmoveupw */
#include <local/string/mempmoveupw.h>
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST >= SRC || !N_WORDS') */
#define __localdep_mempmoveupw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupw))
#endif /* mempmoveupw... */
#endif /* !____localdep_mempmoveupw_defined */

/* Dependency: "mempmoveupl" from "string" */
#ifndef ____localdep_mempmoveupl_defined
#define ____localdep_mempmoveupl_defined 1
#ifdef __fast_mempmoveupl_defined
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST >= SRC || !N_DWORDS') */
#define __localdep_mempmoveupl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupl))
#elif defined(__CRT_HAVE_mempmoveupl)
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST >= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempmoveupl,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),mempmoveupl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_mempmovel)
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST >= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempmoveupl,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),mempmovel,(__dst,__src,__n_dwords))
#else /* LIBC: mempmoveupl */
#include <local/string/mempmoveupl.h>
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST >= SRC || !N_DWORDS') */
#define __localdep_mempmoveupl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupl))
#endif /* mempmoveupl... */
#endif /* !____localdep_mempmoveupl_defined */

/* Dependency: "mempmoveupq" from "string" */
#ifndef ____localdep_mempmoveupq_defined
#define ____localdep_mempmoveupq_defined 1
#ifdef __fast_mempmoveupq_defined
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST >= SRC || !N_QWORDS') */
#define __localdep_mempmoveupq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupq))
#elif defined(__CRT_HAVE_mempmoveupq)
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST >= SRC || !N_QWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_mempmoveupq,(/*aligned(8)*/ void *__restrict __dst, /*aligned(8)*/ void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmoveupq,(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_mempmoveq)
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST >= SRC || !N_QWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_mempmoveupq,(/*aligned(8)*/ void *__restrict __dst, /*aligned(8)*/ void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmoveq,(__dst,__src,__n_qwords))
#else /* LIBC: mempmoveupq */
#include <local/string/mempmoveupq.h>
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST >= SRC || !N_QWORDS') */
#define __localdep_mempmoveupq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupq))
#endif /* mempmoveupq... */
#endif /* !____localdep_mempmoveupq_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memmoveupc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE') */
__LOCAL_LIBC(mempmoveupc) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempmoveupc))(void *__dst,
                                                         void const *__src,
                                                         __SIZE_TYPE__ __elem_count,
                                                         __SIZE_TYPE__ __elem_size) {
#line 2482 "kos/src/libc/magic/string.c"
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (__elem_size) {

	case 1:
		return __localdep_mempmoveup(__dst, __src, __elem_count);

	case 2:
		return __localdep_mempmoveupw(__dst, __src, __elem_count);

	case 4:
		return __localdep_mempmoveupl(__dst, __src, __elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return __localdep_mempmoveupq(__dst, __src, __elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return __localdep_mempmoveup(__dst, __src, __elem_count * __elem_size);
}

__NAMESPACE_LOCAL_END
#endif /* !__local_mempmoveupc_defined */
