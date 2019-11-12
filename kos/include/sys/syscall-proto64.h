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
#ifndef _SYS_SYSCALL_PROTO64_H
#define _SYS_SYSCALL_PROTO64_H 1
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#define __WANT_SYSCALL_ARGUMENT_TYPES 1
#define __WANT_SYSCALL_RETURN_TYPES   1

#include <__crt.h>

#include <asm/syscalls64.inl>
#include <bits/syscall.h>

#define __PRIVATE_SYSCALL64_PROTO_0(name, decl) __NR64RT_##name decl(void)
#define __PRIVATE_SYSCALL64_PROTO_1(name, decl) __NR64RT_##name decl(__NR64AT0_##name)
#define __PRIVATE_SYSCALL64_PROTO_2(name, decl) __NR64RT_##name decl(__NR64AT0_##name, __NR64AT1_##name)
#define __PRIVATE_SYSCALL64_PROTO_3(name, decl) __NR64RT_##name decl(__NR64AT0_##name, __NR64AT1_##name, __NR64AT2_##name)
#define __PRIVATE_SYSCALL64_PROTO_4(name, decl) __NR64RT_##name decl(__NR64AT0_##name, __NR64AT1_##name, __NR64AT2_##name, __NR64AT3_##name)
#define __PRIVATE_SYSCALL64_PROTO_5(name, decl) __NR64RT_##name decl(__NR64AT0_##name, __NR64AT1_##name, __NR64AT2_##name, __NR64AT3_##name, __NR64AT4_##name)
#define __PRIVATE_SYSCALL64_PROTO_6(name, decl) __NR64RT_##name decl(__NR64AT0_##name, __NR64AT1_##name, __NR64AT2_##name, __NR64AT3_##name, __NR64AT4_##name, __NR64AT5_##name)

#define __PRIVATE_SYSCALL64_PROTO2(name, argc, decl) __PRIVATE_SYSCALL64_PROTO_##argc(name, decl)
#define __PRIVATE_SYSCALL64_PROTO(name, argc, decl)  __PRIVATE_SYSCALL64_PROTO2(name, argc, decl)

/* Construct a prototype for a given system call:
 * >> SYSCALL64_PROTO(open, KCALL open_proto) // Expands to `fd_t KCALL open_proto(char const *, oflag_t, mode_t)' */
#define SYSCALL64_PROTO(name, decl) __PRIVATE_SYSCALL64_PROTO(name, __NR64AC_##name, decl)

/* Construct a prototype for a given system call pointer:
 * >> (SYSCALL64_PROTO_POINTER(open)) // Expands to `(fd_t (__LIBCCALL *)(char const *, oflag_t, mode_t))'
 * Same as `SYSCALL64_PROTO(<name>, (__LIBCCALL *))' */
#define SYSCALL64_PROTO_POINTER(name) __PRIVATE_SYSCALL64_PROTO(name, __NR64AC_##name, (__LIBCCALL *))

#endif /* !_SYS_SYSCALL_PROTO64_H */
