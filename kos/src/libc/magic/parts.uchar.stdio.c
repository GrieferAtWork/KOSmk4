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

getchar16:(*) %{uchar(getwchar)}
getchar32:(*) %{uchar(getwchar)}
fgetc16:(*) %{uchar(fgetwc)}
fgetc32:(*) %{uchar(fgetwc)}
getc16:(*) %{uchar(getwc)}
getc32:(*) %{uchar(getwc)}

putchar16:(*) %{uchar(putwchar)}
putchar32:(*) %{uchar(putwchar)}
fputc16:(*) %{uchar(fputwc)}
fputc32:(*) %{uchar(fputwc)}
putc16:(*) %{uchar(putwc)}
putc32:(*) %{uchar(putwc)}

fgetc16s:(*) %{uchar(fgetws)}
fgetc32s:(*) %{uchar(fgetws)}
fputc16s:(*) %{uchar(fputws)}
fputc32s:(*) %{uchar(fputws)}

ungetc16:(*) %{uchar(ungetwc)}
ungetc32:(*) %{uchar(ungetwc)}

%
%#if defined(__USE_ISOC95) || defined(__USE_UNIX98) || defined(__USE_DOS)
fc16printf:(*) %{uchar(fwprintf)}
fc32printf:(*) %{uchar(fwprintf)}
vfc16printf:(*) %{uchar(vfwprintf)}
vfc32printf:(*) %{uchar(vfwprintf)}
c16printf:(*) %{uchar(wprintf)}
c32printf:(*) %{uchar(wprintf)}
vc16printf:(*) %{uchar(vwprintf)}
vc32printf:(*) %{uchar(vwprintf)}

fc16scanf:(*) %{uchar(fwscanf)}
fc32scanf:(*) %{uchar(fwscanf)}
c16scanf:(*) %{uchar(wscanf)}
c32scanf:(*) %{uchar(wscanf)}

sc16scanf:(*) %{uchar(swscanf)}
sc32scanf:(*) %{uchar(swscanf)}

vsc16printf:(*) %{uchar(vswprintf)}
vsc32printf:(*) %{uchar(vswprintf)}
sc16printf:(*) %{uchar(swprintf)}
sc32printf:(*) %{uchar(swprintf)}
%#endif /* __USE_ISOC95 || __USE_UNIX98 || __USE_DOS */

%
%#ifdef __USE_ISOC99
vfc16scanf:(*) %{uchar(vfwscanf)}
vfc32scanf:(*) %{uchar(vfwscanf)}
vc16scanf:(*) %{uchar(vwscanf)}
vc32scanf:(*) %{uchar(vwscanf)}
vsc16scanf:(*) %{uchar(vswscanf)}
vsc32scanf:(*) %{uchar(vswscanf)}
%#endif /* __USE_ISOC99 */

%
%#ifdef __USE_GNU
getchar16_unlocked:(*) %{uchar(getwchar_unlocked)}
getchar32_unlocked:(*) %{uchar(getwchar_unlocked)}
putchar16_unlocked:(*) %{uchar(putwchar_unlocked)}
putchar32_unlocked:(*) %{uchar(putwchar_unlocked)}
getc16_unlocked:(*) %{uchar(getwc_unlocked)}
getc32_unlocked:(*) %{uchar(getwc_unlocked)}
fgetc16_unlocked:(*) %{uchar(fgetwc_unlocked)}
fgetc32_unlocked:(*) %{uchar(fgetwc_unlocked)}
putc16_unlocked:(*) %{uchar(putwc_unlocked)}
putc32_unlocked:(*) %{uchar(putwc_unlocked)}
fputc16_unlocked:(*) %{uchar(fputwc_unlocked)}
fputc32_unlocked:(*) %{uchar(fputwc_unlocked)}
fgetc16s_unlocked:(*) %{uchar(fgetws_unlocked)}
fgetc32s_unlocked:(*) %{uchar(fgetws_unlocked)}
fputc16s_unlocked:(*) %{uchar(fputws_unlocked)}
fputc32s_unlocked:(*) %{uchar(fputws_unlocked)}
%#endif /* __USE_GNU */

%
%#ifdef __USE_XOPEN2K8
open_c16memstream:(*) %{uchar(open_wmemstream)}
open_c32memstream:(*) %{uchar(open_wmemstream)}
%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_KOS
file_c16printer:(*) %{uchar(file_wprinter)}
file_c32printer:(*) %{uchar(file_wprinter)}
file_c16printer_unlocked:(*) %{uchar(file_wprinter_unlocked)}
file_c32printer_unlocked:(*) %{uchar(file_wprinter_unlocked)}

ungetc16_unlocked:(*) %{uchar(ungetwc_unlocked)}
ungetc32_unlocked:(*) %{uchar(ungetwc_unlocked)}

vfc16printf_unlocked:(*) %{uchar(vfwprintf_unlocked)}
vfc32printf_unlocked:(*) %{uchar(vfwprintf_unlocked)}
fc16printf_unlocked:(*) %{uchar(fwprintf_unlocked)}
fc32printf_unlocked:(*) %{uchar(fwprintf_unlocked)}
c16printf_unlocked:(*) %{uchar(wprintf_unlocked)}
c32printf_unlocked:(*) %{uchar(wprintf_unlocked)}
vc16printf_unlocked:(*) %{uchar(vwprintf_unlocked)}
vc32printf_unlocked:(*) %{uchar(vwprintf_unlocked)}

vfc16scanf_unlocked:(*) %{uchar(vfwscanf_unlocked)}
vfc32scanf_unlocked:(*) %{uchar(vfwscanf_unlocked)}
vc16scanf_unlocked:(*) %{uchar(vwscanf_unlocked)}
vc32scanf_unlocked:(*) %{uchar(vwscanf_unlocked)}
fc16scanf_unlocked:(*) %{uchar(fwscanf_unlocked)}
fc32scanf_unlocked:(*) %{uchar(fwscanf_unlocked)}
c16scanf_unlocked:(*) %{uchar(wscanf_unlocked)}
c32scanf_unlocked:(*) %{uchar(wscanf_unlocked)}

/* Functions from `parts.wchar.stdio.c' */
c16remove:(*) %{uchar(wremove)}
c32remove:(*) %{uchar(wremove)}
c16fopen:(*) %{uchar(wfopen)}
c32fopen:(*) %{uchar(wfopen)}
c16freopen:(*) %{uchar(wfreopen)}
c32freopen:(*) %{uchar(wfreopen)}
c16popen:(*) %{uchar(wpopen)}
c32popen:(*) %{uchar(wpopen)}
%#endif /* __USE_KOS */


%{

#endif /* __CC__ */

__SYSDECL_END

}

