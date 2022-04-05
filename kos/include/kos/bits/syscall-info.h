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
#ifndef _KOS_BITS_SYSCALL_INFO_H
#define _KOS_BITS_SYSCALL_INFO_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#define OFFSET_RPC_SYSCALL_INFO_FLAGS  0
#define OFFSET_RPC_SYSCALL_INFO_SYSNO  __SIZEOF_POINTER__
#define OFFSET_RPC_SYSCALL_INFO_REG(i) (((i) + 2) * __SIZEOF_POINTER__)
#define SIZEOF_RPC_SYSCALL_INFO        (8 * __SIZEOF_POINTER__)

#ifdef __CC__
__DECL_BEGIN

struct rpc_syscall_info /*[PREFIX(rsi_)]*/ {
	__UINTPTR_TYPE__ rsi_flags;   /* System call invocation flags (Set of `RPC_SYSCALL_INFO_F*') */
	__UINTPTR_TYPE__ rsi_sysno;   /* The system call vector that got invoked. */
	__UINTPTR_TYPE__ rsi_regs[6]; /* Arguments passed to the system call.
	                               * NOTE: You may validate any argument by testing for `RPC_SYSCALL_INFO_FREGVALID(i)' */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_BITS_SYSCALL_INFO_H */
