/* HASH CRC-32:0xe334a32 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_hcreate_r_defined
#if defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#define __local_hcreate_r_defined 1
#include <hybrid/limitcore.h>

#include <parts/errno.h>
/* Dependency: "isprime" from "search" */
#ifndef ____localdep_isprime_defined
#define ____localdep_isprime_defined 1
#ifdef __CRT_HAVE_isprime
/* For the used double hash method the table size has to be a prime. To
 * correct the user given table size we need a prime test.  This trivial
 * algorithm is adequate because
 * a)  the code is (most probably) called a few times per program run and
 * b)  the number is small because the table must fit in the core */
__CREDIRECT(__ATTR_CONST,int,__NOTHROW_NCX,__localdep_isprime,(unsigned int __number),isprime,(__number))
#else /* LIBC: isprime */
#include <local/search/isprime.h>
/* For the used double hash method the table size has to be a prime. To
 * correct the user given table size we need a prime test.  This trivial
 * algorithm is adequate because
 * a)  the code is (most probably) called a few times per program run and
 * b)  the number is small because the table must fit in the core */
#define __localdep_isprime (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isprime))
#endif /* isprime... */
#endif /* !____localdep_isprime_defined */

/* Dependency: "calloc" from "stdlib" */
#ifndef ____localdep_calloc_defined
#define ____localdep_calloc_defined 1
#ifdef __std___localdep_calloc_defined
__NAMESPACE_STD_USING(__localdep_calloc)
#elif __has_builtin(__builtin_calloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_calloc)
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *__NOTHROW_NCX(__LIBCCALL __localdep_calloc)(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes) { return __builtin_calloc(__count, __num_bytes); }
#elif defined(__CRT_HAVE_calloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__localdep_calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),calloc,(__count,__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#include <local/stdlib/calloc.h>
#define __localdep_calloc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(calloc))
#else /* CUSTOM: calloc */
#undef ____localdep_calloc_defined
#endif /* calloc... */
#endif /* !____localdep_calloc_defined */

__NAMESPACE_LOCAL_BEGIN
/* Reentrant versions which can handle multiple hashing tables at the same time */
__LOCAL_LIBC(hcreate_r) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(hcreate_r))(__SIZE_TYPE__ __nel,
                                                       struct hsearch_data *__htab) {
#line 329 "kos/src/libc/magic/search.c"
	typedef struct {
		unsigned int __used;
		ENTRY        __entry;
	} __entry_type;
	if (__htab == __NULLPTR) {
#ifdef __EINVAL
		__libc_seterrno(__EINVAL);
#endif /* __EINVAL */
		return 0;
	}
	if (__htab->table != __NULLPTR)
		return 0;
	if (__nel < 3)
		__nel = 3;
	for (__nel |= 1; ; __nel += 2) {
		if (__UINT_MAX__ - 2 < __nel) {
#ifdef __ENOMEM
			__libc_seterrno(__ENOMEM);
#endif /* __ENOMEM */
			return 0;
		}
		if (__localdep_isprime(__nel))
			break;
	}
	__htab->size   = __nel;
	__htab->filled = 0;
	__htab->table  = (struct ___ENTRY *)__localdep_calloc(__htab->__size+1, sizeof(__entry_type));
	if (__htab->table == __NULLPTR)
		return 0;
	return 1;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_posix_memalign || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_malloc */
#endif /* !__local_hcreate_r_defined */
