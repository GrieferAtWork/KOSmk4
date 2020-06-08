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

c16memcpy(*) %{uchar(wmemcpy)}
c32memcpy(*) %{uchar(wmemcpy)}
c16memmove(*) %{uchar(wmemmove)}
c32memmove(*) %{uchar(wmemmove)}
c16memset(*) %{uchar(wmemset)}
c32memset(*) %{uchar(wmemset)}
c16mempcpy(*) %{uchar(wmempcpy)}
c32mempcpy(*) %{uchar(wmempcpy)}
c16mempmove(*) %{uchar(wmempmove)}
c32mempmove(*) %{uchar(wmempmove)}
c16mempset(*) %{uchar(wmempset)}
c32mempset(*) %{uchar(wmempset)}

[[libc]] c16end(*) %{uchar(wcsend)}
[[libc]] c32end(*) %{uchar(wcsend)}
[[libc]] c16nend(*) %{uchar(wcsnend)}
[[libc]] c32nend(*) %{uchar(wcsnend)}
[[libc]] c16len(*) %{uchar(wcslen)}
[[libc]] c32len(*) %{uchar(wcslen)}
[[libc]] c16nlen(*) %{uchar(wcsnlen)}
[[libc]] c32nlen(*) %{uchar(wcsnlen)}
[[libc]] c16cmp(*) %{uchar(wcscmp)}
[[libc]] c32cmp(*) %{uchar(wcscmp)}
[[libc]] c16ncmp(*) %{uchar(wcsncmp)}
[[libc]] c32ncmp(*) %{uchar(wcsncmp)}

c16chr(*) %{uchar(wcschr)}
c32chr(*) %{uchar(wcschr)}
c16rchr(*) %{uchar(wcsrchr)}
c32rchr(*) %{uchar(wcsrchr)}
c16nchr(*) %{uchar(wcsnchr)}
c32nchr(*) %{uchar(wcsnchr)}
c16nrchr(*) %{uchar(wcsnrchr)}
c32nrchr(*) %{uchar(wcsnrchr)}

c16chrnul(*) %{uchar(wcschrnul)}
c32chrnul(*) %{uchar(wcschrnul)}
c16rchrnul(*) %{uchar(wcsrchrnul)}
c32rchrnul(*) %{uchar(wcsrchrnul)}
c16nchrnul(*) %{uchar(wcsnchrnul)}
c32nchrnul(*) %{uchar(wcsnchrnul)}
c16nrchrnul(*) %{uchar(wcsnrchrnul)}
c32nrchrnul(*) %{uchar(wcsnrchrnul)}

c16off(*) %{uchar(wcsoff)}
c32off(*) %{uchar(wcsoff)}
c16roff(*) %{uchar(wcsroff)}
c32roff(*) %{uchar(wcsroff)}
c16noff(*) %{uchar(wcsnoff)}
c32noff(*) %{uchar(wcsnoff)}
c16nroff(*) %{uchar(wcsnroff)}
c32nroff(*) %{uchar(wcsnroff)}

c16str(*) %{uchar(wcsstr)}
c32str(*) %{uchar(wcsstr)}
c16casestr(*) %{uchar(wcscasestr)}
c32casestr(*) %{uchar(wcscasestr)}

c16cpy(*) %{uchar(wcscpy)}
c32cpy(*) %{uchar(wcscpy)}
c16pcpy(*) %{uchar(wcspcpy)}
c32pcpy(*) %{uchar(wcspcpy)}
c16ncpy(*) %{uchar(wcsncpy)}
c32ncpy(*) %{uchar(wcsncpy)}
c16pncpy(*) %{uchar(wcspncpy)}
c32pncpy(*) %{uchar(wcspncpy)}

c16cat(*) %{uchar(wcscat)}
c32cat(*) %{uchar(wcscat)}
c16ncat(*) %{uchar(wcsncat)}
c32ncat(*) %{uchar(wcsncat)}

c16spn(*) %{uchar(wcsspn)}
c32spn(*) %{uchar(wcsspn)}
c16cspn(*) %{uchar(wcscspn)}
c32cspn(*) %{uchar(wcscspn)}

c16pbrk(*) %{uchar(wcspbrk)}
c32pbrk(*) %{uchar(wcspbrk)}

[[guard]] c16tok(*) %{uchar(wcstok)}
[[guard]] c32tok(*) %{uchar(wcstok)}

c16sep(*) %{uchar(wcssep)}
c32sep(*) %{uchar(wcssep)}

c16dup(*) %{uchar(wcsdup)}
c32dup(*) %{uchar(wcsdup)}

c16ndup(*) %{uchar(wcsndup)}
c32ndup(*) %{uchar(wcsndup)}

c16fry(*) %{uchar(wcsfry)}
c32fry(*) %{uchar(wcsfry)}

c16casecmp(*) %{uchar(wcscasecmp)}
c32casecmp(*) %{uchar(wcscasecmp)}
c16ncasecmp(*) %{uchar(wcsncasecmp)}
c32ncasecmp(*) %{uchar(wcsncasecmp)}

