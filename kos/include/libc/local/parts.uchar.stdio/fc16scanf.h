/* HASH CRC-32:0xa92434e6 */
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
#ifndef __local_fc16scanf_defined
#define __local_fc16scanf_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwscanf)
#include <kos/anno.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vfc16scanf_defined
#define __local___localdep_vfc16scanf_defined 1
#if defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vfc16scanf,(__FILE *__restrict __stream, __CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$vfwscanf)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep_vfc16scanf,(__FILE *__restrict __stream, __CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#else /* ... */
#undef __local___localdep_vfc16scanf_defined
#endif /* !... */
#endif /* !__local___localdep_vfc16scanf_defined */
__LOCAL_LIBC(fc16scanf) __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(__VLIBDCALL __LIBC_LOCAL_NAME(fc16scanf))(__FILE *__restrict __stream, __CHAR16_TYPE__ const *__restrict __format, ...) __THROWS(...) {
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vfc16scanf(__stream, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fc16scanf_defined
#define __local___localdep_fc16scanf_defined 1
#define __localdep_fc16scanf __LIBC_LOCAL_NAME(fc16scanf)
#endif /* !__local___localdep_fc16scanf_defined */
#else /* (__CRT_HAVE_vfwscanf && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$vfwscanf */
#undef __local_fc16scanf_defined
#endif /* (!__CRT_HAVE_vfwscanf || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$vfwscanf */
#endif /* !__local_fc16scanf_defined */
