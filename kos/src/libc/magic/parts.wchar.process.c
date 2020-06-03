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
%[define_replacement(pid_t = __pid_t)]

%{
#include <features.h>
#ifndef _PROCESS_H
#include <process.h>
#endif /* !_PROCESS_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */
#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__

}

%(user){
#ifndef __T16ARGV
#ifdef __USE_DOS
#   define __T16ARGV char16_t const *const *__restrict ___argv
#   define __T16ENVP char16_t const *const *__restrict ___envp
#else /* __USE_DOS */
#   define __T16ARGV char16_t *const ___argv[__restrict_arr]
#   define __T16ENVP char16_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__T16ARGV */
#ifndef __T32ARGV
#ifdef __USE_DOS
#   define __T32ARGV char32_t const *const *__restrict ___argv
#   define __T32ENVP char32_t const *const *__restrict ___envp
#else /* __USE_DOS */
#   define __T32ARGV char32_t *const ___argv[__restrict_arr]
#   define __T32ENVP char32_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__T32ARGV */
}

%#ifndef __TWARGV
%#ifdef __USE_DOS
%#   define __TWARGV wchar_t const *const *__restrict ___argv
%#   define __TWENVP wchar_t const *const *__restrict ___envp
%#else
%#   define __TWARGV wchar_t *const ___argv[__restrict_arr]
%#   define __TWENVP wchar_t *const ___envp[__restrict_arr]
%#endif
%#endif /* !__TWARGV */

%[default_impl_section({.text.crt.wchar.fs.exec.exec|.text.crt.dos.wchar.fs.exec.exec})]
[cp][wchar][guard][argument_names(path, ___argv)][dosname(_wexecv)]
wexecv:([[nonnull]] wchar_t const *__restrict path, [[nonnull]] __TWARGV) -> int;
[cp][wchar][guard][argument_names(path, ___argv, ___envp)][dosname(_wexecve)]
wexecve:([[nonnull]] wchar_t const *__restrict path, [[nonnull]] __TWARGV, [[nonnull]] __TWENVP) -> int;
[cp][wchar][guard][argument_names(path, ___argv)][dosname(_wexecvp)]
wexecvp:([[nonnull]] wchar_t const *__restrict file, [[nonnull]] __TWARGV) -> int;
[cp][wchar][guard][argument_names(path, ___argv, ___envp)][dosname(_wexecvpe)]
wexecvpe:([[nonnull]] wchar_t const *__restrict file, [[nonnull]] __TWARGV, [[nonnull]] __TWENVP) -> int;

[cp][wchar][guard][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(wexecv)][ATTR_SENTINEL][dosname(_wexecl)][allow_macros]
wexecl:([[nonnull]] wchar_t const *__restrict path, wchar_t const *args, ... /*, (wchar_t *)NULL*/) -> int {
	__REDIRECT_EXECL(wchar_t, wexecv, path, args)
}
[cp][wchar][guard][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(wexecvp)][ATTR_SENTINEL][dosname(_wexeclp)][allow_macros]
wexeclp:([[nonnull]] wchar_t const *__restrict file, wchar_t const *args, ... /*, (wchar_t *)NULL*/) -> int {
	__REDIRECT_EXECL(wchar_t, wexecvp, file, args)
}
[cp][wchar][guard][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(wexecve)][ATTR_SENTINEL_O(1)][dosname(_wexecle)][allow_macros]
wexecle:([[nonnull]] wchar_t const *__restrict path, wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) -> int {
	__REDIRECT_EXECLE(wchar_t, wexecve, path, args)
}
[cp][wchar][guard][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(wexecvpe)][ATTR_SENTINEL_O(1)][dosname(_wexecle)][allow_macros]
wexeclpe:([[nonnull]] wchar_t const *__restrict file, wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) -> int {
	__REDIRECT_EXECLE(wchar_t, wexecvpe, file, args)
}


%[default_impl_section({.text.crt.wchar.fs.exec.spawn|.text.crt.dos.wchar.fs.exec.spawn})]
[cp][wchar][guard][argument_names(mode, path, ___argv)][dosname(_wspawnv)]
wspawnv:(int mode, [[nonnull]] wchar_t const *__restrict path, [[nonnull]] __TWARGV) -> $pid_t;
[cp][wchar][guard][argument_names(mode, path, ___argv, ___envp)][dosname(_wspawnve)]
wspawnve:(int mode, [[nonnull]] wchar_t const *__restrict path, [[nonnull]] __TWARGV, [[nonnull]] __TWENVP) -> $pid_t;
[cp][wchar][guard][argument_names(mode, file, ___argv)][dosname(_wspawnvp)]
wspawnvp:(int mode, [[nonnull]] wchar_t const *__restrict file, [[nonnull]] __TWARGV) -> $pid_t;
[cp][wchar][guard][argument_names(mode, file, ___argv, ___envp)][dosname(_wspawnvpe)]
wspawnvpe:(int mode, [[nonnull]] wchar_t const *__restrict file, [[nonnull]] __TWARGV, [[nonnull]] __TWENVP) -> $pid_t;

[cp][wchar][guard][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(wspawnv)][ATTR_SENTINEL][dosname(_wspawnl)][allow_macros]
wspawnl:(int mode, [[nonnull]] wchar_t const *__restrict path, wchar_t const *args, ... /*, (wchar_t *)NULL*/) -> $pid_t {
	__REDIRECT_SPAWNL(wchar_t, wspawnv, mode, path, args)
}

[cp][wchar][guard][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(wspawnvp)][ATTR_SENTINEL][dosname(_wspawnlp)][allow_macros]
wspawnlp:(int mode, [[nonnull]] wchar_t const *__restrict file, wchar_t const *args, ... /*, (wchar_t *)NULL*/) -> $pid_t {
	__REDIRECT_SPAWNLP(wchar_t, wspawnvp, mode, file, args)
}

[cp][wchar][guard][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(wspawnve)][ATTR_SENTINEL_O(1)][dosname(_wspawnle)][allow_macros]
wspawnle:(int mode, [[nonnull]] wchar_t const *__restrict path, wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) -> $pid_t {
	__REDIRECT_SPAWNLE(wchar_t, wspawnve, mode, path, args)
}

[cp][wchar][guard][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(wspawnvpe)][ATTR_SENTINEL_O(1)][dosname(_wspawnle)][allow_macros]
wspawnlpe:(int mode, [[nonnull]] wchar_t const *__restrict file, wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) -> $pid_t {
	__REDIRECT_SPAWNLPE(wchar_t, wspawnvpe, mode, file, args)
}

[cp][wchar][guard][dosname(_wsystem)]
[section({.text.crt.wchar.fs.exec.system|.text.crt.dos.wchar.fs.exec.system})]
wsystem:([[nullable]] wchar_t const *cmd) -> int;


%{

#endif /* __CC__ */

__SYSDECL_END

}

