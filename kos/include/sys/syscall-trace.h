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
#ifndef _SYS_SYSCALL_TRACE_H
#define _SYS_SYSCALL_TRACE_H 1

/* If <sym/unistd.h> was already included, reset its guard
 * if we didn't get everything we needed the previous time. */
#ifdef _ASM_UNISTD_H
#if !defined(__WANT_SYSCALL_ARGUMENT_COUNT) || \
    !defined(__WANT_SYSCALL_ARGUMENT_FORMAT) || \
    !defined(__WANT_SYSCALL_ARGUMENT_NAMES)
#undef _ASM_UNISTD_H
#endif /* !... */
#endif /* _ASM_UNISTD_H */
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#define __WANT_SYSCALL_ARGUMENT_FORMAT 1
#define __WANT_SYSCALL_ARGUMENT_NAMES 1

#include <asm/unistd.h>
#include <bits/syscall.h>

#define __PRIVATE_SYSCALL_TRACE_FORMAT_0(name) ""
#define __PRIVATE_SYSCALL_TRACE_FORMAT_1(name) __NRATRF0_##name
#define __PRIVATE_SYSCALL_TRACE_FORMAT_2(name) __NRATRF0_##name "," __NRATRF1_##name
#define __PRIVATE_SYSCALL_TRACE_FORMAT_3(name) __NRATRF0_##name "," __NRATRF1_##name "," __NRATRF2_##name
#define __PRIVATE_SYSCALL_TRACE_FORMAT_4(name) __NRATRF0_##name "," __NRATRF1_##name "," __NRATRF2_##name "," __NRATRF3_##name
#define __PRIVATE_SYSCALL_TRACE_FORMAT_5(name) __NRATRF0_##name "," __NRATRF1_##name "," __NRATRF2_##name "," __NRATRF3_##name "," __NRATRF4_##name
#define __PRIVATE_SYSCALL_TRACE_FORMAT_6(name) __NRATRF0_##name "," __NRATRF1_##name "," __NRATRF2_##name "," __NRATRF3_##name "," __NRATRF4_##name "," __NRATRF5_##name
#define __PRIVATE_SYSCALL_TRACE_FORMAT2(name,argc) __PRIVATE_SYSCALL_TRACE_FORMAT_##argc(name)
#define __PRIVATE_SYSCALL_TRACE_FORMAT(name,argc) __PRIVATE_SYSCALL_TRACE_FORMAT2(name,argc)

#define __PRIVATE_SYSCALL_TRACE_LFORMAT_0(name) ""
#define __PRIVATE_SYSCALL_TRACE_LFORMAT_1(name) __NRAN0_##name ": " __NRATRF0_##name
#define __PRIVATE_SYSCALL_TRACE_LFORMAT_2(name) __PRIVATE_SYSCALL_TRACE_LFORMAT_1(name) ", " __NRAN1_##name ": " __NRATRF1_##name
#define __PRIVATE_SYSCALL_TRACE_LFORMAT_3(name) __PRIVATE_SYSCALL_TRACE_LFORMAT_2(name) ", " __NRAN2_##name ": " __NRATRF2_##name
#define __PRIVATE_SYSCALL_TRACE_LFORMAT_4(name) __PRIVATE_SYSCALL_TRACE_LFORMAT_3(name) ", " __NRAN3_##name ": " __NRATRF3_##name
#define __PRIVATE_SYSCALL_TRACE_LFORMAT_5(name) __PRIVATE_SYSCALL_TRACE_LFORMAT_4(name) ", " __NRAN4_##name ": " __NRATRF4_##name
#define __PRIVATE_SYSCALL_TRACE_LFORMAT_6(name) __PRIVATE_SYSCALL_TRACE_LFORMAT_5(name) ", " __NRAN5_##name ": " __NRATRF5_##name
#define __PRIVATE_SYSCALL_TRACE_LFORMAT2(name,argc) __PRIVATE_SYSCALL_TRACE_LFORMAT_##argc(name)
#define __PRIVATE_SYSCALL_TRACE_LFORMAT(name,argc) __PRIVATE_SYSCALL_TRACE_LFORMAT2(name,argc)

#define __PRIVATE_SYSCALL_TRACE_ARGS_0(name,args) /* nothing */
#define __PRIVATE_SYSCALL_TRACE_ARGS_1(name,args) __NRATRA0_##name args
#define __PRIVATE_SYSCALL_TRACE_ARGS_2(name,args) __NRATRA0_##name args __NRATRA1_##name args
#define __PRIVATE_SYSCALL_TRACE_ARGS_3(name,args) __NRATRA0_##name args __NRATRA1_##name args __NRATRA2_##name args
#define __PRIVATE_SYSCALL_TRACE_ARGS_4(name,args) __NRATRA0_##name args __NRATRA1_##name args __NRATRA2_##name args __NRATRA3_##name args
#define __PRIVATE_SYSCALL_TRACE_ARGS_5(name,args) __NRATRA0_##name args __NRATRA1_##name args __NRATRA2_##name args __NRATRA3_##name args __NRATRA4_##name args
#define __PRIVATE_SYSCALL_TRACE_ARGS_6(name,args) __NRATRA0_##name args __NRATRA1_##name args __NRATRA2_##name args __NRATRA3_##name args __NRATRA4_##name args __NRATRA5_##name args
#define __PRIVATE_SYSCALL_TRACE_ARGS2(name,argc,args) __PRIVATE_SYSCALL_TRACE_ARGS_##argc(name,args)
#define __PRIVATE_SYSCALL_TRACE_ARGS(name,argc,args) __PRIVATE_SYSCALL_TRACE_ARGS2(name,argc,args)

/* Returns a string constant which may be used as a printf-string
 * to describe the arguments taken by a given system call.
 * e.g.:
 *   - `SYSCALL_TRACE_ARGS_FORMAT(open)'   == `%q,%#Ix,%#Io'
 *   - `SYSCALL_TRACE_ARGS_FORMAT_L(open)' == `filename: %q, oflags: %#Ix, mode: %#Io'
 * To generate the arguments required for the generated printf-string, use
 * `SYSCALL_TRACE_ARGS_ARGS(open,("foo",O_WRONLY|O_CREAT,0644))'.
 * Note however that `SYSCALL_TRACE_ARGS_ARGS()' will already prepend a leading
 * comma, meaning a fully correct operation then looks like this:
 * >> printf("sys_open(" SYSCALL_TRACE_ARGS_FORMAT_L(open) ")\n"
 * >>        SYSCALL_TRACE_ARGS_ARGS(open,(get_filename(),
 * >>                                      get_oflags(),
 * >>                                      get_mode()))
 * >>        );
 */
#define SYSCALL_TRACE_ARGS_FORMAT(name)     __PRIVATE_SYSCALL_TRACE_FORMAT(name,__NRAC_##name)
#define SYSCALL_TRACE_ARGS_FORMAT_L(name)   __PRIVATE_SYSCALL_TRACE_LFORMAT(name,__NRAC_##name)
#define SYSCALL_TRACE_ARGS_ARGS(name,args)  __PRIVATE_SYSCALL_TRACE_ARGS(name,__NRAC_##name,args)

#endif /* !_SYS_SYSCALL_TRACE_H */
