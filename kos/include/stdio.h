/* HASH CRC-32:0xf9e1a50c */
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
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/stdio.h) */
/* (#) Portability: DJGPP         (/include/stdio.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/stdio.h) */
/* (#) Portability: FreeBSD       (/include/stdio.h) */
/* (#) Portability: GNU C Library (/libio/stdio.h) */
/* (#) Portability: MSVC          (/include/stdio.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/stdio.h) */
/* (#) Portability: NetBSD        (/include/stdio.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/stdio.h) */
/* (#) Portability: OpenBSD       (/include/stdio.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/stdio.h) */
/* (#) Portability: PDCLib        (/include/stdio.h) */
/* (#) Portability: Windows Kits  (/ucrt/stdio.h) */
/* (#) Portability: avr-libc      (/include/stdio.h) */
/* (#) Portability: diet libc     (/include/stdio.h) */
/* (#) Portability: libbsd        (/include/bsd/stdio.h) */
/* (#) Portability: libc4/5       (/include/stdio.h) */
/* (#) Portability: libc6         (/include/stdio.h) */
/* (#) Portability: libcmini      (/include/stdio.h) */
/* (#) Portability: mintlib       (/include/stdio.h) */
/* (#) Portability: musl libc     (/include/stdio.h) */
/* (#) Portability: uClibc        (/include/stdio.h) */
#ifndef _STDIO_H
#define _STDIO_H 1

#ifdef _CXX_STDONLY_CSTDIO
#ifdef __CXX_SYSTEM_HEADER
#undef _STDIO_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "stdio.h" after "cstdio" */
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __fpos_t_defined
#define __fpos_t_defined
__NAMESPACE_STD_USING(fpos_t)
#endif /* !__fpos_t_defined */
#ifndef __FILE_defined
#define __FILE_defined
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#if !defined(__remove_defined) && defined(__std_remove_defined)
#define __remove_defined
__NAMESPACE_STD_USING(remove)
#endif /* !__remove_defined && __std_remove_defined */
#if !defined(__rename_defined) && defined(__std_rename_defined)
#define __rename_defined
__NAMESPACE_STD_USING(rename)
#endif /* !__rename_defined && __std_rename_defined */
#ifdef __CRT_HAVE_tmpnam
__NAMESPACE_STD_USING(tmpnam)
#endif /* __CRT_HAVE_tmpnam */
#if defined(__CRT_HAVE_fclose) || defined(__CRT_HAVE__fclose_nolock) || defined(__CRT_HAVE__IO_fclose)
__NAMESPACE_STD_USING(fclose)
#endif /* __CRT_HAVE_fclose || __CRT_HAVE__fclose_nolock || __CRT_HAVE__IO_fclose */
__NAMESPACE_STD_USING(fflush)
#include <asm/crt/stdio.h>
#include <features.h>
#if defined(__CRT_HAVE_setbuf) || (defined(___IOFBF) && defined(___IONBF) && defined(__BUFSIZ) && (defined(__CRT_HAVE_setvbuf) || defined(__CRT_HAVE__IO_setvbuf) || defined(__CRT_HAVE_setvbuf_unlocked)))
__NAMESPACE_STD_USING(setbuf)
#endif /* __CRT_HAVE_setbuf || (___IOFBF && ___IONBF && __BUFSIZ && (__CRT_HAVE_setvbuf || __CRT_HAVE__IO_setvbuf || __CRT_HAVE_setvbuf_unlocked)) */
#if defined(__CRT_HAVE_setvbuf) || defined(__CRT_HAVE__IO_setvbuf) || defined(__CRT_HAVE_setvbuf_unlocked)
__NAMESPACE_STD_USING(setvbuf)
#endif /* __CRT_HAVE_setvbuf || __CRT_HAVE__IO_setvbuf || __CRT_HAVE_setvbuf_unlocked */
#if defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_STD_USING(fgetc)
__NAMESPACE_STD_USING(getc)
#endif /* __CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock */
#include <libc/template/stdstreams.h>
#if (defined(__CRT_HAVE_getchar_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_getchar) || defined(__CRT_HAVE__fgetchar) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))
__NAMESPACE_STD_USING(getchar)
#endif /* (__CRT_HAVE_getchar_unlocked && __USE_STDIO_UNLOCKED) || __CRT_HAVE_getchar || __CRT_HAVE__fgetchar || (__LOCAL_stdin && (__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock)) */
#if defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_STD_USING(fputc)
__NAMESPACE_STD_USING(putc)
#endif /* __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock */
#if defined(__CRT_HAVE_putchar) || defined(__CRT_HAVE__fputchar) || defined(__CRT_HAVE_putchar_unlocked) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
__NAMESPACE_STD_USING(putchar)
#endif /* __CRT_HAVE_putchar || __CRT_HAVE__fputchar || __CRT_HAVE_putchar_unlocked || (__LOCAL_stdout && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#if defined(__CRT_HAVE_fgets) || defined(__CRT_HAVE__IO_fgets) || defined(__CRT_HAVE_fgets_unlocked) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)))
__NAMESPACE_STD_USING(fgets)
#endif /* __CRT_HAVE_fgets || __CRT_HAVE__IO_fgets || __CRT_HAVE_fgets_unlocked || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked)) */
#if defined(__CRT_HAVE_fputs) || defined(__CRT_HAVE__IO_fputs) || defined(__CRT_HAVE_fputs_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_STD_USING(fputs)
#endif /* __CRT_HAVE_fputs || __CRT_HAVE__IO_fputs || __CRT_HAVE_fputs_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock */
#if defined(__CRT_HAVE_puts) || defined(__CRT_HAVE__IO_puts) || defined(__CRT_HAVE_puts_unlocked) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
__NAMESPACE_STD_USING(puts)
#endif /* __CRT_HAVE_puts || __CRT_HAVE__IO_puts || __CRT_HAVE_puts_unlocked || (__LOCAL_stdout && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#if defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)
__NAMESPACE_STD_USING(ungetc)
#endif /* __CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock */
#if defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_STD_USING(fread)
#endif /* __CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock */
#if defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_STD_USING(fwrite)
#endif /* __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock */
#include <bits/types.h>
#if defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock)
__NAMESPACE_STD_USING(fseek)
#endif /* __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock */
#if defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked)
__NAMESPACE_STD_USING(ftell)
#endif /* __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock || __CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello64 || __CRT_HAVE_ftell64 || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE_ftell64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked */
#include <bits/crt/stdio.h>
#if defined(__CRT_HAVE_rewind) || defined(__CRT_HAVE_rewind_unlocked) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
__NAMESPACE_STD_USING(rewind)
#endif /* __CRT_HAVE_rewind || __CRT_HAVE_rewind_unlocked || __CRT_HAVE_fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || __CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock */
#if defined(__CRT_HAVE_clearerr) || defined(__CRT_HAVE_clearerr_unlocked)
__NAMESPACE_STD_USING(clearerr)
#endif /* __CRT_HAVE_clearerr || __CRT_HAVE_clearerr_unlocked */
#if defined(__CRT_HAVE_feof) || defined(__CRT_HAVE__IO_feof) || defined(__CRT_HAVE_feof_unlocked)
__NAMESPACE_STD_USING(feof)
#endif /* __CRT_HAVE_feof || __CRT_HAVE__IO_feof || __CRT_HAVE_feof_unlocked */
#if defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)
__NAMESPACE_STD_USING(ferror)
#endif /* __CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked */
#if !defined(__perror_defined) && defined(__std_perror_defined)
#define __perror_defined
__NAMESPACE_STD_USING(perror)
#endif /* !__perror_defined && __std_perror_defined */
#include <asm/os/oflags.h>
#if (defined(__CRT_HAVE_tmpfile) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_tmpfile64)
__NAMESPACE_STD_USING(tmpfile)
#endif /* (__CRT_HAVE_tmpfile && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_tmpfile64 */
#if (defined(__CRT_HAVE_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || (defined(__CRT_HAVE__IO_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_fopen64)
__NAMESPACE_STD_USING(fopen)
#endif /* (__CRT_HAVE_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || (__CRT_HAVE__IO_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_fopen64 */
#if (defined(__CRT_HAVE_freopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_freopen64) || (defined(__CRT_HAVE_freopen_unlocked) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_freopen64_unlocked)
__NAMESPACE_STD_USING(freopen)
#endif /* (__CRT_HAVE_freopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_freopen64 || (__CRT_HAVE_freopen_unlocked && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_freopen64_unlocked */
#if defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
__NAMESPACE_STD_USING(fgetpos)
#endif /* __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_ftello64 || __CRT_HAVE_ftell64 || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE_ftell64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock */
#if defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
__NAMESPACE_STD_USING(fsetpos)
#endif /* __CRT_HAVE_fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || __CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock */
#if defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_STD_USING(vfprintf)
#endif /* __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock */
#if defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_STD_USING(fprintf)
#endif /* __CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock */
#if defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
__NAMESPACE_STD_USING(vprintf)
#endif /* __CRT_HAVE_vprintf || __CRT_HAVE_vprintf_s || __CRT_HAVE_vprintf_unlocked || (__LOCAL_stdout && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#if defined(__CRT_HAVE_printf) || defined(__CRT_HAVE__IO_printf) || defined(__CRT_HAVE_printf_s) || defined(__CRT_HAVE_printf_unlocked) || defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
__NAMESPACE_STD_USING(printf)
#endif /* __CRT_HAVE_printf || __CRT_HAVE__IO_printf || __CRT_HAVE_printf_s || __CRT_HAVE_printf_unlocked || __CRT_HAVE_vprintf || __CRT_HAVE_vprintf_s || __CRT_HAVE_vprintf_unlocked || (__LOCAL_stdout && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#if !defined(__vfscanf_defined) && defined(__std_vfscanf_defined)
#define __vfscanf_defined
__NAMESPACE_STD_USING(vfscanf)
#endif /* !__vfscanf_defined && __std_vfscanf_defined */
#if !defined(__vscanf_defined) && defined(__std_vscanf_defined)
#define __vscanf_defined
__NAMESPACE_STD_USING(vscanf)
#endif /* !__vscanf_defined && __std_vscanf_defined */
#if defined(__CRT_HAVE_fscanf) || defined(__CRT_HAVE__IO_fscanf) || defined(__CRT_HAVE_fscanf_unlocked) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
__NAMESPACE_STD_USING(fscanf)
#endif /* __CRT_HAVE_fscanf || __CRT_HAVE__IO_fscanf || __CRT_HAVE_fscanf_unlocked || __CRT_HAVE_vfscanf || __CRT_HAVE__vfscanf || __CRT_HAVE__vfscanf_s || __CRT_HAVE__IO_vfscanf || __CRT_HAVE_vfscanf_unlocked || __CRT_HAVE___vfscanf || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)) */
#if defined(__CRT_HAVE_scanf) || defined(__CRT_HAVE__IO_scanf) || defined(__CRT_HAVE_scanf_unlocked) || defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf) || defined(__CRT_HAVE_vscanf_unlocked) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
__NAMESPACE_STD_USING(scanf)
#endif /* __CRT_HAVE_scanf || __CRT_HAVE__IO_scanf || __CRT_HAVE_scanf_unlocked || __CRT_HAVE_vscanf || __CRT_HAVE__vscanf || __CRT_HAVE_vscanf_unlocked || (__LOCAL_stdin && (__CRT_HAVE_vfscanf || __CRT_HAVE__vfscanf || __CRT_HAVE__vfscanf_s || __CRT_HAVE__IO_vfscanf || __CRT_HAVE_vfscanf_unlocked || __CRT_HAVE___vfscanf || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)))) */
#if !defined(__gets_defined) && defined(__std_gets_defined)
#define __gets_defined
__NAMESPACE_STD_USING(gets)
#endif /* !__gets_defined && __std_gets_defined */
#if !defined(__vsscanf_defined) && defined(__std_vsscanf_defined)
#define __vsscanf_defined
__NAMESPACE_STD_USING(vsscanf)
#endif /* !__vsscanf_defined && __std_vsscanf_defined */
__NAMESPACE_STD_USING(sscanf)
__NAMESPACE_STD_USING(vsprintf)
__NAMESPACE_STD_USING(sprintf)
#if !defined(__vsnprintf_defined) && defined(__std_vsnprintf_defined)
#define __vsnprintf_defined
__NAMESPACE_STD_USING(vsnprintf)
#endif /* !__vsnprintf_defined && __std_vsnprintf_defined */
#if !defined(__snprintf_defined) && defined(__std_snprintf_defined)
#define __snprintf_defined
__NAMESPACE_STD_USING(snprintf)
#endif /* !__snprintf_defined && __std_snprintf_defined */
#undef _CXX_STDONLY_CSTDIO
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CSTDIO */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/crt/stdio.h>
#include <asm/os/limits.h> /* __IOV_MAX */
#include <asm/os/oflags.h>
#include <asm/os/stdio.h>
#include <bits/crt/stdio.h> /* __fpos32_t, __fpos64_t */
#include <bits/types.h>
#include <kos/anno.h>

#include <libio.h>

#ifdef __USE_KOS
#include <bits/crt/format-printer.h>
#endif /* __USE_KOS */

#ifdef __USE_DOS
#include <bits/crt/sys_errlist.h>
#include <xlocale.h>
#endif /* __USE_DOS */

#ifdef __CRT_CYG_PRIMARY
#include <sys/reent.h>
#endif /* __CRT_CYG_PRIMARY */

__SYSDECL_BEGIN

/* The possibilities for the third argument to `setvbuf()'. */
#ifdef ___IOFBF
#define _IOFBF ___IOFBF /* Fully buffered. */
#endif /* ___IOFBF */
#ifdef ___IOLBF
#define _IOLBF ___IOLBF /* Line buffered. */
#endif /* ___IOLBF */
#ifdef ___IONBF
#define _IONBF ___IONBF /* No buffering. */
#endif /* ___IONBF */

/* Default buffer size.  */
#ifndef BUFSIZ
#define BUFSIZ __BUFSIZ
#endif /* !BUFSIZ */

#ifndef EOF
#define EOF __EOF
#endif /* !EOF */

#if !defined(SEEK_SET) && defined(__SEEK_SET)
#define SEEK_SET __SEEK_SET /* Seek from beginning of file. */
#endif /* !SEEK_SET && __SEEK_SET */
#if !defined(SEEK_CUR) && defined(__SEEK_CUR)
#define SEEK_CUR __SEEK_CUR /* Seek from current position. */
#endif /* !SEEK_CUR && __SEEK_CUR */
#if !defined(SEEK_END) && defined(__SEEK_END)
#define SEEK_END __SEEK_END /* Seek from end of file. */
#endif /* !SEEK_END && __SEEK_END */
#if defined(__USE_GNU) || defined(__USE_SOLARIS)
#if !defined(SEEK_DATA) && defined(__SEEK_DATA)
#define SEEK_DATA __SEEK_DATA /* Seek to next data. */
#endif /* !SEEK_DATA && __SEEK_DATA */
#if !defined(SEEK_HOLE) && defined(__SEEK_HOLE)
#define SEEK_HOLE __SEEK_HOLE /* Seek to next hole. */
#endif /* !SEEK_HOLE && __SEEK_HOLE */
#endif /* __USE_GNU || __USE_SOLARIS */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifdef __CRT_DOS_PRIMARY
#define P_tmpdir "\\"
#else /* __CRT_DOS_PRIMARY */
#define P_tmpdir "/tmp"
#endif /* !__CRT_DOS_PRIMARY */
#endif /* __USE_MISC || __USE_XOPEN */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

/* Minimum buffer size for temporary file names */
#if !defined(L_tmpnam) && defined(__L_tmpnam)
#define L_tmpnam __L_tmpnam
#endif /* !L_tmpnam && __L_tmpnam */

/* Recommended buffer size for file names. */
#if !defined(FILENAME_MAX) && defined(__FILENAME_MAX)
#define FILENAME_MAX __FILENAME_MAX
#endif /* !FILENAME_MAX && __FILENAME_MAX */

/* Min # of unique temporary file names what can be generated by `tmpnam()' */
#if !defined(TMP_MAX) && defined(__TMP_MAX)
#define TMP_MAX __TMP_MAX
#endif /* !TMP_MAX && __TMP_MAX */

#ifdef __USE_POSIX
/* - Max # of characters in the string returned by `ctermid()'
 * - Buffer size that must be passed to `ctermid_r()' */
#if !defined(L_ctermid) && defined(__L_ctermid)
#define L_ctermid __L_ctermid
#endif /* !L_ctermid && __L_ctermid */

#if !defined(__USE_XOPEN2K) || defined(__USE_GNU)
/* Max # of characters in the string returned by `cuserid()' */
#if !defined(L_cuserid) && defined(__L_cuserid)
#define L_cuserid __L_cuserid
#endif /* !L_cuserid && __L_cuserid */
#endif /* !__USE_XOPEN2K || __USE_GNU */
#endif /* __USE_POSIX */

#ifndef FOPEN_MAX
#ifdef __CRT_DOS_PRIMARY
#define FOPEN_MAX 20
#else /* __CRT_DOS_PRIMARY */
#define FOPEN_MAX 16
#endif /* !__CRT_DOS_PRIMARY */
#endif /* !FOPEN_MAX */

#ifndef IOV_MAX
/* [default:_POSIX_UIO_MAXIOV] Max # of elements in a `struct iovec' vector. */
#if defined(__IOV_MAX) && __IOV_MAX != -1
#define IOV_MAX __IOV_MAX
#else /* __IOV_MAX != -1 */
#define IOV_MAX 16 /* 16 == _XOPEN_IOV_MAX */
#endif /* __IOV_MAX == -1 */
#endif /* !IOV_MAX */

#ifdef __USE_GNU
#if !defined(RENAME_NOREPLACE) && defined(__RENAME_NOREPLACE)
#define RENAME_NOREPLACE __RENAME_NOREPLACE /* Don't overwrite target */
#endif /* !RENAME_NOREPLACE && __RENAME_NOREPLACE */
#if !defined(RENAME_EXCHANGE) && defined(__RENAME_EXCHANGE)
#define RENAME_EXCHANGE  __RENAME_EXCHANGE  /* Exchange source and dest */
#endif /* !RENAME_EXCHANGE && __RENAME_EXCHANGE */
#if !defined(RENAME_WHITEOUT) && defined(__RENAME_WHITEOUT)
#define RENAME_WHITEOUT  __RENAME_WHITEOUT  /* Whiteout source */
#endif /* !RENAME_WHITEOUT && __RENAME_WHITEOUT */
#endif /* __USE_GNU */

#ifdef __USE_KOS
#if !defined(AT_RENAME_NOREPLACE) && defined(__RENAME_NOREPLACE)
#define AT_RENAME_NOREPLACE __RENAME_NOREPLACE /* Don't overwrite target */
#endif /* !AT_RENAME_NOREPLACE && __RENAME_NOREPLACE */
#if !defined(AT_RENAME_EXCHANGE) && defined(__RENAME_EXCHANGE)
#define AT_RENAME_EXCHANGE  __RENAME_EXCHANGE  /* Exchange source and dest */
#endif /* !AT_RENAME_EXCHANGE && __RENAME_EXCHANGE */
#if !defined(AT_RENAME_WHITEOUT) && defined(__RENAME_WHITEOUT)
#define AT_RENAME_WHITEOUT  __RENAME_WHITEOUT  /* Whiteout source */
#endif /* !AT_RENAME_WHITEOUT && __RENAME_WHITEOUT */
#if !defined(AT_RENAME_MOVETODIR) && defined(__RENAME_MOVETODIR)
#define AT_RENAME_MOVETODIR __RENAME_MOVETODIR /* If `newpath' is a directory, move `oldpath' into it. */
#endif /* !AT_RENAME_MOVETODIR && __RENAME_MOVETODIR */
#endif /* __USE_KOS */


#ifdef __CC__
#ifndef __std_size_t_defined
#define __std_size_t_defined
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */
#ifndef __CXX_SYSTEM_HEADER
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_XOPEN2K8
#ifndef __off_t_defined
#define __off_t_defined
typedef __FS_TYPE(off) off_t;
#endif /* !__off_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifdef __USE_LARGEFILE64
#ifndef __off64_t_defined
#define __off64_t_defined
typedef __off64_t off64_t;
#endif /* !__off64_t_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN2K8 */

#ifndef __std_fpos_t_defined
#define __std_fpos_t_defined
__NAMESPACE_STD_BEGIN
typedef __FS_TYPE(fpos) fpos_t;
__NAMESPACE_STD_END
#endif /* !__std_fpos_t_defined */
#ifndef __CXX_SYSTEM_HEADER
#ifndef __fpos_t_defined
#define __fpos_t_defined
__NAMESPACE_STD_USING(fpos_t)
#endif /* !__fpos_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_LARGEFILE64
#ifndef __fpos64_t_defined
#define __fpos64_t_defined
typedef __fpos64_t fpos64_t;
#endif /* !__fpos64_t_defined */
#endif /* __USE_LARGEFILE64 */

#ifndef __std_FILE_defined
#define __std_FILE_defined
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */
#ifndef __CXX_SYSTEM_HEADER
#ifndef __FILE_defined
#define __FILE_defined
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#endif /* !__CXX_SYSTEM_HEADER */


/************************************************************************/
/* STDIO standard streams (stdin, stdout, stderr)                       */
/************************************************************************/

/* Define symbols needed for stdio FILE access */
#if defined(__CYG_REENT)
/* nothing */
#elif !defined(___iob_defined) && defined(__CRT_HAVE__iob)
#include <bits/crt/io-file.h>
#define ___iob_defined
__CSDECLARE2(,__FILE _iob[],_iob)
#ifndef ____iob_func_defined
#define ____iob_func_defined
#define __iob_func() (_iob)
#endif /* !____iob_func_defined */
#elif !defined(____p__iob_defined) && defined(__CRT_HAVE___p__iob)
#include <bits/crt/io-file.h>
#define ____p__iob_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__FILE *,__NOTHROW,__p__iob,(void),())
#ifndef ____iob_func_defined
#define ____iob_func_defined
#define __iob_func __p__iob
#endif /* !____iob_func_defined */
#elif !defined(____iob_func_defined) && defined(__CRT_HAVE___iob_func)
#include <bits/crt/io-file.h>
#define ____iob_func_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,__FILE *,__NOTHROW,__iob_func,(void),())
#endif /* ... */


/* ===== stdin ============================== */
#ifndef stdin
#ifdef __LOCAL_stdin
#define stdin __LOCAL_stdin
#elif defined(__CRT_HAVE_stdin)
__CSDECLARE(,__FILE *,stdin)
#define stdin stdin
#elif defined(__CYG_REENT)
#define stdin (__CYG_REENT->__cyg_stdin)
#elif defined(____iob_func_defined)
#define stdin (__iob_func() + 0)
#elif defined(__CRT_HAVE__IO_stdin_)
#ifndef _IO_stdin_
__CSDECLARE(,__FILE,_IO_stdin_)
#define _IO_stdin_ _IO_stdin_
#endif /* !_IO_stdin_ */
#define stdin (&_IO_stdin_)
#elif defined(__CRT_HAVE__IO_2_1_stdin_)
#ifndef _IO_2_1_stdin_
__CSDECLARE(,__FILE,_IO_2_1_stdin_)
#define _IO_2_1_stdin_ _IO_2_1_stdin_
#endif /* !_IO_2_1_stdin_ */
#define stdin (&_IO_2_1_stdin_)
#endif /* ... */
#endif /* !stdin */


/* ===== stdout ============================= */
#ifndef stdout
#ifdef __LOCAL_stdout
#define stdout __LOCAL_stdout
#elif defined(__CRT_HAVE_stdout)
__CSDECLARE(,__FILE *,stdout)
#define stdout stdout
#elif defined(__CYG_REENT)
#define stdout (__CYG_REENT->__cyg_stdout)
#elif defined(____iob_func_defined)
#define stdout (__iob_func() + 1)
#elif defined(__CRT_HAVE__IO_stdout_)
#ifndef _IO_stdout_
__CSDECLARE(,__FILE,_IO_stdout_)
#define _IO_stdout_ _IO_stdout_
#endif /* !_IO_stdout_ */
#define stdout (&_IO_stdout_)
#elif defined(__CRT_HAVE__IO_2_1_stdout_)
#ifndef _IO_2_1_stdout_
__CSDECLARE(,__FILE,_IO_2_1_stdout_)
#define _IO_2_1_stdout_ _IO_2_1_stdout_
#endif /* !_IO_2_1_stdout_ */
#define stdout (&_IO_2_1_stdout_)
#endif /* ... */
#endif /* !stdout */


/* ===== stderr ============================= */
#ifndef stderr
#ifdef __LOCAL_stderr
#define stderr __LOCAL_stderr
#elif defined(__CRT_HAVE_stderr)
__CSDECLARE(,__FILE *,stderr)
#define stderr stderr
#elif defined(__CYG_REENT)
#define stderr (__CYG_REENT->__cyg_stderr)
#elif defined(____iob_func_defined)
#define stderr (__iob_func() + 2)
#elif defined(__CRT_HAVE__IO_stderr_)
#ifndef _IO_stderr_
__CSDECLARE(,__FILE,_IO_stderr_)
#define _IO_stderr_ _IO_stderr_
#endif /* !_IO_stderr_ */
#define stderr (&_IO_stderr_)
#elif defined(__CRT_HAVE__IO_2_1_stderr_)
#ifndef _IO_2_1_stderr_
__CSDECLARE(,__FILE,_IO_2_1_stderr_)
#define _IO_2_1_stderr_ _IO_2_1_stderr_
#endif /* !_IO_2_1_stderr_ */
#define stderr (&_IO_2_1_stderr_)
#endif /* ... */
#endif /* !stderr */


/* KOS-extension: standard file stream for `/dev/tty' */
#if defined(__USE_KOS) && !defined(stdtty) && defined(__CRT_HAVE_stdtty)
__CSDECLARE(,__FILE *,stdtty)
#define stdtty stdtty
#endif /* __USE_KOS && !stdtty && __CRT_HAVE_stdtty */

__NAMESPACE_STD_BEGIN
#ifndef __std_remove_defined
#define __std_remove_defined
#ifdef __remove_defined
/* >> remove(3)
 * Remove a file or directory `filename' */
__NAMESPACE_GLB_USING_OR_IMPL(remove, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL remove)(char const *__filename) { return :: remove(__filename); })
#elif defined(__CRT_HAVE_remove)
/* >> remove(3)
 * Remove a file or directory `filename' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,remove,(char const *__filename),(__filename))
#else /* ... */
__NAMESPACE_STD_END
#include <asm/os/fcntl.h>
#include <asm/os/errno.h>
__NAMESPACE_STD_BEGIN
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_removeat) || (defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR)))))) || (defined(__EISDIR) && defined(__ENOTDIR) && (defined(__CRT_HAVE_unlink) || defined(__CRT_HAVE__unlink) || defined(__CRT_HAVE___unlink) || defined(__CRT_HAVE___libc_unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat))) && (defined(__CRT_HAVE_rmdir) || defined(__CRT_HAVE__rmdir) || defined(__CRT_HAVE___rmdir) || defined(__CRT_HAVE___libc_rmdir) || (defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat))))
__NAMESPACE_STD_END
#include <libc/local/stdio/remove.h>
__NAMESPACE_STD_BEGIN
/* >> remove(3)
 * Remove a file or directory `filename' */
__NAMESPACE_LOCAL_USING_OR_IMPL(remove, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL remove)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remove))(__filename); })
#else /* (__AT_FDCWD && (__CRT_HAVE_removeat || (__AT_REMOVEDIR && __CRT_HAVE_unlinkat && (__AT_REMOVEREG || (__EISDIR && __ENOTDIR))))) || (__EISDIR && __ENOTDIR && (__CRT_HAVE_unlink || __CRT_HAVE__unlink || __CRT_HAVE___unlink || __CRT_HAVE___libc_unlink || (__AT_FDCWD && __CRT_HAVE_unlinkat)) && (__CRT_HAVE_rmdir || __CRT_HAVE__rmdir || __CRT_HAVE___rmdir || __CRT_HAVE___libc_rmdir || (__AT_FDCWD && __AT_REMOVEDIR && __CRT_HAVE_unlinkat))) */
#undef __std_remove_defined
#endif /* (!__AT_FDCWD || (!__CRT_HAVE_removeat && (!__AT_REMOVEDIR || !__CRT_HAVE_unlinkat || (!__AT_REMOVEREG && (!__EISDIR || !__ENOTDIR))))) && (!__EISDIR || !__ENOTDIR || (!__CRT_HAVE_unlink && !__CRT_HAVE__unlink && !__CRT_HAVE___unlink && !__CRT_HAVE___libc_unlink && (!__AT_FDCWD || !__CRT_HAVE_unlinkat)) || (!__CRT_HAVE_rmdir && !__CRT_HAVE__rmdir && !__CRT_HAVE___rmdir && !__CRT_HAVE___libc_rmdir && (!__AT_FDCWD || !__AT_REMOVEDIR || !__CRT_HAVE_unlinkat))) */
#endif /* !... */
#endif /* !__std_remove_defined */
#ifndef __std_rename_defined
#define __std_rename_defined
#ifdef __rename_defined
/* >> rename(2)
 * Rename  a given file `oldname' to `newname_or_path', or in the event
 * that `newname_or_path' refers to a directory, place the file within. */
__NAMESPACE_GLB_USING_OR_IMPL(rename, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL rename)(char const *__oldname, char const *__newname_or_path) { return :: rename(__oldname, __newname_or_path); })
#elif defined(__CRT_HAVE_rename)
/* >> rename(2)
 * Rename  a given file `oldname' to `newname_or_path', or in the event
 * that `newname_or_path' refers to a directory, place the file within. */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,rename,(char const *__oldname, char const *__newname_or_path),(__oldname,__newname_or_path))
#elif defined(__CRT_HAVE___rename)
/* >> rename(2)
 * Rename  a given file `oldname' to `newname_or_path', or in the event
 * that `newname_or_path' refers to a directory, place the file within. */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,rename,(char const *__oldname, char const *__newname_or_path),__rename,(__oldname,__newname_or_path))
#elif defined(__CRT_HAVE___libc_rename)
/* >> rename(2)
 * Rename  a given file `oldname' to `newname_or_path', or in the event
 * that `newname_or_path' refers to a directory, place the file within. */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,rename,(char const *__oldname, char const *__newname_or_path),__libc_rename,(__oldname,__newname_or_path))
#else /* ... */
__NAMESPACE_STD_END
#include <asm/os/fcntl.h>
__NAMESPACE_STD_BEGIN
#if defined(__AT_FDCWD) && (defined(__CRT_HAVE_renameat) || defined(__CRT_HAVE_renameat2))
__NAMESPACE_STD_END
#include <libc/local/stdio/rename.h>
__NAMESPACE_STD_BEGIN
/* >> rename(2)
 * Rename  a given file `oldname' to `newname_or_path', or in the event
 * that `newname_or_path' refers to a directory, place the file within. */
