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

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]

%{
#include <features.h>
#ifndef _STRING_H
#include <string.h>
#endif /* !_STRING_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */
#include <parts/malloca.h>

__SYSDECL_BEGIN

#ifdef __CC__

}

[alias(memcpyw)][attribute(*)] c16memcpy:(*) %{uchar(wmemcpy)}
[alias(memcpyl)][attribute(*)] c32memcpy:(*) %{uchar(wmemcpy)}
[alias(memmovew)][attribute(*)] c16memmove:(*) %{uchar(wmemmove)}
[alias(memmovel)][attribute(*)] c32memmove:(*) %{uchar(wmemmove)}
[alias(memsetw)][attribute(*)] c16memset:(*) %{uchar(wmemset)}
[alias(memsetl)][attribute(*)] c32memset:(*) %{uchar(wmemset)}
[alias(mempcpyw)][attribute(*)] c16mempcpy:(*) %{uchar(wmempcpy)}
[alias(mempcpyl)][attribute(*)] c32mempcpy:(*) %{uchar(wmempcpy)}
[alias(mempmovew)][attribute(*)] c16mempmove:(*) %{uchar(wmempmove)}
[alias(mempmovel)][attribute(*)] c32mempmove:(*) %{uchar(wmempmove)}
[alias(mempsetw)][attribute(*)] c16mempset:(*) %{uchar(wmempset)}
[alias(mempsetl)][attribute(*)] c32mempset:(*) %{uchar(wmempset)}

[libc][attribute(*)] c16end:(*) %{uchar(wcsend)}
[libc][attribute(*)] c32end:(*) %{uchar(wcsend)}
[libc][attribute(*)] c16nend:(*) %{uchar(wcsnend)}
[libc][attribute(*)] c32nend:(*) %{uchar(wcsnend)}
[libc][attribute(*)] c16len:(*) %{uchar(wcslen)}
[libc][attribute(*)] c32len:(*) %{uchar(wcslen)}
[libc][attribute(*)] c16nlen:(*) %{uchar(wcsnlen)}
[libc][attribute(*)] c32nlen:(*) %{uchar(wcsnlen)}
[libc][attribute(*)] c16cmp:(*) %{uchar(wcscmp)}
[libc][attribute(*)] c32cmp:(*) %{uchar(wcscmp)}
[libc][attribute(*)] c16ncmp:(*) %{uchar(wcsncmp)}
[libc][attribute(*)] c32ncmp:(*) %{uchar(wcsncmp)}

[attribute(*)] c16chr:(*) %{uchar(wcschr)}
[attribute(*)] c32chr:(*) %{uchar(wcschr)}
[attribute(*)] c16rchr:(*) %{uchar(wcsrchr)}
[attribute(*)] c32rchr:(*) %{uchar(wcsrchr)}
[attribute(*)] c16nchr:(*) %{uchar(wcsnchr)}
[attribute(*)] c32nchr:(*) %{uchar(wcsnchr)}
[attribute(*)] c16nrchr:(*) %{uchar(wcsnrchr)}
[attribute(*)] c32nrchr:(*) %{uchar(wcsnrchr)}

[attribute(*)] c16chrnul:(*) %{uchar(wcschrnul)}
[attribute(*)] c32chrnul:(*) %{uchar(wcschrnul)}
[attribute(*)] c16rchrnul:(*) %{uchar(wcsrchrnul)}
[attribute(*)] c32rchrnul:(*) %{uchar(wcsrchrnul)}
[attribute(*)] c16nchrnul:(*) %{uchar(wcsnchrnul)}
[attribute(*)] c32nchrnul:(*) %{uchar(wcsnchrnul)}
[attribute(*)] c16nrchrnul:(*) %{uchar(wcsnrchrnul)}
[attribute(*)] c32nrchrnul:(*) %{uchar(wcsnrchrnul)}

