/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_OS_KOS_EPOLL_H
#define _BITS_OS_KOS_EPOLL_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>

__DECL_BEGIN

#ifdef __CC__
#ifndef __EPOLL_PACKED
#define __EPOLL_PACKED __ATTR_PACKED
#endif /* !__EPOLL_PACKED */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("ptr")
#pragma push_macro("fd")
#pragma push_macro("u32")
#pragma push_macro("u64")
#pragma push_macro("events")
#pragma push_macro("data")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef ptr
#undef fd
#undef u32
#undef u64
#undef events
#undef data

#if defined(__KOS__) && defined(__USE_KOS_KERNEL)
/* Parameter structure for `EPOLL_CTL_RPC_PROG' */
struct epoll_rpc_program {
	__uint64_t erp_target;          /* Target PID/TID */
	__uint64_t erp_mode;            /* RPC mode (same as the `mode' argument of `sys_rpc_schedule(2)') */
	__uint64_t erp_prog;            /* RPC program pointer (set as `erp_prog = (uint64_t)(uintptr_t)(void *)prog') */
	__uint64_t erp_params;          /* RPC program parameters pointer (set as `erp_prog = (uint64_t)(uintptr_t)(void **)prog') */
	__uint64_t erp_max_param_count; /* RPC program max parameter count */
};
#endif /* __KOS__ && __USE_KOS_KERNEL */


union epoll_data {
	void      *ptr;
	__fd_t     fd;
	__uint32_t u32;
	__uint64_t u64;
};

struct __EPOLL_PACKED epoll_event {
	__uint32_t       events; /* Epoll events (Set of `EPOLL*'; s.a. `EPOLL_EVENTS') */
	union epoll_data data;   /* User data variable */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("data")
#pragma pop_macro("events")
#pragma pop_macro("u64")
#pragma pop_macro("u32")
#pragma pop_macro("fd")
#pragma pop_macro("ptr")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* __CC__ */

__DECL_END

#endif /* !_BITS_OS_KOS_EPOLL_H */
