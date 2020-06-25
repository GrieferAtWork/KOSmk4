/* HASH CRC-32:0x454e9295 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
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
#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sysinfo,(struct sysinfo *__info),(__info))
__CDECLARE_OPT(__ATTR_WUNUSED,int,__NOTHROW_RPC,get_nprocs_conf,(void),())
__CDECLARE_OPT(__ATTR_WUNUSED,int,__NOTHROW_RPC,get_nprocs,(void),())
__CDECLARE_OPT(__ATTR_WUNUSED,__INTPTR_TYPE__,__NOTHROW_RPC,get_phys_pages,(void),())
__CDECLARE_OPT(__ATTR_WUNUSED,__INTPTR_TYPE__,__NOTHROW_RPC,get_avphys_pages,(void),())
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_SYSINFO_H */
