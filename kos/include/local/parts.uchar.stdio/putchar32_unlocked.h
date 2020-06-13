/* HASH CRC-32:0x704d7fef */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_putchar32_unlocked_defined
#define __local_putchar32_unlocked_defined 1
#include <__crt.h>
#if ((defined(__CRT_HAVE_fputwc_unlocked) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked)) && !defined(__NO_STDSTREAMS)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fputc32_unlocked from parts.uchar.stdio */
#ifndef __local___localdep_fputc32_unlocked_defined
#define __local___localdep_fputc32_unlocked_defined 1
#if defined(__CRT_HAVE_fputwc_unlocked) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,__localdep_fputc32_unlocked,(__CHAR32_TYPE__ __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$fputwc_unlocked)
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,__localdep_fputc32_unlocked,(__CHAR32_TYPE__ __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#else /* ... */
#undef __local___localdep_fputc32_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fputc32_unlocked_defined */
__NAMESPACE_LOCAL_END
#include <local/stdstreams.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(putchar32_unlocked) __WINT_TYPE__
(__LIBKCALL __LIBC_LOCAL_NAME(putchar32_unlocked))(__CHAR32_TYPE__ __wc) __THROWS(...) {
	return __localdep_fputc32_unlocked(__wc, __LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_putchar32_unlocked_defined
#define __local___localdep_putchar32_unlocked_defined 1
#define __localdep_putchar32_unlocked __LIBC_LOCAL_NAME(putchar32_unlocked)
#endif /* !__local___localdep_putchar32_unlocked_defined */
#else /* ((__CRT_HAVE_fputwc_unlocked && (__SIZEOF_WCHAR_T__ == 4) && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_DOS$fputwc_unlocked) && !__NO_STDSTREAMS */
#undef __local_putchar32_unlocked_defined
#endif /* ((!__CRT_HAVE_fputwc_unlocked || !(__SIZEOF_WCHAR_T__ == 4) || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_DOS$fputwc_unlocked) || __NO_STDSTREAMS */
#endif /* !__local_putchar32_unlocked_defined */