__NAMESPACE_LOCAL_USING_OR_IMPL(rename, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL rename)(char const *__oldname, char const *__newname_or_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rename))(__oldname, __newname_or_path); })
#else /* __AT_FDCWD && (__CRT_HAVE_renameat || __CRT_HAVE_renameat2) */
#undef __std_rename_defined
#endif /* !__AT_FDCWD || (!__CRT_HAVE_renameat && !__CRT_HAVE_renameat2) */
#endif /* !... */
#endif /* !__std_rename_defined */
/* >> tmpnam(3), tmpnam_r(3) */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,tmpnam,(char *__buf),(__buf))
#ifdef __CRT_HAVE_fclose
/* >> fclose(3)
 * Close and destroy a given file `stream' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fclose,(FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__fclose_nolock)
/* >> fclose(3)
 * Close and destroy a given file `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fclose,(FILE *__restrict __stream),_fclose_nolock,(__stream))
#elif defined(__CRT_HAVE__IO_fclose)
/* >> fclose(3)
 * Close and destroy a given file `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fclose,(FILE *__restrict __stream),_IO_fclose,(__stream))
#endif /* ... */
__NAMESPACE_STD_END
#include <features.h>
__NAMESPACE_STD_BEGIN
#if defined(__CRT_HAVE_fflush_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fflush(3)
 * Flush any unwritten data from `stream' to the underlying filesystem/TTY */
__CREDIRECT(,int,__THROWING,fflush,(FILE *__stream),fflush_unlocked,(__stream))
#elif defined(__CRT_HAVE__fflush_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> fflush(3)
 * Flush any unwritten data from `stream' to the underlying filesystem/TTY */
__CREDIRECT(,int,__THROWING,fflush,(FILE *__stream),_fflush_nolock,(__stream))
#elif defined(__CRT_HAVE_fflush)
/* >> fflush(3)
 * Flush any unwritten data from `stream' to the underlying filesystem/TTY */
__CDECLARE(,int,__THROWING,fflush,(FILE *__stream),(__stream))
#elif defined(__CRT_HAVE__IO_fflush)
/* >> fflush(3)
 * Flush any unwritten data from `stream' to the underlying filesystem/TTY */
__CREDIRECT(,int,__THROWING,fflush,(FILE *__stream),_IO_fflush,(__stream))
#elif defined(__CRT_HAVE_fflush_unlocked)
/* >> fflush(3)
 * Flush any unwritten data from `stream' to the underlying filesystem/TTY */
__CREDIRECT(,int,__THROWING,fflush,(FILE *__stream),fflush_unlocked,(__stream))
#elif defined(__CRT_HAVE__fflush_nolock)
/* >> fflush(3)
 * Flush any unwritten data from `stream' to the underlying filesystem/TTY */
__CREDIRECT(,int,__THROWING,fflush,(FILE *__stream),_fflush_nolock,(__stream))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdio/fflush.h>
__NAMESPACE_STD_BEGIN
/* >> fflush(3)
 * Flush any unwritten data from `stream' to the underlying filesystem/TTY */
__NAMESPACE_LOCAL_USING_OR_IMPL(fflush, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL fflush)(FILE *__stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fflush))(__stream); })
#endif /* !... */
#ifdef __CRT_HAVE_setbuf
/* >> setbuf(3)
 * Alias for `setvbuf(stream, buf, _IOFBF, BUFSIZ)' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,setbuf,(FILE *__restrict __stream, char *__buf),(__stream,__buf))
#elif defined(___IOFBF) && defined(___IONBF) && defined(__BUFSIZ) && (defined(__CRT_HAVE_setvbuf) || defined(__CRT_HAVE__IO_setvbuf) || defined(__CRT_HAVE_setvbuf_unlocked))
__NAMESPACE_STD_END
#include <libc/local/stdio/setbuf.h>
__NAMESPACE_STD_BEGIN
/* >> setbuf(3)
 * Alias for `setvbuf(stream, buf, _IOFBF, BUFSIZ)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(setbuf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL setbuf)(FILE *__restrict __stream, char *__buf) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setbuf))(__stream, __buf); })
#endif /* ... */
#if defined(__CRT_HAVE_setvbuf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> setvbuf(3)
 * Set the buffer and buffer-mode to-be used by the given `stream'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setvbuf,(FILE *__restrict __stream, char *__restrict __buf, __STDC_INT_AS_UINT_T __modes, size_t __bufsize),setvbuf_unlocked,(__stream,__buf,__modes,__bufsize))
#elif defined(__CRT_HAVE_setvbuf)
/* >> setvbuf(3)
 * Set the buffer and buffer-mode to-be used by the given `stream'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setvbuf,(FILE *__restrict __stream, char *__restrict __buf, __STDC_INT_AS_UINT_T __modes, size_t __bufsize),(__stream,__buf,__modes,__bufsize))
#elif defined(__CRT_HAVE__IO_setvbuf)
/* >> setvbuf(3)
 * Set the buffer and buffer-mode to-be used by the given `stream'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setvbuf,(FILE *__restrict __stream, char *__restrict __buf, __STDC_INT_AS_UINT_T __modes, size_t __bufsize),_IO_setvbuf,(__stream,__buf,__modes,__bufsize))
#elif defined(__CRT_HAVE_setvbuf_unlocked)
/* >> setvbuf(3)
 * Set the buffer and buffer-mode to-be used by the given `stream'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setvbuf,(FILE *__restrict __stream, char *__restrict __buf, __STDC_INT_AS_UINT_T __modes, size_t __bufsize),setvbuf_unlocked,(__stream,__buf,__modes,__bufsize))
#endif /* ... */
#if defined(__CRT_HAVE_fgetc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getc_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),_getc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),_fgetc_nolock,(__stream))
#elif defined(__CRT_HAVE_getc)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE_fgetc)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__IO_getc)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),_IO_getc,(__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getc_nolock)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),_getc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc,(FILE *__restrict __stream),_fgetc_nolock,(__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_STD_END
#include <libc/local/stdio/fgetc.h>
__NAMESPACE_STD_BEGIN
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fgetc)(FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc))(__stream); })
#endif /* ... */
#if defined(__CRT_HAVE_fgetc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getc_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),_getc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),_fgetc_nolock,(__stream))
#elif defined(__CRT_HAVE_getc)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_fgetc)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE__IO_getc)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),_IO_getc,(__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getc_nolock)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),_getc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock)
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc,(FILE *__restrict __stream),_fgetc_nolock,(__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_STD_END
#include <libc/local/stdio/fgetc.h>
__NAMESPACE_STD_BEGIN
/* >> getc(3), fgetc(3)
 * Read and return a single character from `stream'
 * If  the given `stream' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL getc)(FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc))(__stream); }
#endif /* ... */
#if defined(__CRT_HAVE_getchar_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> getchar(3)
 * Alias for `fgetc(stdin)' */
__CREDIRECT(,int,__THROWING,getchar,(void),getchar_unlocked,())
#elif defined(__CRT_HAVE_getchar)
/* >> getchar(3)
 * Alias for `fgetc(stdin)' */
__CDECLARE(,int,__THROWING,getchar,(void),())
#elif defined(__CRT_HAVE__fgetchar)
/* >> getchar(3)
 * Alias for `fgetc(stdin)' */
__CREDIRECT(,int,__THROWING,getchar,(void),_fgetchar,())
#else /* ... */
__NAMESPACE_STD_END
#include <libc/template/stdstreams.h>
__NAMESPACE_STD_BEGIN
#if defined(__LOCAL_stdin) && (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))
__NAMESPACE_STD_END
#include <libc/local/stdio/getchar.h>
__NAMESPACE_STD_BEGIN
/* >> getchar(3)
 * Alias for `fgetc(stdin)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(getchar, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL getchar)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar))(); })
#endif /* __LOCAL_stdin && (__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) */
#endif /* !... */
#if __has_builtin(__builtin_fputc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CEIDECLARE(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),{ return __builtin_fputc(__ch, __stream); })
#elif defined(__CRT_HAVE_putc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__putc_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),_putc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE__fputc_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),_fputc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_putc)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__putc_nolock)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),_putc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE__fputc_nolock)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc,(int __ch, FILE *__restrict __stream),_fputc_nolock,(__ch,__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_STD_END
#include <libc/local/stdio/fputc.h>
__NAMESPACE_STD_BEGIN
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fputc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL fputc)(int __ch, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc))(__ch, __stream); })
#endif /* ... */
#if __has_builtin(__builtin_fputc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CEIREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),fputc,{ return __builtin_fputc(__ch, __stream); })
#elif defined(__CRT_HAVE_putc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__putc_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),_putc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE__fputc_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),_fputc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_putc)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE_fputc)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__putc_nolock)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),_putc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE__fputc_nolock)
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc,(int __ch, FILE *__restrict __stream),_fputc_nolock,(__ch,__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_STD_END
#include <libc/local/stdio/fputc.h>
__NAMESPACE_STD_BEGIN
/* >> putc(3), fputc(3)
 * Write a single character `ch' to `stream' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL putc)(int __ch, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc))(__ch, __stream); }
#endif /* ... */
#if __has_builtin(__builtin_putchar) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_putchar)
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__CEIDECLARE(,int,__THROWING,putchar,(int __ch),{ return __builtin_putchar(__ch); })
#elif defined(__CRT_HAVE_putchar_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__CREDIRECT(,int,__THROWING,putchar,(int __ch),putchar_unlocked,(__ch))
#elif defined(__CRT_HAVE_putchar)
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__CDECLARE(,int,__THROWING,putchar,(int __ch),(__ch))
#elif defined(__CRT_HAVE__fputchar)
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__CREDIRECT(,int,__THROWING,putchar,(int __ch),_fputchar,(__ch))
#elif defined(__CRT_HAVE_putchar_unlocked)
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__CREDIRECT(,int,__THROWING,putchar,(int __ch),putchar_unlocked,(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/template/stdstreams.h>
__NAMESPACE_STD_BEGIN
#if defined(__LOCAL_stdout) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
__NAMESPACE_STD_END
#include <libc/local/stdio/putchar.h>
__NAMESPACE_STD_BEGIN
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(putchar, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL putchar)(int __ch) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar))(__ch); })
#endif /* __LOCAL_stdout && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#endif /* !... */
#if defined(__CRT_HAVE_fgets_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fgets(3)
 * Read up  to  `bufsize - 1'  bytes  of  data  from  `stream',  storing  them  into  `buf'  stopped  when
 * the buffer is  full or a  line-feed was read  (in this case,  the line-feed is  also written to  `buf')
 * Afterwards, append a trailing NUL-character and re-return `buf', or return `NULL' if an error occurred. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char *,__THROWING,fgets,(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgets_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgets)
/* >> fgets(3)
 * Read up  to  `bufsize - 1'  bytes  of  data  from  `stream',  storing  them  into  `buf'  stopped  when
 * the buffer is  full or a  line-feed was read  (in this case,  the line-feed is  also written to  `buf')
 * Afterwards, append a trailing NUL-character and re-return `buf', or return `NULL' if an error occurred. */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char *,__THROWING,fgets,(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__IO_fgets)
/* >> fgets(3)
 * Read up  to  `bufsize - 1'  bytes  of  data  from  `stream',  storing  them  into  `buf'  stopped  when
 * the buffer is  full or a  line-feed was read  (in this case,  the line-feed is  also written to  `buf')
 * Afterwards, append a trailing NUL-character and re-return `buf', or return `NULL' if an error occurred. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char *,__THROWING,fgets,(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_IO_fgets,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgets_unlocked)
/* >> fgets(3)
 * Read up  to  `bufsize - 1'  bytes  of  data  from  `stream',  storing  them  into  `buf'  stopped  when
 * the buffer is  full or a  line-feed was read  (in this case,  the line-feed is  also written to  `buf')
 * Afterwards, append a trailing NUL-character and re-return `buf', or return `NULL' if an error occurred. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char *,__THROWING,fgets,(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgets_unlocked,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
__NAMESPACE_STD_END
#include <libc/local/stdio/fgets.h>
__NAMESPACE_STD_BEGIN
/* >> fgets(3)
 * Read up  to  `bufsize - 1'  bytes  of  data  from  `stream',  storing  them  into  `buf'  stopped  when
 * the buffer is  full or a  line-feed was read  (in this case,  the line-feed is  also written to  `buf')
 * Afterwards, append a trailing NUL-character and re-return `buf', or return `NULL' if an error occurred. */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgets, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) char *(__LIBCCALL fgets)(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgets))(__buf, __bufsize, __stream); })
#endif /* ... */
#if __has_builtin(__builtin_fputs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputs)
/* >> fputs(3)
 * Print a given string `string' to `stream'. This is identical to:
 * >> fwrite(string, sizeof(char), strlen(string), stream); */
__CEIDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,fputs,(char const *__restrict __string, FILE *__restrict __stream),{ return __builtin_fputs(__string, __stream); })
#elif defined(__CRT_HAVE_fputs_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fputs(3)
 * Print a given string `string' to `stream'. This is identical to:
 * >> fwrite(string, sizeof(char), strlen(string), stream); */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,fputs,(char const *__restrict __string, FILE *__restrict __stream),fputs_unlocked,(__string,__stream))
#elif defined(__CRT_HAVE_fputs)
/* >> fputs(3)
 * Print a given string `string' to `stream'. This is identical to:
 * >> fwrite(string, sizeof(char), strlen(string), stream); */
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,fputs,(char const *__restrict __string, FILE *__restrict __stream),(__string,__stream))
#elif defined(__CRT_HAVE__IO_fputs)
/* >> fputs(3)
 * Print a given string `string' to `stream'. This is identical to:
 * >> fwrite(string, sizeof(char), strlen(string), stream); */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,fputs,(char const *__restrict __string, FILE *__restrict __stream),_IO_fputs,(__string,__stream))
#elif defined(__CRT_HAVE_fputs_unlocked)
/* >> fputs(3)
 * Print a given string `string' to `stream'. This is identical to:
 * >> fwrite(string, sizeof(char), strlen(string), stream); */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,fputs,(char const *__restrict __string, FILE *__restrict __stream),fputs_unlocked,(__string,__stream))
#elif defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_STD_END
#include <libc/local/stdio/fputs.h>
__NAMESPACE_STD_BEGIN
/* >> fputs(3)
 * Print a given string `string' to `stream'. This is identical to:
 * >> fwrite(string, sizeof(char), strlen(string), stream); */
__NAMESPACE_LOCAL_USING_OR_IMPL(fputs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL fputs)(char const *__restrict __string, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputs))(__string, __stream); })
#endif /* ... */
#if __has_builtin(__builtin_puts) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_puts)
/* >> puts(3)
 * Print a given string `string', followed by a line-feed to `stdout'. This is identical to:
 * >> fputs(string, stdout);
 * >> putchar('\n');
 * Return the number of written characters, or `EOF' on error */
__CEIDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,puts,(char const *__restrict __string),{ return __builtin_puts(__string); })
#elif defined(__CRT_HAVE_puts_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> puts(3)
 * Print a given string `string', followed by a line-feed to `stdout'. This is identical to:
 * >> fputs(string, stdout);
 * >> putchar('\n');
 * Return the number of written characters, or `EOF' on error */
__CREDIRECT(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,puts,(char const *__restrict __string),puts_unlocked,(__string))
#elif defined(__CRT_HAVE_puts)
/* >> puts(3)
 * Print a given string `string', followed by a line-feed to `stdout'. This is identical to:
 * >> fputs(string, stdout);
 * >> putchar('\n');
 * Return the number of written characters, or `EOF' on error */
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,puts,(char const *__restrict __string),(__string))
#elif defined(__CRT_HAVE__IO_puts)
/* >> puts(3)
 * Print a given string `string', followed by a line-feed to `stdout'. This is identical to:
 * >> fputs(string, stdout);
 * >> putchar('\n');
 * Return the number of written characters, or `EOF' on error */
__CREDIRECT(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,puts,(char const *__restrict __string),_IO_puts,(__string))
#elif defined(__CRT_HAVE_puts_unlocked)
/* >> puts(3)
 * Print a given string `string', followed by a line-feed to `stdout'. This is identical to:
 * >> fputs(string, stdout);
 * >> putchar('\n');
 * Return the number of written characters, or `EOF' on error */
__CREDIRECT(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,puts,(char const *__restrict __string),puts_unlocked,(__string))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/template/stdstreams.h>
__NAMESPACE_STD_BEGIN
#if defined(__LOCAL_stdout) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
__NAMESPACE_STD_END
#include <libc/local/stdio/puts.h>
__NAMESPACE_STD_BEGIN
/* >> puts(3)
 * Print a given string `string', followed by a line-feed to `stdout'. This is identical to:
 * >> fputs(string, stdout);
 * >> putchar('\n');
 * Return the number of written characters, or `EOF' on error */
__NAMESPACE_LOCAL_USING_OR_IMPL(puts, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL puts)(char const *__restrict __string) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(puts))(__string); })
#endif /* __LOCAL_stdout && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#endif /* !... */
#if defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> ungetc(3)
 * Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc,(int __ch, FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> ungetc(3)
 * Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc,(int __ch, FILE *__restrict __stream),_ungetc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc)
/* >> ungetc(3)
 * Unget a single character byte of data previously returned by `getc()' */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc,(int __ch, FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE__IO_ungetc)
/* >> ungetc(3)
 * Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc,(int __ch, FILE *__restrict __stream),_IO_ungetc,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc_unlocked)
/* >> ungetc(3)
 * Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc,(int __ch, FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock)
/* >> ungetc(3)
 * Unget a single character byte of data previously returned by `getc()' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc,(int __ch, FILE *__restrict __stream),_ungetc_nolock,(__ch,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fread_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fread(3)
 * Read up to `elemsize * elemcount' bytes of data from `stream' into `buf' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),size_t,__THROWING,fread,(void *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),fread_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fread_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> fread(3)
 * Read up to `elemsize * elemcount' bytes of data from `stream' into `buf' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),size_t,__THROWING,fread,(void *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),_fread_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fread)
/* >> fread(3)
 * Read up to `elemsize * elemcount' bytes of data from `stream' into `buf' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),size_t,__THROWING,fread,(void *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fread)
/* >> fread(3)
 * Read up to `elemsize * elemcount' bytes of data from `stream' into `buf' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),size_t,__THROWING,fread,(void *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),_IO_fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fread_unlocked)
/* >> fread(3)
 * Read up to `elemsize * elemcount' bytes of data from `stream' into `buf' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),size_t,__THROWING,fread,(void *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),fread_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fread_nolock)
/* >> fread(3)
 * Read up to `elemsize * elemcount' bytes of data from `stream' into `buf' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),size_t,__THROWING,fread,(void *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),_fread_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow)))
__NAMESPACE_STD_END
#include <libc/local/stdio/fread.h>
__NAMESPACE_STD_BEGIN
/* >> fread(3)
 * Read up to `elemsize * elemcount' bytes of data from `stream' into `buf' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fread, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 4)) size_t (__LIBCCALL fread)(void *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fread))(__buf, __elemsize, __elemcount, __stream); })
#endif /* ... */
#if __has_builtin(__builtin_fwrite) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fwrite)
/* >> fwrite(3)
 * Write up to `elemsize * elemcount' bytes of data from `buf' into `stream' */
__CEIDECLARE(__ATTR_NONNULL((1, 4)),size_t,__THROWING,fwrite,(void const *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),{ return __builtin_fwrite(__buf, __elemsize, __elemcount, __stream); })
#elif defined(__CRT_HAVE_fwrite_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fwrite(3)
 * Write up to `elemsize * elemcount' bytes of data from `buf' into `stream' */
__CREDIRECT(__ATTR_NONNULL((1, 4)),size_t,__THROWING,fwrite,(void const *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),fwrite_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fwrite_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> fwrite(3)
 * Write up to `elemsize * elemcount' bytes of data from `buf' into `stream' */
__CREDIRECT(__ATTR_NONNULL((1, 4)),size_t,__THROWING,fwrite,(void const *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),_fwrite_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fwrite)
/* >> fwrite(3)
 * Write up to `elemsize * elemcount' bytes of data from `buf' into `stream' */
__CDECLARE(__ATTR_NONNULL((1, 4)),size_t,__THROWING,fwrite,(void const *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fwrite)
/* >> fwrite(3)
 * Write up to `elemsize * elemcount' bytes of data from `buf' into `stream' */
__CREDIRECT(__ATTR_NONNULL((1, 4)),size_t,__THROWING,fwrite,(void const *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),_IO_fwrite,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fwrite_s)
/* >> fwrite(3)
 * Write up to `elemsize * elemcount' bytes of data from `buf' into `stream' */
__CREDIRECT(__ATTR_NONNULL((1, 4)),size_t,__THROWING,fwrite,(void const *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),fwrite_s,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fwrite_unlocked)
/* >> fwrite(3)
 * Write up to `elemsize * elemcount' bytes of data from `buf' into `stream' */
__CREDIRECT(__ATTR_NONNULL((1, 4)),size_t,__THROWING,fwrite,(void const *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),fwrite_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fwrite_nolock)
/* >> fwrite(3)
 * Write up to `elemsize * elemcount' bytes of data from `buf' into `stream' */
__CREDIRECT(__ATTR_NONNULL((1, 4)),size_t,__THROWING,fwrite,(void const *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream),_fwrite_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf)))
__NAMESPACE_STD_END
#include <libc/local/stdio/fwrite.h>
__NAMESPACE_STD_BEGIN
/* >> fwrite(3)
 * Write up to `elemsize * elemcount' bytes of data from `buf' into `stream' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fwrite, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) size_t (__LIBCCALL fwrite)(void const *__restrict __buf, size_t __elemsize, size_t __elemcount, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwrite))(__buf, __elemsize, __elemcount, __stream); })
#endif /* ... */
#if defined(__CRT_HAVE_fseek_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek)
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseek64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked)
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock)
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek,(FILE *__restrict __stream, long int __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock)
__NAMESPACE_STD_END
#include <libc/local/stdio/fseek.h>
__NAMESPACE_STD_BEGIN
/* >> fseek(3)
 * Change the current in-file position of `stream' as a byte-offset from the start of the file */
__NAMESPACE_LOCAL_USING_OR_IMPL(fseek, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fseek)(FILE *__restrict __stream, long int __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseek))(__stream, __off, __whence); })
#endif /* ... */
#if defined(__CRT_HAVE_ftell_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell)
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__IO_ftell)
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftello64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE_ftell64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),ftell64,(__stream))
#elif defined(__CRT_HAVE__ftelli64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftell_unlocked)
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock)
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell,(FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked)
__NAMESPACE_STD_END
#include <libc/local/stdio/ftell.h>
__NAMESPACE_STD_BEGIN
/* >> ftell(3)
 * Return the current in-file position of `stream' as a byte-offset from the start of the file */
__NAMESPACE_LOCAL_USING_OR_IMPL(ftell, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) long int (__LIBCCALL ftell)(FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftell))(__stream); })
#endif /* ... */
#if defined(__CRT_HAVE_rewind_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> rewind(3)
 * Rewind the current in-file position of `stream' to its starting position */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__THROWING,rewind,(FILE *__restrict __stream),rewind_unlocked,(__stream))
#elif defined(__CRT_HAVE_rewind)
/* >> rewind(3)
 * Rewind the current in-file position of `stream' to its starting position */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,rewind,(FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_rewind_unlocked)
/* >> rewind(3)
 * Rewind the current in-file position of `stream' to its starting position */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__THROWING,rewind,(FILE *__restrict __stream),rewind_unlocked,(__stream))
#else /* ... */
__NAMESPACE_STD_END
#include <bits/crt/stdio.h>
__NAMESPACE_STD_BEGIN
#if defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
__NAMESPACE_STD_END
#include <libc/local/stdio/rewind.h>
__NAMESPACE_STD_BEGIN
/* >> rewind(3)
 * Rewind the current in-file position of `stream' to its starting position */
__NAMESPACE_LOCAL_USING_OR_IMPL(rewind, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void (__LIBCCALL rewind)(FILE *__restrict __stream) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rewind))(__stream); })
#endif /* __CRT_HAVE_fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || __CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock */
#endif /* !... */
#if defined(__CRT_HAVE_clearerr_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> clearerr(3)
 * Clear the error state of `stream', returning the stream to normal operations mode */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,clearerr,(__FILE *__restrict __stream),clearerr_unlocked,(__stream))
#elif defined(__CRT_HAVE_clearerr)
/* >> clearerr(3)
 * Clear the error state of `stream', returning the stream to normal operations mode */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,clearerr,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_clearerr_unlocked)
/* >> clearerr(3)
 * Clear the error state of `stream', returning the stream to normal operations mode */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,clearerr,(__FILE *__restrict __stream),clearerr_unlocked,(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_feof_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> feof(3)
 * Check if end-of-file has been reached in `stream' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,feof,(__FILE __KOS_FIXED_CONST *__restrict __stream),feof_unlocked,(__stream))
#elif defined(__CRT_HAVE_feof)
/* >> feof(3)
 * Check if end-of-file has been reached in `stream' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,feof,(__FILE __KOS_FIXED_CONST *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__IO_feof)
/* >> feof(3)
 * Check if end-of-file has been reached in `stream' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,feof,(__FILE __KOS_FIXED_CONST *__restrict __stream),_IO_feof,(__stream))
#elif defined(__CRT_HAVE_feof_unlocked)
/* >> feof(3)
 * Check if end-of-file has been reached in `stream' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,feof,(__FILE __KOS_FIXED_CONST *__restrict __stream),feof_unlocked,(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_ferror_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> ferror(3)
 * Check if an I/O error occurred in `stream' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ferror,(__FILE __KOS_FIXED_CONST *__restrict __stream),ferror_unlocked,(__stream))
#elif defined(__CRT_HAVE_ferror)
/* >> ferror(3)
 * Check if an I/O error occurred in `stream' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ferror,(__FILE __KOS_FIXED_CONST *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__IO_ferror)
/* >> ferror(3)
 * Check if an I/O error occurred in `stream' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ferror,(__FILE __KOS_FIXED_CONST *__restrict __stream),_IO_ferror,(__stream))
#elif defined(__CRT_HAVE_ferror_unlocked)
/* >> ferror(3)
 * Check if an I/O error occurred in `stream' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ferror,(__FILE __KOS_FIXED_CONST *__restrict __stream),ferror_unlocked,(__stream))
#endif /* ... */
#ifndef __std_perror_defined
#define __std_perror_defined
#ifdef __perror_defined
/* >> perror(3)
 * Print a given `message' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
__NAMESPACE_GLB_USING_OR_IMPL(perror, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_RPC(__LIBCCALL perror)(char const *__message) { :: perror(__message); })
#elif defined(__CRT_HAVE_perror)
/* >> perror(3)
 * Print a given `message' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
__CDECLARE_VOID(,__NOTHROW_RPC,perror,(char const *__message),(__message))
#elif defined(__CRT_HAVE__IO_perror)
/* >> perror(3)
 * Print a given `message' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
__CREDIRECT_VOID(,__NOTHROW_RPC,perror,(char const *__message),_IO_perror,(__message))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/template/stdstreams.h>
#include <libc/errno.h>
__NAMESPACE_STD_BEGIN
#if defined(__LOCAL_stderr) && defined(__libc_geterrno) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
__NAMESPACE_STD_END
#include <libc/local/stdio/perror.h>
__NAMESPACE_STD_BEGIN
/* >> perror(3)
 * Print a given `message' alongside `strerror(errno)' to stderr:
 * >> if (message) {
 * >>     fprintf(stderr, "%s: %s\n", message, strerror(errno));
 * >> } else {
 * >>     fprintf(stderr, "%s\n", strerror(errno));
 * >> } */
__NAMESPACE_LOCAL_USING_OR_IMPL(perror, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_RPC(__LIBCCALL perror)(char const *__message) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(perror))(__message); })
#else /* __LOCAL_stderr && __libc_geterrno && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef __std_perror_defined
#endif /* !__LOCAL_stderr || !__libc_geterrno || (!__CRT_HAVE_fprintf && !__CRT_HAVE__IO_fprintf && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !... */
#endif /* !__std_perror_defined */
#if defined(__CRT_HAVE_tmpfile) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> tmpfile(3), tmpfile64(3)
 * Create and return a new file-stream for accessing a temporary file for reading/writing */
__CDECLARE(__ATTR_WUNUSED,FILE *,__NOTHROW_RPC,tmpfile,(void),())
#elif defined(__CRT_HAVE_tmpfile64)
/* >> tmpfile(3), tmpfile64(3)
 * Create and return a new file-stream for accessing a temporary file for reading/writing */
__CREDIRECT(__ATTR_WUNUSED,FILE *,__NOTHROW_RPC,tmpfile,(void),tmpfile64,())
#endif /* ... */
#if defined(__CRT_HAVE_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> fopen(3), fopen64(3)
 * Create and return a new file-stream for accessing `filename' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),FILE *,__NOTHROW_RPC,fopen,(char const *__restrict __filename, char const *__restrict __modes),(__filename,__modes))
#elif defined(__CRT_HAVE__IO_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> fopen(3), fopen64(3)
 * Create and return a new file-stream for accessing `filename' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),FILE *,__NOTHROW_RPC,fopen,(char const *__restrict __filename, char const *__restrict __modes),_IO_fopen,(__filename,__modes))
