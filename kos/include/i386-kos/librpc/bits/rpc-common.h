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
#ifndef _I386_KOS_LIBRPC_BITS_RPC_COMMON_H
#define _I386_KOS_LIBRPC_BITS_RPC_COMMON_H 1

#include <__stdinc.h>

#define RPC_SYSCALL_INFO_METHOD_INT80           0x00 /* int 80h */
#define RPC_SYSCALL_INFO_METHOD_SYSENTER        0x01 /* sysenter */
#define RPC_SYSCALL_INFO_METHOD_CALLBACK        0x02 /* call into the ukern segment */
#define RPC_SYSCALL_INFO_METHOD_LCALL7          0x03 /* lcall $7, ... */
#define RPC_SYSCALL_INFO_METHOD_X86_64_SYSCALL  0x40 /* 64-bit code: int 80h / syscall */
#define RPC_SYSCALL_INFO_METHOD_X86_64_CALLBACK 0x42 /* 64-bit code: call into the ukern segment / lcall 47, ... */
#define RPC_SYSCALL_INFO_METHOD_EMULATE         0xff /* Untyped system call emulation */

#endif /* !_I386_KOS_LIBRPC_BITS_RPC_COMMON_H */
