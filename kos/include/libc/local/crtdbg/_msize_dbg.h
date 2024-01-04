/* HASH CRC-32:0x849a159b */
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
#ifndef __local__msize_dbg_defined
#define __local__msize_dbg_defined
#include <__crt.h>
#if defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_malloc_usable_size_defined
#define __local___localdep_malloc_usable_size_defined
#ifdef __CRT_HAVE_malloc_usable_size
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_malloc_usable_size,(void *__restrict __mallptr),malloc_usable_size,(__mallptr))
#elif defined(__CRT_HAVE__msize)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_malloc_usable_size,(void *__restrict __mallptr),_msize,(__mallptr))
#else /* ... */
#undef __local___localdep_malloc_usable_size_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_usable_size_defined */
__LOCAL_LIBC(_msize_dbg) __ATTR_PURE __ATTR_WUNUSED __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_msize_dbg))(void *__ptr, int __block_type) {
	(void)__block_type;
	return (__NAMESPACE_LOCAL_SYM __localdep_malloc_usable_size)(__ptr);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__msize_dbg_defined
#define __local___localdep__msize_dbg_defined
#define __localdep__msize_dbg __LIBC_LOCAL_NAME(_msize_dbg)
#endif /* !__local___localdep__msize_dbg_defined */
#else /* __CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize */
#undef __local__msize_dbg_defined
#endif /* !__CRT_HAVE_malloc_usable_size && !__CRT_HAVE__msize */
#endif /* !__local__msize_dbg_defined */
