/* HASH CRC-32:0x975905ad */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_dprintf_defined
#define __local_dprintf_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_vdprintf) || defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: vdprintf from stdio */
#ifndef __local___localdep_vdprintf_defined
#define __local___localdep_vdprintf_defined 1
#ifdef __CRT_HAVE_vdprintf
/* >> dprintf(3), vdprintf(3) */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_vdprintf,(__fd_t __fd, char const *__restrict __format, __builtin_va_list __args),vdprintf,(__fd,__format,__args))
#elif defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/vdprintf.h>
__NAMESPACE_LOCAL_BEGIN
/* >> dprintf(3), vdprintf(3) */
#define __localdep_vdprintf __LIBC_LOCAL_NAME(vdprintf)
#else /* ... */
#undef __local___localdep_vdprintf_defined
#endif /* !... */
#endif /* !__local___localdep_vdprintf_defined */
/* >> dprintf(3), vdprintf(3) */
__LOCAL_LIBC(dprintf) __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((2)) __STDC_INT_AS_SSIZE_T
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(dprintf))(__fd_t __fd, char const *__restrict __format, ...) {
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vdprintf(__fd, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_dprintf_defined
#define __local___localdep_dprintf_defined 1
#define __localdep_dprintf __LIBC_LOCAL_NAME(dprintf)
#endif /* !__local___localdep_dprintf_defined */
#else /* __CRT_HAVE_vdprintf || __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write */
#undef __local_dprintf_defined
#endif /* !__CRT_HAVE_vdprintf && !__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write */
#endif /* !__local_dprintf_defined */
