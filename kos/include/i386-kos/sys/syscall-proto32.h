/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_SYS_SYSCALL_PROTO32_H
#define _I386_KOS_SYS_SYSCALL_PROTO32_H 1

#include <__crt.h>

#if (!defined(__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_COUNT) || \
     !defined(__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_TYPES) || \
     !defined(__NR32FEAT_DEFINED_SYSCALL_RETURN_TYPES))
#undef __WANT_SYSCALL_ARGUMENT_COUNT
#undef __WANT_SYSCALL_ARGUMENT_TYPES
#undef __WANT_SYSCALL_RETURN_TYPES
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#define __WANT_SYSCALL_ARGUMENT_TYPES 1
#define __WANT_SYSCALL_RETURN_TYPES   1
#include <asm/syscalls-proto32_d.h>
#endif /* !... */

#ifndef __NR32FEAT_SYSCALL_TABLE_COUNT
#include <asm/syscalls32_d.h>
#endif /* !__NR32FEAT_SYSCALL_TABLE_COUNT */

#ifndef __PRIVATE_SYSCALL_GET_ESCAPED_TYPE
#define __PRIVATE_SYSCALL_GET_ESCAPED_TYPE2(a, b) b
#define __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(t) __PRIVATE_SYSCALL_GET_ESCAPED_TYPE2 t
#endif /* !__PRIVATE_SYSCALL_GET_ESCAPED_TYPE */

#define __PRIVATE_SYSCALL32_PROTO_0(name, decl)         \
	__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name) \
	decl(void)
#define __PRIVATE_SYSCALL32_PROTO_1(name, decl)         \
	__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name) \
	decl(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name))
#define __PRIVATE_SYSCALL32_PROTO_2(name, decl)                \
	__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name)        \
	decl(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), \
	     __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT1_##name))
#define __PRIVATE_SYSCALL32_PROTO_3(name, decl)                \
	__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name)        \
	decl(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), \
	     __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT1_##name), \
	     __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT2_##name))
#define __PRIVATE_SYSCALL32_PROTO_4(name, decl)                \
	__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name)        \
	decl(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), \
	     __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT1_##name), \
	     __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT2_##name), \
	     __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT3_##name))
#define __PRIVATE_SYSCALL32_PROTO_5(name, decl)                \
	__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name)        \
	decl(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), \
	     __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT1_##name), \
	     __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT2_##name), \
	     __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT3_##name), \
	     __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT4_##name))
#define __PRIVATE_SYSCALL32_PROTO_6(name, decl)                \
	__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name)        \
	decl(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), \
	     __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT1_##name), \
	     __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT2_##name), \
	     __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT3_##name), \
	     __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT4_##name), \
	     __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT5_##name))

#define __PRIVATE_SYSCALL32_PROTO2(name, argc, decl) __PRIVATE_SYSCALL32_PROTO_##argc(name, decl)
#define __PRIVATE_SYSCALL32_PROTO(name, argc, decl) __PRIVATE_SYSCALL32_PROTO2(name, argc, decl)

/* Construct a prototype for a given system call:
 * >> SYSCALL32_PROTO(open, KCALL open_proto) // Expands to `fd_t KCALL open_proto(char const *, oflag_t, mode_t)' */
#define SYSCALL32_PROTO(name, decl) __PRIVATE_SYSCALL32_PROTO(name, __NR32AC_##name, decl)

/* Construct a prototype for a given system call pointer:
 * >> (SYSCALL32_PROTO_POINTER(open)) // Expands to `(fd_t (__LIBKCALL *)(char const *, oflag_t, mode_t))'
 * Same as `SYSCALL32_PROTO(<name>, (__LIBKCALL *))' */
#define SYSCALL32_PROTO_POINTER(name) __PRIVATE_SYSCALL32_PROTO(name, __NR32AC_##name, (__LIBKCALL *))

#endif /* !_I386_KOS_SYS_SYSCALL_PROTO32_H */
