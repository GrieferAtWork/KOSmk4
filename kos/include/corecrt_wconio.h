/* HASH CRC-32:0x49746ee8 */
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
/* (#) Portability: Windows Kits (/ucrt/corecrt_wconio.h) */
#ifndef _CORECRT_WCONIO_H
#define _CORECRT_WCONIO_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <hybrid/typecore.h>
#include <asm/crt/stdio.h>

#ifdef __USE_DOS
#include <crtdefs.h>
#endif /* __USE_DOS */

#if !defined(WEOF) && defined(__WEOF)
#define WEOF __WEOF
#endif /* !WEOF && __WEOF */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __wint_t_defined
#define __wint_t_defined
typedef __WINT_TYPE__ wint_t;
#endif /* !__wint_t_defined */

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t; /* Errno code (one of `E*' from <errno.h>) */
#endif /* !__errno_t_defined */

#if defined(__CRT_HAVE__getwch_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED,wint_t,__NOTHROW_NCX,_getwch,(void),_getwch_nolock,())
#elif defined(__CRT_HAVE__getwch)
__CDECLARE(__ATTR_WUNUSED,wint_t,__NOTHROW_NCX,_getwch,(void),())
#else /* ... */
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#if defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getwch_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))))
#include <libc/local/corecrt_wconio/_getwch.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_getwch, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED wint_t __NOTHROW_NCX(__LIBCCALL _getwch)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getwch))(); })
#endif /* __CRT_HAVE_stdtty && (__CRT_HAVE__getwch_nolock || (__ECHO && __TCSANOW && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl))) */
#endif /* !... */
#ifdef __CRT_HAVE__getwch_nolock
__CDECLARE(__ATTR_WUNUSED,wint_t,__NOTHROW_NCX,_getwch_nolock,(void),())
#else /* __CRT_HAVE__getwch_nolock */
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#if defined(__ECHO) && defined(__TCSANOW) && defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
#include <libc/local/corecrt_wconio/_getwch_nolock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_getwch_nolock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED wint_t __NOTHROW_NCX(__LIBCCALL _getwch_nolock)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getwch_nolock))(); })
#endif /* __ECHO && __TCSANOW && __CRT_HAVE_stdtty && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */
#endif /* !__CRT_HAVE__getwch_nolock */
#if defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED,wint_t,__NOTHROW_NCX,_getwche,(void),_getwche_nolock,())
#elif defined(__CRT_HAVE__getwche)
__CDECLARE(__ATTR_WUNUSED,wint_t,__NOTHROW_NCX,_getwche,(void),())
#else /* ... */
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#if defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getwche_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))))
#include <libc/local/corecrt_wconio/_getwche.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_getwche, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED wint_t __NOTHROW_NCX(__LIBCCALL _getwche)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getwche))(); })
#endif /* __CRT_HAVE_stdtty && (__CRT_HAVE__getwche_nolock || (__ECHO && __TCSANOW && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl))) */
#endif /* !... */
#ifdef __CRT_HAVE__getwche_nolock
__CDECLARE(__ATTR_WUNUSED,wint_t,__NOTHROW_NCX,_getwche_nolock,(void),())
#else /* __CRT_HAVE__getwche_nolock */
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#if defined(__ECHO) && defined(__TCSANOW) && defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
#include <libc/local/corecrt_wconio/_getwche_nolock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_getwche_nolock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED wint_t __NOTHROW_NCX(__LIBCCALL _getwche_nolock)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getwche_nolock))(); })
#endif /* __ECHO && __TCSANOW && __CRT_HAVE_stdtty && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */
#endif /* !__CRT_HAVE__getwche_nolock */
#if defined(__CRT_HAVE__putwch_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,wint_t,__NOTHROW_NCX,_putwch,(wchar_t __ch),_putwch_nolock,(__ch))
#elif defined(__CRT_HAVE__putwch)
__CDECLARE(,wint_t,__NOTHROW_NCX,_putwch,(wchar_t __ch),(__ch))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked))
#include <libc/local/corecrt_wconio/_putwch.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_putwch, __FORCELOCAL __ATTR_ARTIFICIAL wint_t __NOTHROW_NCX(__LIBCCALL _putwch)(wchar_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_putwch))(__ch); })
#endif /* ... */
#ifdef __CRT_HAVE__putwch_nolock
__CDECLARE(,wint_t,__NOTHROW_NCX,_putwch_nolock,(wchar_t __ch),(__ch))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc))
#include <libc/local/corecrt_wconio/_putwch_nolock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_putwch_nolock, __FORCELOCAL __ATTR_ARTIFICIAL wint_t __NOTHROW_NCX(__LIBCCALL _putwch_nolock)(wchar_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_putwch_nolock))(__ch); })
#endif /* ... */
#if defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,wint_t,__NOTHROW_NCX,_ungetwch,(wint_t __ch),_ungetwch_nolock,(__ch))
#elif defined(__CRT_HAVE__ungetwch)
__CDECLARE(,wint_t,__NOTHROW_NCX,_ungetwch,(wint_t __ch),(__ch))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked))
#include <libc/local/corecrt_wconio/_ungetwch.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ungetwch, __FORCELOCAL __ATTR_ARTIFICIAL wint_t __NOTHROW_NCX(__LIBCCALL _ungetwch)(wint_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ungetwch))(__ch); })
#endif /* ... */
#ifdef __CRT_HAVE__ungetwch_nolock
__CDECLARE(,wint_t,__NOTHROW_NCX,_ungetwch_nolock,(wint_t __ch),(__ch))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc))
#include <libc/local/corecrt_wconio/_ungetwch_nolock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ungetwch_nolock, __FORCELOCAL __ATTR_ARTIFICIAL wint_t __NOTHROW_NCX(__LIBCCALL _ungetwch_nolock)(wint_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ungetwch_nolock))(__ch); })
#endif /* ... */
#ifdef __CRT_HAVE__cgetws
__CDECLARE(__ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,_cgetws,(wchar_t *__restrict __buf),(__buf))
#else /* __CRT_HAVE__cgetws */
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#if defined(__CRT_HAVE__cgetws_s) || (((defined(__CRT_HAVE__getch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getch_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)))))) && ((defined(__CRT_HAVE__ungetch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))))
#include <libc/local/corecrt_wconio/_cgetws.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_cgetws, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL _cgetws)(wchar_t *__restrict __buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cgetws))(__buf); })
#endif /* __CRT_HAVE__cgetws_s || (((__CRT_HAVE__getch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getch || (__CRT_HAVE_stdtty && (__CRT_HAVE__getch_nolock || (__ECHO && __TCSANOW && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_HAVE_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE_fgetc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl))))) && ((__CRT_HAVE__ungetch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)))) */
#endif /* !__CRT_HAVE__cgetws */
#ifdef __CRT_HAVE__cgetws_s
__CDECLARE(__ATTR_OUT(3) __ATTR_OUTS(1, 2),errno_t,__NOTHROW_NCX,_cgetws_s,(wchar_t *__buf, size_t __bufsize, size_t *__restrict __p_readsize),(__buf,__bufsize,__p_readsize))
#else /* __CRT_HAVE__cgetws_s */
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#if ((defined(__CRT_HAVE__getch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getch_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)))))) && ((defined(__CRT_HAVE__ungetch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))))
#include <libc/local/corecrt_wconio/_cgetws_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_cgetws_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(3) __ATTR_OUTS(1, 2) errno_t __NOTHROW_NCX(__LIBCCALL _cgetws_s)(wchar_t *__buf, size_t __bufsize, size_t *__restrict __p_readsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cgetws_s))(__buf, __bufsize, __p_readsize); })
#endif /* ((__CRT_HAVE__getch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getch || (__CRT_HAVE_stdtty && (__CRT_HAVE__getch_nolock || (__ECHO && __TCSANOW && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_HAVE_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE_fgetc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl))))) && ((__CRT_HAVE__ungetch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock))) */
#endif /* !__CRT_HAVE__cgetws_s */
#ifdef __CRT_HAVE__cputws
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_NCX,_cputws,(wchar_t const *__restrict __str),(__str))
#elif (defined(__CRT_HAVE__putwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__putwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked))) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
#include <libc/local/corecrt_wconio/_cputws.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_cputws, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL _cputws)(wchar_t const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cputws))(__str); })
#endif /* ... */
#ifdef __CRT_HAVE___conio_common_vcwprintf
__CDECLARE(__ATTR_IN(2) __ATTR_LIBC_WPRINTF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__conio_common_vcwprintf,(__UINT64_TYPE__ __options, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__format,__locale,__args))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked))
#include <libc/local/corecrt_wconio/__conio_common_vcwprintf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__conio_common_vcwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_LIBC_WPRINTF(2, 0) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __conio_common_vcwprintf)(__UINT64_TYPE__ __options, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__conio_common_vcwprintf))(__options, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE___conio_common_vcwprintf_s
__CDECLARE(__ATTR_IN(2) __ATTR_LIBC_WPRINTF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__conio_common_vcwprintf_s,(__UINT64_TYPE__ __options, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__format,__locale,__args))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf_s) || defined(__CRT_HAVE___stdio_common_vfwprintf) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked))
#include <libc/local/corecrt_wconio/__conio_common_vcwprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__conio_common_vcwprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_LIBC_WPRINTF(2, 0) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __conio_common_vcwprintf_s)(__UINT64_TYPE__ __options, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__conio_common_vcwprintf_s))(__options, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE___conio_common_vcwprintf_p
__CDECLARE(__ATTR_IN(2) __ATTR_LIBC_WPRINTF_P(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__conio_common_vcwprintf_p,(__UINT64_TYPE__ __options, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__format,__locale,__args))
#elif defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf_p) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked))
#include <libc/local/corecrt_wconio/__conio_common_vcwprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__conio_common_vcwprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_LIBC_WPRINTF_P(2, 0) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __conio_common_vcwprintf_p)(__UINT64_TYPE__ __options, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__conio_common_vcwprintf_p))(__options, __format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE___conio_common_vcwscanf
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__conio_common_vcwscanf,(__UINT64_TYPE__ __options, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__options,__format,__locale,__args))
#else /* __CRT_HAVE___conio_common_vcwscanf */
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#if ((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getwche_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)))))) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked))))
#include <libc/local/corecrt_wconio/__conio_common_vcwscanf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__conio_common_vcwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_LIBC_WSCANF(2, 0) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL __conio_common_vcwscanf)(__UINT64_TYPE__ __options, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__conio_common_vcwscanf))(__options, __format, __locale, __args); })
#endif /* ((__CRT_HAVE__getwche_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getwche || (__CRT_HAVE_stdtty && (__CRT_HAVE__getwche_nolock || (__ECHO && __TCSANOW && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl))))) && ((__CRT_HAVE__ungetwch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetwch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked))) */
#endif /* !__CRT_HAVE___conio_common_vcwscanf */
#ifdef __CRT_HAVE__vcwprintf_l
__CDECLARE(__ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcwprintf_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE___conio_common_vcwprintf) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
#include <libc/local/corecrt_wconio/_vcwprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcwprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcwprintf_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcwprintf_l))(__format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vcwprintf_s_l
__CDECLARE(__ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcwprintf_s_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE___conio_common_vcwprintf_s) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf_s) || defined(__CRT_HAVE___stdio_common_vfwprintf) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
#include <libc/local/corecrt_wconio/_vcwprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcwprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcwprintf_s_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcwprintf_s_l))(__format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vcwprintf_p_l
__CDECLARE(__ATTR_IN(1) __ATTR_LIBC_WPRINTF_P(1, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcwprintf_p_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE___conio_common_vcwprintf_p) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf_p) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
#include <libc/local/corecrt_wconio/_vcwprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcwprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF_P(1, 0) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcwprintf_p_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcwprintf_p_l))(__format, __locale, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vcwscanf_l
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcwscanf_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#else /* __CRT_HAVE__vcwscanf_l */
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#if defined(__CRT_HAVE___conio_common_vcwscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getwche_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)))))) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/corecrt_wconio/_vcwscanf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcwscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcwscanf_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcwscanf_l))(__format, __locale, __args); })
#endif /* __CRT_HAVE___conio_common_vcwscanf || (((__CRT_HAVE__getwche_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getwche || (__CRT_HAVE_stdtty && (__CRT_HAVE__getwche_nolock || (__ECHO && __TCSANOW && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl))))) && ((__CRT_HAVE__ungetwch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetwch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked)))) */
#endif /* !__CRT_HAVE__vcwscanf_l */
#ifdef __CRT_HAVE__vcwscanf_s_l
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcwscanf_s_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#else /* __CRT_HAVE__vcwscanf_s_l */
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#if defined(__CRT_HAVE___conio_common_vcwscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getwche_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)))))) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/corecrt_wconio/_vcwscanf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcwscanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcwscanf_s_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcwscanf_s_l))(__format, __locale, __args); })
#endif /* __CRT_HAVE___conio_common_vcwscanf || (((__CRT_HAVE__getwche_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getwche || (__CRT_HAVE_stdtty && (__CRT_HAVE__getwche_nolock || (__ECHO && __TCSANOW && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl))))) && ((__CRT_HAVE__ungetwch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetwch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked)))) */
#endif /* !__CRT_HAVE__vcwscanf_s_l */
#ifdef __CRT_HAVE__vcwprintf
__CDECLARE(__ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcwprintf,(wchar_t const *__format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE__vcwprintf_l) || defined(__CRT_HAVE___conio_common_vcwprintf) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
#include <libc/local/corecrt_wconio/_vcwprintf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcwprintf)(wchar_t const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcwprintf))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vcwprintf_s
__CDECLARE(__ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcwprintf_s,(wchar_t const *__format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE__vcwprintf_s_l) || defined(__CRT_HAVE___conio_common_vcwprintf_s) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf_s) || defined(__CRT_HAVE___stdio_common_vfwprintf) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
#include <libc/local/corecrt_wconio/_vcwprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcwprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcwprintf_s)(wchar_t const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcwprintf_s))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vcwprintf_p
__CDECLARE(__ATTR_IN(1) __ATTR_LIBC_WPRINTF_P(1, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcwprintf_p,(const wchar_t *__format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE__vcwprintf_p_l) || defined(__CRT_HAVE___conio_common_vcwprintf_p) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf_p) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
#include <libc/local/corecrt_wconio/_vcwprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcwprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF_P(1, 0) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcwprintf_p)(const wchar_t *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcwprintf_p))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE__vcwscanf
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcwscanf,(wchar_t const *__format, __builtin_va_list __args),(__format,__args))
#else /* __CRT_HAVE__vcwscanf */
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#if defined(__CRT_HAVE__vcwscanf_l) || defined(__CRT_HAVE___conio_common_vcwscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getwche_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)))))) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/corecrt_wconio/_vcwscanf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcwscanf)(wchar_t const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcwscanf))(__format, __args); })
#endif /* __CRT_HAVE__vcwscanf_l || __CRT_HAVE___conio_common_vcwscanf || (((__CRT_HAVE__getwche_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getwche || (__CRT_HAVE_stdtty && (__CRT_HAVE__getwche_nolock || (__ECHO && __TCSANOW && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl))))) && ((__CRT_HAVE__ungetwch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetwch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked)))) */
#endif /* !__CRT_HAVE__vcwscanf */
#ifdef __CRT_HAVE__vcwscanf_s
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vcwscanf_s,(wchar_t const *__format, __builtin_va_list __args),(__format,__args))
#else /* __CRT_HAVE__vcwscanf_s */
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#if defined(__CRT_HAVE__vcwscanf_s_l) || defined(__CRT_HAVE___conio_common_vcwscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getwche_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)))))) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/corecrt_wconio/_vcwscanf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vcwscanf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vcwscanf_s)(wchar_t const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vcwscanf_s))(__format, __args); })
#endif /* __CRT_HAVE__vcwscanf_s_l || __CRT_HAVE___conio_common_vcwscanf || (((__CRT_HAVE__getwche_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getwche || (__CRT_HAVE_stdtty && (__CRT_HAVE__getwche_nolock || (__ECHO && __TCSANOW && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl))))) && ((__CRT_HAVE__ungetwch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetwch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked)))) */
#endif /* !__CRT_HAVE__vcwscanf_s */
#ifdef __CRT_HAVE__cwprintf
__LIBC __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 2) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwprintf)(wchar_t const *__format, ...) __CASMNAME_SAME("_cwprintf");
#elif defined(__CRT_HAVE__vcwprintf) || defined(__CRT_HAVE__vcwprintf_l) || defined(__CRT_HAVE___conio_common_vcwprintf) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
#include <libc/local/corecrt_wconio/_cwprintf.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_cwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 2) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwprintf)(wchar_t const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwprintf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _cwprintf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwprintf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__cwprintf_l
__LIBC __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwprintf_l)(wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_cwprintf_l");
#elif defined(__CRT_HAVE__vcwprintf_l) || defined(__CRT_HAVE___conio_common_vcwprintf) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
#include <libc/local/corecrt_wconio/_cwprintf_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_cwprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwprintf_l)(wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwprintf_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _cwprintf_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwprintf_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__cwprintf_s
__LIBC __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 2) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwprintf_s)(wchar_t const *__format, ...) __CASMNAME_SAME("_cwprintf_s");
#elif defined(__CRT_HAVE__vcwprintf_s) || defined(__CRT_HAVE__vcwprintf_s_l) || defined(__CRT_HAVE___conio_common_vcwprintf_s) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf_s) || defined(__CRT_HAVE___stdio_common_vfwprintf) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
#include <libc/local/corecrt_wconio/_cwprintf_s.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_cwprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 2) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwprintf_s)(wchar_t const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwprintf_s))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _cwprintf_s(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwprintf_s))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__cwprintf_s_l
__LIBC __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwprintf_s_l)(wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_cwprintf_s_l");
#elif defined(__CRT_HAVE__vcwprintf_s_l) || defined(__CRT_HAVE___conio_common_vcwprintf_s) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf_s) || defined(__CRT_HAVE___stdio_common_vfwprintf) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
#include <libc/local/corecrt_wconio/_cwprintf_s_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_cwprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwprintf_s_l)(wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwprintf_s_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _cwprintf_s_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwprintf_s_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__cwprintf_p
__LIBC __ATTR_IN(1) __ATTR_LIBC_WPRINTF_P(1, 2) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwprintf_p)(wchar_t const *__format, ...) __CASMNAME_SAME("_cwprintf_p");
#elif defined(__CRT_HAVE__vcwprintf_p) || defined(__CRT_HAVE__vcwprintf_p_l) || defined(__CRT_HAVE___conio_common_vcwprintf_p) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf_p) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
#include <libc/local/corecrt_wconio/_cwprintf_p.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_cwprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF_P(1, 2) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwprintf_p)(wchar_t const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwprintf_p))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _cwprintf_p(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwprintf_p))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__cwprintf_p_l
__LIBC __ATTR_IN(1) __ATTR_LIBC_WPRINTF_P(1, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwprintf_p_l)(wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_cwprintf_p_l");
#elif defined(__CRT_HAVE__vcwprintf_p_l) || defined(__CRT_HAVE___conio_common_vcwprintf_p) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfwprintf_p) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
#include <libc/local/corecrt_wconio/_cwprintf_p_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_cwprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF_P(1, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwprintf_p_l)(wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwprintf_p_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _cwprintf_p_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwprintf_p_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE__cwscanf
__LIBC __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 2) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwscanf)(wchar_t const *__format, ...) __CASMNAME_SAME("_cwscanf");
#else /* __CRT_HAVE__cwscanf */
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#if defined(__CRT_HAVE__vcwscanf) || defined(__CRT_HAVE__vcwscanf_l) || defined(__CRT_HAVE___conio_common_vcwscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getwche_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)))))) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/corecrt_wconio/_cwscanf.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_cwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 2) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwscanf)(wchar_t const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwscanf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _cwscanf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwscanf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* __CRT_HAVE__vcwscanf || __CRT_HAVE__vcwscanf_l || __CRT_HAVE___conio_common_vcwscanf || (((__CRT_HAVE__getwche_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getwche || (__CRT_HAVE_stdtty && (__CRT_HAVE__getwche_nolock || (__ECHO && __TCSANOW && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl))))) && ((__CRT_HAVE__ungetwch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetwch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked)))) */
#endif /* !__CRT_HAVE__cwscanf */
#ifdef __CRT_HAVE__cwscanf_l
__LIBC __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwscanf_l)(wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_cwscanf_l");
#else /* __CRT_HAVE__cwscanf_l */
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#if defined(__CRT_HAVE__vcwscanf_l) || defined(__CRT_HAVE___conio_common_vcwscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getwche_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)))))) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/corecrt_wconio/_cwscanf_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_cwscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwscanf_l)(wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwscanf_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _cwscanf_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwscanf_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* __CRT_HAVE__vcwscanf_l || __CRT_HAVE___conio_common_vcwscanf || (((__CRT_HAVE__getwche_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getwche || (__CRT_HAVE_stdtty && (__CRT_HAVE__getwche_nolock || (__ECHO && __TCSANOW && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl))))) && ((__CRT_HAVE__ungetwch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetwch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked)))) */
#endif /* !__CRT_HAVE__cwscanf_l */
#ifdef __CRT_HAVE__cwscanf_s
__LIBC __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 2) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwscanf_s)(wchar_t const *__format, ...) __CASMNAME_SAME("_cwscanf_s");
#else /* __CRT_HAVE__cwscanf_s */
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#if defined(__CRT_HAVE__vcwscanf_s) || defined(__CRT_HAVE__vcwscanf_s_l) || defined(__CRT_HAVE___conio_common_vcwscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getwche_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)))))) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/corecrt_wconio/_cwscanf_s.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_cwscanf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 2) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwscanf_s)(wchar_t const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwscanf_s))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _cwscanf_s(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwscanf_s))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* __CRT_HAVE__vcwscanf_s || __CRT_HAVE__vcwscanf_s_l || __CRT_HAVE___conio_common_vcwscanf || (((__CRT_HAVE__getwche_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getwche || (__CRT_HAVE_stdtty && (__CRT_HAVE__getwche_nolock || (__ECHO && __TCSANOW && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl))))) && ((__CRT_HAVE__ungetwch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetwch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked)))) */
#endif /* !__CRT_HAVE__cwscanf_s */
#ifdef __CRT_HAVE__cwscanf_s_l
__LIBC __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwscanf_s_l)(wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_cwscanf_s_l");
#else /* __CRT_HAVE__cwscanf_s_l */
#include <asm/os/termios.h>
#include <asm/os/tty.h>
#if defined(__CRT_HAVE__vcwscanf_s_l) || defined(__CRT_HAVE___conio_common_vcwscanf) || (((defined(__CRT_HAVE__getwche_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__getwche) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE__getwche_nolock) || (defined(__ECHO) && defined(__TCSANOW) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked)) && (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)))))) && ((defined(__CRT_HAVE__ungetwch_nolock) && defined(__USE_STDIO_UNLOCKED)) || defined(__CRT_HAVE__ungetwch) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
#include <libc/local/corecrt_wconio/_cwscanf_s_l.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(_cwscanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _cwscanf_s_l)(wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwscanf_s_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define _cwscanf_s_l(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_cwscanf_s_l))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* __CRT_HAVE__vcwscanf_s_l || __CRT_HAVE___conio_common_vcwscanf || (((__CRT_HAVE__getwche_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__getwche || (__CRT_HAVE_stdtty && (__CRT_HAVE__getwche_nolock || (__ECHO && __TCSANOW && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) && (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl))))) && ((__CRT_HAVE__ungetwch_nolock && __USE_STDIO_UNLOCKED) || __CRT_HAVE__ungetwch || (__CRT_HAVE_stdtty && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked)))) */
#endif /* !__CRT_HAVE__cwscanf_s_l */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_CORECRT_WCONIO_H */
