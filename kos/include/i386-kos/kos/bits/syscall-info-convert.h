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
#ifndef _I386_KOS_KOS_BITS_SYSCALL_INFO_CONVERT_H
#define _I386_KOS_KOS_BITS_SYSCALL_INFO_CONVERT_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <libc/string.h>

#include "syscall-info32.h"
#include "syscall-info64.h"

#ifdef __CC__
__DECL_BEGIN

/* Convert between 32-bit and 64-bit `struct rpc_syscall_info' structures */
__LOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(rpc_syscall_info32_to_rpc_syscall_info32)(struct rpc_syscall_info32 const *__restrict __self,
                                                        struct rpc_syscall_info32 *__restrict __result,
                                                        unsigned int __max_regc __DFL(6)) {
	__libc_memcpy(__result, __self, OFFSET_RPC_SYSCALL_INFO32_REG(__max_regc));
}

__LOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(rpc_syscall_info64_to_rpc_syscall_info64)(struct rpc_syscall_info64 const *__restrict __self,
                                                        struct rpc_syscall_info64 *__restrict __result,
                                                        unsigned int __max_regc __DFL(6)) {
	__libc_memcpy(__result, __self, OFFSET_RPC_SYSCALL_INFO64_REG(__max_regc));
}

__LOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(rpc_syscall_info32_to_rpc_syscall_info64)(struct rpc_syscall_info32 const *__restrict __self,
                                                        struct rpc_syscall_info64 *__restrict __result,
                                                        unsigned int __max_regc __DFL(6)) {
	unsigned int __i;
	__result->rsi_flags = (__UINT64_TYPE__)__self->rsi_flags;
	__result->rsi_sysno = (__UINT64_TYPE__)__self->rsi_sysno;
	for (__i = 0; __i < __max_regc; ++__i) {
		__result->rsi_regs[__i] = (__UINT64_TYPE__)__self->rsi_regs[__i];
	}
}

__LOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(rpc_syscall_info64_to_rpc_syscall_info32)(struct rpc_syscall_info64 const *__restrict __self,
                                                        struct rpc_syscall_info32 *__restrict __result,
                                                        unsigned int __max_regc __DFL(6)) {
	unsigned int __i;
	__result->rsi_flags = (__UINT32_TYPE__)__self->rsi_flags;
	__result->rsi_sysno = (__UINT32_TYPE__)__self->rsi_sysno;
	for (__i = 0; __i < __max_regc; ++__i) {
		__result->rsi_regs[__i] = (__UINT32_TYPE__)__self->rsi_regs[__i];
	}
}

#ifdef __x86_64__
#define rpc_syscall_info64_to_rpc_syscall_info rpc_syscall_info64_to_rpc_syscall_info64
#define rpc_syscall_info32_to_rpc_syscall_info rpc_syscall_info32_to_rpc_syscall_info64
#define rpc_syscall_info_to_rpc_syscall_info32 rpc_syscall_info64_to_rpc_syscall_info32
#define rpc_syscall_info_to_rpc_syscall_info64 rpc_syscall_info64_to_rpc_syscall_info64
#else /* __x86_64__ */
#define rpc_syscall_info64_to_rpc_syscall_info rpc_syscall_info64_to_rpc_syscall_info32
#define rpc_syscall_info32_to_rpc_syscall_info rpc_syscall_info32_to_rpc_syscall_info32
#define rpc_syscall_info_to_rpc_syscall_info32 rpc_syscall_info32_to_rpc_syscall_info32
#define rpc_syscall_info_to_rpc_syscall_info64 rpc_syscall_info32_to_rpc_syscall_info64
#endif /* !__x86_64__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_BITS_SYSCALL_INFO_CONVERT_H */
