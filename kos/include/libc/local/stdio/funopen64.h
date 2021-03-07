/* HASH CRC-32:0x2a4f2d3f */
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
#ifndef __local_funopen64_defined
#define __local_funopen64_defined 1
#include <__crt.h>
#include <bits/types.h>
#if (__SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2)))) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2) || defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen)))
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
/* Dependency: crt_fopencookie from stdio */
#if !defined(__local___localdep_crt_fopencookie_defined) && defined(__CRT_HAVE_fopencookie)
#define __local___localdep_crt_fopencookie_defined 1
__NAMESPACE_LOCAL_END
#include <libio.h>
__NAMESPACE_LOCAL_BEGIN
/* >> fopencookie(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,__localdep_crt_fopencookie,(void *__restrict __magic_cookie, char const *__restrict __modes, _IO_cookie_io_functions_t __io_funcs),fopencookie,(__magic_cookie,__modes,__io_funcs))
#endif /* !__local___localdep_crt_fopencookie_defined && __CRT_HAVE_fopencookie */
/* Dependency: free from stdlib */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined 1
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ return __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
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
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/funopen2_64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> funopen2(3), funopen2_64(3) */
#define __localdep_funopen2_64 __LIBC_LOCAL_NAME(funopen2_64)
#else /* ... */
#undef __local___localdep_funopen2_64_defined
#endif /* !... */
#endif /* !__local___localdep_funopen2_64_defined */
/* Dependency: funopen32 from stdio */
#if !defined(__local___localdep_funopen32_defined) && defined(__CRT_HAVE_funopen)
#define __local___localdep_funopen32_defined 1
__NAMESPACE_LOCAL_END
#ifndef ____funopen32_types_defined
#define ____funopen32_types_defined 1
typedef __off32_t (__LIBKCALL *__funopen32_seekfn_t)(void *__cookie, __off32_t __off, int __whence);
#endif /* !____funopen32_types_defined */
__NAMESPACE_LOCAL_BEGIN
/* >> funopen(3), funopen64(3) */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen32,(void const *__cookie, __funopen_readfn_t __readfn, __funopen_writefn_t __writefn, __funopen_seekfn_t __seekfn, __funopen_closefn_t __closefn),funopen,(__cookie,__readfn,__writefn,__seekfn,__closefn))
#endif /* !__local___localdep_funopen32_defined && __CRT_HAVE_funopen */
/* Dependency: malloc from stdlib */
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
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2)))
#ifndef ____funopen2_types_defined
#define ____funopen2_types_defined 1
typedef __ssize_t (__LIBKCALL *__funopen2_readfn_t)(void *__cookie, void *__buf, __size_t __num_bytes);
typedef __ssize_t (__LIBKCALL *__funopen2_writefn_t)(void *__cookie, void const *__buf, __size_t __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen2_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen2_flushfn_t)(void *__cookie);
typedef int (__LIBKCALL *__funopen2_closefn_t)(void *__cookie);
#endif /* !____funopen2_types_defined */

#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((__CRT_HAVE_funopen2 && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen2_64 || ((__CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && __CRT_HAVE_funopen2)) */
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

#ifndef ____funopen64_holder_defined
__NAMESPACE_LOCAL_BEGIN
#define ____funopen64_holder_defined 1
struct __funopen64_holder {
	void                *__fh64_cookie;  /* [0..1] funopen readfn */
	__funopen_readfn_t   __fh64_readfn;  /* [0..1] funopen readfn */
	__funopen_writefn_t  __fh64_writefn; /* [0..1] funopen writefn */
	__funopen64_seekfn_t __fh64_seekfn;  /* [0..1] funopen seekfn */
	__funopen_closefn_t  __fh64_closefn; /* [0..1] funopen closefn */
};
__NAMESPACE_LOCAL_END
#endif /* !____funopen64_holder_defined */