#elif defined(__CRT_HAVE_fopen64)
/* >> fopen(3), fopen64(3)
 * Create and return a new file-stream for accessing `filename' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),FILE *,__NOTHROW_RPC,fopen,(char const *__restrict __filename, char const *__restrict __modes),fopen64,(__filename,__modes))
#endif /* ... */
#if defined(__CRT_HAVE_freopen_unlocked) && defined(__USE_STDIO_UNLOCKED) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),FILE *,__NOTHROW_RPC,freopen,(char const *__restrict __filename, char const *__restrict __modes, FILE *__restrict __stream),freopen_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),FILE *,__NOTHROW_RPC,freopen,(char const *__restrict __filename, char const *__restrict __modes, FILE *__restrict __stream),freopen64_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),FILE *,__NOTHROW_RPC,freopen,(char const *__restrict __filename, char const *__restrict __modes, FILE *__restrict __stream),(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),FILE *,__NOTHROW_RPC,freopen,(char const *__restrict __filename, char const *__restrict __modes, FILE *__restrict __stream),freopen64,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen_unlocked) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),FILE *,__NOTHROW_RPC,freopen,(char const *__restrict __filename, char const *__restrict __modes, FILE *__restrict __stream),freopen_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64_unlocked)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),FILE *,__NOTHROW_RPC,freopen,(char const *__restrict __filename, char const *__restrict __modes, FILE *__restrict __stream),freopen64_unlocked,(__filename,__modes,__stream))
#endif /* ... */
__NAMESPACE_STD_END
#include <bits/crt/stdio.h>
__NAMESPACE_STD_BEGIN
#if defined(__CRT_HAVE_fgetpos_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos,(FILE *__restrict __stream, fpos_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos,(FILE *__restrict __stream, fpos_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos,(FILE *__restrict __stream, fpos_t *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos,(FILE *__restrict __stream, fpos_t *__restrict __pos),_IO_fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos,(FILE *__restrict __stream, fpos_t *__restrict __pos),fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos64) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos,(FILE *__restrict __stream, fpos_t *__restrict __pos),_IO_fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos_unlocked) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos,(FILE *__restrict __stream, fpos_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos,(FILE *__restrict __stream, fpos_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
__NAMESPACE_STD_END
#include <libc/local/stdio/fgetpos.h>
__NAMESPACE_STD_BEGIN
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetpos, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int (__LIBCCALL fgetpos)(FILE *__restrict __stream, fpos_t *__restrict __pos) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetpos))(__stream, __pos); })
#endif /* ... */
#if defined(__CRT_HAVE_fsetpos_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos,(FILE *__restrict __stream, fpos_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos,(FILE *__restrict __stream, fpos_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos,(FILE *__restrict __stream, fpos_t const *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos,(FILE *__restrict __stream, fpos_t const *__restrict __pos),_IO_fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos,(FILE *__restrict __stream, fpos_t const *__restrict __pos),fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos64) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos,(FILE *__restrict __stream, fpos_t const *__restrict __pos),_IO_fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos_unlocked) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos,(FILE *__restrict __stream, fpos_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64_unlocked) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos,(FILE *__restrict __stream, fpos_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
__NAMESPACE_STD_END
#include <libc/local/stdio/fsetpos.h>
__NAMESPACE_STD_BEGIN
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fsetpos, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int (__LIBCCALL fsetpos)(FILE *__restrict __stream, fpos_t const *__restrict __pos) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fsetpos))(__stream, __pos); })
#endif /* ... */
#if __has_builtin(__builtin_vfprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfprintf)
/* >> fprintf(3), vfprintf(3)
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
__CEIDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),{ return __builtin_vfprintf(__stream, __format, __args); })
#elif defined(__CRT_HAVE_vfprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fprintf(3), vfprintf(3)
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf)
/* >> fprintf(3), vfprintf(3)
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf_s)
/* >> fprintf(3), vfprintf(3)
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_s,(__stream,__format,__args))
#elif defined(__CRT_HAVE__IO_vfprintf)
/* >> fprintf(3), vfprintf(3)
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_IO_vfprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf_unlocked)
/* >> fprintf(3), vfprintf(3)
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_STD_END
#include <libc/local/stdio/vfprintf.h>
__NAMESPACE_STD_BEGIN
/* >> fprintf(3), vfprintf(3)
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(vfprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL vfprintf)(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfprintf))(__stream, __format, __args); })
#endif /* ... */
#if __has_builtin(__builtin_fprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fprintf) && __has_builtin(__builtin_va_arg_pack)
/* >> fprintf(3), vfprintf(3)
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
__CEIDECLARE(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,fprintf,(FILE *__restrict __stream, char const *__restrict __format, ...),{ return __builtin_fprintf(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fprintf(3), vfprintf(3)
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_unlocked");
#elif defined(__CRT_HAVE_fprintf)
/* >> fprintf(3), vfprintf(3)
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fprintf");
#elif defined(__CRT_HAVE__IO_fprintf)
/* >> fprintf(3), vfprintf(3)
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("_IO_fprintf");
#elif defined(__CRT_HAVE_fprintf_s)
/* >> fprintf(3), vfprintf(3)
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_s");
#elif defined(__CRT_HAVE_fprintf_unlocked)
/* >> fprintf(3), vfprintf(3)
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_unlocked");
#elif defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_STD_END
#include <libc/local/stdio/fprintf.h>
__NAMESPACE_STD_BEGIN
/* >> fprintf(3), vfprintf(3)
 * Print  data  to  `stream',  following  `format'
 * Return the number of successfully printed bytes */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(fprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fprintf))(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__cplusplus)
#define fprintf(...) __STDC_INT_AS_SSIZE_T((__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fprintf))(__VA_ARGS__))
#else /* ... */
#define fprintf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fprintf))(__VA_ARGS__)
#endif /* !... */
#endif /* ... */
#if __has_builtin(__builtin_vprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vprintf)
/* >> printf(3), vprintf(3)
 * Print  data  to  `stdout',  following  `format'
 * Return the number of successfully printed bytes */
__CEIDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf,(char const *__restrict __format, __builtin_va_list __args),{ return __builtin_vprintf(__format, __args); })
#elif defined(__CRT_HAVE_vprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> printf(3), vprintf(3)
 * Print  data  to  `stdout',  following  `format'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf,(char const *__restrict __format, __builtin_va_list __args),vprintf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_vprintf)
/* >> printf(3), vprintf(3)
 * Print  data  to  `stdout',  following  `format'
 * Return the number of successfully printed bytes */
__CDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf,(char const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE_vprintf_s)
/* >> printf(3), vprintf(3)
 * Print  data  to  `stdout',  following  `format'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf,(char const *__restrict __format, __builtin_va_list __args),vprintf_s,(__format,__args))
#elif defined(__CRT_HAVE_vprintf_unlocked)
/* >> printf(3), vprintf(3)
 * Print  data  to  `stdout',  following  `format'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf,(char const *__restrict __format, __builtin_va_list __args),vprintf_unlocked,(__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/template/stdstreams.h>
__NAMESPACE_STD_BEGIN
#if defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
__NAMESPACE_STD_END
#include <libc/local/stdio/vprintf.h>
__NAMESPACE_STD_BEGIN
/* >> printf(3), vprintf(3)
 * Print  data  to  `stdout',  following  `format'
 * Return the number of successfully printed bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(vprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL vprintf)(char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vprintf))(__format, __args); })
#endif /* __LOCAL_stdout && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#endif /* !... */
#if __has_builtin(__builtin_printf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_printf) && __has_builtin(__builtin_va_arg_pack)
/* >> printf(3), vprintf(3)
 * Print  data  to  `stdout',  following  `format'
 * Return the number of successfully printed bytes */
__CEIDECLARE(__ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,printf,(char const *__restrict __format, ...),{ return __builtin_printf(__format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_printf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> printf(3), vprintf(3)
 * Print  data  to  `stdout',  following  `format'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("printf_unlocked");
#elif defined(__CRT_HAVE_printf)
/* >> printf(3), vprintf(3)
 * Print  data  to  `stdout',  following  `format'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("printf");
#elif defined(__CRT_HAVE__IO_printf)
/* >> printf(3), vprintf(3)
 * Print  data  to  `stdout',  following  `format'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("_IO_printf");
#elif defined(__CRT_HAVE_printf_s)
/* >> printf(3), vprintf(3)
 * Print  data  to  `stdout',  following  `format'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("printf_s");
#elif defined(__CRT_HAVE_printf_unlocked)
/* >> printf(3), vprintf(3)
 * Print  data  to  `stdout',  following  `format'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("printf_unlocked");
#else /* ... */
__NAMESPACE_STD_END
#include <libc/template/stdstreams.h>
__NAMESPACE_STD_BEGIN
#if defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
__NAMESPACE_STD_END
#include <libc/local/stdio/printf.h>
__NAMESPACE_STD_BEGIN
/* >> printf(3), vprintf(3)
 * Print  data  to  `stdout',  following  `format'
 * Return the number of successfully printed bytes */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf)(char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(printf))(__format, __builtin_va_arg_pack()); })
#elif defined(__cplusplus)
#define printf(...) __STDC_INT_AS_SSIZE_T((__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(printf))(__VA_ARGS__))
#else /* ... */
#define printf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(printf))(__VA_ARGS__)
#endif /* !... */
#endif /* __CRT_HAVE_vprintf || __CRT_HAVE_vprintf_s || __CRT_HAVE_vprintf_unlocked || (__LOCAL_stdout && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#endif /* !... */

#if defined(__USE_ISOC99) || defined(__USE_DOS)
#ifndef __std_vfscanf_defined
#define __std_vfscanf_defined
#ifdef __vfscanf_defined
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
__NAMESPACE_GLB_USING_OR_IMPL(vfscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL vfscanf)(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return :: vfscanf(__stream, __format, __args); })
#elif defined(__CRT_HAVE_vfscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfscanf_unlocked,(__stream,__format,__args))
#elif __has_builtin(__builtin_vfscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfscanf)
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),{ return __builtin_vfscanf(__stream, __format, __args); })
#elif defined(__CRT_HAVE_vfscanf)
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE__vfscanf)
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_vfscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE__vfscanf_s)
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_vfscanf_s,(__stream,__format,__args))
#elif defined(__CRT_HAVE__IO_vfscanf)
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_IO_vfscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfscanf_unlocked)
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfscanf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE___vfscanf)
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf,(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),__vfscanf,(__stream,__format,__args))
#elif (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
__NAMESPACE_STD_END
#include <libc/local/stdio/vfscanf.h>
__NAMESPACE_STD_BEGIN
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
__NAMESPACE_LOCAL_USING_OR_IMPL(vfscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL vfscanf)(FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfscanf))(__stream, __format, __args); })
#else /* ... */
#undef __std_vfscanf_defined
#endif /* !... */
#endif /* !__std_vfscanf_defined */
#ifndef __std_vscanf_defined
#define __std_vscanf_defined
#ifdef __vscanf_defined
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
__NAMESPACE_GLB_USING_OR_IMPL(vscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vscanf)(char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return :: vscanf(__format, __args); })
#elif __has_builtin(__builtin_vscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vscanf)
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf,(char const *__restrict __format, __builtin_va_list __args),{ return __builtin_vscanf(__format, __args); })
#elif defined(__CRT_HAVE_vscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf,(char const *__restrict __format, __builtin_va_list __args),vscanf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_vscanf)
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf,(char const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE__vscanf)
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf,(char const *__restrict __format, __builtin_va_list __args),_vscanf,(__format,__args))
#elif defined(__CRT_HAVE_vscanf_unlocked)
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf,(char const *__restrict __format, __builtin_va_list __args),vscanf_unlocked,(__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/template/stdstreams.h>
__NAMESPACE_STD_BEGIN
#if defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))))
__NAMESPACE_STD_END
#include <libc/local/stdio/vscanf.h>
__NAMESPACE_STD_BEGIN
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
__NAMESPACE_LOCAL_USING_OR_IMPL(vscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vscanf)(char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vscanf))(__format, __args); })
#else /* __LOCAL_stdin && (__CRT_HAVE_vfscanf || __CRT_HAVE__vfscanf || __CRT_HAVE__vfscanf_s || __CRT_HAVE__IO_vfscanf || __CRT_HAVE_vfscanf_unlocked || __CRT_HAVE___vfscanf || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock))) */
#undef __std_vscanf_defined
#endif /* !__LOCAL_stdin || (!__CRT_HAVE_vfscanf && !__CRT_HAVE__vfscanf && !__CRT_HAVE__vfscanf_s && !__CRT_HAVE__IO_vfscanf && !__CRT_HAVE_vfscanf_unlocked && !__CRT_HAVE___vfscanf && ((!__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock))) */
#endif /* !... */
#endif /* !__std_vscanf_defined */
#endif /* __USE_ISOC99 || __USE_DOS */

#if __has_builtin(__builtin_fscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fscanf) && __has_builtin(__builtin_va_arg_pack)
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fscanf,(FILE *__restrict __stream, char const *__restrict __format, ...),{ return __builtin_fscanf(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fscanf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fscanf_unlocked");
#elif defined(__CRT_HAVE_fscanf)
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fscanf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fscanf");
#elif defined(__CRT_HAVE__IO_fscanf)
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fscanf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("_IO_fscanf");
#elif defined(__CRT_HAVE_fscanf_unlocked)
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fscanf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fscanf_unlocked");
#elif defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
__NAMESPACE_STD_END
#include <libc/local/stdio/fscanf.h>
__NAMESPACE_STD_BEGIN
/* >> fscanf(3), vfscanf(3)
 * Scan  data   from   `stream',   following   `format'
 * Return the number of successfully scanned data items */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(fscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fscanf)(FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fscanf))(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__cplusplus)
#define fscanf(...) __STDC_INT_AS_SIZE_T((__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fscanf))(__VA_ARGS__))
#else /* ... */
#define fscanf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fscanf))(__VA_ARGS__)
#endif /* !... */
#endif /* ... */
#if __has_builtin(__builtin_scanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scanf) && __has_builtin(__builtin_va_arg_pack)
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,scanf,(char const *__restrict __format, ...),{ return __builtin_scanf(__format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_scanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL scanf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("scanf_unlocked");
#elif defined(__CRT_HAVE_scanf)
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL scanf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("scanf");
#elif defined(__CRT_HAVE__IO_scanf)
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL scanf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("_IO_scanf");
#elif defined(__CRT_HAVE_scanf_unlocked)
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL scanf)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("scanf_unlocked");
#else /* ... */
__NAMESPACE_STD_END
#include <libc/template/stdstreams.h>
__NAMESPACE_STD_BEGIN
#if defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf) || defined(__CRT_HAVE_vscanf_unlocked) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
__NAMESPACE_STD_END
#include <libc/local/stdio/scanf.h>
__NAMESPACE_STD_BEGIN
/* >> scanf(3), vscanf(3)
 * Scan data from `stdin', following `format'
 * Return the number of successfully scanned data items */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL scanf)(char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scanf))(__format, __builtin_va_arg_pack()); })
#elif defined(__cplusplus)
#define scanf(...) __STDC_INT_AS_SIZE_T((__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scanf))(__VA_ARGS__))
#else /* ... */
#define scanf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scanf))(__VA_ARGS__)
#endif /* !... */
#endif /* __CRT_HAVE_vscanf || __CRT_HAVE__vscanf || __CRT_HAVE_vscanf_unlocked || (__LOCAL_stdin && (__CRT_HAVE_vfscanf || __CRT_HAVE__vfscanf || __CRT_HAVE__vfscanf_s || __CRT_HAVE__IO_vfscanf || __CRT_HAVE_vfscanf_unlocked || __CRT_HAVE___vfscanf || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)))) */
#endif /* !... */

#if !defined(__USE_ISOC11) || (defined(__cplusplus) && __cplusplus <= 201103L)
#ifndef __std_gets_defined
#define __std_gets_defined
#ifdef __gets_defined
__NAMESPACE_GLB_USING_OR_IMPL(gets, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_DEPRECATED("No buffer size checks (use `fgets\' instead)") __ATTR_NONNULL((1)) char *(__LIBCCALL gets)(char *__restrict __buf) __THROWS(...) { return :: gets(__buf); })
#elif defined(__CRT_HAVE_gets)
__CDECLARE(__ATTR_WUNUSED __ATTR_DEPRECATED("No buffer size checks (use `fgets\' instead)") __ATTR_NONNULL((1)),char *,__THROWING,gets,(char *__restrict __buf),(__buf))
#elif defined(__CRT_HAVE__IO_gets)
__CREDIRECT(__ATTR_WUNUSED __ATTR_DEPRECATED("No buffer size checks (use `fgets\' instead)") __ATTR_NONNULL((1)),char *,__THROWING,gets,(char *__restrict __buf),_IO_gets,(__buf))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/template/stdstreams.h>
__NAMESPACE_STD_BEGIN
#if defined(__LOCAL_stdin) && (defined(__CRT_HAVE_fgets) || defined(__CRT_HAVE__IO_fgets) || defined(__CRT_HAVE_fgets_unlocked) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))))
__NAMESPACE_STD_END
#include <libc/local/stdio/gets.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(gets, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_DEPRECATED("No buffer size checks (use `fgets\' instead)") __ATTR_NONNULL((1)) char *(__LIBCCALL gets)(char *__restrict __buf) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gets))(__buf); })
#else /* __LOCAL_stdin && (__CRT_HAVE_fgets || __CRT_HAVE__IO_fgets || __CRT_HAVE_fgets_unlocked || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked))) */
#undef __std_gets_defined
#endif /* !__LOCAL_stdin || (!__CRT_HAVE_fgets && !__CRT_HAVE__IO_fgets && !__CRT_HAVE_fgets_unlocked && ((!__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock) || (!__CRT_HAVE_ferror && !__CRT_HAVE__IO_ferror && !__CRT_HAVE_ferror_unlocked))) */
#endif /* !... */
#endif /* !__std_gets_defined */
#endif /* !__USE_ISOC11 || __cplusplus <= 201103L */

#if defined(__USE_ISOC99) || defined(__USE_DOS)
#ifndef __std_vsscanf_defined
#define __std_vsscanf_defined
#ifdef __vsscanf_defined
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return  the  number  of successfully  scanned  data items */
__NAMESPACE_GLB_USING_OR_IMPL(vsscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsscanf)(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args) { return :: vsscanf(__input, __format, __args); })
#elif __has_builtin(__builtin_vsscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsscanf)
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return  the  number  of successfully  scanned  data items */
__CEIDECLARE_GCCNCX(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsscanf,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),{ return __builtin_vsscanf(__input, __format, __args); })
#elif defined(__CRT_HAVE_vsscanf)
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return  the  number  of successfully  scanned  data items */
__CDECLARE_GCCNCX(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsscanf,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),(__input,__format,__args))
#elif defined(__CRT_HAVE__vsscanf)
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return  the  number  of successfully  scanned  data items */
__CREDIRECT_GCCNCX(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsscanf,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),_vsscanf,(__input,__format,__args))
#elif defined(__CRT_HAVE__vsscanf_s)
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return  the  number  of successfully  scanned  data items */
__CREDIRECT_GCCNCX(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsscanf,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),_vsscanf_s,(__input,__format,__args))
#elif defined(__CRT_HAVE___vsscanf)
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return  the  number  of successfully  scanned  data items */
__CREDIRECT_GCCNCX(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsscanf,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),__vsscanf,(__input,__format,__args))
#elif defined(__CRT_HAVE__IO_vsscanf)
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return  the  number  of successfully  scanned  data items */
__CREDIRECT_GCCNCX(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsscanf,(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args),_IO_vsscanf,(__input,__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdio/vsscanf.h>
__NAMESPACE_STD_BEGIN
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return  the  number  of successfully  scanned  data items */
__NAMESPACE_LOCAL_USING_OR_IMPL(vsscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsscanf)(char const *__restrict __input, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsscanf))(__input, __format, __args); })
#endif /* !... */
#endif /* !__std_vsscanf_defined */
#endif /* __USE_ISOC99 || __USE_DOS */

#if __has_builtin(__builtin_sscanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sscanf) && __has_builtin(__builtin_va_arg_pack)
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return  the  number  of successfully  scanned  data items */
__CEIDECLARE_GCCNCX(__ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,sscanf,(char const *__restrict __input, char const *__restrict __format, ...),{ return __builtin_sscanf(__input, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_sscanf)
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return  the  number  of successfully  scanned  data items */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sscanf)(char const *__restrict __input, char const *__restrict __format, ...) __CASMNAME_SAME_GCCNCX("sscanf");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#elif defined(__CRT_HAVE__IO_sscanf)
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return  the  number  of successfully  scanned  data items */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sscanf)(char const *__restrict __input, char const *__restrict __format, ...) __CASMNAME_GCCNCX("_IO_sscanf");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdio/sscanf.h>
__NAMESPACE_STD_BEGIN
/* >> sscanf(3), vsscanf(3)
 * Scan data from a given `input' string, following `format'
 * Return  the  number  of successfully  scanned  data items */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(sscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sscanf)(char const *__restrict __input, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sscanf))(__input, __format, __builtin_va_arg_pack()); })
#elif defined(__cplusplus)
#define sscanf(...) __STDC_INT_AS_SIZE_T((__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sscanf))(__VA_ARGS__))
#else /* ... */
#define sscanf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sscanf))(__VA_ARGS__)
#endif /* !... */
#endif /* !... */
#if __has_builtin(__builtin_vsprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsprintf)
/* >> sprintf(3), vsprintf(3)
 * Print  a  formatted  string  to  a  given  in-member  string  buffer  `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
__CEIDECLARE_GCCNCX(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vsprintf,(char *__restrict __dest, char const *__restrict __format, __builtin_va_list __args),{ return __builtin_vsprintf(__dest, __format, __args); })
#elif defined(__CRT_HAVE_vsprintf)
/* >> sprintf(3), vsprintf(3)
 * Print  a  formatted  string  to  a  given  in-member  string  buffer  `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
__CDECLARE_GCCNCX(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vsprintf,(char *__restrict __dest, char const *__restrict __format, __builtin_va_list __args),(__dest,__format,__args))
#elif defined(__CRT_HAVE__IO_vsprintf)
/* >> sprintf(3), vsprintf(3)
 * Print  a  formatted  string  to  a  given  in-member  string  buffer  `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
__CREDIRECT_GCCNCX(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vsprintf,(char *__restrict __dest, char const *__restrict __format, __builtin_va_list __args),_IO_vsprintf,(__dest,__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdio/vsprintf.h>
__NAMESPACE_STD_BEGIN
/* >> sprintf(3), vsprintf(3)
 * Print  a  formatted  string  to  a  given  in-member  string  buffer  `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
__NAMESPACE_LOCAL_USING_OR_IMPL(vsprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL vsprintf)(char *__restrict __dest, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsprintf))(__dest, __format, __args); })
#endif /* !... */
#if __has_builtin(__builtin_sprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sprintf) && __has_builtin(__builtin_va_arg_pack)
/* >> sprintf(3), vsprintf(3)
 * Print  a  formatted  string  to  a  given  in-member  string  buffer  `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
__CEIDECLARE_GCCNCX(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,sprintf,(char *__restrict __buf, char const *__restrict __format, ...),{ return __builtin_sprintf(__buf, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_sprintf)
/* >> sprintf(3), vsprintf(3)
 * Print  a  formatted  string  to  a  given  in-member  string  buffer  `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME_SAME_GCCNCX("sprintf");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#elif defined(__CRT_HAVE__IO_sprintf)
/* >> sprintf(3), vsprintf(3)
 * Print  a  formatted  string  to  a  given  in-member  string  buffer  `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME_GCCNCX("_IO_sprintf");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdio/sprintf.h>
__NAMESPACE_STD_BEGIN
/* >> sprintf(3), vsprintf(3)
 * Print  a  formatted  string  to  a  given  in-member  string  buffer  `buf'
 * Return the number of written characters, excluding a trailing NUL-character */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(sprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sprintf)(char *__restrict __buf, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sprintf))(__buf, __format, __builtin_va_arg_pack()); })
#elif defined(__cplusplus)
#define sprintf(...) __STDC_INT_AS_SIZE_T((__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sprintf))(__VA_ARGS__))
#else /* ... */
#define sprintf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sprintf))(__VA_ARGS__)
#endif /* !... */
#endif /* !... */

#if defined(__USE_ISOC99) || defined(__USE_UNIX98) || defined(__USE_DOS)
#ifndef __std_vsnprintf_defined
#define __std_vsnprintf_defined
#ifdef __vsnprintf_defined
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
__NAMESPACE_GLB_USING_OR_IMPL(vsnprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsnprintf)(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args) { return :: vsnprintf(__buf, __buflen, __format, __args); })
#elif __has_builtin(__builtin_vsnprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsnprintf)
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
__CEIDECLARE_GCCNCX(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsnprintf,(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args),{ return __builtin_vsnprintf(__buf, __buflen, __format, __args); })
#elif defined(__CRT_HAVE_vsnprintf)
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
__CDECLARE_GCCNCX(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsnprintf,(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args),(__buf,__buflen,__format,__args))
#elif defined(__CRT_HAVE___vsnprintf)
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
__CREDIRECT_GCCNCX(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsnprintf,(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args),__vsnprintf,(__buf,__buflen,__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdio/vsnprintf.h>
__NAMESPACE_STD_BEGIN
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
__NAMESPACE_LOCAL_USING_OR_IMPL(vsnprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsnprintf)(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsnprintf))(__buf, __buflen, __format, __args); })
#endif /* !... */
#endif /* !__std_vsnprintf_defined */
#ifndef __std_snprintf_defined
#define __std_snprintf_defined
#ifdef __snprintf_defined
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
#if __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_GLB_USING_OR_IMPL(snprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL snprintf)(char *__restrict __buf, size_t __buflen, char const *__restrict __format, ...) { return :: snprintf(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#else /* __has_builtin(__builtin_va_arg_pack) */
__NAMESPACE_GLB_USING(snprintf)
#endif /* !__has_builtin(__builtin_va_arg_pack) */
#elif __has_builtin(__builtin_snprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_snprintf) && __has_builtin(__builtin_va_arg_pack)
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
__CEIDECLARE_GCCNCX(__ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,snprintf,(char *__restrict __buf, size_t __buflen, char const *__restrict __format, ...),{ return __builtin_snprintf(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_snprintf)
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL snprintf)(char *__restrict __buf, size_t __buflen, char const *__restrict __format, ...) __CASMNAME_SAME_GCCNCX("snprintf");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/stdio/snprintf.h>
__NAMESPACE_STD_BEGIN
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(snprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL snprintf)(char *__restrict __buf, size_t __buflen, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(snprintf))(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#elif defined(__cplusplus)
#define snprintf(...) __STDC_INT_AS_SIZE_T((__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(snprintf))(__VA_ARGS__))
#else /* ... */
#define snprintf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(snprintf))(__VA_ARGS__)
#endif /* !... */
#endif /* !... */
#endif /* !__std_snprintf_defined */
#endif /* __USE_ISOC99 || __USE_UNIX98 || __USE_DOS */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#if !defined(__remove_defined) && defined(__std_remove_defined)
#define __remove_defined
__NAMESPACE_STD_USING(remove)
#endif /* !__remove_defined && __std_remove_defined */
#if !defined(__rename_defined) && defined(__std_rename_defined)
#define __rename_defined
__NAMESPACE_STD_USING(rename)
#endif /* !__rename_defined && __std_rename_defined */
#ifdef __CRT_HAVE_tmpnam
__NAMESPACE_STD_USING(tmpnam)
#endif /* __CRT_HAVE_tmpnam */
#if defined(__CRT_HAVE_fclose) || defined(__CRT_HAVE__fclose_nolock) || defined(__CRT_HAVE__IO_fclose)
__NAMESPACE_STD_USING(fclose)
#endif /* __CRT_HAVE_fclose || __CRT_HAVE__fclose_nolock || __CRT_HAVE__IO_fclose */
__NAMESPACE_STD_USING(fflush)
#if defined(__CRT_HAVE_setbuf) || (defined(___IOFBF) && defined(___IONBF) && defined(__BUFSIZ) && (defined(__CRT_HAVE_setvbuf) || defined(__CRT_HAVE__IO_setvbuf) || defined(__CRT_HAVE_setvbuf_unlocked)))
__NAMESPACE_STD_USING(setbuf)
#endif /* __CRT_HAVE_setbuf || (___IOFBF && ___IONBF && __BUFSIZ && (__CRT_HAVE_setvbuf || __CRT_HAVE__IO_setvbuf || __CRT_HAVE_setvbuf_unlocked)) */
#if defined(__CRT_HAVE_setvbuf) || defined(__CRT_HAVE__IO_setvbuf) || defined(__CRT_HAVE_setvbuf_unlocked)
__NAMESPACE_STD_USING(setvbuf)
#endif /* __CRT_HAVE_setvbuf || __CRT_HAVE__IO_setvbuf || __CRT_HAVE_setvbuf_unlocked */
#if defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_STD_USING(fgetc)
__NAMESPACE_STD_USING(getc)
#endif /* __CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock */
#include <libc/template/stdstreams.h>
#if (defined(__CRT_HAVE_getchar_unlocked) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE_getchar) || defined(__CRT_HAVE__fgetchar) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))
__NAMESPACE_STD_USING(getchar)
#endif /* (__CRT_HAVE_getchar_unlocked && __USE_STDIO_UNLOCKED) || __CRT_HAVE_getchar || __CRT_HAVE__fgetchar || (__LOCAL_stdin && (__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock)) */
#if defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_STD_USING(fputc)
__NAMESPACE_STD_USING(putc)
#endif /* __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock */
#if defined(__CRT_HAVE_putchar) || defined(__CRT_HAVE__fputchar) || defined(__CRT_HAVE_putchar_unlocked) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
__NAMESPACE_STD_USING(putchar)
#endif /* __CRT_HAVE_putchar || __CRT_HAVE__fputchar || __CRT_HAVE_putchar_unlocked || (__LOCAL_stdout && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#if defined(__CRT_HAVE_fgets) || defined(__CRT_HAVE__IO_fgets) || defined(__CRT_HAVE_fgets_unlocked) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)))
__NAMESPACE_STD_USING(fgets)
#endif /* __CRT_HAVE_fgets || __CRT_HAVE__IO_fgets || __CRT_HAVE_fgets_unlocked || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked)) */
#if defined(__CRT_HAVE_fputs) || defined(__CRT_HAVE__IO_fputs) || defined(__CRT_HAVE_fputs_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_STD_USING(fputs)
#endif /* __CRT_HAVE_fputs || __CRT_HAVE__IO_fputs || __CRT_HAVE_fputs_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock */
#if defined(__CRT_HAVE_puts) || defined(__CRT_HAVE__IO_puts) || defined(__CRT_HAVE_puts_unlocked) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
__NAMESPACE_STD_USING(puts)
#endif /* __CRT_HAVE_puts || __CRT_HAVE__IO_puts || __CRT_HAVE_puts_unlocked || (__LOCAL_stdout && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#if defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)
__NAMESPACE_STD_USING(ungetc)
#endif /* __CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock */
#if defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_STD_USING(fread)
#endif /* __CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock */
#if defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_STD_USING(fwrite)
#endif /* __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock */
#if defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock)
__NAMESPACE_STD_USING(fseek)
#endif /* __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock */
#if defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked)
__NAMESPACE_STD_USING(ftell)
#endif /* __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock || __CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello64 || __CRT_HAVE_ftell64 || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE_ftell64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked */
#if defined(__CRT_HAVE_rewind) || defined(__CRT_HAVE_rewind_unlocked) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
__NAMESPACE_STD_USING(rewind)
#endif /* __CRT_HAVE_rewind || __CRT_HAVE_rewind_unlocked || __CRT_HAVE_fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || __CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock */
#if defined(__CRT_HAVE_clearerr) || defined(__CRT_HAVE_clearerr_unlocked)
__NAMESPACE_STD_USING(clearerr)
#endif /* __CRT_HAVE_clearerr || __CRT_HAVE_clearerr_unlocked */
#if defined(__CRT_HAVE_feof) || defined(__CRT_HAVE__IO_feof) || defined(__CRT_HAVE_feof_unlocked)
__NAMESPACE_STD_USING(feof)
#endif /* __CRT_HAVE_feof || __CRT_HAVE__IO_feof || __CRT_HAVE_feof_unlocked */
#if defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)
__NAMESPACE_STD_USING(ferror)
#endif /* __CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked */
#if !defined(__perror_defined) && defined(__std_perror_defined)
#define __perror_defined
__NAMESPACE_STD_USING(perror)
#endif /* !__perror_defined && __std_perror_defined */
#if (defined(__CRT_HAVE_tmpfile) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_tmpfile64)
__NAMESPACE_STD_USING(tmpfile)
#endif /* (__CRT_HAVE_tmpfile && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_tmpfile64 */
#if (defined(__CRT_HAVE_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || (defined(__CRT_HAVE__IO_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_fopen64)
__NAMESPACE_STD_USING(fopen)
#endif /* (__CRT_HAVE_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || (__CRT_HAVE__IO_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_fopen64 */
#if (defined(__CRT_HAVE_freopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_freopen64) || (defined(__CRT_HAVE_freopen_unlocked) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_freopen64_unlocked)
__NAMESPACE_STD_USING(freopen)
#endif /* (__CRT_HAVE_freopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_freopen64 || (__CRT_HAVE_freopen_unlocked && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_freopen64_unlocked */
#if defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
__NAMESPACE_STD_USING(fgetpos)
#endif /* __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_ftello64 || __CRT_HAVE_ftell64 || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE_ftell64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock */
#if defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
__NAMESPACE_STD_USING(fsetpos)
#endif /* __CRT_HAVE_fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || __CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock */
#if defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_STD_USING(vfprintf)
#endif /* __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock */
#if defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_STD_USING(fprintf)
#endif /* __CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock */
#if defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
__NAMESPACE_STD_USING(vprintf)
#endif /* __CRT_HAVE_vprintf || __CRT_HAVE_vprintf_s || __CRT_HAVE_vprintf_unlocked || (__LOCAL_stdout && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#if defined(__CRT_HAVE_printf) || defined(__CRT_HAVE__IO_printf) || defined(__CRT_HAVE_printf_s) || defined(__CRT_HAVE_printf_unlocked) || defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
__NAMESPACE_STD_USING(printf)
#endif /* __CRT_HAVE_printf || __CRT_HAVE__IO_printf || __CRT_HAVE_printf_s || __CRT_HAVE_printf_unlocked || __CRT_HAVE_vprintf || __CRT_HAVE_vprintf_s || __CRT_HAVE_vprintf_unlocked || (__LOCAL_stdout && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#if !defined(__vfscanf_defined) && defined(__std_vfscanf_defined)
#define __vfscanf_defined
__NAMESPACE_STD_USING(vfscanf)
#endif /* !__vfscanf_defined && __std_vfscanf_defined */
#if !defined(__vscanf_defined) && defined(__std_vscanf_defined)
#define __vscanf_defined
__NAMESPACE_STD_USING(vscanf)
#endif /* !__vscanf_defined && __std_vscanf_defined */
#if defined(__CRT_HAVE_fscanf) || defined(__CRT_HAVE__IO_fscanf) || defined(__CRT_HAVE_fscanf_unlocked) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
__NAMESPACE_STD_USING(fscanf)
#endif /* __CRT_HAVE_fscanf || __CRT_HAVE__IO_fscanf || __CRT_HAVE_fscanf_unlocked || __CRT_HAVE_vfscanf || __CRT_HAVE__vfscanf || __CRT_HAVE__vfscanf_s || __CRT_HAVE__IO_vfscanf || __CRT_HAVE_vfscanf_unlocked || __CRT_HAVE___vfscanf || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)) */
#if defined(__CRT_HAVE_scanf) || defined(__CRT_HAVE__IO_scanf) || defined(__CRT_HAVE_scanf_unlocked) || defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf) || defined(__CRT_HAVE_vscanf_unlocked) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
__NAMESPACE_STD_USING(scanf)
#endif /* __CRT_HAVE_scanf || __CRT_HAVE__IO_scanf || __CRT_HAVE_scanf_unlocked || __CRT_HAVE_vscanf || __CRT_HAVE__vscanf || __CRT_HAVE_vscanf_unlocked || (__LOCAL_stdin && (__CRT_HAVE_vfscanf || __CRT_HAVE__vfscanf || __CRT_HAVE__vfscanf_s || __CRT_HAVE__IO_vfscanf || __CRT_HAVE_vfscanf_unlocked || __CRT_HAVE___vfscanf || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)))) */
#if !defined(__gets_defined) && defined(__std_gets_defined)
#define __gets_defined
__NAMESPACE_STD_USING(gets)
#endif /* !__gets_defined && __std_gets_defined */
#if !defined(__vsscanf_defined) && defined(__std_vsscanf_defined)
#define __vsscanf_defined
__NAMESPACE_STD_USING(vsscanf)
#endif /* !__vsscanf_defined && __std_vsscanf_defined */
__NAMESPACE_STD_USING(sscanf)
__NAMESPACE_STD_USING(vsprintf)
__NAMESPACE_STD_USING(sprintf)
#if !defined(__vsnprintf_defined) && defined(__std_vsnprintf_defined)
#define __vsnprintf_defined
__NAMESPACE_STD_USING(vsnprintf)
#endif /* !__vsnprintf_defined && __std_vsnprintf_defined */
#if !defined(__snprintf_defined) && defined(__std_snprintf_defined)
#define __snprintf_defined
__NAMESPACE_STD_USING(snprintf)
#endif /* !__snprintf_defined && __std_snprintf_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_vdprintf
/* >> dprintf(3), vdprintf(3) */
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,vdprintf,(__fd_t __fd, char const *__restrict __format, __builtin_va_list __args),(__fd,__format,__args))
#else /* __CRT_HAVE_vdprintf */
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if defined(__CRT_HAVE_write_printer) || defined(__CRT_HAVE_writeall) || defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
#include <libc/local/stdio/vdprintf.h>
/* >> dprintf(3), vdprintf(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vdprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((2)) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__LIBCCALL vdprintf)(__fd_t __fd, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vdprintf))(__fd, __format, __args); })
#endif /* __CRT_HAVE_write_printer || __CRT_HAVE_writeall || __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */
#endif /* !__CRT_HAVE_vdprintf */
#ifdef __CRT_HAVE_dprintf
/* >> dprintf(3), vdprintf(3) */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((2)) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__VLIBCCALL dprintf)(__fd_t __fd, char const *__restrict __format, ...) __CASMNAME_SAME("dprintf");
#else /* __CRT_HAVE_dprintf */
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if defined(__CRT_HAVE_vdprintf) || defined(__CRT_HAVE_write_printer) || defined(__CRT_HAVE_writeall) || defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
#include <libc/local/stdio/dprintf.h>
/* >> dprintf(3), vdprintf(3) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(dprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((2)) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__VLIBCCALL dprintf)(__fd_t __fd, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dprintf))(__fd, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define dprintf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dprintf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* __CRT_HAVE_vdprintf || __CRT_HAVE_write_printer || __CRT_HAVE_writeall || __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */
#endif /* !__CRT_HAVE_dprintf */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_ATFILE
#ifdef __CRT_HAVE_renameat
/* >> renameat(2) */
__CDECLARE(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,renameat,(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path),(__oldfd,__oldname,__newfd,__newname_or_path))
#elif defined(__CRT_HAVE_renameat2)
#include <libc/local/stdio/renameat.h>
/* >> renameat(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(renameat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 4)) int __NOTHROW_RPC(__LIBCCALL renameat)(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(renameat))(__oldfd, __oldname, __newfd, __newname_or_path); })
#endif /* ... */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_removeat
/* >> removeat(3)
 * Remove a file or directory `filename' relative to a given base directory `dirfd' */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,removeat,(__fd_t __dirfd, char const *__filename),(__dirfd,__filename))
