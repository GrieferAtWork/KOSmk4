/* HASH CRC-32:0xcf8ba34e */
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
#ifndef __local_memmovedownc_defined
#define __local_memmovedownc_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <hybrid/host.h>
/* Dependency: "memmovedown" from "string" */
#ifndef ____localdep_memmovedown_defined
#define ____localdep_memmovedown_defined 1
#ifdef __fast_memmovedown_defined
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
#define __localdep_memmovedown (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedown))
#elif defined(__CRT_HAVE_memmovedown)
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmovedown,(__dst,__src,__n_bytes))
#else /* LIBC: memmovedown */
#include <local/string/memmovedown.h>
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
#define __localdep_memmovedown (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedown))
#endif /* memmovedown... */
#endif /* !____localdep_memmovedown_defined */

/* Dependency: "memmovedownw" from "string" */
#ifndef ____localdep_memmovedownw_defined
#define ____localdep_memmovedownw_defined 1
#ifdef __fast_memmovedownw_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
#define __localdep_memmovedownw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownw))
#elif defined(__CRT_HAVE_memmovedownw)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownw,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),memmovedownw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownw,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 2)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownw,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#else /* LIBC: memmovedownw */
#include <local/string/memmovedownw.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
#define __localdep_memmovedownw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownw))
#endif /* memmovedownw... */
#endif /* !____localdep_memmovedownw_defined */

/* Dependency: "memmovedownl" from "string" */
#ifndef ____localdep_memmovedownl_defined
#define ____localdep_memmovedownl_defined 1
#ifdef __fast_memmovedownl_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
#define __localdep_memmovedownl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownl))
#elif defined(__CRT_HAVE_memmovedownl)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownl,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),memmovedownl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 4)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownl,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownl,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#else /* LIBC: memmovedownl */
#include <local/string/memmovedownl.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
#define __localdep_memmovedownl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownl))
#endif /* memmovedownl... */
#endif /* !____localdep_memmovedownl_defined */

/* Dependency: "memmovedownq" from "string" */
#ifndef ____localdep_memmovedownq_defined
#define ____localdep_memmovedownq_defined 1
#ifdef __fast_memmovedownq_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_QWORDS') */
#define __localdep_memmovedownq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownq))
#elif defined(__CRT_HAVE_memmovedownq)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_QWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownq,(/*aligned(8)*/ void *__dst, /*aligned(8)*/ void const *__src, __SIZE_TYPE__ __n_qwords),memmovedownq,(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_memmoveq)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_QWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownq,(/*aligned(8)*/ void *__dst, /*aligned(8)*/ void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,(__dst,__src,__n_qwords))
#else /* LIBC: memmovedownq */
#include <local/string/memmovedownq.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_QWORDS') */
#define __localdep_memmovedownq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownq))
#endif /* memmovedownq... */
#endif /* !____localdep_memmovedownq_defined */

__NAMESPACE_LOCAL_BEGIN
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__LOCAL_LIBC(memmovedownc) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memmovedownc))(void *__dst,
                                                          void const *__src,
                                                          __SIZE_TYPE__ __elem_count,
                                                          __SIZE_TYPE__ __elem_size) {
#line 2474 "kos/src/libc/magic/string.c"
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (__elem_size) {

	case 1:
		return __localdep_memmovedown(__dst, __src, __elem_count);

	case 2:
		return __localdep_memmovedownw(__dst, __src, __elem_count);

	case 4:
		return __localdep_memmovedownl(__dst, __src, __elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return __localdep_memmovedownq(__dst, __src, __elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return __localdep_memmovedown(__dst, __src, __elem_count * __elem_size);
}

__NAMESPACE_LOCAL_END
#endif /* !__local_memmovedownc_defined */
