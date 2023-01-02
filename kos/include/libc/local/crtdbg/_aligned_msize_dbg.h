/* HASH CRC-32:0xd4e169d6 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__aligned_msize_dbg_defined
#define __local__aligned_msize_dbg_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__aligned_msize_defined
#define __local___localdep__aligned_msize_defined
#ifdef __CRT_HAVE__aligned_msize
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep__aligned_msize,(void *__aligned_mallptr, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),_aligned_msize,(__aligned_mallptr,__min_alignment,__offset))
#else /* __CRT_HAVE__aligned_msize */
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_malloc/_aligned_msize.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__aligned_msize __LIBC_LOCAL_NAME(_aligned_msize)
#endif /* !__CRT_HAVE__aligned_msize */
#endif /* !__local___localdep__aligned_msize_defined */
__LOCAL_LIBC(_aligned_msize_dbg) __ATTR_PURE __ATTR_WUNUSED __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_aligned_msize_dbg))(void *__ptr, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) {
	return (__NAMESPACE_LOCAL_SYM __localdep__aligned_msize)(__ptr, __min_alignment, __offset);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__aligned_msize_dbg_defined
#define __local___localdep__aligned_msize_dbg_defined
#define __localdep__aligned_msize_dbg __LIBC_LOCAL_NAME(_aligned_msize_dbg)
#endif /* !__local___localdep__aligned_msize_dbg_defined */
#endif /* !__local__aligned_msize_dbg_defined */
