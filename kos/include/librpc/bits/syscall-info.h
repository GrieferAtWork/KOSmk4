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
#ifndef _LIBRPC_BITS_SYSCALL_INFO_H
#define _LIBRPC_BITS_SYSCALL_INFO_H 1

#include <__stdinc.h>
#include <bits/types.h>

__DECL_BEGIN

#define OFFSET_RPC_SYSCALL_INFO_FLAGS      0
#define OFFSET_RPC_SYSCALL_INFO_SYSNO      __SIZEOF_SYSCALL_LONG_T__
#define OFFSET_RPC_SYSCALL_INFO_ARG(i)  (((i) + 2) * __SIZEOF_SYSCALL_LONG_T__)
#define SIZEOF_RPC_SYSCALL_INFO           (8 * __SIZEOF_SYSCALL_LONG_T__)
#ifndef __rpc_syscall_info_defined
#define __rpc_syscall_info_defined 1
#ifdef __CC__
struct rpc_syscall_info {
	/* Structure pushed by `RPC_PROGRAM_OP_psh_sys' */
	__syscall_ulong_t  rsi_flags;   /* System call invocation flags (Set of `RPC_SYSCALL_INFO_F*') */
	__syscall_ulong_t  rsi_sysno;   /* The system call vector that got invoked. */
	__syscall_ulong_t  rsi_args[6]; /* Arguments passed to the system call.
	                                 * NOTE: You may validate any argument by testing for `RPC_SYSCALL_INFO_FARGVALID(i)' */
};
#endif /* __CC__ */
#endif /* !__rpc_syscall_info_defined */

__DECL_END

#endif /* !_LIBRPC_BITS_SYSCALL_INFO_H */
