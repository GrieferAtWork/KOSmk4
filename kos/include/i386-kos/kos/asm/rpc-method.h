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
#ifndef _I386_KOS_KOS_ASM_RPC_METHOD_H
#define _I386_KOS_KOS_ASM_RPC_METHOD_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#define RPC_SYSCALL_INFO_METHOD_INT80H_32    0x00 /* `int 80h' */
#define RPC_SYSCALL_INFO_METHOD_SYSENTER_32  0x01 /* `sysenter' */
#define RPC_SYSCALL_INFO_METHOD_LCALL7_32    0x02 /* `lcall $7' */
#define RPC_SYSCALL_INFO_METHOD_CDECL_32     0x03 /* 32-bit call into the ukern segment */
#define RPC_SYSCALL_INFO_METHOD_SIGRETURN_32 0x7e /* 32-bit call was restarted as part of `sigreturn()' */
#define RPC_SYSCALL_INFO_METHOD_OTHER_32     0x7f /* Some other kind of 32-bit system call invocation method */
#define RPC_SYSCALL_INFO_METHOD_INT80H_64    0x80 /* `int 80h' or `syscall' (on x86_64) */
#define RPC_SYSCALL_INFO_METHOD_LCALL7_64    0x82 /* `lcall $7' (on x86_64) */
#define RPC_SYSCALL_INFO_METHOD_SYSVABI_64   0x83 /* 64-bit call into the ukern segment */
#define RPC_SYSCALL_INFO_METHOD_SIGRETURN_64 0xfe /* 64-bit call was restarted as part of `sigreturn()' */
#define RPC_SYSCALL_INFO_METHOD_OTHER_64     0xff /* Some other kind of 64-bit system call invocation method */
#define RPC_SYSCALL_INFO_METHOD_F32          0x00 /* FLAG: 32-bit system call */
#define RPC_SYSCALL_INFO_METHOD_F64          0x80 /* FLAG: 64-bit system call */
#define RPC_SYSCALL_INFO_METHOD_F3264        0x80 /* MASK: 32/64-bit system call */

#ifdef __x86_64__
#define RPC_SYSCALL_INFO_METHOD_INT80H    RPC_SYSCALL_INFO_METHOD_INT80H_64
#define RPC_SYSCALL_INFO_METHOD_LCALL7    RPC_SYSCALL_INFO_METHOD_LCALL7_64
#define RPC_SYSCALL_INFO_METHOD_SYSVABI   RPC_SYSCALL_INFO_METHOD_SYSVABI_64
#define RPC_SYSCALL_INFO_METHOD_SIGRETURN RPC_SYSCALL_INFO_METHOD_SIGRETURN_64
#define RPC_SYSCALL_INFO_METHOD_OTHER     RPC_SYSCALL_INFO_METHOD_OTHER_64
#else /* __x86_64__ */
#define RPC_SYSCALL_INFO_METHOD_INT80H    RPC_SYSCALL_INFO_METHOD_INT80H_32
#define RPC_SYSCALL_INFO_METHOD_SYSENTER  RPC_SYSCALL_INFO_METHOD_SYSENTER_32
#define RPC_SYSCALL_INFO_METHOD_LCALL7    RPC_SYSCALL_INFO_METHOD_LCALL7_32
#define RPC_SYSCALL_INFO_METHOD_CDECL     RPC_SYSCALL_INFO_METHOD_CDECL_32
#define RPC_SYSCALL_INFO_METHOD_SIGRETURN RPC_SYSCALL_INFO_METHOD_SIGRETURN_32
#define RPC_SYSCALL_INFO_METHOD_OTHER     RPC_SYSCALL_INFO_METHOD_OTHER_32
#endif /* !__x86_64__ */

#define RPC_SYSCALL_INFO_METHOD_ISSYSCALL32(reason) (!((reason) & 0x80))
#define RPC_SYSCALL_INFO_METHOD_ISSYSCALL64(reason) ((reason) & 0x80)
#ifdef __x86_64__
#define RPC_SYSCALL_INFO_METHOD_ISCOMPAT(reason) \
	RPC_SYSCALL_INFO_METHOD_ISSYSCALL32(reason)
#endif /* __x86_64__ */

#endif /* !_I386_KOS_KOS_ASM_RPC_METHOD_H */
