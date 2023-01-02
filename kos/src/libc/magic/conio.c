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
%(c_prefix){
/* (#) Portability: DJGPP        (/include/conio.h) */
/* (#) Portability: EMX kLIBC    (/libc/include/conio.h) */
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/conio.h) */
/* (#) Portability: Windows Kits (/ucrt/conio.h) */
}

%[default:section(".text.crt.dos.conio")]

%(auto_source){
#include "../libc/globals.h"
}

%[define_replacement(stdtty = __LOCAL_stdtty)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

#ifdef __USE_DOS
#include <crtdefs.h>
#ifndef __USE_DOS_CLEAN
#include <corecrt_wconio.h> /* Include <wchar.h> instead */
#endif /* !__USE_DOS_CLEAN */
#endif /* __USE_DOS */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t; /* Errno code (one of `E*' from <errno.h>) */
#endif /* !__errno_t_defined */

/* KOS-extension: standard file stream for `/dev/tty' */
#if defined(__USE_KOS) && !defined(stdtty) && defined(__CRT_HAVE_stdtty)
__CSDECLARE(,FILE *,stdtty)
#define stdtty stdtty
#endif /* __USE_KOS && !stdtty && __CRT_HAVE_stdtty */

}

/*
 * =========== Implementation Notes ========================================
 *
 * - _kbhit()  --> readf(IO_NONBLOCK)
 * - _getch()  --> tcgetattr(SAVED) + tcsetattr(~ECHO) + read() + tcsetattr(SAVED)
 * - _getche() --> tcgetattr(SAVED) + tcsetattr(ECHO) + read() + tcsetattr(SAVED)
 *
 * The race condition where _getch() / _getche() don't affect the echoing of characters
 * entered while not inside of the read-character loop actually also exists on  windows
 * (as  far as I can tell). By looking  at the disassembly of those functions, it seems
 * like they do pretty much the same as we do, except that:
 *  - `tcgetattr()' becomes `GetConsoleMode()'
 *  - `tcsetattr()' becomes `SetConsoleMode()'
 *  - `~ECHO' becomes `0'
 *  - `ECHO' becomes `ENABLE_ECHO_INPUT' (well... actually it also becomes
 *    `0', and the read character  is manually echoed via `_putch()',  but
 *    you should get the idea...)
 */


[[wunused]]
int _kbhit(void);

@@>> _getch(3), _getch_nolock(3)
@@Read a character from the console, without echoing it on-screen
@@@return: * : The character read from the console
@@@return: -1: End-of-file on console
[[wunused]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("_getch_nolock")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(_getch_nolock))]]
[[impl_include("<libc/template/stdtty.h>")]]
int _getch(void) {
	int result;
@@pp_if $has_function(flockfile, funlockfile)@@
	FILE *fp = stdtty;
	flockfile(fp);
@@pp_endif@@
	result = _getch_nolock();
@@pp_if $has_function(flockfile, funlockfile)@@
	funlockfile(fp);
@@pp_endif@@
	return result;
}

[[wunused, alias("_getch"), doc_alias("_getch")]]
[[requires($extended_include_prefix("<asm/os/termios.h>")
           defined(__ECHO) && defined(__TCSANOW) && defined(__CRT_HAVE_stdtty) &&
           $has_function(fileno, fgetc_unlocked, tcgetattr, tcsetattr))]]
[[impl_include("<bits/types.h>", "<asm/os/termios.h>", "<bits/os/termios.h>", "<libc/template/stdtty.h>")]]
int _getch_nolock(void) {
	int result;
	struct termios oios, nios;
	FILE *fp = stdtty;
	fd_t fd  = fileno(fp);
	tcgetattr(fd, &oios);
	memcpy(&nios, &oios, sizeof(nios));
	nios.@c_lflag@ &= ~__ECHO;
	tcsetattr(fd, __TCSANOW, &nios);
	result = fgetc_unlocked(fp);
	tcsetattr(fd, __TCSANOW, &oios);
	return result;
}

