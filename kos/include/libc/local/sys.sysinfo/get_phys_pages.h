/* HASH CRC-32:0x86375b40 */
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
#ifndef __local_get_phys_pages_defined
#define __local_get_phys_pages_defined
#include <__crt.h>
#include <asm/pagesize.h>
#if ((defined(__CRT_HAVE_sysinfo) && !defined(__solaris__)) || defined(__CRT_HAVE___sysinfo) || defined(__CRT_HAVE___libc_sysinfo)) && (defined(__CRT_HAVE_getpagesize) || defined(__CRT_HAVE___getpagesize) || defined(__ARCH_PAGESIZE))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getpagesize_defined
#define __local___localdep_getpagesize_defined
#if defined(__CRT_HAVE_getpagesize) && defined(__ARCH_PAGESIZE)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,__localdep_getpagesize,(void),getpagesize,{ return __ARCH_PAGESIZE; })
#elif defined(__CRT_HAVE_getpagesize)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,__localdep_getpagesize,(void),getpagesize,())
#elif defined(__CRT_HAVE___getpagesize)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,__localdep_getpagesize,(void),__getpagesize,())
#elif defined(__ARCH_PAGESIZE)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __STDC_INT_AS_SIZE_T __NOTHROW(__LIBCCALL __localdep_getpagesize)(void) { return __ARCH_PAGESIZE; }
#else /* ... */
#undef __local___localdep_getpagesize_defined
#endif /* !... */
#endif /* !__local___localdep_getpagesize_defined */
#ifndef __local___localdep_sysinfo_defined
#define __local___localdep_sysinfo_defined
#if defined(__CRT_HAVE_sysinfo) && !defined(__solaris__)
__NAMESPACE_LOCAL_END
#include <linux/sysinfo.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_sysinfo,(struct sysinfo *__info),sysinfo,(__info))
#elif defined(__CRT_HAVE___sysinfo)
__NAMESPACE_LOCAL_END
#include <linux/sysinfo.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_sysinfo,(struct sysinfo *__info),__sysinfo,(__info))
#elif defined(__CRT_HAVE___libc_sysinfo)
__NAMESPACE_LOCAL_END
#include <linux/sysinfo.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_sysinfo,(struct sysinfo *__info),__libc_sysinfo,(__info))
#else /* ... */
#undef __local___localdep_sysinfo_defined
#endif /* !... */
#endif /* !__local___localdep_sysinfo_defined */
__NAMESPACE_LOCAL_END
#include <linux/sysinfo.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(get_phys_pages) __ATTR_WUNUSED __INTPTR_TYPE__
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(get_phys_pages))(void) {
	struct sysinfo __info;
	__UINTPTR_TYPE__ __result;
	__SIZE_TYPE__ __ps;
	if ((__NAMESPACE_LOCAL_SYM __localdep_sysinfo)(&__info))
		return -1;
	__ps = (__NAMESPACE_LOCAL_SYM __localdep_getpagesize)();
	while (__info.mem_unit > 1 && __ps > 1) {
		__info.mem_unit >>= 1;
		__ps >>= 1;
	}
	__result = (__UINTPTR_TYPE__)__info.totalram *
	         (__UINTPTR_TYPE__)__info.mem_unit;
	while (__ps > 1) {
		__result >>= 1;
		__ps >>= 1;
	}
	return (__INTPTR_TYPE__)__result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_get_phys_pages_defined
#define __local___localdep_get_phys_pages_defined
#define __localdep_get_phys_pages __LIBC_LOCAL_NAME(get_phys_pages)
#endif /* !__local___localdep_get_phys_pages_defined */
#else /* ((__CRT_HAVE_sysinfo && !__solaris__) || __CRT_HAVE___sysinfo || __CRT_HAVE___libc_sysinfo) && (__CRT_HAVE_getpagesize || __CRT_HAVE___getpagesize || __ARCH_PAGESIZE) */
#undef __local_get_phys_pages_defined
#endif /* ((!__CRT_HAVE_sysinfo || __solaris__) && !__CRT_HAVE___sysinfo && !__CRT_HAVE___libc_sysinfo) || (!__CRT_HAVE_getpagesize && !__CRT_HAVE___getpagesize && !__ARCH_PAGESIZE) */
#endif /* !__local_get_phys_pages_defined */
