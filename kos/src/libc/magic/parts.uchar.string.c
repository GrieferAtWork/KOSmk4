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

c16memcpy(*) %{uchar("wmemcpy")}
c32memcpy(*) %{uchar("wmemcpy")}
c16memmove(*) %{uchar("wmemmove")}
c32memmove(*) %{uchar("wmemmove")}
c16memset(*) %{uchar("wmemset")}
c32memset(*) %{uchar("wmemset")}
c16mempcpy(*) %{uchar("wmempcpy")}
c32mempcpy(*) %{uchar("wmempcpy")}
c16mempmove(*) %{uchar("wmempmove")}
c32mempmove(*) %{uchar("wmempmove")}
c16mempset(*) %{uchar("wmempset")}
c32mempset(*) %{uchar("wmempset")}

[[libc]] c16send(*) %{uchar("wcsend")}
[[libc]] c32send(*) %{uchar("wcsend")}
[[libc]] c16snend(*) %{uchar("wcsnend")}
[[libc]] c32snend(*) %{uchar("wcsnend")}
[[libc]] c16slen(*) %{uchar("wcslen")}
[[libc]] c32slen(*) %{uchar("wcslen")}
[[libc]] c16snlen(*) %{uchar("wcsnlen")}
[[libc]] c32snlen(*) %{uchar("wcsnlen")}
[[libc]] c16scmp(*) %{uchar("wcscmp")}
[[libc]] c32scmp(*) %{uchar("wcscmp")}
[[libc]] c16sncmp(*) %{uchar("wcsncmp")}
[[libc]] c32sncmp(*) %{uchar("wcsncmp")}

c16schr(*) %{uchar("wcschr")}
c32schr(*) %{uchar("wcschr")}
c16srchr(*) %{uchar("wcsrchr")}
c32srchr(*) %{uchar("wcsrchr")}
c16snchr(*) %{uchar("wcsnchr")}
c32snchr(*) %{uchar("wcsnchr")}
c16snrchr(*) %{uchar("wcsnrchr")}
c32snrchr(*) %{uchar("wcsnrchr")}

c16schrnul(*) %{uchar("wcschrnul")}
c32schrnul(*) %{uchar("wcschrnul")}
c16srchrnul(*) %{uchar("wcsrchrnul")}
c32srchrnul(*) %{uchar("wcsrchrnul")}
c16snchrnul(*) %{uchar("wcsnchrnul")}
c32snchrnul(*) %{uchar("wcsnchrnul")}
c16snrchrnul(*) %{uchar("wcsnrchrnul")}
c32snrchrnul(*) %{uchar("wcsnrchrnul")}

c16soff(*) %{uchar("wcsoff")}
c32soff(*) %{uchar("wcsoff")}
c16sroff(*) %{uchar("wcsroff")}
c32sroff(*) %{uchar("wcsroff")}
c16snoff(*) %{uchar("wcsnoff")}
c32snoff(*) %{uchar("wcsnoff")}
c16snroff(*) %{uchar("wcsnroff")}
c32snroff(*) %{uchar("wcsnroff")}

c16sstr(*) %{uchar("wcsstr")}
c32sstr(*) %{uchar("wcsstr")}
c16scasestr(*) %{uchar("wcscasestr")}
c32scasestr(*) %{uchar("wcscasestr")}

c16scpy(*) %{uchar("wcscpy")}
c32scpy(*) %{uchar("wcscpy")}
c16spcpy(*) %{uchar("wcspcpy")}
c32spcpy(*) %{uchar("wcspcpy")}
c16sncpy(*) %{uchar("wcsncpy")}
c32sncpy(*) %{uchar("wcsncpy")}
c16spncpy(*) %{uchar("wcspncpy")}
c32spncpy(*) %{uchar("wcspncpy")}

c16scat(*) %{uchar("wcscat")}
c32scat(*) %{uchar("wcscat")}
c16sncat(*) %{uchar("wcsncat")}
c32sncat(*) %{uchar("wcsncat")}

c16sspn(*) %{uchar("wcsspn")}
c32sspn(*) %{uchar("wcsspn")}
c16scspn(*) %{uchar("wcscspn")}
c32scspn(*) %{uchar("wcscspn")}

c16spbrk(*) %{uchar("wcspbrk")}
c32spbrk(*) %{uchar("wcspbrk")}

[[guard]] c16stok(*) %{uchar("wcstok")}
[[guard]] c32stok(*) %{uchar("wcstok")}

c16ssep(*) %{uchar("wcssep")}
c32ssep(*) %{uchar("wcssep")}

c16sdup(*) %{uchar("wcsdup")}
c32sdup(*) %{uchar("wcsdup")}

c16sndup(*) %{uchar("wcsndup")}
c32sndup(*) %{uchar("wcsndup")}

c16sfry(*) %{uchar("wcsfry")}
c32sfry(*) %{uchar("wcsfry")}

c16scasecmp(*) %{uchar("wcscasecmp")}
c32scasecmp(*) %{uchar("wcscasecmp")}
c16sncasecmp(*) %{uchar("wcsncasecmp")}
c32sncasecmp(*) %{uchar("wcsncasecmp")}

