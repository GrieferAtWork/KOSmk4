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
#ifndef _KOS_ASM_RPC_METHOD_H
#define _KOS_ASM_RPC_METHOD_H 1

#include <__stdinc.h>

#define RPC_SYSCALL_INFO_METHOD_SYSCALL   0x01 /* Normal system call */
#define RPC_SYSCALL_INFO_METHOD_SIGRETURN 0x02 /* System call was restarted as part of `sigreturn()' */
#define RPC_SYSCALL_INFO_METHOD_OTHER     0x03 /* Some other kind of system call invocation method */

#endif /* !_KOS_ASM_RPC_METHOD_H */
