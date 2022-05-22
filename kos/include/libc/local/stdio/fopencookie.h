/* HASH CRC-32:0x49c22f05 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fopencookie_defined
#define __local_fopencookie_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#include <hybrid/typecore.h>
#if (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen64) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2) || defined(__CRT_HAVE_funopen))
#include <libio.h>
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
#ifndef __local___localdep_funopen_defined
#define __local___localdep_funopen_defined
#if defined(__CRT_HAVE_funopen) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen,(void const *__cookie, int (__LIBKCALL *__readfn)(void *__cookie, char *__buf, int __num_bytes), int (__LIBKCALL *__writefn)(void *__cookie, char const *__buf, int __num_bytes), __FS_TYPE(off) (__LIBKCALL *__seekfn)(void *__cookie, __FS_TYPE(off) __off, int __whence), int (__LIBKCALL *__closefn)(void *__cookie)),funopen,(__cookie,__readfn,__writefn,__seekfn,__closefn))
#elif defined(__CRT_HAVE_funopen64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen,(void const *__cookie, int (__LIBKCALL *__readfn)(void *__cookie, char *__buf, int __num_bytes), int (__LIBKCALL *__writefn)(void *__cookie, char const *__buf, int __num_bytes), __FS_TYPE(off) (__LIBKCALL *__seekfn)(void *__cookie, __FS_TYPE(off) __off, int __whence), int (__LIBKCALL *__closefn)(void *__cookie)),funopen64,(__cookie,__readfn,__writefn,__seekfn,__closefn))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/funopen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_funopen __LIBC_LOCAL_NAME(funopen)
#endif /* !... */
#endif /* !__local___localdep_funopen_defined */
#ifndef __local___localdep_funopen2_defined
#define __local___localdep_funopen2_defined
#if defined(__CRT_HAVE_funopen2) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen2,(void const *__cookie, __SSIZE_TYPE__ (__LIBKCALL *__readfn)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes), __SSIZE_TYPE__ (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes), __FS_TYPE(off) (__LIBKCALL *__seekfn)(void *__cookie, __FS_TYPE(off) __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)),funopen2,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif defined(__CRT_HAVE_funopen2_64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen2,(void const *__cookie, __SSIZE_TYPE__ (__LIBKCALL *__readfn)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes), __SSIZE_TYPE__ (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes), __FS_TYPE(off) (__LIBKCALL *__seekfn)(void *__cookie, __FS_TYPE(off) __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)),funopen2_64,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/funopen2.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_funopen2 __LIBC_LOCAL_NAME(funopen2)
#else /* ... */
#undef __local___localdep_funopen2_defined
#endif /* !... */
#endif /* !__local___localdep_funopen2_defined */
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
#ifndef __local___localdep_funopen64_defined
#define __local___localdep_funopen64_defined
#if defined(__CRT_HAVE_funopen) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen64,(void const *__cookie, int (__LIBKCALL *__readfn)(void *__cookie, char *__buf, int __num_bytes), int (__LIBKCALL *__writefn)(void *__cookie, char const *__buf, int __num_bytes), __off64_t (__LIBKCALL *__seekfn)(void *__cookie, __off64_t __off, int __whence), int (__LIBKCALL *__closefn)(void *__cookie)),funopen,(__cookie,__readfn,__writefn,__seekfn,__closefn))
#elif defined(__CRT_HAVE_funopen64)
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen64,(void const *__cookie, int (__LIBKCALL *__readfn)(void *__cookie, char *__buf, int __num_bytes), int (__LIBKCALL *__writefn)(void *__cookie, char const *__buf, int __num_bytes), __off64_t (__LIBKCALL *__seekfn)(void *__cookie, __off64_t __off, int __whence), int (__LIBKCALL *__closefn)(void *__cookie)),funopen64,(__cookie,__readfn,__writefn,__seekfn,__closefn))
#elif defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2) || defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/funopen64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_funopen64 __LIBC_LOCAL_NAME(funopen64)
#else /* ... */
#undef __local___localdep_funopen64_defined
#endif /* !... */
#endif /* !__local___localdep_funopen64_defined */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
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
#ifndef ____fopencookie_holder_defined
__NAMESPACE_LOCAL_BEGIN
#define ____fopencookie_holder_defined
struct __fopencookie_holder {
	void                     *__foch_cookie; /* User-defined `magic_cookie' */
	_IO_cookie_io_functions_t __foch_funcs;  /* Cookie functions */
};
__NAMESPACE_LOCAL_END
#endif /* !____fopencookie_holder_defined */
#ifndef __fopencookie_to_funopen_closefn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_closefn_defined
__LOCAL_LIBC(__fopencookie_to_funopen_closefn) int
(__LIBKCALL __fopencookie_to_funopen_closefn)(void *__cookie) {
	int __result = 0;
	struct __fopencookie_holder *__holder;
	__holder = (struct __fopencookie_holder *)__cookie;
	if (__holder->__foch_funcs.close != __NULLPTR)
		__result = (*__holder->__foch_funcs.close)(__holder->__foch_cookie);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__fopencookie_to_funopen_closefn_defined */

#if !defined(__BUILDING_LIBC) && defined(__CRT_HAVE_funopen64) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#ifndef __fopencookie_to_funopen_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_readfn_defined
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
#define __fopencookie_to_funopen_writefn_defined
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
#define __fopencookie_to_funopen64_seekfn_defined
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
#define __fopencookie_to_funopen_readfn_defined
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
#define __fopencookie_to_funopen_writefn_defined
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
#define __fopencookie_to_funopen_seekfn_defined
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

#elif (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2))
#ifndef __fopencookie_to_funopen2_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen2_readfn_defined
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
#define __fopencookie_to_funopen2_writefn_defined
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
#define __fopencookie_to_funopen64_seekfn_defined
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
#define __fopencookie_to_funopen2_readfn_defined
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
#define __fopencookie_to_funopen2_writefn_defined
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
#define __fopencookie_to_funopen_seekfn_defined
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

#elif (defined(__CRT_HAVE_funopen) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_funopen2) || defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen)))
#ifndef __fopencookie_to_funopen_readfn_defined
__NAMESPACE_LOCAL_BEGIN
#define __fopencookie_to_funopen_readfn_defined
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
#define __fopencookie_to_funopen_writefn_defined
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
#define __fopencookie_to_funopen64_seekfn_defined
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
#define __fopencookie_to_funopen_readfn_defined
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
#define __fopencookie_to_funopen_writefn_defined
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
#define __fopencookie_to_funopen_seekfn_defined
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
__LOCAL_LIBC(fopencookie) __ATTR_WUNUSED __ATTR_ACCESS_RO(2) __FILE *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fopencookie))(void *__restrict __magic_cookie, char const *__restrict __modes, _IO_cookie_io_functions_t __io_funcs) {
	__FILE *__result;
	struct __NAMESPACE_LOCAL_SYM __fopencookie_holder *__holder;
	(void)__modes; /* unused... */
	__holder = (struct __NAMESPACE_LOCAL_SYM __fopencookie_holder *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(sizeof(struct __NAMESPACE_LOCAL_SYM __fopencookie_holder));
	if __unlikely(!__holder)
		return __NULLPTR;
	__holder->__foch_cookie        = __magic_cookie;
	__holder->__foch_funcs.read  = __io_funcs.read;
	__holder->__foch_funcs.write = __io_funcs.write;
	__holder->__foch_funcs.seek  = __io_funcs.seek;
	__holder->__foch_funcs.close = __io_funcs.close;
#if defined(__CRT_HAVE_funopen64) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__
	__result = (__NAMESPACE_LOCAL_SYM __localdep_funopen64)(/* cookie:  */ __holder,
	                   /* readfn:  */ __io_funcs.read ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_readfn : __NULLPTR,
	                   /* writefn: */ __io_funcs.write ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_writefn : __NULLPTR,
	                   /* seekfn:  */ __io_funcs.seek ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen64_seekfn : __NULLPTR,
	                   /* closefn: */ &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_closefn);
#elif defined(__CRT_HAVE_funopen) && !defined(__CRT_HAVE_funopen2_64) && __SIZEOF_INT__ == __SIZEOF_SIZE_T__
	__result = (__NAMESPACE_LOCAL_SYM __localdep_funopen)(/* cookie:  */ __holder,
	                 /* readfn:  */ __io_funcs.read ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_readfn : __NULLPTR,
	                 /* writefn: */ __io_funcs.write ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_writefn : __NULLPTR,
	                 /* seekfn:  */ __io_funcs.seek ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_seekfn : __NULLPTR,
	                 /* closefn: */ __io_funcs.seek ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_closefn : __NULLPTR);
#elif (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2)
	__result = (__NAMESPACE_LOCAL_SYM __localdep_funopen2_64)(/* cookie:  */ __holder,
	                     /* readfn:  */ __io_funcs.read ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen2_readfn : __NULLPTR,
	                     /* writefn: */ __io_funcs.write ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen2_writefn : __NULLPTR,
	                     /* seekfn:  */ __io_funcs.seek ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen64_seekfn : __NULLPTR,
	                     /* flushfn: */ __NULLPTR,
	                     /* closefn: */ &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_closefn);







#elif defined(__CRT_HAVE_funopen64) || defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen)
	__result = (__NAMESPACE_LOCAL_SYM __localdep_funopen64)(/* cookie:  */ __holder,
	                   /* readfn:  */ __io_funcs.read ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_readfn : __NULLPTR,
	                   /* writefn: */ __io_funcs.write ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_writefn : __NULLPTR,
	                   /* seekfn:  */ __io_funcs.seek ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen64_seekfn : __NULLPTR,
	                   /* closefn: */ &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_closefn);
#else /* ... */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_funopen)(/* cookie:  */ __holder,
	                 /* readfn:  */ __io_funcs.read ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_readfn : __NULLPTR,
	                 /* writefn: */ __io_funcs.write ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_writefn : __NULLPTR,
	                 /* seekfn:  */ __io_funcs.seek ? &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_seekfn : __NULLPTR,
	                 /* closefn: */ &__NAMESPACE_LOCAL_SYM __fopencookie_to_funopen_closefn);
#endif /* !... */
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	if __unlikely(!__result)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__holder);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fopencookie_defined
#define __local___localdep_fopencookie_defined
#define __localdep_fopencookie __LIBC_LOCAL_NAME(fopencookie)
#endif /* !__local___localdep_fopencookie_defined */
#else /* (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_fopencookie || __CRT_HAVE_funopen64 || __CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2 || __CRT_HAVE_funopen) */
#undef __local_fopencookie_defined
#endif /* (!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_fopencookie && !__CRT_HAVE_funopen64 && !__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2 && !__CRT_HAVE_funopen) */
#endif /* !__local_fopencookie_defined */
