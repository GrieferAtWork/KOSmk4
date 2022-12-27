/* HASH CRC-32:0xa2d67adb */
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
#ifndef __local_fopen_c16printer_defined
#define __local_fopen_c16printer_defined
#include <__crt.h>
#include <bits/types.h>
#include <features.h>
#if (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2))
#include <bits/crt/uformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_8to16_defined
#define __local___localdep_format_8to16_defined
#if defined(__CRT_HAVE_format_8tow) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__FORMATPRINTER_CC,__localdep_format_8to16,(void *__arg, char const *__data, __SIZE_TYPE__ __datalen),format_8tow,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$format_8tow) && defined(__LIBDCALL_IS_FORMATPRINTER_CC)
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_format_8to16,(void *__arg, char const *__data, __SIZE_TYPE__ __datalen),format_8tow,(__arg,__data,__datalen))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/format_8tow.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_8to16 __LIBC_LOCAL_NAME(format_8tow)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/format_8to16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_8to16 __LIBC_LOCAL_NAME(format_8to16)
#endif /* !... */
#endif /* !__local___localdep_format_8to16_defined */
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
#ifndef __local___localdep_funopen2_defined
#define __local___localdep_funopen2_defined
#if defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen2,(void const *__cookie, __SSIZE_TYPE__ (__LIBKCALL *__readfn)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes), __SSIZE_TYPE__ (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes), __off_t (__LIBKCALL *__seekfn)(void *__cookie, __off_t __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)),funopen2,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif defined(__CRT_HAVE_funopen2_64) && __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen2,(void const *__cookie, __SSIZE_TYPE__ (__LIBKCALL *__readfn)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes), __SSIZE_TYPE__ (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes), __off_t (__LIBKCALL *__seekfn)(void *__cookie, __off_t __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)),funopen2_64,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/funopen2.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_funopen2 __LIBC_LOCAL_NAME(funopen2)
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
#include <bits/crt/mbstate.h>
#include <libc/errno.h>
#ifndef ____free_and_return_zero_defined
#define ____free_and_return_zero_defined
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(free_and_return_zero) int
(__LIBKCALL __free_and_return_zero)(void *__arg) {
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
#endif /* !____free_and_return_zero_defined */
#ifndef ____fopen_wprinter_flush_defined
#define ____fopen_wprinter_flush_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fopen_wprinter_flush) int
(__LIBKCALL __fopen_wprinter_flush)(void *__arg) {
	struct __local_format_8tow_data {   /* == `struct format_8tow_data' */
		__pwformatprinter __fd_printer;    /* [1..1] Inner printer */
		void            *__fd_arg;        /* Argument for `fd_printer' */
		struct __mbstate       __fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	} *__me = (struct __local_format_8tow_data *)__arg;

	/* Verify that the mbstate is in an empty state. */
	if (__mbstate_isempty(&__me->__fd_incomplete))
		return 0;

	/* If it isn't then we must indicate an illegal-sequence error. */
#ifdef __EILSEQ
	return __libc_seterrno(__EILSEQ);
#else /* __EILSEQ */
	return __libc_seterrno(1);
#endif /* !__EILSEQ */
}
__NAMESPACE_LOCAL_END
#endif /* !____fopen_wprinter_flush_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fopen_c16printer) __ATTR_WUNUSED __ATTR_NONNULL((1)) __FILE *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(fopen_c16printer))(__pc16formatprinter __printer, void *__arg) {
	__FILE *__result;
	struct __local_format_8tow_data {   /* == `struct format_8tow_data' */
		__pc16formatprinter __fd_printer;    /* [1..1] Inner printer */
		void            *__fd_arg;        /* Argument for `fd_printer' */
		struct __mbstate       __fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	} *__cookie;
	__cookie = (struct __local_format_8tow_data *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(sizeof(struct __local_format_8tow_data));
	if __unlikely(!__cookie)
		return __NULLPTR;
	__cookie->__fd_printer = __printer;
	__cookie->__fd_arg     = __arg;
	__mbstate_init(&__cookie->__fd_incomplete);

	/* KOS's pformatprinter is ABI-compatible with the `writefn' of `funopen2(3)' / `funopen2_64(3)'
	 * -> As such, this function can super-easily be implemented with the help of that one! */
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)

	__result = (__NAMESPACE_LOCAL_SYM __localdep_funopen2_64)(__cookie, __NULLPTR, (__SSIZE_TYPE__ (__LIBKCALL *)(void *, void const *, __SIZE_TYPE__))&(__NAMESPACE_LOCAL_SYM __localdep_format_8to16), __NULLPTR,
	                     &__NAMESPACE_LOCAL_SYM __fopen_wprinter_flush,
	                     &__NAMESPACE_LOCAL_SYM __free_and_return_zero);





#else /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */

	__result = (__NAMESPACE_LOCAL_SYM __localdep_funopen2_64)(__cookie, __NULLPTR, (__SSIZE_TYPE__ (__LIBKCALL *)(void *, void const *, __SIZE_TYPE__))&(__NAMESPACE_LOCAL_SYM __localdep_format_8to16),
	                     __NULLPTR, &__NAMESPACE_LOCAL_SYM __fopen_wprinter_flush, __NULLPTR);




#endif /* !__CRT_HAVE_free && !__CRT_HAVE_cfree && !__CRT_HAVE___libc_free */

	/* Cleanup on error. */
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	if __unlikely(!__result)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__cookie);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fopen_c16printer_defined
#define __local___localdep_fopen_c16printer_defined
#define __localdep_fopen_c16printer __LIBC_LOCAL_NAME(fopen_c16printer)
#endif /* !__local___localdep_fopen_c16printer_defined */
#else /* (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2) */
#undef __local_fopen_c16printer_defined
#endif /* (!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2) */
#endif /* !__local_fopen_c16printer_defined */
