/* HASH CRC-32:0x9617cfaf */
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
#ifndef __local_cuserid_defined
#define __local_cuserid_defined
#include <__crt.h>
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_getlogin_r) || defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ) || (defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid) || defined(__CRT_HAVE_getresuid)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getlogin_r_defined
#define __local___localdep_getlogin_r_defined
#ifdef __CRT_HAVE_getlogin_r
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUTS(1, 2),int,__NOTHROW_RPC,__localdep_getlogin_r,(char *__name, __SIZE_TYPE__ __name_len),getlogin_r,(__name,__name_len))
#elif defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ) || (defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid) || defined(__CRT_HAVE_getresuid)))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/getlogin_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getlogin_r __LIBC_LOCAL_NAME(getlogin_r)
#else /* ... */
#undef __local___localdep_getlogin_r_defined
#endif /* !... */
#endif /* !__local___localdep_getlogin_r_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/stdio.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cuserid) __ATTR_OUT_OPT(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cuserid))(char *__s) {
#ifdef __L_cuserid
	static char __cuserid_buffer[__L_cuserid];
	if (!__s)
		__s = __cuserid_buffer;
	return (__NAMESPACE_LOCAL_SYM __localdep_getlogin_r)(__s, __L_cuserid) ? __NULLPTR : __s;
#else /* __L_cuserid */
	static char __cuserid_buffer[9];
	if (!__s)
		__s = __cuserid_buffer;
	return (__NAMESPACE_LOCAL_SYM __localdep_getlogin_r)(__s, 9) ? __NULLPTR : __s;
#endif /* !__L_cuserid */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cuserid_defined
#define __local___localdep_cuserid_defined
#define __localdep_cuserid __LIBC_LOCAL_NAME(cuserid)
#endif /* !__local___localdep_cuserid_defined */
#else /* __CRT_HAVE_getlogin_r || __CRT_HAVE_getenv || __LOCAL_environ || (__CRT_HAVE_getpwuid_r && (__CRT_HAVE_geteuid || __CRT_HAVE___geteuid || __CRT_HAVE___libc_geteuid || __CRT_HAVE_getresuid)) */
#undef __local_cuserid_defined
#endif /* !__CRT_HAVE_getlogin_r && !__CRT_HAVE_getenv && !__LOCAL_environ && (!__CRT_HAVE_getpwuid_r || (!__CRT_HAVE_geteuid && !__CRT_HAVE___geteuid && !__CRT_HAVE___libc_geteuid && !__CRT_HAVE_getresuid)) */
#endif /* !__local_cuserid_defined */