@@>> _getche(3), _getche_nolock(3)
@@Read a character from the console, whilst also echoing it on-screen
@@@return: * : The character read from the console
@@@return: -1: End-of-file on console
[[wunused]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("_getche_nolock")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(_getche_nolock))]]
[[impl_include("<libc/template/stdtty.h>")]]
int _getche(void) {
	int result;
@@pp_if $has_function(flockfile, funlockfile)@@
	FILE *fp = stdtty;
	flockfile(fp);
@@pp_endif@@
	result = _getche_nolock();
@@pp_if $has_function(flockfile, funlockfile)@@
	funlockfile(fp);
@@pp_endif@@
	return result;
}

[[wunused, alias("_getche"), doc_alias("_getche")]]
[[requires($extended_include_prefix("<asm/os/termios.h>")
           defined(__ECHO) && defined(__TCSANOW) && defined(__CRT_HAVE_stdtty) &&
           $has_function(fileno, fgetc_unlocked, tcgetattr, tcsetattr))]]
[[impl_include("<bits/types.h>", "<asm/os/termios.h>", "<bits/os/termios.h>", "<libc/template/stdtty.h>")]]
int _getche_nolock(void) {
	int result;
	struct termios oios, nios;
	FILE *fp = stdtty;
	fd_t fd  = fileno(fp);
	tcgetattr(fd, &oios);
	memcpy(&nios, &oios, sizeof(nios));
	nios.@c_lflag@ |= __ECHO;
	tcsetattr(fd, __TCSANOW, &nios);
	result = fgetc_unlocked(fp);
	tcsetattr(fd, __TCSANOW, &oios);
	return result;
}

[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("_putch_nolock")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(fputc))]]
[[impl_include("<libc/template/stdtty.h>")]]
int _putch(int ch) {
	return fputc(ch, stdtty);
}

[[alias("_putch"), doc_alias("_putch")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(fputc_unlocked))]]
[[impl_include("<libc/template/stdtty.h>")]]
int _putch_nolock(int ch) {
	return fputc_unlocked(ch, stdtty);
}

[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("_ungetch_nolock")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(ungetc))]]
[[impl_include("<libc/template/stdtty.h>")]]
int _ungetch(int ch) {
	return ungetc(ch, stdtty);
}

[[alias("_ungetch"), doc_alias("_ungetch")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(ungetc_unlocked))]]
[[impl_include("<libc/template/stdtty.h>")]]
int _ungetch_nolock(int ch) {
	return ungetc_unlocked(ch, stdtty);
}


[[decl_include("<bits/types.h>"), requires_function(_cgets_s)]]
char *_cgets([[inout]] char *__restrict buf) {
	char *result = buf + 2;
	size_t readsize;
	if (_cgets_s(result, buf[0], &readsize) != 0)
		result = NULL;
	buf[1] = (char)(unsigned char)readsize;
	return result;
}

[[decl_include("<bits/types.h>")]]
[[requires_function(_getch, _ungetch)]]
errno_t _cgets_s([[out(*p_readsize <= bufsize)]] char *buf, size_t bufsize,
                 [[out]] size_t *__restrict p_readsize) {
	int ch;
	if unlikely(!bufsize)
		return DOS_ENOSPC;
	buf[0]      = '\0';
	*p_readsize = 0;
	--bufsize;
	while (bufsize && (ch = _getche()) != -1) {
		if (ch == '\r') {
			ch = _getche();
			if (ch != -1 && ch != '\n')
				_ungetch(ch);
			break;
		}
		if (ch == '\n')
			break;
		*buf++ = (char)(unsigned char)(unsigned int)ch;
		*buf   = '\0';
		++*p_readsize;
		--bufsize;
	}
	return 0;
}

