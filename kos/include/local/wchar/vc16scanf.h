/* HASH CRC-32:0x7c154b05 */
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
#ifndef __local_vc16scanf_defined
#include <__crt.h>
#if defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)
#define __local_vc16scanf_defined 1
#include <kos/anno.h>
#include <local/stdstreams.h>
/* Dependency: "vfwscanf" */
#ifndef ____localdep_vfc16scanf_defined
#define ____localdep_vfc16scanf_defined 1
#if defined(__CRT_HAVE_vfwscanf) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vfc16scanf,(__FILE *__restrict __stream, __CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$vfwscanf)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vfc16scanf,(__FILE *__restrict __stream, __CHAR16_TYPE__ const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#else /* LIBC: vfc16scanf */
#undef ____localdep_vfc16scanf_defined
#endif /* vfc16scanf... */
#endif /* !____localdep_vfc16scanf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vc16scanf) __ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(vc16scanf))(__CHAR16_TYPE__ const *__restrict __format,
                                          __builtin_va_list __args) __THROWS(...) {
#line 639 "kos/src/libc/magic/wchar.c"
	return __localdep_vfc16scanf(__LOCAL_stdin, __format, __args);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS) */
#endif /* !__local_vc16scanf_defined */
