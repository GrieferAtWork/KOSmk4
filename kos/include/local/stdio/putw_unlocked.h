/* HASH CRC-32:0x10c61009 */
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
#ifndef __local_putw_unlocked_defined
#define __local_putw_unlocked_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_putw) || defined(__CRT_HAVE__putw) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: putw from stdio */
#ifndef __local___localdep_putw_defined
#define __local___localdep_putw_defined 1
#ifdef __CRT_HAVE_putw
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_putw,(int __w, __FILE *__restrict __stream),putw,(__w,__stream))
#elif defined(__CRT_HAVE__putw)
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_putw,(int __w, __FILE *__restrict __stream),_putw,(__w,__stream))
#elif defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_LOCAL_END
#include <local/stdio/putw.h>
__NAMESPACE_LOCAL_BEGIN
/* Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
#define __localdep_putw __LIBC_LOCAL_NAME(putw)
#else /* ... */
#undef __local___localdep_putw_defined
#endif /* !... */
#endif /* !__local___localdep_putw_defined */
__LOCAL_LIBC(putw_unlocked) __ATTR_NONNULL((2)) int
(__LIBCCALL __LIBC_LOCAL_NAME(putw_unlocked))(int __w, __FILE *__restrict __stream) __THROWS(...) {
	return __localdep_putw(__w, __stream);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_putw_unlocked_defined
#define __local___localdep_putw_unlocked_defined 1
#define __localdep_putw_unlocked __LIBC_LOCAL_NAME(putw_unlocked)
#endif /* !__local___localdep_putw_unlocked_defined */
#else /* __CRT_HAVE_putw || __CRT_HAVE__putw || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite */
#undef __local_putw_unlocked_defined
#endif /* !__CRT_HAVE_putw && !__CRT_HAVE__putw && !__CRT_HAVE_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock && !__CRT_HAVE__IO_fwrite */
#endif /* !__local_putw_unlocked_defined */
