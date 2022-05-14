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
%(c_prefix){
/* (#) Portability: Windows Kits (/ucrt/corecrt_wprocess.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(oflag_t = __oflag_t)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <corecrt.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef __intptr_t_defined
#define __intptr_t_defined
typedef __INTPTR_TYPE__ intptr_t;
#endif /* !__intptr_t_defined */

}

%
%#ifndef _WPROCESS_DEFINED
%#define _WPROCESS_DEFINED 1
[[argument_names(mode, path, ___argv), decl_include("<features.h>", "<hybrid/typecore.h>")]]
int _wexecv([[nonnull]] wchar_t const *__restrict path,
            [[nonnull]] wchar_t const *const *__restrict ___argv) = wexecv;

[[argument_names(mode, file, ___argv), decl_include("<features.h>", "<hybrid/typecore.h>")]]
int _wexecvp([[nonnull]] wchar_t const *__restrict file,
             [[nonnull]] wchar_t const *const *__restrict ___argv) = wexecvp;

[[argument_names(mode, path, ___argv, ___envp), decl_include("<features.h>", "<hybrid/typecore.h>")]]
int _wexecve([[nonnull]] wchar_t const *__restrict path,
             [[nonnull]] wchar_t const *const *__restrict ___argv,
             [[nonnull]] wchar_t const *const *__restrict ___envp) = wexecve;

[[argument_names(mode, file, ___argv, ___envp), decl_include("<features.h>", "<hybrid/typecore.h>")]]
int _wexecvpe([[nonnull]] wchar_t const *__restrict file,
              [[nonnull]] wchar_t const *const *__restrict ___argv,
              [[nonnull]] wchar_t const *const *__restrict ___envp) = wexecvpe;

%[insert:function(_wexecl = wexecl)]
%[insert:function(_wexeclp = wexeclp)]
%[insert:function(_wexecle = wexecle)]
%[insert:function(_wexeclpe = wexeclpe)]

[[argument_names(mode, path, ___argv), decl_include("<features.h>", "<hybrid/typecore.h>")]]
intptr_t _wspawnv(__STDC_INT_AS_UINT_T mode,
                  [[nonnull]] wchar_t const *__restrict path,
                  [[nonnull]] wchar_t const *const *__restrict ___argv) = wspawnv;

[[argument_names(mode, file, ___argv), decl_include("<features.h>", "<hybrid/typecore.h>")]]
intptr_t _wspawnvp(__STDC_INT_AS_UINT_T mode,
                   [[nonnull]] wchar_t const *__restrict file,
                   [[nonnull]] wchar_t const *const *__restrict ___argv) = wspawnvp;

[[argument_names(mode, path, ___argv, ___envp), decl_include("<features.h>", "<hybrid/typecore.h>")]]
intptr_t _wspawnve(__STDC_INT_AS_UINT_T mode,
                   [[nonnull]] wchar_t const *__restrict path,
                   [[nonnull]] wchar_t const *const *__restrict ___argv,
                   [[nonnull]] wchar_t const *const *__restrict ___envp) = wspawnve;

[[argument_names(mode, file, ___argv, ___envp), decl_include("<features.h>", "<hybrid/typecore.h>")]]
intptr_t _wspawnvpe(__STDC_INT_AS_UINT_T mode,
                    [[nonnull]] wchar_t const *__restrict file,
                    [[nonnull]] wchar_t const *const *__restrict ___argv,
                    [[nonnull]] wchar_t const *const *__restrict ___envp) = wspawnvpe;

[[ATTR_SENTINEL, decl_include("<features.h>", "<hybrid/typecore.h>")]]
intptr_t _wspawnl(__STDC_INT_AS_UINT_T mode, [[nonnull]] wchar_t const *__restrict path,
                  wchar_t const *args, ... /*, (wchar_t *)NULL*/) = wspawnl;

[[ATTR_SENTINEL, decl_include("<features.h>", "<hybrid/typecore.h>")]]
intptr_t _wspawnlp(__STDC_INT_AS_UINT_T mode, [[nonnull]] wchar_t const *__restrict file,
                   wchar_t const *args, ... /*, (wchar_t *)NULL*/) = wspawnlp;

[[ATTR_SENTINEL_O(1), decl_include("<features.h>", "<hybrid/typecore.h>")]]
intptr_t _wspawnle(__STDC_INT_AS_UINT_T mode, [[nonnull]] wchar_t const *__restrict path,
                   wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) = wspawnle;

[[ATTR_SENTINEL_O(1), decl_include("<features.h>", "<hybrid/typecore.h>")]]
intptr_t _wspawnlpe(__STDC_INT_AS_UINT_T mode, [[nonnull]] wchar_t const *__restrict file,
                    wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) = wspawnlpe;
%#endif /* !_WPROCESS_DEFINED */

%
%[insert:function(_wsystem = wsystem, guardName: "_CRT_WSYSTEM_DEFINED")]

%{

__SYSDECL_END
#endif /* __CC__ */

}
