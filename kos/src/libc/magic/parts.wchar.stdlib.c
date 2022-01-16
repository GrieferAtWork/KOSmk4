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
#include <hybrid/typecore.h>
)]%{
#ifndef _STDLIB_H
#include <stdlib.h>
#endif /* !_STDLIB_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */

#ifdef __CC__
__SYSDECL_BEGIN

}

%#ifdef __USE_KOS
%[default:section(".text.crt{|.dos}.wchar.unicode.static.convert")]
[[wchar, pure, wunused, dos_export_alias("_wtoi")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("wtol", "_wtol")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("wtoll", "_wtoll")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_wtoi64")]]
int wtoi([[nonnull]] wchar_t const *nptr) %{generate(str2wcs("atoi"))}

[[wchar, pure, wunused, dos_export_alias("_wtol")]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, wtoi)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__), alias("_wtoi")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("wtoll", "_wtoll")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_wtoi64")]]
long wtol([[nonnull]] wchar_t const *nptr) %{generate(str2wcs("atol"))}

%#ifdef __LONGLONG
[[wchar, pure, wunused, dos_export_alias("_wtoll")]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, "wtoi")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__), alias("_wtoi")]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, "wtol")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("_wtol")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias("_wtoi64")]]
__LONGLONG wtoll([[nonnull]] wchar_t const *nptr) %{generate(str2wcs("atoll"))}
%#endif /* __LONGLONG */
%#endif /* __USE_KOS */

%{

__SYSDECL_END
#endif /* __CC__ */

}