[attribute(*)] c16off:(*) %{uchar(wcsoff)}
[attribute(*)] c32off:(*) %{uchar(wcsoff)}
[attribute(*)] c16roff:(*) %{uchar(wcsroff)}
[attribute(*)] c32roff:(*) %{uchar(wcsroff)}
[attribute(*)] c16noff:(*) %{uchar(wcsnoff)}
[attribute(*)] c32noff:(*) %{uchar(wcsnoff)}
[attribute(*)] c16nroff:(*) %{uchar(wcsnroff)}
[attribute(*)] c32nroff:(*) %{uchar(wcsnroff)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(wcswcs)][alias(DOS$wcswcs)]
[attribute(*)] c16str:(*) %{uchar(wcsstr)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(wcswcs)]
[attribute(*)] c32str:(*) %{uchar(wcsstr)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(wcsistr, _wcsistr, wcscasewcs, wcsiwcs, _wcsiwcs)]
[alias(DOS$wcsistr, DOS$wcsiwcs, DOS$_wcsistr, DOS$_wcsiwcs)]
[attribute(*)] c16casestr:(*) %{uchar(wcscasestr)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(wcsistr, _wcsistr, wcscasewcs, wcsiwcs, _wcsiwcs)]
[attribute(*)] c32casestr:(*) %{uchar(wcscasestr)}

[attribute(*)] c16cpy:(*) %{uchar(wcscpy)}
[attribute(*)] c32cpy:(*) %{uchar(wcscpy)}
[attribute(*)] c16pcpy:(*) %{uchar(wcspcpy)}
[attribute(*)] c32pcpy:(*) %{uchar(wcspcpy)}
[attribute(*)] c16ncpy:(*) %{uchar(wcsncpy)}
[attribute(*)] c32ncpy:(*) %{uchar(wcsncpy)}
[attribute(*)] c16pncpy:(*) %{uchar(wcspncpy)}
[attribute(*)] c32pncpy:(*) %{uchar(wcspncpy)}

[attribute(*)] c16cat:(*) %{uchar(wcscat)}
[attribute(*)] c32cat:(*) %{uchar(wcscat)}
[attribute(*)] c16ncat:(*) %{uchar(wcsncat)}
[attribute(*)] c32ncat:(*) %{uchar(wcsncat)}

[attribute(*)] c16spn:(*) %{uchar(wcsspn)}
[attribute(*)] c32spn:(*) %{uchar(wcsspn)}
[attribute(*)] c16cspn:(*) %{uchar(wcscspn)}
[attribute(*)] c32cspn:(*) %{uchar(wcscspn)}

[attribute(*)] c16pbrk:(*) %{uchar(wcspbrk)}
[attribute(*)] c32pbrk:(*) %{uchar(wcspbrk)}

[attribute(*)] c16tok:(*) %{uchar(wcstok)}
[attribute(*)] c32tok:(*) %{uchar(wcstok)}

[attribute(*)] c16sep:(*) %{uchar(wcssep)}
[attribute(*)] c32sep:(*) %{uchar(wcssep)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(_wcsdup)][alias(DOS$_wcsdup)]
[attribute(*)] c16dup:(*) %{uchar(wcsdup)}
[if(__SIZEOF_WCHAR_T__ == 4), alias(_wcsdup)]
[attribute(*)] c32dup:(*) %{uchar(wcsdup)}

[attribute(*)] c16ndup:(*) %{uchar(wcsndup)}
[attribute(*)] c32ndup:(*) %{uchar(wcsndup)}

[attribute(*)] c16fry:(*) %{uchar(wcsfry)}
[attribute(*)] c32fry:(*) %{uchar(wcsfry)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(wcsicmp, _wcsicmp)]
[alias(DOS$wcsicmp, DOS$_wcsicmp)]
[attribute(*)] c16casecmp:(*) %{uchar(wcscasecmp)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(wcsicmp, _wcsicmp)]
[attribute(*)] c32casecmp:(*) %{uchar(wcscasecmp)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(wcsnicmp, _wcsnicmp)]
[alias(DOS$wcsnicmp, DOS$_wcsnicmp)]
[attribute(*)] c16ncasecmp:(*) %{uchar(wcsncasecmp)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(wcsnicmp, _wcsnicmp)]
[attribute(*)] c32ncasecmp:(*) %{uchar(wcsncasecmp)}