[[impl_include("<libc/template/stdtty.h>")]]
[[requires($has_function(_putch) || (defined(__CRT_HAVE_stdtty) && $has_function(fwrite)))]]
int _cputs([[in]] char const *__restrict str) {
@@pp_if defined(__CRT_HAVE_stdtty) && $has_function(fwrite)@@
	size_t len = strlen(str);
	size_t ok  = fwrite(str, sizeof(char), len, stdtty);
	return ok >= len ? 0 : -1;
@@pp_else@@
	int result = 0;
	do {
		char ch = *str++;
		if (!ch)
			break;
		result = _putch(ch);
	} while (result != -1);
	return result;
@@pp_endif@@
}

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[impl_include("<libc/template/stdtty.h>")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(__stdio_common_vfprintf))]]
__STDC_INT_AS_SSIZE_T __conio_common_vcprintf($uint64_t options, [[in, format]] char const *format,
                                              $locale_t locale, $va_list args) {
	return __stdio_common_vfprintf(options, stdtty, format, locale, args);
}

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[impl_include("<libc/template/stdtty.h>")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(__stdio_common_vfprintf_s))]]
__STDC_INT_AS_SSIZE_T __conio_common_vcprintf_s($uint64_t options, [[in, format]] char const *format,
                                                $locale_t locale, $va_list args) {
	return __stdio_common_vfprintf_s(options, stdtty, format, locale, args);
}

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[crt_intern_alias("__conio_common_vcprintf")]] /* Normal printf already supports positional arguments! */
[[impl_include("<libc/template/stdtty.h>")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(__stdio_common_vfprintf_p))]]
__STDC_INT_AS_SSIZE_T __conio_common_vcprintf_p($uint64_t options, [[in, format]] char const *format,
                                                $locale_t locale, $va_list args) {
	return __stdio_common_vfprintf_p(options, stdtty, format, locale, args);
}

[[decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]]
[[requires_dependent_function(_getche, _ungetch)]]
[[impl_prefix(
@@push_namespace(local)@@
__LOCAL_LIBC(conio_common_vcscanf_getc) __format_word_t
(__FORMATPRINTER_CC conio_common_vcscanf_getc)(void *__UNUSED(arg)) {
	return (__format_word_t)_getche();
}
__LOCAL_LIBC(conio_common_vcscanf_ungetc) ssize_t
(__FORMATPRINTER_CC conio_common_vcscanf_ungetc)(void *__UNUSED(arg), __format_word_t word) {
	return _ungetch((int)(unsigned char)(unsigned int)word);
}
@@pop_namespace@@
)]]
__STDC_INT_AS_SSIZE_T __conio_common_vcscanf($uint64_t options, [[in, format]] char const *format,
                                             $locale_t locale, $va_list args) {
	(void)options;
	(void)locale;
	return format_vscanf(&__NAMESPACE_LOCAL_SYM conio_common_vcscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM conio_common_vcscanf_ungetc,
	                     NULL, format, args);
}


/************************************************************************/
/* __conio_common_* wrappers.                                           */
/************************************************************************/
[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__conio_common_vcprintf)]]
__STDC_INT_AS_SSIZE_T _vcprintf_l([[in, format]] char const *format, $locale_t locale, $va_list args) {
	return __conio_common_vcprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, format, locale, args);
}

[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__conio_common_vcprintf_s)]]
__STDC_INT_AS_SSIZE_T _vcprintf_s_l([[in, format]] char const *format, $locale_t locale, $va_list args) {
	return __conio_common_vcprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, format, locale, args);
}

[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__conio_common_vcprintf_p)]]
[[crt_intern_alias("_vcprintf_l")]] /* Normal printf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vcprintf_p_l([[in, format]] char const *format, $locale_t locale, $va_list args) {
	return __conio_common_vcprintf_p(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, format, locale, args);
}

[[decl_include("<features.h>"), wunused, impl_include("<corecrt_stdio_config.h>"), requires_function(__conio_common_vcscanf)]]
__STDC_INT_AS_SSIZE_T _vcscanf_l([[in, format]] char const *format, $locale_t locale, $va_list args) {
	return __conio_common_vcscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, format, locale, args);
}

[[decl_include("<features.h>"), wunused, impl_include("<corecrt_stdio_config.h>"), requires_function(__conio_common_vcscanf)]]
__STDC_INT_AS_SSIZE_T _vcscanf_s_l([[in, format]] char const *format, $locale_t locale, $va_list args) {
	return __conio_common_vcscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS |
	                              _CRT_INTERNAL_SCANF_SECURECRT,
	                              format, locale, args);
}


/************************************************************************/
/* Simple wrappers.                                                     */
/************************************************************************/
[[decl_include("<features.h>"), requires_function(_vcprintf_l)]]
__STDC_INT_AS_SSIZE_T _vcprintf([[in, format]] char const *format, $va_list args) {
	return _vcprintf_l(format, NULL, args);
}

