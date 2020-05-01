/* HASH CRC-32:0x72610eb1 */
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
#ifndef __local_memmovec_defined
#define __local_memmovec_defined 1
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <hybrid/host.h>
/* Dependency: "memmove" from "string" */
#ifndef ____localdep_memmove_defined
#define ____localdep_memmove_defined 1
#ifdef __fast_memmove_defined
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memmove (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmove))
#elif defined(__CRT_HAVE_memmove)
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmove,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* LIBC: memmove */
#include <local/string/memmove.h>
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memmove (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmove))
#endif /* memmove... */
#endif /* !____localdep_memmove_defined */

/* Dependency: "memmovew" from "string" */
#ifndef ____localdep_memmovew_defined
#define ____localdep_memmovew_defined 1
#ifdef __fast_memmovew_defined
/* Move memory between potentially overlapping memory blocks. */
#define __localdep_memmovew (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovew))
#elif defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovew,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 2)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovew,(/*aligned(2)*/ void *__dst, /*aligned(2)*/ void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#else /* LIBC: memmovew */
#include <local/string/memmovew.h>
/* Move memory between potentially overlapping memory blocks. */
#define __localdep_memmovew (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovew))
#endif /* memmovew... */
#endif /* !____localdep_memmovew_defined */

/* Dependency: "memmovel" from "string" */
#ifndef ____localdep_memmovel_defined
#define ____localdep_memmovel_defined 1
#ifdef __fast_memmovel_defined
/* Move memory between potentially overlapping memory blocks. */
#define __localdep_memmovel (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovel))
#elif defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmovel,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 4)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmovel,(/*aligned(4)*/ void *__dst, /*aligned(4)*/ void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#else /* LIBC: memmovel */
#include <local/string/memmovel.h>
/* Move memory between potentially overlapping memory blocks. */
#define __localdep_memmovel (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovel))
#endif /* memmovel... */
#endif /* !____localdep_memmovel_defined */

/* Dependency: "memmoveq" from "string" */
#ifndef ____localdep_memmoveq_defined
#define ____localdep_memmoveq_defined 1
#ifdef __fast_memmoveq_defined
/* Move memory between potentially overlapping memory blocks. */
#define __localdep_memmoveq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveq))
#elif defined(__CRT_HAVE_memmoveq)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveq,(/*aligned(8)*/ void *__dst, /*aligned(8)*/ void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,(__dst,__src,__n_qwords))
#else /* LIBC: memmoveq */
#include <local/string/memmoveq.h>
/* Move memory between potentially overlapping memory blocks. */
#define __localdep_memmoveq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveq))
#endif /* memmoveq... */
#endif /* !____localdep_memmoveq_defined */

__NAMESPACE_LOCAL_BEGIN
/* Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
__LOCAL_LIBC(memmovec) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memmovec))(void *__dst,
                                                      void const *__src,
                                                      __SIZE_TYPE__ __elem_count,
                                                      __SIZE_TYPE__ __elem_size) {
#line 2477 "kos/src/libc/magic/string.c"
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (__elem_size) {

	case 1:
		return __localdep_memmove(__dst, __src, __elem_count);

	case 2:
		return __localdep_memmovew(__dst, __src, __elem_count);

	case 4:
		return __localdep_memmovel(__dst, __src, __elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return __localdep_memmoveq(__dst, __src, __elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return __localdep_memmove(__dst, __src, __elem_count * __elem_size);
}

__NAMESPACE_LOCAL_END
#endif /* !__local_memmovec_defined */
