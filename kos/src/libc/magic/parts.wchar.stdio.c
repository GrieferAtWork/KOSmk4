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

%[insert:prefix(
#include <features.h>
)]%{
#ifndef _STDIO_H
#include <stdio.h>
#endif /* !_STDIO_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */

}%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

[[guard, wchar, dos_export_alias("_wremove")]]
[[section(".text.crt{|.dos}.wchar.fs.modify")]]
int wremove([[nonnull]] wchar_t const *filename);

[[wchar, wunused, dos_export_alias("_wfopen")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.access")]]
$FILE *wfopen([[nonnull]] wchar_t const *filename,
              [[nonnull]] wchar_t const *mode);

[[wchar, wunused, dos_export_alias("_wfreopen")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.access")]]
$FILE *wfreopen([[nonnull]] wchar_t const *filename,
                [[nonnull]] wchar_t const *mode,
                $FILE *stream);

[[guard, wchar, wunused, dos_export_alias("_wpopen")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.access")]]
$FILE *wpopen([[nonnull]] wchar_t const *command,
              [[nonnull]] wchar_t const *mode);


%{

__SYSDECL_END
#endif /* __CC__ */

}