[[decl_include("<features.h>"), requires_function(_vcprintf_s_l)]]
__STDC_INT_AS_SSIZE_T _vcprintf_s([[in, format]] char const *format, $va_list args) {
	return _vcprintf_s_l(format, NULL, args);
}

[[decl_include("<features.h>"), requires_function(_vcprintf_p_l)]]
[[crt_intern_alias("_vcprintf")]] /* Normal printf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vcprintf_p([[in, format]] char const *format, $va_list args) {
	return _vcprintf_p_l(format, NULL, args);
}

[[decl_include("<features.h>"), wunused, requires_function(_vcscanf_l)]]
__STDC_INT_AS_SSIZE_T _vcscanf([[in, format]] char const *format, $va_list args) {
	return _vcscanf_l(format, NULL, args);
}

[[decl_include("<features.h>"), wunused, requires_function(_vcscanf_s_l)]]
__STDC_INT_AS_SSIZE_T _vcscanf_s([[in, format]] char const *format, $va_list args) {
	return _vcscanf_s_l(format, NULL, args);
}



/************************************************************************/
/* Varargs wrappers.                                                    */
/************************************************************************/
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cprintf([[in, format]] char const *format, ...) %{printf("_vcprintf")}
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cprintf_l([[in, format]] char const *format, $locale_t locale, ...) %{printf("_vcprintf_l")}
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cprintf_s([[in, format]] char const *format, ...) %{printf("_vcprintf_s")}
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cprintf_s_l([[in, format]] char const *format, $locale_t locale, ...) %{printf("_vcprintf_s_l")}
[[crt_intern_alias("_cprintf")]] /* Normal printf already supports positional arguments! */
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cprintf_p([[in, format]] char const *format, ...) %{printf("_vcprintf_p")}
[[crt_intern_alias("_cprintf_l")]] /* Normal printf already supports positional arguments! */
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cprintf_p_l([[in, format]] char const *format, $locale_t locale, ...) %{printf("_vcprintf_p_l")}
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _cscanf([[in, format]] char const *format, ...) %{printf("_vcscanf")}
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _cscanf_l([[in, format]] char const *format, $locale_t locale, ...) %{printf("_vcscanf_l")}
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _cscanf_s([[in, format]] char const *format, ...) %{printf("_vcscanf_s")}
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _cscanf_s_l([[in, format]] char const *format, $locale_t locale, ...) %{printf("_vcscanf_s_l")}



/************************************************************************/
/* Unescaped aliases                                                    */
/************************************************************************/
%[insert:function(cgets = _cgets)]
%[insert:function(cputs = _cputs)]
%[insert:function(getch = _getch)]
%[insert:function(getche = _getche)]
%[insert:function(kbhit = _kbhit)]
%[insert:function(putch = _putch)]
%[insert:function(ungetch = _ungetch)]
%[insert:function(cprintf = _cprintf)]
%[insert:function(cscanf = _cscanf)]


%
%
%
%
%
%
%/* Functions also defined by DJGPP */
%

