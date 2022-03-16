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

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{
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

/************************************************************************/
/* WARNING: UTF-16 functions use DOS paths under `DOSFS_ENABLED'        */
/*          s.a. `dosfs_setenabled(3)'                                  */
/************************************************************************/

#ifndef __wint16_t_defined
#define __wint16_t_defined
typedef __WINT16_TYPE__ wint16_t;
typedef __WINT32_TYPE__ wint32_t;
#endif /* !__wint16_t_defined */

}


/* Functions from `parts.wchar.stdio.c' */
c16remove(*) %{uchar16("wremove")}
c32remove(*) %{uchar32("wremove")}
c16rename(*) %{uchar16("wrename")}
c32rename(*) %{uchar32("wrename")}

%
%#ifdef __USE_ATFILE
c16renameat(*) %{uchar16("wrenameat")}
c32renameat(*) %{uchar32("wrenameat")}

%
%#ifdef __USE_KOS
c16removeat(*) %{uchar16("wremoveat")}
c32removeat(*) %{uchar32("wremoveat")}
%#endif /* __USE_KOS */
%#endif /* __USE_ATFILE */

%
%#ifdef __USE_GNU
c16renameat2(*) %{uchar16("wrenameat2")}
c32renameat2(*) %{uchar32("wrenameat2")}
%#endif /* __USE_GNU */

c16fopen(*) %{uchar16("wfopen")}
c32fopen(*) %{uchar32("wfopen")}
c16freopen(*) %{uchar16("wfreopen")}
c32freopen(*) %{uchar32("wfreopen")}
c16popen(*) %{uchar16("wpopen")}
c32popen(*) %{uchar32("wpopen")}




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
%#endif /* __USE_KOS */



%
%
%
%/* uchar variants of DOS stdio functions */
%#ifdef __USE_DOS

%[insert:function(_c16fopen = c16fopen)]
%[insert:function(_c32fopen = c32fopen)]
%[insert:function(_c16freopen = c16freopen)]
%[insert:function(_c32freopen = c32freopen)]
%[insert:function(_fgetchar16 = getchar16)]
%[insert:function(_fgetchar32 = getchar32)]
%[insert:function(_fputchar16 = putchar16)]
%[insert:function(_fputchar32 = putchar32)]
%[insert:function(_c16popen = c16popen)]
%[insert:function(_c32popen = c32popen)]
%[insert:function(_c16remove = c16remove)]
%[insert:function(_c32remove = c32remove)]
%[insert:function(_fgetc16_nolock = fgetc16_unlocked)]
%[insert:function(_fgetc32_nolock = fgetc32_unlocked)]
%[insert:function(_fputc16_nolock = fputc16_unlocked)]
%[insert:function(_fputc32_nolock = fputc32_unlocked)]
%[insert:function(_ungetc16_nolock = ungetc16_unlocked)]
%[insert:function(_ungetc32_nolock = ungetc32_unlocked)]
%[insert:function(_getc16_nolock = fgetc16_unlocked)]
%[insert:function(_getc32_nolock = fgetc32_unlocked)]
%[insert:function(_putc16_nolock = fputc16_unlocked)]
%[insert:function(_putc32_nolock = fputc32_unlocked)]

_c16perror(*) %{uchar16("_wperror")}
_c32perror(*) %{uchar32("_wperror")}


