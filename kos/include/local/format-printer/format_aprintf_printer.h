/* HASH CRC-32:0x54107dc1 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_format_aprintf_printer_defined
#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_format_aprintf_alloc)
#define __local_format_aprintf_printer_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "format_aprintf_alloc" from "format-printer" */
#ifndef ____localdep_format_aprintf_alloc_defined
#define ____localdep_format_aprintf_alloc_defined 1
#ifdef __CRT_HAVE_format_aprintf_alloc
/* Allocate a buffer of `num_chars' characters at the end of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized, or some other function is used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)),char *,__NOTHROW_NCX,__localdep_format_aprintf_alloc,(struct format_aprintf_data *__restrict __self, __SIZE_TYPE__ __num_chars),format_aprintf_alloc,(__self,__num_chars))
#elif defined(__CRT_HAVE_realloc)
#include <local/format-printer/format_aprintf_alloc.h>
/* Allocate a buffer of `num_chars' characters at the end of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized, or some other function is used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory */
#define __localdep_format_aprintf_alloc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_aprintf_alloc))
#else /* CUSTOM: format_aprintf_alloc */
#undef ____localdep_format_aprintf_alloc_defined
#endif /* format_aprintf_alloc... */
#endif /* !____localdep_format_aprintf_alloc_defined */

/* Dependency: "memcpyc" from "string" */
#ifndef ____localdep_memcpyc_defined
#define ____localdep_memcpyc_defined 1
#ifdef __fast_memcpyc_defined
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpyc (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyc))
#elif defined(__CRT_HAVE_memcpyc)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* LIBC: memcpyc */
#include <local/string/memcpyc.h>
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpyc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyc))
#endif /* memcpyc... */
#endif /* !____localdep_memcpyc_defined */

__NAMESPACE_LOCAL_BEGIN
/* Print data to a dynamically allocated heap buffer. On error, -1 is returned
 * This function is intended to be used as a pformatprinter-compatibile printer sink */
__LOCAL_LIBC(format_aprintf_printer) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(format_aprintf_printer))(/*struct format_aprintf_data **/ void *__arg,
                                                                    /*utf-8*/ char const *__restrict __data,
                                                                    __SIZE_TYPE__ __datalen) {
#line 1211 "kos/src/libc/magic/format-printer.c"
	char *__buf;
	__buf = __localdep_format_aprintf_alloc((struct format_aprintf_data *)__arg,
	                           __datalen);
	if __unlikely(!__buf)
		return -1;
	__localdep_memcpyc(__buf, __data, __datalen, sizeof(char));
	return (__SSIZE_TYPE__)__datalen;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_realloc || __CRT_HAVE_format_aprintf_alloc */
#endif /* !__local_format_aprintf_printer_defined */
