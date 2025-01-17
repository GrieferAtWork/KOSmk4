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
#ifndef _LIBC_TEMPLATE_ARGP_H
#define _LIBC_TEMPLATE_ARGP_H

#include <__crt.h>

#ifdef __CC__
__DECL_BEGIN

struct argp_state;

#ifndef __LOCAL_argp_program_version
#ifdef argp_program_version
#define __LOCAL_argp_program_version argp_program_version
#elif defined(__CRT_HAVE_argp_program_version)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(, char const *, __LOCAL_argp_program_version, argp_program_version)
#define __LOCAL_argp_program_version __LOCAL_argp_program_version
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(, char const *, argp_program_version)
#define argp_program_version         argp_program_version
#define __LOCAL_argp_program_version argp_program_version
#endif /* __NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL_argp_program_version */

#ifndef __LOCAL_argp_program_version_hook
#ifdef argp_program_version_hook
#define __LOCAL_argp_program_version_hook argp_program_version_hook
#elif defined(__CRT_HAVE_argp_program_version_hook)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT2(, void (__LIBKCALL *__LOCAL_argp_program_version_hook)(__FILE *__restrict __stream, struct argp_state *__restrict __state), __LOCAL_argp_program_version_hook, argp_program_version_hook)
#define __LOCAL_argp_program_version_hook __LOCAL_argp_program_version_hook
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE2(, void (__LIBKCALL *argp_program_version_hook)(__FILE *__restrict __stream, struct argp_state *__restrict __state), argp_program_version_hook)
#define argp_program_version_hook         argp_program_version_hook
#define __LOCAL_argp_program_version_hook argp_program_version_hook
#endif /* __NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL_argp_program_version_hook */

#ifndef __LOCAL_argp_program_bug_address
#ifdef argp_program_bug_address
#define __LOCAL_argp_program_bug_address argp_program_bug_address
#elif defined(__CRT_HAVE_argp_program_bug_address)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(, char const *, __LOCAL_argp_program_bug_address, argp_program_bug_address)
#define __LOCAL_argp_program_bug_address __LOCAL_argp_program_bug_address
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(, char const *, argp_program_bug_address)
#define argp_program_bug_address         argp_program_bug_address
#define __LOCAL_argp_program_bug_address argp_program_bug_address
#endif /* __NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL_argp_program_bug_address */

#ifndef __LOCAL_argp_err_exit_status
#ifdef argp_err_exit_status
#define __LOCAL_argp_err_exit_status argp_err_exit_status
#elif defined(__CRT_HAVE_argp_err_exit_status)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(, int, __LOCAL_argp_err_exit_status, argp_err_exit_status)
#define __LOCAL_argp_err_exit_status __LOCAL_argp_err_exit_status
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(, int, argp_err_exit_status)
#define argp_err_exit_status         argp_err_exit_status
#define __LOCAL_argp_err_exit_status argp_err_exit_status
#endif /* __NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL_argp_err_exit_status */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBC_TEMPLATE_ARGP_H */
