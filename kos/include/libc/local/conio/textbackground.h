/* HASH CRC-32:0x1e0638f7 */
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
#ifndef __local_textbackground_defined
#define __local_textbackground_defined
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE__cprintf) || defined(__CRT_HAVE__vcprintf) || defined(__CRT_HAVE__vcprintf_l) || defined(__CRT_HAVE___conio_common_vcprintf) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__cprintf_defined
#define __local___localdep__cprintf_defined
#ifdef __CRT_HAVE__cprintf
__LIBC __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 2) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep__cprintf)(char const *__format, ...) __CASMNAME("_cprintf");
#elif defined(__CRT_HAVE__vcprintf) || defined(__CRT_HAVE__vcprintf_l) || defined(__CRT_HAVE___conio_common_vcprintf) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
__NAMESPACE_LOCAL_END
#include <libc/local/conio/_cprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__cprintf __LIBC_LOCAL_NAME(_cprintf)
#else /* ... */
#undef __local___localdep__cprintf_defined
#endif /* !... */
#endif /* !__local___localdep__cprintf_defined */
__LOCAL_LIBC(textbackground) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(textbackground))(int __color) {
	switch (__color) {
	case 0x0:        __color = 40;  break; /* AC_BG_BLACK   */
	case 0x1:         __color = 44;  break; /* AC_BG_NAVY    */
	case 0x2:        __color = 42;  break; /* AC_BG_GREEN   */
	case 0x3:         __color = 46;  break; /* AC_BG_TEAL    */
	case 0x4:          __color = 41;  break; /* AC_BG_MAROON  */
	case 0x5:      __color = 45;  break; /* AC_BG_PURPLE  */
	case 0x6:        __color = 43;  break; /* AC_BG_OLIVE   */
	case 0x7:    __color = 47;  break; /* AC_BG_SILVER  */
	case 0x8:     __color = 100; break; /* AC_BG_GREY    */
	case 0x9:    __color = 104; break; /* AC_BG_BLUE    */
	case 0xa:   __color = 102; break; /* AC_BG_LIME    */
	case 0xb:    __color = 106; break; /* AC_BG_AQUA    */
	case 0xc:     __color = 101; break; /* AC_BG_RED     */
	case 0xd: __color = 105; break; /* AC_BG_FUCHSIA */
	case 0xe:       __color = 103; break; /* AC_BG_YELLOW  */
	case 0xf:        __color = 107; break; /* AC_BG_WHITE   */
	default: break;
	}
	(__NAMESPACE_LOCAL_SYM __localdep__cprintf)("\033[%dm", __color);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_textbackground_defined
#define __local___localdep_textbackground_defined
#define __localdep_textbackground __LIBC_LOCAL_NAME(textbackground)
#endif /* !__local___localdep_textbackground_defined */
#else /* __CRT_HAVE__cprintf || __CRT_HAVE__vcprintf || __CRT_HAVE__vcprintf_l || __CRT_HAVE___conio_common_vcprintf || (__CRT_HAVE_stdtty && (__CRT_HAVE___stdio_common_vfprintf || __CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#undef __local_textbackground_defined
#endif /* !__CRT_HAVE__cprintf && !__CRT_HAVE__vcprintf && !__CRT_HAVE__vcprintf_l && !__CRT_HAVE___conio_common_vcprintf && (!__CRT_HAVE_stdtty || (!__CRT_HAVE___stdio_common_vfprintf && !__CRT_HAVE_vfprintf && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock)) */
#endif /* !__local_textbackground_defined */
