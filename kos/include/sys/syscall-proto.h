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
#ifndef _SYS_SYSCALL_PROTO_H
#define _SYS_SYSCALL_PROTO_H 1

/* If <sym/unistd.h> was already included, reset its guard
 * if we didn't get everything we needed the previous time. */
#ifdef _ASM_UNISTD_H
#if !defined(__WANT_SYSCALL_ARGUMENT_COUNT) || \
    !defined(__WANT_SYSCALL_ARGUMENT_TYPES) || \
    !defined(__WANT_SYSCALL_RETURN_TYPES)
#undef _ASM_UNISTD_H
#endif /* !... */
#endif /* _ASM_UNISTD_H */
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#define __WANT_SYSCALL_ARGUMENT_TYPES 1
#define __WANT_SYSCALL_RETURN_TYPES   1

#include <__crt.h>

#include <asm/unistd.h>
#include <bits/syscall.h>

#define __PRIVATE_SYSCALL_PROTO_0(name, decl) __NRRT_##name decl(void)
#define __PRIVATE_SYSCALL_PROTO_1(name, decl) __NRRT_##name decl(__NRAT0_##name)
#define __PRIVATE_SYSCALL_PROTO_2(name, decl) __NRRT_##name decl(__NRAT0_##name, __NRAT1_##name)
#define __PRIVATE_SYSCALL_PROTO_3(name, decl) __NRRT_##name decl(__NRAT0_##name, __NRAT1_##name, __NRAT2_##name)
#define __PRIVATE_SYSCALL_PROTO_4(name, decl) __NRRT_##name decl(__NRAT0_##name, __NRAT1_##name, __NRAT2_##name, __NRAT3_##name)
#define __PRIVATE_SYSCALL_PROTO_5(name, decl) __NRRT_##name decl(__NRAT0_##name, __NRAT1_##name, __NRAT2_##name, __NRAT3_##name, __NRAT4_##name)
#define __PRIVATE_SYSCALL_PROTO_6(name, decl) __NRRT_##name decl(__NRAT0_##name, __NRAT1_##name, __NRAT2_##name, __NRAT3_##name, __NRAT4_##name, __NRAT5_##name)

#define __PRIVATE_SYSCALL_PROTO2(name, argc, decl) __PRIVATE_SYSCALL_PROTO_##argc(name, decl)
#define __PRIVATE_SYSCALL_PROTO(name, argc, decl)  __PRIVATE_SYSCALL_PROTO2(name, argc, decl)

/* Construct a prototype for a given system call:
 * >> SYSCALL_PROTO(open, KCALL open_proto) // Expands to `fd_t KCALL open_proto(char const *, oflag_t, mode_t)' */
#define SYSCALL_PROTO(name, decl) __PRIVATE_SYSCALL_PROTO(name, __NRAC_##name, decl)

/* Construct a prototype for a given system call pointer:
 * >> (SYSCALL_PROTO_POINTER(open)) // Expands to `(fd_t (__LIBCCALL *)(char const *, oflag_t, mode_t))'
 * Same as `SYSCALL_PROTO(<name>, (__LIBCCALL *))' */
#define SYSCALL_PROTO_POINTER(name) __PRIVATE_SYSCALL_PROTO(name, __NRAC_##name, (__LIBCCALL *))

#endif /* !_SYS_SYSCALL_PROTO_H */