#else /* __CRT_HAVE_removeat */
#include <asm/os/fcntl.h>
#include <asm/os/errno.h>
#if defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat) && (defined(__AT_REMOVEREG) || (defined(__EISDIR) && defined(__ENOTDIR)))
#include <libc/local/stdio/removeat.h>
/* >> removeat(3)
 * Remove a file or directory `filename' relative to a given base directory `dirfd' */
__NAMESPACE_LOCAL_USING_OR_IMPL(removeat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int __NOTHROW_RPC(__LIBCCALL removeat)(__fd_t __dirfd, char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(removeat))(__dirfd, __filename); })
#endif /* __AT_REMOVEDIR && __CRT_HAVE_unlinkat && (__AT_REMOVEREG || (__EISDIR && __ENOTDIR)) */
#endif /* !__CRT_HAVE_removeat */
#endif /* __USE_KOS */
#endif /* __USE_ATFILE */
#ifdef __USE_GNU
/* >> renameat2(2)
 * @param flags: Set of `0 | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE |
 *                       AT_RENAME_WHITEOUT | AT_RENAME_MOVETODIR | AT_DOSPATH'
 * NOTE: For portability, use the following names:
 *   - `AT_RENAME_NOREPLACE' --> `RENAME_NOREPLACE'
 *   - `AT_RENAME_EXCHANGE'  --> `RENAME_EXCHANGE'
 *   - `AT_RENAME_WHITEOUT'  --> `RENAME_WHITEOUT' */
__CDECLARE_OPT(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,renameat2,(__fd_t __oldfd, char const *__oldname, __fd_t __newfd, char const *__newname_or_path, __atflag_t __flags),(__oldfd,__oldname,__newfd,__newname_or_path,__flags))
#endif /* __USE_GNU */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_tmpnam_r
/* >> tmpnam(3), tmpnam_r(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,tmpnam_r,(char *__buf),(__buf))
#elif defined(__CRT_HAVE_tmpnam)
#include <libc/local/stdio/tmpnam_r.h>
/* >> tmpnam(3), tmpnam_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(tmpnam_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL tmpnam_r)(char *__buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tmpnam_r))(__buf); })
#endif /* ... */
#ifdef __CRT_HAVE_setbuffer
/* >> setbuffer(3)
 * Specify the location and size for the buffer to-be used by `stream' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,setbuffer,(__FILE *__restrict __stream, char *__buf, __SIZE_TYPE__ __bufsize),(__stream,__buf,__bufsize))
#elif defined(__CRT_HAVE__IO_setbuffer)
/* >> setbuffer(3)
 * Specify the location and size for the buffer to-be used by `stream' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,setbuffer,(__FILE *__restrict __stream, char *__buf, __SIZE_TYPE__ __bufsize),_IO_setbuffer,(__stream,__buf,__bufsize))
#elif defined(___IOFBF) && defined(___IONBF) && (defined(__CRT_HAVE_setvbuf) || defined(__CRT_HAVE__IO_setvbuf) || defined(__CRT_HAVE_setvbuf_unlocked))
#include <libc/local/stdio/setbuffer.h>
/* >> setbuffer(3)
 * Specify the location and size for the buffer to-be used by `stream' */
__NAMESPACE_LOCAL_USING_OR_IMPL(setbuffer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL setbuffer)(__FILE *__restrict __stream, char *__buf, __SIZE_TYPE__ __bufsize) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setbuffer))(__stream, __buf, __bufsize); })
#endif /* ... */
#ifdef __CRT_HAVE_setlinebuf
/* >> setlinebuf(3)
 * Change the given `stream' to become line-buffered */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,setlinebuf,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_setvbuf) || defined(__CRT_HAVE__IO_setvbuf) || defined(__CRT_HAVE_setvbuf_unlocked)
#include <libc/local/stdio/setlinebuf.h>
/* >> setlinebuf(3)
 * Change the given `stream' to become line-buffered */
__NAMESPACE_LOCAL_USING_OR_IMPL(setlinebuf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL setlinebuf)(__FILE *__restrict __stream) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setlinebuf))(__stream); })
#endif /* ... */
#ifdef __CRT_HAVE_fflush_unlocked
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
__CDECLARE(,int,__THROWING,fflush_unlocked,(__FILE *__stream),(__stream))
#elif defined(__CRT_HAVE__fflush_nolock)
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(,int,__THROWING,fflush_unlocked,(__FILE *__stream),_fflush_nolock,(__stream))
#elif defined(__CRT_HAVE_fflush)
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(,int,__THROWING,fflush_unlocked,(__FILE *__stream),fflush,(__stream))
#elif defined(__CRT_HAVE__IO_fflush)
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(,int,__THROWING,fflush_unlocked,(__FILE *__stream),_IO_fflush,(__stream))
#else /* ... */
#include <libc/local/stdio/fflush_unlocked.h>
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fflush_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL fflush_unlocked)(__FILE *__stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fflush_unlocked))(__stream); })
#endif /* !... */
#ifdef __CRT_HAVE_fread_unlocked
/* >> fread_unlocked(3)
 * Same as `fread()', but performs I/O without acquiring a lock to `stream' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fread_unlocked,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fread_nolock)
/* >> fread_unlocked(3)
 * Same as `fread()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fread_unlocked,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fread_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fread)
/* >> fread_unlocked(3)
 * Same as `fread()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fread_unlocked,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fread)
/* >> fread_unlocked(3)
 * Same as `fread()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fread_unlocked,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow)))
#include <libc/local/stdio/fread_unlocked.h>
/* >> fread_unlocked(3)
 * Same as `fread()', but performs I/O without acquiring a lock to `stream' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fread_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 4)) __SIZE_TYPE__ (__LIBCCALL fread_unlocked)(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fread_unlocked))(__buf, __elemsize, __elemcount, __stream); })
#endif /* ... */
#ifdef __CRT_HAVE_fwrite_unlocked
/* >> fwrite_unlocked(3)
 * Same as `fwrite()', but performs I/O without acquiring a lock to `stream' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fwrite_nolock)
/* >> fwrite_unlocked(3)
 * Same as `fwrite()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fwrite_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fwrite)
/* >> fwrite_unlocked(3)
 * Same as `fwrite()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fwrite)
/* >> fwrite_unlocked(3)
 * Same as `fwrite()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fwrite,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fwrite_s)
/* >> fwrite_unlocked(3)
 * Same as `fwrite()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite_s,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/stdio/fwrite_unlocked.h>
/* >> fwrite_unlocked(3)
 * Same as `fwrite()', but performs I/O without acquiring a lock to `stream' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fwrite_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 4)) __SIZE_TYPE__ (__LIBCCALL fwrite_unlocked)(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwrite_unlocked))(__buf, __elemsize, __elemcount, __stream); })
#endif /* ... */
#if defined(__CRT_HAVE_feof_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> feof_unlocked(3)
 * Same as `feof()', but skip acquiring internal locks */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,feof_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_feof)
/* >> feof_unlocked(3)
 * Same as `feof()', but skip acquiring internal locks */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,feof_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),feof,(__stream))
#elif defined(__CRT_HAVE__IO_feof)
/* >> feof_unlocked(3)
 * Same as `feof()', but skip acquiring internal locks */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,feof_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),_IO_feof,(__stream))
#elif defined(__CRT_HAVE_feof_unlocked)
/* >> feof_unlocked(3)
 * Same as `feof()', but skip acquiring internal locks */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,feof_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_ferror_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> ferror_unlocked(3)
 * Same as `ferror()', but skip acquiring internal locks */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ferror_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_ferror)
/* >> ferror_unlocked(3)
 * Same as `ferror()', but skip acquiring internal locks */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ferror_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),ferror,(__stream))
#elif defined(__CRT_HAVE__IO_ferror)
/* >> ferror_unlocked(3)
 * Same as `ferror()', but skip acquiring internal locks */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ferror_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),_IO_ferror,(__stream))
#elif defined(__CRT_HAVE_ferror_unlocked)
/* >> ferror_unlocked(3)
 * Same as `ferror()', but skip acquiring internal locks */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ferror_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_clearerr_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> clearerr_unlocked(3)
 * Same as `clearerr()', but skip acquiring internal locks */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,clearerr_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_clearerr)
/* >> clearerr_unlocked(3)
 * Same as `clearerr()', but skip acquiring internal locks */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,clearerr_unlocked,(__FILE *__restrict __stream),clearerr,(__stream))
#elif defined(__CRT_HAVE_clearerr_unlocked)
/* >> clearerr_unlocked(3)
 * Same as `clearerr()', but skip acquiring internal locks */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,clearerr_unlocked,(__FILE *__restrict __stream),(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fileno_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fileno_unlocked(3)
 * Same as `fileno()', but skip acquiring internal locks */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,fileno_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_fileno)
/* >> fileno_unlocked(3)
 * Same as `fileno()', but skip acquiring internal locks */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,fileno_unlocked,(__FILE *__restrict __stream),fileno,(__stream))
#elif defined(__CRT_HAVE__fileno)
/* >> fileno_unlocked(3)
 * Same as `fileno()', but skip acquiring internal locks */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,fileno_unlocked,(__FILE *__restrict __stream),_fileno,(__stream))
#elif defined(__CRT_HAVE_fileno_unlocked)
/* >> fileno_unlocked(3)
 * Same as `fileno()', but skip acquiring internal locks */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,fileno_unlocked,(__FILE *__restrict __stream),(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fgetc_unlocked
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fgetc_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc_unlocked,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getc_nolock)
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc_unlocked,(__FILE *__restrict __stream),_getc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock)
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc_unlocked,(__FILE *__restrict __stream),_fgetc_nolock,(__stream))
#elif defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc_unlocked,(__FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc_unlocked,(__FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fgetc_unlocked,(__FILE *__restrict __stream),_IO_getc,(__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/stdio/fgetc_unlocked.h>
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetc_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fgetc_unlocked)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc_unlocked))(__stream); })
#endif /* ... */
#if __has_builtin(__builtin_fputc_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc_unlocked)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CEIDECLARE(__ATTR_NONNULL((2)),int,__THROWING,fputc_unlocked,(int __ch, __FILE *__restrict __stream),{ return __builtin_fputc_unlocked(__ch, __stream); })
#elif defined(__CRT_HAVE_putc_unlocked)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc_unlocked,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,fputc_unlocked,(int __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE__putc_nolock)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc_unlocked,(int __ch, __FILE *__restrict __stream),_putc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE__fputc_nolock)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc_unlocked,(int __ch, __FILE *__restrict __stream),_fputc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc_unlocked,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc_unlocked,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,fputc_unlocked,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/fputc_unlocked.h>
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fputc_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL fputc_unlocked)(int __ch, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc_unlocked))(__ch, __stream); })
#endif /* ... */
#endif /* __USE_MISC */

#if defined(__USE_MISC) || defined(__USE_XOPEN) || defined(__USE_DOS)
#ifdef __CRT_HAVE_tempnam
/* >> tempnam(3) */
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,tempnam,(char const *__dir, char const *__pfx),(__dir,__pfx))
#elif defined(__CRT_HAVE__tempnam)
/* >> tempnam(3) */
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,tempnam,(char const *__dir, char const *__pfx),_tempnam,(__dir,__pfx))
#endif /* ... */
#endif /* __USE_MISC || __USE_XOPEN || __USE_DOS */

#if defined(__USE_POSIX) || defined(__USE_DOS)
#ifdef __CRT_HAVE_fdopen
/* >> fdopen(3)
 * Open a new file stream by inheriting a given file descriptor `fd'
 * Note   that  upon  success  (`return != NULL'),  the  given  `fd'
 * will be `close()'d once `fclose(return)' is called */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,fdopen,(__fd_t __fd, char const *__restrict __modes),(__fd,__modes))
#elif defined(__CRT_HAVE__fdopen)
/* >> fdopen(3)
 * Open a new file stream by inheriting a given file descriptor `fd'
 * Note   that  upon  success  (`return != NULL'),  the  given  `fd'
 * will be `close()'d once `fclose(return)' is called */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,fdopen,(__fd_t __fd, char const *__restrict __modes),_fdopen,(__fd,__modes))
#elif defined(__CRT_HAVE__IO_fdopen)
/* >> fdopen(3)
 * Open a new file stream by inheriting a given file descriptor `fd'
 * Note   that  upon  success  (`return != NULL'),  the  given  `fd'
 * will be `close()'d once `fclose(return)' is called */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,fdopen,(__fd_t __fd, char const *__restrict __modes),_IO_fdopen,(__fd,__modes))
#endif /* ... */
#if defined(__CRT_HAVE_fileno_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fileno(3)
 * Return the underlying file descriptor number used by `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#elif defined(__CRT_HAVE_fileno)
/* >> fileno(3)
 * Return the underlying file descriptor number used by `stream' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,fileno,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__fileno)
/* >> fileno(3)
 * Return the underlying file descriptor number used by `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,fileno,(__FILE *__restrict __stream),_fileno,(__stream))
#elif defined(__CRT_HAVE_fileno_unlocked)
/* >> fileno(3)
 * Return the underlying file descriptor number used by `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#endif /* ... */
#endif /* __USE_POSIX || __USE_DOS */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_fmemopen
/* >> fmemopen(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__FILE *,__NOTHROW_NCX,fmemopen,(void *__mem, __SIZE_TYPE__ __len, char const *__modes),(__mem,__len,__modes))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2))
#include <libc/local/stdio/fmemopen.h>
/* >> fmemopen(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmemopen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __FILE *__NOTHROW_NCX(__LIBCCALL fmemopen)(void *__mem, __SIZE_TYPE__ __len, char const *__modes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmemopen))(__mem, __len, __modes); })
#endif /* ... */
#ifdef __CRT_HAVE_open_memstream
/* >> open_memstream(3) */
__CDECLARE(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,open_memstream,(char **__bufloc, __SIZE_TYPE__ *__sizeloc),(__bufloc,__sizeloc))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2)) && (defined(__CRT_HAVE_recalloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/stdio/open_memstream.h>
/* >> open_memstream(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(open_memstream, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __FILE *__NOTHROW_NCX(__LIBCCALL open_memstream)(char **__bufloc, __SIZE_TYPE__ *__sizeloc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open_memstream))(__bufloc, __sizeloc); })
#endif /* ... */
#if defined(__CRT_HAVE_getdelim_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> getdelim(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,__getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim_unlocked,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE_getdelim)
/* >> getdelim(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,__getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE_getdelim_unlocked)
/* >> getdelim(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,__getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim_unlocked,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE___getdelim)
/* >> getdelim(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,__getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE__IO_getdelim)
/* >> getdelim(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,__getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),_IO_getdelim,(__lineptr,__pcount,__delimiter,__stream))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
#include <libc/local/stdio/getdelim.h>
/* >> getdelim(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)) __SSIZE_TYPE__ (__LIBCCALL __getdelim)(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getdelim))(__lineptr, __pcount, __delimiter, __stream); }
#endif /* ... */
#if defined(__CRT_HAVE_getdelim_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> getdelim(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim_unlocked,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE_getdelim)
/* >> getdelim(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE_getdelim_unlocked)
/* >> getdelim(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim_unlocked,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE___getdelim)
/* >> getdelim(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),__getdelim,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE__IO_getdelim)
/* >> getdelim(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),_IO_getdelim,(__lineptr,__pcount,__delimiter,__stream))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
#include <libc/local/stdio/getdelim.h>
/* >> getdelim(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getdelim, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)) __SSIZE_TYPE__ (__LIBCCALL getdelim)(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getdelim))(__lineptr, __pcount, __delimiter, __stream); })
#endif /* ... */
#if defined(__CRT_HAVE_getline_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> getline(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,getline,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),getline_unlocked,(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE_getline)
/* >> getline(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,getline,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE_getline_unlocked)
/* >> getline(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,getline,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),getline_unlocked,(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE___getline)
/* >> getline(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,getline,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),__getline,(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE__IO_getline)
/* >> getline(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,getline,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),_IO_getline,(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE_getdelim) || defined(__CRT_HAVE_getdelim_unlocked) || defined(__CRT_HAVE___getdelim) || defined(__CRT_HAVE__IO_getdelim) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <libc/local/stdio/getline.h>
/* >> getline(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getline, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) __SSIZE_TYPE__ (__LIBCCALL getline)(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getline))(__lineptr, __pcount, __stream); })
#endif /* ... */
#endif /* __USE_XOPEN2K8 */

#if defined(__USE_POSIX) || defined(__USE_REENTRANT)
#ifdef __CRT_HAVE_fgetc_unlocked
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc_unlocked,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,getc_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__getc_nolock)
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc_unlocked,(__FILE *__restrict __stream),_getc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock)
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc_unlocked,(__FILE *__restrict __stream),_fgetc_nolock,(__stream))
#elif defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc_unlocked,(__FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc_unlocked,(__FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getc_unlocked,(__FILE *__restrict __stream),_IO_getc,(__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/stdio/fgetc_unlocked.h>
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL getc_unlocked)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc_unlocked))(__stream); }
#endif /* ... */
#if __has_builtin(__builtin_fputc_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc_unlocked)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CEIREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc_unlocked,(int __ch, __FILE *__restrict __stream),fputc_unlocked,{ return __builtin_fputc_unlocked(__ch, __stream); })
#elif defined(__CRT_HAVE_putc_unlocked)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,putc_unlocked,(int __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc_unlocked,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__putc_nolock)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc_unlocked,(int __ch, __FILE *__restrict __stream),_putc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE__fputc_nolock)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc_unlocked,(int __ch, __FILE *__restrict __stream),_fputc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc_unlocked,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc_unlocked,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putc_unlocked,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/fputc_unlocked.h>
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL putc_unlocked)(int __ch, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc_unlocked))(__ch, __stream); }
#endif /* ... */
#ifdef __CRT_HAVE_getchar_unlocked
/* >> getchar_unlocked(3)
 * Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
__CDECLARE(,int,__THROWING,getchar_unlocked,(void),())
#elif defined(__LOCAL_stdin) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))
#include <libc/local/stdio/getchar_unlocked.h>
/* >> getchar_unlocked(3)
 * Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
__NAMESPACE_LOCAL_USING_OR_IMPL(getchar_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL getchar_unlocked)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar_unlocked))(); })
#endif /* ... */
#if __has_builtin(__builtin_putchar_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_putchar_unlocked)
/* >> putchar_unlocked(3)
 * Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
__CEIDECLARE(,int,__THROWING,putchar_unlocked,(int __ch),{ return __builtin_putchar_unlocked(__ch); })
#elif defined(__CRT_HAVE_putchar_unlocked)
/* >> putchar_unlocked(3)
 * Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
__CDECLARE(,int,__THROWING,putchar_unlocked,(int __ch),(__ch))
#elif defined(__LOCAL_stdout) && (defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/stdio/putchar_unlocked.h>
/* >> putchar_unlocked(3)
 * Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
__NAMESPACE_LOCAL_USING_OR_IMPL(putchar_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL putchar_unlocked)(int __ch) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar_unlocked))(__ch); })
#endif /* ... */
#ifdef __CRT_HAVE_flockfile
/* >> flockfile(3)
 * Acquire a lock to `stream' and block until doing so succeeds */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,flockfile,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__lock_file)
/* >> flockfile(3)
 * Acquire a lock to `stream' and block until doing so succeeds */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,flockfile,(__FILE *__restrict __stream),_lock_file,(__stream))
#elif defined(__CRT_HAVE__IO_flockfile)
/* >> flockfile(3)
 * Acquire a lock to `stream' and block until doing so succeeds */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,flockfile,(__FILE *__restrict __stream),_IO_flockfile,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_funlockfile
/* >> funlockfile(3)
 * Release a previously acquired lock from `stream' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,funlockfile,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__unlock_file)
/* >> funlockfile(3)
 * Release a previously acquired lock from `stream' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,funlockfile,(__FILE *__restrict __stream),_unlock_file,(__stream))
#elif defined(__CRT_HAVE__IO_funlockfile)
/* >> funlockfile(3)
 * Release a previously acquired lock from `stream' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,funlockfile,(__FILE *__restrict __stream),_IO_funlockfile,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_ftrylockfile
/* >> ftrylockfile(3)
 * Try to acquire a lock to `stream' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ftrylockfile,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__IO_ftrylockfile)
/* >> ftrylockfile(3)
 * Try to acquire a lock to `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,ftrylockfile,(__FILE *__restrict __stream),_IO_ftrylockfile,(__stream))
#endif /* ... */
#endif /* __USE_POSIX || __USE_REENTRANT */
#ifdef __CRT_HAVE__filbuf
/* >> __uflow(3)
 * This is essentially gLibc's version of `_filbuf(3)' (but sadly not binary compatible) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__uflow,(FILE *__stream),_filbuf,(__stream))
#elif defined(__CRT_HAVE___uflow)
/* >> __uflow(3)
 * This is essentially gLibc's version of `_filbuf(3)' (but sadly not binary compatible) */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__uflow,(FILE *__stream),(__stream))
#elif defined(__CRT_HAVE___underflow)
/* >> __uflow(3)
 * This is essentially gLibc's version of `_filbuf(3)' (but sadly not binary compatible) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__uflow,(FILE *__stream),__underflow,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE___overflow
/* >> __overflow(3)
 * This is essentially gLibc's version of `_flsbuf(3)' (but sadly not binary compatible) */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,__overflow,(__FILE *__stream, int __ch),(__stream,__ch))
#elif defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf)
#include <libc/local/stdio/__overflow.h>
/* >> __overflow(3)
 * This is essentially gLibc's version of `_flsbuf(3)' (but sadly not binary compatible) */
__NAMESPACE_LOCAL_USING_OR_IMPL(__overflow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL __overflow)(__FILE *__stream, int __ch) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__overflow))(__stream, __ch); })
#endif /* ... */

#ifdef __USE_POSIX
#ifndef __ctermid_defined
#define __ctermid_defined
#ifdef __CRT_HAVE_ctermid
/* >> ctermid(3)
 * Writes the string "/dev/tty" to `s', or returns a pointer to
 * a writable  data location  that contains  that same  string. */
__CDECLARE(__ATTR_RETNONNULL,char *,__NOTHROW_NCX,ctermid,(char *__s),(__s))
#else /* __CRT_HAVE_ctermid */
#include <libc/local/unistd/ctermid.h>
/* >> ctermid(3)
 * Writes the string "/dev/tty" to `s', or returns a pointer to
 * a writable  data location  that contains  that same  string. */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctermid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL char *__NOTHROW_NCX(__LIBCCALL ctermid)(char *__s) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctermid))(__s); })
#endif /* !__CRT_HAVE_ctermid */
#endif /* !__ctermid_defined */
#endif /* __USE_POSIX */

#ifdef __USE_REENTRANT
#ifndef __ctermid_r_defined
#define __ctermid_r_defined
#ifdef __CRT_HAVE_ctermid_r
/* >> ctermid_r(3)
 * Same as `ctermid', but return `NULL' when `s' is `NULL' */
__CDECLARE(,char *,__NOTHROW_NCX,ctermid_r,(char *__s),(__s))
#else /* __CRT_HAVE_ctermid_r */
#include <libc/local/unistd/ctermid_r.h>
/* >> ctermid_r(3)
 * Same as `ctermid', but return `NULL' when `s' is `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctermid_r, __FORCELOCAL __ATTR_ARTIFICIAL char *__NOTHROW_NCX(__LIBCCALL ctermid_r)(char *__s) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctermid_r))(__s); })
#endif /* !__CRT_HAVE_ctermid_r */
#endif /* !__ctermid_r_defined */
#endif /* __USE_REENTRANT */

