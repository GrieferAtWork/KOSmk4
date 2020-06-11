/* HASH CRC-32:0xb531743 */
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
#ifndef __local__vprintf_p_l_defined
#define __local__vprintf_p_l_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE__vprintf_p) || (!defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE__vfprintf_p) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)))
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: _vprintf_p from stdio */
#ifndef __local___localdep__vprintf_p_defined
#define __local___localdep__vprintf_p_defined 1
#ifdef __CRT_HAVE__vprintf_p
__CREDIRECT(__ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,__localdep__vprintf_p,(char const *__restrict __format, __builtin_va_list __args),_vprintf_p,(__format,__args))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE__vfprintf_p) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite))
__NAMESPACE_LOCAL_END
#include <local/stdio/_vprintf_p.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vprintf_p __LIBC_LOCAL_NAME(_vprintf_p)
#else /* ... */
#undef __local___localdep__vprintf_p_defined
#endif /* !... */
#endif /* !__local___localdep__vprintf_p_defined */
__LOCAL_LIBC(_vprintf_p_l) __ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T
(__LIBCCALL __LIBC_LOCAL_NAME(_vprintf_p_l))(char const *__restrict __format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) {
	(void)__locale;
	return __localdep__vprintf_p(__format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vprintf_p_l_defined
#define __local___localdep__vprintf_p_l_defined 1
#define __localdep__vprintf_p_l __LIBC_LOCAL_NAME(_vprintf_p_l)
#endif /* !__local___localdep__vprintf_p_l_defined */
#else /* __CRT_HAVE__vprintf_p || (!__NO_STDSTREAMS && (__CRT_HAVE__vfprintf_p || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite)) */
#undef __local__vprintf_p_l_defined
#endif /* !__CRT_HAVE__vprintf_p && (__NO_STDSTREAMS || (!__CRT_HAVE__vfprintf_p && !__CRT_HAVE_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock && !__CRT_HAVE__IO_fwrite)) */
#endif /* !__local__vprintf_p_l_defined */
