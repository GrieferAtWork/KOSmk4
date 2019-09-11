/* HASH 0xe57c45ba */
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
#ifndef _PARTS_UCHAR_STDIO_H
#define _PARTS_UCHAR_STDIO_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _STDIO_H
#include <stdio.h>
#endif /* !_STDIO_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__CRT_HAVE_getwchar) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(,wint_t,__NOTHROW_NCX,getchar16,(void),getwchar,())
#elif defined(__CRT_HAVE_DOS$getwchar)
__CREDIRECT_DOS(,wint_t,__NOTHROW_NCX,getchar16,(void),getwchar,())
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc))
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/getwchar.h>
__FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL getchar16)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar))(); }
#else /* LIBC: getchar16 */
#include <local/wchar/getchar16.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getchar16, __FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL getchar16)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar16))(); })
#endif /* LIBC: getchar16 */
#endif /* getchar16... */
#if defined(__CRT_HAVE_getwchar) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(,wint_t,__NOTHROW_NCX,getchar32,(void),getwchar,())
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc))
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/getwchar.h>
__FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL getchar32)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar))(); }
#else /* LIBC: getchar32 */
#include <local/wchar/getchar32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getchar32, __FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL getchar32)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar32))(); })
#endif /* LIBC: getchar32 */
#endif /* getchar32... */
#if defined(__CRT_HAVE_fgetwc) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,fgetc16,(FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_getwc) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,fgetc16,(FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_DOS$getwc)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,fgetc16,(FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,fgetc16,(FILE *__restrict __stream),fgetwc,(__stream))
#endif /* fgetc16... */
#if defined(__CRT_HAVE_fgetwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,fgetc32,(FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_getwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,fgetc32,(FILE *__restrict __stream),getwc,(__stream))
#endif /* fgetc32... */
#if defined(__CRT_HAVE_getwc) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,getc16,(FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_fgetwc) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,getc16,(FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,getc16,(FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_DOS$getwc)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,getc16,(FILE *__restrict __stream),getwc,(__stream))
#endif /* getc16... */
#if defined(__CRT_HAVE_getwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,getc32,(FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_fgetwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,getc32,(FILE *__restrict __stream),fgetwc,(__stream))
#endif /* getc32... */
#if defined(__CRT_HAVE_putwchar) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(,wint_t,__NOTHROW_NCX,putchar16,(char16_t __wc),putwchar,(__wc))
#elif defined(__CRT_HAVE_DOS$putwchar)
__CREDIRECT_DOS(,wint_t,__NOTHROW_NCX,putchar16,(char16_t __wc),putwchar,(__wc))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc))
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/putwchar.h>
__FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL putchar16)(char16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar))((__WCHAR_TYPE__)__wc); }
#else /* LIBC: putchar16 */
#include <local/wchar/putchar16.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(putchar16, __FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL putchar16)(char16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar16))(__wc); })
#endif /* LIBC: putchar16 */
#endif /* putchar16... */
#if defined(__CRT_HAVE_putwchar) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(,wint_t,__NOTHROW_NCX,putchar32,(char32_t __wc),putwchar,(__wc))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc))
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/putwchar.h>
__FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL putchar32)(char32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar))((__WCHAR_TYPE__)__wc); }
#else /* LIBC: putchar32 */
#include <local/wchar/putchar32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(putchar32, __FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL putchar32)(char32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar32))(__wc); })
#endif /* LIBC: putchar32 */
#endif /* putchar32... */
#if defined(__CRT_HAVE_fputwc) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,fputc16,(char16_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,fputc16,(char16_t __wc, FILE *__stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$putwc)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,fputc16,(char16_t __wc, FILE *__stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$fputwc)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,fputc16,(char16_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#endif /* fputc16... */
#if defined(__CRT_HAVE_fputwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,fputc32,(char32_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,fputc32,(char32_t __wc, FILE *__stream),putwc,(__wc,__stream))
#endif /* fputc32... */
#if defined(__CRT_HAVE_putwc) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,putc16,(char16_t __wc, FILE *__stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,putc16,(char16_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$fputwc)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,putc16,(char16_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$putwc)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,putc16,(char16_t __wc, FILE *__stream),putwc,(__wc,__stream))
#endif /* putc16... */
#if defined(__CRT_HAVE_putwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,putc32,(char32_t __wc, FILE *__stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,putc32,(char32_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#endif /* putc32... */
#if defined(__CRT_HAVE_fgetws) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__NOTHROW_NCX,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws_unlocked) && (defined(__USE_STDIO_UNLOCKED) && (__SIZEOF_WCHAR_T__ == 2))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__NOTHROW_NCX,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock) && (defined(__USE_STDIO_UNLOCKED) && (__SIZEOF_WCHAR_T__ == 2))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__NOTHROW_NCX,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$fgetws_unlocked) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__NOTHROW_NCX,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$_fgetws_nolock) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__NOTHROW_NCX,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__NOTHROW_NCX,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__NOTHROW_NCX,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$fgetws_unlocked)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__NOTHROW_NCX,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$_fgetws_nolock)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__NOTHROW_NCX,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$fgetws)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char16_t *,__NOTHROW_NCX,fgetc16s,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE_ferror_unlocked))
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fgetws.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) char16_t *__NOTHROW_NCX(__LIBCCALL fgetc16s)(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetws))((__WCHAR_TYPE__ *)__buf, __bufsize, __stream); }
#else /* LIBC: fgetc16s */
#include <local/wchar/fgetc16s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetc16s, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) char16_t *__NOTHROW_NCX(__LIBCCALL fgetc16s)(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc16s))(__buf, __bufsize, __stream); })
#endif /* LIBC: fgetc16s */
#endif /* fgetc16s... */
#if defined(__CRT_HAVE_fgetws) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char32_t *,__NOTHROW_NCX,fgetc32s,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws_unlocked) && (defined(__USE_STDIO_UNLOCKED) && (__SIZEOF_WCHAR_T__ == 4))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char32_t *,__NOTHROW_NCX,fgetc32s,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock) && (defined(__USE_STDIO_UNLOCKED) && (__SIZEOF_WCHAR_T__ == 4))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char32_t *,__NOTHROW_NCX,fgetc32s,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char32_t *,__NOTHROW_NCX,fgetc32s,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),char32_t *,__NOTHROW_NCX,fgetc32s,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE_ferror_unlocked))
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fgetws.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) char32_t *__NOTHROW_NCX(__LIBCCALL fgetc32s)(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetws))((__WCHAR_TYPE__ *)__buf, __bufsize, __stream); }
#else /* LIBC: fgetc32s */
#include <local/wchar/fgetc32s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetc32s, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) char32_t *__NOTHROW_NCX(__LIBCCALL fgetc32s)(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc32s))(__buf, __bufsize, __stream); })
#endif /* LIBC: fgetc32s */
#endif /* fgetc32s... */
#if defined(__CRT_HAVE_fputws) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc16s,(char16_t const *__restrict __string, FILE *__restrict __stream),fputws,(__string,__stream))
#elif defined(__CRT_HAVE_fputws_unlocked) && (defined(__USE_STDIO_UNLOCKED) && (__SIZEOF_WCHAR_T__ == 2))
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc16s,(char16_t const *__restrict __string, FILE *__restrict __stream),fputws_unlocked,(__string,__stream))
#elif defined(__CRT_HAVE__fputws_nolock) && (defined(__USE_STDIO_UNLOCKED) && (__SIZEOF_WCHAR_T__ == 2))
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc16s,(char16_t const *__restrict __string, FILE *__restrict __stream),_fputws_nolock,(__string,__stream))
#elif defined(__CRT_HAVE_DOS$fputws_unlocked) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc16s,(char16_t const *__restrict __string, FILE *__restrict __stream),fputws_unlocked,(__string,__stream))
#elif defined(__CRT_HAVE_DOS$_fputws_nolock) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc16s,(char16_t const *__restrict __string, FILE *__restrict __stream),_fputws_nolock,(__string,__stream))
#elif defined(__CRT_HAVE_fputws_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc16s,(char16_t const *__restrict __string, FILE *__restrict __stream),fputws_unlocked,(__string,__stream))
#elif defined(__CRT_HAVE__fputws_nolock) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc16s,(char16_t const *__restrict __string, FILE *__restrict __stream),_fputws_nolock,(__string,__stream))
#elif defined(__CRT_HAVE_DOS$fputws_unlocked)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc16s,(char16_t const *__restrict __string, FILE *__restrict __stream),fputws_unlocked,(__string,__stream))
#elif defined(__CRT_HAVE_DOS$_fputws_nolock)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc16s,(char16_t const *__restrict __string, FILE *__restrict __stream),_fputws_nolock,(__string,__stream))
#elif defined(__CRT_HAVE_DOS$fputws)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc16s,(char16_t const *__restrict __string, FILE *__restrict __stream),fputws,(__string,__stream))
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fputws.h>
__FORCELOCAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL fputc16s)(char16_t const *__restrict __string, FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputws))((__WCHAR_TYPE__ const *)__string, __stream); }
#else /* LIBC: fputc16s */
#include <local/wchar/fputc16s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fputc16s, __FORCELOCAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL fputc16s)(char16_t const *__restrict __string, FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc16s))(__string, __stream); })
#endif /* LIBC: fputc16s */
#endif /* fputc16s... */
#if defined(__CRT_HAVE_fputws) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc32s,(char32_t const *__restrict __string, FILE *__restrict __stream),fputws,(__string,__stream))
#elif defined(__CRT_HAVE_fputws_unlocked) && (defined(__USE_STDIO_UNLOCKED) && (__SIZEOF_WCHAR_T__ == 4))
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc32s,(char32_t const *__restrict __string, FILE *__restrict __stream),fputws_unlocked,(__string,__stream))
#elif defined(__CRT_HAVE__fputws_nolock) && (defined(__USE_STDIO_UNLOCKED) && (__SIZEOF_WCHAR_T__ == 4))
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc32s,(char32_t const *__restrict __string, FILE *__restrict __stream),_fputws_nolock,(__string,__stream))
#elif defined(__CRT_HAVE_fputws_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc32s,(char32_t const *__restrict __string, FILE *__restrict __stream),fputws_unlocked,(__string,__stream))
#elif defined(__CRT_HAVE__fputws_nolock) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc32s,(char32_t const *__restrict __string, FILE *__restrict __stream),_fputws_nolock,(__string,__stream))
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fputws.h>
__FORCELOCAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL fputc32s)(char32_t const *__restrict __string, FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputws))((__WCHAR_TYPE__ const *)__string, __stream); }
#else /* LIBC: fputc32s */
#include <local/wchar/fputc32s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fputc32s, __FORCELOCAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL fputc32s)(char32_t const *__restrict __string, FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc32s))(__string, __stream); })
#endif /* LIBC: fputc32s */
#endif /* fputc32s... */
#if defined(__CRT_HAVE_ungetwc) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetc16,(wint_t __wc, FILE *__stream),ungetwc,(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc_unlocked) && (defined(__USE_STDIO_UNLOCKED) && (__SIZEOF_WCHAR_T__ == 2))
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetc16,(wint_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$ungetwc_unlocked) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetc16,(wint_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetc16,(wint_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$ungetwc_unlocked)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetc16,(wint_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$ungetwc)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetc16,(wint_t __wc, FILE *__stream),ungetwc,(__wc,__stream))
#endif /* ungetc16... */
#if defined(__CRT_HAVE_ungetwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetc32,(wint_t __wc, FILE *__stream),ungetwc,(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc_unlocked) && (defined(__USE_STDIO_UNLOCKED) && (__SIZEOF_WCHAR_T__ == 4))
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetc32,(wint_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetc32,(wint_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#endif /* ungetc32... */

#if defined(__USE_ISOC95) || defined(__USE_UNIX98) || defined(__USE_DOS)
#if defined(__CRT_HAVE_fwprintf) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL fc16printf)(FILE *__restrict __stream, char16_t const *__restrict __format, ...) __CASMNAME("fwprintf");
#elif defined(__CRT_HAVE_DOS$fwprintf) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBDCALL fc16printf)(FILE *__restrict __stream, char16_t const *__restrict __format, ...) __CASMNAME_DOS("fwprintf");
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fwprintf.h>
#define fc16printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf))
#else /* LIBC: fc16printf */
#include <local/wchar/fc16printf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(fc16printf)
#else /* __cplusplus */
#define fc16printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc16printf))
#endif /* !__cplusplus */
#endif /* LIBC: fc16printf */
#endif /* fc16printf... */
#if defined(__CRT_HAVE_fwprintf) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL fc32printf)(FILE *__restrict __stream, char32_t const *__restrict __format, ...) __CASMNAME("fwprintf");
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fwprintf.h>
#define fc32printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf))
#else /* LIBC: fc32printf */
#include <local/wchar/fc32printf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(fc32printf)
#else /* __cplusplus */
#define fc32printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc32printf))
#endif /* !__cplusplus */
#endif /* LIBC: fc32printf */
#endif /* fc32printf... */
#if defined(__CRT_HAVE_vfwprintf) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vfc16printf,(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$vfwprintf)
__CREDIRECT_DOS(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vfc16printf,(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/vfwprintf.h>
__FORCELOCAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vfc16printf)(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf))(__stream, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: vfc16printf */
#include <local/wchar/vfc16printf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vfc16printf, __FORCELOCAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vfc16printf)(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfc16printf))(__stream, __format, __args); })
#endif /* LIBC: vfc16printf */
#endif /* vfc16printf... */
#if defined(__CRT_HAVE_vfwprintf) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vfc32printf,(FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/vfwprintf.h>
__FORCELOCAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vfc32printf)(FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf))(__stream, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: vfc32printf */
#include <local/wchar/vfc32printf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vfc32printf, __FORCELOCAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vfc32printf)(FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfc32printf))(__stream, __format, __args); })
#endif /* LIBC: vfc32printf */
#endif /* vfc32printf... */
#if defined(__CRT_HAVE_wprintf) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL c16printf)(char16_t const *__restrict __format, ...) __CASMNAME("wprintf");
#elif defined(__CRT_HAVE_DOS$wprintf) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBDCALL c16printf)(char16_t const *__restrict __format, ...) __CASMNAME_DOS("wprintf");
#elif ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS) || defined(__CRT_HAVE_vwprintf))
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wprintf.h>
#define c16printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf))
#else /* LIBC: c16printf */
#include <local/wchar/c16printf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16printf)
#else /* __cplusplus */
#define c16printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16printf))
#endif /* !__cplusplus */
#endif /* LIBC: c16printf */
#endif /* c16printf... */
#if defined(__CRT_HAVE_wprintf) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL c32printf)(char32_t const *__restrict __format, ...) __CASMNAME("wprintf");
#elif ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS) || defined(__CRT_HAVE_vwprintf))
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wprintf.h>
#define c32printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf))
#else /* LIBC: c32printf */
#include <local/wchar/c32printf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32printf)
#else /* __cplusplus */
#define c32printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32printf))
#endif /* !__cplusplus */
#endif /* LIBC: c32printf */
#endif /* c32printf... */
#if defined(__CRT_HAVE_vwprintf) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vc16printf,(char16_t const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args))
#elif defined(__CRT_HAVE_DOS$vwprintf)
__CREDIRECT_DOS(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vc16printf,(char16_t const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args))
#elif (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/vwprintf.h>
__FORCELOCAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vc16printf)(char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf))((__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: vc16printf */
#include <local/wchar/vc16printf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vc16printf, __FORCELOCAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vc16printf)(char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc16printf))(__format, __args); })
#endif /* LIBC: vc16printf */
#endif /* vc16printf... */
#if defined(__CRT_HAVE_vwprintf) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vc32printf,(char32_t const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args))
#elif (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/vwprintf.h>
__FORCELOCAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vc32printf)(char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf))((__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: vc32printf */
#include <local/wchar/vc32printf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vc32printf, __FORCELOCAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vc32printf)(char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc32printf))(__format, __args); })
#endif /* LIBC: vc32printf */
#endif /* vc32printf... */
#if defined(__CRT_HAVE_fwscanf) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL fc16scanf)(FILE *__restrict __stream, char16_t const *__restrict __format, ...) __CASMNAME("fwscanf");
#elif defined(__CRT_HAVE_DOS$fwscanf) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBDCALL fc16scanf)(FILE *__restrict __stream, char16_t const *__restrict __format, ...) __CASMNAME_DOS("fwscanf");
#elif defined(__CRT_HAVE_vfwscanf)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fwscanf.h>
#define fc16scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf))
#else /* LIBC: fc16scanf */
#include <local/wchar/fc16scanf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(fc16scanf)
#else /* __cplusplus */
#define fc16scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc16scanf))
#endif /* !__cplusplus */
#endif /* LIBC: fc16scanf */
#endif /* fc16scanf... */
#if defined(__CRT_HAVE_fwscanf) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL fc32scanf)(FILE *__restrict __stream, char32_t const *__restrict __format, ...) __CASMNAME("fwscanf");
#elif defined(__CRT_HAVE_vfwscanf)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fwscanf.h>
#define fc32scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf))
#else /* LIBC: fc32scanf */
#include <local/wchar/fc32scanf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(fc32scanf)
#else /* __cplusplus */
#define fc32scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc32scanf))
#endif /* !__cplusplus */
#endif /* LIBC: fc32scanf */
#endif /* fc32scanf... */
#if defined(__CRT_HAVE_wscanf) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WSCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL c16scanf)(char16_t const *__restrict __format, ...) __CASMNAME("wscanf");
#elif defined(__CRT_HAVE_DOS$wscanf) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WSCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBDCALL c16scanf)(char16_t const *__restrict __format, ...) __CASMNAME_DOS("wscanf");
#elif (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS) || defined(__CRT_HAVE_vwscanf))
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wscanf.h>
#define c16scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf))
#else /* LIBC: c16scanf */
#include <local/wchar/c16scanf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16scanf)
#else /* __cplusplus */
#define c16scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scanf))
#endif /* !__cplusplus */
#endif /* LIBC: c16scanf */
#endif /* c16scanf... */
#if defined(__CRT_HAVE_wscanf) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WSCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL c32scanf)(char32_t const *__restrict __format, ...) __CASMNAME("wscanf");
#elif (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS) || defined(__CRT_HAVE_vwscanf))
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wscanf.h>
#define c32scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf))
#else /* LIBC: c32scanf */
#include <local/wchar/c32scanf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32scanf)
#else /* __cplusplus */
#define c32scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scanf))
#endif /* !__cplusplus */
#endif /* LIBC: c32scanf */
#endif /* c32scanf... */
#if defined(__CRT_HAVE_swscanf) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sc16scanf)(char16_t const *__restrict __src, char16_t const *__restrict __format, ...) __CASMNAME("swscanf");
#elif defined(__CRT_HAVE_DOS$swscanf) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBDCALL sc16scanf)(char16_t const *__restrict __src, char16_t const *__restrict __format, ...) __CASMNAME_DOS("swscanf");
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/swscanf.h>
#define sc16scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swscanf))
#else /* LIBC: sc16scanf */
#include <local/wchar/sc16scanf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(sc16scanf)
#else /* __cplusplus */
#define sc16scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sc16scanf))
#endif /* !__cplusplus */
#endif /* sc16scanf... */
#if defined(__CRT_HAVE_swscanf) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sc32scanf)(char32_t const *__restrict __src, char32_t const *__restrict __format, ...) __CASMNAME("swscanf");
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/swscanf.h>
#define sc32scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swscanf))
#else /* LIBC: sc32scanf */
#include <local/wchar/sc32scanf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(sc32scanf)
#else /* __cplusplus */
#define sc32scanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sc32scanf))
#endif /* !__cplusplus */
#endif /* sc32scanf... */
#if defined(__CRT_HAVE_vswprintf) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1, 3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsc16printf,(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#elif defined(__CRT_HAVE_DOS$vswprintf)
__CREDIRECT_DOS(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1, 3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsc16printf,(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/vswprintf.h>
__FORCELOCAL __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsc16printf)(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswprintf))((__WCHAR_TYPE__ *)__buf, __buflen, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: vsc16printf */
#include <local/wchar/vsc16printf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vsc16printf, __FORCELOCAL __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsc16printf)(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsc16printf))(__buf, __buflen, __format, __args); })
#endif /* vsc16printf... */
#if defined(__CRT_HAVE_vswprintf) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1, 3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsc32printf,(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/vswprintf.h>
__FORCELOCAL __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsc32printf)(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswprintf))((__WCHAR_TYPE__ *)__buf, __buflen, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: vsc32printf */
#include <local/wchar/vsc32printf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vsc32printf, __FORCELOCAL __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsc32printf)(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsc32printf))(__buf, __buflen, __format, __args); })
#endif /* vsc32printf... */
#if defined(__CRT_HAVE_swprintf) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sc16printf)(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, ...) __CASMNAME("swprintf");
#elif defined(__CRT_HAVE_DOS$swprintf) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBDCALL sc16printf)(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, ...) __CASMNAME_DOS("swprintf");
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/swprintf.h>
#define sc16printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swprintf))
#else /* LIBC: sc16printf */
#include <local/wchar/sc16printf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(sc16printf)
#else /* __cplusplus */
#define sc16printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sc16printf))
#endif /* !__cplusplus */
#endif /* sc16printf... */
#if defined(__CRT_HAVE_swprintf) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL sc32printf)(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, ...) __CASMNAME("swprintf");
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/swprintf.h>
#define sc32printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swprintf))
#else /* LIBC: sc32printf */
#include <local/wchar/sc32printf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(sc32printf)
#else /* __cplusplus */
#define sc32printf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sc32printf))
#endif /* !__cplusplus */
#endif /* sc32printf... */
#endif /* __USE_ISOC95 || __USE_UNIX98 || __USE_DOS */

#ifdef __USE_ISOC99
#if defined(__CRT_HAVE_vfwscanf) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vfc16scanf,(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$vfwscanf)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vfc16scanf,(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#endif /* vfc16scanf... */
#if defined(__CRT_HAVE_vfwscanf) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vfc32scanf,(FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#endif /* vfc32scanf... */
#if defined(__CRT_HAVE_vwscanf) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vc16scanf,(char16_t const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#elif defined(__CRT_HAVE_DOS$vwscanf)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vc16scanf,(char16_t const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#elif defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/vwscanf.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vc16scanf)(char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf))((__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: vc16scanf */
#include <local/wchar/vc16scanf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vc16scanf, __FORCELOCAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vc16scanf)(char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc16scanf))(__format, __args); })
#endif /* LIBC: vc16scanf */
#endif /* vc16scanf... */
#if defined(__CRT_HAVE_vwscanf) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vc32scanf,(char32_t const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#elif defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/vwscanf.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vc32scanf)(char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf))((__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: vc32scanf */
#include <local/wchar/vc32scanf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vc32scanf, __FORCELOCAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vc32scanf)(char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc32scanf))(__format, __args); })
#endif /* LIBC: vc32scanf */
#endif /* vc32scanf... */
#if defined(__CRT_HAVE_vswscanf) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsc16scanf,(char16_t const *__restrict __src, char16_t const *__restrict __format, __builtin_va_list __args),vswscanf,(__src,__format,__args))
#elif defined(__CRT_HAVE_DOS$vswscanf)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsc16scanf,(char16_t const *__restrict __src, char16_t const *__restrict __format, __builtin_va_list __args),vswscanf,(__src,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/vswscanf.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsc16scanf)(char16_t const *__restrict __src, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswscanf))((__WCHAR_TYPE__ const *)__src, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: vsc16scanf */
#include <local/wchar/vsc16scanf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vsc16scanf, __FORCELOCAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsc16scanf)(char16_t const *__restrict __src, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsc16scanf))(__src, __format, __args); })
#endif /* vsc16scanf... */
#if defined(__CRT_HAVE_vswscanf) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsc32scanf,(char32_t const *__restrict __src, char32_t const *__restrict __format, __builtin_va_list __args),vswscanf,(__src,__format,__args))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/vswscanf.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsc32scanf)(char32_t const *__restrict __src, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswscanf))((__WCHAR_TYPE__ const *)__src, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: vsc32scanf */
#include <local/wchar/vsc32scanf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vsc32scanf, __FORCELOCAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsc32scanf)(char32_t const *__restrict __src, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsc32scanf))(__src, __format, __args); })
#endif /* vsc32scanf... */
#endif /* __USE_ISOC99 */

#ifdef __USE_GNU
#if defined(__CRT_HAVE_getwchar_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(,wint_t,__NOTHROW_NCX,getchar16_unlocked,(void),getwchar_unlocked,())
#elif defined(__CRT_HAVE__getwchar_nolock) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(,wint_t,__NOTHROW_NCX,getchar16_unlocked,(void),_getwchar_nolock,())
#elif defined(__CRT_HAVE_DOS$_getwchar_nolock)
__CREDIRECT_DOS(,wint_t,__NOTHROW_NCX,getchar16_unlocked,(void),_getwchar_nolock,())
#elif defined(__CRT_HAVE_DOS$getwchar_unlocked)
__CREDIRECT_DOS(,wint_t,__NOTHROW_NCX,getchar16_unlocked,(void),getwchar_unlocked,())
#elif (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE__fgetwc_nolock)) && !defined(__NO_STDSTREAMS)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/getwchar_unlocked.h>
__FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL getchar16_unlocked)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar_unlocked))(); }
#else /* LIBC: getchar16_unlocked */
#include <local/wchar/getchar16_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getchar16_unlocked, __FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL getchar16_unlocked)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar16_unlocked))(); })
#endif /* LIBC: getchar16_unlocked */
#endif /* getchar16_unlocked... */
#if defined(__CRT_HAVE_getwchar_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(,wint_t,__NOTHROW_NCX,getchar32_unlocked,(void),getwchar_unlocked,())
#elif defined(__CRT_HAVE__getwchar_nolock) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(,wint_t,__NOTHROW_NCX,getchar32_unlocked,(void),_getwchar_nolock,())
#elif (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE__fgetwc_nolock)) && !defined(__NO_STDSTREAMS)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/getwchar_unlocked.h>
__FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL getchar32_unlocked)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar_unlocked))(); }
#else /* LIBC: getchar32_unlocked */
#include <local/wchar/getchar32_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getchar32_unlocked, __FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL getchar32_unlocked)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getchar32_unlocked))(); })
#endif /* LIBC: getchar32_unlocked */
#endif /* getchar32_unlocked... */
#if defined(__CRT_HAVE_putwchar_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(,wint_t,__NOTHROW_NCX,putchar16_unlocked,(char16_t __wc),putwchar_unlocked,(__wc))
#elif defined(__CRT_HAVE__putwchar_nolock) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(,wint_t,__NOTHROW_NCX,putchar16_unlocked,(char16_t __wc),_putwchar_nolock,(__wc))
#elif defined(__CRT_HAVE_DOS$_putwchar_nolock)
__CREDIRECT_DOS(,wint_t,__NOTHROW_NCX,putchar16_unlocked,(char16_t __wc),_putwchar_nolock,(__wc))
#elif defined(__CRT_HAVE_DOS$putwchar_unlocked)
__CREDIRECT_DOS(,wint_t,__NOTHROW_NCX,putchar16_unlocked,(char16_t __wc),putwchar_unlocked,(__wc))
#elif (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/putwchar_unlocked.h>
__FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL putchar16_unlocked)(char16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar_unlocked))((__WCHAR_TYPE__)__wc); }
#else /* LIBC: putchar16_unlocked */
#include <local/wchar/putchar16_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(putchar16_unlocked, __FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL putchar16_unlocked)(char16_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar16_unlocked))(__wc); })
#endif /* LIBC: putchar16_unlocked */
#endif /* putchar16_unlocked... */
#if defined(__CRT_HAVE_putwchar_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(,wint_t,__NOTHROW_NCX,putchar32_unlocked,(char32_t __wc),putwchar_unlocked,(__wc))
#elif defined(__CRT_HAVE__putwchar_nolock) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(,wint_t,__NOTHROW_NCX,putchar32_unlocked,(char32_t __wc),_putwchar_nolock,(__wc))
#elif (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/putwchar_unlocked.h>
__FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL putchar32_unlocked)(char32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar_unlocked))((__WCHAR_TYPE__)__wc); }
#else /* LIBC: putchar32_unlocked */
#include <local/wchar/putchar32_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(putchar32_unlocked, __FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL putchar32_unlocked)(char32_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putchar32_unlocked))(__wc); })
#endif /* LIBC: putchar32_unlocked */
#endif /* putchar32_unlocked... */
#if defined(__CRT_HAVE_getwc_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,getc16_unlocked,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_fgetwc_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,getc16_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,getc16_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc_unlocked)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,getc16_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_DOS$_fgetwc_nolock)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,getc16_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_DOS$getwc_unlocked)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,getc16_unlocked,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#endif /* getc16_unlocked... */
#if defined(__CRT_HAVE_getwc_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,getc32_unlocked,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_fgetwc_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,getc32_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,getc32_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#endif /* getc32_unlocked... */
#if defined(__CRT_HAVE_fgetwc_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,fgetc16_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,fgetc16_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_DOS$_fgetwc_nolock)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,fgetc16_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_DOS$fgetwc_unlocked)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,fgetc16_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#endif /* fgetc16_unlocked... */
#if defined(__CRT_HAVE_fgetwc_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,fgetc32_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__NOTHROW_NCX,fgetc32_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#endif /* fgetc32_unlocked... */
#if defined(__CRT_HAVE_putwc_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,putc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),putwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,putc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,putc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$fputwc_unlocked)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,putc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$_fputwc_nolock)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,putc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$putwc_unlocked)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,putc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),putwc_unlocked,(__wc,__stream))
#endif /* putc16_unlocked... */
#if defined(__CRT_HAVE_putwc_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,putc32_unlocked,(char32_t __wc, __FILE *__restrict __stream),putwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,putc32_unlocked,(char32_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,putc32_unlocked,(char32_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#endif /* putc32_unlocked... */
#if defined(__CRT_HAVE_fputwc_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,fputc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,fputc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$_fputwc_nolock)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,fputc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_DOS$fputwc_unlocked)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,fputc16_unlocked,(char16_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#endif /* fputc16_unlocked... */
#if defined(__CRT_HAVE_fputwc_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,fputc32_unlocked,(char32_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,fputc32_unlocked,(char32_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#endif /* fputc32_unlocked... */
#if defined(__CRT_HAVE_fgetws_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1, 3)),char16_t *,__NOTHROW_NCX,fgetc16s_unlocked,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1, 3)),char16_t *,__NOTHROW_NCX,fgetc16s_unlocked,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1, 3)),char16_t *,__NOTHROW_NCX,fgetc16s_unlocked,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$fgetws)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 3)),char16_t *,__NOTHROW_NCX,fgetc16s_unlocked,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$_fgetws_nolock)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 3)),char16_t *,__NOTHROW_NCX,fgetc16s_unlocked,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_DOS$fgetws_unlocked)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 3)),char16_t *,__NOTHROW_NCX,fgetc16s_unlocked,(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE__fgetwc_nolock)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE_ungetwc)) && (defined(__CRT_HAVE_ferror_unlocked) || defined(__CRT_HAVE_ferror))
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fgetws_unlocked.h>
__FORCELOCAL __ATTR_NONNULL((1, 3)) char16_t *__NOTHROW_NCX(__LIBCCALL fgetc16s_unlocked)(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) { return (char16_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetws_unlocked))((__WCHAR_TYPE__ *)__buf, __bufsize, __stream); }
#else /* LIBC: fgetc16s_unlocked */
#include <local/wchar/fgetc16s_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetc16s_unlocked, __FORCELOCAL __ATTR_NONNULL((1, 3)) char16_t *__NOTHROW_NCX(__LIBCCALL fgetc16s_unlocked)(char16_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc16s_unlocked))(__buf, __bufsize, __stream); })
#endif /* LIBC: fgetc16s_unlocked */
#endif /* fgetc16s_unlocked... */
#if defined(__CRT_HAVE_fgetws_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1, 3)),char32_t *,__NOTHROW_NCX,fgetc32s_unlocked,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1, 3)),char32_t *,__NOTHROW_NCX,fgetc32s_unlocked,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1, 3)),char32_t *,__NOTHROW_NCX,fgetc32s_unlocked,(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE__fgetwc_nolock)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE_ungetwc)) && (defined(__CRT_HAVE_ferror_unlocked) || defined(__CRT_HAVE_ferror))
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fgetws_unlocked.h>
__FORCELOCAL __ATTR_NONNULL((1, 3)) char32_t *__NOTHROW_NCX(__LIBCCALL fgetc32s_unlocked)(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) { return (char32_t *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetws_unlocked))((__WCHAR_TYPE__ *)__buf, __bufsize, __stream); }
#else /* LIBC: fgetc32s_unlocked */
#include <local/wchar/fgetc32s_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetc32s_unlocked, __FORCELOCAL __ATTR_NONNULL((1, 3)) char32_t *__NOTHROW_NCX(__LIBCCALL fgetc32s_unlocked)(char32_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc32s_unlocked))(__buf, __bufsize, __stream); })
#endif /* LIBC: fgetc32s_unlocked */
#endif /* fgetc32s_unlocked... */
#if defined(__CRT_HAVE_fputws_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc16s_unlocked,(char16_t const *__restrict __string, __FILE *__restrict __stream),fputws_unlocked,(__string,__stream))
#elif defined(__CRT_HAVE__fputws_nolock) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc16s_unlocked,(char16_t const *__restrict __string, __FILE *__restrict __stream),_fputws_nolock,(__string,__stream))
#elif defined(__CRT_HAVE_DOS$_fputws_nolock)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc16s_unlocked,(char16_t const *__restrict __string, __FILE *__restrict __stream),_fputws_nolock,(__string,__stream))
#elif defined(__CRT_HAVE_DOS$fputws_unlocked)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc16s_unlocked,(char16_t const *__restrict __string, __FILE *__restrict __stream),fputws_unlocked,(__string,__stream))
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fputws_unlocked.h>
__FORCELOCAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL fputc16s_unlocked)(char16_t const *__restrict __string, __FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputws_unlocked))((__WCHAR_TYPE__ const *)__string, __stream); }
#else /* LIBC: fputc16s_unlocked */
#include <local/wchar/fputc16s_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fputc16s_unlocked, __FORCELOCAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL fputc16s_unlocked)(char16_t const *__restrict __string, __FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc16s_unlocked))(__string, __stream); })
#endif /* LIBC: fputc16s_unlocked */
#endif /* fputc16s_unlocked... */
#if defined(__CRT_HAVE_fputws_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc32s_unlocked,(char32_t const *__restrict __string, __FILE *__restrict __stream),fputws_unlocked,(__string,__stream))
#elif defined(__CRT_HAVE__fputws_nolock) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,fputc32s_unlocked,(char32_t const *__restrict __string, __FILE *__restrict __stream),_fputws_nolock,(__string,__stream))
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fputws_unlocked.h>
__FORCELOCAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL fputc32s_unlocked)(char32_t const *__restrict __string, __FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputws_unlocked))((__WCHAR_TYPE__ const *)__string, __stream); }
#else /* LIBC: fputc32s_unlocked */
#include <local/wchar/fputc32s_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fputc32s_unlocked, __FORCELOCAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL fputc32s_unlocked)(char32_t const *__restrict __string, __FILE *__restrict __stream) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc32s_unlocked))(__string, __stream); })
#endif /* LIBC: fputc32s_unlocked */
#endif /* fputc32s_unlocked... */
#endif /* __USE_GNU */

