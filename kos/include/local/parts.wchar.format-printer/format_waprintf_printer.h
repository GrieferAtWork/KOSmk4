/* HASH CRC-32:0xcb5ce04c */
/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef __local_format_waprintf_printer_defined
#if defined(__CRT_HAVE_realloc)
#define __local_format_waprintf_printer_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <hybrid/__assert.h>
/* Dependency: "realloc" */
#ifndef ____localdep_realloc_defined
#define ____localdep_realloc_defined 1
#ifdef __std___localdep_realloc_defined
__NAMESPACE_STD_USING(__localdep_realloc)
#elif __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__FORCELOCAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL __localdep_realloc)(void *__mallptr, __SIZE_TYPE__ __n_bytes) { return __builtin_realloc(__mallptr, __n_bytes); }
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __n_bytes),realloc,(__mallptr,__n_bytes))
#else /* LIBC: realloc */
#undef ____localdep_realloc_defined
#endif /* realloc... */
#endif /* !____localdep_realloc_defined */

/* Dependency: "memcpy" from "string" */
#ifndef ____localdep_memcpy_defined
#define ____localdep_memcpy_defined 1
#if defined(__fast_memcpy_defined)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))
#elif defined(__CRT_HAVE_memcpy)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* LIBC: memcpy */
#include <local/string/memcpy.h>
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))
#endif /* memcpy... */
#endif /* !____localdep_memcpy_defined */

__NAMESPACE_LOCAL_BEGIN
/* Print data to a dynamically allocated heap buffer. On error, -1 is returned */
__LOCAL_LIBC(format_waprintf_printer) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(format_waprintf_printer))(/*struct format_waprintf_data **/void *__arg,
                                                                     __WCHAR_TYPE__ const *__restrict __data,
                                                                     __SIZE_TYPE__ __datalen) {
#line 1141 "kos/src/libc/magic/format-printer.c"
	struct __format_aprintf_data {
		__WCHAR_TYPE__         *__ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
		__SIZE_TYPE__ __ap_avail; /* Unused buffer size */
		__SIZE_TYPE__ __ap_used;  /* Used buffer size */
	};
	struct __format_aprintf_data *__buf;
	__buf = (struct __format_aprintf_data *)__arg;
	if (__buf->__ap_avail < __datalen) {
		__WCHAR_TYPE__ *__newbuf;
		__SIZE_TYPE__ __min_alloc = __buf->__ap_used + __datalen;
		__SIZE_TYPE__ __new_alloc = __buf->__ap_used + __buf->__ap_avail;
		if (!__new_alloc)
			__new_alloc = 8;
		while (__new_alloc < __min_alloc)
			__new_alloc *= 2;
		__newbuf = (__WCHAR_TYPE__ *)__localdep_realloc(__buf->__ap_base, (__new_alloc + 1) * sizeof(__WCHAR_TYPE__));
		if __unlikely(!__newbuf) {
			__new_alloc = __min_alloc;
			__newbuf    = (__WCHAR_TYPE__ *)__localdep_realloc(__buf->__ap_base, (__new_alloc + 1) * sizeof(__WCHAR_TYPE__));
			if __unlikely(!__newbuf)
				return -1;
		}
		__hybrid_assert(__new_alloc >= __buf->__ap_used + __datalen);
		__buf->__ap_base  = __newbuf;
		__buf->__ap_avail = __new_alloc - __buf->__ap_used;
	}
	__localdep_memcpy(__buf->__ap_base + __buf->__ap_used, __data, __datalen * sizeof(__WCHAR_TYPE__));
	__buf->__ap_avail -= __datalen;
	__buf->__ap_used  += __datalen;
	return (__SSIZE_TYPE__)__datalen;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_realloc) */
#endif /* !__local_format_waprintf_printer_defined */
