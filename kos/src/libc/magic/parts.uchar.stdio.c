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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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

[alias(*)][attribute(*)] getchar16:(*) %{uchar(getwchar)}
[alias(*)][attribute(*)] getchar32:(*) %{uchar(getwchar)}
[alias(*)][attribute(*)] fgetc16:(*) %{uchar(fgetwc)}
[alias(*)][attribute(*)] fgetc32:(*) %{uchar(fgetwc)}
[alias(*)][attribute(*)] getc16:(*) %{uchar(getwc)}
[alias(*)][attribute(*)] getc32:(*) %{uchar(getwc)}

[alias(*)][attribute(*)] putchar16:(*) %{uchar(putwchar)}
[alias(*)][attribute(*)] putchar32:(*) %{uchar(putwchar)}
[alias(*)][attribute(*)] fputc16:(*) %{uchar(fputwc)}
[alias(*)][attribute(*)] fputc32:(*) %{uchar(fputwc)}
[alias(*)][attribute(*)] putc16:(*) %{uchar(putwc)}
[alias(*)][attribute(*)] putc32:(*) %{uchar(putwc)}

[alias(*)][attribute(*)] fgetc16s:(*) %{uchar(fgetws)}
[alias(*)][attribute(*)] fgetc32s:(*) %{uchar(fgetws)}
[alias(*)][attribute(*)] fputc16s:(*) %{uchar(fputws)}
[alias(*)][attribute(*)] fputc32s:(*) %{uchar(fputws)}

[alias(*)][attribute(*)] ungetc16:(*) %{uchar(ungetwc)}
[alias(*)][attribute(*)] ungetc32:(*) %{uchar(ungetwc)}

%
%#if defined(__USE_ISOC95) || defined(__USE_UNIX98) || defined(__USE_DOS)
[alias(*)][attribute(*)] fc16printf:(*) %{uchar(fwprintf)}
[alias(*)][attribute(*)] fc32printf:(*) %{uchar(fwprintf)}
[alias(*)][attribute(*)] vfc16printf:(*) %{uchar(vfwprintf)}
[alias(*)][attribute(*)] vfc32printf:(*) %{uchar(vfwprintf)}
[alias(*)][attribute(*)] c16printf:(*) %{uchar(wprintf)}
[alias(*)][attribute(*)] c32printf:(*) %{uchar(wprintf)}
[alias(*)][attribute(*)] vc16printf:(*) %{uchar(vwprintf)}
[alias(*)][attribute(*)] vc32printf:(*) %{uchar(vwprintf)}

[alias(*)][attribute(*)] fc16scanf:(*) %{uchar(fwscanf)}
[alias(*)][attribute(*)] fc32scanf:(*) %{uchar(fwscanf)}
[alias(*)][attribute(*)] c16scanf:(*) %{uchar(wscanf)}
[alias(*)][attribute(*)] c32scanf:(*) %{uchar(wscanf)}

[alias(*)][attribute(*)] sc16scanf:(*) %{uchar(swscanf)}
[alias(*)][attribute(*)] sc32scanf:(*) %{uchar(swscanf)}

[alias(*)][attribute(*)] vsc16printf:(*) %{uchar(vswprintf)}
[alias(*)][attribute(*)] vsc32printf:(*) %{uchar(vswprintf)}
[alias(*)][attribute(*)] sc16printf:(*) %{uchar(swprintf)}
[alias(*)][attribute(*)] sc32printf:(*) %{uchar(swprintf)}
%#endif /* __USE_ISOC95 || __USE_UNIX98 || __USE_DOS */

%
%#ifdef __USE_ISOC99
[alias(*)][attribute(*)] vfc16scanf:(*) %{uchar(vfwscanf)}
[alias(*)][attribute(*)] vfc32scanf:(*) %{uchar(vfwscanf)}
[alias(*)][attribute(*)] vc16scanf:(*) %{uchar(vwscanf)}
[alias(*)][attribute(*)] vc32scanf:(*) %{uchar(vwscanf)}
[alias(*)][attribute(*)] vsc16scanf:(*) %{uchar(vswscanf)}
[alias(*)][attribute(*)] vsc32scanf:(*) %{uchar(vswscanf)}
%#endif /* __USE_ISOC99 */

