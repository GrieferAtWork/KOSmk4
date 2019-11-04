/* HASH CRC-32:0x629ca39a */
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
#ifndef __local__aligned_offset_malloc_dbg_defined
#if defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE__aligned_offset_malloc)
#define __local__aligned_offset_malloc_dbg_defined 1
/* Dependency: "_aligned_offset_malloc" from "stdlib" */
#ifndef ____localdep__aligned_offset_malloc_defined
#define ____localdep__aligned_offset_malloc_defined 1
#ifdef __CRT_HAVE__aligned_offset_malloc
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep__aligned_offset_malloc,(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),_aligned_offset_malloc,(__num_bytes,__min_alignment,__offset))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#include <local/stdlib/_aligned_offset_malloc.h>
#define __localdep__aligned_offset_malloc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_offset_malloc))
#else /* CUSTOM: _aligned_offset_malloc */
#undef ____localdep__aligned_offset_malloc_defined
#endif /* _aligned_offset_malloc... */
#endif /* !____localdep__aligned_offset_malloc_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_aligned_offset_malloc_dbg) __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_aligned_offset_malloc_dbg))(__SIZE_TYPE__ __num_bytes,
                                                                        __SIZE_TYPE__ __min_alignment,
                                                                        __SIZE_TYPE__ __offset,
                                                                        char const *__filename,
                                                                        int __line) {
#line 378 "kos/src/libc/magic/crtdbg.c"
	(void)__filename;
	(void)__line;
	return __localdep__aligned_offset_malloc(__num_bytes, __min_alignment, __offset);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE__aligned_offset_malloc) */
#endif /* !__local__aligned_offset_malloc_dbg_defined */