c16xfrm(*) %{uchar(wcsxfrm)}
c32xfrm(*) %{uchar(wcsxfrm)}

c16coll(*) %{uchar(wcscoll)}
c32coll(*) %{uchar(wcscoll)}
c16ncoll(*) %{uchar(wcsncoll)}
c32ncoll(*) %{uchar(wcsncoll)}
c16casecoll(*) %{uchar(wcscasecoll)}
c32casecoll(*) %{uchar(wcscasecoll)}
c16ncasecoll(*) %{uchar(wcsncasecoll)}
c32ncasecoll(*) %{uchar(wcsncasecoll)}

c16lwr(*) %{uchar(wcslwr)}
c32lwr(*) %{uchar(wcslwr)}
c16upr(*) %{uchar(wcsupr)}
c32upr(*) %{uchar(wcsupr)}
c16rev(*) %{uchar(wcsrev)}
c32rev(*) %{uchar(wcsrev)}
c16nrev(*) %{uchar(wcsnrev)}
c32nrev(*) %{uchar(wcsnrev)}
c16set(*) %{uchar(wcsset)}
c32set(*) %{uchar(wcsset)}
c16nset(*) %{uchar(wcsnset)}
c32nset(*) %{uchar(wcsnset)}

fuzzy_c16memcmp(*) %{uchar(fuzzy_wmemcmp)}
fuzzy_c32memcmp(*) %{uchar(fuzzy_wmemcmp)}
fuzzy_c16memcasecmp(*) %{uchar(fuzzy_wmemcasecmp)}
fuzzy_c32memcasecmp(*) %{uchar(fuzzy_wmemcasecmp)}
fuzzy_c16cmp(*) %{uchar(fuzzy_wcscmp)}
fuzzy_c32cmp(*) %{uchar(fuzzy_wcscmp)}
fuzzy_c16ncmp(*) %{uchar(fuzzy_wcsncmp)}
fuzzy_c32ncmp(*) %{uchar(fuzzy_wcsncmp)}
fuzzy_c16casecmp(*) %{uchar(fuzzy_wcscasecmp)}
fuzzy_c32casecmp(*) %{uchar(fuzzy_wcscasecmp)}
fuzzy_c16ncasecmp(*) %{uchar(fuzzy_wcsncasecmp)}
fuzzy_c32ncasecmp(*) %{uchar(fuzzy_wcsncasecmp)}

wildc16cmp(*) %{uchar(wildwcscmp)}
wildc32cmp(*) %{uchar(wildwcscmp)}
wildc16casecmp(*) %{uchar(wildwcscasecmp)}
wildc32casecmp(*) %{uchar(wildwcscasecmp)}

c16verscmp(*) %{uchar(wcsverscmp)}
c32verscmp(*) %{uchar(wcsverscmp)}


%#ifdef __USE_XOPEN2K8
c16casestr_l(*) %{uchar(wcscasestr_l)}
c32casestr_l(*) %{uchar(wcscasestr_l)}
c16casecmp_l(*) %{uchar(wcscasecmp_l)}
c32casecmp_l(*) %{uchar(wcscasecmp_l)}
c16ncasecmp_l(*) %{uchar(wcsncasecmp_l)}
c32ncasecmp_l(*) %{uchar(wcsncasecmp_l)}
c16xfrm_l(*) %{uchar(wcsxfrm_l)}
c32xfrm_l(*) %{uchar(wcsxfrm_l)}
c16coll_l(*) %{uchar(wcscoll_l)}
c32coll_l(*) %{uchar(wcscoll_l)}
c16ncoll_l(*) %{uchar(wcsncoll_l)}
c32ncoll_l(*) %{uchar(wcsncoll_l)}
c16casecoll_l(*) %{uchar(wcscasecoll_l)}
c32casecoll_l(*) %{uchar(wcscasecoll_l)}
c16ncasecoll_l(*) %{uchar(wcsncasecoll_l)}
c32ncasecoll_l(*) %{uchar(wcsncasecoll_l)}
c16lwr_l(*) %{uchar(wcslwr_l)}
c32lwr_l(*) %{uchar(wcslwr_l)}
c16upr_l(*) %{uchar(wcsupr_l)}
c32upr_l(*) %{uchar(wcsupr_l)}

fuzzy_c16memcasecmp_l(*) %{uchar(fuzzy_wmemcasecmp_l)}
fuzzy_c32memcasecmp_l(*) %{uchar(fuzzy_wmemcasecmp_l)}
fuzzy_c16casecmp_l(*) %{uchar(fuzzy_wcscasecmp_l)}
fuzzy_c32casecmp_l(*) %{uchar(fuzzy_wcscasecmp_l)}
fuzzy_c16ncasecmp_l(*) %{uchar(fuzzy_wcsncasecmp_l)}
fuzzy_c32ncasecmp_l(*) %{uchar(fuzzy_wcsncasecmp_l)}

wildc16casecmp_l(*) %{uchar(wildwcscasecmp_l)}
wildc32casecmp_l(*) %{uchar(wildwcscasecmp_l)}
%#endif /* __USE_XOPEN2K8 */


%{

#endif /* __CC__ */

__SYSDECL_END

}

