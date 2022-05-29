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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_SYSCALL_PROPERTIES_H
#define GUARD_KERNEL_INCLUDE_KERNEL_SYSCALL_PROPERTIES_H 1

#include <kernel/compiler.h>

#include <hybrid/typecore.h>

#include <kernel/arch/syscall-properties.h>
#include <asm/unistd.h>
#include <bits/types.h>

/* For `__NRFEAT_SYSCALL_REGISTER_MAX_COUNT': */
#ifndef __NRFEAT_DEFINED_SYSCALL_REGISTER_COUNT
#undef __WANT_SYSCALL_REGISTER_COUNT
#define __WANT_SYSCALL_REGISTER_COUNT 1
#include <asm/syscalls.h>
#endif /* !__NRFEAT_DEFINED_SYSCALL_REGISTER_COUNT */


/* Restart codes. */
#define SYSCALL_RESTART_MODE_AUTO 0 /* Automatic restarting */
#define SYSCALL_RESTART_MODE_DONT 1 /* Don't restart */
#define SYSCALL_RESTART_MODE_MUST 2 /* Always restart */

#ifdef __CC__
DECL_BEGIN

#if __NR_syscall0_min == 0
#define _kernel_private_syscall_istable0(sysno) (sysno) <= __NR_syscall0_max
#else /* __NR_syscall0_min == 0 */
#define _kernel_private_syscall_istable0(sysno) ((sysno) >= __NR_syscall0_min && (sysno) <= __NR_syscall0_max)
#endif /* __NR_syscall0_min != 0 */

/* Invoke `callback(table_index, __VA_ARGS__)' for `sysno'
 * Note that `table_index' is a preprocessor-time literal suitable for token concat!
 * If   `sysno'  isn't  apart   of  any  defined   table,  invoke  `error'  instead. */
#if __NRFEAT_SYSCALL_TABLE_COUNT == 3
#define _kernel_private_syscall_withtable(sysno, error, callback, ...)  \
	(_kernel_private_syscall_istable0(sysno)                            \
	 ? callback(0, __VA_ARGS__)                                         \
	 : ((sysno) >= __NR_syscall1_min && (sysno) <= __NR_syscall1_max)   \
	   ? callback(1, __VA_ARGS__)                                       \
	   : ((sysno) >= __NR_syscall2_min && (sysno) <= __NR_syscall2_max) \
	     ? callback(2, __VA_ARGS__)                                     \
	     : error)
#elif __NRFEAT_SYSCALL_TABLE_COUNT == 2
#define _kernel_private_syscall_withtable(sysno, error, callback, ...) \
	(_kernel_private_syscall_istable0(sysno)                           \
	 ? callback(0, __VA_ARGS__)                                        \
	 : ((sysno) >= __NR_syscall1_min && (sysno) <= __NR_syscall1_max)  \
	   ? callback(1, __VA_ARGS__)                                      \
	   : error)
#elif __NRFEAT_SYSCALL_TABLE_COUNT == 1
#define _kernel_private_syscall_withtable(sysno, error, callback, ...) \
	(_kernel_private_syscall_istable0(sysno)                           \
	 ? callback(0, __VA_ARGS__)                                        \
	 : error)
#else /* __NRFEAT_SYSCALL_TABLE_COUNT == ... */
#error "Unsupported number of system call tables"
#endif /* __NRFEAT_SYSCALL_TABLE_COUNT != ... */

#define _DEFINE_KERNEL_SYSCALL_TABLES_METADATA(id)                  \
	DATDEF __UINT8_TYPE__ const kernel_syscall##id##_iscp[];        \
	DATDEF __UINT8_TYPE__ const kernel_syscall##id##_restartmode[]; \
	DATDEF __UINT8_TYPE__ const kernel_syscall##id##_regcnt[];