#ifdef __USE_XOPEN
#ifndef __cuserid_defined
#define __cuserid_defined
#ifdef __CRT_HAVE_cuserid
/* >> cuserid(3)
 * Return the name of the current user (`$LOGNAME' or `getpwuid(geteuid())'), storing
 * that  name  in  `s'.  When  `s'  is   NULL,  a  static  buffer  is  used   instead
 * When  given,   `s'   must  be   a   buffer   of  at   least   `L_cuserid'   bytes.
 * If the actual  username is longer  than this,  it may be  truncated, and  programs
 * that wish to support longer usernames  should make use of `getlogin_r()'  instead.
 * s.a. `getlogin()' and `getlogin_r()' */
__CDECLARE(,char *,__NOTHROW_NCX,cuserid,(char *__s),(__s))
#else /* __CRT_HAVE_cuserid */
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_getlogin_r) || defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ) || (defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid)))
#include <libc/local/unistd/cuserid.h>
/* >> cuserid(3)
 * Return the name of the current user (`$LOGNAME' or `getpwuid(geteuid())'), storing
 * that  name  in  `s'.  When  `s'  is   NULL,  a  static  buffer  is  used   instead
 * When  given,   `s'   must  be   a   buffer   of  at   least   `L_cuserid'   bytes.
 * If the actual  username is longer  than this,  it may be  truncated, and  programs
 * that wish to support longer usernames  should make use of `getlogin_r()'  instead.
 * s.a. `getlogin()' and `getlogin_r()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(cuserid, __FORCELOCAL __ATTR_ARTIFICIAL char *__NOTHROW_NCX(__LIBCCALL cuserid)(char *__s) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cuserid))(__s); })
#else /* __CRT_HAVE_getlogin_r || __CRT_HAVE_getenv || __LOCAL_environ || (__CRT_HAVE_getpwuid_r && (__CRT_HAVE_geteuid || __CRT_HAVE___geteuid || __CRT_HAVE___libc_geteuid)) */
#undef __cuserid_defined
#endif /* !__CRT_HAVE_getlogin_r && !__CRT_HAVE_getenv && !__LOCAL_environ && (!__CRT_HAVE_getpwuid_r || (!__CRT_HAVE_geteuid && !__CRT_HAVE___geteuid && !__CRT_HAVE___libc_geteuid)) */
#endif /* !__CRT_HAVE_cuserid */
#endif /* !__cuserid_defined */
#endif /* Use X/Open, but not issue 6.  */

#ifdef __USE_POSIX2
#ifdef __CRT_HAVE_popen
/* >> popen(3)
 * Open and return a new process I/O stream for executing `command'
 * @param: command: The command to execute (s.a. `shexec(3)')
 * @param: modes:   One of "r", "w", "re" or "we" ('e' sets  O_CLOEXEC
 *                  for the internal file descriptor within the parent
 *                  process) */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,popen,(char const *__command, char const *__modes),(__command,__modes))
#elif defined(__CRT_HAVE__popen)
/* >> popen(3)
 * Open and return a new process I/O stream for executing `command'
 * @param: command: The command to execute (s.a. `shexec(3)')
 * @param: modes:   One of "r", "w", "re" or "we" ('e' sets  O_CLOEXEC
 *                  for the internal file descriptor within the parent
 *                  process) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,popen,(char const *__command, char const *__modes),_popen,(__command,__modes))
#elif defined(__CRT_HAVE__IO_popen)
/* >> popen(3)
 * Open and return a new process I/O stream for executing `command'
 * @param: command: The command to execute (s.a. `shexec(3)')
 * @param: modes:   One of "r", "w", "re" or "we" ('e' sets  O_CLOEXEC
 *                  for the internal file descriptor within the parent
 *                  process) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,popen,(char const *__command, char const *__modes),_IO_popen,(__command,__modes))
#endif /* ... */
#ifdef __CRT_HAVE_pclose
/* >> pclose(3)
 * Close a process I/O file `stream' (s.a. `popen(3)') */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pclose,(__FILE *__stream),(__stream))
#elif defined(__CRT_HAVE__pclose)
/* >> pclose(3)
 * Close a process I/O file `stream' (s.a. `popen(3)') */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pclose,(__FILE *__stream),_pclose,(__stream))
#endif /* ... */
#endif /* __USE_POSIX2 */

#ifdef __USE_NETBSD
#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */
/* >> popenve(3)
 * Similar to `popen(3)', but rather than running `shexec(command)', this
 * function will `execve(path, argv, envp)'. The returned FILE must still
 * be closed using `pclose(3)', rather than `fclose(3)' */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3, 4)),__FILE *,__NOTHROW_RPC,popenve,(char const *__path, __TARGV, __TENVP, char const *__modes),(__path,___argv,___envp,__modes))
#endif /* __USE_NETBSD */

#if (defined(__USE_MISC) || defined(__USE_DOS) || \
     (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))
#if defined(__CRT_HAVE_getw_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> getw(3)
 * Similar to `getc()', but read 2 bytes */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getw,(__FILE *__restrict __stream),getw_unlocked,(__stream))
#elif defined(__CRT_HAVE_getw)
/* >> getw(3)
 * Similar to `getc()', but read 2 bytes */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,getw,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__getw)
/* >> getw(3)
 * Similar to `getc()', but read 2 bytes */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getw,(__FILE *__restrict __stream),_getw,(__stream))
#elif defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/stdio/getw.h>
/* >> getw(3)
 * Similar to `getc()', but read 2 bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(getw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL getw)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getw))(__stream); })
#endif /* ... */
#if defined(__CRT_HAVE_putw_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> putw(3)
 * Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putw,(int __w, __FILE *__restrict __stream),putw_unlocked,(__w,__stream))
#elif defined(__CRT_HAVE_putw)
/* >> putw(3)
 * Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,putw,(int __w, __FILE *__restrict __stream),(__w,__stream))
#elif defined(__CRT_HAVE__putw)
/* >> putw(3)
 * Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putw,(int __w, __FILE *__restrict __stream),_putw,(__w,__stream))
#elif defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/putw.h>
/* >> putw(3)
 * Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__NAMESPACE_LOCAL_USING_OR_IMPL(putw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL putw)(int __w, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putw))(__w, __stream); })
#endif /* ... */
#endif /* __USE_MISC || __USE_DOS || (__USE_XOPEN && !__USE_XOPEN2K) */

#if defined(__USE_GNU) || defined(__USE_DOS)
#ifdef __CRT_HAVE_fcloseall
/* >> fcloseall(3)
 * Close all opened files */
__CDECLARE(,int,__THROWING,fcloseall,(void),())
#elif defined(__CRT_HAVE__fcloseall)
/* >> fcloseall(3)
 * Close all opened files */
__CREDIRECT(,int,__THROWING,fcloseall,(void),_fcloseall,())
#endif /* ... */
#endif /* __USE_GNU || __USE_DOS */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_fopencookie
/* >> fopencookie(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,fopencookie,(void *__restrict __magic_cookie, char const *__restrict __modes, _IO_cookie_io_functions_t __io_funcs),(__magic_cookie,__modes,__io_funcs))
#else /* __CRT_HAVE_fopencookie */
#include <hybrid/typecore.h>
#if (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_funopen64) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2) || defined(__CRT_HAVE_funopen))
#include <libc/local/stdio/fopencookie.h>
/* >> fopencookie(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fopencookie, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __FILE *__NOTHROW_NCX(__LIBCCALL fopencookie)(void *__restrict __magic_cookie, char const *__restrict __modes, _IO_cookie_io_functions_t __io_funcs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fopencookie))(__magic_cookie, __modes, __io_funcs); })
#endif /* (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_funopen64 || __CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2 || __CRT_HAVE_funopen) */
#endif /* !__CRT_HAVE_fopencookie */
#ifdef __CRT_HAVE_fgets_unlocked
/* >> fgets_unlocked(3)
 * Same as `fgets()', but performs I/O without acquiring a lock to `stream' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char *,__THROWING,fgets_unlocked,(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgets)
/* >> fgets_unlocked(3)
 * Same as `fgets()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char *,__THROWING,fgets_unlocked,(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgets,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
#include <libc/local/stdio/fgets_unlocked.h>
/* >> fgets_unlocked(3)
 * Same as `fgets()', but performs I/O without acquiring a lock to `stream' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgets_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) char *(__LIBCCALL fgets_unlocked)(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgets_unlocked))(__buf, __bufsize, __stream); })
#endif /* ... */
#if __has_builtin(__builtin_fputs_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputs_unlocked)
/* >> fputs_unlocked(3)
 * Same as `fputs()', but performs I/O without acquiring a lock to `stream' */
__CEIDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputs_unlocked,(char const *__restrict __string, __FILE *__restrict __stream),{ return __builtin_fputs_unlocked(__string, __stream); })
#elif defined(__CRT_HAVE_fputs_unlocked)
/* >> fputs_unlocked(3)
 * Same as `fputs()', but performs I/O without acquiring a lock to `stream' */
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputs_unlocked,(char const *__restrict __string, __FILE *__restrict __stream),(__string,__stream))
#elif defined(__CRT_HAVE_fputs)
/* >> fputs_unlocked(3)
 * Same as `fputs()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputs_unlocked,(char const *__restrict __string, __FILE *__restrict __stream),fputs,(__string,__stream))
#elif defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/stdio/fputs_unlocked.h>
/* >> fputs_unlocked(3)
 * Same as `fputs()', but performs I/O without acquiring a lock to `stream' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fputs_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL fputs_unlocked)(char const *__restrict __string, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputs_unlocked))(__string, __stream); })
#endif /* ... */

struct obstack;
#ifdef __CRT_HAVE_obstack_vprintf
/* >> obstack_printf(3), obstack_vprintf(3)
 * Append formated strings to a given obstack. s.a. `obstack_printer(3)' */
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,obstack_vprintf,(struct obstack *__restrict __self, char const *__restrict __format, __builtin_va_list __args),(__self,__format,__args))
#else /* __CRT_HAVE_obstack_vprintf */
#include <bits/crt/obstack.h>
#if defined(__CRT_HAVE_obstack_printer) || defined(__CRT_HAVE__obstack_newchunk) || defined(__LOCAL_obstack_alloc_failed_handler) || defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE_xexit)
#include <libc/local/stdio/obstack_vprintf.h>
/* >> obstack_printf(3), obstack_vprintf(3)
 * Append formated strings to a given obstack. s.a. `obstack_printer(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(obstack_vprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL obstack_vprintf)(struct obstack *__restrict __self, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(obstack_vprintf))(__self, __format, __args); })
#endif /* __CRT_HAVE_obstack_printer || __CRT_HAVE__obstack_newchunk || __LOCAL_obstack_alloc_failed_handler || __CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit || __CRT_HAVE_xexit */
#endif /* !__CRT_HAVE_obstack_vprintf */
#ifdef __CRT_HAVE_obstack_printf
/* >> obstack_printf(3), obstack_vprintf(3)
 * Append formated strings to a given obstack. s.a. `obstack_printer(3)' */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL obstack_printf)(struct obstack *__restrict __self, char const *__restrict __format, ...) __CASMNAME_SAME("obstack_printf");
#else /* __CRT_HAVE_obstack_printf */
#include <bits/crt/obstack.h>
#if defined(__CRT_HAVE_obstack_vprintf) || defined(__CRT_HAVE_obstack_printer) || defined(__CRT_HAVE__obstack_newchunk) || defined(__LOCAL_obstack_alloc_failed_handler) || defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE_xexit)
#include <libc/local/stdio/obstack_printf.h>
/* >> obstack_printf(3), obstack_vprintf(3)
 * Append formated strings to a given obstack. s.a. `obstack_printer(3)' */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(obstack_printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL obstack_printf)(struct obstack *__restrict __self, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(obstack_printf))(__self, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define obstack_printf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(obstack_printf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* __CRT_HAVE_obstack_vprintf || __CRT_HAVE_obstack_printer || __CRT_HAVE__obstack_newchunk || __LOCAL_obstack_alloc_failed_handler || __CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit || __CRT_HAVE_xexit */
#endif /* !__CRT_HAVE_obstack_printf */
#endif /* __USE_GNU */
#if defined(__USE_LARGEFILE) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_fseek_unlocked) && defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseek64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <libc/local/stdio/fseeko.h>
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fseeko, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fseeko)(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseeko))(__stream, __off, __whence); })
#endif /* ... */
#if defined(__CRT_HAVE_ftell_unlocked) && defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_ftello64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE_ftell64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),ftell64,(__stream))
#elif defined(__CRT_HAVE__ftelli64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftell_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
#include <libc/local/stdio/ftello.h>
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ftello, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __FS_TYPE(off) (__LIBCCALL ftello)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftello))(__stream); })
#endif /* ... */
#endif /* __USE_LARGEFILE || __USE_XOPEN2K */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_tmpfile) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> tmpfile(3), tmpfile64(3)
 * Create and return a new file-stream for accessing a temporary file for reading/writing */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_RPC,tmpfile64,(void),tmpfile,())
#elif defined(__CRT_HAVE_tmpfile64)
/* >> tmpfile(3), tmpfile64(3)
 * Create and return a new file-stream for accessing a temporary file for reading/writing */
__CDECLARE(__ATTR_WUNUSED,__FILE *,__NOTHROW_RPC,tmpfile64,(void),())
#endif /* ... */
#if defined(__CRT_HAVE_fseek_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <libc/local/stdio/fseeko64.h>
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fseeko64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fseeko64)(__FILE *__restrict __stream, __off64_t __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseeko64))(__stream, __off, __whence); })
#endif /* ... */
#if defined(__CRT_HAVE_ftell_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftello64)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_ftell64)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),ftell64,(__stream))
#elif defined(__CRT_HAVE__ftelli64)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftell_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
#include <libc/local/stdio/ftello64.h>
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ftello64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __off64_t (__LIBCCALL ftello64)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftello64))(__stream); })
#endif /* ... */
#if defined(__CRT_HAVE_fopen) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> fopen(3), fopen64(3)
 * Create and return a new file-stream for accessing `filename' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,fopen64,(char const *__restrict __filename, char const *__restrict __modes),fopen,(__filename,__modes))
#elif defined(__CRT_HAVE_fopen64)
/* >> fopen(3), fopen64(3)
 * Create and return a new file-stream for accessing `filename' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,fopen64,(char const *__restrict __filename, char const *__restrict __modes),(__filename,__modes))
#endif /* ... */
#if defined(__CRT_HAVE_freopen_unlocked) && defined(__USE_STDIO_UNLOCKED) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen64_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen_unlocked) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64_unlocked)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen64_unlocked,(__filename,__modes,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fgetpos_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),_IO_fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64)
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos64)
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),_IO_fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos_unlocked) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked)
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
#include <libc/local/stdio/fgetpos64.h>
/* >> fgetpos(3), fgetpos64(3)
 * Initialize   an   opaque  descriptor   `pos'   for  the   current   in-file  position   of  `stream'
 * Upon success (return == 0), `pos' can be used to restore the current position by calling `fsetpos()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetpos64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int (__LIBCCALL fgetpos64)(__FILE *__restrict __stream, fpos64_t *__restrict __pos) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetpos64))(__stream, __pos); })
#endif /* ... */
#if defined(__CRT_HAVE_fsetpos_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),_IO_fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64)
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos64)
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),_IO_fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos_unlocked) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64_unlocked)
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))
#include <libc/local/stdio/fsetpos64.h>
/* >> fsetpos(3), fsetpos64(3)
 * Set the file position of `stream' to `pos', as previously initialized with a call to `fgetpos()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fsetpos64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int (__LIBCCALL fsetpos64)(__FILE *__restrict __stream, fpos64_t const *__restrict __pos) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fsetpos64))(__stream, __pos); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_KOS
#if defined(__CRT_HAVE_file_printer_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> file_printer(3)
 * For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__COMPILER_CREDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__FORMATPRINTER_CC,file_printer,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),file_printer_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_printer)
/* >> file_printer(3)
 * For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__LIBC __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__FORMATPRINTER_CC file_printer)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) __CASMNAME_SAME("file_printer");
#elif defined(__CRT_HAVE_file_printer_unlocked)
/* >> file_printer(3)
 * For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__COMPILER_CREDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__FORMATPRINTER_CC,file_printer,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),file_printer_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/file_printer.h>
/* >> file_printer(3)
 * For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__FORMATPRINTER_CC file_printer)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_printer))(__arg, __data, __datalen); })
#endif /* ... */
#ifdef __CRT_HAVE_file_printer_unlocked
/* >> file_printer_unlocked(3)
 * Same as `file_printer()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__LIBC __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__FORMATPRINTER_CC file_printer_unlocked)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) __CASMNAME_SAME("file_printer_unlocked");
#elif defined(__CRT_HAVE_file_printer)
/* >> file_printer_unlocked(3)
 * Same as `file_printer()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,__FORMATPRINTER_CC,file_printer_unlocked,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),file_printer,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/stdio/file_printer_unlocked.h>
/* >> file_printer_unlocked(3)
 * Same as `file_printer()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_printer_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__FORMATPRINTER_CC file_printer_unlocked)(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_printer_unlocked))(__arg, __data, __datalen); })
#endif /* ... */
#endif /* __USE_KOS */

#if defined(__USE_GNU) || defined(__USE_SOLARIS) || defined(__USE_BSD)
#ifndef __vasprintf_defined
#define __vasprintf_defined
#ifdef __CRT_HAVE_vasprintf
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vasprintf,(char **__restrict __pstr, char const *__restrict __format, __builtin_va_list __args),(__pstr,__format,__args))
#elif (defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))
#include <libc/local/stdio/vasprintf.h>
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
__NAMESPACE_LOCAL_USING_OR_IMPL(vasprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL vasprintf)(char **__restrict __pstr, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vasprintf))(__pstr, __format, __args); })
#else /* ... */
#undef __vasprintf_defined
#endif /* !... */
#endif /* !__vasprintf_defined */
#ifndef __asprintf_defined
#define __asprintf_defined
#ifdef __CRT_HAVE_asprintf
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL asprintf)(char **__restrict __pstr, char const *__restrict __format, ...) __CASMNAME_SAME("asprintf");
#elif defined(__CRT_HAVE___asprintf)
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL asprintf)(char **__restrict __pstr, char const *__restrict __format, ...) __CASMNAME("__asprintf");
#elif defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))
#include <libc/local/stdio/asprintf.h>
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(asprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL asprintf)(char **__restrict __pstr, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asprintf))(__pstr, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define asprintf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asprintf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* ... */
#undef __asprintf_defined
#endif /* !... */
#endif /* !__asprintf_defined */
#ifdef __CRT_HAVE_asprintf
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL __asprintf)(char **__restrict __pstr, char const *__restrict __format, ...) __CASMNAME("asprintf");
#elif defined(__CRT_HAVE___asprintf)
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL __asprintf)(char **__restrict __pstr, char const *__restrict __format, ...) __CASMNAME_SAME("__asprintf");
#elif defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))
#include <libc/local/stdio/asprintf.h>
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
#define __asprintf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asprintf))(__VA_ARGS__)
#endif /* ... */
#endif /* __USE_GNU || __USE_SOLARIS || __USE_BSD */




#ifdef __USE_KOS
#if defined(__CRT_HAVE_fdreopen_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fdreopen(3), fdreopen_unlocked(3)
 * Re-open the given `stream' as a file-stream for accessing `fd' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,fdreopen,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),fdreopen_unlocked,(__fd,__modes,__stream))
#elif defined(__CRT_HAVE_fdreopen)
/* >> fdreopen(3), fdreopen_unlocked(3)
 * Re-open the given `stream' as a file-stream for accessing `fd' */
__CDECLARE(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,fdreopen,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),(__fd,__modes,__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fdreopen_unlocked
/* >> fdreopen(3), fdreopen_unlocked(3)
 * Re-open the given `stream' as a file-stream for accessing `fd' */
__CDECLARE(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,fdreopen_unlocked,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),(__fd,__modes,__stream))
#elif defined(__CRT_HAVE_fdreopen)
/* >> fdreopen(3), fdreopen_unlocked(3)
 * Re-open the given `stream' as a file-stream for accessing `fd' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),__FILE *,__NOTHROW_RPC,fdreopen_unlocked,(__fd_t __fd, char const *__restrict __modes, __FILE *__restrict __stream),fdreopen,(__fd,__modes,__stream))
#endif /* ... */
#ifndef __freopen_unlocked_defined
#define __freopen_unlocked_defined
#if defined(__CRT_HAVE_freopen_unlocked) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64_unlocked)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen64_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen64,(__filename,__modes,__stream))
#else /* ... */
#undef __freopen_unlocked_defined
#endif /* !... */
#endif /* !__freopen_unlocked_defined */
#if defined(__CRT_HAVE_freopen_unlocked) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64_unlocked)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen64_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen64,(__filename,__modes,__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fseek_unlocked
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),fseek64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek_unlocked,(__FILE *__restrict __stream, long int __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock)
#include <libc/local/stdio/fseek_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fseek_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fseek_unlocked)(__FILE *__restrict __stream, long int __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseek_unlocked))(__stream, __off, __whence); })
#endif /* ... */
#ifdef __CRT_HAVE_ftell_unlocked
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__ftell_nolock)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftello64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE_ftell64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),ftell64,(__stream))
#elif defined(__CRT_HAVE__ftelli64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,ftell_unlocked,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked)
#include <libc/local/stdio/ftell_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ftell_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) long int (__LIBCCALL ftell_unlocked)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftell_unlocked))(__stream); })
#endif /* ... */
#if defined(__CRT_HAVE_fseek_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),fseek64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko_unlocked,(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <libc/local/stdio/fseeko_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fseeko_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fseeko_unlocked)(__FILE *__restrict __stream, __FS_TYPE(off) __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseeko_unlocked))(__stream, __off, __whence); })
#endif /* ... */
#if defined(__CRT_HAVE_ftell_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && __FS_SIZEOF(OFF) == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftello64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE_ftell64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),ftell64,(__stream))
#elif defined(__CRT_HAVE__ftelli64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__FS_TYPE(off),__THROWING,ftello_unlocked,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
#include <libc/local/stdio/ftello_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ftello_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __FS_TYPE(off) (__LIBCCALL ftello_unlocked)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftello_unlocked))(__stream); })
#endif /* ... */
#ifdef __CRT_HAVE_flushall_unlocked
__CDECLARE(,int,__THROWING,flushall_unlocked,(void),())
#elif defined(__CRT_HAVE__flushall)
__CREDIRECT(,int,__THROWING,flushall_unlocked,(void),_flushall,())
#elif defined(__CRT_HAVE__IO_flush_all)
__CREDIRECT(,int,__THROWING,flushall_unlocked,(void),_IO_flush_all,())
#else /* ... */
#include <libc/local/stdio/flushall_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(flushall_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL flushall_unlocked)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(flushall_unlocked))(); })
#endif /* !... */
#if defined(__CRT_HAVE_fgetpos_unlocked) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(fpos) *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(fpos) *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(fpos) *__restrict __pos),fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(fpos) *__restrict __pos),_IO_fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(fpos) *__restrict __pos),fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos64) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(fpos) *__restrict __pos),_IO_fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
#include <libc/local/stdio/fgetpos_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetpos_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int (__LIBCCALL fgetpos_unlocked)(__FILE *__restrict __stream, __FS_TYPE(fpos) *__restrict __pos) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetpos_unlocked))(__stream, __pos); })
#endif /* ... */
#if defined(__CRT_HAVE_fsetpos_unlocked) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(fpos) const *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64_unlocked) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(fpos) const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(fpos) const *__restrict __pos),fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(fpos) const *__restrict __pos),_IO_fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(fpos) const *__restrict __pos),fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos64) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos_unlocked,(__FILE *__restrict __stream, __FS_TYPE(fpos) const *__restrict __pos),_IO_fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <libc/local/stdio/fsetpos_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fsetpos_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int (__LIBCCALL fsetpos_unlocked)(__FILE *__restrict __stream, __FS_TYPE(fpos) const *__restrict __pos) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fsetpos_unlocked))(__stream, __pos); })
#endif /* ... */
#ifdef __CRT_HAVE_getw_unlocked
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,getw_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_getw)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getw_unlocked,(__FILE *__restrict __stream),getw,(__stream))
#elif defined(__CRT_HAVE__getw)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,getw_unlocked,(__FILE *__restrict __stream),_getw,(__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/stdio/getw_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getw_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL getw_unlocked)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getw_unlocked))(__stream); })
#endif /* ... */
#ifdef __CRT_HAVE_putw_unlocked
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,putw_unlocked,(int __w, __FILE *__restrict __stream),(__w,__stream))
#elif defined(__CRT_HAVE_putw)
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putw_unlocked,(int __w, __FILE *__restrict __stream),putw,(__w,__stream))
#elif defined(__CRT_HAVE__putw)
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,putw_unlocked,(int __w, __FILE *__restrict __stream),_putw,(__w,__stream))
#elif defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/putw_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(putw_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL putw_unlocked)(int __w, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putw_unlocked))(__w, __stream); })
#endif /* ... */
#ifdef __CRT_HAVE_setvbuf_unlocked
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setvbuf_unlocked,(__FILE *__restrict __stream, char *__restrict __buf, __STDC_INT_AS_UINT_T __modes, __SIZE_TYPE__ __bufsize),(__stream,__buf,__modes,__bufsize))
#elif defined(__CRT_HAVE_setvbuf)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setvbuf_unlocked,(__FILE *__restrict __stream, char *__restrict __buf, __STDC_INT_AS_UINT_T __modes, __SIZE_TYPE__ __bufsize),setvbuf,(__stream,__buf,__modes,__bufsize))
#elif defined(__CRT_HAVE__IO_setvbuf)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setvbuf_unlocked,(__FILE *__restrict __stream, char *__restrict __buf, __STDC_INT_AS_UINT_T __modes, __SIZE_TYPE__ __bufsize),_IO_setvbuf,(__stream,__buf,__modes,__bufsize))
#endif /* ... */
#ifdef __CRT_HAVE_ungetc_unlocked
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc_unlocked,(int __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc_unlocked,(int __ch, __FILE *__restrict __stream),_ungetc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc_unlocked,(int __ch, __FILE *__restrict __stream),ungetc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_ungetc)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,ungetc_unlocked,(int __ch, __FILE *__restrict __stream),_IO_ungetc,(__ch,__stream))
#endif /* ... */
#ifdef __CRT_HAVE_getdelim_unlocked
/* >> getdelim(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,getdelim_unlocked,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE_getdelim)
/* >> getdelim(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,getdelim_unlocked,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE___getdelim)
/* >> getdelim(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,getdelim_unlocked,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),__getdelim,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE__IO_getdelim)
/* >> getdelim(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)),__SSIZE_TYPE__,__THROWING,getdelim_unlocked,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),_IO_getdelim,(__lineptr,__pcount,__delimiter,__stream))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
#include <libc/local/stdio/getdelim_unlocked.h>
/* >> getdelim(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getdelim_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 4)) __SSIZE_TYPE__ (__LIBCCALL getdelim_unlocked)(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getdelim_unlocked))(__lineptr, __pcount, __delimiter, __stream); })
#endif /* ... */
#ifdef __CRT_HAVE_getline_unlocked
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,getline_unlocked,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE_getline)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,getline_unlocked,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),getline,(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE___getline)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,getline_unlocked,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),__getline,(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE__IO_getline)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),__SSIZE_TYPE__,__THROWING,getline_unlocked,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream),_IO_getline,(__lineptr,__pcount,__stream))
#elif defined(__CRT_HAVE_getdelim_unlocked) || defined(__CRT_HAVE_getdelim) || defined(__CRT_HAVE___getdelim) || defined(__CRT_HAVE__IO_getdelim) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <libc/local/stdio/getline_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getline_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) __SSIZE_TYPE__ (__LIBCCALL getline_unlocked)(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getline_unlocked))(__lineptr, __pcount, __stream); })
#endif /* ... */
#ifdef __CRT_HAVE_rewind_unlocked
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,rewind_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_rewind)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__THROWING,rewind_unlocked,(__FILE *__restrict __stream),rewind,(__stream))
#elif defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <libc/local/stdio/rewind_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(rewind_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void (__LIBCCALL rewind_unlocked)(__FILE *__restrict __stream) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rewind_unlocked))(__stream); })
#endif /* ... */
#ifdef __CRT_HAVE_fisatty
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,fisatty,(__FILE *__restrict __stream),(__stream))
#else /* __CRT_HAVE_fisatty */
#include <asm/os/tty.h>
#if (defined(__CRT_HAVE_isatty) || defined(__CRT_HAVE__isatty) || defined(__CRT_HAVE___isatty) || defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked))
#include <libc/local/stdio/fisatty.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fisatty, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL fisatty)(__FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fisatty))(__stream); })
#endif /* (__CRT_HAVE_isatty || __CRT_HAVE__isatty || __CRT_HAVE___isatty || __CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) */
#endif /* !__CRT_HAVE_fisatty */
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __FS_TYPE(pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __FS_TYPE(off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
#if defined(__CRT_HAVE_fftruncate_unlocked) && defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
/* >> fftruncate(3)
 * Truncate the given file `stream' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate,(__FILE *__restrict __stream, __PIO_OFFSET __length),fftruncate_unlocked,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> fftruncate(3)
 * Truncate the given file `stream' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate,(__FILE *__restrict __stream, __PIO_OFFSET __length),fftruncate64_unlocked,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
/* >> fftruncate(3)
 * Truncate the given file `stream' to a length of `length' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fftruncate,(__FILE *__restrict __stream, __PIO_OFFSET __length),(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> fftruncate(3)
 * Truncate the given file `stream' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate,(__FILE *__restrict __stream, __PIO_OFFSET __length),fftruncate64,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
/* >> fftruncate(3)
 * Truncate the given file `stream' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate,(__FILE *__restrict __stream, __PIO_OFFSET __length),fftruncate_unlocked,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate64_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> fftruncate(3)
 * Truncate the given file `stream' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate,(__FILE *__restrict __stream, __PIO_OFFSET __length),fftruncate64_unlocked,(__stream,__length))
#elif (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked))
#include <libc/local/stdio/fftruncate.h>
/* >> fftruncate(3)
 * Truncate the given file `stream' to a length of `length' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fftruncate, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fftruncate)(__FILE *__restrict __stream, __PIO_OFFSET __length) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fftruncate))(__stream, __length); })
#endif /* ... */
#if defined(__CRT_HAVE_fftruncate_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fftruncate_unlocked,(__FILE *__restrict __stream, __PIO_OFFSET __length),(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate64_unlocked) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate_unlocked,(__FILE *__restrict __stream, __PIO_OFFSET __length),fftruncate64_unlocked,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate_unlocked,(__FILE *__restrict __stream, __PIO_OFFSET __length),fftruncate,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate_unlocked,(__FILE *__restrict __stream, __PIO_OFFSET __length),fftruncate64,(__stream,__length))
#elif (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked))
#include <libc/local/stdio/fftruncate_unlocked.h>
/* >> fftruncate_unlocked(3)
 * Same as `fftruncate()', but don't acquire a lock to the file */
__NAMESPACE_LOCAL_USING_OR_IMPL(fftruncate_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fftruncate_unlocked)(__FILE *__restrict __stream, __PIO_OFFSET __length) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fftruncate_unlocked))(__stream, __length); })
#endif /* ... */
#if __has_builtin(__builtin_puts_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_puts_unlocked)
__CEIDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,puts_unlocked,(char const *__restrict __string),{ return __builtin_puts_unlocked(__string); })
#elif defined(__CRT_HAVE_puts_unlocked)
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,puts_unlocked,(char const *__restrict __string),(__string))
#elif defined(__CRT_HAVE_puts)
__CREDIRECT(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,puts_unlocked,(char const *__restrict __string),puts,(__string))
#elif defined(__LOCAL_stdout) && (defined(__CRT_HAVE_fputs_unlocked) || defined(__CRT_HAVE_fputs) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))
#include <libc/local/stdio/puts_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(puts_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL puts_unlocked)(char const *__restrict __string) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(puts_unlocked))(__string); })
#endif /* ... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_fseek_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64_unlocked,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64_unlocked,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64_unlocked,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked)
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fseeko64_unlocked,(__FILE *__restrict __stream, __off64_t __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64_unlocked,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64_unlocked,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64_unlocked,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64_unlocked,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64_unlocked,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64_unlocked,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseeko64_unlocked,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <libc/local/stdio/fseeko64_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fseeko64_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fseeko64_unlocked)(__FILE *__restrict __stream, __off64_t __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseeko64_unlocked))(__stream, __off, __whence); })
#endif /* ... */
#if defined(__CRT_HAVE_ftell_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftello64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE_ftell64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),ftell64,(__stream))
#elif defined(__CRT_HAVE__ftelli64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftello64_unlocked,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
#include <libc/local/stdio/ftello64_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ftello64_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __off64_t (__LIBCCALL ftello64_unlocked)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftello64_unlocked))(__stream); })
#endif /* ... */
#if defined(__CRT_HAVE_fgetpos_unlocked) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),_IO_fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fgetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t *__restrict __pos),_IO_fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
#include <libc/local/stdio/fgetpos64_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetpos64_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int (__LIBCCALL fgetpos64_unlocked)(__FILE *__restrict __stream, fpos64_t *__restrict __pos) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetpos64_unlocked))(__stream, __pos); })
#endif /* ... */
#if defined(__CRT_HAVE_fsetpos_unlocked) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64_unlocked)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),_IO_fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,fsetpos64_unlocked,(__FILE *__restrict __stream, fpos64_t const *__restrict __pos),_IO_fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))
#include <libc/local/stdio/fsetpos64_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fsetpos64_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int (__LIBCCALL fsetpos64_unlocked)(__FILE *__restrict __stream, fpos64_t const *__restrict __pos) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fsetpos64_unlocked))(__stream, __pos); })
#endif /* ... */
#if defined(__CRT_HAVE_fftruncate_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> fftruncate64(3)
 * Truncate the given file `stream' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),fftruncate_unlocked,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fftruncate64(3)
 * Truncate the given file `stream' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),fftruncate64_unlocked,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> fftruncate64(3)
 * Truncate the given file `stream' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),fftruncate,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate64)
/* >> fftruncate64(3)
 * Truncate the given file `stream' to a length of `length' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> fftruncate64(3)
 * Truncate the given file `stream' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),fftruncate_unlocked,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate64_unlocked)
/* >> fftruncate64(3)
 * Truncate the given file `stream' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),fftruncate64_unlocked,(__stream,__length))
