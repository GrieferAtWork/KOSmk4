/* HASH CRC-32:0xbbe517d5 */
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
#ifndef __local_vasnprintf_defined
#define __local_vasnprintf_defined
#include <__crt.h>
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_vprintf_defined
#define __local___localdep_format_vprintf_defined
#ifdef __CRT_HAVE_format_vprintf
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,__localdep_format_vprintf,(__pformatprinter __printer, void *__arg, char const *__restrict __format, __builtin_va_list __args),format_vprintf,(__printer,__arg,__format,__args))
#else /* __CRT_HAVE_format_vprintf */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_vprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vprintf __LIBC_LOCAL_NAME(format_vprintf)
#endif /* !__CRT_HAVE_format_vprintf */
#endif /* !__local___localdep_format_vprintf_defined */
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
#ifndef __local___localdep_malloc_usable_size_defined
#define __local___localdep_malloc_usable_size_defined
#ifdef __CRT_HAVE_malloc_usable_size
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_malloc_usable_size,(void *__restrict __mallptr),malloc_usable_size,(__mallptr))
#elif defined(__CRT_HAVE__msize)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_malloc_usable_size,(void *__restrict __mallptr),_msize,(__mallptr))
#else /* ... */
#undef __local___localdep_malloc_usable_size_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_usable_size_defined */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#ifndef __local___localdep_mempcpy_defined
#define __local___localdep_mempcpy_defined
#ifdef __CRT_HAVE_mempcpy
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempcpy __LIBC_LOCAL_NAME(mempcpy)
#endif /* !... */
#endif /* !__local___localdep_mempcpy_defined */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
#ifndef __local___localdep_realloc_in_place_defined
#define __local___localdep_realloc_in_place_defined
#ifdef __CRT_HAVE_realloc_in_place
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc_in_place,(void *__restrict __mallptr, __SIZE_TYPE__ __n_bytes),realloc_in_place,(__mallptr,__n_bytes))
#elif defined(__CRT_HAVE__expand)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc_in_place,(void *__restrict __mallptr, __SIZE_TYPE__ __n_bytes),_expand,(__mallptr,__n_bytes))
#else /* ... */
#undef __local___localdep_realloc_in_place_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_in_place_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
struct __vasnprintf_data {
	char  *__vapd_obf; /* [0..1][MAYBE(owned)] Original output buffer. */
	char  *__vapd_buf; /* [0..1][MAYBE(owned)] Output buffer base pointer. */
	char  *__vapd_ptr; /* [0..vapd_cnt] Pointer into `vapd_buf' for where to continue writing */
	__SIZE_TYPE__ __vapd_cnt; /* # of remaining, available bytes in `vapd_ptr' (excluding space for trailing NUL) */
};
__LOCAL_LIBC(vasnprintf_printer) __SSIZE_TYPE__
__NOTHROW_NCX(__FORMATPRINTER_CC __vasnprintf_printer)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) {
	struct __vasnprintf_data *__cookie;
	__cookie = (struct __vasnprintf_data *)__arg;

	/* Check for sufficient space. */
	if (__datalen > __cookie->__vapd_cnt) {
		char *__newbuf;
		__SIZE_TYPE__ __reqlen;
		__reqlen = (__cookie->__vapd_ptr - __cookie->__vapd_buf) * sizeof(char);
		__reqlen += __datalen * sizeof(char);
		__reqlen += sizeof(char); /* For trailing NUL */
		if (__cookie->__vapd_buf == __cookie->__vapd_obf) {
			__SIZE_TYPE__ __offset;
#if defined(__CRT_HAVE_realloc_in_place) || defined(__CRT_HAVE__expand)
			__newbuf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc_in_place)(__cookie->__vapd_obf, __reqlen);
			if (__newbuf) {
				__cookie->__vapd_cnt = __datalen;
				goto __dowrite;
			}
#endif /* __CRT_HAVE_realloc_in_place || __CRT_HAVE__expand */

			/* Allocate the initial version of our own heap-buffer */
			__reqlen += 512 * sizeof(char);
			__newbuf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__reqlen);
			if __unlikely(!__newbuf) {
				__reqlen -= 512 * sizeof(char);
				__newbuf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__reqlen);
				if __unlikely(!__newbuf)
					goto __err;
			}
#if defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize)
			__reqlen = (__NAMESPACE_LOCAL_SYM __localdep_malloc_usable_size)(__newbuf) - sizeof(char);
#endif /* __CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize */
			__offset = (__SIZE_TYPE__)(__cookie->__vapd_ptr - __cookie->__vapd_buf);
			/* Copy already-printed data off of the initial buffer */
			__newbuf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__newbuf, __cookie->__vapd_buf,
			                        __offset * sizeof(char));
			__cookie->__vapd_buf = __newbuf;
			__cookie->__vapd_ptr = __newbuf + __offset;
			__cookie->__vapd_cnt = (__reqlen / sizeof(char)) - __offset;
		} else {
			__SIZE_TYPE__ __offset;

#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
			/* Already on secondary buffer -> try to realloc to a larger size */
			__reqlen += 512 * sizeof(char);
			__newbuf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__cookie->__vapd_buf, __reqlen);
			if __unlikely(!__newbuf) {
				__reqlen -= 512 * sizeof(char);
				__newbuf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__cookie->__vapd_buf, __reqlen);
				if __unlikely(!__newbuf)
					goto __err;
			}
