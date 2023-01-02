/* HASH CRC-32:0x85c01c23 */
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
/* (#) Portability: OpenSolaris (/usr/src/uts/common/sys/systeminfo.h) */
/* (#) Portability: mintlib     (/include/sys/systeminfo.h) */
#ifndef _SYS_SYSTEMINFO_H
#define _SYS_SYSTEMINFO_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <asm/os/utsname.h>

#define SI_SYSNAME             1   /* s.a. `struct utsname::sysname' */
#define SI_HOSTNAME            2   /* s.a. `gethostname(3)' */
#define SI_RELEASE             3   /* s.a. `struct utsname::release' */
#define SI_VERSION             4   /* s.a. `struct utsname::version' */
#define SI_MACHINE             5   /* s.a. `struct utsname::machine' */
#define SI_ARCHITECTURE        6   /* s.a. `getauxval(AT_BASE_PLATFORM)' */
#define SI_HW_SERIAL           7   /* ??? */
#define SI_HW_PROVIDER         8   /* ??? */
#define SI_SRPC_DOMAIN         9   /* s.a. `getdomainname(2)' */
#define SI_SET_HOSTNAME        258 /* s.a. `sethostname(2)' */
#define SI_SET_SRPC_DOMAIN     265 /* s.a. `setdomainname(2)' */
#define SI_PLATFORM            513 /* s.a. `getauxval(AT_PLATFORM)' */
#define SI_ISALIST             514 /* ??? */
#define SI_DHCP_CACHE          515 /* ??? */
#define SI_ARCHITECTURE_32     516 /* 32-bit arch name */
#define SI_ARCHITECTURE_64     517 /* 64-bit arch name */
#define SI_ARCHITECTURE_K      518 /* s.a. `getauxval(AT_BASE_PLATFORM)' */
#define SI_ARCHITECTURE_NATIVE 519 /* s.a. `getauxval(AT_PLATFORM)' */

//???#ifndef HW_INVALID_HOSTID
//???#define HW_INVALID_HOSTID 0xffffffff
//???#endif   /*   !HW_INVALID_HOSTID  */
//???#ifndef HW_HOSTID_LEN
//???#define HW_HOSTID_LEN 11 /* == strlen(sprintf("%d", HW_INVALID_HOSTID)) + 1 */
//???#endif /* !HW_HOSTID_LEN */

#if !defined(DOM_NM_LN) && defined(_UTSNAME_DOMAIN_LENGTH)
#define DOM_NM_LN _UTSNAME_DOMAIN_LENGTH
#endif /* !DOM_NM_LN && _UTSNAME_DOMAIN_LENGTH */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __sysinfo_defined
#define __sysinfo_defined
#if defined(__CRT_HAVE_sysinfo) && defined(__solaris__)
__CDECLARE(,int,__NOTHROW_NCX,sysinfo,(__STDC_INT_AS_UINT_T __command, char *__buf, __STDC_LONG_AS_SIZE_T __buflen),(__command,__buf,__buflen))
#elif defined(__CRT_HAVE___solaris_sysinfo)
__CREDIRECT(,int,__NOTHROW_NCX,sysinfo,(__STDC_INT_AS_UINT_T __command, char *__buf, __STDC_LONG_AS_SIZE_T __buflen),__solaris_sysinfo,(__command,__buf,__buflen))
#else /* ... */
#undef __sysinfo_defined
#endif /* !... */
#endif /* !__sysinfo_defined */
__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_SYSTEMINFO_H */
