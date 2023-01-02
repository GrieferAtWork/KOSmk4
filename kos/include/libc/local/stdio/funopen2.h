/* HASH CRC-32:0xed01f0ad */
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
#ifndef __local_funopen2_defined
#define __local_funopen2_defined
#include <__crt.h>
#include <bits/types.h>
#if (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2))
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_funopen2_64_defined
#define __local___localdep_funopen2_64_defined
#if defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen2_64,(void const *__cookie, __SSIZE_TYPE__ (__LIBKCALL *__readfn)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes), __SSIZE_TYPE__ (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes), __off64_t (__LIBKCALL *__seekfn)(void *__cookie, __off64_t __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)),funopen2,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif defined(__CRT_HAVE_funopen2_64)
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen2_64,(void const *__cookie, __SSIZE_TYPE__ (__LIBKCALL *__readfn)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes), __SSIZE_TYPE__ (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes), __off64_t (__LIBKCALL *__seekfn)(void *__cookie, __off64_t __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)),funopen2_64,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif defined(__CRT_HAVE_funopen2)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/funopen2_64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_funopen2_64 __LIBC_LOCAL_NAME(funopen2_64)
#else /* ... */
#undef __local___localdep_funopen2_64_defined
#endif /* !... */
#endif /* !__local___localdep_funopen2_64_defined */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),__libc_malloc,(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#else /* ... */
#undef __local___localdep_malloc_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#ifndef ____funopen_holder_defined
__NAMESPACE_LOCAL_BEGIN
#define ____funopen_holder_defined
struct __funopen_holder {
	void            *__fh_cookie;                                                 /* [?..?] funopen cookie */
	int   (__LIBKCALL *__fh_readfn)(void *__cookie, char *__buf, int __num_bytes);        /* [0..1] funopen readfn */
	int   (__LIBKCALL *__fh_writefn)(void *__cookie, char const *__buf, int __num_bytes); /* [0..1] funopen writefn */
	__off_t (__LIBKCALL *__fh_seekfn)(void *__cookie, __off_t __off, int __whence);           /* [0..1] funopen seekfn */
	int   (__LIBKCALL *__fh_closefn)(void *__cookie);                                 /* [0..1] funopen closefn */
};
__NAMESPACE_LOCAL_END
#endif /* !____funopen_holder_defined */
#ifndef ____funopen2_holder_defined
#define ____funopen2_holder_defined
struct __funopen2_holder {
	void              *__f2h_cookie;                                                    /* [0..1] funopen2 readfn */
	__SSIZE_TYPE__ (__LIBKCALL *__f2h_readfn)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes);        /* [0..1] funopen2 readfn */
	__SSIZE_TYPE__ (__LIBKCALL *__f2h_writefn)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes); /* [0..1] funopen2 writefn */
	__off_t   (__LIBKCALL *__f2h_seekfn)(void *__cookie, __off_t __off, int __whence);              /* [0..1] funopen2 seekfn */
	int     (__LIBKCALL *__f2h_closefn)(void *__cookie);                                    /* [0..1] funopen2 closefn */
	int     (__LIBKCALL *__f2h_flushfn)(void *__cookie);                                    /* [0..1] funopen2 flushfn */
};
#endif /* !____funopen2_holder_defined */
#ifndef __funopen_to_funopen64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen64_seekfn_defined
__LOCAL_LIBC(__funopen_to_funopen64_seekfn) __off64_t
(__LIBKCALL __funopen_to_funopen64_seekfn)(void *__cookie, __off64_t __off, int __whence) {
	struct __funopen_holder *__holder;
	__holder = (struct __funopen_holder *)__cookie;
	return (*__holder->__fh_seekfn)(__holder->__fh_cookie, (__off_t)__off, __whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen64_seekfn_defined */
#ifndef __funopen_to_funopen2_closefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_closefn_defined
__LOCAL_LIBC(__funopen_to_funopen2_closefn) int
(__LIBKCALL __funopen_to_funopen2_closefn)(void *__cookie) {
	int __result = 0;
	struct __funopen_holder *__holder;
	__holder = (struct __funopen_holder *)__cookie;
	if (__holder->__fh_closefn != __NULLPTR)
		__result = (*__holder->__fh_closefn)(__holder->__fh_cookie);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_closefn_defined */
#ifndef __funopen2_to_funopen2_64_flushfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen2_to_funopen2_64_flushfn_defined
__LOCAL_LIBC(__funopen2_to_funopen2_64_flushfn) int
(__LIBKCALL __funopen2_to_funopen2_64_flushfn)(void *__cookie) {
	struct __funopen2_holder *__holder;
	__holder = (struct __funopen2_holder *)__cookie;
	return (*__holder->__f2h_flushfn)(__holder->__f2h_cookie);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen2_to_funopen2_64_flushfn_defined */
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#ifndef __funopen_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_readfn_defined
__LOCAL_LIBC(__funopen_to_funopen2_readfn) __SSIZE_TYPE__
(__LIBKCALL __funopen_to_funopen2_readfn)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes) {
	struct __funopen_holder *__holder;
	__holder = (struct __funopen_holder *)__cookie;
	return (__SSIZE_TYPE__)(*__holder->__fh_readfn)(__holder->__fh_cookie, (char *)__buf,
	                                     (int)(unsigned int)__num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_readfn_defined */

#ifndef __funopen_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_writefn_defined
__LOCAL_LIBC(__funopen_to_funopen2_writefn) __SSIZE_TYPE__
(__LIBKCALL __funopen_to_funopen2_writefn)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes) {
	struct __funopen_holder *__holder;
	__holder = (struct __funopen_holder *)__cookie;
	return (__SSIZE_TYPE__)(*__holder->__fh_writefn)(__holder->__fh_cookie, (char const *)__buf,
	                                      (int)(unsigned int)__num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_writefn_defined */

#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
#ifndef __funopen2_to_funopen2_64_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen2_to_funopen2_64_readfn_defined
__LOCAL_LIBC(__funopen2_to_funopen2_64_readfn) __SSIZE_TYPE__
(__LIBKCALL __funopen2_to_funopen2_64_readfn)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes) {
	struct __funopen2_holder *__holder;
	__holder = (struct __funopen2_holder *)__cookie;
	return (*__holder->__f2h_readfn)(__holder->__f2h_cookie, __buf, __num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen2_to_funopen2_64_readfn_defined */

#ifndef __funopen2_to_funopen2_64_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen2_to_funopen2_64_writefn_defined
__LOCAL_LIBC(__funopen2_to_funopen2_64_writefn) __SSIZE_TYPE__
(__LIBKCALL __funopen2_to_funopen2_64_writefn)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes) {
	struct __funopen2_holder *__holder;
	__holder = (struct __funopen2_holder *)__cookie;
	return (*__holder->__f2h_writefn)(__holder->__f2h_cookie, __buf, __num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen2_to_funopen2_64_writefn_defined */

#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(funopen2) __ATTR_WUNUSED __FILE *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(funopen2))(void const *__cookie, __SSIZE_TYPE__ (__LIBKCALL *__readfn)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes), __SSIZE_TYPE__ (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes), __off_t (__LIBKCALL *__seekfn)(void *__cookie, __off_t __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)) {
	__FILE *__result;
	struct __NAMESPACE_LOCAL_SYM __funopen2_holder *__holder;
	if (!__seekfn)
		return (__NAMESPACE_LOCAL_SYM __localdep_funopen2_64)(__cookie, __readfn, __writefn, __NULLPTR, __flushfn, __closefn);
	__holder = (struct __NAMESPACE_LOCAL_SYM __funopen2_holder *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(sizeof(struct __NAMESPACE_LOCAL_SYM __funopen2_holder));
	if __unlikely(!__holder)
		return __NULLPTR;
	__holder->__f2h_cookie  = (void *)__cookie;
	__holder->__f2h_readfn  = __readfn;
	__holder->__f2h_writefn = __writefn;
	__holder->__f2h_seekfn  = __seekfn;
	__holder->__f2h_flushfn = __flushfn;
	__holder->__f2h_closefn = __closefn;
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
	__result = (__NAMESPACE_LOCAL_SYM __localdep_funopen2_64)(/* cookie:  */ __holder,
	                     /* readfn:  */ __readfn ? (__SSIZE_TYPE__ (__LIBKCALL *)(void *, void *, __SIZE_TYPE__))&__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_readfn : __NULLPTR,
	                     /* writefn: */ __writefn ? (__SSIZE_TYPE__ (__LIBKCALL *)(void *, void const *, __SIZE_TYPE__))&__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_writefn : __NULLPTR,
	                     /* seekfn:  */ __seekfn ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen64_seekfn : __NULLPTR,
	                     /* flushfn: */ __flushfn ? &__NAMESPACE_LOCAL_SYM __funopen2_to_funopen2_64_flushfn : __NULLPTR,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_closefn);
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_funopen2_64)(/* cookie:  */ __holder,
	                     /* readfn:  */ __readfn ? &__NAMESPACE_LOCAL_SYM __funopen2_to_funopen2_64_readfn : __NULLPTR,
	                     /* writefn: */ __writefn ? &__NAMESPACE_LOCAL_SYM __funopen2_to_funopen2_64_writefn : __NULLPTR,
	                     /* seekfn:  */ __seekfn ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen64_seekfn : __NULLPTR,
	                     /* flushfn: */ __flushfn ? &__NAMESPACE_LOCAL_SYM __funopen2_to_funopen2_64_flushfn : __NULLPTR,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_closefn);
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	if __unlikely(!__result)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_funopen2_defined
#define __local___localdep_funopen2_defined
#define __localdep_funopen2 __LIBC_LOCAL_NAME(funopen2)
#endif /* !__local___localdep_funopen2_defined */
#else /* (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && ((__CRT_HAVE_funopen2 && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2) */
#undef __local_funopen2_defined
#endif /* (!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2) */
#endif /* !__local_funopen2_defined */
