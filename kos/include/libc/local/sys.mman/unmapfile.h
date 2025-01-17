/* HASH CRC-32:0x524ea211 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_unmapfile_defined
#define __local_unmapfile_defined
#include <__crt.h>
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <bits/crt/mapfile.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_munmap_defined
#define __local___localdep_munmap_defined
#ifdef __CRT_HAVE_munmap
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_NONE(1),int,__NOTHROW_NCX,__localdep_munmap,(void *__addr, __SIZE_TYPE__ __len),munmap,(__addr,__len))
#elif defined(__CRT_HAVE___munmap)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_NONE(1),int,__NOTHROW_NCX,__localdep_munmap,(void *__addr, __SIZE_TYPE__ __len),__munmap,(__addr,__len))
#elif defined(__CRT_HAVE___libc_munmap)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_NONE(1),int,__NOTHROW_NCX,__localdep_munmap,(void *__addr, __SIZE_TYPE__ __len),__libc_munmap,(__addr,__len))
#else /* ... */
#undef __local___localdep_munmap_defined
#endif /* !... */
#endif /* !__local___localdep_munmap_defined */
__LOCAL_LIBC(unmapfile) __ATTR_INOUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unmapfile))(struct mapfile *__restrict __mapping) {
	if (__mapping->__mf_mapsize) {
#if defined(__CRT_HAVE_munmap) || defined(__CRT_HAVE___munmap) || defined(__CRT_HAVE___libc_munmap)
		return (__NAMESPACE_LOCAL_SYM __localdep_munmap)(__mapping->mf_addr, __mapping->__mf_mapsize);
#endif /* __CRT_HAVE_munmap || __CRT_HAVE___munmap || __CRT_HAVE___libc_munmap */
	} else {
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__mapping->mf_addr);
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_unmapfile_defined
#define __local___localdep_unmapfile_defined
#define __localdep_unmapfile __LIBC_LOCAL_NAME(unmapfile)
#endif /* !__local___localdep_unmapfile_defined */
#else /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
#undef __local_unmapfile_defined
#endif /* !__CRT_HAVE_free && !__CRT_HAVE_cfree && !__CRT_HAVE___libc_free */
#endif /* !__local_unmapfile_defined */
