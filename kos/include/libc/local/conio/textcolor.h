/* HASH CRC-32:0x4c7eb637 */
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
#ifndef __local_textcolor_defined
#define __local_textcolor_defined
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE__cprintf) || defined(__CRT_HAVE__vcprintf) || defined(__CRT_HAVE__vcprintf_l) || defined(__CRT_HAVE___conio_common_vcprintf) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__cprintf_defined
#define __local___localdep__cprintf_defined
#ifdef __CRT_HAVE__cprintf
__LIBC __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 2) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__VLIBCCALL __localdep__cprintf)(char const *__format, ...) __CASMNAME("_cprintf");
#elif defined(__CRT_HAVE__vcprintf) || defined(__CRT_HAVE__vcprintf_l) || defined(__CRT_HAVE___conio_common_vcprintf) || (defined(__CRT_HAVE_stdtty) && (defined(__CRT_HAVE___stdio_common_vfprintf) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
__NAMESPACE_LOCAL_END
#include <libc/local/conio/_cprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__cprintf __LIBC_LOCAL_NAME(_cprintf)
#else /* ... */
#undef __local___localdep__cprintf_defined
#endif /* !... */
#endif /* !__local___localdep__cprintf_defined */
__LOCAL_LIBC(textcolor) void
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(textcolor))(int __color) {
	switch (__color) {
	case 0x0:        __color = 30; break; /* AC_FG_BLACK   */
	case 0x1:         __color = 34; break; /* AC_FG_NAVY    */
	case 0x2:        __color = 32; break; /* AC_FG_GREEN   */
	case 0x3:         __color = 36; break; /* AC_FG_TEAL    */
	case 0x4:          __color = 31; break; /* AC_FG_MAROON  */
	case 0x5:      __color = 35; break; /* AC_FG_PURPLE  */
	case 0x6:        __color = 33; break; /* AC_FG_OLIVE   */
	case 0x7:    __color = 37; break; /* AC_FG_SILVER  */
	case 0x8:     __color = 90; break; /* AC_FG_GREY    */
	case 0x9:    __color = 94; break; /* AC_FG_BLUE    */
	case 0xa:   __color = 92; break; /* AC_FG_LIME    */
	case 0xb:    __color = 96; break; /* AC_FG_AQUA    */
	case 0xc:     __color = 91; break; /* AC_FG_RED     */
	case 0xd: __color = 95; break; /* AC_FG_FUCHSIA */
	case 0xe:       __color = 93; break; /* AC_FG_YELLOW  */
	case 0xf:        __color = 97; break; /* AC_FG_WHITE   */
	default: break;
	}
	(__NAMESPACE_LOCAL_SYM __localdep__cprintf)("\033[%dm", __color);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_textcolor_defined
#define __local___localdep_textcolor_defined
#define __localdep_textcolor __LIBC_LOCAL_NAME(textcolor)
#endif /* !__local___localdep_textcolor_defined */
#else /* __CRT_HAVE__cprintf || __CRT_HAVE__vcprintf || __CRT_HAVE__vcprintf_l || __CRT_HAVE___conio_common_vcprintf || (__CRT_HAVE_stdtty && (__CRT_HAVE___stdio_common_vfprintf || __CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */
#undef __local_textcolor_defined
#endif /* !__CRT_HAVE__cprintf && !__CRT_HAVE__vcprintf && !__CRT_HAVE__vcprintf_l && !__CRT_HAVE___conio_common_vcprintf && (!__CRT_HAVE_stdtty || (!__CRT_HAVE___stdio_common_vfprintf && !__CRT_HAVE_vfprintf && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock)) */
#endif /* !__local_textcolor_defined */