_c16fsopen(*) %{uchar16("_wfsopen")}
_c32fsopen(*) %{uchar32("_wfsopen")}
_c16fdopen(*) %{uchar16("_wfdopen")}
_c32fdopen(*) %{uchar32("_wfdopen")}
_c16fopen_s(*) %{uchar16("_wfopen_s")}
_c32fopen_s(*) %{uchar32("_wfopen_s")}
_c16freopen_s(*) %{uchar16("_wfreopen_s")}
_c32freopen_s(*) %{uchar32("_wfreopen_s")}
_getc16s(*) %{uchar16("_getws")}
_getc32s(*) %{uchar32("_getws")}
_getc16s_s(*) %{uchar16("_getws_s")}
_getc32s_s(*) %{uchar32("_getws_s")}
_putc16s(*) %{uchar16("_putws")}
_putc32s(*) %{uchar32("_putws")}
_c16tempnam(*) %{uchar16("_wtempnam")}
_c32tempnam(*) %{uchar32("_wtempnam")}
_c16tmpnam_s(*) %{uchar16("_wtmpnam_s")}
_c32tmpnam_s(*) %{uchar32("_wtmpnam_s")}
_c16tmpnam(*) %{uchar16("_wtmpnam")}
_c32tmpnam(*) %{uchar32("_wtmpnam")}
__stdio_common_vfc16printf(*) %{uchar16("__stdio_common_vfwprintf")}
__stdio_common_vfc32printf(*) %{uchar32("__stdio_common_vfwprintf")}
__stdio_common_vfc16printf_s(*) %{uchar16("__stdio_common_vfwprintf_s")}
__stdio_common_vfc32printf_s(*) %{uchar32("__stdio_common_vfwprintf_s")}
__stdio_common_vfc16printf_p(*) %{uchar16("__stdio_common_vfwprintf_p")}
__stdio_common_vfc32printf_p(*) %{uchar32("__stdio_common_vfwprintf_p")}
__stdio_common_vsc16printf(*) %{uchar16("__stdio_common_vswprintf")}
__stdio_common_vsc32printf(*) %{uchar32("__stdio_common_vswprintf")}
__stdio_common_vsc16printf_s(*) %{uchar16("__stdio_common_vswprintf_s")}
__stdio_common_vsc32printf_s(*) %{uchar32("__stdio_common_vswprintf_s")}
__stdio_common_vsnc16printf_s(*) %{uchar16("__stdio_common_vsnwprintf_s")}
__stdio_common_vsnc32printf_s(*) %{uchar32("__stdio_common_vsnwprintf_s")}
__stdio_common_vsc16printf_p(*) %{uchar16("__stdio_common_vswprintf_p")}
__stdio_common_vsc32printf_p(*) %{uchar32("__stdio_common_vswprintf_p")}
__stdio_common_vfc16scanf(*) %{uchar16("__stdio_common_vfwscanf")}
__stdio_common_vfc32scanf(*) %{uchar32("__stdio_common_vfwscanf")}
__stdio_common_vsc16scanf(*) %{uchar16("__stdio_common_vswscanf")}
__stdio_common_vsc32scanf(*) %{uchar32("__stdio_common_vswscanf")}
_vsnc16printf_l(*) %{uchar16("_vsnwprintf_l")}
_vsnc32printf_l(*) %{uchar32("_vsnwprintf_l")}
_vsc16printf_s_l(*) %{uchar16("_vswprintf_s_l")}
_vsc32printf_s_l(*) %{uchar32("_vswprintf_s_l")}
_vsc16printf_p_l(*) %{uchar16("_vswprintf_p_l")}
_vsc32printf_p_l(*) %{uchar32("_vswprintf_p_l")}
_vscc16printf_l(*) %{uchar16("_vscwprintf_l")}
_vscc32printf_l(*) %{uchar32("_vscwprintf_l")}
_vscc16printf_p_l(*) %{uchar16("_vscwprintf_p_l")}
_vscc32printf_p_l(*) %{uchar32("_vscwprintf_p_l")}
_vsc16printf_c_l(*) %{uchar16("_vswprintf_c_l")}
_vsc32printf_c_l(*) %{uchar32("_vswprintf_c_l")}
_vsnc16printf_s_l(*) %{uchar16("_vsnwprintf_s_l")}
_vsnc32printf_s_l(*) %{uchar32("_vsnwprintf_s_l")}
_vfc16printf_s_l(*) %{uchar16("_vfwprintf_s_l")}
_vfc32printf_s_l(*) %{uchar32("_vfwprintf_s_l")}
_vfc16printf_p_l(*) %{uchar16("_vfwprintf_p_l")}
_vfc32printf_p_l(*) %{uchar32("_vfwprintf_p_l")}
_vfc16scanf_l(*) %{uchar16("_vfwscanf_l")}
_vfc32scanf_l(*) %{uchar32("_vfwscanf_l")}
_vfc16scanf_s_l(*) %{uchar16("_vfwscanf_s_l")}
_vfc32scanf_s_l(*) %{uchar32("_vfwscanf_s_l")}
_vsnc16scanf_l(*) %{uchar16("_vsnwscanf_l")}
_vsnc32scanf_l(*) %{uchar32("_vsnwscanf_l")}
_vsnc16scanf_s_l(*) %{uchar16("_vsnwscanf_s_l")}
_vsnc32scanf_s_l(*) %{uchar32("_vsnwscanf_s_l")}
_vc16printf_l(*) %{uchar16("_vwprintf_l")}
_vc32printf_l(*) %{uchar32("_vwprintf_l")}
_vfc16printf_l(*) %{uchar16("_vfwprintf_l")}
_vfc32printf_l(*) %{uchar32("_vfwprintf_l")}
__vsc16printf_l(*) %{uchar16("__vswprintf_l")}
__vsc32printf_l(*) %{uchar32("__vswprintf_l")}
_vc16scanf_l(*) %{uchar16("_vwscanf_l")}
_vc32scanf_l(*) %{uchar32("_vwscanf_l")}
_vsc16printf_l(*) = _vsc16printf_c_l;
_vsc32printf_l(*) = _vsc32printf_c_l;
_vfc16printf_p(*) %{uchar16("_vfwprintf_p")}
_vfc32printf_p(*) %{uchar32("_vfwprintf_p")}
_vsnc16printf_s(*) %{uchar16("_vsnwprintf_s")}
_vsnc32printf_s(*) %{uchar32("_vsnwprintf_s")}
_vsnc16printf(*) %{uchar16("_vsnwprintf")}
_vsnc32printf(*) %{uchar32("_vsnwprintf")}
_vsc16printf_c(*) %{uchar16("_vswprintf_c")}
_vsc32printf_c(*) %{uchar32("_vswprintf_c")}
_vsc16printf(*) %{uchar16("_vswprintf")}
_vsc32printf(*) %{uchar32("_vswprintf")}
_vc16printf_p(*) %{uchar16("_vwprintf_p")}
_vc32printf_p(*) %{uchar32("_vwprintf_p")}
_vsc16printf_p(*) %{uchar16("_vswprintf_p")}
_vsc32printf_p(*) %{uchar32("_vswprintf_p")}
_vscc16printf(*) %{uchar16("_vscwprintf")}
_vscc32printf(*) %{uchar32("_vscwprintf")}
_vscc16printf_p(*) %{uchar16("_vscwprintf_p")}
_vscc32printf_p(*) %{uchar32("_vscwprintf_p")}
_vsc16scanf_l(*) %{uchar16("_vswscanf_l")}
_vsc32scanf_l(*) %{uchar32("_vswscanf_l")}
_vsc16scanf_s_l(*) %{uchar16("_vswscanf_s_l")}
_vsc32scanf_s_l(*) %{uchar32("_vswscanf_s_l")}
_vsnc16scanf(*) %{uchar16("_vsnwscanf")}
_vsnc32scanf(*) %{uchar32("_vsnwscanf")}
_vsnc16scanf_s(*) %{uchar16("_vsnwscanf_s")}
_vsnc32scanf_s(*) %{uchar32("_vsnwscanf_s")}
_vc16printf_s_l(*) %{uchar16("_vwprintf_s_l")}
_vc32printf_s_l(*) %{uchar32("_vwprintf_s_l")}
_vc16printf_p_l(*) %{uchar16("_vwprintf_p_l")}
_vc32printf_p_l(*) %{uchar32("_vwprintf_p_l")}
_vc16scanf_s_l(*) %{uchar16("_vwscanf_s_l")}
_vc32scanf_s_l(*) %{uchar32("_vwscanf_s_l")}
_fc16printf_l(*) %{uchar16("_fwprintf_l")}
_fc32printf_l(*) %{uchar32("_fwprintf_l")}
_fc16printf_s_l(*) %{uchar16("_fwprintf_s_l")}
_fc32printf_s_l(*) %{uchar32("_fwprintf_s_l")}
_fc16printf_p_l(*) %{uchar16("_fwprintf_p_l")}
_fc32printf_p_l(*) %{uchar32("_fwprintf_p_l")}
_c16printf_l(*) %{uchar16("_wprintf_l")}
_c32printf_l(*) %{uchar32("_wprintf_l")}
_c16printf_s_l(*) %{uchar16("_wprintf_s_l")}
_c32printf_s_l(*) %{uchar32("_wprintf_s_l")}
_c16printf_p_l(*) %{uchar16("_wprintf_p_l")}
_c32printf_p_l(*) %{uchar32("_wprintf_p_l")}
__sc16printf_l(*) %{uchar16("__swprintf_l")}
__sc32printf_l(*) %{uchar32("__swprintf_l")}
_fc16printf_p(*) %{uchar16("_fwprintf_p")}
_fc32printf_p(*) %{uchar32("_fwprintf_p")}
_c16printf_p(*) %{uchar16("_wprintf_p")}
_c32printf_p(*) %{uchar32("_wprintf_p")}
_sc16printf(*) %{uchar16("_swprintf")}
_sc32printf(*) %{uchar32("_swprintf")}
_sc16printf_l(*) = _sc16printf_c_l;
_sc32printf_l(*) = _sc32printf_c_l;
_sc16printf_s_l(*) %{uchar16("_swprintf_s_l")}
_sc32printf_s_l(*) %{uchar32("_swprintf_s_l")}
_sc16printf_p_l(*) %{uchar16("_swprintf_p_l")}
_sc32printf_p_l(*) %{uchar32("_swprintf_p_l")}
_sc16printf_c_l(*) %{uchar16("_swprintf_c_l")}
_sc32printf_c_l(*) %{uchar32("_swprintf_c_l")}
_snc16printf_l(*) %{uchar16("_snwprintf_l")}
_snc32printf_l(*) %{uchar32("_snwprintf_l")}
_snc16printf_s_l(*) %{uchar16("_snwprintf_s_l")}
_snc32printf_s_l(*) %{uchar32("_snwprintf_s_l")}
_sc16printf_p(*) %{uchar16("_swprintf_p")}
_sc32printf_p(*) %{uchar32("_swprintf_p")}
_sc16printf_c(*) %{uchar16("_swprintf_c")}
_sc32printf_c(*) %{uchar32("_swprintf_c")}
_snc16printf(*) %{uchar16("_snwprintf")}
_snc32printf(*) %{uchar32("_snwprintf")}
_snc16printf_s(*) %{uchar16("_snwprintf_s")}
_snc32printf_s(*) %{uchar32("_snwprintf_s")}
_scc16printf_l(*) %{uchar16("_scwprintf_l")}
_scc32printf_l(*) %{uchar32("_scwprintf_l")}
_scc16printf_p_l(*) %{uchar16("_scwprintf_p_l")}
_scc32printf_p_l(*) %{uchar32("_scwprintf_p_l")}
_scc16printf(*) %{uchar16("_scwprintf")}
_scc32printf(*) %{uchar32("_scwprintf")}
_scc16printf_p(*) %{uchar16("_scwprintf_p")}
_scc32printf_p(*) %{uchar32("_scwprintf_p")}
_fc16scanf_l(*) %{uchar16("_fwscanf_l")}
_fc32scanf_l(*) %{uchar32("_fwscanf_l")}
_fc16scanf_s_l(*) %{uchar16("_fwscanf_s_l")}
_fc32scanf_s_l(*) %{uchar32("_fwscanf_s_l")}
_c16scanf_l(*) %{uchar16("_wscanf_l")}
_c32scanf_l(*) %{uchar32("_wscanf_l")}
_c16scanf_s_l(*) %{uchar16("_wscanf_s_l")}
_c32scanf_s_l(*) %{uchar32("_wscanf_s_l")}
_sc16scanf_l(*) %{uchar16("_swscanf_l")}
_sc32scanf_l(*) %{uchar32("_swscanf_l")}
_sc16scanf_s_l(*) %{uchar16("_swscanf_s_l")}
_sc32scanf_s_l(*) %{uchar32("_swscanf_s_l")}
_snc16scanf_l(*) %{uchar16("_snwscanf_l")}
_snc32scanf_l(*) %{uchar32("_snwscanf_l")}
_snc16scanf(*) %{uchar16("_snwscanf")}
_snc32scanf(*) %{uchar32("_snwscanf")}
_snc16scanf_s_l(*) %{uchar16("_snwscanf_s_l")}
_snc32scanf_s_l(*) %{uchar32("_snwscanf_s_l")}
_snc16scanf_s(*) %{uchar16("_snwscanf_s")}
_snc32scanf_s(*) %{uchar32("_snwscanf_s")}

