/* HASH CRC-32:0x9e0b9834 */
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
#ifndef __local_getopt_long_only_defined
#define __local_getopt_long_only_defined
#include <__crt.h>
#include <libc/template/getopt.h>
#if defined(__LOCAL_optarg) && defined(__LOCAL_optind)
#include <bits/crt/getopt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getopt_impl_defined
#define __local___localdep_getopt_impl_defined
__NAMESPACE_LOCAL_END
#include <libc/local/getopt/getopt_impl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getopt_impl __LIBC_LOCAL_NAME(getopt_impl)
#endif /* !__local___localdep_getopt_impl_defined */
__LOCAL_LIBC(getopt_long_only) __ATTR_WUNUSED __ATTR_NONNULL((2, 3)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getopt_long_only))(int ___argc, char *const ___argv[], char const *__optstring, struct option const *__longopts, int *__longindex) {
	return (__NAMESPACE_LOCAL_SYM __localdep_getopt_impl)((unsigned int)___argc, (char const **)___argv, __optstring,
	                   __longopts, (unsigned int *)__longindex, 1);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getopt_long_only_defined
#define __local___localdep_getopt_long_only_defined
#define __localdep_getopt_long_only __LIBC_LOCAL_NAME(getopt_long_only)
#endif /* !__local___localdep_getopt_long_only_defined */
#else /* __LOCAL_optarg && __LOCAL_optind */
#undef __local_getopt_long_only_defined
#endif /* !__LOCAL_optarg || !__LOCAL_optind */
#endif /* !__local_getopt_long_only_defined */
