/* HASH CRC-32:0x8fc19e66 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_argp_usage_defined
#define __local_argp_usage_defined
#include <__crt.h>
#include <bits/crt/argp.h>
#include <libc/template/stdstreams.h>
#if (defined(__CRT_HAVE_argp_state_help) || defined(__CRT_HAVE___argp_state_help)) && defined(__LOCAL_stderr) && defined(__ARGP_HELP_STD_USAGE)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_argp_state_help_defined
#define __local___localdep_argp_state_help_defined
#ifdef __CRT_HAVE_argp_state_help
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1),__NOTHROW_NCX,__localdep_argp_state_help,(struct argp_state const *__restrict __state, __FILE *__restrict __stream, unsigned int __flags),argp_state_help,(__state,__stream,__flags))
#elif defined(__CRT_HAVE___argp_state_help)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1),__NOTHROW_NCX,__localdep_argp_state_help,(struct argp_state const *__restrict __state, __FILE *__restrict __stream, unsigned int __flags),__argp_state_help,(__state,__stream,__flags))
#else /* ... */
#undef __local___localdep_argp_state_help_defined
#endif /* !... */
#endif /* !__local___localdep_argp_state_help_defined */
__LOCAL_LIBC(argp_usage) __ATTR_IN(1) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argp_usage))(struct argp_state const *__state) {
	(__NAMESPACE_LOCAL_SYM __localdep_argp_state_help)(__state, __LOCAL_stderr, __ARGP_HELP_STD_USAGE);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_argp_usage_defined
#define __local___localdep_argp_usage_defined
#define __localdep_argp_usage __LIBC_LOCAL_NAME(argp_usage)
#endif /* !__local___localdep_argp_usage_defined */
#else /* (__CRT_HAVE_argp_state_help || __CRT_HAVE___argp_state_help) && __LOCAL_stderr && __ARGP_HELP_STD_USAGE */
#undef __local_argp_usage_defined
#endif /* (!__CRT_HAVE_argp_state_help && !__CRT_HAVE___argp_state_help) || !__LOCAL_stderr || !__ARGP_HELP_STD_USAGE */
#endif /* !__local_argp_usage_defined */
