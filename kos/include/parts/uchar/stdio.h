/* HASH CRC-32:0x86b31341 */
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
#ifndef _PARTS_UCHAR_STDIO_H
#define _PARTS_UCHAR_STDIO_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <kos/anno.h>
#ifndef _STDIO_H
#include <stdio.h>
#endif /* !_STDIO_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

#ifndef WEOF16
#define WEOF16 __WEOF16
#define WEOF32 __WEOF32
#endif /* !WEOF16 */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __wint16_t_defined
#define __wint16_t_defined
typedef __WINT16_TYPE__ wint16_t;
typedef __WINT32_TYPE__ wint32_t;
#endif /* !__wint16_t_defined */

#if defined(__CRT_HAVE_getwchar) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> getwchar(3) */
__CREDIRECT(,wint16_t,__THROWING,getchar16,(void),getwchar,())
#elif defined(__CRT_HAVE_DOS$getwchar)
/* >> getwchar(3) */
__CREDIRECT_DOS(,wint16_t,__THROWING,getchar16,(void),getwchar,())
#elif defined(__CRT_HAVE__fgetwchar) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> getwchar(3) */
__CREDIRECT(,wint16_t,__THROWING,getchar16,(void),_fgetwchar,())
#elif defined(__CRT_HAVE_DOS$_fgetwchar)
/* >> getwchar(3) */
__CREDIRECT_DOS(,wint16_t,__THROWING,getchar16,(void),_fgetwchar,())
#else /* ... */
#include <__crt.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/getwchar.h>
/* >> getwchar(3) */
__FORCELOCAL __ATTR_ARTIFICIAL wint16_t (__LIBDCALL getchar16)(void) __THROWS(...) { return (__WINT16_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar))(); }
#elif !defined(__NO_STDSTREAMS) && ((defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fgetwc) || (defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$getwc))
#include <libc/local/parts.uchar.stdio/getchar16.h>
/* >> getwchar(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getchar16, __FORCELOCAL __ATTR_ARTIFICIAL wint16_t (__LIBDCALL getchar16)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar16))(); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_getwchar) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> getwchar(3) */
__CREDIRECT(,wint32_t,__THROWING,getchar32,(void),getwchar,())
#elif defined(__CRT_HAVE_KOS$getwchar)
/* >> getwchar(3) */
__CREDIRECT_KOS(,wint32_t,__THROWING,getchar32,(void),getwchar,())
#elif defined(__CRT_HAVE__fgetwchar) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> getwchar(3) */
__CREDIRECT(,wint32_t,__THROWING,getchar32,(void),_fgetwchar,())
#elif defined(__CRT_HAVE_KOS$_fgetwchar)
/* >> getwchar(3) */
__CREDIRECT_KOS(,wint32_t,__THROWING,getchar32,(void),_fgetwchar,())
#else /* ... */
#include <__crt.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/getwchar.h>
/* >> getwchar(3) */
__FORCELOCAL __ATTR_ARTIFICIAL wint32_t (__LIBKCALL getchar32)(void) __THROWS(...) { return (__WINT32_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar))(); }
#elif !defined(__NO_STDSTREAMS) && ((defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fgetwc) || (defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$getwc))
#include <libc/local/parts.uchar.stdio/getchar32.h>
/* >> getwchar(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getchar32, __FORCELOCAL __ATTR_ARTIFICIAL wint32_t (__LIBKCALL getchar32)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar32))(); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fgetwc(3) */
__CREDIRECT(__ATTR_NONNULL((1)),wint16_t,__THROWING,fgetc16,(FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc)
/* >> fgetwc(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),wint16_t,__THROWING,fgetc16,(FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fgetwc(3) */
__CREDIRECT(__ATTR_NONNULL((1)),wint16_t,__THROWING,fgetc16,(FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_DOS$getwc)
/* >> fgetwc(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),wint16_t,__THROWING,fgetc16,(FILE *__restrict __stream),getwc,(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fgetwc(3) */
__CREDIRECT(__ATTR_NONNULL((1)),wint32_t,__THROWING,fgetc32,(FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_KOS$fgetwc)
/* >> fgetwc(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),wint32_t,__THROWING,fgetc32,(FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fgetwc(3) */
__CREDIRECT(__ATTR_NONNULL((1)),wint32_t,__THROWING,fgetc32,(FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_KOS$getwc)
/* >> fgetwc(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),wint32_t,__THROWING,fgetc32,(FILE *__restrict __stream),getwc,(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fgetwc(3) */
__CREDIRECT(__ATTR_NONNULL((1)),wint16_t,__THROWING,getc16,(FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc)
/* >> fgetwc(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),wint16_t,__THROWING,getc16,(FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fgetwc(3) */
__CREDIRECT(__ATTR_NONNULL((1)),wint16_t,__THROWING,getc16,(FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_DOS$getwc)
/* >> fgetwc(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),wint16_t,__THROWING,getc16,(FILE *__restrict __stream),getwc,(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fgetwc(3) */
__CREDIRECT(__ATTR_NONNULL((1)),wint32_t,__THROWING,getc32,(FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_KOS$fgetwc)
/* >> fgetwc(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),wint32_t,__THROWING,getc32,(FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fgetwc(3) */
__CREDIRECT(__ATTR_NONNULL((1)),wint32_t,__THROWING,getc32,(FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_KOS$getwc)
/* >> fgetwc(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),wint32_t,__THROWING,getc32,(FILE *__restrict __stream),getwc,(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_putwchar) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> putwchar(3) */
__CREDIRECT(,wint16_t,__THROWING,putchar16,(char16_t __wc),putwchar,(__wc))
#elif defined(__CRT_HAVE_DOS$putwchar)
/* >> putwchar(3) */
__CREDIRECT_DOS(,wint16_t,__THROWING,putchar16,(char16_t __wc),putwchar,(__wc))
#elif defined(__CRT_HAVE__fputwchar) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> putwchar(3) */
__CREDIRECT(,wint16_t,__THROWING,putchar16,(char16_t __wc),_fputwchar,(__wc))
#elif defined(__CRT_HAVE_DOS$_fputwchar)
/* >> putwchar(3) */
__CREDIRECT_DOS(,wint16_t,__THROWING,putchar16,(char16_t __wc),_fputwchar,(__wc))
#else /* ... */
#include <__crt.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/putwchar.h>
/* >> putwchar(3) */
__FORCELOCAL __ATTR_ARTIFICIAL wint16_t (__LIBDCALL putchar16)(char16_t __wc) __THROWS(...) { return (__WINT16_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar))((__WCHAR_TYPE__)__wc); }
#elif !defined(__NO_STDSTREAMS) && ((defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc))
#include <libc/local/parts.uchar.stdio/putchar16.h>
/* >> putwchar(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(putchar16, __FORCELOCAL __ATTR_ARTIFICIAL wint16_t (__LIBDCALL putchar16)(char16_t __wc) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar16))(__wc); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_putwchar) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> putwchar(3) */
__CREDIRECT(,wint32_t,__THROWING,putchar32,(char32_t __wc),putwchar,(__wc))
#elif defined(__CRT_HAVE_KOS$putwchar)
/* >> putwchar(3) */
__CREDIRECT_KOS(,wint32_t,__THROWING,putchar32,(char32_t __wc),putwchar,(__wc))
#elif defined(__CRT_HAVE__fputwchar) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> putwchar(3) */
__CREDIRECT(,wint32_t,__THROWING,putchar32,(char32_t __wc),_fputwchar,(__wc))
#elif defined(__CRT_HAVE_KOS$_fputwchar)
/* >> putwchar(3) */
__CREDIRECT_KOS(,wint32_t,__THROWING,putchar32,(char32_t __wc),_fputwchar,(__wc))
#else /* ... */
#include <__crt.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/putwchar.h>
/* >> putwchar(3) */
__FORCELOCAL __ATTR_ARTIFICIAL wint32_t (__LIBKCALL putchar32)(char32_t __wc) __THROWS(...) { return (__WINT32_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar))((__WCHAR_TYPE__)__wc); }
#elif !defined(__NO_STDSTREAMS) && ((defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$putwc))
#include <libc/local/parts.uchar.stdio/putchar32.h>
/* >> putwchar(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(putchar32, __FORCELOCAL __ATTR_ARTIFICIAL wint32_t (__LIBKCALL putchar32)(char32_t __wc) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar32))(__wc); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fputwc(3) */
__CREDIRECT(__ATTR_NONNULL((2)),wint16_t,__THROWING,fputc16,(char16_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$fputwc)
/* >> fputwc(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint16_t,__THROWING,fputc16,(char16_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fputwc(3) */
__CREDIRECT(__ATTR_NONNULL((2)),wint16_t,__THROWING,fputc16,(char16_t __wc, FILE *__stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$putwc)
/* >> fputwc(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint16_t,__THROWING,fputc16,(char16_t __wc, FILE *__stream),putwc,(__wc,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fputwc(3) */
__CREDIRECT(__ATTR_NONNULL((2)),wint32_t,__THROWING,fputc32,(char32_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$fputwc)
/* >> fputwc(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),wint32_t,__THROWING,fputc32,(char32_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fputwc(3) */
__CREDIRECT(__ATTR_NONNULL((2)),wint32_t,__THROWING,fputc32,(char32_t __wc, FILE *__stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$putwc)
/* >> fputwc(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),wint32_t,__THROWING,fputc32,(char32_t __wc, FILE *__stream),putwc,(__wc,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fputwc(3) */
__CREDIRECT(__ATTR_NONNULL((2)),wint16_t,__THROWING,putc16,(char16_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$fputwc)
/* >> fputwc(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint16_t,__THROWING,putc16,(char16_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fputwc(3) */
__CREDIRECT(__ATTR_NONNULL((2)),wint16_t,__THROWING,putc16,(char16_t __wc, FILE *__stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$putwc)
/* >> fputwc(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint16_t,__THROWING,putc16,(char16_t __wc, FILE *__stream),putwc,(__wc,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fputwc(3) */
__CREDIRECT(__ATTR_NONNULL((2)),wint32_t,__THROWING,putc32,(char32_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$fputwc)
/* >> fputwc(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),wint32_t,__THROWING,putc32,(char32_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fputwc(3) */
__CREDIRECT(__ATTR_NONNULL((2)),wint32_t,__THROWING,putc32,(char32_t __wc, FILE *__stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$putwc)
/* >> fputwc(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),wint32_t,__THROWING,putc32,(char32_t __wc, FILE *__stream),putwc,(__wc,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fgetws_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fgetws(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__THROWING,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$fgetws_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fgetws(3) */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__THROWING,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fgetws(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__THROWING,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$_fgetws_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> fgetws(3) */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__THROWING,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fgetws(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__THROWING,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$fgetws)
/* >> fgetws(3) */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__THROWING,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fgetws(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__THROWING,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$fgetws_unlocked)
/* >> fgetws(3) */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__THROWING,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fgetws(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__THROWING,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$_fgetws_nolock)
/* >> fgetws(3) */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__THROWING,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fgetws.h>
/* >> fgetws(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) char16_t *(__LIBDCALL fgetc16s)(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream) __THROWS(...) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetws))((__WCHAR_TYPE__ *)__buf, __bufsize, __stream); }
#elif ((defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fgetwc) || (defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$getwc)) && ((defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$ungetwc) || (defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
#include <libc/local/parts.uchar.stdio/fgetc16s.h>
/* >> fgetws(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetc16s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) char16_t *(__LIBDCALL fgetc16s)(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc16s))(__buf, __bufsize, __stream); })
#endif /* ... */
#if defined(__CRT_HAVE_fgetws_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fgetws(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char32_t *,__THROWING,fgetc32s,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_KOS$fgetws_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fgetws(3) */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char32_t *,__THROWING,fgetc32s,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fgetws(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char32_t *,__THROWING,fgetc32s,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_KOS$_fgetws_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> fgetws(3) */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char32_t *,__THROWING,fgetc32s,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fgetws(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char32_t *,__THROWING,fgetc32s,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_KOS$fgetws)
/* >> fgetws(3) */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char32_t *,__THROWING,fgetc32s,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fgetws(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char32_t *,__THROWING,fgetc32s,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_KOS$fgetws_unlocked)
/* >> fgetws(3) */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char32_t *,__THROWING,fgetc32s,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fgetws(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char32_t *,__THROWING,fgetc32s,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_KOS$_fgetws_nolock)
/* >> fgetws(3) */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char32_t *,__THROWING,fgetc32s,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fgetws.h>
/* >> fgetws(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) char32_t *(__LIBKCALL fgetc32s)(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream) __THROWS(...) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetws))((__WCHAR_TYPE__ *)__buf, __bufsize, __stream); }
#elif ((defined(__CRT_HAVE_fgetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fgetwc) || (defined(__CRT_HAVE_getwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$getwc)) && ((defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$ungetwc) || (defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
#include <libc/local/parts.uchar.stdio/fgetc32s.h>
/* >> fgetws(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetc32s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) char32_t *(__LIBKCALL fgetc32s)(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc32s))(__buf, __bufsize, __stream); })
#endif /* ... */
#if defined(__CRT_HAVE_fputws_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fputws(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc16s,(char16_t const *__restrict __str, FILE *__restrict __stream),fputws_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE_DOS$fputws_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fputws(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc16s,(char16_t const *__restrict __str, FILE *__restrict __stream),fputws_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE__fputws_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fputws(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc16s,(char16_t const *__restrict __str, FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif defined(__CRT_HAVE_DOS$_fputws_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> fputws(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc16s,(char16_t const *__restrict __str, FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif defined(__CRT_HAVE_fputws) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fputws(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc16s,(char16_t const *__restrict __str, FILE *__restrict __stream),fputws,(__str,__stream))
#elif defined(__CRT_HAVE_DOS$fputws)
/* >> fputws(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc16s,(char16_t const *__restrict __str, FILE *__restrict __stream),fputws,(__str,__stream))
#elif defined(__CRT_HAVE_fputws_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fputws(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc16s,(char16_t const *__restrict __str, FILE *__restrict __stream),fputws_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE_DOS$fputws_unlocked)
/* >> fputws(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc16s,(char16_t const *__restrict __str, FILE *__restrict __stream),fputws_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE__fputws_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fputws(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc16s,(char16_t const *__restrict __str, FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif defined(__CRT_HAVE_DOS$_fputws_nolock)
/* >> fputws(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc16s,(char16_t const *__restrict __str, FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif (defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fputws.h>
/* >> fputws(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBDCALL fputc16s)(char16_t const *__restrict __str, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputws))((__WCHAR_TYPE__ const *)__str, __stream); }
#elif (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc)
#include <libc/local/parts.uchar.stdio/fputc16s.h>
/* >> fputws(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fputc16s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBDCALL fputc16s)(char16_t const *__restrict __str, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc16s))(__str, __stream); })
#endif /* ... */
#if defined(__CRT_HAVE_fputws_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fputws(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc32s,(char32_t const *__restrict __str, FILE *__restrict __stream),fputws_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE_KOS$fputws_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fputws(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc32s,(char32_t const *__restrict __str, FILE *__restrict __stream),fputws_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE__fputws_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fputws(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc32s,(char32_t const *__restrict __str, FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif defined(__CRT_HAVE_KOS$_fputws_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> fputws(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc32s,(char32_t const *__restrict __str, FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif defined(__CRT_HAVE_fputws) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fputws(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc32s,(char32_t const *__restrict __str, FILE *__restrict __stream),fputws,(__str,__stream))
#elif defined(__CRT_HAVE_KOS$fputws)
/* >> fputws(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc32s,(char32_t const *__restrict __str, FILE *__restrict __stream),fputws,(__str,__stream))
#elif defined(__CRT_HAVE_fputws_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fputws(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc32s,(char32_t const *__restrict __str, FILE *__restrict __stream),fputws_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE_KOS$fputws_unlocked)
/* >> fputws(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc32s,(char32_t const *__restrict __str, FILE *__restrict __stream),fputws_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE__fputws_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fputws(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc32s,(char32_t const *__restrict __str, FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif defined(__CRT_HAVE_KOS$_fputws_nolock)
/* >> fputws(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc32s,(char32_t const *__restrict __str, FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif (defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fputws.h>
/* >> fputws(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBKCALL fputc32s)(char32_t const *__restrict __str, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputws))((__WCHAR_TYPE__ const *)__str, __stream); }
#elif (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter_unlocked) || ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$putwc)
#include <libc/local/parts.uchar.stdio/fputc32s.h>
/* >> fputws(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fputc32s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBKCALL fputc32s)(char32_t const *__restrict __str, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc32s))(__str, __stream); })
#endif /* ... */
#if defined(__CRT_HAVE_ungetwc_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> ungetwc(3) */
__CREDIRECT(__ATTR_NONNULL((2)),wint16_t,__NOTHROW_NCX,ungetc16,(wint16_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$ungetwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> ungetwc(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint16_t,__NOTHROW_NCX,ungetc16,(wint16_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> ungetwc(3) */
__CREDIRECT(__ATTR_NONNULL((2)),wint16_t,__NOTHROW_NCX,ungetc16,(wint16_t __wc, FILE *__stream),ungetwc,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$ungetwc)
/* >> ungetwc(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint16_t,__NOTHROW_NCX,ungetc16,(wint16_t __wc, FILE *__stream),ungetwc,(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> ungetwc(3) */
__CREDIRECT(__ATTR_NONNULL((2)),wint16_t,__NOTHROW_NCX,ungetc16,(wint16_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$ungetwc_unlocked)
/* >> ungetwc(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint16_t,__NOTHROW_NCX,ungetc16,(wint16_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_ungetwc_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> ungetwc(3) */
__CREDIRECT(__ATTR_NONNULL((2)),wint32_t,__NOTHROW_NCX,ungetc32,(wint32_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$ungetwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> ungetwc(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),wint32_t,__NOTHROW_NCX,ungetc32,(wint32_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> ungetwc(3) */
__CREDIRECT(__ATTR_NONNULL((2)),wint32_t,__NOTHROW_NCX,ungetc32,(wint32_t __wc, FILE *__stream),ungetwc,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$ungetwc)
/* >> ungetwc(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),wint32_t,__NOTHROW_NCX,ungetc32,(wint32_t __wc, FILE *__stream),ungetwc,(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> ungetwc(3) */
__CREDIRECT(__ATTR_NONNULL((2)),wint32_t,__NOTHROW_NCX,ungetc32,(wint32_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$ungetwc_unlocked)
/* >> ungetwc(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),wint32_t,__NOTHROW_NCX,ungetc32,(wint32_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#endif /* ... */

#if defined(__USE_ISOC95) || defined(__USE_UNIX98) || defined(__USE_DOS)
#if defined(__CRT_HAVE_fwprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
/* >> fwprintf(3) */
__LIBC __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBDCALL fc16printf)(FILE *__restrict __stream, char16_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwprintf");
#elif (defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fwprintf.h>
/* >> fwprintf(3) */
#define fc16printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf))
#elif (defined(__CRT_HAVE_vfwprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwprintf) || ((defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc)
#include <libc/local/parts.uchar.stdio/fc16printf.h>
/* >> fwprintf(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fc16printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBDCALL fc16printf)(FILE *__restrict __stream, char16_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc16printf))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fc16printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc16printf))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_fwprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
/* >> fwprintf(3) */
__LIBC __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBKCALL fc32printf)(FILE *__restrict __stream, char32_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwprintf");
#elif (defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fwprintf.h>
/* >> fwprintf(3) */
#define fc32printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf))
#elif (defined(__CRT_HAVE_vfwprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwprintf) || ((defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter_unlocked) || ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$putwc)
#include <libc/local/parts.uchar.stdio/fc32printf.h>
/* >> fwprintf(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fc32printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBKCALL fc32printf)(FILE *__restrict __stream, char32_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc32printf))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fc32printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc32printf))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_vfwprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> vfwprintf(3) */
__CREDIRECT(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc16printf,(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$vfwprintf)
/* >> vfwprintf(3) */
__CREDIRECT_DOS(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc16printf,(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args))
#elif (defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/vfwprintf.h>
/* >> vfwprintf(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBDCALL vfc16printf)(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf))(__stream, (__WCHAR_TYPE__ const *)__format, __args); }
#elif (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc)
#include <libc/local/parts.uchar.stdio/vfc16printf.h>
/* >> vfwprintf(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vfc16printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBDCALL vfc16printf)(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfc16printf))(__stream, __format, __args); })
#endif /* ... */
#if defined(__CRT_HAVE_vfwprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> vfwprintf(3) */
__CREDIRECT(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc32printf,(FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_KOS$vfwprintf)
/* >> vfwprintf(3) */
__CREDIRECT_KOS(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc32printf,(FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args))
#elif (defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/vfwprintf.h>
/* >> vfwprintf(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBKCALL vfc32printf)(FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf))(__stream, (__WCHAR_TYPE__ const *)__format, __args); }
#elif (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter_unlocked) || ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$putwc)
#include <libc/local/parts.uchar.stdio/vfc32printf.h>
/* >> vfwprintf(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vfc32printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBKCALL vfc32printf)(FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfc32printf))(__stream, __format, __args); })
#endif /* ... */
#if defined(__CRT_HAVE_wprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
/* >> wprintf(3) */
__LIBC __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBDCALL c16printf)(char16_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wprintf");
#else /* __CRT_HAVE_wprintf && __SIZEOF_WCHAR_T__ == 2 && __VLIBCCALL_IS_VLIBDCALL */
#include <__crt.h>
#if (defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS))) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wprintf.h>
/* >> wprintf(3) */
#define c16printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf))
#elif (defined(__CRT_HAVE_vwprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_vfwprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwprintf) || ((defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc)) && !defined(__NO_STDSTREAMS))
#include <libc/local/parts.uchar.stdio/c16printf.h>
/* >> wprintf(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c16printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBDCALL c16printf)(char16_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16printf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c16printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16printf))
#endif /* !__cplusplus */
#endif /* ... */
#endif /* !__CRT_HAVE_wprintf || __SIZEOF_WCHAR_T__ != 2 || !__VLIBCCALL_IS_VLIBDCALL */
#if defined(__CRT_HAVE_wprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
/* >> wprintf(3) */
__LIBC __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBKCALL c32printf)(char32_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wprintf");
#else /* __CRT_HAVE_wprintf && __SIZEOF_WCHAR_T__ == 4 && __VLIBCCALL_IS_VLIBKCALL */
#include <__crt.h>
#if (defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS))) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wprintf.h>
/* >> wprintf(3) */
#define c32printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf))
#elif (defined(__CRT_HAVE_vwprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 4) || (((defined(__CRT_HAVE_vfwprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwprintf) || ((defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter_unlocked) || ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$putwc)) && !defined(__NO_STDSTREAMS))
#include <libc/local/parts.uchar.stdio/c32printf.h>
/* >> wprintf(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c32printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBKCALL c32printf)(char32_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32printf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c32printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32printf))
#endif /* !__cplusplus */
#endif /* ... */
#endif /* !__CRT_HAVE_wprintf || __SIZEOF_WCHAR_T__ != 4 || !__VLIBCCALL_IS_VLIBKCALL */
#if defined(__CRT_HAVE_vwprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> vwprintf(3) */
__CREDIRECT(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vc16printf,(char16_t const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args))
#elif defined(__CRT_HAVE_DOS$vwprintf)
/* >> vwprintf(3) */
__CREDIRECT_DOS(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vc16printf,(char16_t const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args))
#else /* ... */
#include <__crt.h>
#if (defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/vwprintf.h>
/* >> vwprintf(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBDCALL vc16printf)(char16_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf))((__WCHAR_TYPE__ const *)__format, __args); }
#elif ((defined(__CRT_HAVE_vfwprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwprintf) || ((defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc)) && !defined(__NO_STDSTREAMS)
#include <libc/local/parts.uchar.stdio/vc16printf.h>
/* >> vwprintf(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vc16printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBDCALL vc16printf)(char16_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc16printf))(__format, __args); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_vwprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> vwprintf(3) */
__CREDIRECT(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vc32printf,(char32_t const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args))
#elif defined(__CRT_HAVE_KOS$vwprintf)
/* >> vwprintf(3) */
__CREDIRECT_KOS(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vc32printf,(char32_t const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args))
#else /* ... */
#include <__crt.h>
#if (defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/vwprintf.h>
/* >> vwprintf(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBKCALL vc32printf)(char32_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf))((__WCHAR_TYPE__ const *)__format, __args); }
#elif ((defined(__CRT_HAVE_vfwprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwprintf) || ((defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter_unlocked) || ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$putwc)) && !defined(__NO_STDSTREAMS)
#include <libc/local/parts.uchar.stdio/vc32printf.h>
/* >> vwprintf(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vc32printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBKCALL vc32printf)(char32_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc32printf))(__format, __args); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_fwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
/* >> fwscanf(3) */
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBDCALL fc16scanf)(FILE *__restrict __stream, char16_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwscanf");
#elif defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fwscanf.h>
/* >> fwscanf(3) */
#define fc16scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf))
#elif defined(__CRT_HAVE_DOS$vfwscanf)
#include <libc/local/parts.uchar.stdio/fc16scanf.h>
/* >> fwscanf(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fc16scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBDCALL fc16scanf)(FILE *__restrict __stream, char16_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc16scanf))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fc16scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc16scanf))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_fwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
/* >> fwscanf(3) */
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBKCALL fc32scanf)(FILE *__restrict __stream, char32_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwscanf");
#elif defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fwscanf.h>
/* >> fwscanf(3) */
#define fc32scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf))
#elif defined(__CRT_HAVE_KOS$vfwscanf)
#include <libc/local/parts.uchar.stdio/fc32scanf.h>
/* >> fwscanf(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fc32scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBKCALL fc32scanf)(FILE *__restrict __stream, char32_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc32scanf))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fc32scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc32scanf))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
/* >> wscanf(3) */
__LIBC __ATTR_LIBC_WSCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBDCALL c16scanf)(char16_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wscanf");
#else /* __CRT_HAVE_wscanf && __SIZEOF_WCHAR_T__ == 2 && __VLIBCCALL_IS_VLIBDCALL */
#include <__crt.h>
#if (defined(__CRT_HAVE_vwscanf) || (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS))) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wscanf.h>
/* >> wscanf(3) */
#define c16scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf))
#elif (defined(__CRT_HAVE_vwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vwscanf) || (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwscanf)) && !defined(__NO_STDSTREAMS))
#include <libc/local/parts.uchar.stdio/c16scanf.h>
/* >> wscanf(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c16scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WSCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBDCALL c16scanf)(char16_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scanf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c16scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scanf))
#endif /* !__cplusplus */
#endif /* ... */
#endif /* !__CRT_HAVE_wscanf || __SIZEOF_WCHAR_T__ != 2 || !__VLIBCCALL_IS_VLIBDCALL */
#if defined(__CRT_HAVE_wscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
/* >> wscanf(3) */
__LIBC __ATTR_LIBC_WSCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBKCALL c32scanf)(char32_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wscanf");
#else /* __CRT_HAVE_wscanf && __SIZEOF_WCHAR_T__ == 4 && __VLIBCCALL_IS_VLIBKCALL */
#include <__crt.h>
#if (defined(__CRT_HAVE_vwscanf) || (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS))) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wscanf.h>
/* >> wscanf(3) */
#define c32scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf))
#elif (defined(__CRT_HAVE_vwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vwscanf) || (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 4) || (((defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwscanf)) && !defined(__NO_STDSTREAMS))
#include <libc/local/parts.uchar.stdio/c32scanf.h>
/* >> wscanf(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c32scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WSCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBKCALL c32scanf)(char32_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scanf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c32scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scanf))
#endif /* !__cplusplus */
#endif /* ... */
#endif /* !__CRT_HAVE_wscanf || __SIZEOF_WCHAR_T__ != 4 || !__VLIBCCALL_IS_VLIBKCALL */
#if defined(__CRT_HAVE_swscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
/* >> swscanf(3) */
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBDCALL sc16scanf)(char16_t const *__restrict __src, char16_t const *__restrict __format, ...) __CASMNAME("swscanf");
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/swscanf.h>
/* >> swscanf(3) */
#define sc16scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swscanf))
#else /* ... */
#include <libc/local/parts.uchar.stdio/sc16scanf.h>
/* >> swscanf(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(sc16scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBDCALL sc16scanf)(char16_t const *__restrict __src, char16_t const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sc16scanf))(__src, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define sc16scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sc16scanf))
#endif /* !__cplusplus */
#endif /* !... */
#if defined(__CRT_HAVE_swscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
/* >> swscanf(3) */
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBKCALL sc32scanf)(char32_t const *__restrict __src, char32_t const *__restrict __format, ...) __CASMNAME("swscanf");
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/swscanf.h>
/* >> swscanf(3) */
#define sc32scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swscanf))
#else /* ... */
#include <libc/local/parts.uchar.stdio/sc32scanf.h>
/* >> swscanf(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(sc32scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBKCALL sc32scanf)(char32_t const *__restrict __src, char32_t const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sc32scanf))(__src, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define sc32scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sc32scanf))
#endif /* !__cplusplus */
#endif /* !... */
#if defined(__CRT_HAVE_vswprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> vswprintf(3) */
__CREDIRECT(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsc16printf,(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#elif defined(__CRT_HAVE_DOS$vswprintf)
/* >> vswprintf(3) */
__CREDIRECT_DOS(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsc16printf,(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/vswprintf.h>
/* >> vswprintf(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBDCALL vsc16printf)(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswprintf))((__WCHAR_TYPE__ *)__buf, __buflen, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* ... */
#include <libc/local/parts.uchar.stdio/vsc16printf.h>
/* >> vswprintf(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vsc16printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBDCALL vsc16printf)(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsc16printf))(__buf, __buflen, __format, __args); })
#endif /* !... */
#if defined(__CRT_HAVE_vswprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> vswprintf(3) */
__CREDIRECT(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsc32printf,(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#elif defined(__CRT_HAVE_KOS$vswprintf)
/* >> vswprintf(3) */
__CREDIRECT_KOS(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsc32printf,(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/vswprintf.h>
/* >> vswprintf(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBKCALL vsc32printf)(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswprintf))((__WCHAR_TYPE__ *)__buf, __buflen, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* ... */
#include <libc/local/parts.uchar.stdio/vsc32printf.h>
/* >> vswprintf(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vsc32printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBKCALL vsc32printf)(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsc32printf))(__buf, __buflen, __format, __args); })
#endif /* !... */
#if defined(__CRT_HAVE_swprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
/* >> swprintf(3) */
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBDCALL sc16printf)(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, ...) __CASMNAME("swprintf");
#elif defined(__CRT_HAVE__swprintf) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
/* >> swprintf(3) */
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBDCALL sc16printf)(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, ...) __CASMNAME("_swprintf");
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/swprintf.h>
/* >> swprintf(3) */
#define sc16printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swprintf))
#else /* ... */
#include <libc/local/parts.uchar.stdio/sc16printf.h>
/* >> swprintf(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(sc16printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBDCALL sc16printf)(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sc16printf))(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define sc16printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sc16printf))
#endif /* !__cplusplus */
#endif /* !... */
#if defined(__CRT_HAVE_swprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
/* >> swprintf(3) */
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBKCALL sc32printf)(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, ...) __CASMNAME("swprintf");
#elif defined(__CRT_HAVE__swprintf) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
/* >> swprintf(3) */
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBKCALL sc32printf)(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, ...) __CASMNAME("_swprintf");
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/swprintf.h>
/* >> swprintf(3) */
#define sc32printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swprintf))
#else /* ... */
#include <libc/local/parts.uchar.stdio/sc32printf.h>
/* >> swprintf(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(sc32printf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBKCALL sc32printf)(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sc32printf))(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define sc32printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sc32printf))
#endif /* !__cplusplus */
#endif /* !... */
#endif /* __USE_ISOC95 || __USE_UNIX98 || __USE_DOS */

#ifdef __USE_ISOC99
#if defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> vfwscanf(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc16scanf,(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$vfwscanf)
/* >> vfwscanf(3) */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc16scanf,(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#endif /* ... */
#if defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> vfwscanf(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc32scanf,(FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_KOS$vfwscanf)
/* >> vfwscanf(3) */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc32scanf,(FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#endif /* ... */
#if defined(__CRT_HAVE_vwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> vwscanf(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vc16scanf,(char16_t const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#elif defined(__CRT_HAVE_DOS$vwscanf)
/* >> vwscanf(3) */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vc16scanf,(char16_t const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#else /* ... */
#include <__crt.h>
#if defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/vwscanf.h>
/* >> vwscanf(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBDCALL vc16scanf)(char16_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf))((__WCHAR_TYPE__ const *)__format, __args); }
#elif ((defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwscanf)) && !defined(__NO_STDSTREAMS)
#include <libc/local/parts.uchar.stdio/vc16scanf.h>
/* >> vwscanf(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vc16scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBDCALL vc16scanf)(char16_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc16scanf))(__format, __args); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_vwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> vwscanf(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vc32scanf,(char32_t const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#elif defined(__CRT_HAVE_KOS$vwscanf)
/* >> vwscanf(3) */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vc32scanf,(char32_t const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#else /* ... */
#include <__crt.h>
#if defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/vwscanf.h>
/* >> vwscanf(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBKCALL vc32scanf)(char32_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf))((__WCHAR_TYPE__ const *)__format, __args); }
#elif ((defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwscanf)) && !defined(__NO_STDSTREAMS)
#include <libc/local/parts.uchar.stdio/vc32scanf.h>
/* >> vwscanf(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vc32scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBKCALL vc32scanf)(char32_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc32scanf))(__format, __args); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_vswscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> vswscanf(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsc16scanf,(char16_t const *__restrict __src, char16_t const *__restrict __format, __builtin_va_list __args),vswscanf,(__src,__format,__args))
#elif defined(__CRT_HAVE_DOS$vswscanf)
/* >> vswscanf(3) */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsc16scanf,(char16_t const *__restrict __src, char16_t const *__restrict __format, __builtin_va_list __args),vswscanf,(__src,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/vswscanf.h>
/* >> vswscanf(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBDCALL vsc16scanf)(char16_t const *__restrict __src, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswscanf))((__WCHAR_TYPE__ const *)__src, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* ... */
#include <libc/local/parts.uchar.stdio/vsc16scanf.h>
/* >> vswscanf(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vsc16scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBDCALL vsc16scanf)(char16_t const *__restrict __src, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsc16scanf))(__src, __format, __args); })
#endif /* !... */
#if defined(__CRT_HAVE_vswscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> vswscanf(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsc32scanf,(char32_t const *__restrict __src, char32_t const *__restrict __format, __builtin_va_list __args),vswscanf,(__src,__format,__args))
#elif defined(__CRT_HAVE_KOS$vswscanf)
/* >> vswscanf(3) */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsc32scanf,(char32_t const *__restrict __src, char32_t const *__restrict __format, __builtin_va_list __args),vswscanf,(__src,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/vswscanf.h>
/* >> vswscanf(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBKCALL vsc32scanf)(char32_t const *__restrict __src, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswscanf))((__WCHAR_TYPE__ const *)__src, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* ... */
#include <libc/local/parts.uchar.stdio/vsc32scanf.h>
/* >> vswscanf(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vsc32scanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBKCALL vsc32scanf)(char32_t const *__restrict __src, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsc32scanf))(__src, __format, __args); })
#endif /* !... */
#endif /* __USE_ISOC99 */

#ifdef __USE_GNU
#if defined(__CRT_HAVE_getwchar_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> getwchar_unlocked(3) */
__CREDIRECT(,__WINT16_TYPE__,__THROWING,getchar16_unlocked,(void),getwchar_unlocked,())
#elif defined(__CRT_HAVE_DOS$getwchar_unlocked)
/* >> getwchar_unlocked(3) */
__CREDIRECT_DOS(,__WINT16_TYPE__,__THROWING,getchar16_unlocked,(void),getwchar_unlocked,())
#else /* ... */
#include <__crt.h>
#if (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE__fgetwc_nolock)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/getwchar_unlocked.h>
/* >> getwchar_unlocked(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __WINT16_TYPE__ (__LIBDCALL getchar16_unlocked)(void) __THROWS(...) { return (__WINT16_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar_unlocked))(); }
#elif ((defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fgetwc_unlocked) || (defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_fgetwc_nolock)) && !defined(__NO_STDSTREAMS)
#include <libc/local/parts.uchar.stdio/getchar16_unlocked.h>
/* >> getwchar_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getchar16_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __WINT16_TYPE__ (__LIBDCALL getchar16_unlocked)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar16_unlocked))(); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_getwchar_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> getwchar_unlocked(3) */
__CREDIRECT(,__WINT32_TYPE__,__THROWING,getchar32_unlocked,(void),getwchar_unlocked,())
#elif defined(__CRT_HAVE_KOS$getwchar_unlocked)
/* >> getwchar_unlocked(3) */
__CREDIRECT_KOS(,__WINT32_TYPE__,__THROWING,getchar32_unlocked,(void),getwchar_unlocked,())
#else /* ... */
#include <__crt.h>
#if (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE__fgetwc_nolock)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/getwchar_unlocked.h>
/* >> getwchar_unlocked(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __WINT32_TYPE__ (__LIBKCALL getchar32_unlocked)(void) __THROWS(...) { return (__WINT32_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar_unlocked))(); }
#elif ((defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fgetwc_unlocked) || (defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fgetwc_nolock)) && !defined(__NO_STDSTREAMS)
#include <libc/local/parts.uchar.stdio/getchar32_unlocked.h>
/* >> getwchar_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getchar32_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __WINT32_TYPE__ (__LIBKCALL getchar32_unlocked)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar32_unlocked))(); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_putwchar_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> putwchar_unlocked(3) */
__CREDIRECT(,__WINT16_TYPE__,__THROWING,putchar16_unlocked,(char16_t __wc),putwchar_unlocked,(__wc))
#elif defined(__CRT_HAVE_DOS$putwchar_unlocked)
/* >> putwchar_unlocked(3) */
__CREDIRECT_DOS(,__WINT16_TYPE__,__THROWING,putchar16_unlocked,(char16_t __wc),putwchar_unlocked,(__wc))
#else /* ... */
#include <__crt.h>
#if (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/putwchar_unlocked.h>
/* >> putwchar_unlocked(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __WINT16_TYPE__ (__LIBDCALL putchar16_unlocked)(char16_t __wc) __THROWS(...) { return (__WINT16_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar_unlocked))((__WCHAR_TYPE__)__wc); }
#elif ((defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_fputwc_nolock)) && !defined(__NO_STDSTREAMS)
#include <libc/local/parts.uchar.stdio/putchar16_unlocked.h>
/* >> putwchar_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(putchar16_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __WINT16_TYPE__ (__LIBDCALL putchar16_unlocked)(char16_t __wc) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar16_unlocked))(__wc); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_putwchar_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> putwchar_unlocked(3) */
__CREDIRECT(,__WINT32_TYPE__,__THROWING,putchar32_unlocked,(char32_t __wc),putwchar_unlocked,(__wc))
#elif defined(__CRT_HAVE_KOS$putwchar_unlocked)
/* >> putwchar_unlocked(3) */
__CREDIRECT_KOS(,__WINT32_TYPE__,__THROWING,putchar32_unlocked,(char32_t __wc),putwchar_unlocked,(__wc))
#else /* ... */
#include <__crt.h>
#if (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/putwchar_unlocked.h>
/* >> putwchar_unlocked(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __WINT32_TYPE__ (__LIBKCALL putchar32_unlocked)(char32_t __wc) __THROWS(...) { return (__WINT32_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar_unlocked))((__WCHAR_TYPE__)__wc); }
#elif ((defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc_unlocked) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fputwc_nolock)) && !defined(__NO_STDSTREAMS)
#include <libc/local/parts.uchar.stdio/putchar32_unlocked.h>
/* >> putwchar_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(putchar32_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __WINT32_TYPE__ (__LIBKCALL putchar32_unlocked)(char32_t __wc) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar32_unlocked))(__wc); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1)),__WINT16_TYPE__,__THROWING,fgetc16_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc_unlocked)
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__WINT16_TYPE__,__THROWING,fgetc16_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1)),__WINT16_TYPE__,__THROWING,fgetc16_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_DOS$_fgetwc_nolock)
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__WINT16_TYPE__,__THROWING,fgetc16_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1)),__WINT32_TYPE__,__THROWING,fgetc32_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_KOS$fgetwc_unlocked)
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__WINT32_TYPE__,__THROWING,fgetc32_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1)),__WINT32_TYPE__,__THROWING,fgetc32_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_KOS$_fgetwc_nolock)
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__WINT32_TYPE__,__THROWING,fgetc32_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((2)),__WINT16_TYPE__,__THROWING,fputc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$fputwc_unlocked)
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__WINT16_TYPE__,__THROWING,fputc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((2)),__WINT16_TYPE__,__THROWING,fputc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$_fputwc_nolock)
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__WINT16_TYPE__,__THROWING,fputc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((2)),__WINT32_TYPE__,__THROWING,fputc32_unlocked,(char32_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$fputwc_unlocked)
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__WINT32_TYPE__,__THROWING,fputc32_unlocked,(char32_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((2)),__WINT32_TYPE__,__THROWING,fputc32_unlocked,(char32_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$_fputwc_nolock)
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__WINT32_TYPE__,__THROWING,fputc32_unlocked,(char32_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1)),__WINT16_TYPE__,__THROWING,getc16_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc_unlocked)
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__WINT16_TYPE__,__THROWING,getc16_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1)),__WINT16_TYPE__,__THROWING,getc16_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_DOS$_fgetwc_nolock)
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1)),__WINT16_TYPE__,__THROWING,getc16_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1)),__WINT32_TYPE__,__THROWING,getc32_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_KOS$fgetwc_unlocked)
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__WINT32_TYPE__,__THROWING,getc32_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1)),__WINT32_TYPE__,__THROWING,getc32_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_KOS$_fgetwc_nolock)
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1)),__WINT32_TYPE__,__THROWING,getc32_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((2)),__WINT16_TYPE__,__THROWING,putc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$fputwc_unlocked)
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__WINT16_TYPE__,__THROWING,putc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((2)),__WINT16_TYPE__,__THROWING,putc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$_fputwc_nolock)
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__WINT16_TYPE__,__THROWING,putc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((2)),__WINT32_TYPE__,__THROWING,putc32_unlocked,(char32_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$fputwc_unlocked)
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__WINT32_TYPE__,__THROWING,putc32_unlocked,(char32_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((2)),__WINT32_TYPE__,__THROWING,putc32_unlocked,(char32_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_KOS$_fputwc_nolock)
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__WINT32_TYPE__,__THROWING,putc32_unlocked,(char32_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_fgetws_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fgetws_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1, 3)),char16_t *,__THROWING,fgetc16s_unlocked,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$fgetws_unlocked)
/* >> fgetws_unlocked(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 3)),char16_t *,__THROWING,fgetc16s_unlocked,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fgetws_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1, 3)),char16_t *,__THROWING,fgetc16s_unlocked,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$_fgetws_nolock)
/* >> fgetws_unlocked(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 3)),char16_t *,__THROWING,fgetc16s_unlocked,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fgetws_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1, 3)),char16_t *,__THROWING,fgetc16s_unlocked,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$fgetws)
/* >> fgetws_unlocked(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 3)),char16_t *,__THROWING,fgetc16s_unlocked,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE__fgetwc_nolock)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fgetws_unlocked.h>
/* >> fgetws_unlocked(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) char16_t *(__LIBDCALL fgetc16s_unlocked)(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) __THROWS(...) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetws_unlocked))((__WCHAR_TYPE__ *)__buf, __bufsize, __stream); }
#elif ((defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fgetwc_unlocked) || (defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_fgetwc_nolock)) && ((defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$ungetwc_unlocked) || (defined(__CRT_HAVE__ungetwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_ungetwc_nolock) || (defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$ungetwc)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
#include <libc/local/parts.uchar.stdio/fgetc16s_unlocked.h>
/* >> fgetws_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetc16s_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) char16_t *(__LIBDCALL fgetc16s_unlocked)(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc16s_unlocked))(__buf, __bufsize, __stream); })
#endif /* ... */
#if defined(__CRT_HAVE_fgetws_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fgetws_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1, 3)),char32_t *,__THROWING,fgetc32s_unlocked,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_KOS$fgetws_unlocked)
/* >> fgetws_unlocked(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 3)),char32_t *,__THROWING,fgetc32s_unlocked,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fgetws_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1, 3)),char32_t *,__THROWING,fgetc32s_unlocked,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_KOS$_fgetws_nolock)
/* >> fgetws_unlocked(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 3)),char32_t *,__THROWING,fgetc32s_unlocked,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fgetws_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1, 3)),char32_t *,__THROWING,fgetc32s_unlocked,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_KOS$fgetws)
/* >> fgetws_unlocked(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 3)),char32_t *,__THROWING,fgetc32s_unlocked,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE__fgetwc_nolock)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fgetws_unlocked.h>
/* >> fgetws_unlocked(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) char32_t *(__LIBKCALL fgetc32s_unlocked)(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) __THROWS(...) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetws_unlocked))((__WCHAR_TYPE__ *)__buf, __bufsize, __stream); }
#elif ((defined(__CRT_HAVE_fgetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fgetwc_unlocked) || (defined(__CRT_HAVE__fgetwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fgetwc_nolock)) && ((defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$ungetwc_unlocked) || (defined(__CRT_HAVE__ungetwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_ungetwc_nolock) || (defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$ungetwc)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
#include <libc/local/parts.uchar.stdio/fgetc32s_unlocked.h>
/* >> fgetws_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetc32s_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) char32_t *(__LIBKCALL fgetc32s_unlocked)(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc32s_unlocked))(__buf, __bufsize, __stream); })
#endif /* ... */
#if defined(__CRT_HAVE_fputws_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fputws_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc16s_unlocked,(char16_t const *__restrict __str, __FILE *__restrict __stream),fputws_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE_DOS$fputws_unlocked)
/* >> fputws_unlocked(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc16s_unlocked,(char16_t const *__restrict __str, __FILE *__restrict __stream),fputws_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE__fputws_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> fputws_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc16s_unlocked,(char16_t const *__restrict __str, __FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif defined(__CRT_HAVE_DOS$_fputws_nolock)
/* >> fputws_unlocked(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc16s_unlocked,(char16_t const *__restrict __str, __FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif (defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fputws_unlocked.h>
/* >> fputws_unlocked(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBDCALL fputc16s_unlocked)(char16_t const *__restrict __str, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputws_unlocked))((__WCHAR_TYPE__ const *)__str, __stream); }
#elif (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_fputwc_nolock)
#include <libc/local/parts.uchar.stdio/fputc16s_unlocked.h>
/* >> fputws_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fputc16s_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBDCALL fputc16s_unlocked)(char16_t const *__restrict __str, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc16s_unlocked))(__str, __stream); })
#endif /* ... */
#if defined(__CRT_HAVE_fputws_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fputws_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc32s_unlocked,(char32_t const *__restrict __str, __FILE *__restrict __stream),fputws_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE_KOS$fputws_unlocked)
/* >> fputws_unlocked(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc32s_unlocked,(char32_t const *__restrict __str, __FILE *__restrict __stream),fputws_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE__fputws_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> fputws_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc32s_unlocked,(char32_t const *__restrict __str, __FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif defined(__CRT_HAVE_KOS$_fputws_nolock)
/* >> fputws_unlocked(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputc32s_unlocked,(char32_t const *__restrict __str, __FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif (defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fputws_unlocked.h>
/* >> fputws_unlocked(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBKCALL fputc32s_unlocked)(char32_t const *__restrict __str, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputws_unlocked))((__WCHAR_TYPE__ const *)__str, __stream); }
#elif (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc_unlocked) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fputwc_nolock)
#include <libc/local/parts.uchar.stdio/fputc32s_unlocked.h>
/* >> fputws_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fputc32s_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBKCALL fputc32s_unlocked)(char32_t const *__restrict __str, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc32s_unlocked))(__str, __stream); })
#endif /* ... */
#endif /* __USE_GNU */

#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_open_wmemstream) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> open_wmemstream(3) */
__CREDIRECT(,__FILE *,__NOTHROW_NCX,open_c16memstream,(char16_t **__bufloc, __SIZE_TYPE__ *__sizeloc),open_wmemstream,(__bufloc,__sizeloc))
#elif defined(__CRT_HAVE_DOS$open_wmemstream)
/* >> open_wmemstream(3) */
__CREDIRECT_DOS(,__FILE *,__NOTHROW_NCX,open_c16memstream,(char16_t **__bufloc, __SIZE_TYPE__ *__sizeloc),open_wmemstream,(__bufloc,__sizeloc))
#endif /* ... */
#if defined(__CRT_HAVE_open_wmemstream) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> open_wmemstream(3) */
__CREDIRECT(,__FILE *,__NOTHROW_NCX,open_c32memstream,(char32_t **__bufloc, __SIZE_TYPE__ *__sizeloc),open_wmemstream,(__bufloc,__sizeloc))
#elif defined(__CRT_HAVE_KOS$open_wmemstream)
/* >> open_wmemstream(3) */
__CREDIRECT_KOS(,__FILE *,__NOTHROW_NCX,open_c32memstream,(char32_t **__bufloc, __SIZE_TYPE__ *__sizeloc),open_wmemstream,(__bufloc,__sizeloc))
#endif /* ... */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_KOS
#if defined(__CRT_HAVE_file_wprinter_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c16printer,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c16printer,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c16printer,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter)
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c16printer,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c16printer,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter_unlocked)
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c16printer,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/file_wprinter.h>
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__LIBDCALL file_c16printer)(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#elif (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$putwc)
#include <libc/local/parts.uchar.stdio/file_c16printer.h>
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_c16printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__LIBDCALL file_c16printer)(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_c16printer))(__arg, __data, __datalen); })
#endif /* ... */
#if defined(__CRT_HAVE_file_wprinter_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c32printer,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$file_wprinter_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c32printer,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c32printer,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$file_wprinter)
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c32printer,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c32printer,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$file_wprinter_unlocked)
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c32printer,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/file_wprinter.h>
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__LIBKCALL file_c32printer)(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#elif (defined(__CRT_HAVE_fputwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc) || (defined(__CRT_HAVE_putwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$putwc)
#include <libc/local/parts.uchar.stdio/file_c32printer.h>
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_c32printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__LIBKCALL file_c32printer)(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_c32printer))(__arg, __data, __datalen); })
#endif /* ... */
#if defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c16printer_unlocked,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter_unlocked)
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c16printer_unlocked,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c16printer_unlocked,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter)
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c16printer_unlocked,(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/file_wprinter_unlocked.h>
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__LIBDCALL file_c16printer_unlocked)(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter_unlocked))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#elif (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_fputwc_nolock)
#include <libc/local/parts.uchar.stdio/file_c16printer_unlocked.h>
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_c16printer_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__LIBDCALL file_c16printer_unlocked)(void *__arg, char16_t const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_c16printer_unlocked))(__arg, __data, __datalen); })
#endif /* ... */
#if defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c32printer_unlocked,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$file_wprinter_unlocked)
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c32printer_unlocked,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c32printer_unlocked,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_KOS$file_wprinter)
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_c32printer_unlocked,(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/file_wprinter_unlocked.h>
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__LIBKCALL file_c32printer_unlocked)(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter_unlocked))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#elif (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc_unlocked) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fputwc_nolock)
#include <libc/local/parts.uchar.stdio/file_c32printer_unlocked.h>
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_c32printer_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__LIBKCALL file_c32printer_unlocked)(void *__arg, char32_t const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_c32printer_unlocked))(__arg, __data, __datalen); })
#endif /* ... */
#if defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> ungetwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((2)),__WINT16_TYPE__,__NOTHROW_NCX,ungetc16_unlocked,(__WINT16_TYPE__ __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_DOS$ungetwc_unlocked)
/* >> ungetwc_unlocked(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__WINT16_TYPE__,__NOTHROW_NCX,ungetc16_unlocked,(__WINT16_TYPE__ __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> ungetwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((2)),__WINT16_TYPE__,__NOTHROW_NCX,ungetc16_unlocked,(__WINT16_TYPE__ __ch, __FILE *__restrict __stream),_ungetwc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_DOS$_ungetwc_nolock)
/* >> ungetwc_unlocked(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__WINT16_TYPE__,__NOTHROW_NCX,ungetc16_unlocked,(__WINT16_TYPE__ __ch, __FILE *__restrict __stream),_ungetwc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> ungetwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((2)),__WINT16_TYPE__,__NOTHROW_NCX,ungetc16_unlocked,(__WINT16_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#elif defined(__CRT_HAVE_DOS$ungetwc)
/* >> ungetwc_unlocked(3) */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),__WINT16_TYPE__,__NOTHROW_NCX,ungetc16_unlocked,(__WINT16_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_ungetwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> ungetwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((2)),__WINT32_TYPE__,__NOTHROW_NCX,ungetc32_unlocked,(__WINT32_TYPE__ __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_KOS$ungetwc_unlocked)
/* >> ungetwc_unlocked(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__WINT32_TYPE__,__NOTHROW_NCX,ungetc32_unlocked,(__WINT32_TYPE__ __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> ungetwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((2)),__WINT32_TYPE__,__NOTHROW_NCX,ungetc32_unlocked,(__WINT32_TYPE__ __ch, __FILE *__restrict __stream),_ungetwc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_KOS$_ungetwc_nolock)
/* >> ungetwc_unlocked(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__WINT32_TYPE__,__NOTHROW_NCX,ungetc32_unlocked,(__WINT32_TYPE__ __ch, __FILE *__restrict __stream),_ungetwc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetwc) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> ungetwc_unlocked(3) */
__CREDIRECT(__ATTR_NONNULL((2)),__WINT32_TYPE__,__NOTHROW_NCX,ungetc32_unlocked,(__WINT32_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#elif defined(__CRT_HAVE_KOS$ungetwc)
/* >> ungetwc_unlocked(3) */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),__WINT32_TYPE__,__NOTHROW_NCX,ungetc32_unlocked,(__WINT32_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_vfwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> vfwprintf_unlocked(3) */
__CREDIRECT(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc16printf_unlocked,(__FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$vfwprintf_unlocked)
/* >> vfwprintf_unlocked(3) */
__CREDIRECT_DOS(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc16printf_unlocked,(__FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif (defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/vfwprintf_unlocked.h>
/* >> vfwprintf_unlocked(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBDCALL vfc16printf_unlocked)(__FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf_unlocked))(__stream, (__WCHAR_TYPE__ const *)__format, __args); }
#elif (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_fputwc_nolock)
#include <libc/local/parts.uchar.stdio/vfc16printf_unlocked.h>
/* >> vfwprintf_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vfc16printf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBDCALL vfc16printf_unlocked)(__FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfc16printf_unlocked))(__stream, __format, __args); })
#endif /* ... */
#if defined(__CRT_HAVE_vfwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> vfwprintf_unlocked(3) */
__CREDIRECT(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc32printf_unlocked,(__FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_KOS$vfwprintf_unlocked)
/* >> vfwprintf_unlocked(3) */
__CREDIRECT_KOS(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc32printf_unlocked,(__FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif (defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/vfwprintf_unlocked.h>
/* >> vfwprintf_unlocked(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBKCALL vfc32printf_unlocked)(__FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf_unlocked))(__stream, (__WCHAR_TYPE__ const *)__format, __args); }
#elif (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc_unlocked) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fputwc_nolock)
#include <libc/local/parts.uchar.stdio/vfc32printf_unlocked.h>
/* >> vfwprintf_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vfc32printf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBKCALL vfc32printf_unlocked)(__FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfc32printf_unlocked))(__stream, __format, __args); })
#endif /* ... */
#if defined(__CRT_HAVE_fwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
/* >> fwprintf_unlocked(3) */
__LIBC __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBDCALL fc16printf_unlocked)(__FILE *__restrict __stream, char16_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwprintf_unlocked");
#elif (defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fwprintf_unlocked.h>
/* >> fwprintf_unlocked(3) */
#define fc16printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf_unlocked))
#elif (defined(__CRT_HAVE_vfwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwprintf_unlocked) || ((defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_fputwc_nolock)
#include <libc/local/parts.uchar.stdio/fc16printf_unlocked.h>
/* >> fwprintf_unlocked(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fc16printf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBDCALL fc16printf_unlocked)(__FILE *__restrict __stream, char16_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc16printf_unlocked))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fc16printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc16printf_unlocked))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_fwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
/* >> fwprintf_unlocked(3) */
__LIBC __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBKCALL fc32printf_unlocked)(__FILE *__restrict __stream, char32_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwprintf_unlocked");
#elif (defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fwprintf_unlocked.h>
/* >> fwprintf_unlocked(3) */
#define fc32printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf_unlocked))
#elif (defined(__CRT_HAVE_vfwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwprintf_unlocked) || ((defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc_unlocked) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fputwc_nolock)
#include <libc/local/parts.uchar.stdio/fc32printf_unlocked.h>
/* >> fwprintf_unlocked(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fc32printf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBKCALL fc32printf_unlocked)(__FILE *__restrict __stream, char32_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc32printf_unlocked))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fc32printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc32printf_unlocked))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wprintf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
/* >> wprintf_unlocked(3) */
__LIBC __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBDCALL c16printf_unlocked)(char16_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wprintf_unlocked");
#else /* __CRT_HAVE_wprintf_unlocked && __SIZEOF_WCHAR_T__ == 2 && __VLIBCCALL_IS_VLIBDCALL */
#include <__crt.h>
#if (defined(__CRT_HAVE_vwprintf_unlocked) || ((defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS))) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wprintf_unlocked.h>
/* >> wprintf_unlocked(3) */
#define c16printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf_unlocked))
#elif (defined(__CRT_HAVE_vwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vwprintf_unlocked) || ((defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_vfwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwprintf_unlocked) || ((defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_fputwc_nolock)) && !defined(__NO_STDSTREAMS))
#include <libc/local/parts.uchar.stdio/c16printf_unlocked.h>
/* >> wprintf_unlocked(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c16printf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBDCALL c16printf_unlocked)(char16_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16printf_unlocked))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c16printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16printf_unlocked))
#endif /* !__cplusplus */
#endif /* ... */
#endif /* !__CRT_HAVE_wprintf_unlocked || __SIZEOF_WCHAR_T__ != 2 || !__VLIBCCALL_IS_VLIBDCALL */
#if defined(__CRT_HAVE_wprintf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
/* >> wprintf_unlocked(3) */
__LIBC __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBKCALL c32printf_unlocked)(char32_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wprintf_unlocked");
#else /* __CRT_HAVE_wprintf_unlocked && __SIZEOF_WCHAR_T__ == 4 && __VLIBCCALL_IS_VLIBKCALL */
#include <__crt.h>
#if (defined(__CRT_HAVE_vwprintf_unlocked) || ((defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS))) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wprintf_unlocked.h>
/* >> wprintf_unlocked(3) */
#define c32printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf_unlocked))
#elif (defined(__CRT_HAVE_vwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vwprintf_unlocked) || ((defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 4) || (((defined(__CRT_HAVE_vfwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwprintf_unlocked) || ((defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc_unlocked) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fputwc_nolock)) && !defined(__NO_STDSTREAMS))
#include <libc/local/parts.uchar.stdio/c32printf_unlocked.h>
/* >> wprintf_unlocked(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c32printf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBKCALL c32printf_unlocked)(char32_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32printf_unlocked))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c32printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32printf_unlocked))
#endif /* !__cplusplus */
#endif /* ... */
#endif /* !__CRT_HAVE_wprintf_unlocked || __SIZEOF_WCHAR_T__ != 4 || !__VLIBCCALL_IS_VLIBKCALL */
#if defined(__CRT_HAVE_vwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> vwprintf_unlocked(3) */
__CREDIRECT(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vc16printf_unlocked,(char16_t const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_DOS$vwprintf_unlocked)
/* >> vwprintf_unlocked(3) */
__CREDIRECT_DOS(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vc16printf_unlocked,(char16_t const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#else /* ... */
#include <__crt.h>
#if (defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/vwprintf_unlocked.h>
/* >> vwprintf_unlocked(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBDCALL vc16printf_unlocked)(char16_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf_unlocked))((__WCHAR_TYPE__ const *)__format, __args); }
#elif ((defined(__CRT_HAVE_vfwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwprintf_unlocked) || ((defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$fputwc_unlocked) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_fputwc_nolock)) && !defined(__NO_STDSTREAMS)
#include <libc/local/parts.uchar.stdio/vc16printf_unlocked.h>
/* >> vwprintf_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vc16printf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBDCALL vc16printf_unlocked)(char16_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc16printf_unlocked))(__format, __args); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_vwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> vwprintf_unlocked(3) */
__CREDIRECT(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vc32printf_unlocked,(char32_t const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_KOS$vwprintf_unlocked)
/* >> vwprintf_unlocked(3) */
__CREDIRECT_KOS(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vc32printf_unlocked,(char32_t const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#else /* ... */
#include <__crt.h>
#if (defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/vwprintf_unlocked.h>
/* >> vwprintf_unlocked(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBKCALL vc32printf_unlocked)(char32_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf_unlocked))((__WCHAR_TYPE__ const *)__format, __args); }
#elif ((defined(__CRT_HAVE_vfwprintf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwprintf_unlocked) || ((defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_file_wprinter_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter_unlocked) || (defined(__CRT_HAVE_file_wprinter) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$file_wprinter) || ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_fputwc_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$fputwc_unlocked) || (defined(__CRT_HAVE__fputwc_nolock) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_fputwc_nolock)) && !defined(__NO_STDSTREAMS)
#include <libc/local/parts.uchar.stdio/vc32printf_unlocked.h>
/* >> vwprintf_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vc32printf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBKCALL vc32printf_unlocked)(char32_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc32printf_unlocked))(__format, __args); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_vfwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> vfwscanf_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc16scanf_unlocked,(__FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwscanf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$vfwscanf_unlocked)
/* >> vfwscanf_unlocked(3) */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc16scanf_unlocked,(__FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwscanf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> vfwscanf_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc16scanf_unlocked,(__FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$vfwscanf)
/* >> vfwscanf_unlocked(3) */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc16scanf_unlocked,(__FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#endif /* ... */
#if defined(__CRT_HAVE_vfwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> vfwscanf_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc32scanf_unlocked,(__FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args),vfwscanf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_KOS$vfwscanf_unlocked)
/* >> vfwscanf_unlocked(3) */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc32scanf_unlocked,(__FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args),vfwscanf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> vfwscanf_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc32scanf_unlocked,(__FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_KOS$vfwscanf)
/* >> vfwscanf_unlocked(3) */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfc32scanf_unlocked,(__FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#endif /* ... */
#if defined(__CRT_HAVE_vwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> vwscanf_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vc16scanf_unlocked,(char16_t const *__restrict __format, __builtin_va_list __args),vwscanf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_DOS$vwscanf_unlocked)
/* >> vwscanf_unlocked(3) */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vc16scanf_unlocked,(char16_t const *__restrict __format, __builtin_va_list __args),vwscanf_unlocked,(__format,__args))
#elif (defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/vwscanf_unlocked.h>
/* >> vwscanf_unlocked(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBDCALL vc16scanf_unlocked)(char16_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf_unlocked))((__WCHAR_TYPE__ const *)__format, __args); }
#elif ((defined(__CRT_HAVE_vfwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwscanf_unlocked) || (defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwscanf)) && !defined(__NO_STDSTREAMS)
#include <libc/local/parts.uchar.stdio/vc16scanf_unlocked.h>
/* >> vwscanf_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vc16scanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBDCALL vc16scanf_unlocked)(char16_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc16scanf_unlocked))(__format, __args); })
#endif /* ... */
#if defined(__CRT_HAVE_vwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> vwscanf_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vc32scanf_unlocked,(char32_t const *__restrict __format, __builtin_va_list __args),vwscanf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_KOS$vwscanf_unlocked)
/* >> vwscanf_unlocked(3) */
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vc32scanf_unlocked,(char32_t const *__restrict __format, __builtin_va_list __args),vwscanf_unlocked,(__format,__args))
#elif (defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/vwscanf_unlocked.h>
/* >> vwscanf_unlocked(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBKCALL vc32scanf_unlocked)(char32_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf_unlocked))((__WCHAR_TYPE__ const *)__format, __args); }
#elif ((defined(__CRT_HAVE_vfwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwscanf_unlocked) || (defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwscanf)) && !defined(__NO_STDSTREAMS)
#include <libc/local/parts.uchar.stdio/vc32scanf_unlocked.h>
/* >> vwscanf_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vc32scanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBKCALL vc32scanf_unlocked)(char32_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc32scanf_unlocked))(__format, __args); })
#endif /* ... */
#if defined(__CRT_HAVE_fwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
/* >> fwscanf_unlocked(3) */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBDCALL fc16scanf_unlocked)(__FILE *__restrict __stream, char16_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwscanf_unlocked");
#elif (defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/fwscanf_unlocked.h>
/* >> fwscanf_unlocked(3) */
#define fc16scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf_unlocked))
#elif (defined(__CRT_HAVE_vfwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwscanf_unlocked) || (defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwscanf)
#include <libc/local/parts.uchar.stdio/fc16scanf_unlocked.h>
/* >> fwscanf_unlocked(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fc16scanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBDCALL fc16scanf_unlocked)(__FILE *__restrict __stream, char16_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc16scanf_unlocked))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fc16scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc16scanf_unlocked))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_fwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
/* >> fwscanf_unlocked(3) */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBKCALL fc32scanf_unlocked)(__FILE *__restrict __stream, char32_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwscanf_unlocked");
#elif (defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/fwscanf_unlocked.h>
/* >> fwscanf_unlocked(3) */
#define fc32scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf_unlocked))
#elif (defined(__CRT_HAVE_vfwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwscanf_unlocked) || (defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwscanf)
#include <libc/local/parts.uchar.stdio/fc32scanf_unlocked.h>
/* >> fwscanf_unlocked(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fc32scanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBKCALL fc32scanf_unlocked)(__FILE *__restrict __stream, char32_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc32scanf_unlocked))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fc32scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc32scanf_unlocked))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wscanf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
/* >> wscanf_unlocked(3) */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBDCALL c16scanf_unlocked)(char16_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wscanf_unlocked");
#elif (defined(__CRT_HAVE_vwscanf_unlocked) || ((defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && !defined(__NO_STDSTREAMS))) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wscanf_unlocked.h>
/* >> wscanf_unlocked(3) */
#define c16scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf_unlocked))
#elif (defined(__CRT_HAVE_vwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vwscanf_unlocked) || ((defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 2) || (((defined(__CRT_HAVE_vfwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwscanf_unlocked) || (defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$vfwscanf)) && !defined(__NO_STDSTREAMS))
#include <libc/local/parts.uchar.stdio/c16scanf_unlocked.h>
/* >> wscanf_unlocked(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c16scanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBDCALL c16scanf_unlocked)(char16_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scanf_unlocked))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c16scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scanf_unlocked))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wscanf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
/* >> wscanf_unlocked(3) */
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBKCALL c32scanf_unlocked)(char32_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wscanf_unlocked");
#elif (defined(__CRT_HAVE_vwscanf_unlocked) || ((defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && !defined(__NO_STDSTREAMS))) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wscanf_unlocked.h>
/* >> wscanf_unlocked(3) */
#define c32scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf_unlocked))
#elif (defined(__CRT_HAVE_vwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vwscanf_unlocked) || ((defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && !defined(__NO_STDSTREAMS) && __SIZEOF_WCHAR_T__ == 4) || (((defined(__CRT_HAVE_vfwscanf_unlocked) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwscanf_unlocked) || (defined(__CRT_HAVE_vfwscanf) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$vfwscanf)) && !defined(__NO_STDSTREAMS))
#include <libc/local/parts.uchar.stdio/c32scanf_unlocked.h>
/* >> wscanf_unlocked(3) */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c32scanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBKCALL c32scanf_unlocked)(char32_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scanf_unlocked))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c32scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scanf_unlocked))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wremove) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16remove,(char16_t const *__filename),wremove,(__filename))
#elif defined(__CRT_HAVE_DOS$wremove)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16remove,(char16_t const *__filename),wremove,(__filename))
#elif defined(__CRT_HAVE__wremove) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16remove,(char16_t const *__filename),_wremove,(__filename))
#elif defined(__CRT_HAVE_DOS$_wremove)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c16remove,(char16_t const *__filename),_wremove,(__filename))
#endif /* ... */
#if defined(__CRT_HAVE_wremove) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32remove,(char32_t const *__filename),wremove,(__filename))
#elif defined(__CRT_HAVE_KOS$wremove)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32remove,(char32_t const *__filename),wremove,(__filename))
#elif defined(__CRT_HAVE__wremove) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32remove,(char32_t const *__filename),_wremove,(__filename))
#elif defined(__CRT_HAVE_KOS$_wremove)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,c32remove,(char32_t const *__filename),_wremove,(__filename))
#endif /* ... */
#if defined(__CRT_HAVE_wfopen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c16fopen,(char16_t const *__filename, char16_t const *__mode),wfopen,(__filename,__mode))
#elif defined(__CRT_HAVE_DOS$wfopen)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c16fopen,(char16_t const *__filename, char16_t const *__mode),wfopen,(__filename,__mode))
#elif defined(__CRT_HAVE__wfopen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c16fopen,(char16_t const *__filename, char16_t const *__mode),_wfopen,(__filename,__mode))
#elif defined(__CRT_HAVE_DOS$_wfopen)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c16fopen,(char16_t const *__filename, char16_t const *__mode),_wfopen,(__filename,__mode))
#endif /* ... */
#if defined(__CRT_HAVE_wfopen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c32fopen,(char32_t const *__filename, char32_t const *__mode),wfopen,(__filename,__mode))
#elif defined(__CRT_HAVE_KOS$wfopen)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c32fopen,(char32_t const *__filename, char32_t const *__mode),wfopen,(__filename,__mode))
#elif defined(__CRT_HAVE__wfopen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c32fopen,(char32_t const *__filename, char32_t const *__mode),_wfopen,(__filename,__mode))
#elif defined(__CRT_HAVE_KOS$_wfopen)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c32fopen,(char32_t const *__filename, char32_t const *__mode),_wfopen,(__filename,__mode))
#endif /* ... */
#if defined(__CRT_HAVE_wfreopen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c16freopen,(char16_t const *__filename, char16_t const *__mode, __FILE *__stream),wfreopen,(__filename,__mode,__stream))
#elif defined(__CRT_HAVE_DOS$wfreopen)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c16freopen,(char16_t const *__filename, char16_t const *__mode, __FILE *__stream),wfreopen,(__filename,__mode,__stream))
#elif defined(__CRT_HAVE__wfreopen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c16freopen,(char16_t const *__filename, char16_t const *__mode, __FILE *__stream),_wfreopen,(__filename,__mode,__stream))
#elif defined(__CRT_HAVE_DOS$_wfreopen)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c16freopen,(char16_t const *__filename, char16_t const *__mode, __FILE *__stream),_wfreopen,(__filename,__mode,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_wfreopen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c32freopen,(char32_t const *__filename, char32_t const *__mode, __FILE *__stream),wfreopen,(__filename,__mode,__stream))
#elif defined(__CRT_HAVE_KOS$wfreopen)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c32freopen,(char32_t const *__filename, char32_t const *__mode, __FILE *__stream),wfreopen,(__filename,__mode,__stream))
#elif defined(__CRT_HAVE__wfreopen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c32freopen,(char32_t const *__filename, char32_t const *__mode, __FILE *__stream),_wfreopen,(__filename,__mode,__stream))
#elif defined(__CRT_HAVE_KOS$_wfreopen)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c32freopen,(char32_t const *__filename, char32_t const *__mode, __FILE *__stream),_wfreopen,(__filename,__mode,__stream))
#endif /* ... */
#if defined(__CRT_HAVE_wpopen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c16popen,(char16_t const *__command, char16_t const *__mode),wpopen,(__command,__mode))
#elif defined(__CRT_HAVE_DOS$wpopen)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c16popen,(char16_t const *__command, char16_t const *__mode),wpopen,(__command,__mode))
#elif defined(__CRT_HAVE__wpopen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c16popen,(char16_t const *__command, char16_t const *__mode),_wpopen,(__command,__mode))
#elif defined(__CRT_HAVE_DOS$_wpopen)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c16popen,(char16_t const *__command, char16_t const *__mode),_wpopen,(__command,__mode))
#endif /* ... */
#if defined(__CRT_HAVE_wpopen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c32popen,(char32_t const *__command, char32_t const *__mode),wpopen,(__command,__mode))
#elif defined(__CRT_HAVE_KOS$wpopen)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c32popen,(char32_t const *__command, char32_t const *__mode),wpopen,(__command,__mode))
#elif defined(__CRT_HAVE__wpopen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c32popen,(char32_t const *__command, char32_t const *__mode),_wpopen,(__command,__mode))
#elif defined(__CRT_HAVE_KOS$_wpopen)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,c32popen,(char32_t const *__command, char32_t const *__mode),_wpopen,(__command,__mode))
#endif /* ... */
#endif /* __USE_KOS */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_UCHAR_STDIO_H */