#ifndef __funopen_to_funopen2_closefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_closefn_defined 1
__LOCAL_LIBC(__funopen_to_funopen2_closefn) int
(__LIBKCALL __funopen_to_funopen2_closefn)(void *__cookie) {
	struct __funopen_holder *__holder;
	__holder = (struct __funopen_holder *)__cookie;
	return (*__holder->__fh_closefn)(__holder->__fh_cookie);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_closefn_defined */

#if (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2))
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

#ifndef ____funopen2_types_defined
#define ____funopen2_types_defined 1
typedef __ssize_t (__LIBKCALL *__funopen2_readfn_t)(void *__cookie, void *__buf, __size_t __num_bytes);
typedef __ssize_t (__LIBKCALL *__funopen2_writefn_t)(void *__cookie, void const *__buf, __size_t __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen2_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen2_flushfn_t)(void *__cookie);
typedef int (__LIBKCALL *__funopen2_closefn_t)(void *__cookie);
#endif /* !____funopen2_types_defined */

#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
#ifndef __funopen_to_funopen2_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen2_seekfn_defined 1
__LOCAL_LIBC(__funopen_to_funopen2_seekfn) __FS_TYPE(off)
(__LIBKCALL __funopen_to_funopen2_seekfn)(void *__cookie, __FS_TYPE(off) __off, int __whence) {
	struct __funopen_holder *__holder;
	__holder = (struct __funopen_holder *)__cookie;
	return (*__holder->__fh_seekfn)(__holder->__fh_cookie, __off, __whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen2_seekfn_defined */

#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
#ifndef __funopen64_to_funopen2_64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen64_to_funopen2_64_seekfn_defined 1
__LOCAL_LIBC(__funopen64_to_funopen2_64_seekfn) __off64_t
(__LIBKCALL __funopen64_to_funopen2_64_seekfn)(void *__cookie, __off64_t __off, int __whence) {
	struct __funopen_holder *__holder;
	__holder = (struct __funopen_holder *)__cookie;
	return (*__holder->__fh_seekfn)(__holder->__fh_cookie, __off, __whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen64_to_funopen2_64_seekfn_defined */

#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
#elif defined(__CRT_HAVE_fopencookie)
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

#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
#ifndef __funopen_to_fopencookie_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_fopencookie_seekfn_defined 1
#ifdef __USE_KOS_ALTERATIONS
__LOCAL_LIBC(__funopen_to_fopencookie_seekfn) int
(__LIBKCALL __funopen_to_fopencookie_seekfn)(void *__cookie, __pos64_t *__pos, int __whence)
#else /* __USE_KOS_ALTERATIONS */
__LOCAL_LIBC(__funopen_to_fopencookie_seekfn) int
(__LIBKCALL __funopen_to_fopencookie_seekfn)(void *__cookie, __off64_t *__pos, int __whence)
#endif /* !__USE_KOS_ALTERATIONS */
{
	__FS_TYPE(off) __newpos;
	struct __funopen_holder *__holder;
	__holder = (struct __funopen_holder *)__cookie;
	__newpos = (*__holder->__fh_seekfn)(__holder->__fh_cookie, (__FS_TYPE(off))*__pos, __whence);
	if __unlikely(__newpos == -1)
		return -1;
#ifdef __USE_KOS_ALTERATIONS
	*__pos = (__pos64_t)(__off64_t)__newpos;
#else /* __USE_KOS_ALTERATIONS */
	*__pos = (__off64_t)__newpos;
#endif /* !__USE_KOS_ALTERATIONS */
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_fopencookie_seekfn_defined */

#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
#ifndef __funopen64_to_fopencookie_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen64_to_fopencookie_seekfn_defined 1
#ifdef __USE_KOS_ALTERATIONS
__LOCAL_LIBC(__funopen64_to_fopencookie_seekfn) int
(__LIBKCALL __funopen64_to_fopencookie_seekfn)(void *__cookie, __pos64_t *__pos, int __whence)
#else /* __USE_KOS_ALTERATIONS */
__LOCAL_LIBC(__funopen64_to_fopencookie_seekfn) int
(__LIBKCALL __funopen64_to_fopencookie_seekfn)(void *__cookie, __off64_t *__pos, int __whence)
#endif /* !__USE_KOS_ALTERATIONS */
{
	__off64_t __newpos;
	struct __funopen_holder *__holder;
	__holder = (struct __funopen_holder *)__cookie;
	__newpos = (*__holder->__fh_seekfn)(__holder->__fh_cookie, (__off64_t)*__pos, __whence);
	if __unlikely(__newpos == -1)
		return -1;
#ifdef __USE_KOS_ALTERATIONS
	*__pos = (__pos64_t)__newpos;
#else /* __USE_KOS_ALTERATIONS */
	*__pos = __newpos;
#endif /* !__USE_KOS_ALTERATIONS */
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen64_to_fopencookie_seekfn_defined */

#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
#include <libio.h>
#else /* ... */
#ifndef ____funopen64_types_defined
#define ____funopen64_types_defined 1
typedef __off64_t (__LIBKCALL *__funopen64_seekfn_t)(void *__cookie, __off64_t __off, int __whence);
#endif /* !____funopen64_types_defined */

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
#ifndef __funopen_to_funopen64_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen64_readfn_defined 1
__LOCAL_LIBC(__funopen_to_funopen64_readfn) int
(__LIBKCALL __funopen_to_funopen64_readfn)(void *__cookie, char *__buf, int __num_bytes) {
	struct __funopen_holder *__holder;
	__holder = (struct __funopen_holder *)__cookie;
	return (*__holder->__fh_readfn)(__holder->__fh_cookie, __buf, __num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen64_readfn_defined */

#ifndef __funopen_to_funopen64_writefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen64_writefn_defined 1
__LOCAL_LIBC(__funopen_to_funopen64_writefn) int
(__LIBKCALL __funopen_to_funopen64_writefn)(void *__cookie, char const *__buf, int __num_bytes) {
	struct __funopen_holder *__holder;
	__holder = (struct __funopen_holder *)__cookie;
	return (*__holder->__fh_writefn)(__holder->__fh_cookie, __buf, __num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen64_writefn_defined */

#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
#ifndef __funopen_to_funopen64_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen_to_funopen64_seekfn_defined 1
__LOCAL_LIBC(__funopen_to_funopen64_seekfn) __off64_t
(__LIBKCALL __funopen_to_funopen64_seekfn)(void *__cookie, __off64_t __off, int __whence) {
	struct __funopen_holder *__holder;
	__holder = (struct __funopen_holder *)__cookie;
	return (*__holder->__fh_seekfn)(__holder->__fh_cookie, (__FS_TYPE(off))__off, __whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen_to_funopen64_seekfn_defined */

#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
#ifndef __funopen64_to_funopen_seekfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __funopen64_to_funopen_seekfn_defined 1
__LOCAL_LIBC(__funopen64_to_funopen_seekfn) __FS_TYPE(off)
(__LIBKCALL __funopen64_to_funopen_seekfn)(void *__cookie, __FS_TYPE(off) __off, int __whence) {
	struct __funopen_holder *__holder;
	__holder = (struct __funopen_holder *)__cookie;
	return (__FS_TYPE(off))(*__holder->__fh_seekfn)(__holder->__fh_cookie, (__off64_t)__off, __whence);
}
__NAMESPACE_LOCAL_END
#endif /* !__funopen64_to_funopen_seekfn_defined */

#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
#endif /* !... */
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ || ((!__CRT_HAVE_funopen2 || __SIZEOF_OFF64_T__ != __SIZEOF_OFF32_T__) && !__CRT_HAVE_funopen2_64 && ((!__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign) || !__CRT_HAVE_funopen2)) */
__NAMESPACE_LOCAL_BEGIN
/* >> funopen(3), funopen64(3) */
__LOCAL_LIBC(funopen64) __ATTR_WUNUSED __FILE *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(funopen64))(void const *__cookie, __funopen_readfn_t __readfn, __funopen_writefn_t __writefn, __funopen64_seekfn_t __seekfn, __funopen_closefn_t __closefn) {
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2)))
	return __localdep_funopen2_64(__cookie,
	                   (__funopen2_readfn_t)__readfn,
	                   (__funopen2_writefn_t)__writefn,
	                   __seekfn, __NULLPTR, __closefn);
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((__CRT_HAVE_funopen2 && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen2_64 || ((__CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && __CRT_HAVE_funopen2)) */
	__FILE *__result;
	struct __NAMESPACE_LOCAL_SYM __funopen64_holder *__holder;

#ifdef __CRT_HAVE_funopen
	if (!__seekfn)
		return __localdep_funopen32(__cookie, __readfn, __writefn, __NULLPTR, __closefn);
#endif /* __CRT_HAVE_funopen */

	__holder = (struct __NAMESPACE_LOCAL_SYM __funopen64_holder *)__localdep_malloc(sizeof(struct __NAMESPACE_LOCAL_SYM __funopen64_holder));
	if __unlikely(!__holder)
		return __NULLPTR;
	__holder->__fh64_cookie  = (void *)__cookie;
	__holder->__fh64_readfn  = __readfn;
	__holder->__fh64_writefn = __writefn;
	__holder->__fh64_seekfn  = __seekfn;
	__holder->__fh64_closefn = __closefn;
#if (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2))
#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
	__result = __localdep_funopen2_64(/* cookie:  */ __holder,
	                     /* readfn:  */ __readfn  ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_readfn  : __NULLPTR,
	                     /* writefn: */ __writefn ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_writefn : __NULLPTR,
	                     /* seekfn:  */ __seekfn  ? (__funopen2_64_seekfn_t)&__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_seekfn  : __NULLPTR,
	                     /* flushfn: */ __NULLPTR,
	                     /* closefn: */ __closefn ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_closefn : __NULLPTR);
#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
	__result = __localdep_funopen2_64(/* cookie:  */ __holder,
	                     /* readfn:  */ __readfn  ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_readfn  : __NULLPTR,
	                     /* writefn: */ __writefn ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_writefn : __NULLPTR,
	                     /* seekfn:  */ __seekfn  ? &__NAMESPACE_LOCAL_SYM __funopen64_to_funopen2_64_seekfn  : __NULLPTR,
	                     /* flushfn: */ __NULLPTR,
	                     /* closefn: */ __closefn ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_closefn : __NULLPTR);
#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
#elif defined(__CRT_HAVE_fopencookie)
	{
		_IO_cookie_io_functions_t __ioc_functions;
		__ioc_functions.read  = __readfn ? (__io_read_fn *)&__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_readfn : __NULLPTR;
		__ioc_functions.write = __writefn ? (__io_write_fn *)&__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_writefn : __NULLPTR;
#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
		__ioc_functions.seek  = __seekfn ? &__NAMESPACE_LOCAL_SYM __funopen_to_fopencookie_seekfn : __NULLPTR;
#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
		__ioc_functions.seek  = __seekfn ? &__NAMESPACE_LOCAL_SYM __funopen64_to_fopencookie_seekfn : __NULLPTR;
#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
		__ioc_functions.close = __closefn ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_closefn : __NULLPTR;
		__result = __localdep_crt_fopencookie(__holder, __readfn && __writefn ? "r+" : __readfn ? "r" : "w", __ioc_functions);
	}
#else /* ... */
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
	__result = __localdep_funopen32(/* cookie:  */ __holder,
	                   /* readfn:  */ __readfn  ? (__funopen_readfn_t)&__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_readfn  : __NULLPTR,
	                   /* writefn: */ __writefn ? (__funopen_writefn_t)&__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_writefn : __NULLPTR,
	                   /* seekfn:  */ __seekfn  ? (__funopen_seekfn_t)&__NAMESPACE_LOCAL_SYM __funopen_to_funopen64_seekfn  : __NULLPTR,
	                   /* closefn: */ __closefn ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_closefn : __NULLPTR);
#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
	__result = __localdep_funopen32(/* cookie:  */ __holder,
	                   /* readfn:  */ __readfn  ? (__funopen_readfn_t)&__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_readfn  : __NULLPTR,
	                   /* writefn: */ __writefn ? (__funopen_writefn_t)&__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_writefn : __NULLPTR,
	                   /* seekfn:  */ __seekfn  ? &__NAMESPACE_LOCAL_SYM __funopen64_to_funopen_seekfn  : __NULLPTR,
	                   /* closefn: */ __closefn ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_closefn : __NULLPTR);
#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
#if __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
	__result = __localdep_funopen32(/* cookie:  */ __holder,
	                   /* readfn:  */ __readfn  ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen64_readfn  : __NULLPTR,
	                   /* writefn: */ __writefn ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen64_writefn : __NULLPTR,
	                   /* seekfn:  */ __seekfn  ? (__funopen_seekfn_t)&__NAMESPACE_LOCAL_SYM __funopen_to_funopen64_seekfn  : __NULLPTR,
	                   /* closefn: */ __closefn ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_closefn : __NULLPTR);
#else /* __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__ */
	__result = __localdep_funopen32(/* cookie:  */ __holder,
	                   /* readfn:  */ __readfn  ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen64_readfn  : __NULLPTR,
	                   /* writefn: */ __writefn ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen64_writefn : __NULLPTR,
	                   /* seekfn:  */ __seekfn  ? &__NAMESPACE_LOCAL_SYM __funopen64_to_funopen_seekfn  : __NULLPTR,
	                   /* closefn: */ __closefn ? &__NAMESPACE_LOCAL_SYM __funopen_to_funopen2_closefn : __NULLPTR);
#endif /* __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__ */
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
#endif /* !... */
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	if __unlikely(!__result)
		__localdep_free(__holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	return __result;
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ || ((!__CRT_HAVE_funopen2 || __SIZEOF_OFF64_T__ != __SIZEOF_OFF32_T__) && !__CRT_HAVE_funopen2_64 && ((!__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign) || !__CRT_HAVE_funopen2)) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_funopen64_defined
#define __local___localdep_funopen64_defined 1
#define __localdep_funopen64 __LIBC_LOCAL_NAME(funopen64)
#endif /* !__local___localdep_funopen64_defined */
#else /* (__SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((__CRT_HAVE_funopen2 && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen2_64 || ((__CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && __CRT_HAVE_funopen2))) || ((__CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2 || __CRT_HAVE_fopencookie || __CRT_HAVE_funopen)) */
#undef __local_funopen64_defined
#endif /* (__SIZEOF_INT__ != __SIZEOF_SIZE_T__ || ((!__CRT_HAVE_funopen2 || __SIZEOF_OFF64_T__ != __SIZEOF_OFF32_T__) && !__CRT_HAVE_funopen2_64 && ((!__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign) || !__CRT_HAVE_funopen2))) && ((!__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2 && !__CRT_HAVE_fopencookie && !__CRT_HAVE_funopen)) */
#endif /* !__local_funopen64_defined */