#elif (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked))
#include <libc/local/stdio/fftruncate64.h>
/* >> fftruncate64(3)
 * Truncate the given file `stream' to a length of `length' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fftruncate64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fftruncate64)(__FILE *__restrict __stream, __PIO_OFFSET64 __length) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fftruncate64))(__stream, __length); })
#endif /* ... */
#if defined(__CRT_HAVE_fftruncate_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `stream' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64_unlocked,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),fftruncate_unlocked,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate64_unlocked)
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `stream' to a length of `length' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64_unlocked,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `stream' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64_unlocked,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),fftruncate,(__stream,__length))
#elif defined(__CRT_HAVE_fftruncate64)
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `stream' to a length of `length' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fftruncate64_unlocked,(__FILE *__restrict __stream, __PIO_OFFSET64 __length),fftruncate64,(__stream,__length))
#elif (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked))
#include <libc/local/stdio/fftruncate64_unlocked.h>
/* >> fftruncate64_unlocked(3)
 * Truncate the given file `stream' to a length of `length' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fftruncate64_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fftruncate64_unlocked)(__FILE *__restrict __stream, __PIO_OFFSET64 __length) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fftruncate64_unlocked))(__stream, __length); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#ifdef __CRT_HAVE_vfprintf_unlocked
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf)
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf_s)
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_s,(__stream,__format,__args))
#elif defined(__CRT_HAVE__IO_vfprintf)
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,vfprintf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_IO_vfprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/stdio/vfprintf_unlocked.h>
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vfprintf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL vfprintf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfprintf_unlocked))(__stream, __format, __args); })
#endif /* ... */
#if __has_builtin(__builtin_fprintf_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fprintf_unlocked) && __has_builtin(__builtin_va_arg_pack)
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
__CEIDECLARE(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,fprintf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, ...),{ return __builtin_fprintf_unlocked(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fprintf_unlocked)
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fprintf_unlocked");
#elif defined(__CRT_HAVE_fprintf_s)
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_s");
#elif defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/stdio/fprintf_unlocked.h>
/* >> fprintf_unlocked(3), vfprintf_unlocked(3) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(fprintf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fprintf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fprintf_unlocked))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define fprintf_unlocked(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fprintf_unlocked))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE_vprintf_unlocked
/* >> printf_unlocked(3), vprintf_unlocked(3) */
__CDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf_unlocked,(char const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE_vprintf_s)
/* >> printf_unlocked(3), vprintf_unlocked(3) */
__CREDIRECT(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,vprintf_unlocked,(char const *__restrict __format, __builtin_va_list __args),vprintf_s,(__format,__args))
#elif defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/stdio/vprintf_unlocked.h>
/* >> printf_unlocked(3), vprintf_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vprintf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL vprintf_unlocked)(char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vprintf_unlocked))(__format, __args); })
#endif /* ... */
#if __has_builtin(__builtin_printf_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_printf_unlocked) && __has_builtin(__builtin_va_arg_pack)
/* >> printf_unlocked(3), vprintf_unlocked(3) */
__CEIDECLARE(__ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,printf_unlocked,(char const *__restrict __format, ...),{ return __builtin_printf_unlocked(__format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_printf_unlocked)
/* >> printf_unlocked(3), vprintf_unlocked(3) */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf_unlocked)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("printf_unlocked");
#elif defined(__CRT_HAVE_printf_s)
/* >> printf_unlocked(3), vprintf_unlocked(3) */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf_unlocked)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME("printf_s");
#elif defined(__CRT_HAVE_vprintf_unlocked) || defined(__CRT_HAVE_vprintf_s) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/stdio/printf_unlocked.h>
/* >> printf_unlocked(3), vprintf_unlocked(3) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(printf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL printf_unlocked)(char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(printf_unlocked))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define printf_unlocked(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(printf_unlocked))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE_vfscanf_unlocked
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfscanf)
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE___vfscanf)
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),__vfscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE__vfscanf)
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_vfscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE__vfscanf_s)
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_vfscanf_s,(__stream,__format,__args))
#elif defined(__CRT_HAVE__IO_vfscanf)
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfscanf_unlocked,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_IO_vfscanf,(__stream,__format,__args))
#elif (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
#include <libc/local/stdio/vfscanf_unlocked.h>
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vfscanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL vfscanf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfscanf_unlocked))(__stream, __format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_vscanf_unlocked
/* >> scanf_unlocked(3), vscanf_unlocked(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf_unlocked,(char const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE__vscanf)
/* >> scanf_unlocked(3), vscanf_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vscanf_unlocked,(char const *__restrict __format, __builtin_va_list __args),_vscanf,(__format,__args))
#elif defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE___vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || ((defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))))
#include <libc/local/stdio/vscanf_unlocked.h>
/* >> scanf_unlocked(3), vscanf_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vscanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vscanf_unlocked)(char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vscanf_unlocked))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_fscanf_unlocked
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fscanf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fscanf_unlocked");
#elif defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE___vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || ((defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <libc/local/stdio/fscanf_unlocked.h>
/* >> fscanf_unlocked(3), vfscanf_unlocked(3) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(fscanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fscanf_unlocked)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fscanf_unlocked))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define fscanf_unlocked(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fscanf_unlocked))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE_scanf_unlocked
/* >> scanf_unlocked(3), vscanf_unlocked(3) */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL scanf_unlocked)(char const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("scanf_unlocked");
#elif defined(__CRT_HAVE_vscanf_unlocked) || defined(__CRT_HAVE__vscanf) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE___vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || ((defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
#include <libc/local/stdio/scanf_unlocked.h>
/* >> scanf_unlocked(3), vscanf_unlocked(3) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(scanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL scanf_unlocked)(char const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scanf_unlocked))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define scanf_unlocked(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scanf_unlocked))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#endif /* __USE_KOS */

#ifdef __USE_SOLARIS
#if !defined(__USE_XOPEN) || defined(_EVERY_SOURCE)
#ifndef __getsubopt_defined
#define __getsubopt_defined
#ifdef __CRT_HAVE_getsubopt
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,getsubopt,(char **__restrict __optionp, char *const *__restrict __tokens, char **__restrict __valuep),(__optionp,__tokens,__valuep))
#else /* __CRT_HAVE_getsubopt */
#include <libc/local/stdlib/getsubopt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getsubopt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL getsubopt)(char **__restrict __optionp, char *const *__restrict __tokens, char **__restrict __valuep) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getsubopt))(__optionp, __tokens, __valuep); })
#endif /* !__CRT_HAVE_getsubopt */
#endif /* !__getsubopt_defined */
#endif /* !__USE_XOPEN || _EVERY_SOURCE */
#endif /* __USE_SOLARIS */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_fseek_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,fseek64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <libc/local/stdio/fseeko64.h>
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL fseek64)(__FILE *__restrict __stream, __off64_t __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseeko64))(__stream, __off, __whence); }
#endif /* ... */
#if defined(__CRT_HAVE_ftell_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftello64)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE_ftell64)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__ftelli64)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftell_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,ftell64,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
#include <libc/local/stdio/ftello64.h>
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __off64_t (__LIBCCALL ftell64)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftello64))(__stream); }
#endif /* ... */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_NETBSD
#ifndef __fparseln_defined
#define __fparseln_defined
#ifdef __CRT_HAVE_fparseln
/* >> fparseln(3)
 * Parse one line of text from `stream', whilst accounting for
 * special character escapes, as well as custom line-comments.
 * @param: plen:    When non-NULL, store `strlen(return)' here
 * @param: plineno: When non-NULL, incremented for every line-feed read from `stream'
 * @param: delim:   Special characters (use NUL to disable, and NULL to use defaults)
 *                     delim[0]: The escape character (defaults to '\\')
 *                     delim[1]: The line-continuation character (defaults to '\\')
 *                     delim[2]: The line-comment character (defaults to '#')
 * @param: flags:   Set of `FPARSELN_UNESC*'
 * @return: * :     Pointer to a heap-allocated, and pre-escaped (according to `flags')
 *                  line,  that must  be `free(3)'ed by  the caller once  they are done
 *                  using it.
 *                  If the result would be empty  as the result of `feof(stream)'  upon
 *                  return of this function, `strdup("")' will be returned. (i.e.  NULL
 *                  is only returned in case of an error; _NOT_ in case of end-of-file)
 * @return: NULL:   Error (s.a. `errno' and `ferror(stream)') */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_RPC,fparseln,(__FILE *__stream, size_t *__plen, size_t *__plineno, char const __delim[3], __STDC_INT_AS_UINT_T __flags),(__stream,__plen,__plineno,__delim,__flags))
#elif (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/util/fparseln.h>
/* >> fparseln(3)
 * Parse one line of text from `stream', whilst accounting for
 * special character escapes, as well as custom line-comments.
 * @param: plen:    When non-NULL, store `strlen(return)' here
 * @param: plineno: When non-NULL, incremented for every line-feed read from `stream'
 * @param: delim:   Special characters (use NUL to disable, and NULL to use defaults)
 *                     delim[0]: The escape character (defaults to '\\')
 *                     delim[1]: The line-continuation character (defaults to '\\')
 *                     delim[2]: The line-comment character (defaults to '#')
 * @param: flags:   Set of `FPARSELN_UNESC*'
 * @return: * :     Pointer to a heap-allocated, and pre-escaped (according to `flags')
 *                  line,  that must  be `free(3)'ed by  the caller once  they are done
 *                  using it.
 *                  If the result would be empty  as the result of `feof(stream)'  upon
 *                  return of this function, `strdup("")' will be returned. (i.e.  NULL
 *                  is only returned in case of an error; _NOT_ in case of end-of-file)
 * @return: NULL:   Error (s.a. `errno' and `ferror(stream)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(fparseln, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_RPC(__LIBCCALL fparseln)(__FILE *__stream, size_t *__plen, size_t *__plineno, char const __delim[3], __STDC_INT_AS_UINT_T __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fparseln))(__stream, __plen, __plineno, __delim, __flags); })
#else /* ... */
#undef __fparseln_defined
#endif /* !... */
#endif /* !__fparseln_defined */
#ifndef __fmtcheck_defined
#define __fmtcheck_defined
#ifdef __CRT_HAVE_fmtcheck
/* >> fmtcheck(3)
 * Check if `user_format' may be used as a drop-in replacement for `good_format'
 * in the context of a call to `printf(3)' (or `format_printf()'), such that all
 * contained format qualifiers reference the  same (or compatible) underlying  C
 * types, and in the same order.
 * If all of this is the  case, simply re-return `user_format'. Otherwise  (i.e.
 * when `user_format' isn't compatible with `good_format'), return `good_format'
 * instead. This function is meant to  be used to validate user-provided  printf
 * format strings before actually using them, after they've been read from  lang
 * config files: `printf(fmtcheck(get_user_fmt(), "%s %s"), "Foo", "Bar");' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((2)) __ATTR_FORMAT_ARG(2),char const *,__NOTHROW_NCX,fmtcheck,(char const *__user_format, char const *__good_format),(__user_format,__good_format))
#else /* __CRT_HAVE_fmtcheck */
#include <libc/local/stdio/fmtcheck.h>
/* >> fmtcheck(3)
 * Check if `user_format' may be used as a drop-in replacement for `good_format'
 * in the context of a call to `printf(3)' (or `format_printf()'), such that all
 * contained format qualifiers reference the  same (or compatible) underlying  C
 * types, and in the same order.
 * If all of this is the  case, simply re-return `user_format'. Otherwise  (i.e.
 * when `user_format' isn't compatible with `good_format'), return `good_format'
 * instead. This function is meant to  be used to validate user-provided  printf
 * format strings before actually using them, after they've been read from  lang
 * config files: `printf(fmtcheck(get_user_fmt(), "%s %s"), "Foo", "Bar");' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmtcheck, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((2)) __ATTR_FORMAT_ARG(2) char const *__NOTHROW_NCX(__LIBCCALL fmtcheck)(char const *__user_format, char const *__good_format) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmtcheck))(__user_format, __good_format); })
#endif /* !__CRT_HAVE_fmtcheck */
#endif /* !__fmtcheck_defined */
#endif /* __USE_NETBSD */

#ifdef __USE_BSD
#ifndef __fpurge_defined
#define __fpurge_defined
#ifdef __CRT_HAVE___fpurge
/* >> __fpurge(3)
 * Discard all modified, but unwritten data from `stream', as  well
 * as  all unread data previously buffered, but not yet read. After
 * a call to this function, the next `fread(3)' or `fwrite(3)' will
 * start off from a blank state. */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,fpurge,(__FILE *__stream),__fpurge,(__stream))
#elif defined(__CRT_HAVE_fpurge)
/* >> __fpurge(3)
 * Discard all modified, but unwritten data from `stream', as  well
 * as  all unread data previously buffered, but not yet read. After
 * a call to this function, the next `fread(3)' or `fwrite(3)' will
 * start off from a blank state. */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,fpurge,(__FILE *__stream),(__stream))
#else /* ... */
#undef __fpurge_defined
#endif /* !... */
#endif /* !__fpurge_defined */
#if !defined(__fgetln_defined) && defined(__CRT_HAVE_fgetln)
#define __fgetln_defined
/* >> fgetln(3)
 * A slightly more convenient (but way less portable) alternative to `fgets(3)'
 * This function automatically malloc's a  buffer of sufficient length for  the
 * next line in the given `stream', and stores its length in `*lenp'
 * NOTE: KOS adds the following extensions to this function:
 *  - We guaranty that "return[*lenp] == '\0'" upon a non-NULL return
 *  - You may pass `lenp == NULL', which simply ignores that argument
 * @return: NULL: The EOF flag of `stream' is set (fix this with `clearerr(3)'),
 *                or the underlying file has been fully read.
 * @return: * :   Pointer to an  automatically malloc'd  buffer (to-be  freed
 *                by  fclose(3)  once you  call  that function  on  the given
 *                `stream'). The buffer is re-used in subsequence invocations
 *                of this function, and documentation states that it may also
 *                be invalidated during any  other I/O operation relating  to
 *                `stream', tough this isn't the case under KOS. */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,fgetln,(__FILE *__restrict __stream, __SIZE_TYPE__ *__restrict __lenp),(__stream,__lenp))
#endif /* !__fgetln_defined && __CRT_HAVE_fgetln */
#endif /* __USE_BSD */

#if defined(__USE_BSD) || defined(__USE_KOS)
#ifndef __off_t_defined
#define __off_t_defined
typedef __FS_TYPE(off) off_t;
#endif /* !__off_t_defined */
#ifndef __funopen_defined
#define __funopen_defined
#if defined(__CRT_HAVE_funopen) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
/* >> funopen(3), funopen64(3) */
__CDECLARE(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,funopen,(void const *__cookie, int (__LIBKCALL *__readfn)(void *__cookie, char *__buf, int __num_bytes), int (__LIBKCALL *__writefn)(void *__cookie, char const *__buf, int __num_bytes), off_t (__LIBKCALL *__seekfn)(void *__cookie, off_t __off, int __whence), int (__LIBKCALL *__closefn)(void *__cookie)),(__cookie,__readfn,__writefn,__seekfn,__closefn))
#elif defined(__CRT_HAVE_funopen64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> funopen(3), funopen64(3) */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,funopen,(void const *__cookie, int (__LIBKCALL *__readfn)(void *__cookie, char *__buf, int __num_bytes), int (__LIBKCALL *__writefn)(void *__cookie, char const *__buf, int __num_bytes), off_t (__LIBKCALL *__seekfn)(void *__cookie, off_t __off, int __whence), int (__LIBKCALL *__closefn)(void *__cookie)),funopen64,(__cookie,__readfn,__writefn,__seekfn,__closefn))
#else /* ... */
#include <hybrid/typecore.h>
#if (__SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((defined(__CRT_HAVE_funopen2) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__) || (defined(__CRT_HAVE_funopen2_64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2))))) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2) || defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen64) || defined(__CRT_HAVE_funopen)))
#include <libc/local/stdio/funopen.h>
/* >> funopen(3), funopen64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(funopen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __FILE *__NOTHROW_NCX(__LIBCCALL funopen)(void const *__cookie, int (__LIBKCALL *__readfn)(void *__cookie, char *__buf, int __num_bytes), int (__LIBKCALL *__writefn)(void *__cookie, char const *__buf, int __num_bytes), off_t (__LIBKCALL *__seekfn)(void *__cookie, off_t __off, int __whence), int (__LIBKCALL *__closefn)(void *__cookie)) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(funopen))(__cookie, __readfn, __writefn, __seekfn, __closefn); })
#else /* (__SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((__CRT_HAVE_funopen2 && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__) || (__CRT_HAVE_funopen2_64 && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__) || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && ((__CRT_HAVE_funopen2 && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2)))) || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2 || __CRT_HAVE_fopencookie || __CRT_HAVE_funopen64 || __CRT_HAVE_funopen)) */
#undef __funopen_defined
#endif /* (__SIZEOF_INT__ != __SIZEOF_SIZE_T__ || ((!__CRT_HAVE_funopen2 || __FS_SIZEOF(OFF) != __SIZEOF_OFF32_T__) && (!__CRT_HAVE_funopen2_64 || __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__) && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2)))) && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2 && !__CRT_HAVE_fopencookie && !__CRT_HAVE_funopen64 && !__CRT_HAVE_funopen)) */
#endif /* !... */
#endif /* !__funopen_defined */
#ifndef __funopen2_defined
#define __funopen2_defined
#if defined(__CRT_HAVE_funopen2) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
/* >> funopen2(3), funopen2_64(3) */
__CDECLARE(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,funopen2,(void const *__cookie, ssize_t (__LIBKCALL *__readfn)(void *__cookie, void *__buf, size_t __num_bytes), ssize_t (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, size_t __num_bytes), off_t (__LIBKCALL *__seekfn)(void *__cookie, off_t __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)),(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif defined(__CRT_HAVE_funopen2_64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> funopen2(3), funopen2_64(3) */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,funopen2,(void const *__cookie, ssize_t (__LIBKCALL *__readfn)(void *__cookie, void *__buf, size_t __num_bytes), ssize_t (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, size_t __num_bytes), off_t (__LIBKCALL *__seekfn)(void *__cookie, off_t __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)),funopen2_64,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2))
#include <libc/local/stdio/funopen2.h>
/* >> funopen2(3), funopen2_64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(funopen2, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __FILE *__NOTHROW_NCX(__LIBCCALL funopen2)(void const *__cookie, ssize_t (__LIBKCALL *__readfn)(void *__cookie, void *__buf, size_t __num_bytes), ssize_t (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, size_t __num_bytes), off_t (__LIBKCALL *__seekfn)(void *__cookie, off_t __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(funopen2))(__cookie, __readfn, __writefn, __seekfn, __flushfn, __closefn); })
#else /* ... */
#undef __funopen2_defined
#endif /* !... */
#endif /* !__funopen2_defined */
#ifdef __USE_LARGEFILE64
#ifndef __off64_t_defined
#define __off64_t_defined
typedef __off64_t off_t;
#endif /* !__off64_t_defined */
#if defined(__CRT_HAVE_funopen) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> funopen(3), funopen64(3) */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,funopen64,(void const *__cookie, int (__LIBKCALL *__readfn)(void *__cookie, char *__buf, int __num_bytes), int (__LIBKCALL *__writefn)(void *__cookie, char const *__buf, int __num_bytes), off64_t (__LIBKCALL *__seekfn)(void *__cookie, off64_t __off, int __whence), int (__LIBKCALL *__closefn)(void *__cookie)),funopen,(__cookie,__readfn,__writefn,__seekfn,__closefn))
#elif defined(__CRT_HAVE_funopen64)
/* >> funopen(3), funopen64(3) */
__CDECLARE(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,funopen64,(void const *__cookie, int (__LIBKCALL *__readfn)(void *__cookie, char *__buf, int __num_bytes), int (__LIBKCALL *__writefn)(void *__cookie, char const *__buf, int __num_bytes), off64_t (__LIBKCALL *__seekfn)(void *__cookie, off64_t __off, int __whence), int (__LIBKCALL *__closefn)(void *__cookie)),(__cookie,__readfn,__writefn,__seekfn,__closefn))
#elif (__SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2)))) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2) || defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen)))
#include <libc/local/stdio/funopen64.h>
/* >> funopen(3), funopen64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(funopen64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __FILE *__NOTHROW_NCX(__LIBCCALL funopen64)(void const *__cookie, int (__LIBKCALL *__readfn)(void *__cookie, char *__buf, int __num_bytes), int (__LIBKCALL *__writefn)(void *__cookie, char const *__buf, int __num_bytes), off64_t (__LIBKCALL *__seekfn)(void *__cookie, off64_t __off, int __whence), int (__LIBKCALL *__closefn)(void *__cookie)) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(funopen64))(__cookie, __readfn, __writefn, __seekfn, __closefn); })
#endif /* ... */
#if defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> funopen2(3), funopen2_64(3) */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,funopen2_64,(void const *__cookie, ssize_t (__LIBKCALL *__readfn)(void *__cookie, void *__buf, size_t __num_bytes), ssize_t (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, size_t __num_bytes), off64_t (__LIBKCALL *__seekfn)(void *__cookie, off64_t __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)),funopen2,(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif defined(__CRT_HAVE_funopen2_64)
/* >> funopen2(3), funopen2_64(3) */
__CDECLARE(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,funopen2_64,(void const *__cookie, ssize_t (__LIBKCALL *__readfn)(void *__cookie, void *__buf, size_t __num_bytes), ssize_t (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, size_t __num_bytes), off64_t (__LIBKCALL *__seekfn)(void *__cookie, off64_t __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)),(__cookie,__readfn,__writefn,__seekfn,__flushfn,__closefn))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_funopen2)
#include <libc/local/stdio/funopen2_64.h>
/* >> funopen2(3), funopen2_64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(funopen2_64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __FILE *__NOTHROW_NCX(__LIBCCALL funopen2_64)(void const *__cookie, ssize_t (__LIBKCALL *__readfn)(void *__cookie, void *__buf, size_t __num_bytes), ssize_t (__LIBKCALL *__writefn)(void *__cookie, void const *__buf, size_t __num_bytes), off64_t (__LIBKCALL *__seekfn)(void *__cookie, off64_t __off, int __whence), int (__LIBKCALL *__flushfn)(void *__cookie), int (__LIBKCALL *__closefn)(void *__cookie)) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(funopen2_64))(__cookie, __readfn, __writefn, __seekfn, __flushfn, __closefn); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#ifdef __USE_BSD
#ifdef __funopen_defined
#define fropen(cookie, fn) funopen(cookie, fn, __NULLPTR, __NULLPTR, __NULLPTR)
#define fwopen(cookie, fn) funopen(cookie, __NULLPTR, fn, __NULLPTR, __NULLPTR)
#endif /* __funopen_defined */
#ifdef __funopen2_defined
#define fropen2(cookie, fn) funopen2(cookie, fn, __NULLPTR, __NULLPTR, __NULLPTR, __NULLPTR)
#define fwopen2(cookie, fn) funopen2(cookie, __NULLPTR, fn, __NULLPTR, __NULLPTR, __NULLPTR)
#endif /* __funopen2_defined */
#endif /* __USE_BSD */
#endif /* __USE_BSD || __USE_KOS */

#endif /* __CC__ */





#ifdef __USE_DOS
#define _NFILE          512
#define _NSTREAM_       512
#define _IOB_ENTRIES    20
#define _P_tmpdir       "\\"
#define _wP_tmpdir     L"\\"
#define _SYS_OPEN       20
#ifdef __USE_DOS_SLIB
#define L_tmpnam_s      18
#define TMP_MAX_S       2147483647
#define _TMP_MAX_S      2147483647
#endif /* __USE_DOS_SLIB */

#ifndef _FPOS_T_DEFINED
#define _FPOS_T_DEFINED 1
#endif /* !_FPOS_T_DEFINED */

#ifndef _STDSTREAM_DEFINED
#define _STDSTREAM_DEFINED 1
#endif /* !_STDSTREAM_DEFINED */

#ifndef _FILE_DEFINED
#define _FILE_DEFINED 1
#endif /* !_FILE_DEFINED */

#ifndef _CRT_PERROR_DEFINED
#define _CRT_PERROR_DEFINED 1
#endif /* !_CRT_PERROR_DEFINED */

#ifdef __CC__
#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */

#ifndef __rsize_t_defined
#define __rsize_t_defined
typedef __SIZE_TYPE__ rsize_t;
#endif /* !__rsize_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __std_FILE_defined
#define __std_FILE_defined
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */
#ifndef __FILE_defined
#define __FILE_defined
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */


#ifndef _CRT_DIRECTORY_DEFINED
#define _CRT_DIRECTORY_DEFINED 1
#ifndef __unlink_defined
#define __unlink_defined
#ifdef __CRT_HAVE_unlink
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,unlink,(char const *__file),(__file))
#elif defined(__CRT_HAVE__unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,unlink,(char const *__file),_unlink,(__file))
#elif defined(__CRT_HAVE___unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,unlink,(char const *__file),__unlink,(__file))
#elif defined(__CRT_HAVE___libc_unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,unlink,(char const *__file),__libc_unlink,(__file))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <libc/local/unistd/unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL unlink)(char const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unlink))(__file); })
#else /* __AT_FDCWD && __CRT_HAVE_unlinkat */
#undef __unlink_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_unlinkat */
#endif /* !... */
#endif /* !__unlink_defined */
#ifndef ___unlink_defined
#define ___unlink_defined
#ifdef __CRT_HAVE_unlink
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_unlink,(char const *__file),unlink,(__file))
#elif defined(__CRT_HAVE__unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_unlink,(char const *__file),(__file))
#elif defined(__CRT_HAVE___unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_unlink,(char const *__file),__unlink,(__file))
#elif defined(__CRT_HAVE___libc_unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_unlink,(char const *__file),__libc_unlink,(__file))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <libc/local/unistd/unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL _unlink)(char const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unlink))(__file); }
#else /* __AT_FDCWD && __CRT_HAVE_unlinkat */
#undef ___unlink_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_unlinkat */
#endif /* !... */
#endif /* !___unlink_defined */
#endif /* !_CRT_DIRECTORY_DEFINED */

#ifndef _STDIO_DEFINED
#define _STDIO_DEFINED 1
#ifdef __CRT_HAVE_popen
/* >> popen(3)
 * Open and return a new process I/O stream for executing `command'
 * @param: command: The command to execute (s.a. `shexec(3)')
 * @param: modes:   One of "r", "w", "re" or "we" ('e' sets  O_CLOEXEC
 *                  for the internal file descriptor within the parent
 *                  process) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,_popen,(char const *__command, char const *__modes),popen,(__command,__modes))
#elif defined(__CRT_HAVE__popen)
/* >> popen(3)
 * Open and return a new process I/O stream for executing `command'
 * @param: command: The command to execute (s.a. `shexec(3)')
 * @param: modes:   One of "r", "w", "re" or "we" ('e' sets  O_CLOEXEC
 *                  for the internal file descriptor within the parent
 *                  process) */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,_popen,(char const *__command, char const *__modes),(__command,__modes))
#elif defined(__CRT_HAVE__IO_popen)
/* >> popen(3)
 * Open and return a new process I/O stream for executing `command'
 * @param: command: The command to execute (s.a. `shexec(3)')
 * @param: modes:   One of "r", "w", "re" or "we" ('e' sets  O_CLOEXEC
 *                  for the internal file descriptor within the parent
 *                  process) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,_popen,(char const *__command, char const *__modes),_IO_popen,(__command,__modes))
#endif /* ... */
#ifdef __CRT_HAVE_pclose
/* >> pclose(3)
 * Close a process I/O file `stream' (s.a. `popen(3)') */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_pclose,(__FILE *__stream),pclose,(__stream))
