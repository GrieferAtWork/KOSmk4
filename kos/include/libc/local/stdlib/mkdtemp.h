/* HASH CRC-32:0x56547009 */
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
#ifndef __local_mkdtemp_defined
#define __local_mkdtemp_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_mkdir) || defined(__CRT_HAVE___mkdir) || defined(__CRT_HAVE___libc_mkdir) || (defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_mkdirat) || defined(__CRT_HAVE_fmkdirat)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_system_mktemp_defined
#define __local___localdep_system_mktemp_defined
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/system_mktemp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_system_mktemp __LIBC_LOCAL_NAME(system_mktemp)
#endif /* !__local___localdep_system_mktemp_defined */
__LOCAL_LIBC(mkdtemp) __ATTR_WUNUSED __ATTR_INOUT(1) char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(mkdtemp))(char *__template_) {
	if ((__NAMESPACE_LOCAL_SYM __localdep_system_mktemp)(1, __template_, 0, 0) )
		__template_ = __NULLPTR;
	return __template_;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mkdtemp_defined
#define __local___localdep_mkdtemp_defined
#define __localdep_mkdtemp __LIBC_LOCAL_NAME(mkdtemp)
#endif /* !__local___localdep_mkdtemp_defined */
#else /* __CRT_HAVE_mkdir || __CRT_HAVE___mkdir || __CRT_HAVE___libc_mkdir || (__CRT_DOS_PRIMARY && __CRT_HAVE__mkdir) || (__AT_FDCWD && (__CRT_HAVE_mkdirat || __CRT_HAVE_fmkdirat)) */
#undef __local_mkdtemp_defined
#endif /* !__CRT_HAVE_mkdir && !__CRT_HAVE___mkdir && !__CRT_HAVE___libc_mkdir && (!__CRT_DOS_PRIMARY || !__CRT_HAVE__mkdir) && (!__AT_FDCWD || (!__CRT_HAVE_mkdirat && !__CRT_HAVE_fmkdirat)) */
#endif /* !__local_mkdtemp_defined */