#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_open_wmemstream) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(,__FILE *,__NOTHROW_NCX,open_c16memstream,(char16_t **__bufloc, size_t *__sizeloc),open_wmemstream,(__bufloc,__sizeloc))
#elif defined(__CRT_HAVE_DOS$open_wmemstream)
__CREDIRECT_DOS(,__FILE *,__NOTHROW_NCX,open_c16memstream,(char16_t **__bufloc, size_t *__sizeloc),open_wmemstream,(__bufloc,__sizeloc))
#endif /* open_c16memstream... */
#if defined(__CRT_HAVE_open_wmemstream) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(,__FILE *,__NOTHROW_NCX,open_c32memstream,(char32_t **__bufloc, size_t *__sizeloc),open_wmemstream,(__bufloc,__sizeloc))
#endif /* open_c32memstream... */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_KOS
#if defined(__CRT_HAVE_file_wprinter) && (__SIZEOF_WCHAR_T__ == 2)
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,file_c16printer,(void *__arg, char16_t const *__restrict __data, size_t __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter_unlocked) && (defined(__USE_STDIO_UNLOCKED) && (__SIZEOF_WCHAR_T__ == 2))
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,file_c16printer,(void *__arg, char16_t const *__restrict __data, size_t __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter_unlocked) && (defined(__USE_STDIO_UNLOCKED))
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,file_c16printer,(void *__arg, char16_t const *__restrict __data, size_t __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,file_c16printer,(void *__arg, char16_t const *__restrict __data, size_t __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter_unlocked)
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,file_c16printer,(void *__arg, char16_t const *__restrict __data, size_t __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter)
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,file_c16printer,(void *__arg, char16_t const *__restrict __data, size_t __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/file_wprinter.h>
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL file_c16printer)(void *__arg, char16_t const *__restrict __data, size_t __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* LIBC: file_c16printer */
#include <local/wchar/file_c16printer.h>
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_c16printer, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL file_c16printer)(void *__arg, char16_t const *__restrict __data, size_t __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_c16printer))(__arg, __data, __datalen); })
#endif /* LIBC: file_c16printer */
#endif /* file_c16printer... */
#if defined(__CRT_HAVE_file_wprinter) && (__SIZEOF_WCHAR_T__ == 4)
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,file_c32printer,(void *__arg, char32_t const *__restrict __data, size_t __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter_unlocked) && (defined(__USE_STDIO_UNLOCKED) && (__SIZEOF_WCHAR_T__ == 4))
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,file_c32printer,(void *__arg, char32_t const *__restrict __data, size_t __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,file_c32printer,(void *__arg, char32_t const *__restrict __data, size_t __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/file_wprinter.h>
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL file_c32printer)(void *__arg, char32_t const *__restrict __data, size_t __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* LIBC: file_c32printer */
#include <local/wchar/file_c32printer.h>
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_c32printer, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL file_c32printer)(void *__arg, char32_t const *__restrict __data, size_t __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_c32printer))(__arg, __data, __datalen); })
#endif /* LIBC: file_c32printer */
#endif /* file_c32printer... */
#if defined(__CRT_HAVE_file_wprinter_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `file_c16printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,file_c16printer_unlocked,(void *__arg, char16_t const *__restrict __data, size_t __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `file_c16printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,file_c16printer_unlocked,(void *__arg, char16_t const *__restrict __data, size_t __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter)
/* Same as `file_c16printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,file_c16printer_unlocked,(void *__arg, char16_t const *__restrict __data, size_t __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_DOS$file_wprinter_unlocked)
/* Same as `file_c16printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,file_c16printer_unlocked,(void *__arg, char16_t const *__restrict __data, size_t __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/file_wprinter_unlocked.h>
/* Same as `file_c16printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL file_c16printer_unlocked)(void *__arg, char16_t const *__restrict __data, size_t __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter_unlocked))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* LIBC: file_c16printer_unlocked */
#include <local/wchar/file_c16printer_unlocked.h>
/* Same as `file_c16printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_c16printer_unlocked, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL file_c16printer_unlocked)(void *__arg, char16_t const *__restrict __data, size_t __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_c16printer_unlocked))(__arg, __data, __datalen); })
#endif /* LIBC: file_c16printer_unlocked */
#endif /* file_c16printer_unlocked... */
#if defined(__CRT_HAVE_file_wprinter_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `file_c32printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,file_c32printer_unlocked,(void *__arg, char32_t const *__restrict __data, size_t __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `file_c32printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,file_c32printer_unlocked,(void *__arg, char32_t const *__restrict __data, size_t __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/file_wprinter_unlocked.h>
/* Same as `file_c32printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL file_c32printer_unlocked)(void *__arg, char32_t const *__restrict __data, size_t __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter_unlocked))(__arg, (__WCHAR_TYPE__ const *)__data, __datalen); }
#else /* LIBC: file_c32printer_unlocked */
#include <local/wchar/file_c32printer_unlocked.h>
/* Same as `file_c32printer()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_c32printer_unlocked, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL file_c32printer_unlocked)(void *__arg, char32_t const *__restrict __data, size_t __datalen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_c32printer_unlocked))(__arg, __data, __datalen); })
#endif /* LIBC: file_c32printer_unlocked */
#endif /* file_c32printer_unlocked... */
#if defined(__CRT_HAVE_ungetwc_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetc16_unlocked,(wint_t __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetwc) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetc16_unlocked,(wint_t __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#elif defined(__CRT_HAVE_DOS$ungetwc)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetc16_unlocked,(wint_t __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#elif defined(__CRT_HAVE_DOS$ungetwc_unlocked)
__CREDIRECT_DOS(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetc16_unlocked,(wint_t __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#endif /* ungetc16_unlocked... */
#if defined(__CRT_HAVE_ungetwc_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetc32_unlocked,(wint_t __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetwc) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetc32_unlocked,(wint_t __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#endif /* ungetc32_unlocked... */
#if defined(__CRT_HAVE_vfwprintf_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vfc16printf_unlocked,(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$vfwprintf_unlocked)
__CREDIRECT_DOS(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vfc16printf_unlocked,(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/vfwprintf_unlocked.h>
__FORCELOCAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vfc16printf_unlocked)(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf_unlocked))(__stream, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: vfc16printf_unlocked */
#include <local/wchar/vfc16printf_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vfc16printf_unlocked, __FORCELOCAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vfc16printf_unlocked)(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfc16printf_unlocked))(__stream, __format, __args); })
#endif /* LIBC: vfc16printf_unlocked */
#endif /* vfc16printf_unlocked... */
#if defined(__CRT_HAVE_vfwprintf_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vfc32printf_unlocked,(FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/vfwprintf_unlocked.h>
__FORCELOCAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vfc32printf_unlocked)(FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf_unlocked))(__stream, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: vfc32printf_unlocked */
#include <local/wchar/vfc32printf_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vfc32printf_unlocked, __FORCELOCAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vfc32printf_unlocked)(FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfc32printf_unlocked))(__stream, __format, __args); })
#endif /* LIBC: vfc32printf_unlocked */
#endif /* vfc32printf_unlocked... */
#if defined(__CRT_HAVE_fwprintf_unlocked) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL fc16printf_unlocked)(FILE *__restrict __stream, char16_t const *__restrict __format, ...) __CASMNAME("fwprintf_unlocked");
#elif defined(__CRT_HAVE_DOS$fwprintf_unlocked) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBDCALL fc16printf_unlocked)(FILE *__restrict __stream, char16_t const *__restrict __format, ...) __CASMNAME_DOS("fwprintf_unlocked");
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_vfwprintf_unlocked)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fwprintf_unlocked.h>
#define fc16printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf_unlocked))
#else /* LIBC: fc16printf_unlocked */
#include <local/wchar/fc16printf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(fc16printf_unlocked)
#else /* __cplusplus */
#define fc16printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc16printf_unlocked))
#endif /* !__cplusplus */
#endif /* LIBC: fc16printf_unlocked */
#endif /* fc16printf_unlocked... */
#if defined(__CRT_HAVE_fwprintf_unlocked) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL fc32printf_unlocked)(FILE *__restrict __stream, char32_t const *__restrict __format, ...) __CASMNAME("fwprintf_unlocked");
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_vfwprintf_unlocked)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fwprintf_unlocked.h>
#define fc32printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf_unlocked))
#else /* LIBC: fc32printf_unlocked */
#include <local/wchar/fc32printf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(fc32printf_unlocked)
#else /* __cplusplus */
#define fc32printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc32printf_unlocked))
#endif /* !__cplusplus */
#endif /* LIBC: fc32printf_unlocked */
#endif /* fc32printf_unlocked... */
#if defined(__CRT_HAVE_wprintf_unlocked) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL c16printf_unlocked)(char16_t const *__restrict __format, ...) __CASMNAME("wprintf_unlocked");
#elif defined(__CRT_HAVE_DOS$wprintf_unlocked) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBDCALL c16printf_unlocked)(char16_t const *__restrict __format, ...) __CASMNAME_DOS("wprintf_unlocked");
#elif ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_vfwprintf_unlocked)) && !defined(__NO_STDSTREAMS) || defined(__CRT_HAVE_vwprintf_unlocked))
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wprintf_unlocked.h>
#define c16printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf_unlocked))
#else /* LIBC: c16printf_unlocked */
#include <local/wchar/c16printf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16printf_unlocked)
#else /* __cplusplus */
#define c16printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16printf_unlocked))
#endif /* !__cplusplus */
#endif /* LIBC: c16printf_unlocked */
#endif /* c16printf_unlocked... */
#if defined(__CRT_HAVE_wprintf_unlocked) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL c32printf_unlocked)(char32_t const *__restrict __format, ...) __CASMNAME("wprintf_unlocked");
#elif ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_vfwprintf_unlocked)) && !defined(__NO_STDSTREAMS) || defined(__CRT_HAVE_vwprintf_unlocked))
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wprintf_unlocked.h>
#define c32printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf_unlocked))
#else /* LIBC: c32printf_unlocked */
#include <local/wchar/c32printf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32printf_unlocked)
#else /* __cplusplus */
#define c32printf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32printf_unlocked))
#endif /* !__cplusplus */
#endif /* LIBC: c32printf_unlocked */
#endif /* c32printf_unlocked... */
#if defined(__CRT_HAVE_vwprintf_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vc16printf_unlocked,(char16_t const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_DOS$vwprintf_unlocked)
__CREDIRECT_DOS(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vc16printf_unlocked,(char16_t const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#elif (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_vfwprintf_unlocked)) && !defined(__NO_STDSTREAMS)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/vwprintf_unlocked.h>
__FORCELOCAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vc16printf_unlocked)(char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf_unlocked))((__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: vc16printf_unlocked */
#include <local/wchar/vc16printf_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vc16printf_unlocked, __FORCELOCAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vc16printf_unlocked)(char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc16printf_unlocked))(__format, __args); })
#endif /* LIBC: vc16printf_unlocked */
#endif /* vc16printf_unlocked... */
#if defined(__CRT_HAVE_vwprintf_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vc32printf_unlocked,(char32_t const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#elif (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_vfwprintf_unlocked)) && !defined(__NO_STDSTREAMS)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/vwprintf_unlocked.h>
__FORCELOCAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vc32printf_unlocked)(char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf_unlocked))((__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: vc32printf_unlocked */
#include <local/wchar/vc32printf_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vc32printf_unlocked, __FORCELOCAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vc32printf_unlocked)(char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc32printf_unlocked))(__format, __args); })
#endif /* LIBC: vc32printf_unlocked */
#endif /* vc32printf_unlocked... */
#if defined(__CRT_HAVE_vfwscanf_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vfc16scanf_unlocked,(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwscanf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfwscanf) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vfc16scanf_unlocked,(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$vfwscanf)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vfc16scanf_unlocked,(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_DOS$vfwscanf_unlocked)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vfc16scanf_unlocked,(FILE *__restrict __stream, char16_t const *__restrict __format, __builtin_va_list __args),vfwscanf_unlocked,(__stream,__format,__args))
#endif /* vfc16scanf_unlocked... */
#if defined(__CRT_HAVE_vfwscanf_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vfc32scanf_unlocked,(FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args),vfwscanf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfwscanf) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vfc32scanf_unlocked,(FILE *__restrict __stream, char32_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#endif /* vfc32scanf_unlocked... */
#if defined(__CRT_HAVE_vwscanf_unlocked) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_LIBC_SCANF(1, 0) __ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vc16scanf_unlocked,(char16_t const *__restrict __format, __builtin_va_list __args),vwscanf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_DOS$vwscanf_unlocked)
__CREDIRECT_DOS(__ATTR_LIBC_SCANF(1, 0) __ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vc16scanf_unlocked,(char16_t const *__restrict __format, __builtin_va_list __args),vwscanf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/vwscanf_unlocked.h>
__FORCELOCAL __ATTR_LIBC_SCANF(1, 0) __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vc16scanf_unlocked)(char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf_unlocked))((__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: vc16scanf_unlocked */
#include <local/wchar/vc16scanf_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vc16scanf_unlocked, __FORCELOCAL __ATTR_LIBC_SCANF(1, 0) __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vc16scanf_unlocked)(char16_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc16scanf_unlocked))(__format, __args); })
#endif /* LIBC: vc16scanf_unlocked */
#endif /* vc16scanf_unlocked... */
#if defined(__CRT_HAVE_vwscanf_unlocked) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_LIBC_SCANF(1, 0) __ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vc32scanf_unlocked,(char32_t const *__restrict __format, __builtin_va_list __args),vwscanf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/vwscanf_unlocked.h>
__FORCELOCAL __ATTR_LIBC_SCANF(1, 0) __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vc32scanf_unlocked)(char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf_unlocked))((__WCHAR_TYPE__ const *)__format, __args); }
#else /* LIBC: vc32scanf_unlocked */
#include <local/wchar/vc32scanf_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vc32scanf_unlocked, __FORCELOCAL __ATTR_LIBC_SCANF(1, 0) __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vc32scanf_unlocked)(char32_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vc32scanf_unlocked))(__format, __args); })
#endif /* LIBC: vc32scanf_unlocked */
#endif /* vc32scanf_unlocked... */
#if defined(__CRT_HAVE_fwscanf_unlocked) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_SCANF(2, 3) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL fc16scanf_unlocked)(__FILE *__restrict __stream, char16_t const *__restrict __format, ...) __CASMNAME("fwscanf_unlocked");
#elif defined(__CRT_HAVE_DOS$fwscanf_unlocked) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_SCANF(2, 3) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBDCALL fc16scanf_unlocked)(__FILE *__restrict __stream, char16_t const *__restrict __format, ...) __CASMNAME_DOS("fwscanf_unlocked");
#elif defined(__CRT_HAVE_vfwscanf)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/fwscanf_unlocked.h>
#define fc16scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf_unlocked))
#else /* LIBC: fc16scanf_unlocked */
#include <local/wchar/fc16scanf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(fc16scanf_unlocked)
#else /* __cplusplus */
#define fc16scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc16scanf_unlocked))
#endif /* !__cplusplus */
#endif /* LIBC: fc16scanf_unlocked */
#endif /* fc16scanf_unlocked... */
#if defined(__CRT_HAVE_fwscanf_unlocked) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_SCANF(2, 3) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL fc32scanf_unlocked)(__FILE *__restrict __stream, char32_t const *__restrict __format, ...) __CASMNAME("fwscanf_unlocked");
#elif defined(__CRT_HAVE_vfwscanf)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/fwscanf_unlocked.h>
#define fc32scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf_unlocked))
#else /* LIBC: fc32scanf_unlocked */
#include <local/wchar/fc32scanf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(fc32scanf_unlocked)
#else /* __cplusplus */
#define fc32scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fc32scanf_unlocked))
#endif /* !__cplusplus */
#endif /* LIBC: fc32scanf_unlocked */
#endif /* fc32scanf_unlocked... */
#if defined(__CRT_HAVE_wscanf_unlocked) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_SCANF(1, 2) __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL c16scanf_unlocked)(char16_t const *__restrict __format, ...) __CASMNAME("wscanf_unlocked");
#elif defined(__CRT_HAVE_DOS$wscanf_unlocked) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_SCANF(1, 2) __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBDCALL c16scanf_unlocked)(char16_t const *__restrict __format, ...) __CASMNAME_DOS("wscanf_unlocked");
#elif (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS) || defined(__CRT_HAVE_vwscanf))
#if __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wscanf_unlocked.h>
#define c16scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf_unlocked))
#else /* LIBC: c16scanf_unlocked */
#include <local/wchar/c16scanf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16scanf_unlocked)
#else /* __cplusplus */
#define c16scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16scanf_unlocked))
#endif /* !__cplusplus */
#endif /* LIBC: c16scanf_unlocked */
#endif /* c16scanf_unlocked... */
#if defined(__CRT_HAVE_wscanf_unlocked) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_LIBC_SCANF(1, 2) __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL c32scanf_unlocked)(char32_t const *__restrict __format, ...) __CASMNAME("wscanf_unlocked");
#elif (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS) || defined(__CRT_HAVE_vwscanf))
#if __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wscanf_unlocked.h>
#define c32scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf_unlocked))
#else /* LIBC: c32scanf_unlocked */
#include <local/wchar/c32scanf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32scanf_unlocked)
#else /* __cplusplus */
#define c32scanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32scanf_unlocked))
#endif /* !__cplusplus */
#endif /* LIBC: c32scanf_unlocked */
#endif /* c32scanf_unlocked... */
#endif /* __USE_KOS */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_UCHAR_STDIO_H */
