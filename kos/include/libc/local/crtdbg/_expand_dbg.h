/* HASH CRC-32:0xef2f8f2 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__expand_dbg_defined
#define __local__expand_dbg_defined
#include <__crt.h>
#if defined(__CRT_HAVE_realloc_in_place) || defined(__CRT_HAVE__expand)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
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
__LOCAL_LIBC(_expand_dbg) __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_expand_dbg))(void *__ptr, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) {
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return (__NAMESPACE_LOCAL_SYM __localdep_realloc_in_place)(__ptr, __num_bytes);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__expand_dbg_defined
#define __local___localdep__expand_dbg_defined
#define __localdep__expand_dbg __LIBC_LOCAL_NAME(_expand_dbg)
#endif /* !__local___localdep__expand_dbg_defined */
#else /* __CRT_HAVE_realloc_in_place || __CRT_HAVE__expand */
#undef __local__expand_dbg_defined
#endif /* !__CRT_HAVE_realloc_in_place && !__CRT_HAVE__expand */
#endif /* !__local__expand_dbg_defined */