#elif defined(__CRT_HAVE__pclose)
/* >> pclose(3)
 * Close a process I/O file `stream' (s.a. `popen(3)') */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_pclose,(__FILE *__stream),(__stream))
#endif /* ... */
#ifdef __CRT_HAVE__fsopen
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,_fsopen,(char const *__filename, char const *__modes, int __sflag),(__filename,__modes,__sflag))
#elif (defined(__CRT_HAVE_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || (defined(__CRT_HAVE__IO_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_fopen64)
#include <libc/local/stdio/_fsopen.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_fsopen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __FILE *__NOTHROW_RPC(__LIBCCALL _fsopen)(char const *__filename, char const *__modes, int __sflag) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fsopen))(__filename, __modes, __sflag); })
#endif /* ... */
#ifdef __CRT_HAVE_fdopen
/* >> fdopen(3)
 * Open a new file stream by inheriting a given file descriptor `fd'
 * Note   that  upon  success  (`return != NULL'),  the  given  `fd'
 * will be `close()'d once `fclose(return)' is called */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,_fdopen,(__fd_t __fd, char const *__restrict __modes),fdopen,(__fd,__modes))
#elif defined(__CRT_HAVE__fdopen)
/* >> fdopen(3)
 * Open a new file stream by inheriting a given file descriptor `fd'
 * Note   that  upon  success  (`return != NULL'),  the  given  `fd'
 * will be `close()'d once `fclose(return)' is called */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,_fdopen,(__fd_t __fd, char const *__restrict __modes),(__fd,__modes))
#elif defined(__CRT_HAVE__IO_fdopen)
/* >> fdopen(3)
 * Open a new file stream by inheriting a given file descriptor `fd'
 * Note   that  upon  success  (`return != NULL'),  the  given  `fd'
 * will be `close()'d once `fclose(return)' is called */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,_fdopen,(__fd_t __fd, char const *__restrict __modes),_IO_fdopen,(__fd,__modes))
#endif /* ... */
#if defined(__CRT_HAVE_flushall_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,int,__THROWING,_flushall,(void),flushall_unlocked,())
#elif defined(__CRT_HAVE__flushall)
__CDECLARE(,int,__THROWING,_flushall,(void),())
#elif defined(__CRT_HAVE__IO_flush_all)
__CREDIRECT(,int,__THROWING,_flushall,(void),_IO_flush_all,())
#elif defined(__CRT_HAVE_flushall_unlocked)
__CREDIRECT(,int,__THROWING,_flushall,(void),flushall_unlocked,())
#else /* ... */
#include <libc/local/stdio/_flushall.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_flushall, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL _flushall)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_flushall))(); })
#endif /* !... */
#ifdef __CRT_HAVE_fcloseall
/* >> fcloseall(3)
 * Close all opened files */
__CREDIRECT(,int,__THROWING,_fcloseall,(void),fcloseall,())
#elif defined(__CRT_HAVE__fcloseall)
/* >> fcloseall(3)
 * Close all opened files */
__CDECLARE(,int,__THROWING,_fcloseall,(void),())
#endif /* ... */
#if defined(__CRT_HAVE_fileno_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fileno(3)
 * Return the underlying file descriptor number used by `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,_fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#elif defined(__CRT_HAVE_fileno)
/* >> fileno(3)
 * Return the underlying file descriptor number used by `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,_fileno,(__FILE *__restrict __stream),fileno,(__stream))
#elif defined(__CRT_HAVE__fileno)
/* >> fileno(3)
 * Return the underlying file descriptor number used by `stream' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,_fileno,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_fileno_unlocked)
/* >> fileno(3)
 * Return the underlying file descriptor number used by `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,_fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_getchar_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> getchar(3)
 * Alias for `fgetc(stdin)' */
__CREDIRECT(,int,__THROWING,_fgetchar,(void),getchar_unlocked,())
#elif defined(__CRT_HAVE_getchar)
/* >> getchar(3)
 * Alias for `fgetc(stdin)' */
__CREDIRECT(,int,__THROWING,_fgetchar,(void),getchar,())
#elif defined(__CRT_HAVE__fgetchar)
/* >> getchar(3)
 * Alias for `fgetc(stdin)' */
__CDECLARE(,int,__THROWING,_fgetchar,(void),())
#elif defined(__LOCAL_stdin) && (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))
#include <libc/local/stdio/getchar.h>
/* >> getchar(3)
 * Alias for `fgetc(stdin)' */
__FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL _fgetchar)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar))(); }
#endif /* ... */
#if __has_builtin(__builtin_putchar) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_putchar)
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__CEIREDIRECT(,int,__THROWING,_fputchar,(int __ch),putchar,{ return __builtin_putchar(__ch); })
#elif defined(__CRT_HAVE_putchar_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__CREDIRECT(,int,__THROWING,_fputchar,(int __ch),putchar_unlocked,(__ch))
#elif defined(__CRT_HAVE_putchar)
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__CREDIRECT(,int,__THROWING,_fputchar,(int __ch),putchar,(__ch))
#elif defined(__CRT_HAVE__fputchar)
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__CDECLARE(,int,__THROWING,_fputchar,(int __ch),(__ch))
#elif defined(__CRT_HAVE_putchar_unlocked)
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__CREDIRECT(,int,__THROWING,_fputchar,(int __ch),putchar_unlocked,(__ch))
#elif defined(__LOCAL_stdout) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/stdio/putchar.h>
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL _fputchar)(int __ch) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar))(__ch); }
#endif /* ... */
#if defined(__CRT_HAVE_getw_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> getw(3)
 * Similar to `getc()', but read 2 bytes */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_getw,(__FILE *__restrict __stream),getw_unlocked,(__stream))
#elif defined(__CRT_HAVE_getw)
/* >> getw(3)
 * Similar to `getc()', but read 2 bytes */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_getw,(__FILE *__restrict __stream),getw,(__stream))
#elif defined(__CRT_HAVE__getw)
/* >> getw(3)
 * Similar to `getc()', but read 2 bytes */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,_getw,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/stdio/getw.h>
/* >> getw(3)
 * Similar to `getc()', but read 2 bytes */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL _getw)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getw))(__stream); }
#endif /* ... */
#if defined(__CRT_HAVE_putw_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> putw(3)
 * Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putw,(int __w, __FILE *__restrict __stream),putw_unlocked,(__w,__stream))
#elif defined(__CRT_HAVE_putw)
/* >> putw(3)
 * Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putw,(int __w, __FILE *__restrict __stream),putw,(__w,__stream))
#elif defined(__CRT_HAVE__putw)
/* >> putw(3)
 * Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,_putw,(int __w, __FILE *__restrict __stream),(__w,__stream))
#elif defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/putw.h>
/* >> putw(3)
 * Similar to `putc()', but write 2 bytes loaded from `W & 0xffff' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL _putw)(int __w, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putw))(__w, __stream); }
#endif /* ... */
#ifdef __CRT_HAVE_tempnam
/* >> tempnam(3) */
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,_tempnam,(char const *__dir, char const *__pfx),tempnam,(__dir,__pfx))
#elif defined(__CRT_HAVE__tempnam)
/* >> tempnam(3) */
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,_tempnam,(char const *__dir, char const *__pfx),(__dir,__pfx))
#endif /* ... */

#if defined(__CRT_HAVE_fseek_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock)
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <libc/local/stdio/fseeko64.h>
/* >> fseeko(3), fseeko64(3)
 * Change the current in-file position of `stream' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL _fseeki64)(__FILE *__restrict __stream, __off64_t __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseeko64))(__stream, __off, __whence); }
#endif /* ... */
#if defined(__CRT_HAVE_ftell_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftello64)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE_ftell64)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftell64,(__stream))
#elif defined(__CRT_HAVE__ftelli64)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_ftell_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock)
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
#include <libc/local/stdio/ftello64.h>
/* >> ftello(3), ftello64(3)
 * Return the current in-file position of `stream' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __off64_t (__LIBCCALL _ftelli64)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftello64))(__stream); }
#endif /* ... */

__CDECLARE_OPT(,int,__NOTHROW_RPC,_rmtmp,(void),())

#ifdef __CRT_HAVE__filbuf
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,_filbuf,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE___uflow)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_filbuf,(__FILE *__restrict __stream),__uflow,(__stream))
#elif defined(__CRT_HAVE___underflow)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_filbuf,(__FILE *__restrict __stream),__underflow,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE__flsbuf
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,_flsbuf,(int __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE___swbuf)
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_flsbuf,(int __ch, __FILE *__restrict __stream),__swbuf,(__ch,__stream))
#endif /* ... */

#ifdef __CRT_HAVE__getmaxstdio
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,_getmaxstdio,(void),())
#else /* __CRT_HAVE__getmaxstdio */
#include <asm/os/resource.h>
#if defined(__RLIMIT_NOFILE) && ((defined(__CRT_HAVE_getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___libc_getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE_getrlimit64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)))
#include <libc/local/stdio/_getmaxstdio.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_getmaxstdio, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _getmaxstdio)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getmaxstdio))(); })
#endif /* __RLIMIT_NOFILE && ((__CRT_HAVE_getrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___getrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___libc_getrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE_getrlimit64 && (__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__))) */
#endif /* !__CRT_HAVE__getmaxstdio */
#ifdef __CRT_HAVE__setmaxstdio
__CDECLARE(,int,__NOTHROW_NCX,_setmaxstdio,(int __newmaxval),(__newmaxval))
#else /* __CRT_HAVE__setmaxstdio */
#include <asm/os/resource.h>
#if defined(__RLIMIT_NOFILE) && ((defined(__CRT_HAVE_getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___libc_getrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE_getrlimit64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__))) && ((defined(__CRT_HAVE_setrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___setrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE___libc_setrlimit) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (defined(__CRT_HAVE_setrlimit64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)))
#include <libc/local/stdio/_setmaxstdio.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_setmaxstdio, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL _setmaxstdio)(int __newmaxval) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_setmaxstdio))(__newmaxval); })
#endif /* __RLIMIT_NOFILE && ((__CRT_HAVE_getrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___getrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___libc_getrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE_getrlimit64 && (__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__))) && ((__CRT_HAVE_setrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___setrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE___libc_setrlimit && (!__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__)) || (__CRT_HAVE_setrlimit64 && (__USE_FILE_OFFSET64 || __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__))) */
#endif /* !__CRT_HAVE__setmaxstdio */
/* >> _get_printf_count_output(3), _set_printf_count_output(3)
 * Enable or disable use of '%n' in printf-style format strings. */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_get_printf_count_output,(void),())
/* >> _get_printf_count_output(3), _set_printf_count_output(3)
 * Enable or disable use of '%n' in printf-style format strings. */
__CDECLARE_OPT(,int,__NOTHROW_NCX,_set_printf_count_output,(int __val),(__val))
__CDECLARE_OPT(__ATTR_WUNUSED,__UINT32_TYPE__,__NOTHROW_NCX,_get_output_format,(void),())
__CDECLARE_OPT(,__UINT32_TYPE__,__NOTHROW_NCX,_set_output_format,(__UINT32_TYPE__ __format),(__format))

#ifdef __USE_DOS_SLIB
#ifdef __CRT_HAVE_fopen_s
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),errno_t,__NOTHROW_RPC,fopen_s,(__FILE **__pstream, char const *__filename, char const *__modes),(__pstream,__filename,__modes))
#elif (defined(__CRT_HAVE_fopen) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_fopen64)
#include <libc/local/stdio/fopen_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fopen_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) errno_t __NOTHROW_RPC(__LIBCCALL fopen_s)(__FILE **__pstream, char const *__filename, char const *__modes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fopen_s))(__pstream, __filename, __modes); })
#endif /* ... */
#ifdef __CRT_HAVE_freopen_s
__CDECLARE(__ATTR_NONNULL((1, 2, 3, 4)),errno_t,__NOTHROW_RPC,freopen_s,(__FILE **__pstream, char const *__filename, char const *__modes, __FILE *__oldstream),(__pstream,__filename,__modes,__oldstream))
#elif (defined(__CRT_HAVE_freopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_freopen64) || (defined(__CRT_HAVE_freopen_unlocked) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_freopen64_unlocked)
#include <libc/local/stdio/freopen_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(freopen_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3, 4)) errno_t __NOTHROW_RPC(__LIBCCALL freopen_s)(__FILE **__pstream, char const *__filename, char const *__modes, __FILE *__oldstream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(freopen_s))(__pstream, __filename, __modes, __oldstream); })
#endif /* ... */
#ifdef __CRT_HAVE_tmpnam_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,tmpnam_s,(char *__restrict __buf, rsize_t __bufsize),(__buf,__bufsize))
#elif defined(__CRT_HAVE_tmpnam)
#include <libc/local/stdio/tmpnam_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(tmpnam_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL tmpnam_s)(char *__restrict __buf, rsize_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tmpnam_s))(__buf, __bufsize); })
#endif /* ... */

#ifdef __CRT_HAVE_clearerr_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,clearerr_s,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_clearerr) || defined(__CRT_HAVE_clearerr_unlocked)
#include <libc/local/stdio/clearerr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(clearerr_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL clearerr_s)(__FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(clearerr_s))(__stream); })
#endif /* ... */
#ifdef __CRT_HAVE_tmpfile_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_RPC,tmpfile_s,(__FILE **__pstream),(__pstream))
#elif (defined(__CRT_HAVE_tmpfile) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_tmpfile64)
#include <libc/local/stdio/tmpfile_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(tmpfile_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_RPC(__LIBCCALL tmpfile_s)(__FILE **__pstream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tmpfile_s))(__pstream); })
#endif /* ... */
#ifdef __CRT_HAVE_fread_s
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 5)),__SIZE_TYPE__,__NOTHROW_RPC,fread_s,(void *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),(__buf,__bufsize,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/stdio/fread_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fread_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 5)) __SIZE_TYPE__ __NOTHROW_RPC(__LIBCCALL fread_s)(void *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fread_s))(__buf, __bufsize, __elemsize, __elemcount, __stream); })
#endif /* ... */
#ifdef __CRT_HAVE_gets_s
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_RPC,gets_s,(char *__restrict __buf, rsize_t __bufsize),(__buf,__bufsize))
#elif defined(__LOCAL_stdin) && (defined(__CRT_HAVE_fgets) || defined(__CRT_HAVE__IO_fgets) || defined(__CRT_HAVE_fgets_unlocked) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))))
#include <libc/local/stdio/gets_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(gets_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_RPC(__LIBCCALL gets_s)(char *__restrict __buf, rsize_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gets_s))(__buf, __bufsize); })
#endif /* ... */
#endif /* __USE_DOS_SLIB */
#endif /* _STDIO_DEFINED */
#ifdef __CRT_HAVE_fgetc_unlocked
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fgetc_nolock,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fgetc_nolock,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getc_nolock)
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fgetc_nolock,(__FILE *__restrict __stream),_getc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock)
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,_fgetc_nolock,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fgetc_nolock,(__FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fgetc_nolock,(__FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fgetc_nolock,(__FILE *__restrict __stream),_IO_getc,(__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/stdio/fgetc_unlocked.h>
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL _fgetc_nolock)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc_unlocked))(__stream); }
#endif /* ... */
#if __has_builtin(__builtin_fputc_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc_unlocked)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CEIREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_fputc_nolock,(int __ch, __FILE *__restrict __stream),fputc_unlocked,{ return __builtin_fputc_unlocked(__ch, __stream); })
#elif defined(__CRT_HAVE_putc_unlocked)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_fputc_nolock,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_fputc_nolock,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__putc_nolock)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_fputc_nolock,(int __ch, __FILE *__restrict __stream),_putc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE__fputc_nolock)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,_fputc_nolock,(int __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_fputc_nolock,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_fputc_nolock,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_fputc_nolock,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/fputc_unlocked.h>
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL _fputc_nolock)(int __ch, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc_unlocked))(__ch, __stream); }
#endif /* ... */
#ifdef __CRT_HAVE_fgetc_unlocked
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_getc_nolock,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_getc_nolock,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getc_nolock)
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,_getc_nolock,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock)
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_getc_nolock,(__FILE *__restrict __stream),_fgetc_nolock,(__stream))
#elif defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_getc_nolock,(__FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_getc_nolock,(__FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_getc_nolock,(__FILE *__restrict __stream),_IO_getc,(__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/stdio/fgetc_unlocked.h>
/* >> fgetc_unlocked(3)
 * Same as `fgetc()', but performs I/O without acquiring a lock to `stream' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL _getc_nolock)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc_unlocked))(__stream); }
#endif /* ... */
#if __has_builtin(__builtin_fputc_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc_unlocked)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CEIREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putc_nolock,(int __ch, __FILE *__restrict __stream),fputc_unlocked,{ return __builtin_fputc_unlocked(__ch, __stream); })
#elif defined(__CRT_HAVE_putc_unlocked)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putc_nolock,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putc_nolock,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__putc_nolock)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CDECLARE(__ATTR_NONNULL((2)),int,__THROWING,_putc_nolock,(int __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE__fputc_nolock)
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putc_nolock,(int __ch, __FILE *__restrict __stream),_fputc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putc_nolock,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putc_nolock,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,_putc_nolock,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/fputc_unlocked.h>
/* >> fputc_unlocked(3)
 * Same as `fputc()', but performs I/O without acquiring a lock to `stream' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) int (__LIBCCALL _putc_nolock)(int __ch, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc_unlocked))(__ch, __stream); }
#endif /* ... */
#ifdef __CRT_HAVE_getchar_unlocked
/* >> getchar_unlocked(3)
 * Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
__CREDIRECT(,int,__THROWING,_getchar_nolock,(void),getchar_unlocked,())
#elif defined(__LOCAL_stdin) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))
#include <libc/local/stdio/getchar_unlocked.h>
/* >> getchar_unlocked(3)
 * Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
__FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL _getchar_nolock)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar_unlocked))(); }
#endif /* ... */
#if __has_builtin(__builtin_putchar_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_putchar_unlocked)
/* >> putchar_unlocked(3)
 * Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
__CEIREDIRECT(,int,__THROWING,_putchar_nolock,(int __ch),putchar_unlocked,{ return __builtin_putchar_unlocked(__ch); })
#elif defined(__CRT_HAVE_putchar_unlocked)
/* >> putchar_unlocked(3)
 * Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
__CREDIRECT(,int,__THROWING,_putchar_nolock,(int __ch),putchar_unlocked,(__ch))
#elif defined(__LOCAL_stdout) && (defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/stdio/putchar_unlocked.h>
/* >> putchar_unlocked(3)
 * Same as `putchar()', but performs I/O without acquiring a lock to `stdout' */
__FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL _putchar_nolock)(int __ch) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar_unlocked))(__ch); }
#endif /* ... */
#ifdef __CRT_HAVE_flockfile
/* >> flockfile(3)
 * Acquire a lock to `stream' and block until doing so succeeds */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,_lock_file,(__FILE *__restrict __stream),flockfile,(__stream))
#elif defined(__CRT_HAVE__lock_file)
/* >> flockfile(3)
 * Acquire a lock to `stream' and block until doing so succeeds */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,_lock_file,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__IO_flockfile)
/* >> flockfile(3)
 * Acquire a lock to `stream' and block until doing so succeeds */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,_lock_file,(__FILE *__restrict __stream),_IO_flockfile,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_funlockfile
/* >> funlockfile(3)
 * Release a previously acquired lock from `stream' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_unlock_file,(__FILE *__restrict __stream),funlockfile,(__stream))
#elif defined(__CRT_HAVE__unlock_file)
/* >> funlockfile(3)
 * Release a previously acquired lock from `stream' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_unlock_file,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__IO_funlockfile)
/* >> funlockfile(3)
 * Release a previously acquired lock from `stream' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_unlock_file,(__FILE *__restrict __stream),_IO_funlockfile,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fclose
/* >> fclose(3)
 * Close and destroy a given file `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fclose_nolock,(FILE *__restrict __stream),fclose,(__stream))
#elif defined(__CRT_HAVE__fclose_nolock)
/* >> fclose(3)
 * Close and destroy a given file `stream' */
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,_fclose_nolock,(FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__IO_fclose)
/* >> fclose(3)
 * Close and destroy a given file `stream' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fclose_nolock,(FILE *__restrict __stream),_IO_fclose,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fflush_unlocked
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(,int,__THROWING,_fflush_nolock,(__FILE *__stream),fflush_unlocked,(__stream))
#elif defined(__CRT_HAVE__fflush_nolock)
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
__CDECLARE(,int,__THROWING,_fflush_nolock,(__FILE *__stream),(__stream))
#elif defined(__CRT_HAVE_fflush)
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(,int,__THROWING,_fflush_nolock,(__FILE *__stream),fflush,(__stream))
#elif defined(__CRT_HAVE__IO_fflush)
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(,int,__THROWING,_fflush_nolock,(__FILE *__stream),_IO_fflush,(__stream))
#else /* ... */
#include <libc/local/stdio/fflush_unlocked.h>
/* >> fflush_unlocked(3)
 * Same as `fflush()', but performs I/O without acquiring a lock to `stream' */
__FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL _fflush_nolock)(__FILE *__stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fflush_unlocked))(__stream); }
#endif /* !... */
#ifdef __CRT_HAVE_fread_unlocked
/* >> fread_unlocked(3)
 * Same as `fread()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fread_nolock,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fread_nolock)
/* >> fread_unlocked(3)
 * Same as `fread()', but performs I/O without acquiring a lock to `stream' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fread_nolock,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fread)
/* >> fread_unlocked(3)
 * Same as `fread()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fread_nolock,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fread)
/* >> fread_unlocked(3)
 * Same as `fread()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fread_nolock,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow)))
#include <libc/local/stdio/fread_unlocked.h>
/* >> fread_unlocked(3)
 * Same as `fread()', but performs I/O without acquiring a lock to `stream' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 4)) __SIZE_TYPE__ (__LIBCCALL _fread_nolock)(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fread_unlocked))(__buf, __elemsize, __elemcount, __stream); }
#endif /* ... */
#ifdef __CRT_HAVE_fwrite_unlocked
/* >> fwrite_unlocked(3)
 * Same as `fwrite()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fwrite_nolock,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fwrite_nolock)
/* >> fwrite_unlocked(3)
 * Same as `fwrite()', but performs I/O without acquiring a lock to `stream' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fwrite_nolock,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fwrite)
/* >> fwrite_unlocked(3)
 * Same as `fwrite()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fwrite_nolock,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fwrite)
/* >> fwrite_unlocked(3)
 * Same as `fwrite()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fwrite_nolock,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fwrite,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fwrite_s)
/* >> fwrite_unlocked(3)
 * Same as `fwrite()', but performs I/O without acquiring a lock to `stream' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,_fwrite_nolock,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite_s,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/stdio/fwrite_unlocked.h>
/* >> fwrite_unlocked(3)
 * Same as `fwrite()', but performs I/O without acquiring a lock to `stream' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 4)) __SIZE_TYPE__ (__LIBCCALL _fwrite_nolock)(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwrite_unlocked))(__buf, __elemsize, __elemcount, __stream); }
#endif /* ... */
#ifdef __CRT_HAVE__fread_nolock_s
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 5)),__SIZE_TYPE__,__THROWING,_fread_nolock_s,(void *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),(__buf,__bufsize,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <libc/local/stdio/_fread_nolock_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_fread_nolock_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 5)) __SIZE_TYPE__ (__LIBCCALL _fread_nolock_s)(void *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fread_nolock_s))(__buf, __bufsize, __elemsize, __elemcount, __stream); })
#endif /* ... */
#ifdef __CRT_HAVE_fseek_unlocked
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock)
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),fseek64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseek_nolock,(__FILE *__restrict __stream, long int __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock)
#include <libc/local/stdio/fseek_unlocked.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL _fseek_nolock)(__FILE *__restrict __stream, long int __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseek_unlocked))(__stream, __off, __whence); }
#endif /* ... */
#ifdef __CRT_HAVE_ftell_unlocked
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftello64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE_ftell64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),ftell64,(__stream))
#elif defined(__CRT_HAVE__ftelli64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__THROWING,_ftell_nolock,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked)
#include <libc/local/stdio/ftell_unlocked.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) long int (__LIBCCALL _ftell_nolock)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftell_unlocked))(__stream); }
#endif /* ... */
#if defined(__CRT_HAVE_fseek_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64_nolock,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64_nolock,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64_nolock,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64_nolock,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64_nolock,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock)
__CDECLARE(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64_nolock,(__FILE *__restrict __stream, __off64_t __off, int __whence),(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64_nolock,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64_nolock,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64_nolock,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64_nolock,(__FILE *__restrict __stream, __off64_t __off, int __whence),fseek64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,_fseeki64_nolock,(__FILE *__restrict __stream, __off64_t __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <libc/local/stdio/fseeko64_unlocked.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int (__LIBCCALL _fseeki64_nolock)(__FILE *__restrict __stream, __off64_t __off, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fseeko64_unlocked))(__stream, __off, __whence); }
#endif /* ... */
#if defined(__CRT_HAVE_ftell_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftello64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE_ftell64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),ftell64,(__stream))
#elif defined(__CRT_HAVE__ftelli64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__off64_t,__THROWING,_ftelli64_nolock,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
#include <libc/local/stdio/ftello64_unlocked.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __off64_t (__LIBCCALL _ftelli64_nolock)(__FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftello64_unlocked))(__stream); }
#endif /* ... */
#ifdef __CRT_HAVE_ungetc_unlocked
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,_ungetc_nolock,(int __ch, __FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock)
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,_ungetc_nolock,(int __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,_ungetc_nolock,(int __ch, __FILE *__restrict __stream),ungetc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_ungetc)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,_ungetc_nolock,(int __ch, __FILE *__restrict __stream),_IO_ungetc,(__ch,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_getchar_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> getchar(3)
 * Alias for `fgetc(stdin)' */
__CREDIRECT(,int,__THROWING,fgetchar,(void),getchar_unlocked,())
#elif defined(__CRT_HAVE_getchar)
/* >> getchar(3)
 * Alias for `fgetc(stdin)' */
__CREDIRECT(,int,__THROWING,fgetchar,(void),getchar,())
#elif defined(__CRT_HAVE__fgetchar)
/* >> getchar(3)
 * Alias for `fgetc(stdin)' */
__CREDIRECT(,int,__THROWING,fgetchar,(void),_fgetchar,())
#elif defined(__LOCAL_stdin) && (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))
#include <libc/local/stdio/getchar.h>
/* >> getchar(3)
 * Alias for `fgetc(stdin)' */
__FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL fgetchar)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar))(); }
#endif /* ... */
#if __has_builtin(__builtin_putchar) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_putchar)
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__CEIREDIRECT(,int,__THROWING,fputchar,(int __ch),putchar,{ return __builtin_putchar(__ch); })
#elif defined(__CRT_HAVE_putchar_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__CREDIRECT(,int,__THROWING,fputchar,(int __ch),putchar_unlocked,(__ch))
#elif defined(__CRT_HAVE_putchar)
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__CREDIRECT(,int,__THROWING,fputchar,(int __ch),putchar,(__ch))
#elif defined(__CRT_HAVE__fputchar)
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__CREDIRECT(,int,__THROWING,fputchar,(int __ch),_fputchar,(__ch))
#elif defined(__CRT_HAVE_putchar_unlocked)
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__CREDIRECT(,int,__THROWING,fputchar,(int __ch),putchar_unlocked,(__ch))
#elif defined(__LOCAL_stdout) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/stdio/putchar.h>
/* >> putchar(3)
 * Alias for `fputc(ch, stdout)' */
__FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL fputchar)(int __ch) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar))(__ch); }
#endif /* ... */
#if defined(__CRT_HAVE_flushall_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,int,__THROWING,flushall,(void),flushall_unlocked,())
#elif defined(__CRT_HAVE__flushall)
__CREDIRECT(,int,__THROWING,flushall,(void),_flushall,())
#elif defined(__CRT_HAVE__IO_flush_all)
__CREDIRECT(,int,__THROWING,flushall,(void),_IO_flush_all,())
#elif defined(__CRT_HAVE_flushall_unlocked)
__CREDIRECT(,int,__THROWING,flushall,(void),flushall_unlocked,())
#else /* ... */
#include <libc/local/stdio/_flushall.h>
__FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL flushall)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_flushall))(); }
#endif /* !... */
#ifdef __CRT_HAVE__rmtmp
__CREDIRECT(,int,__NOTHROW_RPC,rmtmp,(void),_rmtmp,())
#endif /* __CRT_HAVE__rmtmp */
#define SYS_OPEN     _SYS_OPEN

