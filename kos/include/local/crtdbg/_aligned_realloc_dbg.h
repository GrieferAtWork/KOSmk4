/* HASH CRC-32:0x41028314 */
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
#ifndef __local__aligned_realloc_dbg_defined
#if ((defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE__aligned_malloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE__aligned_free))) || defined(__CRT_HAVE__aligned_realloc)
#define __local__aligned_realloc_dbg_defined 1
/* Dependency: "_aligned_realloc" from "stdlib" */
#ifndef ____localdep__aligned_realloc_defined
#define ____localdep__aligned_realloc_defined 1
#ifdef __CRT_HAVE__aligned_realloc
__CREDIRECT(__ATTR_WUNUSED __ATTR_ALLOC_ALIGN(3) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep__aligned_realloc,(void *__aligned_mallptr, __SIZE_TYPE__ __newsize, __SIZE_TYPE__ __min_alignment),_aligned_realloc,(__aligned_mallptr,__newsize,__min_alignment))
#elif (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE__aligned_malloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE__aligned_free))
#include <local/stdlib/_aligned_realloc.h>
#define __localdep__aligned_realloc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_realloc))
#else /* CUSTOM: _aligned_realloc */
#undef ____localdep__aligned_realloc_defined
#endif /* _aligned_realloc... */
#endif /* !____localdep__aligned_realloc_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_aligned_realloc_dbg) __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(3) __ATTR_ALLOC_SIZE((2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_aligned_realloc_dbg))(void *__ptr,
                                                                  __SIZE_TYPE__ __num_bytes,
                                                                  __SIZE_TYPE__ __min_alignment,
                                                                  char const *__filename,
                                                                  int __line) {
#line 362 "kos/src/libc/magic/crtdbg.c"
	(void)__filename;
	(void)__line;
	return __localdep__aligned_realloc(__ptr, __num_bytes, __min_alignment);
}
__NAMESPACE_LOCAL_END
#endif /* ((__CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_posix_memalign || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_malloc || __CRT_HAVE__aligned_malloc) && (__CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE__aligned_free)) || __CRT_HAVE__aligned_realloc */
#endif /* !__local__aligned_realloc_dbg_defined */