[attribute(*)] c16xfrm:(*) %{uchar(wcsxfrm)}
[attribute(*)] c32xfrm:(*) %{uchar(wcsxfrm)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(wcscmp)][alias(DOS$wcscmp)]
[attribute(*)] c16coll:(*) %{uchar(wcscoll)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(wcscmp)]
[attribute(*)] c32coll:(*) %{uchar(wcscoll)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(wcsncmp)][alias(DOS$wcsncmp)]
[attribute(*)] c16ncoll:(*) %{uchar(wcsncoll)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(wcsncmp)]
[attribute(*)] c32ncoll:(*) %{uchar(wcsncoll)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(_wcsicoll, wcsicoll, wcscasecmp, _wcsicmp, wcsicmp)]
[alias(DOS$_wcsicoll, DOS$wcsicoll, DOS$_wcsicmp, DOS$wcsicmp)]
[attribute(*)] c16casecoll:(*) %{uchar(wcscasecoll)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(_wcsicoll, wcsicoll, wcscasecmp, _wcsicmp, wcsicmp)]
[attribute(*)] c32casecoll:(*) %{uchar(wcscasecoll)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(_wcsnicoll, wcsncasecmp, _wcsnicmp, wcsnicmp)]
[alias(DOS$_wcsnicoll, DOS$_wcsnicmp, DOS$wcsnicmp)]
[attribute(*)] c16ncasecoll:(*) %{uchar(wcsncasecoll)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(_wcsnicoll, wcsncasecmp, _wcsnicmp, wcsnicmp)]
[attribute(*)] c32ncasecoll:(*) %{uchar(wcsncasecoll)}


[if(__SIZEOF_WCHAR_T__ == 2), alias(_wcslwr)][alias(DOS$_wcslwr)]
[attribute(*)] c16lwr:(*) %{uchar(wcslwr)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(_wcslwr)]
[attribute(*)] c32lwr:(*) %{uchar(wcslwr)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(_wcsupr)][alias(DOS$_wcsupr)]
[attribute(*)] c16upr:(*) %{uchar(wcsupr)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(_wcsupr)]
[attribute(*)] c32upr:(*) %{uchar(wcsupr)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(_wcsrev)][alias(DOS$_wcsrev)]
[attribute(*)] c16rev:(*) %{uchar(wcsrev)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(_wcsrev)]
[attribute(*)] c32rev:(*) %{uchar(wcsrev)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(_wcsnrev)][alias(DOS$_wcsnrev)]
[attribute(*)] c16nrev:(*) %{uchar(wcsnrev)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(_wcsnrev)]
[attribute(*)] c32nrev:(*) %{uchar(wcsnrev)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(_wcsset)][alias(DOS$_wcsset)]
[attribute(*)] c16set:(*) %{uchar(wcsset)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(_wcsset)]
[attribute(*)] c32set:(*) %{uchar(wcsset)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(_wcsnset)][alias(DOS$_wcsnset)]
[attribute(*)] c16nset:(*) %{uchar(wcsnset)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(_wcsnset)]
[attribute(*)] c32nset:(*) %{uchar(wcsnset)}

