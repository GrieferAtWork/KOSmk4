/* HASH CRC-32:0x365ba0f3 */
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
#ifndef __local_funopen2_64_defined
#define __local_funopen2_64_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2)
#ifndef ____funopen2_types_defined
#define ____funopen2_types_defined 1
typedef __ssize_t (__LIBKCALL *__funopen2_readfn_t)(void *__cookie, void *__buf, __size_t __num_bytes);
typedef __ssize_t (__LIBKCALL *__funopen2_writefn_t)(void *__cookie, void const *__buf, __size_t __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen2_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen2_flushfn_t)(void *__cookie);
typedef int (__LIBKCALL *__funopen2_closefn_t)(void *__cookie);
#endif /* !____funopen2_types_defined */
#ifndef ____funopen2_64_types_defined
#define ____funopen2_64_types_defined 1
typedef __off64_t (__LIBKCALL *__funopen2_64_seekfn_t)(void *__cookie, __off64_t __off, int __whence);
#endif /* !____funopen2_64_types_defined */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined 1
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_funopen2_32_defined
#define __local___localdep_funopen2_32_defined 1
__NAMESPACE_LOCAL_END
#ifndef ____funopen2_32_types_defined
#define ____funopen2_32_types_defined 1
typedef __off32_t (__LIBKCALL *__funopen2_32_seekfn_t)(void *__cookie, __off32_t __off, int __whence);
#endif /* !____funopen2_32_types_defined */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen2_32,(void const *__cookie, __funopen2_readfn_t __readfn, __funopen2_writefn_t __writefn, __funopen2_seekfn_t __seekfn, __funopen2_flushfn_t __flushfn, __funopen2_closefn_t __closefn),funopen2,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#endif /* !__local___localdep_funopen2_32_defined */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined 1
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
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
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
#define ____funopen_holder_defined 1
struct __funopen_holder {
	void               *__fh_cookie;  /* [0..1] funopen readfn */
	__funopen_readfn_t  __fh_readfn;  /* [0..1] funopen readfn */
	__funopen_writefn_t __fh_writefn; /* [0..1] funopen writefn */
	__funopen_seekfn_t  __fh_seekfn;  /* [0..1] funopen seekfn */
	__funopen_closefn_t __fh_closefn; /* [0..1] funopen closefn */
};
__NAMESPACE_LOCAL_END
#endif /* !____funopen_holder_defined */
#ifndef ____funopen2_holder_defined
#define ____funopen2_holder_defined 1
struct __funopen2_holder {
	void                *__f2h_cookie;  /* [0..1] funopen2 readfn */
	__funopen2_readfn_t  __f2h_readfn;  /* [0..1] funopen2 readfn */
	__funopen2_writefn_t __f2h_writefn; /* [0..1] funopen2 writefn */
	__funopen2_seekfn_t  __f2h_seekfn;  /* [0..1] funopen2 seekfn */
	__funopen2_closefn_t __f2h_closefn; /* [0..1] funopen2 closefn */
	__funopen2_flushfn_t __f2h_flushfn; /* [0..1] funopen2 flushfn */
};
#endif /* !____funopen2_holder_defined */
#ifndef ____funopen2_64_holder_defined
#define ____funopen2_64_holder_defined 1
struct __funopen2_64_holder {
	void                  *__f2h64_cookie;  /* [0..1] funopen2 readfn */
	__funopen2_readfn_t    __f2h64_readfn;  /* [0..1] funopen2 readfn */
	__funopen2_writefn_t   __f2h64_writefn; /* [0..1] funopen2 writefn */
	__funopen2_64_seekfn_t __f2h64_seekfn;  /* [0..1] funopen2 seekfn */
	__funopen2_closefn_t   __f2h64_closefn; /* [0..1] funopen2 closefn */
	__funopen2_flushfn_t   __f2h64_flushfn; /* [0..1] funopen2 flushfn */
};
#endif /* !____funopen2_64_holder_defined */
#ifndef __funopen2_64_to_funopen2_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen2_64_to_funopen2_seekfn_defined 1
__LOCAL_LIBC(__funopen2_64_to_funopen2_seekfn) __off32_t
(__LIBKCALL __funopen2_64_to_funopen2_seekfn)(void *__cookie, __off32_t __off, int __whence) {
	struct __funopen2_64_holder *__holder;
	__holder = (struct __funopen2_64_holder *)__cookie;
	return (__off32_t)(*__holder->__f2h64_seekfn)(__holder->__f2h64_cookie, __off, __whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen2_64_to_funopen2_seekfn_defined */
#ifndef __funopen2_to_funopen2_64_flushfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen2_to_funopen2_64_flushfn_defined 1
__LOCAL_LIBC(__funopen2_to_funopen2_64_flushfn) int
(__LIBKCALL __funopen2_to_funopen2_64_flushfn)(void *__cookie) {
	struct __funopen2_holder *__holder;
	__holder = (struct __funopen2_holder *)__cookie;
	return (*__holder->__f2h_flushfn)(__holder->__f2h_cookie);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen2_to_funopen2_64_flushfn_defined */
#ifndef __funopen_to_funopen2_closefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_closefn_defined 1
__LOCAL_LIBC(__funopen_to_funopen2_closefn) int
(__LIBKCALL __funopen_to_funopen2_closefn)(void *__cookie) {
	int __result = 0;
	struct __funopen_holder *__holder;
	__holder = (struct __funopen_holder *)__cookie;
	if (__holder->__fh_closefn != __NULLPTR)
		__result = (*__holder->__fh_closefn)(__holder->__fh_cookie);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_closefn_defined */
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#ifndef __funopen_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_readfn_defined 1
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
#define __funopen_to_funopen2_writefn_defined 1
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
#define __funopen2_to_funopen2_64_readfn_defined 1
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
#define __funopen2_to_funopen2_64_writefn_defined 1
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
__LOCAL_LIBC(funopen2_64) __ATTR_WUNUSED __FILE *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(funopen2_64))(void const *__cookie, __funopen2_readfn_t __readfn, __funopen2_writefn_t __writefn, __funopen2_64_seekfn_t __seekfn, __funopen2_flushfn_t __flushfn, __funopen2_closefn_t __closefn) {
	__FILE *__result;
	struct __NAMESPACE_LOCAL_SYM __funopen2_64_holder *__holder;
	if (!__seekfn)
		return __localdep_funopen2_32(__cookie, __readfn, __writefn, __NULLPTR, __flushfn, __closefn);
	__holder = (struct __NAMESPACE_LOCAL_SYM __funopen2_64_holder *)__localdep_malloc(sizeof(struct __NAMESPACE_LOCAL_SYM __funopen2_64_holder));
	if __unlikely(!__holder)
		return __NULLPTR;
	__holder->__f2h64_cookie  = __cookie;
	__holder->__f2h64_readfn  = __readfn;
	__holder->__f2h64_writefn = __writefn;
	__holder->__f2h64_seekfn  = __seekfn;
	__holder->__f2h64_closefn = __closefn;
	__holder->__f2h64_flushfn = __flushfn;
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
	__result = __localdep_funopen2_32(/* cookie:  */ __holder,
	                     /* readfn:  */ __readfn  ? (__funopen2_readfn_t)&__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_readfn  : __NULLPTR,
	                     /* writefn: */ __writefn ? (__funopen2_writefn_t)&__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_writefn : __NULLPTR,
	                     /* seekfn:  */ __seekfn  ? &__NAMESPACE_LOCAL_SYM __funopen2_64_to_funopen2_seekfn  : __NULLPTR,
	                     /* flushfn: */ __flushfn ? &__NAMESPACE_LOCAL_SYM __funopen2_to_funopen2_64_flushfn : __NULLPTR,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_closefn);
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
	__result = __localdep_funopen2_32(/* cookie:  */ __holder,
	                     /* readfn:  */ __readfn  ? &__NAMESPACE_LOCAL_SYM __funopen2_to_funopen2_64_readfn  : __NULLPTR,
	                     /* writefn: */ __writefn ? &__NAMESPACE_LOCAL_SYM __funopen2_to_funopen2_64_writefn : __NULLPTR,
	                     /* seekfn:  */ __seekfn  ? &__NAMESPACE_LOCAL_SYM __funopen2_64_to_funopen2_seekfn  : __NULLPTR,
	                     /* flushfn: */ __flushfn ? &__NAMESPACE_LOCAL_SYM __funopen2_to_funopen2_64_flushfn : __NULLPTR,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_closefn);
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	if __unlikely(!__result)
		__localdep_free(__holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_funopen2_64_defined
#define __local___localdep_funopen2_64_defined 1
#define __localdep_funopen2_64 __LIBC_LOCAL_NAME(funopen2_64)
#endif /* !__local___localdep_funopen2_64_defined */
#else /* (__CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && __CRT_HAVE_funopen2 */
#undef __local_funopen2_64_defined
#endif /* (!__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign) || !__CRT_HAVE_funopen2 */
#endif /* !__local_funopen2_64_defined */
