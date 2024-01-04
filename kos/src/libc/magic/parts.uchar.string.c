/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]

%[insert:prefix(
#include <features.h>
)]%{
#ifndef _STRING_H
#include <string.h>
#endif /* !_STRING_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

}%[insert:prefix(
#include <parts/malloca.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

c16memcpy(*) %{uchar16("wmemcpy")}
c32memcpy(*) %{uchar32("wmemcpy")}
c16memcmp(*) %{uchar16("wmemcmp")}
c32memcmp(*) %{uchar32("wmemcmp")}
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

[[libc]] c16end(*) %{uchar16("wcsend")}
[[libc]] c32end(*) %{uchar32("wcsend")}
[[libc]] c16nend(*) %{uchar16("wcsnend")}
[[libc]] c32nend(*) %{uchar32("wcsnend")}
[[libc]] c16len(*) %{uchar16("wcslen")}
[[libc]] c32len(*) %{uchar32("wcslen")}
[[libc]] c16nlen(*) %{uchar16("wcsnlen")}
[[libc]] c32nlen(*) %{uchar32("wcsnlen")}
[[libc]] c16cmp(*) %{uchar16("wcscmp")}
[[libc]] c32cmp(*) %{uchar32("wcscmp")}
[[libc]] c16ncmp(*) %{uchar16("wcsncmp")}
[[libc]] c32ncmp(*) %{uchar32("wcsncmp")}

c16chr(*) %{uchar16("wcschr")}
c32chr(*) %{uchar32("wcschr")}
c16rchr(*) %{uchar16("wcsrchr")}
c32rchr(*) %{uchar32("wcsrchr")}
c16nchr(*) %{uchar16("wcsnchr")}
c32nchr(*) %{uchar32("wcsnchr")}
c16nrchr(*) %{uchar16("wcsnrchr")}
c32nrchr(*) %{uchar32("wcsnrchr")}

c16chrnul(*) %{uchar16("wcschrnul")}
c32chrnul(*) %{uchar32("wcschrnul")}
c16rchrnul(*) %{uchar16("wcsrchrnul")}
c32rchrnul(*) %{uchar32("wcsrchrnul")}
c16nchrnul(*) %{uchar16("wcsnchrnul")}
c32nchrnul(*) %{uchar32("wcsnchrnul")}
c16nrchrnul(*) %{uchar16("wcsnrchrnul")}
c32nrchrnul(*) %{uchar32("wcsnrchrnul")}

c16off(*) %{uchar16("wcsoff")}
c32off(*) %{uchar32("wcsoff")}
c16roff(*) %{uchar16("wcsroff")}
c32roff(*) %{uchar32("wcsroff")}
c16noff(*) %{uchar16("wcsnoff")}
c32noff(*) %{uchar32("wcsnoff")}
c16nroff(*) %{uchar16("wcsnroff")}
c32nroff(*) %{uchar32("wcsnroff")}

c16str(*) %{uchar16("wcsstr")}
c32str(*) %{uchar32("wcsstr")}
c16casestr(*) %{uchar16("wcscasestr")}
c32casestr(*) %{uchar32("wcscasestr")}

c16cpy(*) %{uchar16("wcscpy")}
c32cpy(*) %{uchar32("wcscpy")}
c16pcpy(*) %{uchar16("wcspcpy")}
c32pcpy(*) %{uchar32("wcspcpy")}
c16ncpy(*) %{uchar16("wcsncpy")}
c32ncpy(*) %{uchar32("wcsncpy")}
c16pncpy(*) %{uchar16("wcspncpy")}
c32pncpy(*) %{uchar32("wcspncpy")}

c16cat(*) %{uchar16("wcscat")}
c32cat(*) %{uchar32("wcscat")}
c16ncat(*) %{uchar16("wcsncat")}
c32ncat(*) %{uchar32("wcsncat")}

c16spn(*) %{uchar16("wcsspn")}
c32spn(*) %{uchar32("wcsspn")}
c16cspn(*) %{uchar16("wcscspn")}
c32cspn(*) %{uchar32("wcscspn")}

c16pbrk(*) %{uchar16("wcspbrk")}
c32pbrk(*) %{uchar32("wcspbrk")}

[[guard]] c16tok(*) %{uchar16("wcstok")}
[[guard]] c32tok(*) %{uchar32("wcstok")}

c16sep(*) %{uchar16("wcssep")}
c32sep(*) %{uchar32("wcssep")}

c16dup(*) %{uchar16("wcsdup")}
c32dup(*) %{uchar32("wcsdup")}

c16ndup(*) %{uchar16("wcsndup")}
c32ndup(*) %{uchar32("wcsndup")}

c16fry(*) %{uchar16("wcsfry")}
c32fry(*) %{uchar32("wcsfry")}

c16casecmp(*) %{uchar16("wcscasecmp")}
c32casecmp(*) %{uchar32("wcscasecmp")}
c16ncasecmp(*) %{uchar16("wcsncasecmp")}
c32ncasecmp(*) %{uchar32("wcsncasecmp")}

c16xfrm(*) %{uchar16("wcsxfrm")}
c32xfrm(*) %{uchar32("wcsxfrm")}

c16coll(*) %{uchar16("wcscoll")}
c32coll(*) %{uchar32("wcscoll")}
c16ncoll(*) %{uchar16("wcsncoll")}
c32ncoll(*) %{uchar32("wcsncoll")}
c16casecoll(*) %{uchar16("wcscasecoll")}
c32casecoll(*) %{uchar32("wcscasecoll")}
c16ncasecoll(*) %{uchar16("wcsncasecoll")}
c32ncasecoll(*) %{uchar32("wcsncasecoll")}

c16lwr(*) %{uchar16("wcslwr")}
c32lwr(*) %{uchar32("wcslwr")}
c16upr(*) %{uchar16("wcsupr")}
c32upr(*) %{uchar32("wcsupr")}
c16rev(*) %{uchar16("wcsrev")}
c32rev(*) %{uchar32("wcsrev")}
c16nrev(*) %{uchar16("wcsnrev")}
c32nrev(*) %{uchar32("wcsnrev")}
c16set(*) %{uchar16("wcsset")}
c32set(*) %{uchar32("wcsset")}
c16nset(*) %{uchar16("wcsnset")}
c32nset(*) %{uchar32("wcsnset")}

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

wildc16cmp(*) %{uchar16("wildwcscmp")}
wildc32cmp(*) %{uchar32("wildwcscmp")}
wildc16casecmp(*) %{uchar16("wildwcscasecmp")}
wildc32casecmp(*) %{uchar32("wildwcscasecmp")}

c16verscmp(*) %{uchar16("wcsverscmp")}
c32verscmp(*) %{uchar32("wcsverscmp")}

c16lstrip(*) %{uchar16("wcslstrip")}
c32lstrip(*) %{uchar32("wcslstrip")}
c16rstrip(*) %{uchar16("wcsrstrip")}
c32rstrip(*) %{uchar32("wcsrstrip")}
c16strip(*) %{uchar16("wcsstrip")}
c32strip(*) %{uchar32("wcsstrip")}

c16memcasecmp(*) %{uchar16("wmemcasecmp")}
c32memcasecmp(*) %{uchar32("wmemcasecmp")}

%#ifdef __USE_XOPEN2K8
c16memcasecmp_l(*) %{uchar16("wmemcasecmp_l")}
c32memcasecmp_l(*) %{uchar32("wmemcasecmp_l")}

c16casestr_l(*) %{uchar16("wcscasestr_l")}
c32casestr_l(*) %{uchar32("wcscasestr_l")}
c16casecmp_l(*) %{uchar16("wcscasecmp_l")}
c32casecmp_l(*) %{uchar32("wcscasecmp_l")}
c16ncasecmp_l(*) %{uchar16("wcsncasecmp_l")}
c32ncasecmp_l(*) %{uchar32("wcsncasecmp_l")}
c16xfrm_l(*) %{uchar16("wcsxfrm_l")}
c32xfrm_l(*) %{uchar32("wcsxfrm_l")}
c16coll_l(*) %{uchar16("wcscoll_l")}
c32coll_l(*) %{uchar32("wcscoll_l")}
c16ncoll_l(*) %{uchar16("wcsncoll_l")}
c32ncoll_l(*) %{uchar32("wcsncoll_l")}
c16casecoll_l(*) %{uchar16("wcscasecoll_l")}
c32casecoll_l(*) %{uchar32("wcscasecoll_l")}
c16ncasecoll_l(*) %{uchar16("wcsncasecoll_l")}
c32ncasecoll_l(*) %{uchar32("wcsncasecoll_l")}
c16lwr_l(*) %{uchar16("wcslwr_l")}
c32lwr_l(*) %{uchar32("wcslwr_l")}
c16upr_l(*) %{uchar16("wcsupr_l")}
c32upr_l(*) %{uchar32("wcsupr_l")}

fuzzy_c16memcasecmp_l(*) %{uchar16("fuzzy_wmemcasecmp_l")}
fuzzy_c32memcasecmp_l(*) %{uchar32("fuzzy_wmemcasecmp_l")}
fuzzy_c16casecmp_l(*) %{uchar16("fuzzy_wcscasecmp_l")}
fuzzy_c32casecmp_l(*) %{uchar32("fuzzy_wcscasecmp_l")}
fuzzy_c16ncasecmp_l(*) %{uchar16("fuzzy_wcsncasecmp_l")}
fuzzy_c32ncasecmp_l(*) %{uchar32("fuzzy_wcsncasecmp_l")}

wildc16casecmp_l(*) %{uchar16("wildwcscasecmp_l")}
wildc32casecmp_l(*) %{uchar32("wildwcscasecmp_l")}
%#endif /* __USE_XOPEN2K8 */


%{

__SYSDECL_END
#endif /* __CC__ */

}
