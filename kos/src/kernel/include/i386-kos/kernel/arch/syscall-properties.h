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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_SYSCALL_PROPERTIES_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_SYSCALL_PROPERTIES_H 1

#include <kernel/compiler.h>

#undef KERNEL_SYSCALL_PROPERTIES_COMPAT_ALIAS
#ifdef __CC__
#include <hybrid/host.h>

#ifdef __x86_64__
#include <hybrid/typecore.h>

/* For `__NR32FEAT_SYSCALL_REGISTER_MAX_COUNT': */
#ifndef __NR32FEAT_DEFINED_SYSCALL_REGISTER_COUNT
#undef __WANT_SYSCALL_REGISTER_COUNT
#define __WANT_SYSCALL_REGISTER_COUNT 1
#include <asm/syscalls32_d.h>
#endif /* !__NR32FEAT_DEFINED_SYSCALL_REGISTER_COUNT */

DECL_BEGIN


#if __NR32_syscall0_min == 0
#define __KERNEL_SYSCALL32_ISTABLE0(sysno) (sysno) <= __NR32_syscall0_max
#else /* __NR32_syscall0_min == 0 */
#define __KERNEL_SYSCALL32_ISTABLE0(sysno) ((sysno) >= __NR32_syscall0_min && (sysno) <= __NR32_syscall0_max)
#endif /* __NR32_syscall0_min != 0 */

/* Invoke `callback(table_index, __VA_ARGS__)' for `sysno'
 * Note that `table_index' is a preprocessor-time literal suitable for token concat!
 * If   `sysno'  isn't  apart   of  any  defined   table,  invoke  `error'  instead. */
#if __NR32FEAT_SYSCALL_TABLE_COUNT == 3
#define __kernel_syscall32_withtable(sysno, error, callback, ...)           \
	(__KERNEL_SYSCALL32_ISTABLE0(sysno)                                     \
	 ? callback(0, __VA_ARGS__)                                             \
	 : ((sysno) >= __NR32_syscall1_min && (sysno) <= __NR32_syscall1_max)   \
	   ? callback(1, __VA_ARGS__)                                           \
	   : ((sysno) >= __NR32_syscall2_min && (sysno) <= __NR32_syscall2_max) \
	     ? callback(2, __VA_ARGS__)                                         \
	     : error)
#elif __NR32FEAT_SYSCALL_TABLE_COUNT == 2
#define __kernel_syscall32_withtable(sysno, error, callback, ...)         \
	(__KERNEL_SYSCALL32_ISTABLE0(sysno)                                   \
	 ? callback(0, __VA_ARGS__)                                           \
	 : ((sysno) >= __NR32_syscall1_min && (sysno) <= __NR32_syscall1_max) \
	   ? callback(1, __VA_ARGS__)                                         \
	   : error)
#elif __NR32FEAT_SYSCALL_TABLE_COUNT == 1
#define __kernel_syscall32_withtable(sysno, error, callback, ...) \
	(__KERNEL_SYSCALL32_ISTABLE0(sysno)                           \
	 ? callback(0, __VA_ARGS__)                                   \
	 : error)
#else /* __NR32FEAT_SYSCALL_TABLE_COUNT == ... */
#error "Unsupported number of system call tables"
#endif /* __NR32FEAT_SYSCALL_TABLE_COUNT != ... */

#define DEFINE_KERNEL_SYSCALL_TABLES_METADATA(id)                     \
	DATDEF __UINT8_TYPE__ const kernel_syscall##id##_restartmode32[]; \
	DATDEF __UINT8_TYPE__ const kernel_syscall##id##_iscp32[];        \
	DATDEF __UINT8_TYPE__ const kernel_syscall##id##_regcnt32[];
__NR32FEAT_SYSCALL_TABLE_FOREACH(DEFINE_KERNEL_SYSCALL_TABLES_METADATA)
#undef DEFINE_KERNEL_SYSCALL_TABLES_METADATA


/* Check if a given `sysno' system call is a cancellation point. */
#define kernel_syscall32_iscp(sysno) \
	__kernel_syscall32_withtable(sysno, 0, __kernel_syscall32_iscp_impl, sysno)
