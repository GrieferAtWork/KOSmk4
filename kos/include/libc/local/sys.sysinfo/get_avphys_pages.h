/* HASH CRC-32:0x5a41ae6 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_get_avphys_pages_defined
#define __local_get_avphys_pages_defined 1
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <asm/pagesize.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <asm/pagesize.h>
#if defined(__CRT_HAVE_sysinfo) && !defined(__solaris__) && (defined(__CRT_HAVE_getpagesize) || defined(__CRT_HAVE___getpagesize) || defined(__ARCH_PAGESIZE))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: getpagesize from unistd */
#ifndef __local___localdep_getpagesize_defined
#define __local___localdep_getpagesize_defined 1
#ifdef __CRT_HAVE_getpagesize
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,__localdep_getpagesize,(void),getpagesize,())
#elif defined(__CRT_HAVE___getpagesize)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,__localdep_getpagesize,(void),__getpagesize,())
#elif defined(__ARCH_PAGESIZE)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/getpagesize.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
#define __localdep_getpagesize __LIBC_LOCAL_NAME(getpagesize)
#else /* ... */
#undef __local___localdep_getpagesize_defined
#endif /* !... */
#endif /* !__local___localdep_getpagesize_defined */
/* Dependency: sysinfo from sys.sysinfo */
#ifndef __local___localdep_sysinfo_defined
#define __local___localdep_sysinfo_defined 1
__NAMESPACE_LOCAL_END
#include <linux/sysinfo.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sysinfo(2)
 * Return current system information */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_sysinfo,(struct sysinfo *__info),sysinfo,(__info))
#endif /* !__local___localdep_sysinfo_defined */
__NAMESPACE_LOCAL_END
#include <linux/sysinfo.h>
__NAMESPACE_LOCAL_BEGIN
/* >> get_avphys_pages(3)
 * Return the total # of free pages of physical memory */
__LOCAL_LIBC(get_avphys_pages) __ATTR_WUNUSED __INTPTR_TYPE__
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(get_avphys_pages))(void) {
	struct sysinfo __info;
	__UINTPTR_TYPE__ __result;
	__SIZE_TYPE__ __ps;
	if (__localdep_sysinfo(&__info))
		return -1;
	__ps = __localdep_getpagesize();
	while (__info.mem_unit > 1 && __ps > 1) {
		__info.mem_unit >>= 1;
		__ps >>= 1;
	}
	__result = __info.freeram * __info.mem_unit;
	while (__ps > 1) {
		__result >>= 1;
		__ps >>= 1;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_get_avphys_pages_defined
#define __local___localdep_get_avphys_pages_defined 1
#define __localdep_get_avphys_pages __LIBC_LOCAL_NAME(get_avphys_pages)
#endif /* !__local___localdep_get_avphys_pages_defined */
#else /* __CRT_HAVE_sysinfo && !__solaris__ && (__CRT_HAVE_getpagesize || __CRT_HAVE___getpagesize || __ARCH_PAGESIZE) */
#undef __local_get_avphys_pages_defined
#endif /* !__CRT_HAVE_sysinfo || __solaris__ || (!__CRT_HAVE_getpagesize && !__CRT_HAVE___getpagesize && !__ARCH_PAGESIZE) */
#endif /* !__local_get_avphys_pages_defined */
