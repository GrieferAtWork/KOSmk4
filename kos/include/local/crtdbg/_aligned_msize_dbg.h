/* HASH CRC-32:0x3a4edb1 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__aligned_msize_dbg_defined
#if 1
#define __local__aligned_msize_dbg_defined 1
/* Dependency: "_aligned_msize" from "stdlib" */
#ifndef ____localdep__aligned_msize_defined
#define ____localdep__aligned_msize_defined 1
#ifdef __CRT_HAVE__aligned_msize
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep__aligned_msize,(void *__aligned_mallptr, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),_aligned_msize,(__aligned_mallptr,__min_alignment,__offset))
#else /* LIBC: _aligned_msize */
#include <local/stdlib/_aligned_msize.h>
#define __localdep__aligned_msize (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_msize))
#endif /* _aligned_msize... */
#endif /* !____localdep__aligned_msize_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_aligned_msize_dbg) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_aligned_msize_dbg))(void *__ptr,
                                                                __SIZE_TYPE__ __min_alignment,
                                                                __SIZE_TYPE__ __offset) {
#line 345 "kos/src/libc/magic/crtdbg.c"
	return __localdep__aligned_msize(__ptr, __min_alignment, __offset);
}
__NAMESPACE_LOCAL_END
#endif /* 1 */
#endif /* !__local__aligned_msize_dbg_defined */
