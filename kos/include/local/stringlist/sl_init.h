/* HASH CRC-32:0xff870add */
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
#ifndef __local_sl_init_defined
#define __local_sl_init_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#ifndef ___stringlist_defined
#define ___stringlist_defined 1
typedef struct _stringlist {
	char   **sl_str;
	__SIZE_TYPE__   sl_max;
	__SIZE_TYPE__   sl_cur;
} StringList;
#endif
__NAMESPACE_LOCAL_BEGIN
/* Dependency: free from stdlib */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined 1
#ifdef __free_defined
__NAMESPACE_GLB_USING(free)
#define __localdep_free free
#elif defined(__std_free_defined)
__NAMESPACE_STD_USING(free)
#define __localdep_free free
#elif __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ return __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
/* Dependency: malloc from stdlib */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined 1
#ifdef __malloc_defined
__NAMESPACE_GLB_USING(malloc)
#define __localdep_malloc malloc
#elif defined(__std_malloc_defined)
__NAMESPACE_STD_USING(malloc)
#define __localdep_malloc malloc
#elif __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#else /* ... */
#undef __local___localdep_malloc_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
/* Allocates and returns a new StringList object. Upon error, `NULL' is returned */
__LOCAL_LIBC(sl_init) __ATTR_WUNUSED struct _stringlist *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sl_init))(void) {
	struct _stringlist *__result;
	__result = (struct _stringlist *)__localdep_malloc(sizeof(struct _stringlist));
	if __likely(__result != __NULLPTR) {
		__result->sl_cur = 0;
		__result->sl_max = 20;
		__result->sl_str = (char **)__localdep_malloc(20 * sizeof(char *));
		if __unlikely(__result->sl_str == __NULLPTR) {
			__localdep_free(__result);
			__result = __NULLPTR;
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sl_init_defined
#define __local___localdep_sl_init_defined 1
#define __localdep_sl_init __LIBC_LOCAL_NAME(sl_init)
#endif /* !__local___localdep_sl_init_defined */
#else /* (__CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_free || __CRT_HAVE_cfree) */
#undef __local_sl_init_defined
#endif /* (!__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_free && !__CRT_HAVE_cfree) */
#endif /* !__local_sl_init_defined */
