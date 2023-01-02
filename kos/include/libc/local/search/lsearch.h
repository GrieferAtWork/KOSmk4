/* HASH CRC-32:0xd79b5a02 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_lsearch_defined
#define __local_lsearch_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_lfind_defined
#define __local___localdep_lfind_defined
#ifdef __CRT_HAVE_lfind
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void *,__THROWING,__localdep_lfind,(void const *__key, void const *__pbase, __SIZE_TYPE__ __KOS_FIXED_CONST *__pitem_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),lfind,(__key,__pbase,__pitem_count,__item_size,__compar))
#elif defined(__CRT_HAVE__lfind)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)),void *,__THROWING,__localdep_lfind,(void const *__key, void const *__pbase, __SIZE_TYPE__ __KOS_FIXED_CONST *__pitem_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)),_lfind,(__key,__pbase,__pitem_count,__item_size,__compar))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/search/lfind.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_lfind __LIBC_LOCAL_NAME(lfind)
#endif /* !... */
#endif /* !__local___localdep_lfind_defined */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
__LOCAL_LIBC(lsearch) __ATTR_INOUT(2) __ATTR_INOUT(3) __ATTR_IN_OPT(1) __ATTR_NONNULL((5)) void *
(__LIBCCALL __LIBC_LOCAL_NAME(lsearch))(void const *__key, void *__pbase, __SIZE_TYPE__ *__pitem_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) __THROWS(...) {
	void *__result;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_lfind)(__key, __pbase, __pitem_count, __item_size, __compar);
	if (__result == __NULLPTR) {
		__result = (__NAMESPACE_LOCAL_SYM __localdep_memcpy)((__BYTE_TYPE__ *)__pbase + (*__pitem_count) * __item_size, __key, __item_size);
		++*__pitem_count;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lsearch_defined
#define __local___localdep_lsearch_defined
#define __localdep_lsearch __LIBC_LOCAL_NAME(lsearch)
#endif /* !__local___localdep_lsearch_defined */
#endif /* !__local_lsearch_defined */