[attribute(*)] fuzzy_c16memcmp:(*) %{uchar(fuzzy_wmemcmp)}
[attribute(*)] fuzzy_c32memcmp:(*) %{uchar(fuzzy_wmemcmp)}
[attribute(*)] fuzzy_c16memcasecmp:(*) %{uchar(fuzzy_wmemcasecmp)}
[attribute(*)] fuzzy_c32memcasecmp:(*) %{uchar(fuzzy_wmemcasecmp)}
[attribute(*)] fuzzy_c16cmp:(*) %{uchar(fuzzy_wcscmp)}
[attribute(*)] fuzzy_c32cmp:(*) %{uchar(fuzzy_wcscmp)}
[attribute(*)] fuzzy_c16ncmp:(*) %{uchar(fuzzy_wcsncmp)}
[attribute(*)] fuzzy_c32ncmp:(*) %{uchar(fuzzy_wcsncmp)}
[attribute(*)] fuzzy_c16casecmp:(*) %{uchar(fuzzy_wcscasecmp)}
[attribute(*)] fuzzy_c32casecmp:(*) %{uchar(fuzzy_wcscasecmp)}
[attribute(*)] fuzzy_c16ncasecmp:(*) %{uchar(fuzzy_wcsncasecmp)}
[attribute(*)] fuzzy_c32ncasecmp:(*) %{uchar(fuzzy_wcsncasecmp)}

//%[define_wchar_replacement(wildwcscmp = wildc16cmp,wildc32cmp)]

[attribute(*)] wildc16cmp:(*) %{uchar(wildwcscmp)}
[attribute(*)] wildc32cmp:(*) %{uchar(wildwcscmp)}
[attribute(*)] wildc16casecmp:(*) %{uchar(wildwcscasecmp)}
[attribute(*)] wildc32casecmp:(*) %{uchar(wildwcscasecmp)}


[attribute(*)] c16verscmp:(*) %{uchar(wcsverscmp)}
[attribute(*)] c32verscmp:(*) %{uchar(wcsverscmp)}









%#ifdef __USE_XOPEN2K8
[if(__SIZEOF_WCHAR_T__ == 2), alias(wcsistr_l, _wcsistr_l, wcscasewcs_l, wcsiwcs_l, _wcsiwcs_l)]
[alias(DOS$wcsistr_l, DOS$wcsiwcs_l, DOS$_wcsistr_l, DOS$_wcsiwcs_l)]
[attribute(*)] c16casestr_l:(*) %{uchar(wcscasestr_l)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(wcsistr_l, _wcsistr_l, wcscasewcs_l, wcsiwcs_l, _wcsiwcs_l)]
[attribute(*)] c32casestr_l:(*) %{uchar(wcscasestr_l)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(wcsicmp_l, _wcsicmp_l)]
[alias(DOS$wcsicmp_l, DOS$_wcsicmp_l)]
[attribute(*)] c16casecmp_l:(*) %{uchar(wcscasecmp_l)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(wcsicmp_l, _wcsicmp_l)]
[attribute(*)] c32casecmp_l:(*) %{uchar(wcscasecmp_l)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(wcsnicmp_l, _wcsnicmp_l)]
[alias(DOS$wcsnicmp_l, DOS$_wcsnicmp_l)]
[attribute(*)] c16ncasecmp_l:(*) %{uchar(wcsncasecmp_l)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(wcsnicmp_l, _wcsnicmp_l)]
[attribute(*)] c32ncasecmp_l:(*) %{uchar(wcsncasecmp_l)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(_wcsxfrm_l)][alias(DOS$_wcsxfrm_l)]
[attribute(*)] c16xfrm_l:(*) %{uchar(wcsxfrm_l)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(_wcsxfrm_l)]
[attribute(*)] c32xfrm_l:(*) %{uchar(wcsxfrm_l)}


