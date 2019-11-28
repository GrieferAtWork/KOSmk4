/* HASH CRC-32:0xf0dd7b3 */
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
#ifndef __local_putchar16_unlocked_defined
#if (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS)
#define __local_putchar16_unlocked_defined 1
#include <kos/anno.h>
/* Dependency: "fputwc_unlocked" */
#ifndef ____localdep_fputc16_unlocked_defined
#define ____localdep_fputc16_unlocked_defined 1
#if defined(__CRT_HAVE_fputwc_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$_fputwc_nolock)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$_fputwc_nolock)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,__localdep_fputc16_unlocked,(__CHAR16_TYPE__ __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#else /* LIBC: fputc16_unlocked */
#undef ____localdep_fputc16_unlocked_defined
#endif /* fputc16_unlocked... */
#endif /* !____localdep_fputc16_unlocked_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(putchar16_unlocked) __WINT_TYPE__
(__LIBDCALL __LIBC_LOCAL_NAME(putchar16_unlocked))(__CHAR16_TYPE__ __wc) __THROWS(...) {
#line 1027 "kos/src/libc/magic/wchar.c"
	return __localdep_fputc16_unlocked(__wc, __LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_HAVE_fputwc_unlocked || __CRT_HAVE__fputwc_nolock) && !__NO_STDSTREAMS */
#endif /* !__local_putchar16_unlocked_defined */
