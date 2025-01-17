/* HASH CRC-32:0x6f29f58b */
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
#ifndef __local_getopt_defined
#define __local_getopt_defined
#include <__crt.h>
#include <libc/template/getopt.h>
#if defined(__CRT_HAVE_getopt_long) || (defined(__LOCAL_optarg) && defined(__LOCAL_optind))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getopt_long_defined
#define __local___localdep_getopt_long_defined
#ifdef __CRT_HAVE_getopt_long
__NAMESPACE_LOCAL_END
#include <bits/crt/getopt.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2, 3)),int,__NOTHROW_NCX,__localdep_getopt_long,(int ___argc, char *const ___argv[], char const *__optstring, struct option const *__longopts, int *__longindex),getopt_long,(___argc,___argv,__optstring,__longopts,__longindex))
#elif defined(__LOCAL_optarg) && defined(__LOCAL_optind)
__NAMESPACE_LOCAL_END
#include <libc/local/getopt/getopt_long.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getopt_long __LIBC_LOCAL_NAME(getopt_long)
#else /* ... */
#undef __local___localdep_getopt_long_defined
#endif /* !... */
#endif /* !__local___localdep_getopt_long_defined */
__LOCAL_LIBC(getopt) __ATTR_WUNUSED __ATTR_NONNULL((2, 3)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getopt))(int ___argc, char *const ___argv[], char const *__optstring) {
	return (__NAMESPACE_LOCAL_SYM __localdep_getopt_long)(___argc, ___argv, __optstring, __NULLPTR, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getopt_defined
#define __local___localdep_getopt_defined
#define __localdep_getopt __LIBC_LOCAL_NAME(getopt)
#endif /* !__local___localdep_getopt_defined */
#else /* __CRT_HAVE_getopt_long || (__LOCAL_optarg && __LOCAL_optind) */
#undef __local_getopt_defined
#endif /* !__CRT_HAVE_getopt_long && (!__LOCAL_optarg || !__LOCAL_optind) */
#endif /* !__local_getopt_defined */
