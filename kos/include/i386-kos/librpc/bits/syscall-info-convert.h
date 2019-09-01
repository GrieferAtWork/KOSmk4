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
#ifndef _I386_KOS_LIBRPC_BITS_SYSCALL_INFO_CONVERT_H
#define _I386_KOS_LIBRPC_BITS_SYSCALL_INFO_CONVERT_H 1

#include <__stdinc.h>
#include "syscall-info32.h"
#include "syscall-info64.h"
#include <hybrid/typecore.h>

__DECL_BEGIN

/* Convert between 32-bit and 64-bit siginfo_t structures */
#ifdef __CC__

__LOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(rpc_syscall_info32_to_rpc_syscall_info64)(struct rpc_syscall_info64 *__restrict dst,
                                                        struct rpc_syscall_info32 const *__restrict src,
                                                        unsigned int max_argc __DFL(6)) {
	unsigned int i;
	dst->rsi_flags = (__UINT64_TYPE__)src->rsi_flags;
	dst->rsi_sysno = (__UINT64_TYPE__)src->rsi_sysno;
	for (i = 0; i < max_argc; ++i) {
		dst->rsi_args[i] = (__UINT64_TYPE__)src->rsi_args[i];
	}
}

__LOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(rpc_syscall_info64_to_rpc_syscall_info32)(struct rpc_syscall_info32 *__restrict dst,
                                                        struct rpc_syscall_info64 const *__restrict src,
                                                        unsigned int max_argc __DFL(6)) {
	unsigned int i;
	dst->rsi_flags = (__UINT32_TYPE__)src->rsi_flags;
	dst->rsi_sysno = (__UINT32_TYPE__)src->rsi_sysno;
	for (i = 0; i < max_argc; ++i) {
		dst->rsi_args[i] = (__UINT32_TYPE__)src->rsi_args[i];
	}
}

#endif /* __CC__ */


__DECL_END

#endif /* !_I386_KOS_LIBRPC_BITS_SYSCALL_INFO_CONVERT_H */