c16sxfrm(*) %{uchar("wcsxfrm")}
c32sxfrm(*) %{uchar("wcsxfrm")}

c16scoll(*) %{uchar("wcscoll")}
c32scoll(*) %{uchar("wcscoll")}
c16sncoll(*) %{uchar("wcsncoll")}
c32sncoll(*) %{uchar("wcsncoll")}
c16scasecoll(*) %{uchar("wcscasecoll")}
c32scasecoll(*) %{uchar("wcscasecoll")}
c16sncasecoll(*) %{uchar("wcsncasecoll")}
c32sncasecoll(*) %{uchar("wcsncasecoll")}

c16slwr(*) %{uchar("wcslwr")}
c32slwr(*) %{uchar("wcslwr")}
c16supr(*) %{uchar("wcsupr")}
c32supr(*) %{uchar("wcsupr")}
c16srev(*) %{uchar("wcsrev")}
c32srev(*) %{uchar("wcsrev")}
c16snrev(*) %{uchar("wcsnrev")}
c32snrev(*) %{uchar("wcsnrev")}
c16sset(*) %{uchar("wcsset")}
c32sset(*) %{uchar("wcsset")}
c16snset(*) %{uchar("wcsnset")}
c32snset(*) %{uchar("wcsnset")}

fuzzy_c16memcmp(*) %{uchar("fuzzy_wmemcmp")}
fuzzy_c32memcmp(*) %{uchar("fuzzy_wmemcmp")}
fuzzy_c16memcasecmp(*) %{uchar("fuzzy_wmemcasecmp")}
fuzzy_c32memcasecmp(*) %{uchar("fuzzy_wmemcasecmp")}
fuzzy_c16scmp(*) %{uchar("fuzzy_wcscmp")}
fuzzy_c32scmp(*) %{uchar("fuzzy_wcscmp")}
fuzzy_c16sncmp(*) %{uchar("fuzzy_wcsncmp")}
fuzzy_c32sncmp(*) %{uchar("fuzzy_wcsncmp")}
fuzzy_c16scasecmp(*) %{uchar("fuzzy_wcscasecmp")}
fuzzy_c32scasecmp(*) %{uchar("fuzzy_wcscasecmp")}
fuzzy_c16sncasecmp(*) %{uchar("fuzzy_wcsncasecmp")}
fuzzy_c32sncasecmp(*) %{uchar("fuzzy_wcsncasecmp")}

wildc16scmp(*) %{uchar("wildwcscmp")}
wildc32scmp(*) %{uchar("wildwcscmp")}
wildc16scasecmp(*) %{uchar("wildwcscasecmp")}
wildc32scasecmp(*) %{uchar("wildwcscasecmp")}

c16sverscmp(*) %{uchar("wcsverscmp")}
c32sverscmp(*) %{uchar("wcsverscmp")}


%#ifdef __USE_XOPEN2K8
c16scasestr_l(*) %{uchar("wcscasestr_l")}
c32scasestr_l(*) %{uchar("wcscasestr_l")}
c16scasecmp_l(*) %{uchar("wcscasecmp_l")}
c32scasecmp_l(*) %{uchar("wcscasecmp_l")}
c16sncasecmp_l(*) %{uchar("wcsncasecmp_l")}
c32sncasecmp_l(*) %{uchar("wcsncasecmp_l")}
c16sxfrm_l(*) %{uchar("wcsxfrm_l")}
c32sxfrm_l(*) %{uchar("wcsxfrm_l")}
c16scoll_l(*) %{uchar("wcscoll_l")}
c32scoll_l(*) %{uchar("wcscoll_l")}
c16sncoll_l(*) %{uchar("wcsncoll_l")}
c32sncoll_l(*) %{uchar("wcsncoll_l")}
c16scasecoll_l(*) %{uchar("wcscasecoll_l")}
c32scasecoll_l(*) %{uchar("wcscasecoll_l")}
c16sncasecoll_l(*) %{uchar("wcsncasecoll_l")}
c32sncasecoll_l(*) %{uchar("wcsncasecoll_l")}
c16slwr_l(*) %{uchar("wcslwr_l")}
c32slwr_l(*) %{uchar("wcslwr_l")}
c16supr_l(*) %{uchar("wcsupr_l")}
c32supr_l(*) %{uchar("wcsupr_l")}

fuzzy_c16memcasecmp_l(*) %{uchar("fuzzy_wmemcasecmp_l")}
fuzzy_c32memcasecmp_l(*) %{uchar("fuzzy_wmemcasecmp_l")}
fuzzy_c16scasecmp_l(*) %{uchar("fuzzy_wcscasecmp_l")}
fuzzy_c32scasecmp_l(*) %{uchar("fuzzy_wcscasecmp_l")}
fuzzy_c16sncasecmp_l(*) %{uchar("fuzzy_wcsncasecmp_l")}
fuzzy_c32sncasecmp_l(*) %{uchar("fuzzy_wcsncasecmp_l")}

wildc16scasecmp_l(*) %{uchar("wildwcscasecmp_l")}
wildc32scasecmp_l(*) %{uchar("wildwcscasecmp_l")}
%#endif /* __USE_XOPEN2K8 */


%{

#endif /* __CC__ */

__SYSDECL_END

}