[if(__SIZEOF_WCHAR_T__ == 2), alias(_wcscoll_l, wcscmp_l, _wcscmp_l)]
[alias(DOS$_wcscoll_l, DOS$_wcscmp_l)]
[attribute(*)] c16coll_l:(*) %{uchar(wcscoll_l)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(_wcscoll_l, wcscmp_l, _wcscmp_l)]
[attribute(*)] c32coll_l:(*) %{uchar(wcscoll_l)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(_wcsncoll_l, wcsncmp_l, _wcsncmp_l)][alias(DOS$_wcsncmp_l)]
[attribute(*)] c16ncoll_l:(*) %{uchar(wcsncoll_l)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(_wcsncmp_l, wcsncmp_l)]
[attribute(*)] c32ncoll_l:(*) %{uchar(wcsncoll_l)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(_wcsicoll_l, wcsicoll_l, wcscasecmp_l, _wcsicmp_l, wcsicmp_l)]
[alias(DOS$_wcsicoll_l, DOS$wcsicoll_l, DOS$_wcsicmp_l, DOS$wcsicmp_l)]
[attribute(*)] c16casecoll_l:(*) %{uchar(wcscasecoll_l)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(_wcsicoll_l, wcsicoll_l, wcscasecmp_l, _wcsicmp_l, wcsicmp_l)]
[attribute(*)] c32casecoll_l:(*) %{uchar(wcscasecoll_l)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(_wcsnicoll_l, wcsncasecmp_l, _wcsnicmp_l, wcsnicmp_l)]
[alias(DOS$_wcsnicoll_l, DOS$_wcsnicmp_l, DOS$wcsnicmp_l)]
[attribute(*)] c16ncasecoll_l:(*) %{uchar(wcsncasecoll_l)}

[if(__SIZEOF_WCHAR_T__ == 4), alias(_wcsnicoll_l, wcsncasecmp_l, _wcsnicmp_l, wcsnicmp_l)]
[attribute(*)] c32ncasecoll_l:(*) %{uchar(wcsncasecoll_l)}

[if(__SIZEOF_WCHAR_T__ == 2), alias(_wcslwr_l)][alias(DOS$_wcslwr_l)]
[attribute(*)] c16lwr_l:(*) %{uchar(wcslwr_l)}
[if(__SIZEOF_WCHAR_T__ == 4), alias(_wcslwr_l)]
[attribute(*)] c32lwr_l:(*) %{uchar(wcslwr_l)}
[if(__SIZEOF_WCHAR_T__ == 2), alias(_wcsupr_l)][alias(DOS$_wcsupr_l)]
[attribute(*)] c16upr_l:(*) %{uchar(wcsupr_l)}
[if(__SIZEOF_WCHAR_T__ == 4), alias(_wcsupr_l)]
[attribute(*)] c32upr_l:(*) %{uchar(wcsupr_l)}

[attribute(*)] fuzzy_c16memcasecmp_l:(*) %{uchar(fuzzy_wmemcasecmp_l)}
[attribute(*)] fuzzy_c32memcasecmp_l:(*) %{uchar(fuzzy_wmemcasecmp_l)}
[attribute(*)] fuzzy_c16casecmp_l:(*) %{uchar(fuzzy_wcscasecmp_l)}
[attribute(*)] fuzzy_c32casecmp_l:(*) %{uchar(fuzzy_wcscasecmp_l)}
[attribute(*)] fuzzy_c16ncasecmp_l:(*) %{uchar(fuzzy_wcsncasecmp_l)}
[attribute(*)] fuzzy_c32ncasecmp_l:(*) %{uchar(fuzzy_wcsncasecmp_l)}

[attribute(*)] wildc16casecmp_l:(*) %{uchar(wildwcscasecmp_l)}
[attribute(*)] wildc32casecmp_l:(*) %{uchar(wildwcscasecmp_l)}

%#endif /* __USE_XOPEN2K8 */


[attribute(*)] c16to32:(*) %{uchar16(wcsto32)}
[attribute(*)] c32to32:(*) %{uchar32(wcsto32)}
[attribute(*)] c16tou32:(*) %{uchar16(wcstou32)}
[attribute(*)] c32tou32:(*) %{uchar32(wcstou32)}
[attribute(*)] c16to64:(*) %{uchar16(wcsto64)}
[attribute(*)] c32to64:(*) %{uchar32(wcsto64)}
[attribute(*)] c16tou64:(*) %{uchar16(wcstou64)}
[attribute(*)] c32tou64:(*) %{uchar32(wcstou64)}


%{

#endif /* __CC__ */

__SYSDECL_END

}

