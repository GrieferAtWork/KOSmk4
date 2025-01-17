/* HASH CRC-32:0xd4b5a5ec */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fopen_printer_defined
#define __local_fopen_printer_defined
#include <__crt.h>
#include <bits/types.h>
#include <features.h>
#if (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2)) || (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF_T__ == __SIZEOF_OFF32_T__)
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_funopen2_defined
#define __local___localdep_funopen2_defined
#if defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen2,(void const *__cookie, __SSIZE_TYPE__ (__LIBKCALL *__readfn)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes), __SSIZE_TYPE__ (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes), __off_t (__LIBKCALL *__seekfn)(void *__cookie, __off_t __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)),funopen2,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif defined(__CRT_HAVE_funopen2_64) && __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,__localdep_funopen2,(void const *__cookie, __SSIZE_TYPE__ (__LIBKCALL *__readfn)(void *__cookie, void *__buf, __SIZE_TYPE__ __num_bytes), __SSIZE_TYPE__ (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, __SIZE_TYPE__ __num_bytes), __off_t (__LIBKCALL *__seekfn)(void *__cookie, __off_t __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)),funopen2_64,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2))
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
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/funopen2_64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_funopen2_64 __LIBC_LOCAL_NAME(funopen2_64)
#else /* ... */
#undef __local___localdep_funopen2_64_defined
#endif /* !... */
#endif /* !__local___localdep_funopen2_64_defined */
__LOCAL_LIBC(fopen_printer) __ATTR_WUNUSED __ATTR_NONNULL((1)) __FILE *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fopen_printer))(__pformatprinter __printer, void *__arg) {
	/* KOS's pformatprinter is ABI-compatible with the `writefn' of `funopen2(3)' / `funopen2_64(3)'
	 * -> As such, this function can super-easily be implemented with the help of that one! */
#if (defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2))
	return (__NAMESPACE_LOCAL_SYM __localdep_funopen2_64)(__arg, __NULLPTR, (__SSIZE_TYPE__ (__LIBKCALL *)(void *, void const *, __SIZE_TYPE__))__printer, __NULLPTR, __NULLPTR, __NULLPTR);
#else /* (__CRT_HAVE_funopen2 && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen2_64 || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_funopen2) */
	return (__NAMESPACE_LOCAL_SYM __localdep_funopen2)(__arg, __NULLPTR, (__SSIZE_TYPE__ (__LIBKCALL *)(void *, void const *, __SIZE_TYPE__))__printer, __NULLPTR, __NULLPTR, __NULLPTR);
#endif /* (!__CRT_HAVE_funopen2 || __SIZEOF_OFF64_T__ != __SIZEOF_OFF32_T__) && !__CRT_HAVE_funopen2_64 && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || !__CRT_HAVE_funopen2) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fopen_printer_defined
#define __local___localdep_fopen_printer_defined
#define __localdep_fopen_printer __LIBC_LOCAL_NAME(fopen_printer)
#endif /* !__local___localdep_fopen_printer_defined */
#else /* (__CRT_HAVE_funopen2 && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen2_64 || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_funopen2) || (__CRT_HAVE_funopen2 && __SIZEOF_OFF_T__ == __SIZEOF_OFF32_T__) */
#undef __local_fopen_printer_defined
#endif /* (!__CRT_HAVE_funopen2 || __SIZEOF_OFF64_T__ != __SIZEOF_OFF32_T__) && !__CRT_HAVE_funopen2_64 && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || !__CRT_HAVE_funopen2) && (!__CRT_HAVE_funopen2 || __SIZEOF_OFF_T__ != __SIZEOF_OFF32_T__) */
#endif /* !__local_fopen_printer_defined */
