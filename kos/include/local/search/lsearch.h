/* HASH CRC-32:0xc13f65a3 */
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
#ifndef __local_lsearch_defined
#define __local_lsearch_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "lfind" from "search" */
#ifndef ____localdep_lfind_defined
#define ____localdep_lfind_defined 1
#ifdef __CRT_HAVE_lfind
/* Perform linear search for KEY by comparing by COMPAR in an array [BASE, BASE+NMEMB*SIZE) */
__CREDIRECT(,void *,__NOTHROW_NCX,__localdep_lfind,(void const *__key, void const *__base, __SIZE_TYPE__ *__nmemb, __SIZE_TYPE__ __size, __compar_fn_t __compar),lfind,(__key,__base,__nmemb,__size,__compar))
#else /* LIBC: lfind */
#include <local/search/lfind.h>
/* Perform linear search for KEY by comparing by COMPAR in an array [BASE, BASE+NMEMB*SIZE) */
#define __localdep_lfind (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lfind))
#endif /* lfind... */
#endif /* !____localdep_lfind_defined */

/* Dependency: "memcpy" from "string" */
#ifndef ____localdep_memcpy_defined
#define ____localdep_memcpy_defined 1
#ifdef __fast_memcpy_defined
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))
#elif defined(__CRT_HAVE_memcpy)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* LIBC: memcpy */
#include <local/string/memcpy.h>
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))
#endif /* memcpy... */
#endif /* !____localdep_memcpy_defined */

__NAMESPACE_LOCAL_BEGIN
/* Perform linear search for KEY by comparing by COMPAR function
 * in array [BASE, BASE+NMEMB*SIZE) and insert entry if not found */
__LOCAL_LIBC(lsearch) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(lsearch))(void const *__key,
                                                     void *__base,
                                                     __SIZE_TYPE__ *__nmemb,
                                                     __SIZE_TYPE__ __size,
                                                     __compar_fn_t __compar) {
#line 788 "kos/src/libc/magic/search.c"
	void *__result;
	__result = __localdep_lfind(__key, __base, __nmemb, __size, __compar);
	if (__result == __NULLPTR) {
		__result = __localdep_memcpy((__BYTE_TYPE__ *)__base + (*__nmemb) * __size, __key, __size);
		++(*__nmemb);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_lsearch_defined */