@@>> clreol(3)
@@Clear all cells from the cursor (inclusive) until the end
@@of the  current  line.  (s.a.  `AC_EL(ANSITTY_EL_AFTER)')
[[requires_function(_cputs)]]
void clreol(void) {
	_cputs("\033[K"); /* AC_EL(ANSITTY_EL_AFTER) */
}

@@>> clrscr(3)
@@Clear the entire screen (s.a. `AC_ED(ANSITTY_CLS_ALL)')
[[requires_function(_cputs)]]
void clrscr(void) {
	_cputs("\033[2J"); /* AC_ED(ANSITTY_CLS_ALL) */
}

@@>> gotoxy(3)
@@Set the cursor {x,y} position (s.a. `AC_CUP(y, x)')
[[requires_function(_cprintf)]]
void gotoxy(int x, int y) {
	_cprintf("\033[%d;%dH", y, x); /* AC_CUP(y, x) */
}

@@>> delline(3)
@@Delete the line at the current cursor position, moving  the
@@screen contents underneath up one line. (s.a. `AC_DL("1")')
[[requires_function(_cputs)]]
void delline(void) {
	_cputs("\033[M"); /* AC_DL("1") */
}

@@>> insline(3)
@@Insert a blank line at the current cursor position, moving the
@@screen  contents underneath down one line. (s.a. `AC_IL("1")')
[[requires_function(_cputs)]]
void insline(void) {
	_cputs("\033[L"); /* AC_IL("1") */
}

@@>> highvideo(3)
@@Brighten text foreground color (s.a. `AC_FGBRIGHT')
[[requires_function(_cputs)]]
void highvideo(void) {
	_cputs("\033[1m"); /* AC_FGBRIGHT */
}

@@>> lowvideo(3)
@@Darken text foreground color (s.a. `AC_FGDARK')
[[requires_function(_cputs)]]
void lowvideo(void) {
	_cputs("\033[2m"); /* AC_FGDARK */
}

@@>> normvideo(3)
@@Reset all graphics attributes to normal (s.a. `AC_DEFATTR')
[[requires_function(_cputs)]]
void normvideo(void) {
	_cputs("\033[m"); /* AC_DEFATTR */
}



%[push_macro @undef {
	COLORS BLACK BLUE GREEN CYAN RED MAGENTA BROWN LIGHTGRAY DARKGRA
	LIGHTBLUE LIGHTGREEN LIGHTCYAN LIGHTRED LIGHTMAGENTA YELLOW WHITE
}]%{

/* CONIO color codes for `textcolor(3)' and `textbackground(3)' */
enum COLORS {
	BLACK        = 0x0,
	BLUE         = 0x1,
	GREEN        = 0x2,
	CYAN         = 0x3,
	RED          = 0x4,
	MAGENTA      = 0x5,
	BROWN        = 0x6,
	LIGHTGRAY    = 0x7,
	DARKGRAY     = 0x8,
	LIGHTBLUE    = 0x9,
	LIGHTGREEN   = 0xa,
	LIGHTCYAN    = 0xb,
	LIGHTRED     = 0xc,
	LIGHTMAGENTA = 0xd,
	YELLOW       = 0xe,
	WHITE        = 0xf
};
}%[pop_macro]

%[define(CONIO_BLACK        = 0x0)]
%[define(CONIO_BLUE         = 0x1)]
%[define(CONIO_GREEN        = 0x2)]
%[define(CONIO_CYAN         = 0x3)]
%[define(CONIO_RED          = 0x4)]
%[define(CONIO_MAGENTA      = 0x5)]
%[define(CONIO_BROWN        = 0x6)]
%[define(CONIO_LIGHTGRAY    = 0x7)]
%[define(CONIO_DARKGRAY     = 0x8)]
%[define(CONIO_LIGHTBLUE    = 0x9)]
%[define(CONIO_LIGHTGREEN   = 0xa)]
%[define(CONIO_LIGHTCYAN    = 0xb)]
%[define(CONIO_LIGHTRED     = 0xc)]
%[define(CONIO_LIGHTMAGENTA = 0xd)]
%[define(CONIO_YELLOW       = 0xe)]
%[define(CONIO_WHITE        = 0xf)]

@@>> textcolor(3)
@@@param: color: Color code (s.a. constants in `<conio.h>')
[[requires_function(_cprintf)]]
void textcolor(int color) {
	switch (color) {
	case CONIO_BLACK:        color = 30; break; /* AC_FG_BLACK   */
	case CONIO_BLUE:         color = 34; break; /* AC_FG_NAVY    */
	case CONIO_GREEN:        color = 32; break; /* AC_FG_GREEN   */
	case CONIO_CYAN:         color = 36; break; /* AC_FG_TEAL    */
	case CONIO_RED:          color = 31; break; /* AC_FG_MAROON  */
	case CONIO_MAGENTA:      color = 35; break; /* AC_FG_PURPLE  */
	case CONIO_BROWN:        color = 33; break; /* AC_FG_OLIVE   */
	case CONIO_LIGHTGRAY:    color = 37; break; /* AC_FG_SILVER  */
	case CONIO_DARKGRAY:     color = 90; break; /* AC_FG_GREY    */
	case CONIO_LIGHTBLUE:    color = 94; break; /* AC_FG_BLUE    */
	case CONIO_LIGHTGREEN:   color = 92; break; /* AC_FG_LIME    */
	case CONIO_LIGHTCYAN:    color = 96; break; /* AC_FG_AQUA    */
	case CONIO_LIGHTRED:     color = 91; break; /* AC_FG_RED     */
	case CONIO_LIGHTMAGENTA: color = 95; break; /* AC_FG_FUCHSIA */
	case CONIO_YELLOW:       color = 93; break; /* AC_FG_YELLOW  */
	case CONIO_WHITE:        color = 97; break; /* AC_FG_WHITE   */
	default: break;
	}
	_cprintf("\033[%dm", color);
}

@@>> textbackground(3)
@@@param: color: Color code (s.a. constants in `<conio.h>')
[[requires_function(_cprintf)]]
void textbackground(int color) {
	switch (color) {
	case CONIO_BLACK:        color = 40;  break; /* AC_BG_BLACK   */
	case CONIO_BLUE:         color = 44;  break; /* AC_BG_NAVY    */
	case CONIO_GREEN:        color = 42;  break; /* AC_BG_GREEN   */
	case CONIO_CYAN:         color = 46;  break; /* AC_BG_TEAL    */
	case CONIO_RED:          color = 41;  break; /* AC_BG_MAROON  */
	case CONIO_MAGENTA:      color = 45;  break; /* AC_BG_PURPLE  */
	case CONIO_BROWN:        color = 43;  break; /* AC_BG_OLIVE   */
	case CONIO_LIGHTGRAY:    color = 47;  break; /* AC_BG_SILVER  */
	case CONIO_DARKGRAY:     color = 100; break; /* AC_BG_GREY    */
	case CONIO_LIGHTBLUE:    color = 104; break; /* AC_BG_BLUE    */
	case CONIO_LIGHTGREEN:   color = 102; break; /* AC_BG_LIME    */
	case CONIO_LIGHTCYAN:    color = 106; break; /* AC_BG_AQUA    */
	case CONIO_LIGHTRED:     color = 101; break; /* AC_BG_RED     */
	case CONIO_LIGHTMAGENTA: color = 105; break; /* AC_BG_FUCHSIA */
	case CONIO_YELLOW:       color = 103; break; /* AC_BG_YELLOW  */
	case CONIO_WHITE:        color = 107; break; /* AC_BG_WHITE   */
	default: break;
	}
	_cprintf("\033[%dm", color);
}

@@>> textattr(3)
@@Set text attributes: `textcolor(attr & 0x0f)' and `textbackground((attr & 0xf0) >> 8)'
[[requires_function(textcolor, textbackground)]]
void textattr(int attr) {
	textcolor(attr & 0x0f);
	textbackground((attr & 0xf0) >> 8);
}

@@>> clearkeybuf(3)
@@Flush all unread input (usually keyboard) data pending on the terminal
[[requires($extended_include_prefix("<asm/os/termios.h>")
           defined(__TCSADRAIN) && defined(__CRT_HAVE_stdtty) &&
           $has_function(__fpurge, fileno, fgetc_unlocked, tcgetattr, tcsetattr))]]
[[impl_include("<bits/types.h>", "<asm/os/termios.h>", "<bits/os/termios.h>", "<libc/template/stdtty.h>")]]
void clearkeybuf(void) {
	struct termios ios;
	FILE *fp = stdtty;
	fd_t fd  = fileno(fp);

	/* Flush (read: "drain") kernel-space buffer. */
	tcgetattr(fd, &ios);
	tcsetattr(fd, __TCSADRAIN, &ios);

	/* Flush (read: "purge") user-space buffer. */
	__fpurge(fp);
}

@@>> _conio_getpass(3)
@@CONIO version of getpass(3). But note the slightly different variant from `<unistd.h>'
[[guard, requires_function(getpass_r), exposed_name("getpass")]]
char *_conio_getpass([[in]] const char *prompt, [[inout]] char *str) {
	unsigned char buflen = (unsigned char)str[0];
	char *result = getpass_r(prompt, &str[2], buflen);
	if (result != NULL) {
		str[1] = (unsigned char)strlen(result);
		result = str;
	}
	return result;
}

%[define_c_language_keyword(__KOS_FIXED_CONST)]

@@>> cputsxy(3)
@@Combination of `gotoxy(3)' and `cputs(3)'
[[requires_function(gotoxy, _cputs)]]
void cputsxy(int x, int y, [[in]] char __KOS_FIXED_CONST *str) {
	gotoxy(x, y);
	_cputs(str);
}

@@>> putchxy(3)
@@Combination of `gotoxy(3)' and `putch(3)'
[[requires_function(gotoxy, _putch)]]
void putchxy(int x, int y, char ch) {
	gotoxy(x, y);
	_putch(ch);
}

%[insert:guarded_function(delay = _sleep)] /* Also declared in <dos.h> */

[[static, decl_include("<hybrid/typecore.h>")]]
[[requires((defined(__KOS__) && defined(__CRT_HAVE_stdtty) && $has_function(fileno, ioctl)) ||
           $has_function(_getch, _ungetch, _cscanf))]]
[[impl_include("<libc/template/stdtty.h>", "<kos/ioctl/video.h>", "<bits/crt/inttypes.h>")]]
int _conio_wherexy([[out]] $uint16_t xy[2]) {
@@pp_if defined(__KOS__) && defined(__CRT_HAVE_stdtty) && $has_function(fileno, ioctl)@@
	return (int)ioctl(fileno(stdtty), @VID_IOC_GETCURSOR@, xy);
@@pp_else@@
	char putback[64];
	unsigned int i;
	int result;
	_cputs("\033[6n"); /* DSR */
	for (i = 0; i < 64; ++i) {
		int ch = _getch();
		if (ch == '\033')
			break;
		putback[i] = ch;
	}
	result = _cscanf("[%" __SCA2_PREFIX "u"
	                 ";%" __SCA2_PREFIX "uR",
	                 &xy[1], &xy[0]) == 2
	         ? 0
	         : -1;
	while (i) {
		--i;
		_ungetch(putback[i]);
	}
	return result;
@@pp_endif@@
}

@@>> wherex(3)
@@Return the current cursor 'X' position (1-based)
[[requires_function(_conio_wherexy)]]
int wherex(void) {
	uint16_t xy[2];
	if (_conio_wherexy(xy))
		return -1;
	return xy[0] + 1;
}

@@>> wherey(3)
@@Return the current cursor 'Y' position (1-based)
[[requires_function(_conio_wherexy)]]
int wherey(void) {
	uint16_t xy[2];
	if (_conio_wherexy(xy))
		return -1;
	return xy[1] + 1;
}

@@>> window(3)
@@Set scroll range and margains to the specified rectangle (1-based)
[[requires_function(_cprintf)]]
void window(int left, int top, int right, int bottom) {
	_cprintf("\033[?69h"    /* DECLRMM  (enable scroll margins) */
	         "\033[%d;%ds"  /* DECSLRM  (set scroll margins) */
	         "\033[%d;%dr", /* DECSTBM  (set scroll region; iow: top/bottom) */
	         left, right, top, bottom);
}

@@>> movetext(3)
@@Duplicate a  given rectangle  (1-based)  of on-screen  text  at
@@another location. Overlapping rectangles are handled correctly.
[[requires(defined(__KOS__) && defined(__CRT_HAVE_stdtty) && $has_function(fileno, ioctl))]]
[[impl_include("<bits/types.h>", "<libc/template/stdtty.h>", "<kos/ioctl/video.h>", "<parts/malloca.h>")]]
int movetext(int left, int top, int right, int bottom, int destleft, int desttop) {
	@struct vidttyinfo@ info;
	@struct vidttycelldata@ data;
	fd_t fd = fileno(stdtty);
	uint16_t args[6], i, error;
	if (ioctl(fd, @VID_IOC_GETTTYINFO@, &info) != 0)
		goto err;
	args[0] = (uint16_t)(unsigned int)left;
	args[1] = (uint16_t)(unsigned int)right;
	args[2] = (uint16_t)(unsigned int)destleft;
	args[3] = (uint16_t)(unsigned int)top;
	args[4] = (uint16_t)(unsigned int)bottom;
	args[5] = (uint16_t)(unsigned int)desttop;
	for (i = 0; i < 6; ++i) {
		uint16_t v = args[i] - 1;
		if (v < 0) {
			v = 0;
		} else {
			uint16_t maxval;
			maxval = i >= 3 ? info.@vti_cellh@ : info.@vti_cellw@;
			if (v > maxval)
				v = maxval;
		}
		args[i] = v;
	}
	if (args[0]/*left*/ >= args[1]/*right*/)
		goto done;
	if (args[3]/*top*/ >= args[4]/*bottom*/)
		goto done;
	bzero(&data, sizeof(data));
	data.@vcd_x@ = args[0]/*left*/;
	data.@vcd_y@ = args[3]/*top*/;
	data.@vcd_w@ = args[1]/*right*/ - args[0]/*left*/;
	data.@vcd_h@ = args[4]/*bottom*/ - args[3]/*top*/;
	data.@vcd_dat@ = (byte_t *)__malloca(data.@vcd_w@ * data.@vcd_h@ * info.@vti_cellsize@);
	if unlikely(!data.@vcd_dat@)
		goto err;
	error = ioctl(fd, @VID_IOC_GETCELLDATA@, &data);
	if likely(error == 0) {
		data.@vcd_x@ = args[2]/*destleft*/;
		data.@vcd_y@ = args[5]/*desttop*/;
		error = ioctl(fd, @VID_IOC_SETCELLDATA@, &data);
	}
	__freea(data.@vcd_dat@);
	if unlikely(error != 0)
		goto err;
done:
	return 0;
err:
	return 1;
}



/*
#define _NOCURSOR      0
#define _NORMALCURSOR  20
#define _SOLIDCURSOR   100
struct text_info {
	unsigned char winleft;
	unsigned char wintop;
	unsigned char winright;
	unsigned char winbottom;
	unsigned char attribute;
	unsigned char normattr;
	unsigned char currmode;
	unsigned char screenheight;
	unsigned char screenwidth;
	unsigned char curx;
	unsigned char cury;
};
struct char_info {
	char           letter;
	unsigned short attr;
};
*/

// TODO: @@>> switchbackground(3)
// TODO: @@Set background to `color' in all cells within the current "window" (s.a. `window(3)')
// TODO: void switchbackground(int color);

// TODO: @@>> flashbackground(3)
// TODO: @@Does `switchbackground(color); delay(ms);', then restores
// TODO: @@the background color of all previously affected cells.
// TODO: void flashbackground(int color, int ms);

// TODO: @@>> gettextinfo(3)
// TODO: @@Get terminal information
// TODO: void gettextinfo(struct text_info *r);
// TODO:     Add a custom VID_IOC_* ioctl() for this, as well as `libkernel32/wincon.c'

// TODO: @@>> intensevideo(3)
// TODO: @@Configure display for textattr(0x80) --> "bright background"
// TODO: void intensevideo(void);

// TODO: @@>> blinkvideo(3)
// TODO: @@Configure display for textattr(0x80) --> "blinking text"
// TODO: void blinkvideo(void);

// TODO: @@>> _conio_gettext(3)
// TODO: @@Convert on-screen cells back into raw text
// TODO: int _conio_gettext(int left, int top, int right, int bottom, struct char_info *destin);
// TODO:     Once cell buffer formats have been unified, implement this one via `VID_IOC_GETCELLDATA'

// TODO: #define gettext _conio_gettext  // NOTE: <libintl.h> should override this one when both are #include'ed

// TODO: @@>> puttext(3)
// TODO: @@Fill on-screen cells with textual contents (s.a. `_conio_gettext')
// TODO: int puttext(int left, int top, int right, int bottom, struct char_info *source);

// TODO: @@>> _setcursortype(3)
// TODO: @@Sets cursor height to be `type' percent the height of a full cell
// TODO: void _setcursortype(int type);

// TODO: @@>> _set_screen_lines(3)
// TODO: @@Sets the terminal to use a resolution of `80x{nlines}'
// TODO: void _set_screen_lines(int nlines);

// TODO: enum text_modes { LASTMODE=-1, BW40=0, C40, BW80, C80, MONO=7, C4350=64 };

// TODO: @@>> textmode(3)
// TODO: @@@param: mode: One of the values from `enum text_modes'
// TODO: void textmode(int mode);



%{

__SYSDECL_END
#endif /* __CC__ */

}
