/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
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

c16memcpy(*) %{uchar16("wmemcpy")}
c32memcpy(*) %{uchar32("wmemcpy")}
c16memmove(*) %{uchar16("wmemmove")}
c32memmove(*) %{uchar32("wmemmove")}
c16memset(*) %{uchar16("wmemset")}
c32memset(*) %{uchar32("wmemset")}
c16mempcpy(*) %{uchar16("wmempcpy")}
c32mempcpy(*) %{uchar32("wmempcpy")}
c16mempmove(*) %{uchar16("wmempmove")}
c32mempmove(*) %{uchar32("wmempmove")}
c16mempset(*) %{uchar16("wmempset")}
c32mempset(*) %{uchar32("wmempset")}

[[libc]] c16send(*) %{uchar16("wcsend")}
[[libc]] c32send(*) %{uchar32("wcsend")}
[[libc]] c16snend(*) %{uchar16("wcsnend")}
[[libc]] c32snend(*) %{uchar32("wcsnend")}
[[libc]] c16slen(*) %{uchar16("wcslen")}
[[libc]] c32slen(*) %{uchar32("wcslen")}
[[libc]] c16snlen(*) %{uchar16("wcsnlen")}
[[libc]] c32snlen(*) %{uchar32("wcsnlen")}
[[libc]] c16scmp(*) %{uchar16("wcscmp")}
[[libc]] c32scmp(*) %{uchar32("wcscmp")}
[[libc]] c16sncmp(*) %{uchar16("wcsncmp")}
[[libc]] c32sncmp(*) %{uchar32("wcsncmp")}

c16schr(*) %{uchar16("wcschr")}
c32schr(*) %{uchar32("wcschr")}
c16srchr(*) %{uchar16("wcsrchr")}
c32srchr(*) %{uchar32("wcsrchr")}
c16snchr(*) %{uchar16("wcsnchr")}
c32snchr(*) %{uchar32("wcsnchr")}
c16snrchr(*) %{uchar16("wcsnrchr")}
c32snrchr(*) %{uchar32("wcsnrchr")}

c16schrnul(*) %{uchar16("wcschrnul")}
c32schrnul(*) %{uchar32("wcschrnul")}
c16srchrnul(*) %{uchar16("wcsrchrnul")}
c32srchrnul(*) %{uchar32("wcsrchrnul")}
c16snchrnul(*) %{uchar16("wcsnchrnul")}
c32snchrnul(*) %{uchar32("wcsnchrnul")}
c16snrchrnul(*) %{uchar16("wcsnrchrnul")}
c32snrchrnul(*) %{uchar32("wcsnrchrnul")}

c16soff(*) %{uchar16("wcsoff")}
c32soff(*) %{uchar32("wcsoff")}
c16sroff(*) %{uchar16("wcsroff")}
c32sroff(*) %{uchar32("wcsroff")}
c16snoff(*) %{uchar16("wcsnoff")}
c32snoff(*) %{uchar32("wcsnoff")}
c16snroff(*) %{uchar16("wcsnroff")}
c32snroff(*) %{uchar32("wcsnroff")}

c16sstr(*) %{uchar16("wcsstr")}
c32sstr(*) %{uchar32("wcsstr")}
c16scasestr(*) %{uchar16("wcscasestr")}
c32scasestr(*) %{uchar32("wcscasestr")}

c16scpy(*) %{uchar16("wcscpy")}
c32scpy(*) %{uchar32("wcscpy")}
c16spcpy(*) %{uchar16("wcspcpy")}
c32spcpy(*) %{uchar32("wcspcpy")}
c16sncpy(*) %{uchar16("wcsncpy")}
c32sncpy(*) %{uchar32("wcsncpy")}
c16spncpy(*) %{uchar16("wcspncpy")}
c32spncpy(*) %{uchar32("wcspncpy")}

c16scat(*) %{uchar16("wcscat")}
c32scat(*) %{uchar32("wcscat")}
c16sncat(*) %{uchar16("wcsncat")}
c32sncat(*) %{uchar32("wcsncat")}

c16sspn(*) %{uchar16("wcsspn")}
c32sspn(*) %{uchar32("wcsspn")}
c16scspn(*) %{uchar16("wcscspn")}
c32scspn(*) %{uchar32("wcscspn")}

c16spbrk(*) %{uchar16("wcspbrk")}
c32spbrk(*) %{uchar32("wcspbrk")}

[[guard]] c16stok(*) %{uchar16("wcstok")}
[[guard]] c32stok(*) %{uchar32("wcstok")}

c16ssep(*) %{uchar16("wcssep")}
c32ssep(*) %{uchar32("wcssep")}

c16sdup(*) %{uchar16("wcsdup")}
c32sdup(*) %{uchar32("wcsdup")}

c16sndup(*) %{uchar16("wcsndup")}
c32sndup(*) %{uchar32("wcsndup")}

c16sfry(*) %{uchar16("wcsfry")}
c32sfry(*) %{uchar32("wcsfry")}

c16scasecmp(*) %{uchar16("wcscasecmp")}
c32scasecmp(*) %{uchar32("wcscasecmp")}
c16sncasecmp(*) %{uchar16("wcsncasecmp")}
c32sncasecmp(*) %{uchar32("wcsncasecmp")}

c16sxfrm(*) %{uchar16("wcsxfrm")}
c32sxfrm(*) %{uchar32("wcsxfrm")}

