/* HASH CRC-32:0x4d6f0f9b */
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
#ifndef __local_hcreate_r_defined
#define __local_hcreate_r_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
struct hsearch_data;
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: calloc from stdlib */
#ifndef __local___localdep_calloc_defined
#define __local___localdep_calloc_defined 1
#if __has_builtin(__builtin_calloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_calloc)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__localdep_calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),calloc,{ return __builtin_calloc(__count, __num_bytes); })
#elif defined(__CRT_HAVE_calloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__localdep_calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),calloc,(__count,__num_bytes))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <local/stdlib/calloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_calloc __LIBC_LOCAL_NAME(calloc)
#else /* ... */
#undef __local___localdep_calloc_defined
#endif /* !... */
#endif /* !__local___localdep_calloc_defined */
__NAMESPACE_LOCAL_END
#ifndef __hsearch_data_defined
#define __hsearch_data_defined 1
struct _ENTRY;
struct hsearch_data {
	struct _ENTRY  *table;
	__UINT32_TYPE__ size;
	__UINT32_TYPE__ filled;
};
#endif /* !__hsearch_data_defined */
#ifndef __ENTRY_defined
#define __ENTRY_defined 1
typedef struct entry {
	char *key;
	void *data;
} ENTRY;
#endif /* !__ENTRY_defined */
#include <hybrid/limitcore.h>
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* For the used double hash method the table size has to be a prime. To
 * correct the user given table size we need a prime test.  This trivial
 * algorithm is adequate because
 * a)  the code is (most probably) called a few times per program run and
 * b)  the number is small because the table must fit in the core */
__LOCAL_LIBC(__isprime) __ATTR_CONST int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(__isprime))(unsigned int __number) {
	/* no even number will be passed */
	for (unsigned int __div = 3; __div <= __number / __div; __div += 2) {
		if (__number % __div == 0)
			return 0;
	}
	return 1;
}
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
/* Reentrant versions which can handle multiple hashing tables at the same time */
__LOCAL_LIBC(hcreate_r) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(hcreate_r))(__SIZE_TYPE__ __nel, struct hsearch_data *__htab) {
	typedef struct {
		unsigned int __used;
		struct entry        __entry;
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
		if (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__isprime)(__nel))
			break;
	}
	__htab->size   = __nel;
	__htab->filled = 0;
	__htab->table  = (struct _ENTRY *)__localdep_calloc(__htab->size + 1, sizeof(__entry_type));
	if (__htab->table == __NULLPTR)
		return 0;
	return 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_hcreate_r_defined
#define __local___localdep_hcreate_r_defined 1
#define __localdep_hcreate_r __LIBC_LOCAL_NAME(hcreate_r)
#endif /* !__local___localdep_hcreate_r_defined */
#else /* __CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign */
#undef __local_hcreate_r_defined
#endif /* !__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign */
#endif /* !__local_hcreate_r_defined */
