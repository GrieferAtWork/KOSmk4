/* HASH CRC-32:0xa05be19b */
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
#ifndef __local_fmemopen_defined
#define __local_fmemopen_defined
#include <__crt.h>
#include <bits/types.h>
#if (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2))
#include <hybrid/typecore.h>
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
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#ifndef __local___localdep_strchr_defined
#define __local___localdep_strchr_defined
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
#elif __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
#elif defined(__CRT_HAVE_strchr)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
#elif defined(__CRT_HAVE_index)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),index,(__haystack,__needle))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strchr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strchr __LIBC_LOCAL_NAME(strchr)
#endif /* !... */
#endif /* !__local___localdep_strchr_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <asm/os/stdio.h>
__NAMESPACE_LOCAL_BEGIN
struct __memopen_cookie {
	__BYTE_TYPE__ *__moc_base; /* [1..1] Base-pointer */
	__BYTE_TYPE__ *__moc_cur;  /* [1..1] Current position */
	__BYTE_TYPE__ *__moc_end;  /* [1..1] End-pointer */
};

__LOCAL_LIBC(memopen_read) __SSIZE_TYPE__ __LIBCCALL
__memopen_read(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes) {
	__SIZE_TYPE__ __maxlen;
	struct __memopen_cookie *__me;
	__me = (struct __memopen_cookie *)__cookie;
	__maxlen = (__SIZE_TYPE__)(__me->__moc_end - __me->__moc_cur);
	if (__maxlen > __num_bytes)
		__maxlen = __num_bytes;
	(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__buf, __me->__moc_cur, __maxlen);
	__me->__moc_cur += __maxlen;
	return (__SIZE_TYPE__)__maxlen;
}

__LOCAL_LIBC(memopen_write) __SSIZE_TYPE__ __LIBCCALL
__memopen_write(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes) {
	__SIZE_TYPE__ __maxlen;
	struct __memopen_cookie *__me;
	__me = (struct __memopen_cookie *)__cookie;
	__maxlen = (__SIZE_TYPE__)(__me->__moc_end - __me->__moc_cur);
	if (__maxlen > __num_bytes)
		__maxlen = __num_bytes;
	(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__me->__moc_cur, __buf, __maxlen);
	__me->__moc_cur += __maxlen;
	return (__SIZE_TYPE__)__maxlen;
}

__LOCAL_LIBC(memopen_seek) __off64_t __LIBCCALL
__memopen_seek(void *__cookie, __off64_t __off, int __whence) {
	__pos64_t __newpos;
	struct __memopen_cookie *__me;
	__SIZE_TYPE__ __maxlen;
	__me = (struct __memopen_cookie *)__cookie;
	__newpos = (__pos64_t)__off;
	__maxlen = (__SIZE_TYPE__)(__me->__moc_end - __me->__moc_cur);
	switch (__whence) {

	case __SEEK_SET:
		break;

	case __SEEK_CUR:
		__newpos += (__SIZE_TYPE__)(__me->__moc_cur - __me->__moc_base);
		if __unlikely((__off64_t)__newpos < 0)
			goto __err_EOVERFLOW;
		break;

	case __SEEK_END:
		__newpos += __maxlen;
		if __unlikely((__off64_t)__newpos < 0)
			goto __err_EOVERFLOW;
		break;

	default:
#ifdef __EINVAL
		return (__off64_t)__libc_seterrno(__EINVAL);
#else /* __EINVAL */
		return (__off64_t)__libc_seterrno(1);
#endif /* !__EINVAL */
	}
	if (__newpos > __maxlen)
		__newpos = __maxlen;
	__me->__moc_cur = __me->__moc_base + (__SIZE_TYPE__)__newpos;
	return (__off64_t)__newpos;
__err_EOVERFLOW:
#ifdef __EOVERFLOW
	return (__off64_t)__libc_seterrno(__EOVERFLOW);
#else /* __EOVERFLOW */
	return (__off64_t)__libc_seterrno(1);
#endif /* !__EOVERFLOW */
}

__LOCAL_LIBC(memopen_close) int __LIBCCALL
__memopen_close(void *__cookie) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__cookie);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return 0;
}
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fmemopen) __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __FILE *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fmemopen))(void *__mem, __SIZE_TYPE__ __len, char const *__modes) {
	__FILE *__result;
	struct __NAMESPACE_LOCAL_SYM __memopen_cookie *__magic;
	__magic = (struct __NAMESPACE_LOCAL_SYM __memopen_cookie *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(sizeof(struct __NAMESPACE_LOCAL_SYM __memopen_cookie));
	if __unlikely(!__magic)
		return __NULLPTR;
	__magic->__moc_base = (__BYTE_TYPE__ *)__mem;
	__magic->__moc_cur  = (__BYTE_TYPE__ *)__mem;
	__magic->__moc_end  = (__BYTE_TYPE__ *)__mem + __len;
	/* Open a custom file-stream. */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_funopen2_64)(__magic,
	                     &__NAMESPACE_LOCAL_SYM __memopen_read,
	                     ((__NAMESPACE_LOCAL_SYM __localdep_strchr)(__modes, 'w') || (__NAMESPACE_LOCAL_SYM __localdep_strchr)(__modes, '+'))
	                     ? &__NAMESPACE_LOCAL_SYM __memopen_write
	                     : __NULLPTR,
	                     &__NAMESPACE_LOCAL_SYM __memopen_seek,
	                     __NULLPTR,
	                     &__NAMESPACE_LOCAL_SYM __memopen_close);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	if __unlikely(!__result)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__magic);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fmemopen_defined
#define __local___localdep_fmemopen_defined
#define __localdep_fmemopen __LIBC_LOCAL_NAME(fmemopen)
#endif /* !__local___localdep_fmemopen_defined */
#else /* (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && ((__CRT_HAVE_funopen2 && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2) */
#undef __local_fmemopen_defined
#endif /* (!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2) */
#endif /* !__local_fmemopen_defined */
