/* HASH CRC-32:0x10f1960 */
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
#ifndef __local_mempmovec_defined
#define __local_mempmovec_defined 1
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <hybrid/host.h>
/* Dependency: "mempmove" from "string" */
#ifndef ____localdep_mempmove_defined
#define ____localdep_mempmove_defined 1
#ifdef __fast_mempmove_defined
/* Same as `memmove', but return `DST + N_BYTES', rather than `DST' */
#define __localdep_mempmove (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmove))
#elif defined(__CRT_HAVE_mempmove)
/* Same as `memmove', but return `DST + N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempmove,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmove,(__dst,__src,__n_bytes))
#else /* LIBC: mempmove */
#include <local/string/mempmove.h>
/* Same as `memmove', but return `DST + N_BYTES', rather than `DST' */
#define __localdep_mempmove (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmove))
#endif /* mempmove... */
#endif /* !____localdep_mempmove_defined */

/* Dependency: "mempmovew" from "string" */
#ifndef ____localdep_mempmovew_defined
#define ____localdep_mempmovew_defined 1
#ifdef __fast_mempmovew_defined
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' */
#define __localdep_mempmovew (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovew))
#elif defined(__CRT_HAVE_mempmovew)
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovew,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),mempmovew,(__dst,__src,__n_words))
#else /* LIBC: mempmovew */
#include <local/string/mempmovew.h>
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' */
#define __localdep_mempmovew (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovew))
#endif /* mempmovew... */
#endif /* !____localdep_mempmovew_defined */

/* Dependency: "mempmovel" from "string" */
#ifndef ____localdep_mempmovel_defined
#define ____localdep_mempmovel_defined 1
#ifdef __fast_mempmovel_defined
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' */
#define __localdep_mempmovel (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovel))
#elif defined(__CRT_HAVE_mempmovel)
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovel,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),mempmovel,(__dst,__src,__n_dwords))
#else /* LIBC: mempmovel */
#include <local/string/mempmovel.h>
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' */
#define __localdep_mempmovel (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovel))
#endif /* mempmovel... */
#endif /* !____localdep_mempmovel_defined */

/* Dependency: "mempmoveq" from "string" */
#ifndef ____localdep_mempmoveq_defined
#define ____localdep_mempmoveq_defined 1
#ifdef __fast_mempmoveq_defined
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' */
#define __localdep_mempmoveq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveq))
#elif defined(__CRT_HAVE_mempmoveq)
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_mempmoveq,(/*aligned(8)*/ void *__restrict __dst, /*aligned(8)*/ void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmoveq,(__dst,__src,__n_qwords))
#else /* LIBC: mempmoveq */
#include <local/string/mempmoveq.h>
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' */
#define __localdep_mempmoveq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveq))
#endif /* mempmoveq... */
#endif /* !____localdep_mempmoveq_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memmovec', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
__LOCAL_LIBC(mempmovec) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempmovec))(void *__dst,
                                                       void const *__src,
                                                       __SIZE_TYPE__ __elem_count,
                                                       __SIZE_TYPE__ __elem_size) {
#line 2485 "kos/src/libc/magic/string.c"
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (__elem_size) {

	case 1:
		return __localdep_mempmove(__dst, __src, __elem_count);

	case 2:
		return __localdep_mempmovew(__dst, __src, __elem_count);

	case 4:
		return __localdep_mempmovel(__dst, __src, __elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return __localdep_mempmoveq(__dst, __src, __elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return __localdep_mempmove(__dst, __src, __elem_count * __elem_size);
}

__NAMESPACE_LOCAL_END
#endif /* !__local_mempmovec_defined */
