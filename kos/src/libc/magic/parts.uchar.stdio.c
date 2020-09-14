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

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]

%{
#include <features.h>
#ifndef _STDIO_H
#include <stdio.h>
#endif /* !_STDIO_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

__SYSDECL_BEGIN

#ifdef __CC__

}

getchar16(*) %{uchar16("getwchar")}
getchar32(*) %{uchar32("getwchar")}
fgetc16(*) %{uchar16("fgetwc")}
fgetc32(*) %{uchar32("fgetwc")}
%[insert:function(getc16 = fgetc16)]
%[insert:function(getc32 = fgetc32)]

putchar16(*) %{uchar16("putwchar")}
putchar32(*) %{uchar32("putwchar")}
fputc16(*) %{uchar16("fputwc")}
fputc32(*) %{uchar32("fputwc")}
%[insert:function(putc16 = fputc16)]
%[insert:function(putc32 = fputc32)]

fgetc16s(*) %{uchar16("fgetws")}
fgetc32s(*) %{uchar32("fgetws")}
fputc16s(*) %{uchar16("fputws")}
fputc32s(*) %{uchar32("fputws")}

ungetc16(*) %{uchar16("ungetwc")}
ungetc32(*) %{uchar32("ungetwc")}

%
%#if defined(__USE_ISOC95) || defined(__USE_UNIX98) || defined(__USE_DOS)
fc16printf(*) %{uchar16("fwprintf")}
fc32printf(*) %{uchar32("fwprintf")}
vfc16printf(*) %{uchar16("vfwprintf")}
vfc32printf(*) %{uchar32("vfwprintf")}
c16printf(*) %{uchar16("wprintf")}
c32printf(*) %{uchar32("wprintf")}
vc16printf(*) %{uchar16("vwprintf")}
vc32printf(*) %{uchar32("vwprintf")}

fc16scanf(*) %{uchar16("fwscanf")}
fc32scanf(*) %{uchar32("fwscanf")}
c16scanf(*) %{uchar16("wscanf")}
c32scanf(*) %{uchar32("wscanf")}

sc16scanf(*) %{uchar16("swscanf")}
sc32scanf(*) %{uchar32("swscanf")}

vsc16printf(*) %{uchar16("vswprintf")}
vsc32printf(*) %{uchar32("vswprintf")}
sc16printf(*) %{uchar16("swprintf")}
sc32printf(*) %{uchar32("swprintf")}
%#endif /* __USE_ISOC95 || __USE_UNIX98 || __USE_DOS */

%
%#ifdef __USE_ISOC99
vfc16scanf(*) %{uchar16("vfwscanf")}
vfc32scanf(*) %{uchar32("vfwscanf")}
vc16scanf(*) %{uchar16("vwscanf")}
vc32scanf(*) %{uchar32("vwscanf")}
vsc16scanf(*) %{uchar16("vswscanf")}
vsc32scanf(*) %{uchar32("vswscanf")}
%#endif /* __USE_ISOC99 */

%
%#ifdef __USE_GNU
getchar16_unlocked(*) %{uchar16("getwchar_unlocked")}
getchar32_unlocked(*) %{uchar32("getwchar_unlocked")}
putchar16_unlocked(*) %{uchar16("putwchar_unlocked")}
putchar32_unlocked(*) %{uchar32("putwchar_unlocked")}
fgetc16_unlocked(*) %{uchar16("fgetwc_unlocked")}
fgetc32_unlocked(*) %{uchar32("fgetwc_unlocked")}
fputc16_unlocked(*) %{uchar16("fputwc_unlocked")}
fputc32_unlocked(*) %{uchar32("fputwc_unlocked")}

%[insert:function(getc16_unlocked = fgetc16_unlocked)]
%[insert:function(getc32_unlocked = fgetc32_unlocked)]
%[insert:function(putc16_unlocked = fputc16_unlocked)]
%[insert:function(putc32_unlocked = fputc32_unlocked)]

fgetc16s_unlocked(*) %{uchar16("fgetws_unlocked")}
fgetc32s_unlocked(*) %{uchar32("fgetws_unlocked")}
fputc16s_unlocked(*) %{uchar16("fputws_unlocked")}
fputc32s_unlocked(*) %{uchar32("fputws_unlocked")}
%#endif /* __USE_GNU */

%
%#ifdef __USE_XOPEN2K8
open_c16memstream(*) %{uchar16("open_wmemstream")}
open_c32memstream(*) %{uchar32("open_wmemstream")}
%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_KOS
file_c16printer(*) %{uchar16("file_wprinter")}
file_c32printer(*) %{uchar32("file_wprinter")}
file_c16printer_unlocked(*) %{uchar16("file_wprinter_unlocked")}
file_c32printer_unlocked(*) %{uchar32("file_wprinter_unlocked")}

ungetc16_unlocked(*) %{uchar16("ungetwc_unlocked")}
ungetc32_unlocked(*) %{uchar32("ungetwc_unlocked")}

vfc16printf_unlocked(*) %{uchar16("vfwprintf_unlocked")}
vfc32printf_unlocked(*) %{uchar32("vfwprintf_unlocked")}
fc16printf_unlocked(*) %{uchar16("fwprintf_unlocked")}
fc32printf_unlocked(*) %{uchar32("fwprintf_unlocked")}
c16printf_unlocked(*) %{uchar16("wprintf_unlocked")}
c32printf_unlocked(*) %{uchar32("wprintf_unlocked")}
vc16printf_unlocked(*) %{uchar16("vwprintf_unlocked")}
vc32printf_unlocked(*) %{uchar32("vwprintf_unlocked")}

vfc16scanf_unlocked(*) %{uchar16("vfwscanf_unlocked")}
vfc32scanf_unlocked(*) %{uchar32("vfwscanf_unlocked")}
vc16scanf_unlocked(*) %{uchar16("vwscanf_unlocked")}
vc32scanf_unlocked(*) %{uchar32("vwscanf_unlocked")}
fc16scanf_unlocked(*) %{uchar16("fwscanf_unlocked")}
fc32scanf_unlocked(*) %{uchar32("fwscanf_unlocked")}
c16scanf_unlocked(*) %{uchar16("wscanf_unlocked")}
c32scanf_unlocked(*) %{uchar32("wscanf_unlocked")}

/* Functions from `parts.wchar.stdio.c' */
c16remove(*) %{uchar16("wremove")}
c32remove(*) %{uchar32("wremove")}
c16fopen(*) %{uchar16("wfopen")}
c32fopen(*) %{uchar32("wfopen")}
c16freopen(*) %{uchar16("wfreopen")}
c32freopen(*) %{uchar32("wfreopen")}
c16popen(*) %{uchar16("wpopen")}
c32popen(*) %{uchar32("wpopen")}
%#endif /* __USE_KOS */


%{

#endif /* __CC__ */

__SYSDECL_END

}

