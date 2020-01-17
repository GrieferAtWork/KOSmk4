/* HASH CRC-32:0xa075aeaf */
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
#ifndef __local__recalloc_dbg_defined
#if (defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))) || defined(__CRT_HAVE__recalloc)
#define __local__recalloc_dbg_defined 1
/* Dependency: "_recalloc" from "stdlib" */
#ifndef ____localdep__recalloc_defined
#define ____localdep__recalloc_defined 1
#ifdef __CRT_HAVE__recalloc
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,__localdep__recalloc,(void *__mallptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),_recalloc,(__mallptr,__count,__num_bytes))
#elif defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <local/stdlib/_recalloc.h>
#define __localdep__recalloc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_recalloc))
#else /* CUSTOM: _recalloc */
#undef ____localdep__recalloc_defined
#endif /* _recalloc... */
#endif /* !____localdep__recalloc_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_recalloc_dbg) __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_recalloc_dbg))(void *__ptr,
                                                           __SIZE_TYPE__ __count,
                                                           __SIZE_TYPE__ __num_bytes,
                                                           int __block_type,
                                                           char const *__filename,
                                                           int __line) {
#line 316 "kos/src/libc/magic/crtdbg.c"
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return __localdep__recalloc(__ptr, __count, __num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_HAVE_realloc && (__CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize)) || __CRT_HAVE__recalloc */
#endif /* !__local__recalloc_dbg_defined */