%
%#ifdef __USE_GNU
[alias(*)][attribute(*)] getchar16_unlocked:(*) %{uchar(getwchar_unlocked)}
[alias(*)][attribute(*)] getchar32_unlocked:(*) %{uchar(getwchar_unlocked)}
[alias(*)][attribute(*)] putchar16_unlocked:(*) %{uchar(putwchar_unlocked)}
[alias(*)][attribute(*)] putchar32_unlocked:(*) %{uchar(putwchar_unlocked)}
[alias(*)][attribute(*)] getc16_unlocked:(*) %{uchar(getwc_unlocked)}
[alias(*)][attribute(*)] getc32_unlocked:(*) %{uchar(getwc_unlocked)}
[alias(*)][attribute(*)] fgetc16_unlocked:(*) %{uchar(fgetwc_unlocked)}
[alias(*)][attribute(*)] fgetc32_unlocked:(*) %{uchar(fgetwc_unlocked)}
[alias(*)][attribute(*)] putc16_unlocked:(*) %{uchar(putwc_unlocked)}
[alias(*)][attribute(*)] putc32_unlocked:(*) %{uchar(putwc_unlocked)}
[alias(*)][attribute(*)] fputc16_unlocked:(*) %{uchar(fputwc_unlocked)}
[alias(*)][attribute(*)] fputc32_unlocked:(*) %{uchar(fputwc_unlocked)}
[alias(*)][attribute(*)] fgetc16s_unlocked:(*) %{uchar(fgetws_unlocked)}
[alias(*)][attribute(*)] fgetc32s_unlocked:(*) %{uchar(fgetws_unlocked)}
[alias(*)][attribute(*)] fputc16s_unlocked:(*) %{uchar(fputws_unlocked)}
[alias(*)][attribute(*)] fputc32s_unlocked:(*) %{uchar(fputws_unlocked)}
%#endif /* __USE_GNU */

%
%#ifdef __USE_XOPEN2K8
[alias(*)][attribute(*)] open_c16memstream:(*) %{uchar(open_wmemstream)}
[alias(*)][attribute(*)] open_c32memstream:(*) %{uchar(open_wmemstream)}
%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_KOS
[alias(*)][attribute(*)] file_c16printer:(*) %{uchar(file_wprinter)}
[alias(*)][attribute(*)] file_c32printer:(*) %{uchar(file_wprinter)}
[alias(*)][attribute(*)] file_c16printer_unlocked:(*) %{uchar(file_wprinter_unlocked)}
[alias(*)][attribute(*)] file_c32printer_unlocked:(*) %{uchar(file_wprinter_unlocked)}

[alias(*)][attribute(*)] ungetc16_unlocked:(*) %{uchar(ungetwc_unlocked)}
[alias(*)][attribute(*)] ungetc32_unlocked:(*) %{uchar(ungetwc_unlocked)}

[alias(*)][attribute(*)] vfc16printf_unlocked:(*) %{uchar(vfwprintf_unlocked)}
[alias(*)][attribute(*)] vfc32printf_unlocked:(*) %{uchar(vfwprintf_unlocked)}
[alias(*)][attribute(*)] fc16printf_unlocked:(*) %{uchar(fwprintf_unlocked)}
[alias(*)][attribute(*)] fc32printf_unlocked:(*) %{uchar(fwprintf_unlocked)}
[alias(*)][attribute(*)] c16printf_unlocked:(*) %{uchar(wprintf_unlocked)}
[alias(*)][attribute(*)] c32printf_unlocked:(*) %{uchar(wprintf_unlocked)}
[alias(*)][attribute(*)] vc16printf_unlocked:(*) %{uchar(vwprintf_unlocked)}
[alias(*)][attribute(*)] vc32printf_unlocked:(*) %{uchar(vwprintf_unlocked)}

[alias(*)][attribute(*)] vfc16scanf_unlocked:(*) %{uchar(vfwscanf_unlocked)}
[alias(*)][attribute(*)] vfc32scanf_unlocked:(*) %{uchar(vfwscanf_unlocked)}
[alias(*)][attribute(*)] vc16scanf_unlocked:(*) %{uchar(vwscanf_unlocked)}
[alias(*)][attribute(*)] vc32scanf_unlocked:(*) %{uchar(vwscanf_unlocked)}
[alias(*)][attribute(*)] fc16scanf_unlocked:(*) %{uchar(fwscanf_unlocked)}
[alias(*)][attribute(*)] fc32scanf_unlocked:(*) %{uchar(fwscanf_unlocked)}
[alias(*)][attribute(*)] c16scanf_unlocked:(*) %{uchar(wscanf_unlocked)}
[alias(*)][attribute(*)] c32scanf_unlocked:(*) %{uchar(wscanf_unlocked)}

/* Functions from `parts.wchar.stdio.c' */
[alias(*)][attribute(*)] c16remove:(*) %{uchar(wremove)}
[alias(*)][attribute(*)] c32remove:(*) %{uchar(wremove)}
[alias(*)][attribute(*)] c16fopen:(*) %{uchar(wfopen)}
[alias(*)][attribute(*)] c32fopen:(*) %{uchar(wfopen)}
[alias(*)][attribute(*)] c16freopen:(*) %{uchar(wfreopen)}
[alias(*)][attribute(*)] c32freopen:(*) %{uchar(wfreopen)}
[alias(*)][attribute(*)] c16popen:(*) %{uchar(wpopen)}
[alias(*)][attribute(*)] c32popen:(*) %{uchar(wpopen)}
%#endif /* __USE_KOS */


%{

#endif /* __CC__ */

__SYSDECL_END

}

