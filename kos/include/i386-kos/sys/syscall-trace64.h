/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef _I386_KOS_SYS_SYSCALL_TRACE64_H
#define _I386_KOS_SYS_SYSCALL_TRACE64_H 1

#include <__stdinc.h>

#ifndef __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_COUNT
#undef __WANT_SYSCALL_ARGUMENT_COUNT
#define __WANT_SYSCALL_ARGUMENT_COUNT  1
#include <asm/syscalls-proto64_d.h>
#endif /* !__NR64FEAT_DEFINED_SYSCALL_ARGUMENT_COUNT */

#if !defined(__NR64FEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT) || \
    !defined(__NR64FEAT_DEFINED_SYSCALL_ARGUMENT_NAMES)
#undef __WANT_SYSCALL_ARGUMENT_FORMAT
#undef __WANT_SYSCALL_ARGUMENT_NAMES
#define __WANT_SYSCALL_ARGUMENT_FORMAT 1
#define __WANT_SYSCALL_ARGUMENT_NAMES  1
#include <asm/syscalls-trace64_d.h>
#endif /* !... */

#ifndef __NR64FEAT_SYSCALL_TABLE_COUNT
#include <asm/syscalls64_d.h>
#endif /* !__NR64FEAT_SYSCALL_TABLE_COUNT */

#define __PRIVATE_SYSCALL_TRACE_STR2(name) #name
#define __PRIVATE_SYSCALL_TRACE_STR(name) __PRIVATE_SYSCALL_TRACE_STR2(name)

#define __PRIVATE_SYSCALL64_TRACE_FORMAT_0(name)      ""
#define __PRIVATE_SYSCALL64_TRACE_FORMAT_1(name)      __NR64ATRF0_##name
#define __PRIVATE_SYSCALL64_TRACE_FORMAT_2(name)      __NR64ATRF0_##name ", " __NR64ATRF1_##name
#define __PRIVATE_SYSCALL64_TRACE_FORMAT_3(name)      __NR64ATRF0_##name ", " __NR64ATRF1_##name ", " __NR64ATRF2_##name
#define __PRIVATE_SYSCALL64_TRACE_FORMAT_4(name)      __NR64ATRF0_##name ", " __NR64ATRF1_##name ", " __NR64ATRF2_##name ", " __NR64ATRF3_##name
#define __PRIVATE_SYSCALL64_TRACE_FORMAT_5(name)      __NR64ATRF0_##name ", " __NR64ATRF1_##name ", " __NR64ATRF2_##name ", " __NR64ATRF3_##name ", " __NR64ATRF4_##name
#define __PRIVATE_SYSCALL64_TRACE_FORMAT_6(name)      __NR64ATRF0_##name ", " __NR64ATRF1_##name ", " __NR64ATRF2_##name ", " __NR64ATRF3_##name ", " __NR64ATRF4_##name ", " __NR64ATRF5_##name
#define __PRIVATE_SYSCALL64_TRACE_FORMAT2(name, argc) __PRIVATE_SYSCALL64_TRACE_FORMAT_##argc(name)
#define __PRIVATE_SYSCALL64_TRACE_FORMAT(name, argc)  __PRIVATE_SYSCALL64_TRACE_FORMAT2(name, argc)

#define __PRIVATE_SYSCALL64_TRACE_LFORMAT_0(name)      ""
#define __PRIVATE_SYSCALL64_TRACE_LFORMAT_1(name)      __PRIVATE_SYSCALL_TRACE_STR(__NR64AN0_##name) ": " __NR64ATRF0_##name
#define __PRIVATE_SYSCALL64_TRACE_LFORMAT_2(name)      __PRIVATE_SYSCALL64_TRACE_LFORMAT_1(name) ", " __PRIVATE_SYSCALL_TRACE_STR(__NR64AN1_##name) ": " __NR64ATRF1_##name
#define __PRIVATE_SYSCALL64_TRACE_LFORMAT_3(name)      __PRIVATE_SYSCALL64_TRACE_LFORMAT_2(name) ", " __PRIVATE_SYSCALL_TRACE_STR(__NR64AN2_##name) ": " __NR64ATRF2_##name
#define __PRIVATE_SYSCALL64_TRACE_LFORMAT_4(name)      __PRIVATE_SYSCALL64_TRACE_LFORMAT_3(name) ", " __PRIVATE_SYSCALL_TRACE_STR(__NR64AN3_##name) ": " __NR64ATRF3_##name
#define __PRIVATE_SYSCALL64_TRACE_LFORMAT_5(name)      __PRIVATE_SYSCALL64_TRACE_LFORMAT_4(name) ", " __PRIVATE_SYSCALL_TRACE_STR(__NR64AN4_##name) ": " __NR64ATRF4_##name
#define __PRIVATE_SYSCALL64_TRACE_LFORMAT_6(name)      __PRIVATE_SYSCALL64_TRACE_LFORMAT_5(name) ", " __PRIVATE_SYSCALL_TRACE_STR(__NR64AN5_##name) ": " __NR64ATRF5_##name
#define __PRIVATE_SYSCALL64_TRACE_LFORMAT2(name, argc) __PRIVATE_SYSCALL64_TRACE_LFORMAT_##argc(name)
#define __PRIVATE_SYSCALL64_TRACE_LFORMAT(name, argc)  __PRIVATE_SYSCALL64_TRACE_LFORMAT2(name, argc)