#if defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize)
			__reqlen = (__NAMESPACE_LOCAL_SYM __localdep_malloc_usable_size)(__newbuf) - sizeof(char);
#endif /* __CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize */
			__offset = (__SIZE_TYPE__)(__cookie->__vapd_ptr - __cookie->__vapd_buf);
			__cookie->__vapd_buf = __newbuf;
			__cookie->__vapd_ptr = __newbuf + __offset;
			__cookie->__vapd_cnt = (__reqlen / sizeof(char)) - __offset;
#else /* __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
			/* No realloc(3) function -> can only use malloc */
			__reqlen += 512 * sizeof(char);
			__newbuf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__reqlen);
			if __unlikely(!__newbuf) {
				__reqlen -= 512 * sizeof(char);
				__newbuf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__reqlen);
				if __unlikely(!__newbuf)
					goto __err;
			}
#if defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize)
			__reqlen = (__NAMESPACE_LOCAL_SYM __localdep_malloc_usable_size)(__newbuf) - sizeof(char);
#endif /* __CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize */
			__offset = (__SIZE_TYPE__)(__cookie->__vapd_ptr - __cookie->__vapd_buf);
			__newbuf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__newbuf, __cookie->__vapd_buf, __offset * sizeof(char));
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
			(__NAMESPACE_LOCAL_SYM __localdep_free)(__cookie->__vapd_buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
			__cookie->__vapd_buf = __newbuf;
			__cookie->__vapd_ptr = __newbuf + __offset;
			__cookie->__vapd_cnt = (__reqlen / sizeof(char)) - __offset;
#endif /* !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc */
		}
	}

	/* Do the write! */
__dowrite:
	__cookie->__vapd_ptr = (char *)(__NAMESPACE_LOCAL_SYM __localdep_mempcpy)(__cookie->__vapd_ptr, __data, __datalen * sizeof(char));
	__cookie->__vapd_cnt -= __datalen;
	return (__SSIZE_TYPE__)__datalen;
__err:
	return -1; /* Stop printing! */
}
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vasnprintf) __ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_LIBC_PRINTF(3, 0) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vasnprintf))(char *__heapbuf, __SIZE_TYPE__ *__p_buflen, char const *__format, __builtin_va_list __args) {
	__SIZE_TYPE__ __result_buflen;
	struct __NAMESPACE_LOCAL_SYM __vasnprintf_data __cookie;
	__cookie.__vapd_obf = __heapbuf;
	__cookie.__vapd_buf = __heapbuf;
	__cookie.__vapd_ptr = __heapbuf;
	__cookie.__vapd_cnt = *__p_buflen;

	/* Allocate an initial buffer if none was provided by the caller. */
	if (!__cookie.__vapd_buf || !__cookie.__vapd_cnt) {
		__cookie.__vapd_obf = __NULLPTR;
		__cookie.__vapd_cnt = 512;
		__cookie.__vapd_buf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(512 * sizeof(char));
		if __unlikely(!__cookie.__vapd_buf) {
			__cookie.__vapd_cnt = 1;
			__cookie.__vapd_buf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(sizeof(char));
			if __unlikely(!__cookie.__vapd_buf)
				return __NULLPTR;
		}
		__cookie.__vapd_ptr = __cookie.__vapd_buf;
	}

	/* Do the print. */
	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_format_vprintf)(&__NAMESPACE_LOCAL_SYM __vasnprintf_printer,
	                           &__cookie, __format, __args) < 0)
		goto __err;

	/* Realloc to shrink result buffer to its minimal size. */
	__result_buflen = (__SIZE_TYPE__)(__cookie.__vapd_ptr - __cookie.__vapd_buf);
	if (__cookie.__vapd_buf == __cookie.__vapd_obf) {
#if defined(__CRT_HAVE_realloc_in_place) || defined(__CRT_HAVE__expand)
		/* Still using caller-given buffer -> must use realloc_in_place! */
		(__NAMESPACE_LOCAL_SYM __localdep_realloc_in_place)(__cookie.__vapd_obf, (__result_buflen + 1) * sizeof(char));
#endif /* __CRT_HAVE_realloc_in_place || __CRT_HAVE__expand */
	} else {
#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
		char *__result;
		__result = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__cookie.__vapd_buf, (__result_buflen + 1) * sizeof(char));
		if __likely(__result != __NULLPTR)
			__cookie.__vapd_buf = __result;
#endif /* __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
	}

	/* Ensure NUL-termination */
	__cookie.__vapd_buf[__result_buflen] = '\0';
	*__p_buflen = __result_buflen;
	return __cookie.__vapd_buf;
__err:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	if (__cookie.__vapd_buf != __cookie.__vapd_obf)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__cookie.__vapd_buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vasnprintf_defined
#define __local___localdep_vasnprintf_defined
#define __localdep_vasnprintf __LIBC_LOCAL_NAME(vasnprintf)
#endif /* !__local___localdep_vasnprintf_defined */
#else /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
#undef __local_vasnprintf_defined
#endif /* !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign */
#endif /* !__local_vasnprintf_defined */
