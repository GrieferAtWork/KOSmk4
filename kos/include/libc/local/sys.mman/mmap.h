/* HASH CRC-32:0xfe4323d3 */
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
#ifndef __local_mmap_defined
#define __local_mmap_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_mmap64) || defined(__CRT_HAVE_mmap)
#include <features.h>
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __FS_TYPE(pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __FS_TYPE(off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_mmap32_defined) && defined(__CRT_HAVE_mmap)
#define __local___localdep_mmap32_defined
__CREDIRECT(__ATTR_ACCESS_NONE(1),void *,__NOTHROW_NCX,__localdep_mmap32,(void *__addr, __SIZE_TYPE__ __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __off32_t __offset),mmap,(__addr,__len,__prot,__flags,__fd,__offset))
#endif /* !__local___localdep_mmap32_defined && __CRT_HAVE_mmap */
#ifndef __local___localdep_mmap64_defined
#define __local___localdep_mmap64_defined
#if defined(__CRT_HAVE_mmap) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_NONE(1),void *,__NOTHROW_NCX,__localdep_mmap64,(void *__addr, __SIZE_TYPE__ __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __PIO_OFFSET64 __offset),mmap,(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_mmap64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_NONE(1),void *,__NOTHROW_NCX,__localdep_mmap64,(void *__addr, __SIZE_TYPE__ __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __PIO_OFFSET64 __offset),mmap64,(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_mmap)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.mman/mmap64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mmap64 __LIBC_LOCAL_NAME(mmap64)
#else /* ... */
#undef __local___localdep_mmap64_defined
#endif /* !... */
#endif /* !__local___localdep_mmap64_defined */
__LOCAL_LIBC(mmap) __ATTR_WUNUSED __ATTR_ACCESS_NONE(1) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mmap))(void *__addr, __SIZE_TYPE__ __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __PIO_OFFSET __offset) {

	return (__NAMESPACE_LOCAL_SYM __localdep_mmap64)(__addr, __len, __prot, __flags, __fd, (__PIO_OFFSET64)__offset);



}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mmap_defined
#define __local___localdep_mmap_defined
#define __localdep_mmap __LIBC_LOCAL_NAME(mmap)
#endif /* !__local___localdep_mmap_defined */
#else /* __CRT_HAVE_mmap64 || __CRT_HAVE_mmap */
#undef __local_mmap_defined
#endif /* !__CRT_HAVE_mmap64 && !__CRT_HAVE_mmap */
#endif /* !__local_mmap_defined */