#define __kernel_syscall32_iscp_impl(table, sysno) \
	_kernel_private_syscall_iscp(kernel_syscall##table##_iscp32, (sysno)-__NR32_syscall##table##_min)

/* Return the restart mode used for `sysno' (one of `SYSCALL_RESTART_MODE_*'). */
#define kernel_syscall32_restartmode(sysno) \
	__kernel_syscall32_withtable(sysno, 0, __kernel_syscall32_restartmode_impl, sysno)
#define __kernel_syscall32_restartmode_impl(table, sysno) \
	_kernel_private_syscall_restartmode(kernel_syscall##table##_restartmode32, (sysno)-__NR32_syscall##table##_min)

/* Return the number of registers table by `sysno' (<= `__NR32FEAT_SYSCALL_REGISTER_MAX_COUNT') */
#define kernel_syscall32_regcnt(sysno) \
	__kernel_syscall32_withtable(sysno, __NR32FEAT_SYSCALL_REGISTER_MAX_COUNT, __kernel_syscall32_regcnt_impl, sysno)
#define __kernel_syscall32_regcnt_impl(table, sysno) \
	_kernel_private_syscall_regcnt(kernel_syscall##table##_regcnt32, (sysno)-__NR32_syscall##table##_min)

/* Check if a given system call `sysno' has a double-wide return
 * value (i.e.  the  return  value is  passed  in  2  registers) */
#define kernel_syscall32_doublewide(sysno) \
	__kernel_syscall32_withtable(sysno, 0, __kernel_syscall32_doublewide_impl, sysno)
#define __kernel_syscall32_doublewide_impl(table, sysno) \
	_kernel_private_syscall_doublewide(kernel_syscall##table##_regcnt32, (sysno)-__NR32_syscall##table##_min)

#define kernel_syscall64_iscp        _kernel_syscall_iscp
#define kernel_syscall64_restartmode _kernel_syscall_restartmode
#define kernel_syscall64_regcnt      _kernel_syscall_regcnt
#define kernel_syscall64_doublewide  _kernel_syscall_doublewide


/* For compatibility mode, we need to look at the RPC syscall info method
 * to figure out which namespace  the encoded system call number  belongs
 * to (either 32-bit, or 64-bit) */
#define _rpc_syscall_info_iscompat(sc_info) \
	(((sc_info)->rsi_flags & RPC_SYSCALL_INFO_METHOD_F3264) == RPC_SYSCALL_INFO_METHOD_F32)
#define kernel_syscall_iscp(sc_info)               \
	(_rpc_syscall_info_iscompat(sc_info)           \
	 ? kernel_syscall32_iscp((sc_info)->rsi_sysno) \
	 : kernel_syscall64_iscp((sc_info)->rsi_sysno))
#define kernel_syscall_restartmode(sc_info)               \
	(_rpc_syscall_info_iscompat(sc_info)                  \
	 ? kernel_syscall32_restartmode((sc_info)->rsi_sysno) \
	 : kernel_syscall64_restartmode((sc_info)->rsi_sysno))
#define kernel_syscall_regcnt(sc_info)               \
	(_rpc_syscall_info_iscompat(sc_info)             \
	 ? kernel_syscall32_regcnt((sc_info)->rsi_sysno) \
	 : kernel_syscall64_regcnt((sc_info)->rsi_sysno))
#define kernel_syscall_doublewide(sc_info)               \
	(_rpc_syscall_info_iscompat(sc_info)                 \
	 ? kernel_syscall32_doublewide((sc_info)->rsi_sysno) \
	 : kernel_syscall64_doublewide((sc_info)->rsi_sysno))

DECL_END

/* Enable compatibility-mode alias properties */
#define KERNEL_SYSCALL_PROPERTIES_COMPAT_ALIAS 32

#define kernel_syscall0_iscp64        kernel_syscall0_iscp
#define kernel_syscall0_restartmode64 kernel_syscall0_restartmode
#define kernel_syscall0_regcnt64      kernel_syscall0_regcnt
#define kernel_syscall1_iscp64        kernel_syscall1_iscp
#define kernel_syscall1_restartmode64 kernel_syscall1_restartmode
#define kernel_syscall1_regcnt64      kernel_syscall1_regcnt
#else /* __x86_64__ */
#define kernel_syscall32_iscp         _kernel_syscall_iscp
#define kernel_syscall32_restartmode  _kernel_syscall_restartmode
#define kernel_syscall32_regcnt       _kernel_syscall_regcnt
#define kernel_syscall32_doublewide   _kernel_syscall_doublewide
#define kernel_syscall0_iscp32        kernel_syscall0_iscp
#define kernel_syscall0_restartmode32 kernel_syscall0_restartmode
#define kernel_syscall0_regcnt32      kernel_syscall0_regcnt
#define kernel_syscall1_iscp32        kernel_syscall1_iscp
#define kernel_syscall1_restartmode32 kernel_syscall1_restartmode
#define kernel_syscall1_regcnt32      kernel_syscall1_regcnt
#endif /* !__x86_64__ */
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_SYSCALL_PROPERTIES_H */
