/* HASH CRC-32:0x7edb73ca */
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
#ifndef __local_dprintf_defined
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE_vdprintf)
#define __local_dprintf_defined 1
/* Dependency: "vdprintf" from "stdio" */
#ifndef ____localdep_vdprintf_defined
#define ____localdep_vdprintf_defined 1
#if defined(__CRT_HAVE_vdprintf)
__CREDIRECT(__ATTR_NONNULL((2)) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_vdprintf,(__fd_t __fd, char const *__restrict __format, __builtin_va_list __args),vdprintf,(__fd,__format,__args))
#elif defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)
#include <local/stdio/vdprintf.h>
#define __localdep_vdprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vdprintf))
#else /* CUSTOM: vdprintf */
#undef ____localdep_vdprintf_defined
#endif /* vdprintf... */
#endif /* !____localdep_vdprintf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(dprintf) __ATTR_NONNULL((2)) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(dprintf))(__fd_t __fd,
                                                      char const *__restrict __format,
                                                      ...) {
#line 1027 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vdprintf(__fd, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE_vdprintf) */
#endif /* !__local_dprintf_defined */
