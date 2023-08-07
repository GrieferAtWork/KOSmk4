/* HASH CRC-32:0x41949415 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_insline_defined
#define __local_insline_defined
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE__cputs) || (defined(__CRT_HAVE__putch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__putch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__cputs_defined
#define __local___localdep__cputs_defined
#ifdef __CRT_HAVE__cputs
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep__cputs,(char const *__restrict __str),_cputs,(__str))
#elif (defined(__CRT_HAVE__putch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__putch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
__NAMESPACE_LOCAL_END
#include <libc/local/conio/_cputs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__cputs __LIBC_LOCAL_NAME(_cputs)
#else /* ... */
#undef __local___localdep__cputs_defined
#endif /* !... */
#endif /* !__local___localdep__cputs_defined */
__LOCAL_LIBC(insline) void
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(insline))(void) {
	(__NAMESPACE_LOCAL_SYM __localdep__cputs)("\033[L"); /* AC_IL("1") */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_insline_defined
#define __local___localdep_insline_defined
#define __localdep_insline __LIBC_LOCAL_NAME(insline)
#endif /* !__local___localdep_insline_defined */
#else /* __CRT_HAVE__cputs || (__CRT_HAVE__putch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__putch || (__CRT_HAVE_stdtty && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#undef __local_insline_defined
#endif /* !__CRT_HAVE__cputs && (!__CRT_HAVE__putch_nolock || !__USE_STDIO_UNLOCKED) && !__CRT_HAVE__putch && (!__CRT_HAVE_stdtty || (!__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock)) */
#endif /* !__local_insline_defined */
