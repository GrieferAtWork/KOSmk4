/* HASH CRC-32:0x3d9086f9 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local___conio_common_vcscanf_defined
#define __local___conio_common_vcscanf_defined
#include <__crt.h>
#include <features.h>
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#if ((defined(__CRT_HAVE__getche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getche) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getche_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)))))) && ((defined(__CRT_HAVE__ungetch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__getche_defined
#define __local___localdep__getche_defined
#if defined(__CRT_HAVE__getche_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__getche,(void),_getche_nolock,())
#elif defined(__CRT_HAVE__getche)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__getche,(void),_getche,())
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getche_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))))
__NAMESPACE_LOCAL_END
#include <libc/local/conio/_getche.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__getche __LIBC_LOCAL_NAME(_getche)
#else /* ... */
#undef __local___localdep__getche_defined
#endif /* !... */
#endif /* !__local___localdep__getche_defined */
#ifndef __local___localdep__ungetch_defined
#define __local___localdep__ungetch_defined
#if defined(__CRT_HAVE__ungetch_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep__ungetch,(int __ch),_ungetch_nolock,(__ch))
#elif defined(__CRT_HAVE__ungetch)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep__ungetch,(int __ch),_ungetch,(__ch))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
__NAMESPACE_LOCAL_END
#include <libc/local/conio/_ungetch.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ungetch __LIBC_LOCAL_NAME(_ungetch)
#else /* ... */
#undef __local___localdep__ungetch_defined
#endif /* !... */
#endif /* !__local___localdep__ungetch_defined */
#ifndef __local___localdep_format_vscanf_defined
#define __local___localdep_format_vscanf_defined
#ifdef __CRT_HAVE_format_vscanf
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(4) __ATTR_LIBC_SCANF(4, 0) __ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__localdep_format_vscanf,(__pformatgetc __pgetc, __pformatungetc __pungetc, void *__arg, char const *__restrict __format, __builtin_va_list __args),format_vscanf,(__pgetc,__pungetc,__arg,__format,__args))
#else /* __CRT_HAVE_format_vscanf */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_vscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vscanf __LIBC_LOCAL_NAME(format_vscanf)
#endif /* !__CRT_HAVE_format_vscanf */
#endif /* !__local___localdep_format_vscanf_defined */
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__conio_common_vcscanf_getc) __format_word_t
(__FORMATPRINTER_CC __conio_common_vcscanf_getc)(void *__UNUSED(__arg)) {
	return (__format_word_t)(__NAMESPACE_LOCAL_SYM __localdep__getche)();
}
__LOCAL_LIBC(__conio_common_vcscanf_ungetc) __SSIZE_TYPE__
(__FORMATPRINTER_CC __conio_common_vcscanf_ungetc)(void *__UNUSED(__arg), __format_word_t __word) {
	return (__NAMESPACE_LOCAL_SYM __localdep__ungetch)((int)(unsigned char)(unsigned int)__word);
}
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__conio_common_vcscanf) __ATTR_WUNUSED __ATTR_IN(2) __ATTR_LIBC_SCANF(2, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__conio_common_vcscanf))(__UINT64_TYPE__ __options, char const *__format, __locale_t __locale, __builtin_va_list __args) {
	(void)__options;
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_format_vscanf)(&__NAMESPACE_LOCAL_SYM __conio_common_vcscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM __conio_common_vcscanf_ungetc,
	                     __NULLPTR, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___conio_common_vcscanf_defined
#define __local___localdep___conio_common_vcscanf_defined
#define __localdep___conio_common_vcscanf __LIBC_LOCAL_NAME(__conio_common_vcscanf)
#endif /* !__local___localdep___conio_common_vcscanf_defined */
#else /* ((__CRT_HAVE__getche_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getche || (__CRT_HAVE_stdtty && (__CRT_HAVE__getche_nolock || (__ECHO && __TCSANOW && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_HAVE_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow))) || (__CRT_HAVE_fgetc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow))) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow))) || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl))))) && ((__CRT_HAVE__ungetch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock))) */
#undef __local___conio_common_vcscanf_defined
#endif /* ((!__CRT_HAVE__getche_nolock || !__USE_STDIO_UNLOCKED) && !__CRT_HAVE__getche && (!__CRT_HAVE_stdtty || (!__CRT_HAVE__getche_nolock && (!__ECHO || !__TCSANOW || (!__CRT_HAVE_fileno && !__CRT_HAVE__fileno && !__CRT_HAVE_fileno_unlocked) || (!__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && !__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_tcgetattr && !__CRT_HAVE___tcgetattr && ((!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__TCGETA)) || (!__CRT_HAVE_tcsetattr && !__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl))))) || ((!__CRT_HAVE__ungetch_nolock || !__USE_STDIO_UNLOCKED) && !__CRT_HAVE__ungetch && (!__CRT_HAVE_stdtty || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock))) */
#endif /* !__local___conio_common_vcscanf_defined */
