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
#ifndef _I386_KOS_KOS_BITS_SYSCALL_INFO64_H
#define _I386_KOS_KOS_BITS_SYSCALL_INFO64_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>
#include <hybrid/host.h>

#ifdef __x86_64__
#define OFFSET_RPC_SYSCALL_INFO_FLAGS OFFSET_RPC_SYSCALL_INFO64_FLAGS
#define OFFSET_RPC_SYSCALL_INFO_SYSNO OFFSET_RPC_SYSCALL_INFO64_SYSNO
#define OFFSET_RPC_SYSCALL_INFO_REG   OFFSET_RPC_SYSCALL_INFO64_REG
#define SIZEOF_RPC_SYSCALL_INFO       SIZEOF_RPC_SYSCALL_INFO64
#define rpc_syscall_info64            rpc_syscall_info
#endif /* __x86_64__ */

#define OFFSET_RPC_SYSCALL_INFO64_FLAGS  0
#define OFFSET_RPC_SYSCALL_INFO64_SYSNO  8
#define OFFSET_RPC_SYSCALL_INFO64_REG(i) (((i) + 2) * 8)
#define SIZEOF_RPC_SYSCALL_INFO64        64

#ifdef __CC__
__DECL_BEGIN

struct rpc_syscall_info64 /*[PREFIX(rsi_)]*/ {
	__UINT64_TYPE__  rsi_flags;   /* System call invocation flags (Set of `RPC_SYSCALL_INFO_F*') */
	__UINT64_TYPE__  rsi_sysno;   /* The system call vector that got invoked. */
	__UINT64_TYPE__  rsi_regs[6]; /* Arguments passed to the system call.
	                               * NOTE: You may validate any argument by testing for `RPC_SYSCALL_INFO_FREGVALID(i)' */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_BITS_SYSCALL_INFO64_H */
