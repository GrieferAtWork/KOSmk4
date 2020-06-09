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
#ifndef _STDLIB_H
#include <stdlib.h>
#endif /* !_STDLIB_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */

__SYSDECL_BEGIN

#ifdef __CC__

}

%#ifdef __USE_KOS
%[default_impl_section("{.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert}")]
[[wchar, ATTR_WUNUSED, ATTR_PURE, crt_dosname("_wtoi")]]
[[if(__SIZEOF_INT__ == __SIZEOF_LONG__), alias("wtol", "_wtol")]]
[[if(__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("wtoll", "_wtoll")]]
[[if(__SIZEOF_INT__ == 8), alias("_wtoi64")]]
int wtoi([[nonnull]] wchar_t const *nptr) %{generate(str2wcs("atoi"))}

[[wchar, ATTR_WUNUSED, ATTR_PURE, crt_dosname("_wtol")]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, wtoi)]]
[[if(__SIZEOF_LONG__ == __SIZEOF_INT__), alias("_wtoi")]]
[[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("wtoll", "_wtoll")]]
[[if(__SIZEOF_LONG__ == 8), alias("_wtoi64")]]
long wtol([[nonnull]] wchar_t const *nptr) %{generate(str2wcs("atol"))}

%#ifdef __LONGLONG
[[wchar, ATTR_WUNUSED, ATTR_PURE, crt_dosname("_wtoll")]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, "wtoi")]]
[[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INT__), alias("_wtoi")]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, "wtol")]]
[[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("_wtol")]]
[[if(__SIZEOF_LONG_LONG__ == 8), alias("_wtoi64")]]
__LONGLONG wtoll([[nonnull]] wchar_t const *nptr) %{generate(str2wcs("atoll"))}
%#endif /* __LONGLONG */
%#endif /* __USE_KOS */

%{

#endif /* __CC__ */

__SYSDECL_END

}