%#ifdef __USE_DOS_SLIB
vfc16printf_s(*) %{uchar16("vfwprintf_s")}
vfc32printf_s(*) %{uchar32("vfwprintf_s")}
vc16printf_s(*) %{uchar16("vwprintf_s")}
vc32printf_s(*) %{uchar32("vwprintf_s")}
vsc16printf_s(*) %{uchar16("vswprintf_s")}
vsc32printf_s(*) %{uchar32("vswprintf_s")}
vfc16scanf_s(*) %{uchar16("vfwscanf_s")}
vfc32scanf_s(*) %{uchar32("vfwscanf_s")}
vc16scanf_s(*) %{uchar16("vwscanf_s")}
vc32scanf_s(*) %{uchar32("vwscanf_s")}
vsc16scanf_s(*) %{uchar16("vswscanf_s")}
vsc32scanf_s(*) %{uchar32("vswscanf_s")}
fc16printf_s(*) %{uchar16("fwprintf_s")}
fc32printf_s(*) %{uchar32("fwprintf_s")}
c16printf_s(*) %{uchar16("wprintf_s")}
c32printf_s(*) %{uchar32("wprintf_s")}
sc16printf_s(*) %{uchar16("swprintf_s")}
sc32printf_s(*) %{uchar32("swprintf_s")}
fc16scanf_s(*) %{uchar16("fwscanf_s")}
fc32scanf_s(*) %{uchar32("fwscanf_s")}
c16scanf_s(*) %{uchar16("wscanf_s")}
c32scanf_s(*) %{uchar32("wscanf_s")}
sc16scanf_s(*) %{uchar16("swscanf_s")}
sc32scanf_s(*) %{uchar32("swscanf_s")}
%#endif /* __USE_DOS_SLIB */

%#endif /* __USE_DOS */

%{

__SYSDECL_END
#endif /* __CC__ */

}
