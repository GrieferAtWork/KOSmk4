/* HASH CRC-32:0xfffddd69 */
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
#ifndef __local_fopencookie_defined
#define __local_fopencookie_defined 1
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#include <hybrid/typecore.h>
#if (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen64) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2) || defined(__CRT_HAVE_funopen))
#include <libio.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: free from stdlib */
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
/* Dependency: funopen from stdio */
#ifndef __local___localdep_funopen_defined
#define __local___localdep_funopen_defined 1
#if defined(__CRT_HAVE_funopen) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
__NAMESPACE_LOCAL_END
#ifndef ____funopen_types_defined
#define ____funopen_types_defined 1
typedef int (__LIBKCALL *__funopen_readfn_t)(void *__cookie, char *__buf, int __num_bytes);
typedef int (__LIBKCALL *__funopen_writefn_t)(void *__cookie, char const *__buf, int __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen_closefn_t)(void *__cookie);
#endif /* !____funopen_types_defined */
__NAMESPACE_LOCAL_BEGIN
/* >> funopen(3), funopen64(3) */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen,(void const *__cookie, __funopen_readfn_t __readfn, __funopen_writefn_t __writefn, __funopen_seekfn_t __seekfn, __funopen_closefn_t __closefn),funopen,(__cookie,__readfn,__writefn,__seekfn,__closefn))
#elif defined(__CRT_HAVE_funopen64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#ifndef ____funopen_types_defined
#define ____funopen_types_defined 1
typedef int (__LIBKCALL *__funopen_readfn_t)(void *__cookie, char *__buf, int __num_bytes);
typedef int (__LIBKCALL *__funopen_writefn_t)(void *__cookie, char const *__buf, int __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen_closefn_t)(void *__cookie);
#endif /* !____funopen_types_defined */
__NAMESPACE_LOCAL_BEGIN
/* >> funopen(3), funopen64(3) */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen,(void const *__cookie, __funopen_readfn_t __readfn, __funopen_writefn_t __writefn, __funopen_seekfn_t __seekfn, __funopen_closefn_t __closefn),funopen64,(__cookie,__readfn,__writefn,__seekfn,__closefn))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/funopen.h>
__NAMESPACE_LOCAL_BEGIN
/* >> funopen(3), funopen64(3) */
#define __localdep_funopen __LIBC_LOCAL_NAME(funopen)
#endif /* !... */
#endif /* !__local___localdep_funopen_defined */
/* Dependency: funopen2 from stdio */
#ifndef __local___localdep_funopen2_defined
#define __local___localdep_funopen2_defined 1
#if defined(__CRT_HAVE_funopen2) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
__NAMESPACE_LOCAL_END
#ifndef ____funopen2_types_defined
#define ____funopen2_types_defined 1
typedef __ssize_t (__LIBKCALL *__funopen2_readfn_t)(void *__cookie, void *__buf, __size_t __num_bytes);
typedef __ssize_t (__LIBKCALL *__funopen2_writefn_t)(void *__cookie, void const *__buf, __size_t __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen2_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen2_flushfn_t)(void *__cookie);
typedef int (__LIBKCALL *__funopen2_closefn_t)(void *__cookie);
#endif /* !____funopen2_types_defined */
__NAMESPACE_LOCAL_BEGIN
/* >> funopen2(3), funopen2_64(3) */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen2,(void const *__cookie, __funopen2_readfn_t __readfn, __funopen2_writefn_t __writefn, __funopen2_seekfn_t __seekfn, __funopen2_flushfn_t __flushfn, __funopen2_closefn_t __closefn),funopen2,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif defined(__CRT_HAVE_funopen2_64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#ifndef ____funopen2_types_defined
#define ____funopen2_types_defined 1
typedef __ssize_t (__LIBKCALL *__funopen2_readfn_t)(void *__cookie, void *__buf, __size_t __num_bytes);
typedef __ssize_t (__LIBKCALL *__funopen2_writefn_t)(void *__cookie, void const *__buf, __size_t __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen2_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen2_flushfn_t)(void *__cookie);
typedef int (__LIBKCALL *__funopen2_closefn_t)(void *__cookie);
#endif /* !____funopen2_types_defined */
__NAMESPACE_LOCAL_BEGIN
/* >> funopen2(3), funopen2_64(3) */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen2,(void const *__cookie, __funopen2_readfn_t __readfn, __funopen2_writefn_t __writefn, __funopen2_seekfn_t __seekfn, __funopen2_flushfn_t __flushfn, __funopen2_closefn_t __closefn),funopen2_64,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/funopen2.h>
__NAMESPACE_LOCAL_BEGIN
/* >> funopen2(3), funopen2_64(3) */
#define __localdep_funopen2 __LIBC_LOCAL_NAME(funopen2)
#else /* ... */
#undef __local___localdep_funopen2_defined
#endif /* !... */
#endif /* !__local___localdep_funopen2_defined */
/* Dependency: funopen2_64 from stdio */
#ifndef __local___localdep_funopen2_64_defined
#define __local___localdep_funopen2_64_defined 1
#if defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__NAMESPACE_LOCAL_END
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
/* >> funopen2(3), funopen2_64(3) */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen2_64,(void const *__cookie, __funopen2_readfn_t __readfn, __funopen2_writefn_t __writefn, __funopen2_64_seekfn_t __seekfn, __funopen2_flushfn_t __flushfn, __funopen2_closefn_t __closefn),funopen2,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif defined(__CRT_HAVE_funopen2_64)
__NAMESPACE_LOCAL_END
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
/* >> funopen2(3), funopen2_64(3) */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen2_64,(void const *__cookie, __funopen2_readfn_t __readfn, __funopen2_writefn_t __writefn, __funopen2_64_seekfn_t __seekfn, __funopen2_flushfn_t __flushfn, __funopen2_closefn_t __closefn),funopen2_64,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif defined(__CRT_HAVE_funopen2)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/funopen2_64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> funopen2(3), funopen2_64(3) */
#define __localdep_funopen2_64 __LIBC_LOCAL_NAME(funopen2_64)
#else /* ... */
#undef __local___localdep_funopen2_64_defined
#endif /* !... */
#endif /* !__local___localdep_funopen2_64_defined */
/* Dependency: funopen64 from stdio */
#ifndef __local___localdep_funopen64_defined
#define __local___localdep_funopen64_defined 1
#if defined(__CRT_HAVE_funopen) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__NAMESPACE_LOCAL_END
#ifndef ____funopen_types_defined
#define ____funopen_types_defined 1
typedef int (__LIBKCALL *__funopen_readfn_t)(void *__cookie, char *__buf, int __num_bytes);
typedef int (__LIBKCALL *__funopen_writefn_t)(void *__cookie, char const *__buf, int __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen_closefn_t)(void *__cookie);
#endif /* !____funopen_types_defined */
#ifndef ____funopen64_types_defined
#define ____funopen64_types_defined 1
typedef __off64_t (__LIBKCALL *__funopen64_seekfn_t)(void *__cookie, __off64_t __off, int __whence);
#endif /* !____funopen64_types_defined */
__NAMESPACE_LOCAL_BEGIN
/* >> funopen(3), funopen64(3) */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen64,(void const *__cookie, __funopen_readfn_t __readfn, __funopen_writefn_t __writefn, __funopen64_seekfn_t __seekfn, __funopen_closefn_t __closefn),funopen,(__cookie,__readfn,__writefn,__seekfn,__closefn))
#elif defined(__CRT_HAVE_funopen64)
__NAMESPACE_LOCAL_END
#ifndef ____funopen_types_defined
#define ____funopen_types_defined 1
typedef int (__LIBKCALL *__funopen_readfn_t)(void *__cookie, char *__buf, int __num_bytes);
typedef int (__LIBKCALL *__funopen_writefn_t)(void *__cookie, char const *__buf, int __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen_closefn_t)(void *__cookie);
#endif /* !____funopen_types_defined */
#ifndef ____funopen64_types_defined
#define ____funopen64_types_defined 1
typedef __off64_t (__LIBKCALL *__funopen64_seekfn_t)(void *__cookie, __off64_t __off, int __whence);
#endif /* !____funopen64_types_defined */
__NAMESPACE_LOCAL_BEGIN
/* >> funopen(3), funopen64(3) */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen64,(void const *__cookie, __funopen_readfn_t __readfn, __funopen_writefn_t __writefn, __funopen64_seekfn_t __seekfn, __funopen_closefn_t __closefn),funopen64,(__cookie,__readfn,__writefn,__seekfn,__closefn))
#elif defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2) || defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/funopen64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> funopen(3), funopen64(3) */
#define __localdep_funopen64 __LIBC_LOCAL_NAME(funopen64)
#else /* ... */
#undef __local___localdep_funopen64_defined
#endif /* !... */
#endif /* !__local___localdep_funopen64_defined */
/* Dependency: malloc from stdlib */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined 1
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
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
#ifndef ____fopencookie_holder_defined
__NAMESPACE_LOCAL_BEGIN
#define ____fopencookie_holder_defined 1
struct __fopencookie_holder {
	void                     *__foch_cookie; /* User-defined `magic_cookie' */
	_IO_cookie_io_functions_t __foch_funcs;  /* Cookie functions */
};
__NAMESPACE_LOCAL_END
#endif /* !____fopencookie_holder_defined */
#ifndef __fopencookie_to_funopen_closefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_closefn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen_closefn) int
(__LIBKCALL __fopencookie_to_funopen_closefn)(void *__cookie) {
	int __result = 0;
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	if (__holder->__foch_funcs.close != __NULLPTR)
		__result = (*__holder->__foch_funcs.close)(__holder->__foch_cookie);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_closefn_defined */

#if !defined(__BUILDING_LIBC) && defined(__CRT_HAVE_funopen64) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#ifndef __fopencookie_to_funopen_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_readfn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen_readfn) int
(__LIBKCALL __fopencookie_to_funopen_readfn)(void *__cookie, char *__buf, int __num_bytes) {
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	return (int)(*__holder->__foch_funcs.read)(__holder->__foch_cookie, __buf, (__SIZE_TYPE__)(unsigned int)__num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_readfn_defined */

#ifndef __fopencookie_to_funopen_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_writefn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen_writefn) int
(__LIBKCALL __fopencookie_to_funopen_writefn)(void *__cookie, char const *__buf, int __num_bytes) {
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	return (int)(*__holder->__foch_funcs.write)(__holder->__foch_cookie, __buf, (__SIZE_TYPE__)(unsigned int)__num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_writefn_defined */

#ifndef __fopencookie_to_funopen64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen64_seekfn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen64_seekfn) __off64_t
(__LIBKCALL __fopencookie_to_funopen64_seekfn)(void *__cookie, __off64_t __off, int __whence) {
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
#ifdef __USE_KOS_ALTERATIONS
	if ((*__holder->__foch_funcs.seek)(__holder->__foch_cookie, (__pos64_t *)&__off, __whence) != 0)
		return -1;
#else /* __USE_KOS_ALTERATIONS */
	if ((*__holder->__foch_funcs.seek)(__holder->__foch_cookie, &__off, __whence) != 0)
		return -1;
#endif /* !__USE_KOS_ALTERATIONS */
	return __off;
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen64_seekfn_defined */

#elif !defined(__BUILDING_LIBC) && defined(__CRT_HAVE_funopen) && !defined(__CRT_HAVE_funopen2_64) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#ifndef __fopencookie_to_funopen_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_readfn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen_readfn) int
(__LIBKCALL __fopencookie_to_funopen_readfn)(void *__cookie, char *__buf, int __num_bytes) {
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	return (int)(*__holder->__foch_funcs.read)(__holder->__foch_cookie, __buf, (__SIZE_TYPE__)(unsigned int)__num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_readfn_defined */

#ifndef __fopencookie_to_funopen_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_writefn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen_writefn) int
(__LIBKCALL __fopencookie_to_funopen_writefn)(void *__cookie, char const *__buf, int __num_bytes) {
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	return (int)(*__holder->__foch_funcs.write)(__holder->__foch_cookie, __buf, (__SIZE_TYPE__)(unsigned int)__num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_writefn_defined */

#ifndef __fopencookie_to_funopen_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_seekfn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen_seekfn) __FS_TYPE(off)
(__LIBKCALL __fopencookie_to_funopen_seekfn)(void *__cookie, __FS_TYPE(off) __off, int __whence) {
#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
#ifdef __USE_KOS_ALTERATIONS
	if ((*__holder->__foch_funcs.seek)(__holder->__foch_cookie, (__pos64_t *)&__off, __whence) != 0)
		return -1;
#else /* __USE_KOS_ALTERATIONS */
	if ((*__holder->__foch_funcs.seek)(__holder->__foch_cookie, (__off64_t *)&__off, __whence) != 0)
		return -1;
#endif /* !__USE_KOS_ALTERATIONS */
	return __off;
#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
#ifdef __USE_KOS_ALTERATIONS
	__pos64_t __newpos = (__pos64_t)__off;
#else /* __USE_KOS_ALTERATIONS */
	__off64_t __newpos = __off;
#endif /* !__USE_KOS_ALTERATIONS */
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	if ((*__holder->__foch_funcs.seek)(__holder->__foch_cookie, &__newpos, __whence) != 0)
		return -1;
	return (__FS_TYPE(off))__newpos;
#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_seekfn_defined */

#elif (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2))
#ifndef __fopencookie_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen2_readfn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen2_readfn) __SSIZE_TYPE__
(__LIBKCALL __fopencookie_to_funopen2_readfn)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes) {
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	return (*__holder->__foch_funcs.read)(__holder->__foch_cookie, (char *)__buf, __num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen2_readfn_defined */

#ifndef __fopencookie_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen2_writefn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen2_writefn) __SSIZE_TYPE__
(__LIBKCALL __fopencookie_to_funopen2_writefn)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes) {
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	return (*__holder->__foch_funcs.write)(__holder->__foch_cookie, (char const *)__buf, __num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen2_writefn_defined */

#ifndef __fopencookie_to_funopen64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen64_seekfn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen64_seekfn) __off64_t
(__LIBKCALL __fopencookie_to_funopen64_seekfn)(void *__cookie, __off64_t __off, int __whence) {
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
#ifdef __USE_KOS_ALTERATIONS
	if ((*__holder->__foch_funcs.seek)(__holder->__foch_cookie, (__pos64_t *)&__off, __whence) != 0)
		return -1;
#else /* __USE_KOS_ALTERATIONS */
	if ((*__holder->__foch_funcs.seek)(__holder->__foch_cookie, &__off, __whence) != 0)
		return -1;
#endif /* !__USE_KOS_ALTERATIONS */
	return __off;
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen64_seekfn_defined */

#elif defined(__CRT_HAVE_funopen2) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
#ifndef __fopencookie_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen2_readfn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen2_readfn) __SSIZE_TYPE__
(__LIBKCALL __fopencookie_to_funopen2_readfn)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes) {
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	return (*__holder->__foch_funcs.read)(__holder->__foch_cookie, (char *)__buf, __num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen2_readfn_defined */

#ifndef __fopencookie_to_funopen2_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen2_writefn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen2_writefn) __SSIZE_TYPE__
(__LIBKCALL __fopencookie_to_funopen2_writefn)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes) {
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	return (*__holder->__foch_funcs.write)(__holder->__foch_cookie, (char const *)__buf, __num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen2_writefn_defined */

#ifndef __fopencookie_to_funopen_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_seekfn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen_seekfn) __FS_TYPE(off)
(__LIBKCALL __fopencookie_to_funopen_seekfn)(void *__cookie, __FS_TYPE(off) __off, int __whence) {
#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
#ifdef __USE_KOS_ALTERATIONS
	if ((*__holder->__foch_funcs.seek)(__holder->__foch_cookie, (__pos64_t *)&__off, __whence) != 0)
		return -1;
#else /* __USE_KOS_ALTERATIONS */
	if ((*__holder->__foch_funcs.seek)(__holder->__foch_cookie, (__off64_t *)&__off, __whence) != 0)
		return -1;
#endif /* !__USE_KOS_ALTERATIONS */
	return __off;
#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
#ifdef __USE_KOS_ALTERATIONS
	__pos64_t __newpos = (__pos64_t)__off;
#else /* __USE_KOS_ALTERATIONS */
	__off64_t __newpos = __off;
#endif /* !__USE_KOS_ALTERATIONS */
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	if ((*__holder->__foch_funcs.seek)(__holder->__foch_cookie, &__newpos, __whence) != 0)
		return -1;
	return (__FS_TYPE(off))__newpos;
#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_seekfn_defined */

#elif (defined(__CRT_HAVE_funopen) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_funopen2) || defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen)))
#ifndef __fopencookie_to_funopen_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_readfn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen_readfn) int
(__LIBKCALL __fopencookie_to_funopen_readfn)(void *__cookie, char *__buf, int __num_bytes) {
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	return (int)(*__holder->__foch_funcs.read)(__holder->__foch_cookie, __buf, (__SIZE_TYPE__)(unsigned int)__num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_readfn_defined */

#ifndef __fopencookie_to_funopen_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_writefn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen_writefn) int
(__LIBKCALL __fopencookie_to_funopen_writefn)(void *__cookie, char const *__buf, int __num_bytes) {
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	return (int)(*__holder->__foch_funcs.write)(__holder->__foch_cookie, __buf, (__SIZE_TYPE__)(unsigned int)__num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_writefn_defined */

#ifndef __fopencookie_to_funopen64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen64_seekfn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen64_seekfn) __off64_t
(__LIBKCALL __fopencookie_to_funopen64_seekfn)(void *__cookie, __off64_t __off, int __whence) {
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
#ifdef __USE_KOS_ALTERATIONS
	if ((*__holder->__foch_funcs.seek)(__holder->__foch_cookie, (__pos64_t *)&__off, __whence) != 0)
		return -1;
#else /* __USE_KOS_ALTERATIONS */
	if ((*__holder->__foch_funcs.seek)(__holder->__foch_cookie, &__off, __whence) != 0)
		return -1;
#endif /* !__USE_KOS_ALTERATIONS */
	return __off;
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen64_seekfn_defined */

#else /* ... */
#ifndef __fopencookie_to_funopen_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_readfn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen_readfn) int
(__LIBKCALL __fopencookie_to_funopen_readfn)(void *__cookie, char *__buf, int __num_bytes) {
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	return (int)(*__holder->__foch_funcs.read)(__holder->__foch_cookie, __buf, (__SIZE_TYPE__)(unsigned int)__num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_readfn_defined */

#ifndef __fopencookie_to_funopen_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_writefn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen_writefn) int
(__LIBKCALL __fopencookie_to_funopen_writefn)(void *__cookie, char const *__buf, int __num_bytes) {
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	return (int)(*__holder->__foch_funcs.write)(__holder->__foch_cookie, __buf, (__SIZE_TYPE__)(unsigned int)__num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_writefn_defined */

#ifndef __fopencookie_to_funopen_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_seekfn_defined 1
__LOCAL_LIBC(__fopencookie_to_funopen_seekfn) __FS_TYPE(off)
(__LIBKCALL __fopencookie_to_funopen_seekfn)(void *__cookie, __FS_TYPE(off) __off, int __whence) {
#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
#ifdef __USE_KOS_ALTERATIONS
	if ((*__holder->__foch_funcs.seek)(__holder->__foch_cookie, (__pos64_t *)&__off, __whence) != 0)
		return -1;
#else /* __USE_KOS_ALTERATIONS */
	if ((*__holder->__foch_funcs.seek)(__holder->__foch_cookie, (__off64_t *)&__off, __whence) != 0)
		return -1;
#endif /* !__USE_KOS_ALTERATIONS */
	return __off;
#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
#ifdef __USE_KOS_ALTERATIONS
	__pos64_t __newpos = (__pos64_t)__off;
#else /* __USE_KOS_ALTERATIONS */
	__off64_t __newpos = __off;
#endif /* !__USE_KOS_ALTERATIONS */
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	if ((*__holder->__foch_funcs.seek)(__holder->__foch_cookie, &__newpos, __whence) != 0)
		return -1;
	return (__FS_TYPE(off))__newpos;
#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_seekfn_defined */

#endif /* !... */
__NAMESPACE_LOCAL_BEGIN
/* >> fopencookie(3) */
__LOCAL_LIBC(fopencookie) __ATTR_WUNUSED __ATTR_NONNULL((2)) __FILE *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fopencookie))(void *__restrict __magic_cookie, char const *__restrict __modes, _IO_cookie_io_functions_t __io_funcs) {
	__FILE *__result;
	struct __NAMESPACE_LOCAL_SYM __fopencookie_holder *__holder;
	(void)__modes; /* unused... */
	__holder = (struct __NAMESPACE_LOCAL_SYM __fopencookie_holder *)__localdep_malloc(sizeof(struct __NAMESPACE_LOCAL_SYM __fopencookie_holder));
	if __unlikely(!__holder)
		return __NULLPTR;
	__holder->__foch_cookie        = __magic_cookie;
	__holder->__foch_funcs.read  = __io_funcs.read;
	__holder->__foch_funcs.write = __io_funcs.write;
	__holder->__foch_funcs.seek  = __io_funcs.seek;
	__holder->__foch_funcs.close = __io_funcs.close;
#if defined(__CRT_HAVE_funopen64) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__
	__result = __localdep_funopen64(/* cookie:  */ __holder,
	                   /* readfn:  */ __io_funcs.read ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_readfn : __NULLPTR,
	                   /* writefn: */ __io_funcs.write ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_writefn : __NULLPTR,
	                   /* seekfn:  */ __io_funcs.seek ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen64_seekfn : __NULLPTR,
	                   /* closefn: */ &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_closefn);
#elif defined(__CRT_HAVE_funopen) && !defined(__CRT_HAVE_funopen2_64) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__
	__result = __localdep_funopen(/* cookie:  */ __holder,
	                 /* readfn:  */ __io_funcs.read ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_readfn : __NULLPTR,
	                 /* writefn: */ __io_funcs.write ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_writefn : __NULLPTR,
	                 /* seekfn:  */ __io_funcs.seek ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_seekfn : __NULLPTR,
	                 /* closefn: */ __io_funcs.seek ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_closefn : __NULLPTR);
#elif (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2)
	__result = __localdep_funopen2_64(/* cookie:  */ __holder,
	                     /* readfn:  */ __io_funcs.read ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen2_readfn : __NULLPTR,
	                     /* writefn: */ __io_funcs.write ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen2_writefn : __NULLPTR,
	                     /* seekfn:  */ __io_funcs.seek ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen64_seekfn : __NULLPTR,
	                     /* flushfn: */ __NULLPTR,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_closefn);







#elif defined(__CRT_HAVE_funopen64) || defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen)
	__result = __localdep_funopen64(/* cookie:  */ __holder,
	                   /* readfn:  */ __io_funcs.read ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_readfn : __NULLPTR,
	                   /* writefn: */ __io_funcs.write ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_writefn : __NULLPTR,
	                   /* seekfn:  */ __io_funcs.seek ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen64_seekfn : __NULLPTR,
	                   /* closefn: */ &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_closefn);
#else /* ... */
	__result = __localdep_funopen(/* cookie:  */ __holder,
	                 /* readfn:  */ __io_funcs.read ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_readfn : __NULLPTR,
	                 /* writefn: */ __io_funcs.write ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_writefn : __NULLPTR,
	                 /* seekfn:  */ __io_funcs.seek ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_seekfn : __NULLPTR,
	                 /* closefn: */ &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_closefn);
#endif /* !... */
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	if __unlikely(!__result)
		__localdep_free(__holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fopencookie_defined
#define __local___localdep_fopencookie_defined 1
#define __localdep_fopencookie __LIBC_LOCAL_NAME(fopencookie)
#endif /* !__local___localdep_fopencookie_defined */
#else /* (__CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_fopencookie || __CRT_HAVE_funopen64 || __CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2 || __CRT_HAVE_funopen) */
#undef __local_fopencookie_defined
#endif /* (!__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_fopencookie && !__CRT_HAVE_funopen64 && !__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2 && !__CRT_HAVE_funopen) */
#endif /* !__local_fopencookie_defined */
