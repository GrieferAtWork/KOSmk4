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
%(c_prefix){
/* (#) Portability: OpenSolaris (/usr/src/uts/common/sys/systeminfo.h) */
/* (#) Portability: mintlib     (/include/sys/systeminfo.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.system.info")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/os/utsname.h>
)]%{

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

}

[[guard, exposed_name("sysinfo")]]
[[if(defined(__solaris__)), preferred_alias("sysinfo")]]
[[decl_include("<features.h>")]]
int __solaris_sysinfo(__STDC_INT_AS_UINT_T command, char *buf,
                      __STDC_LONG_AS_SIZE_T buflen);
/* TODO: Implement me! */



%{
__SYSDECL_END
#endif /* __CC__ */

}
