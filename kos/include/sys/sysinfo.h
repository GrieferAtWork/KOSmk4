/* HASH CRC-32:0xae89a117 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _SYS_SYSINFO_H
#define _SYS_SYSINFO_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <linux/kernel.h>

__SYSDECL_BEGIN

#ifdef __CC__
#ifdef __CRT_HAVE_sysinfo
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sysinfo,(struct sysinfo *__info),(__info))
#endif /* sysinfo... */
#ifdef __CRT_HAVE_get_nprocs_conf
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_RPC,get_nprocs_conf,(void),())
#endif /* get_nprocs_conf... */
#ifdef __CRT_HAVE_get_nprocs
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_RPC,get_nprocs,(void),())
#endif /* get_nprocs... */
#ifdef __CRT_HAVE_get_phys_pages
__CDECLARE(__ATTR_WUNUSED,__INTPTR_TYPE__,__NOTHROW_RPC,get_phys_pages,(void),())
#endif /* get_phys_pages... */
#ifdef __CRT_HAVE_get_avphys_pages
__CDECLARE(__ATTR_WUNUSED,__INTPTR_TYPE__,__NOTHROW_RPC,get_avphys_pages,(void),())
#endif /* get_avphys_pages... */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_SYSINFO_H */
