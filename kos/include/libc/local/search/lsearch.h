/* HASH CRC-32:0x654befce */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_lsearch_defined
#define __local_lsearch_defined 1
#include <__crt.h>
#ifndef ____compar_fn_t_defined
#define ____compar_fn_t_defined 1
typedef int (__LIBCCALL *__compar_fn_t)(void const *__a, void const *__b);
#endif /* !____compar_fn_t_defined */
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_lfind_defined
#define __local___localdep_lfind_defined 1
#ifdef __CRT_HAVE_lfind
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2, 3, 5)),void *,__NOTHROW_NCX,__localdep_lfind,(void const *__key, void const *__base, __SIZE_TYPE__ __KOS_FIXED_CONST *__nmemb, __SIZE_TYPE__ __size, __compar_fn_t __compar),lfind,(__key,__base,__nmemb,__size,__compar))
#else /* __CRT_HAVE_lfind */
__NAMESPACE_LOCAL_END
#include <libc/local/search/lfind.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_lfind __LIBC_LOCAL_NAME(lfind)
#endif /* !__CRT_HAVE_lfind */
#endif /* !__local___localdep_lfind_defined */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined 1
#ifdef __CRT_HAVE_memcpy
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
__LOCAL_LIBC(lsearch) __ATTR_NONNULL((2, 3, 5)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(lsearch))(void const *__key, void *__base, __SIZE_TYPE__ *__nmemb, __SIZE_TYPE__ __size, __compar_fn_t __compar) {
	void *__result;
	__result = __NAMESPACE_LOCAL_SYM __localdep_lfind(__key, __base, __nmemb, __size, __compar);
	if (__result == __NULLPTR) {
		__result = __NAMESPACE_LOCAL_SYM __localdep_memcpy((__BYTE_TYPE__ *)__base + (*__nmemb) * __size, __key, __size);
		++*__nmemb;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lsearch_defined
#define __local___localdep_lsearch_defined 1
#define __localdep_lsearch __LIBC_LOCAL_NAME(lsearch)
#endif /* !__local___localdep_lsearch_defined */
#endif /* !__local_lsearch_defined */
