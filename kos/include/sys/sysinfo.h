/* HASH CRC-32:0x675b69c5 */
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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/sysinfo.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/sysinfo.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/sysinfo.h) */
/* (#) Portability: diet libc     (/include/sys/sysinfo.h) */
/* (#) Portability: musl libc     (/include/sys/sysinfo.h) */
/* (#) Portability: uClibc        (/include/sys/sysinfo.h) */
#ifndef _SYS_SYSINFO_H
#define _SYS_SYSINFO_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <linux/kernel.h>
#include <bits/types.h>


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __sysinfo_defined
#define __sysinfo_defined
#if defined(__CRT_HAVE_sysinfo) && !defined(__solaris__)
/* >> sysinfo(2)
 * Return current system information */
__CDECLARE(__ATTR_ACCESS_WR(1),int,__NOTHROW_NCX,sysinfo,(struct sysinfo *__info),(__info))
#elif defined(__CRT_HAVE___sysinfo)
/* >> sysinfo(2)
 * Return current system information */
__CREDIRECT(__ATTR_ACCESS_WR(1),int,__NOTHROW_NCX,sysinfo,(struct sysinfo *__info),__sysinfo,(__info))
#elif defined(__CRT_HAVE___libc_sysinfo)
/* >> sysinfo(2)
 * Return current system information */
__CREDIRECT(__ATTR_ACCESS_WR(1),int,__NOTHROW_NCX,sysinfo,(struct sysinfo *__info),__libc_sysinfo,(__info))
#else /* ... */
#undef __sysinfo_defined
#endif /* !... */
#endif /* !__sysinfo_defined */
/* >> get_nprocs_conf(3)
 * Return the # of configured online processors */
__CDECLARE_OPT(__ATTR_WUNUSED,int,__NOTHROW,get_nprocs_conf,(void),())
/* >> get_nprocs(3)
 * Return the # of currently online processors */
__CDECLARE_OPT(__ATTR_WUNUSED,int,__NOTHROW,get_nprocs,(void),())
#ifdef __CRT_HAVE_get_phys_pages
/* >> get_phys_pages(3)
 * Return the total # of pages of physical memory */
__CDECLARE(__ATTR_WUNUSED,__INTPTR_TYPE__,__NOTHROW,get_phys_pages,(void),())
#else /* __CRT_HAVE_get_phys_pages */
#include <asm/pagesize.h>
#if ((defined(__CRT_HAVE_sysinfo) && !defined(__solaris__)) || defined(__CRT_HAVE___sysinfo) || defined(__CRT_HAVE___libc_sysinfo)) && (defined(__CRT_HAVE_getpagesize) || defined(__CRT_HAVE___getpagesize) || defined(__ARCH_PAGESIZE))
#include <libc/local/sys.sysinfo/get_phys_pages.h>
/* >> get_phys_pages(3)
 * Return the total # of pages of physical memory */
__NAMESPACE_LOCAL_USING_OR_IMPL(get_phys_pages, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __INTPTR_TYPE__ __NOTHROW(__LIBCCALL get_phys_pages)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(get_phys_pages))(); })
#endif /* ((__CRT_HAVE_sysinfo && !__solaris__) || __CRT_HAVE___sysinfo || __CRT_HAVE___libc_sysinfo) && (__CRT_HAVE_getpagesize || __CRT_HAVE___getpagesize || __ARCH_PAGESIZE) */
#endif /* !__CRT_HAVE_get_phys_pages */
#ifdef __CRT_HAVE_get_avphys_pages
/* >> get_avphys_pages(3)
 * Return the total # of free pages of physical memory */
__CDECLARE(__ATTR_WUNUSED,__INTPTR_TYPE__,__NOTHROW,get_avphys_pages,(void),())
#else /* __CRT_HAVE_get_avphys_pages */
#include <asm/pagesize.h>
#if ((defined(__CRT_HAVE_sysinfo) && !defined(__solaris__)) || defined(__CRT_HAVE___sysinfo) || defined(__CRT_HAVE___libc_sysinfo)) && (defined(__CRT_HAVE_getpagesize) || defined(__CRT_HAVE___getpagesize) || defined(__ARCH_PAGESIZE))
#include <libc/local/sys.sysinfo/get_avphys_pages.h>
/* >> get_avphys_pages(3)
 * Return the total # of free pages of physical memory */
__NAMESPACE_LOCAL_USING_OR_IMPL(get_avphys_pages, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __INTPTR_TYPE__ __NOTHROW(__LIBCCALL get_avphys_pages)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(get_avphys_pages))(); })
#endif /* ((__CRT_HAVE_sysinfo && !__solaris__) || __CRT_HAVE___sysinfo || __CRT_HAVE___libc_sysinfo) && (__CRT_HAVE_getpagesize || __CRT_HAVE___getpagesize || __ARCH_PAGESIZE) */
#endif /* !__CRT_HAVE_get_avphys_pages */
__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_SYSINFO_H */
