/* HASH CRC-32:0x43711501 */
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
#ifndef __local_obstack_printer_defined
#define __local_obstack_printer_defined
#include <__crt.h>
#include <bits/crt/obstack.h>
#if defined(__CRT_HAVE__obstack_newchunk) || defined(__LOCAL_obstack_alloc_failed_handler) || defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE_xexit)
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__obstack_newchunk_defined
#define __local___localdep__obstack_newchunk_defined
#ifdef __CRT_HAVE__obstack_newchunk
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__localdep__obstack_newchunk,(struct obstack *__self, __SIZE_TYPE__ __num_bytes),_obstack_newchunk,(__self,__num_bytes))
#elif defined(__LOCAL_obstack_alloc_failed_handler) || defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE_xexit)
__NAMESPACE_LOCAL_END
#include <libc/local/obstack/_obstack_newchunk.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__obstack_newchunk __LIBC_LOCAL_NAME(_obstack_newchunk)
#else /* ... */
#undef __local___localdep__obstack_newchunk_defined
#endif /* !... */
#endif /* !__local___localdep__obstack_newchunk_defined */
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
__LOCAL_LIBC(obstack_printer) __ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__FORMATPRINTER_CC __LIBC_LOCAL_NAME(obstack_printer))(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) {
	struct obstack *__me = (struct obstack *)__arg;
	if ((__SIZE_TYPE__)(__me->chunk_limit - __me->next_free) < __datalen)
		(__NAMESPACE_LOCAL_SYM __localdep__obstack_newchunk)(__me, __datalen);
	__me->next_free = (char *)(__NAMESPACE_LOCAL_SYM __localdep_mempcpy)(__me->next_free, __data, __datalen);
	return (__SSIZE_TYPE__)__datalen;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_obstack_printer_defined
#define __local___localdep_obstack_printer_defined
#define __localdep_obstack_printer __LIBC_LOCAL_NAME(obstack_printer)
#endif /* !__local___localdep_obstack_printer_defined */
#else /* __CRT_HAVE__obstack_newchunk || __LOCAL_obstack_alloc_failed_handler || __CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit || __CRT_HAVE_xexit */
#undef __local_obstack_printer_defined
#endif /* !__CRT_HAVE__obstack_newchunk && !__LOCAL_obstack_alloc_failed_handler && !__CRT_HAVE_exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE__exit && !__CRT_HAVE__Exit && !__CRT_HAVE_xexit */
#endif /* !__local_obstack_printer_defined */
