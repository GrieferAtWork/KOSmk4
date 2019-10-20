/* HASH CRC-32:0x26f272d4 */
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
#ifndef __local_sscanf_defined
#if 1
#define __local_sscanf_defined 1
/* Dependency: "vsscanf" from "stdio" */
#ifndef ____localdep_vsscanf_defined
#define ____localdep_vsscanf_defined 1
#ifdef __std___localdep_vsscanf_defined
__NAMESPACE_STD_USING(__localdep_vsscanf)
#elif __has_builtin(__builtin_vsscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsscanf)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__FORCELOCAL __ATTR_LIBC_SCANF(2, 0) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL __localdep_vsscanf)(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args) { return __builtin_vsscanf(__input, __format, __args); }
#elif defined(__CRT_HAVE_vsscanf)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_LIBC_SCANF(2, 0) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsscanf,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),vsscanf,(__input,__format,__args))
#elif defined(__CRT_HAVE__vsscanf)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_LIBC_SCANF(2, 0) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsscanf,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),_vsscanf,(__input,__format,__args))
#elif defined(__CRT_HAVE__vsscanf_s)
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_LIBC_SCANF(2, 0) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsscanf,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),_vsscanf_s,(__input,__format,__args))
#else /* LIBC: vsscanf */
#include <local/stdio/vsscanf.h>
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
#define __localdep_vsscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsscanf))
#endif /* vsscanf... */
#endif /* !____localdep_vsscanf_defined */

__NAMESPACE_LOCAL_BEGIN
/* Scan data from a given `INPUT' string, following `FORMAT'
 * Return the number of successfully scanned data items */
__LOCAL_LIBC(sscanf) __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(sscanf))(char const *__restrict __input,
                                                     char const *__restrict __format,
                                                     ...) {
#line 934 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vsscanf(__input, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* 1 */
#endif /* !__local_sscanf_defined */