#define __PRIVATE_SYSCALL64_TRACE_ARGS_0(name, args)      /* nothing */
#define __PRIVATE_SYSCALL64_TRACE_ARGS_1(name, args)      __NR64ATRA0_##name args
#define __PRIVATE_SYSCALL64_TRACE_ARGS_2(name, args)      __NR64ATRA0_##name args __NR64ATRA1_##name args
#define __PRIVATE_SYSCALL64_TRACE_ARGS_3(name, args)      __NR64ATRA0_##name args __NR64ATRA1_##name args __NR64ATRA2_##name args
#define __PRIVATE_SYSCALL64_TRACE_ARGS_4(name, args)      __NR64ATRA0_##name args __NR64ATRA1_##name args __NR64ATRA2_##name args __NR64ATRA3_##name args
#define __PRIVATE_SYSCALL64_TRACE_ARGS_5(name, args)      __NR64ATRA0_##name args __NR64ATRA1_##name args __NR64ATRA2_##name args __NR64ATRA3_##name args __NR64ATRA4_##name args
#define __PRIVATE_SYSCALL64_TRACE_ARGS_6(name, args)      __NR64ATRA0_##name args __NR64ATRA1_##name args __NR64ATRA2_##name args __NR64ATRA3_##name args __NR64ATRA4_##name args __NR64ATRA5_##name args
#define __PRIVATE_SYSCALL64_TRACE_ARGS2(name, argc, args) __PRIVATE_SYSCALL64_TRACE_ARGS_##argc(name, args)
#define __PRIVATE_SYSCALL64_TRACE_ARGS(name, argc, args)  __PRIVATE_SYSCALL64_TRACE_ARGS2(name, argc, args)

/* Returns a string constant which may be used as a printf-string
 * to describe the arguments taken by a given system call.
 * e.g.:
 *   - `SYSCALL64_TRACE_ARGS_FORMAT(open)'   == `%q, %#Ix, %#Io'
 *   - `SYSCALL64_TRACE_ARGS_FORMAT_L(open)' == `filename: %q, oflags: %#Ix, mode: %#Io'
 * To generate the arguments required for the generated printf-string, use
 * `SYSCALL64_TRACE_ARGS_ARGS(open,("foo",O_WRONLY|O_CREAT,0644))'.
 * Note however that `SYSCALL64_TRACE_ARGS_ARGS()' will already prepend a leading
 * comma, meaning a fully correct operation then looks like this:
 * >> printf("sys_open(" SYSCALL64_TRACE_ARGS_FORMAT_L(open) ")\n"
 * >>        SYSCALL64_TRACE_ARGS_ARGS(open,(get_filename(),
 * >>                                        get_oflags(),
 * >>                                        get_mode()))
 * >>        );
 */
#define SYSCALL64_TRACE_ARGS_FORMAT(name)     __PRIVATE_SYSCALL64_TRACE_FORMAT(name, __NR64AC_##name)
#define SYSCALL64_TRACE_ARGS_FORMAT_L(name)   __PRIVATE_SYSCALL64_TRACE_LFORMAT(name, __NR64AC_##name)
#define SYSCALL64_TRACE_ARGS_ARGS(name, args) __PRIVATE_SYSCALL64_TRACE_ARGS(name, __NR64AC_##name, args)

#endif /* !_I386_KOS_SYS_SYSCALL_TRACE64_H */