c16scoll(*) %{uchar16("wcscoll")}
c32scoll(*) %{uchar32("wcscoll")}
c16sncoll(*) %{uchar16("wcsncoll")}
c32sncoll(*) %{uchar32("wcsncoll")}
c16scasecoll(*) %{uchar16("wcscasecoll")}
c32scasecoll(*) %{uchar32("wcscasecoll")}
c16sncasecoll(*) %{uchar16("wcsncasecoll")}
c32sncasecoll(*) %{uchar32("wcsncasecoll")}

c16slwr(*) %{uchar16("wcslwr")}
c32slwr(*) %{uchar32("wcslwr")}
c16supr(*) %{uchar16("wcsupr")}
c32supr(*) %{uchar32("wcsupr")}
c16srev(*) %{uchar16("wcsrev")}
c32srev(*) %{uchar32("wcsrev")}
c16snrev(*) %{uchar16("wcsnrev")}
c32snrev(*) %{uchar32("wcsnrev")}
c16sset(*) %{uchar16("wcsset")}
c32sset(*) %{uchar32("wcsset")}
c16snset(*) %{uchar16("wcsnset")}
c32snset(*) %{uchar32("wcsnset")}

fuzzy_c16memcmp(*) %{uchar16("fuzzy_wmemcmp")}
fuzzy_c32memcmp(*) %{uchar32("fuzzy_wmemcmp")}
fuzzy_c16memcasecmp(*) %{uchar16("fuzzy_wmemcasecmp")}
fuzzy_c32memcasecmp(*) %{uchar32("fuzzy_wmemcasecmp")}
fuzzy_c16scmp(*) %{uchar16("fuzzy_wcscmp")}
fuzzy_c32scmp(*) %{uchar32("fuzzy_wcscmp")}
fuzzy_c16sncmp(*) %{uchar16("fuzzy_wcsncmp")}
fuzzy_c32sncmp(*) %{uchar32("fuzzy_wcsncmp")}
fuzzy_c16scasecmp(*) %{uchar16("fuzzy_wcscasecmp")}
fuzzy_c32scasecmp(*) %{uchar32("fuzzy_wcscasecmp")}
fuzzy_c16sncasecmp(*) %{uchar16("fuzzy_wcsncasecmp")}
fuzzy_c32sncasecmp(*) %{uchar32("fuzzy_wcsncasecmp")}

wildc16scmp(*) %{uchar16("wildwcscmp")}
wildc32scmp(*) %{uchar32("wildwcscmp")}
wildc16scasecmp(*) %{uchar16("wildwcscasecmp")}
wildc32scasecmp(*) %{uchar32("wildwcscasecmp")}

c16sverscmp(*) %{uchar16("wcsverscmp")}
c32sverscmp(*) %{uchar32("wcsverscmp")}


%#ifdef __USE_XOPEN2K8
c16scasestr_l(*) %{uchar16("wcscasestr_l")}
c32scasestr_l(*) %{uchar32("wcscasestr_l")}
c16scasecmp_l(*) %{uchar16("wcscasecmp_l")}
c32scasecmp_l(*) %{uchar32("wcscasecmp_l")}
c16sncasecmp_l(*) %{uchar16("wcsncasecmp_l")}
c32sncasecmp_l(*) %{uchar32("wcsncasecmp_l")}
c16sxfrm_l(*) %{uchar16("wcsxfrm_l")}
c32sxfrm_l(*) %{uchar32("wcsxfrm_l")}
c16scoll_l(*) %{uchar16("wcscoll_l")}
c32scoll_l(*) %{uchar32("wcscoll_l")}
c16sncoll_l(*) %{uchar16("wcsncoll_l")}
c32sncoll_l(*) %{uchar32("wcsncoll_l")}
c16scasecoll_l(*) %{uchar16("wcscasecoll_l")}
c32scasecoll_l(*) %{uchar32("wcscasecoll_l")}
c16sncasecoll_l(*) %{uchar16("wcsncasecoll_l")}
c32sncasecoll_l(*) %{uchar32("wcsncasecoll_l")}
c16slwr_l(*) %{uchar16("wcslwr_l")}
c32slwr_l(*) %{uchar32("wcslwr_l")}
c16supr_l(*) %{uchar16("wcsupr_l")}
c32supr_l(*) %{uchar32("wcsupr_l")}

fuzzy_c16memcasecmp_l(*) %{uchar16("fuzzy_wmemcasecmp_l")}
fuzzy_c32memcasecmp_l(*) %{uchar32("fuzzy_wmemcasecmp_l")}
fuzzy_c16scasecmp_l(*) %{uchar16("fuzzy_wcscasecmp_l")}
fuzzy_c32scasecmp_l(*) %{uchar32("fuzzy_wcscasecmp_l")}
fuzzy_c16sncasecmp_l(*) %{uchar16("fuzzy_wcsncasecmp_l")}
fuzzy_c32sncasecmp_l(*) %{uchar32("fuzzy_wcsncasecmp_l")}

wildc16scasecmp_l(*) %{uchar16("wildwcscasecmp_l")}
wildc32scasecmp_l(*) %{uchar32("wildwcscasecmp_l")}
%#endif /* __USE_XOPEN2K8 */


%{

#endif /* __CC__ */

__SYSDECL_END

}

