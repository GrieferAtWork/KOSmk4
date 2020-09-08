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

%(auto_header,user){
#ifndef __T16ARGV
#ifdef __USE_DOS
#define __T16ARGV char16_t const *const *__restrict ___argv
#define __T16ENVP char16_t const *const *__restrict ___envp
#else /* __USE_DOS */
#define __T16ARGV char16_t *const ___argv[__restrict_arr]
#define __T16ENVP char16_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__T16ARGV */
#ifndef __T32ARGV
#ifdef __USE_DOS
#define __T32ARGV char32_t const *const *__restrict ___argv
#define __T32ENVP char32_t const *const *__restrict ___envp
#else /* __USE_DOS */
#define __T32ARGV char32_t *const ___argv[__restrict_arr]
#define __T32ENVP char32_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__T32ARGV */
}

%{
#ifndef __TWARGV
#ifdef __USE_DOS
#define __TWARGV wchar_t const *const *__restrict ___argv
#define __TWENVP wchar_t const *const *__restrict ___envp
#else /* __USE_DOS */
#define __TWARGV wchar_t *const ___argv[__restrict_arr]
#define __TWENVP wchar_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__TWARGV */
}

%[define_type_class(__TWARGV = "TP")]
%[define_type_class(__TWENVP = "TP")]

%[default:section(".text.crt{|.dos}.wchar.fs.exec.exec")]

[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[cp, guard, wchar, argument_names(path, ___argv), dos_export_alias("_wexecv")]]
int wexecv([[nonnull]] wchar_t const *__restrict path, [[nonnull]] __TWARGV);

[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[cp, guard, wchar, argument_names(path, ___argv, ___envp), dos_export_alias("_wexecve")]]
int wexecve([[nonnull]] wchar_t const *__restrict path, [[nonnull]] __TWARGV, [[nonnull]] __TWENVP);

[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[cp, guard, wchar, argument_names(path, ___argv), dos_export_alias("_wexecvp")]]
int wexecvp([[nonnull]] wchar_t const *__restrict file, [[nonnull]] __TWARGV);

[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[cp, guard, wchar, argument_names(path, ___argv, ___envp), dos_export_alias("_wexecvpe")]]
int wexecvpe([[nonnull]] wchar_t const *__restrict file, [[nonnull]] __TWARGV, [[nonnull]] __TWENVP);


[[cp, guard, wchar, userimpl, impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function(wexecv), ATTR_SENTINEL, dos_export_alias("_wexecl")]]
int wexecl([[nonnull]] wchar_t const *__restrict path, wchar_t const *args, ... /*, (wchar_t *)NULL*/) {
	__REDIRECT_EXECL(wchar_t, wexecv, path, args)
}

[[cp, guard, wchar, userimpl, impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function(wexecvp), ATTR_SENTINEL, dos_export_alias("_wexeclp")]]
int wexeclp([[nonnull]] wchar_t const *__restrict file, wchar_t const *args, ... /*, (wchar_t *)NULL*/) {
	__REDIRECT_EXECL(wchar_t, wexecvp, file, args)
}

[[cp, guard, wchar, userimpl, impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function(wexecve), ATTR_SENTINEL_O(1), dos_export_alias("_wexecle")]]
int wexecle([[nonnull]] wchar_t const *__restrict path, wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) {
	__REDIRECT_EXECLE(wchar_t, wexecve, path, args)
}

[[cp, guard, wchar, userimpl, impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function(wexecvpe), ATTR_SENTINEL_O(1), dos_export_alias("_wexeclpe")]]
int wexeclpe([[nonnull]] wchar_t const *__restrict file, wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) {
	__REDIRECT_EXECLE(wchar_t, wexecvpe, file, args)
}


%[default:section(".text.crt{|.dos}.wchar.fs.exec.spawn")]

[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[cp, guard, wchar, argument_names(mode, path, ___argv), dos_export_alias("_wspawnv")]]
$pid_t wspawnv(int mode, [[nonnull]] wchar_t const *__restrict path, [[nonnull]] __TWARGV);

[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[cp, guard, wchar, argument_names(mode, path, ___argv, ___envp), dos_export_alias("_wspawnve")]]
$pid_t wspawnve(int mode, [[nonnull]] wchar_t const *__restrict path, [[nonnull]] __TWARGV, [[nonnull]] __TWENVP);

[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[cp, guard, wchar, argument_names(mode, file, ___argv), dos_export_alias("_wspawnvp")]]
$pid_t wspawnvp(int mode, [[nonnull]] wchar_t const *__restrict file, [[nonnull]] __TWARGV);

[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[cp, guard, wchar, argument_names(mode, file, ___argv, ___envp), dos_export_alias("_wspawnvpe")]]
$pid_t wspawnvpe(int mode, [[nonnull]] wchar_t const *__restrict file, [[nonnull]] __TWARGV, [[nonnull]] __TWENVP);

[[cp, guard, wchar, userimpl, impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function(wspawnv), ATTR_SENTINEL, dos_export_alias("_wspawnl")]]
$pid_t wspawnl(int mode, [[nonnull]] wchar_t const *__restrict path, wchar_t const *args, ... /*, (wchar_t *)NULL*/) {
	__REDIRECT_SPAWNL(wchar_t, wspawnv, mode, path, args)
}

[[cp, guard, wchar, userimpl, impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function(wspawnvp), ATTR_SENTINEL, dos_export_alias("_wspawnlp")]]
$pid_t wspawnlp(int mode, [[nonnull]] wchar_t const *__restrict file, wchar_t const *args, ... /*, (wchar_t *)NULL*/) {
	__REDIRECT_SPAWNL(wchar_t, wspawnvp, mode, file, args)
}

[[cp, guard, wchar, userimpl, impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function(wspawnve), ATTR_SENTINEL_O(1), dos_export_alias("_wspawnle")]]
$pid_t wspawnle(int mode, [[nonnull]] wchar_t const *__restrict path, wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) {
	__REDIRECT_SPAWNLE(wchar_t, wspawnve, mode, path, args)
}

[[cp, guard, wchar, userimpl, impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function(wspawnvpe), ATTR_SENTINEL_O(1), dos_export_alias("_wspawnlpe")]]
$pid_t wspawnlpe(int mode, [[nonnull]] wchar_t const *__restrict file, wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) {
	__REDIRECT_SPAWNLE(wchar_t, wspawnvpe, mode, file, args)
}

[[cp, guard, wchar, dos_export_alias("_wsystem")]]
[[section(".text.crt{|.dos}.wchar.fs.exec.system")]]
int wsystem([[nullable]] wchar_t const *cmd);


%{

#endif /* __CC__ */

__SYSDECL_END

}