#ifdef __CRT_HAVE___stdio_common_vfprintf
__CDECLARE(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((2, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__stdio_common_vfprintf,(__UINT64_TYPE__ __options, __FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/__stdio_common_vfprintf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__stdio_common_vfprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((2, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __stdio_common_vfprintf)(__UINT64_TYPE__ __options, __FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__stdio_common_vfprintf))(__options, __stream, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE___stdio_common_vfprintf_s
__CDECLARE(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((2, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__stdio_common_vfprintf_s,(__UINT64_TYPE__ __options, __FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/__stdio_common_vfprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__stdio_common_vfprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((2, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __stdio_common_vfprintf_s)(__UINT64_TYPE__ __options, __FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__stdio_common_vfprintf_s))(__options, __stream, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE___stdio_common_vfprintf_p
__CDECLARE(__ATTR_LIBC_PRINTF_P(3, 0) __ATTR_NONNULL((2, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__stdio_common_vfprintf_p,(__UINT64_TYPE__ __options, __FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/__stdio_common_vfprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__stdio_common_vfprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(3, 0) __ATTR_NONNULL((2, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __stdio_common_vfprintf_p)(__UINT64_TYPE__ __options, __FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__stdio_common_vfprintf_p))(__options, __stream, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE___stdio_common_vsprintf
__CDECLARE(__ATTR_LIBC_PRINTF(4, 0) __ATTR_NONNULL((4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__stdio_common_vsprintf,(__UINT64_TYPE__ __options, char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__buf,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE___stdio_common_vsprintf */
#include <libc/local/stdio/__stdio_common_vsprintf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__stdio_common_vsprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(4, 0) __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __stdio_common_vsprintf)(__UINT64_TYPE__ __options, char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__stdio_common_vsprintf))(__options, __buf, __bufsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE___stdio_common_vsprintf */
#ifdef __CRT_HAVE___stdio_common_vsprintf_s
__CDECLARE(__ATTR_LIBC_PRINTF(4, 0) __ATTR_NONNULL((4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__stdio_common_vsprintf_s,(__UINT64_TYPE__ __options, char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__buf,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE___stdio_common_vsprintf_s */
#include <libc/local/stdio/__stdio_common_vsprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__stdio_common_vsprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(4, 0) __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __stdio_common_vsprintf_s)(__UINT64_TYPE__ __options, char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__stdio_common_vsprintf_s))(__options, __buf, __bufsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE___stdio_common_vsprintf_s */
#ifdef __CRT_HAVE___stdio_common_vsnprintf_s
__CDECLARE(__ATTR_LIBC_PRINTF(5, 0) __ATTR_NONNULL((5)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__stdio_common_vsnprintf_s,(__UINT64_TYPE__ __options, char *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __maxsize, char const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__buf,__bufsize,__maxsize,__format,__locale,__args))
#else /* __CRT_HAVE___stdio_common_vsnprintf_s */
#include <libc/local/stdio/__stdio_common_vsnprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__stdio_common_vsnprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(5, 0) __ATTR_NONNULL((5)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __stdio_common_vsnprintf_s)(__UINT64_TYPE__ __options, char *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __maxsize, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__stdio_common_vsnprintf_s))(__options, __buf, __bufsize, __maxsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE___stdio_common_vsnprintf_s */
#ifdef __CRT_HAVE___stdio_common_vsprintf_p
__CDECLARE(__ATTR_LIBC_PRINTF_P(4, 0) __ATTR_NONNULL((4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__stdio_common_vsprintf_p,(__UINT64_TYPE__ __options, char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__buf,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE___stdio_common_vsprintf_p */
#include <libc/local/stdio/__stdio_common_vsprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__stdio_common_vsprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(4, 0) __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __stdio_common_vsprintf_p)(__UINT64_TYPE__ __options, char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__stdio_common_vsprintf_p))(__options, __buf, __bufsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE___stdio_common_vsprintf_p */
#ifdef __CRT_HAVE___stdio_common_vfscanf
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(3, 0) __ATTR_NONNULL((2, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__stdio_common_vfscanf,(__UINT64_TYPE__ __options, __FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <libc/local/stdio/__stdio_common_vfscanf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__stdio_common_vfscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(3, 0) __ATTR_NONNULL((2, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __stdio_common_vfscanf)(__UINT64_TYPE__ __options, __FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__stdio_common_vfscanf))(__options, __stream, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE___stdio_common_vsscanf
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(4, 0) __ATTR_NONNULL((4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__stdio_common_vsscanf,(__UINT64_TYPE__ __options, char const *__input, __SIZE_TYPE__ __inputsize, char const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__input,__inputsize,__format,__locale,__args))
#else /* __CRT_HAVE___stdio_common_vsscanf */
#include <libc/local/stdio/__stdio_common_vsscanf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__stdio_common_vsscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(4, 0) __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __stdio_common_vsscanf)(__UINT64_TYPE__ __options, char const *__input, __SIZE_TYPE__ __inputsize, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__stdio_common_vsscanf))(__options, __input, __inputsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE___stdio_common_vsscanf */
#ifdef __CRT_HAVE__vsnprintf_l
__CDECLARE(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsnprintf_l,(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args),(__buf,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE__vsnprintf_l */
#include <libc/local/stdio/_vsnprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsnprintf_l)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnprintf_l))(__buf, __bufsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vsnprintf_l */
#ifdef __CRT_HAVE__vsprintf_s_l
__CDECLARE(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsprintf_s_l,(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args),(__buf,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE__vsprintf_s_l */
#include <libc/local/stdio/_vsprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsprintf_s_l)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsprintf_s_l))(__buf, __bufsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vsprintf_s_l */
#ifdef __CRT_HAVE__vsprintf_p_l
__CDECLARE(__ATTR_LIBC_PRINTF_P(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsprintf_p_l,(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args),(__buf,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE__vsprintf_p_l */
#include <libc/local/stdio/_vsprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsprintf_p_l)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsprintf_p_l))(__buf, __bufsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vsprintf_p_l */
#ifdef __CRT_HAVE__vscprintf_l
__CDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscprintf_l,(char const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#else /* __CRT_HAVE__vscprintf_l */
#include <libc/local/stdio/_vscprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscprintf_l)(char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscprintf_l))(__format, __locale, __args); })
#endif /* !__CRT_HAVE__vscprintf_l */
#ifdef __CRT_HAVE__vscprintf_p_l
__CDECLARE(__ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscprintf_p_l,(char const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#else /* __CRT_HAVE__vscprintf_p_l */
#include <libc/local/stdio/_vscprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscprintf_p_l)(char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscprintf_p_l))(__format, __locale, __args); })
#endif /* !__CRT_HAVE__vscprintf_p_l */
#ifdef __CRT_HAVE__vsnprintf_c_l
__CDECLARE(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsnprintf_c_l,(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args),(__buf,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE__vsnprintf_c_l */
#include <libc/local/stdio/_vsnprintf_c_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnprintf_c_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsnprintf_c_l)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnprintf_c_l))(__buf, __bufsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vsnprintf_c_l */
#ifdef __CRT_HAVE__vsnprintf_s_l
__CDECLARE(__ATTR_LIBC_PRINTF(4, 0) __ATTR_NONNULL((4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsnprintf_s_l,(char *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __maxsize, char const *__format, __locale_t __locale, __builtin_va_list __args),(__buf,__bufsize,__maxsize,__format,__locale,__args))
#else /* __CRT_HAVE__vsnprintf_s_l */
#include <libc/local/stdio/_vsnprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(4, 0) __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsnprintf_s_l)(char *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __maxsize, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnprintf_s_l))(__buf, __bufsize, __maxsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vsnprintf_s_l */
#ifdef __CRT_HAVE__vfprintf_s_l
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vfprintf_s_l,(__FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE___stdio_common_vfprintf_s) || defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/_vfprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vfprintf_s_l)(__FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfprintf_s_l))(__stream, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vfprintf_p_l
__CDECLARE(__ATTR_LIBC_PRINTF_P(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vfprintf_p_l,(__FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE___stdio_common_vfprintf_p) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/_vfprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vfprintf_p_l)(__FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfprintf_p_l))(__stream, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vfscanf_l
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vfscanf_l,(__FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <libc/local/stdio/_vfscanf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vfscanf_l)(__FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfscanf_l))(__stream, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vfscanf_s_l
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vfscanf_s_l,(__FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <libc/local/stdio/_vfscanf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfscanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vfscanf_s_l)(__FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfscanf_s_l))(__stream, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vprintf_l
__CDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vprintf_l,(char const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/stdio/_vprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vprintf_l)(char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vprintf_l))(__format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vfprintf_l
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vfprintf_l,(__FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/_vfprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vfprintf_l)(__FILE *__stream, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfprintf_l))(__stream, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vscanf_l
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscanf_l,(char const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf) || defined(__CRT_HAVE_vscanf_unlocked) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
#include <libc/local/stdio/_vscanf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscanf_l)(char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscanf_l))(__format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vsprintf_l
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsprintf_l,(char *__buf, char const *__format, __locale_t __locale, __builtin_va_list __args),(__buf,__format,__locale,__args))
#else /* __CRT_HAVE__vsprintf_l */
#include <libc/local/stdio/_vsprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsprintf_l)(char *__buf, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsprintf_l))(__buf, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vsprintf_l */
#ifdef __CRT_HAVE__vfprintf_p
__CDECLARE(__ATTR_LIBC_PRINTF_P(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vfprintf_p,(__FILE *__stream, char const *__format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE__vfprintf_p_l) || defined(__CRT_HAVE___stdio_common_vfprintf_p) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/_vfprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vfprintf_p)(__FILE *__stream, char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfprintf_p))(__stream, __format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vprintf_p
__CDECLARE(__ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vprintf_p,(char const *__format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE__vprintf_p_l) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE__vfprintf_p_l) || defined(__CRT_HAVE___stdio_common_vfprintf_p) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/stdio/_vprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vprintf_p)(char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vprintf_p))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vsnprintf
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
__CDECLARE(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsnprintf,(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __builtin_va_list __args),(__buf,__bufsize,__format,__args))
#else /* __CRT_HAVE__vsnprintf */
#include <libc/local/stdio/_vsnprintf.h>
/* WARNING: This function returns the number of written character. - Not the required buffer size! */
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsnprintf)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnprintf))(__buf, __bufsize, __format, __args); })
#endif /* !__CRT_HAVE__vsnprintf */
#ifdef __CRT_HAVE__vsprintf_p
__CDECLARE(__ATTR_LIBC_PRINTF_P(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsprintf_p,(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __builtin_va_list __args),(__buf,__bufsize,__format,__args))
#else /* __CRT_HAVE__vsprintf_p */
#include <libc/local/stdio/_vsprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsprintf_p)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsprintf_p))(__buf, __bufsize, __format, __args); })
#endif /* !__CRT_HAVE__vsprintf_p */
#ifdef __CRT_HAVE__vsnprintf_s
__CDECLARE(__ATTR_LIBC_PRINTF(4, 0) __ATTR_NONNULL((4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsnprintf_s,(char *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __maxsize, char const *__format, __builtin_va_list __args),(__buf,__bufsize,__maxsize,__format,__args))
#else /* __CRT_HAVE__vsnprintf_s */
#include <libc/local/stdio/_vsnprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(4, 0) __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsnprintf_s)(char *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __maxsize, char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnprintf_s))(__buf, __bufsize, __maxsize, __format, __args); })
#endif /* !__CRT_HAVE__vsnprintf_s */
#ifdef __CRT_HAVE__vscprintf
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscprintf,(char const *__format, __builtin_va_list __args),(__format,__args))
#else /* __CRT_HAVE__vscprintf */
#include <libc/local/stdio/_vscprintf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscprintf)(char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscprintf))(__format, __args); })
#endif /* !__CRT_HAVE__vscprintf */
#ifdef __CRT_HAVE__vscprintf_p
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscprintf_p,(char const *__format, __builtin_va_list __args),(__format,__args))
#else /* __CRT_HAVE__vscprintf_p */
#include <libc/local/stdio/_vscprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscprintf_p)(char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscprintf_p))(__format, __args); })
#endif /* !__CRT_HAVE__vscprintf_p */
#ifdef __CRT_HAVE__vsnprintf_c
__CDECLARE(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsnprintf_c,(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __builtin_va_list __args),(__buf,__bufsize,__format,__args))
#else /* __CRT_HAVE__vsnprintf_c */
#include <libc/local/stdio/_vsnprintf_c.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnprintf_c, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsnprintf_c)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnprintf_c))(__buf, __bufsize, __format, __args); })
#endif /* !__CRT_HAVE__vsnprintf_c */
#ifdef __CRT_HAVE__vsscanf_l
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsscanf_l,(char const *__buf, char const *__format, __locale_t __locale, __builtin_va_list __args),(__buf,__format,__locale,__args))
#else /* __CRT_HAVE__vsscanf_l */
#include <libc/local/stdio/_vsscanf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsscanf_l)(char const *__buf, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsscanf_l))(__buf, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vsscanf_l */
#ifdef __CRT_HAVE__vsscanf_s_l
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsscanf_s_l,(char const *__buf, char const *__format, __locale_t __locale, __builtin_va_list __args),(__buf,__format,__locale,__args))
#else /* __CRT_HAVE__vsscanf_s_l */
#include <libc/local/stdio/_vsscanf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsscanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsscanf_s_l)(char const *__buf, char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsscanf_s_l))(__buf, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vsscanf_s_l */
#ifdef __CRT_HAVE__vprintf_s_l
__CDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vprintf_s_l,(char const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__LOCAL_stdout) && (defined(__CRT_HAVE__vfprintf_s_l) || defined(__CRT_HAVE___stdio_common_vfprintf_s) || defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/stdio/_vprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vprintf_s_l)(char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vprintf_s_l))(__format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vprintf_p_l
__CDECLARE(__ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vprintf_p_l,(char const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__LOCAL_stdout) && (defined(__CRT_HAVE__vfprintf_p_l) || defined(__CRT_HAVE___stdio_common_vfprintf_p) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/stdio/_vprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vprintf_p_l)(char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vprintf_p_l))(__format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vscanf_s_l
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscanf_s_l,(char const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__LOCAL_stdin) && (defined(__CRT_HAVE__vfscanf_s_l) || defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))))
#include <libc/local/stdio/_vscanf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscanf_s_l)(char const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscanf_s_l))(__format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__fprintf_l
__LIBC __ATTR_LIBC_PRINTF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _fprintf_l)(__FILE *__stream, char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_fprintf_l");
#elif defined(__CRT_HAVE__vfprintf_l) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/_fprintf_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_fprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _fprintf_l)(__FILE *__stream, char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fprintf_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _fprintf_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fprintf_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__fprintf_s_l
__LIBC __ATTR_LIBC_PRINTF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _fprintf_s_l)(__FILE *__stream, char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_fprintf_s_l");
#elif defined(__CRT_HAVE__vfprintf_s_l) || defined(__CRT_HAVE___stdio_common_vfprintf_s) || defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/_fprintf_s_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_fprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _fprintf_s_l)(__FILE *__stream, char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fprintf_s_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _fprintf_s_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fprintf_s_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__fprintf_p
__LIBC __ATTR_LIBC_PRINTF_P(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _fprintf_p)(__FILE *__stream, char const *__format, ...) __CASMNAME_SAME("_fprintf_p");
#elif defined(__CRT_HAVE__vfprintf_p) || defined(__CRT_HAVE__vfprintf_p_l) || defined(__CRT_HAVE___stdio_common_vfprintf_p) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/_fprintf_p.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_fprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _fprintf_p)(__FILE *__stream, char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fprintf_p))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _fprintf_p(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fprintf_p))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__fprintf_p_l
__LIBC __ATTR_LIBC_PRINTF_P(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _fprintf_p_l)(__FILE *__stream, char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_fprintf_p_l");
#elif defined(__CRT_HAVE__vfprintf_p_l) || defined(__CRT_HAVE___stdio_common_vfprintf_p) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/_fprintf_p_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_fprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _fprintf_p_l)(__FILE *__stream, char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fprintf_p_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _fprintf_p_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fprintf_p_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__printf_l
__LIBC __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _printf_l)(char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_printf_l");
#elif defined(__CRT_HAVE__vprintf_l) || defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/stdio/_printf_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_printf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _printf_l)(char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_printf_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _printf_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_printf_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__printf_s_l
__LIBC __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _printf_s_l)(char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_printf_s_l");
#elif defined(__CRT_HAVE__vprintf_s_l) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE__vfprintf_s_l) || defined(__CRT_HAVE___stdio_common_vfprintf_s) || defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/stdio/_printf_s_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_printf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _printf_s_l)(char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_printf_s_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _printf_s_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_printf_s_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__printf_p
__LIBC __ATTR_LIBC_PRINTF_P(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _printf_p)(char const *__format, ...) __CASMNAME_SAME("_printf_p");
#elif defined(__CRT_HAVE__vprintf_p) || defined(__CRT_HAVE__vprintf_p_l) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE__vfprintf_p_l) || defined(__CRT_HAVE___stdio_common_vfprintf_p) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/stdio/_printf_p.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_printf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _printf_p)(char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_printf_p))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _printf_p(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_printf_p))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__printf_p_l
__LIBC __ATTR_LIBC_PRINTF_P(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _printf_p_l)(char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_printf_p_l");
#elif defined(__CRT_HAVE__vprintf_p_l) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE__vfprintf_p_l) || defined(__CRT_HAVE___stdio_common_vfprintf_p) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/stdio/_printf_p_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_printf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _printf_p_l)(char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_printf_p_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _printf_p_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_printf_p_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__sprintf_l
__LIBC __ATTR_LIBC_PRINTF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _sprintf_l)(char *__buf, char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_sprintf_l");
#else /* __CRT_HAVE__sprintf_l */
#include <libc/local/stdio/_sprintf_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_sprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _sprintf_l)(char *__buf, char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sprintf_l))(__buf, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _sprintf_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sprintf_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__sprintf_l */
#ifdef __CRT_HAVE__sprintf_s_l
__LIBC __ATTR_LIBC_PRINTF(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _sprintf_s_l)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_sprintf_s_l");
#else /* __CRT_HAVE__sprintf_s_l */
#include <libc/local/stdio/_sprintf_s_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_sprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _sprintf_s_l)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sprintf_s_l))(__buf, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _sprintf_s_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sprintf_s_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__sprintf_s_l */
#ifdef __CRT_HAVE__sprintf_p_l
__LIBC __ATTR_LIBC_PRINTF_P(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _sprintf_p_l)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_sprintf_p_l");
#else /* __CRT_HAVE__sprintf_p_l */
#include <libc/local/stdio/_sprintf_p_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_sprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _sprintf_p_l)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sprintf_p_l))(__buf, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _sprintf_p_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sprintf_p_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__sprintf_p_l */
#ifdef __CRT_HAVE__sprintf_p
__LIBC __ATTR_LIBC_PRINTF_P(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _sprintf_p)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, ...) __CASMNAME_SAME("_sprintf_p");
#else /* __CRT_HAVE__sprintf_p */
#include <libc/local/stdio/_sprintf_p.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_sprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _sprintf_p)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sprintf_p))(__buf, __bufsize, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _sprintf_p(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sprintf_p))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__sprintf_p */
#ifdef __CRT_HAVE__snprintf_l
__LIBC __ATTR_LIBC_PRINTF(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_l)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snprintf_l");
#else /* __CRT_HAVE__snprintf_l */
#include <libc/local/stdio/_snprintf_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_snprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_l)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_l))(__buf, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _snprintf_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__snprintf_l */
#ifdef __CRT_HAVE__snprintf
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, ...) __CASMNAME_SAME("_snprintf");
#else /* __CRT_HAVE__snprintf */
#include <libc/local/stdio/_snprintf.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_snprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf))(__buf, __bufsize, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _snprintf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__snprintf */
#ifdef __CRT_HAVE__snprintf_c_l
__LIBC __ATTR_LIBC_PRINTF(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_c_l)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snprintf_c_l");
#else /* __CRT_HAVE__snprintf_c_l */
#include <libc/local/stdio/_snprintf_c_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_snprintf_c_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_c_l)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_c_l))(__buf, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _snprintf_c_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_c_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__snprintf_c_l */
#ifdef __CRT_HAVE__snprintf_c
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_c)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, ...) __CASMNAME_SAME("_snprintf_c");
#else /* __CRT_HAVE__snprintf_c */
#include <libc/local/stdio/_snprintf_c.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_snprintf_c, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_c)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_c))(__buf, __bufsize, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _snprintf_c(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_c))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__snprintf_c */
#ifdef __CRT_HAVE__snprintf_s_l
__LIBC __ATTR_LIBC_PRINTF(4, 6) __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_s_l)(char *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __maxsize, char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snprintf_s_l");
#else /* __CRT_HAVE__snprintf_s_l */
#include <libc/local/stdio/_snprintf_s_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_snprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(4, 6) __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_s_l)(char *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __maxsize, char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_s_l))(__buf, __bufsize, __maxsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _snprintf_s_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_s_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__snprintf_s_l */
#ifdef __CRT_HAVE__snprintf_s
__LIBC __ATTR_LIBC_PRINTF(4, 5) __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_s)(char *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __maxsize, char const *__format, ...) __CASMNAME_SAME("_snprintf_s");
#else /* __CRT_HAVE__snprintf_s */
#include <libc/local/stdio/_snprintf_s.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_snprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(4, 5) __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snprintf_s)(char *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __maxsize, char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_s))(__buf, __bufsize, __maxsize, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _snprintf_s(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snprintf_s))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__snprintf_s */
#ifdef __CRT_HAVE__scprintf_l
__LIBC __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scprintf_l)(char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_scprintf_l");
#else /* __CRT_HAVE__scprintf_l */
#include <libc/local/stdio/_scprintf_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_scprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scprintf_l)(char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scprintf_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _scprintf_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scprintf_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__scprintf_l */
#ifdef __CRT_HAVE__scprintf
__LIBC __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scprintf)(char const *__format, ...) __CASMNAME_SAME("_scprintf");
#else /* __CRT_HAVE__scprintf */
#include <libc/local/stdio/_scprintf.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_scprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scprintf)(char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scprintf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _scprintf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scprintf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__scprintf */
#ifdef __CRT_HAVE__scprintf_p_l
__LIBC __ATTR_LIBC_PRINTF_P(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scprintf_p_l)(char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_scprintf_p_l");
#else /* __CRT_HAVE__scprintf_p_l */
#include <libc/local/stdio/_scprintf_p_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_scprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF_P(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scprintf_p_l)(char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scprintf_p_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _scprintf_p_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scprintf_p_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__scprintf_p_l */
#ifdef __CRT_HAVE__scprintf_p
__LIBC __ATTR_WUNUSED __ATTR_LIBC_PRINTF_P(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scprintf_p)(char const *__format, ...) __CASMNAME_SAME("_scprintf_p");
#else /* __CRT_HAVE__scprintf_p */
#include <libc/local/stdio/_scprintf_p.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_scprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_PRINTF_P(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scprintf_p)(char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scprintf_p))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _scprintf_p(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scprintf_p))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__scprintf_p */
#ifdef __CRT_HAVE__fscanf_l
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _fscanf_l)(__FILE *__stream, char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_fscanf_l");
#elif defined(__CRT_HAVE__vfscanf_l) || defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <libc/local/stdio/_fscanf_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_fscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _fscanf_l)(__FILE *__stream, char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fscanf_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _fscanf_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fscanf_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__fscanf_s_l
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _fscanf_s_l)(__FILE *__stream, char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_fscanf_s_l");
#elif defined(__CRT_HAVE__vfscanf_s_l) || defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <libc/local/stdio/_fscanf_s_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_fscanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _fscanf_s_l)(__FILE *__stream, char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fscanf_s_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _fscanf_s_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fscanf_s_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__scanf_l
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scanf_l)(char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_scanf_l");
#elif defined(__CRT_HAVE__vscanf_l) || defined(__CRT_HAVE_vscanf) || defined(__CRT_HAVE__vscanf) || defined(__CRT_HAVE_vscanf_unlocked) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
#include <libc/local/stdio/_scanf_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_scanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scanf_l)(char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scanf_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _scanf_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scanf_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__scanf_s_l
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scanf_s_l)(char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_scanf_s_l");
#elif defined(__CRT_HAVE__vscanf_s_l) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE__vfscanf_s_l) || defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
#include <libc/local/stdio/_scanf_s_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_scanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 3) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scanf_s_l)(char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scanf_s_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _scanf_s_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scanf_s_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__sscanf_l
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _sscanf_l)(char const *__buf, char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_sscanf_l");
#else /* __CRT_HAVE__sscanf_l */
#include <libc/local/stdio/_sscanf_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_sscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _sscanf_l)(char const *__buf, char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sscanf_l))(__buf, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _sscanf_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sscanf_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__sscanf_l */
#ifdef __CRT_HAVE__sscanf_s_l
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _sscanf_s_l)(char const *__buf, char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_sscanf_s_l");
#else /* __CRT_HAVE__sscanf_s_l */
#include <libc/local/stdio/_sscanf_s_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_sscanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 4) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _sscanf_s_l)(char const *__buf, char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sscanf_s_l))(__buf, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _sscanf_s_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_sscanf_s_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__sscanf_s_l */
#ifdef __CRT_HAVE__snscanf_l
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf_l)(char const *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snscanf_l");
#else /* __CRT_HAVE__snscanf_l */
#include <libc/local/stdio/_snscanf_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_snscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf_l)(char const *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snscanf_l))(__buf, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _snscanf_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snscanf_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__snscanf_l */
#ifdef __CRT_HAVE__snscanf
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf)(char const *__buf, __SIZE_TYPE__ __bufsize, char const *__format, ...) __CASMNAME_SAME("_snscanf");
#else /* __CRT_HAVE__snscanf */
#include <libc/local/stdio/_snscanf.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_snscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf)(char const *__buf, __SIZE_TYPE__ __bufsize, char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snscanf))(__buf, __bufsize, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _snscanf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snscanf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__snscanf */
#ifdef __CRT_HAVE__snscanf_s_l
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf_s_l)(char const *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snscanf_s_l");
#else /* __CRT_HAVE__snscanf_s_l */
#include <libc/local/stdio/_snscanf_s_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_snscanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(3, 5) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf_s_l)(char const *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snscanf_s_l))(__buf, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _snscanf_s_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snscanf_s_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__snscanf_s_l */
#ifdef __CRT_HAVE__snscanf_s
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf_s)(char const *__buf, __SIZE_TYPE__ __bufsize, char const *__format, ...) __CASMNAME_SAME("_snscanf_s");
#else /* __CRT_HAVE__snscanf_s */
#include <libc/local/stdio/_snscanf_s.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_snscanf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snscanf_s)(char const *__buf, __SIZE_TYPE__ __bufsize, char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snscanf_s))(__buf, __bufsize, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _snscanf_s(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snscanf_s))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE__snscanf_s */
#ifdef __USE_DOS_SLIB
#ifdef __CRT_HAVE_vfprintf_s
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vfprintf_s,(__FILE *__stream, char const *__format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE__vfprintf_s_l) || defined(__CRT_HAVE___stdio_common_vfprintf_s) || defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/vfprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vfprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL vfprintf_s)(__FILE *__stream, char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfprintf_s))(__stream, __format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_vprintf_s
__CDECLARE(__ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vprintf_s,(char const *__format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE__vprintf_s_l) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE__vfprintf_s_l) || defined(__CRT_HAVE___stdio_common_vfprintf_s) || defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/stdio/vprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL vprintf_s)(char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vprintf_s))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_vsprintf_s
__CDECLARE(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vsprintf_s,(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __builtin_va_list __args),(__buf,__bufsize,__format,__args))
#else /* __CRT_HAVE_vsprintf_s */
#include <libc/local/stdio/vsprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vsprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL vsprintf_s)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsprintf_s))(__buf, __bufsize, __format, __args); })
#endif /* !__CRT_HAVE_vsprintf_s */
#ifdef __CRT_HAVE_vsnprintf_s
__CDECLARE(__ATTR_LIBC_PRINTF(4, 0) __ATTR_NONNULL((4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vsnprintf_s,(char *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __maxsize, char const *__format, __builtin_va_list __args),(__buf,__bufsize,__maxsize,__format,__args))
#else /* __CRT_HAVE_vsnprintf_s */
#include <libc/local/stdio/vsnprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vsnprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(4, 0) __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL vsnprintf_s)(char *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __maxsize, char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsnprintf_s))(__buf, __bufsize, __maxsize, __format, __args); })
#endif /* !__CRT_HAVE_vsnprintf_s */
#ifdef __CRT_HAVE_vfscanf_s
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vfscanf_s,(__FILE *__stream, char const *__format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE__vfscanf_s_l) || defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <libc/local/stdio/vfscanf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vfscanf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL vfscanf_s)(__FILE *__stream, char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfscanf_s))(__stream, __format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_vscanf_s
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vscanf_s,(char const *__format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE__vscanf_s_l) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE__vfscanf_s_l) || defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
#include <libc/local/stdio/vscanf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vscanf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL vscanf_s)(char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vscanf_s))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_vsscanf_s
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vsscanf_s,(char const *__buf, char const *__format, __builtin_va_list __args),(__buf,__format,__args))
#else /* __CRT_HAVE_vsscanf_s */
#include <libc/local/stdio/vsscanf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vsscanf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL vsscanf_s)(char const *__buf, char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsscanf_s))(__buf, __format, __args); })
#endif /* !__CRT_HAVE_vsscanf_s */
#ifdef __CRT_HAVE_fprintf_s
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL fprintf_s)(__FILE *__stream, char const *__format, ...) __CASMNAME_SAME("fprintf_s");
#elif defined(__CRT_HAVE__vfprintf_s_l) || defined(__CRT_HAVE___stdio_common_vfprintf_s) || defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/stdio/fprintf_s.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(fprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL fprintf_s)(__FILE *__stream, char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fprintf_s))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define fprintf_s(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fprintf_s))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE_printf_s
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL printf_s)(char const *__format, ...) __CASMNAME_SAME("printf_s");
#elif defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE__vprintf_s_l) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE__vfprintf_s_l) || defined(__CRT_HAVE___stdio_common_vfprintf_s) || defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#include <libc/local/stdio/printf_s.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(printf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL printf_s)(char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(printf_s))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define printf_s(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(printf_s))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE_sprintf_s
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL sprintf_s)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, ...) __CASMNAME_SAME("sprintf_s");
#else /* __CRT_HAVE_sprintf_s */
#include <libc/local/stdio/sprintf_s.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(sprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL sprintf_s)(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sprintf_s))(__buf, __bufsize, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define sprintf_s(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sprintf_s))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE_sprintf_s */
#ifdef __CRT_HAVE_fscanf_s
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL fscanf_s)(__FILE *__stream, char const *__format, ...) __CASMNAME_SAME("fscanf_s");
#elif defined(__CRT_HAVE_vfscanf_s) || defined(__CRT_HAVE__vfscanf_s_l) || defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <libc/local/stdio/fscanf_s.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(fscanf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL fscanf_s)(__FILE *__stream, char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fscanf_s))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define fscanf_s(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fscanf_s))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE_scanf_s
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL scanf_s)(char const *__format, ...) __CASMNAME_SAME("scanf_s");
#elif defined(__CRT_HAVE_vscanf_s) || defined(__CRT_HAVE__vscanf_s_l) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE__vfscanf_s_l) || defined(__CRT_HAVE___stdio_common_vfscanf) || defined(__CRT_HAVE_vfscanf) || defined(__CRT_HAVE__vfscanf) || defined(__CRT_HAVE__vfscanf_s) || defined(__CRT_HAVE__IO_vfscanf) || defined(__CRT_HAVE_vfscanf_unlocked) || defined(__CRT_HAVE___vfscanf) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
#include <libc/local/stdio/scanf_s.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(scanf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL scanf_s)(char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scanf_s))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define scanf_s(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scanf_s))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE_sscanf_s
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL sscanf_s)(char const *__buf, char const *__format, ...) __CASMNAME_SAME("sscanf_s");
#else /* __CRT_HAVE_sscanf_s */
#include <libc/local/stdio/sscanf_s.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(sscanf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL sscanf_s)(char const *__buf, char const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sscanf_s))(__buf, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define sscanf_s(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sscanf_s))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE_sscanf_s */
#endif /* __USE_DOS_SLIB */
#endif /* __CC__ */
#endif /* __USE_DOS */


__SYSDECL_END

#if defined(__USE_DOS) && !defined(__USE_DOS_CLEAN)
#include <corecrt_wstdio.h> /* Include <wchar.h> instead */
#endif /* __USE_DOS && !__USE_DOS_CLEAN */

#if ((defined(__USE_XOPEN) && !defined(__USE_XOPEN2K) && !defined(__USE_GNU)) || defined(__USE_SOLARIS))
#include <getopt.h>
#endif /* (__USE_XOPEN && !__USE_XOPEN2K && !__USE_GNU) || __USE_SOLARIS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STDIO_H)
#include <parts/uchar/stdio.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_STDIO_H */
#endif /* __USE_UTF */

#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_STDIO_H)
#include <parts/wchar/stdio.h>
#endif /* _WCHAR_H && !_PARTS_WCHAR_STDIO_H */
#endif /* __USE_KOS */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CSTDIO
#undef _STDIO_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CSTDIO */
#endif /* !_STDIO_H */
