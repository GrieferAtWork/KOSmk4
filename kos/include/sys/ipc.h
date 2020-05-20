/* HASH CRC-32:0xd9eced6e */
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
#ifndef _SYS_IPC_H
#define _SYS_IPC_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <bits/ipctypes.h>
#include <bits/ipc.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __uid_t_defined
#define __uid_t_defined 1
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */

#ifndef __gid_t_defined
#define __gid_t_defined 1
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */

#ifndef __mode_t_defined
#define __mode_t_defined 1
typedef __mode_t mode_t; /* INode type (Set of `S_*' from `<fcntl.h>' or `<sys/stat.h>') */
#endif /* !__mode_t_defined */

#ifndef __key_t_defined
#define __key_t_defined 1
typedef __key_t key_t;
#endif /* !__key_t_defined */

#ifdef __CRT_HAVE_ftok
/* Generates key for System V style IPC */
__CDECLARE(__ATTR_NONNULL((1)),key_t,__NOTHROW_RPC,ftok,(char const *__pathname, int __proj_id),(__pathname,__proj_id))
#endif /* ftok... */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_IPC_H */