__NRFEAT_SYSCALL_TABLE_FOREACH(_DEFINE_KERNEL_SYSCALL_TABLES_METADATA)
#undef _DEFINE_KERNEL_SYSCALL_TABLES_METADATA

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL ATTR_CONST NONNULL((1)) __BOOL
NOTHROW(KCALL _kernel_private_syscall_iscp)(__UINT8_TYPE__ const *__restrict base,
                                            __syscall_ulong_t rel_sysno) {
	return (base[rel_sysno / 8] >> (rel_sysno % 8)) & 1;
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL ATTR_CONST NONNULL((1)) __UINT8_TYPE__
NOTHROW(KCALL _kernel_private_syscall_restartmode)(__UINT8_TYPE__ const *__restrict base,
                                                   __syscall_ulong_t rel_sysno) {
	return (base[rel_sysno / 4] >> (2 * (rel_sysno % 4))) & 3;
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL ATTR_CONST NONNULL((1)) __UINT8_TYPE__
NOTHROW(KCALL _kernel_private_syscall_regcnt)(__UINT8_TYPE__ const *__restrict base,
                                              __syscall_ulong_t rel_sysno) {
	return rel_sysno & 1
	       ? (base[rel_sysno / 2] & 0x70) >> 4
	       : (base[rel_sysno / 2] & 0x07);
}
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL ATTR_CONST NONNULL((1)) __BOOL
NOTHROW(KCALL _kernel_private_syscall_doublewide)(__UINT8_TYPE__ const *__restrict base,
                                                  __syscall_ulong_t rel_sysno) {
	return rel_sysno & 1
	       ? (base[rel_sysno / 2] & 0x80) != 0
	       : (base[rel_sysno / 2] & 0x08) != 0;
}


/* Check if a given `sysno' system call is a cancellation point. */
#define _kernel_syscall_iscp(sysno) \
	_kernel_private_syscall_withtable(sysno, 0, _kernel_private_syscall_iscp_impl, sysno)
#define _kernel_private_syscall_iscp_impl(table, sysno) \
	_kernel_private_syscall_iscp(kernel_syscall##table##_iscp, (sysno)-__NR_syscall##table##_min)

/* Return the restart mode used for `sysno' (one of `SYSCALL_RESTART_MODE_*'). */
#define _kernel_syscall_restartmode(sysno) \
	_kernel_private_syscall_withtable(sysno, 0, __kernel_syscall_restartmode_impl, sysno)
#define __kernel_syscall_restartmode_impl(table, sysno) \
	_kernel_private_syscall_restartmode(kernel_syscall##table##_restartmode, (sysno)-__NR_syscall##table##_min)

/* Return the number of registers table by `sysno' (<= `__NRFEAT_SYSCALL_REGISTER_MAX_COUNT') */
#define _kernel_syscall_regcnt(sysno) \
	_kernel_private_syscall_withtable(sysno, __NRFEAT_SYSCALL_REGISTER_MAX_COUNT, _kernel_private_syscall_regcnt_impl, sysno)
#define _kernel_private_syscall_regcnt_impl(table, sysno) \
	_kernel_private_syscall_regcnt(kernel_syscall##table##_regcnt, (sysno)-__NR_syscall##table##_min)

/* Check if a given system call `sysno' has a double-wide return
 * value (i.e.  the  return  value is  passed  in  2  registers) */
#define _kernel_syscall_doublewide(sysno) \
	_kernel_private_syscall_withtable(sysno, 0, _kernel_private_syscall_doublewide_impl, sysno)
#define _kernel_private_syscall_doublewide_impl(table, sysno) \
	_kernel_private_syscall_doublewide(kernel_syscall##table##_regcnt, (sysno)-__NR_syscall##table##_min)

/* Arch may override these. */
#ifndef kernel_syscall_iscp
#define kernel_syscall_iscp(sc_info)        _kernel_syscall_iscp((sc_info)->rsi_sysno)
#define kernel_syscall_restartmode(sc_info) _kernel_syscall_restartmode((sc_info)->rsi_sysno)
#define kernel_syscall_regcnt(sc_info)      _kernel_syscall_regcnt((sc_info)->rsi_sysno)
#define kernel_syscall_doublewide(sc_info)  _kernel_syscall_doublewide((sc_info)->rsi_sysno)
#endif /* !kernel_syscall_iscp */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_SYSCALL_PROPERTIES_H */
