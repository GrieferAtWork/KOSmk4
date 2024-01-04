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
%[define_replacement(pid_t = __pid_t)]

%[insert:prefix(
#include <features.h>
)]%{
#ifndef _PROCESS_H
#include <process.h>
#endif /* !_PROCESS_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */

}%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

%(auto_header){
#ifndef __T16ARGV
#ifdef __USE_DOS_ALTERATIONS
#define __T16ARGV char16_t const *const *__restrict ___argv
#define __T16ENVP char16_t const *const *__restrict ___envp
#else /* __USE_DOS_ALTERATIONS */
#define __T16ARGV char16_t *const ___argv[__restrict_arr]
#define __T16ENVP char16_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__T16ARGV */
#ifndef __T32ARGV
#ifdef __USE_DOS_ALTERATIONS
#define __T32ARGV char32_t const *const *__restrict ___argv
#define __T32ENVP char32_t const *const *__restrict ___envp
#else /* __USE_DOS_ALTERATIONS */
#define __T32ARGV char32_t *const ___argv[__restrict_arr]
#define __T32ENVP char32_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__T32ARGV */
}

%{
#ifndef __TWARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TWARGV wchar_t const *const *__restrict ___argv
#define __TWENVP wchar_t const *const *__restrict ___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TWARGV wchar_t *const ___argv[__restrict_arr]
#define __TWENVP wchar_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TWARGV */
}

%[define_type_class(__TWARGV = "TP")]
%[define_type_class(__TWENVP = "TP")]

%[default:section(".text.crt{|.dos}.wchar.fs.exec.exec")]

[[decl_include("<features.h>", "<hybrid/typecore.h>"), decl_prefix(DEFINE_TARGV)]]
[[cp, guard, wchar, argument_names(path, ___argv), dos_export_alias("_wexecv")]]
[[requires_function(execv, convert_wcstombs, convert_wcstombsv)]]
int wexecv([[in]] wchar_t const *__restrict path, [[in]] __TWARGV) {
	int result = -1;
	char *utf8_path, **utf8_argv;
	utf8_path = convert_wcstombs(path);
	if unlikely(!utf8_path)
		goto done;
	utf8_argv = convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	result = execv(utf8_path, utf8_argv);
@@pp_if $has_function(convert_freev)@@
	convert_freev(utf8_argv);
@@pp_endif@@
done_file:
@@pp_if $has_function(free)@@
	free(utf8_path);
@@pp_endif@@
done:
	return result;
}

[[decl_include("<features.h>", "<hybrid/typecore.h>"), decl_prefix(DEFINE_TARGV)]]
[[cp, guard, wchar, argument_names(path, ___argv, ___envp), dos_export_alias("_wexecve")]]
[[requires_function(execve, convert_wcstombs, convert_wcstombsv)]]
int wexecve([[in]] wchar_t const *__restrict path, [[in]] __TWARGV, [[in]] __TWENVP) {
	int result = -1;
	char *utf8_path, **utf8_argv, **utf8_envp;
	utf8_path = convert_wcstombs(path);
	if unlikely(!utf8_path)
		goto done;
	utf8_argv = convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	utf8_envp = NULL;
	if unlikely(___envp && (utf8_envp = convert_wcstombsv(___envp)) == NULL)
		goto done_argv;
	result = execve(utf8_path, utf8_argv, utf8_envp);
@@pp_if $has_function(convert_freev)@@
	convert_freev(utf8_envp);
@@pp_endif@@
done_argv:
@@pp_if $has_function(convert_freev)@@
	convert_freev(utf8_argv);
@@pp_endif@@
done_file:
@@pp_if $has_function(free)@@
	free(utf8_path);
@@pp_endif@@
done:
	return result;
}

[[decl_include("<features.h>", "<hybrid/typecore.h>"), decl_prefix(DEFINE_TARGV)]]
[[cp, guard, wchar, argument_names(file, ___argv), dos_export_alias("_wexecvp")]]
[[requires_function(execvp, convert_wcstombs, convert_wcstombsv)]]
int wexecvp([[in]] wchar_t const *__restrict file, [[in]] __TWARGV) {
	int result = -1;
	char *utf8_file, **utf8_argv;
	utf8_file = convert_wcstombs(file);
	if unlikely(!utf8_file)
		goto done;
	utf8_argv = convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	result = execvp(utf8_file, utf8_argv);
@@pp_if $has_function(convert_freev)@@
	convert_freev(utf8_argv);
@@pp_endif@@
done_file:
@@pp_if $has_function(free)@@
	free(utf8_file);
@@pp_endif@@
done:
	return result;
}

[[decl_include("<features.h>", "<hybrid/typecore.h>"), decl_prefix(DEFINE_TARGV)]]
[[cp, guard, wchar, argument_names(file, ___argv, ___envp), dos_export_alias("_wexecvpe")]]
[[requires_function(execvpe, convert_wcstombs, convert_wcstombsv)]]
int wexecvpe([[in]] wchar_t const *__restrict file, [[in]] __TWARGV, [[in]] __TWENVP) {
	int result = -1;
	char *utf8_file, **utf8_argv, **utf8_envp;
	utf8_file = convert_wcstombs(file);
	if unlikely(!utf8_file)
		goto done;
	utf8_argv = convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	utf8_envp = NULL;
	if unlikely(___envp && (utf8_envp = convert_wcstombsv(___envp)) == NULL)
		goto done_argv;
	result = execvpe(utf8_file, utf8_argv, utf8_envp);
@@pp_if $has_function(convert_freev)@@
	convert_freev(utf8_envp);
@@pp_endif@@
done_argv:
@@pp_if $has_function(convert_freev)@@
	convert_freev(utf8_argv);
@@pp_endif@@
done_file:
@@pp_if $has_function(free)@@
	free(utf8_file);
@@pp_endif@@
done:
	return result;
}


[[cp, guard, wchar, impl_include("<parts/redirect-exec.h>"), decl_include("<hybrid/typecore.h>")]]
[[requires_dependent_function(wexecv), ATTR_SENTINEL, dos_export_alias("_wexecl")]]
int wexecl([[in]] wchar_t const *__restrict path, [[in_opt]] wchar_t const *args, ... /*, (wchar_t *)NULL*/) {
	__REDIRECT_EXECL(wchar_t, wexecv, path, args)
}

[[cp, guard, wchar, impl_include("<parts/redirect-exec.h>"), decl_include("<hybrid/typecore.h>")]]
[[requires_dependent_function(wexecve), ATTR_SENTINEL_O(1), dos_export_alias("_wexecle")]]
int wexecle([[in]] wchar_t const *__restrict path, [[in_opt]] wchar_t const *args, ... /*, (wchar_t *)NULL, [[in]] wchar_t **environ*/) {
	__REDIRECT_EXECLE(wchar_t, wexecve, path, args)
}

[[cp, guard, wchar, impl_include("<parts/redirect-exec.h>"), decl_include("<hybrid/typecore.h>")]]
[[requires_dependent_function(wexecvp), ATTR_SENTINEL, dos_export_alias("_wexeclp")]]
int wexeclp([[in]] wchar_t const *__restrict file, [[in_opt]] wchar_t const *args, ... /*, (wchar_t *)NULL*/) {
	__REDIRECT_EXECL(wchar_t, wexecvp, file, args)
}

[[cp, guard, wchar, impl_include("<parts/redirect-exec.h>"), decl_include("<hybrid/typecore.h>")]]
[[requires_dependent_function(wexecvpe), ATTR_SENTINEL_O(1), dos_export_alias("_wexeclpe")]]
int wexeclpe([[in]] wchar_t const *__restrict file, [[in_opt]] wchar_t const *args, ... /*, (wchar_t *)NULL, [[in]] wchar_t **environ*/) {
	__REDIRECT_EXECLE(wchar_t, wexecvpe, file, args)
}


%[default:section(".text.crt{|.dos}.wchar.fs.exec.spawn")]

[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV), decl_include("<bits/types.h>")]]
[[cp, guard, wchar, argument_names(mode, path, ___argv), dos_export_alias("_wspawnv")]]
[[requires_function(spawnv, convert_wcstombs, convert_wcstombsv)]]
$pid_t wspawnv(__STDC_INT_AS_UINT_T mode, [[in]] wchar_t const *__restrict path, [[in]] __TWARGV) {
	int result = -1;
	char *utf8_path, **utf8_argv;
	utf8_path = convert_wcstombs(path);
	if unlikely(!utf8_path)
		goto done;
	utf8_argv = convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	result = spawnv(mode, utf8_path, utf8_argv);
@@pp_if $has_function(convert_freev)@@
	convert_freev(utf8_argv);
@@pp_endif@@
done_file:
@@pp_if $has_function(free)@@
	free(utf8_path);
@@pp_endif@@
done:
	return result;
}


[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV), decl_include("<bits/types.h>")]]
[[cp, guard, wchar, argument_names(mode, path, ___argv, ___envp), dos_export_alias("_wspawnve")]]
[[requires_function(spawnve, convert_wcstombs, convert_wcstombsv)]]
$pid_t wspawnve(__STDC_INT_AS_UINT_T mode,
                [[in]] wchar_t const *__restrict path,
                [[in]] __TWARGV, [[in]] __TWENVP) {
	int result = -1;
	char *utf8_path, **utf8_argv, **utf8_envp;
	utf8_path = convert_wcstombs(path);
	if unlikely(!utf8_path)
		goto done;
	utf8_argv = convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	utf8_envp = NULL;
	if unlikely(___envp && (utf8_envp = convert_wcstombsv(___envp)) == NULL)
		goto done_argv;
	result = spawnve(mode, utf8_path, utf8_argv, utf8_envp);
@@pp_if $has_function(convert_freev)@@
	convert_freev(utf8_envp);
@@pp_endif@@
done_argv:
@@pp_if $has_function(convert_freev)@@
	convert_freev(utf8_argv);
@@pp_endif@@
done_file:
@@pp_if $has_function(free)@@
	free(utf8_path);
@@pp_endif@@
done:
	return result;
}

[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV), decl_include("<bits/types.h>")]]
[[cp, guard, wchar, argument_names(mode, file, ___argv), dos_export_alias("_wspawnvp")]]
[[requires_function(spawnvp, convert_wcstombs, convert_wcstombsv)]]
$pid_t wspawnvp(__STDC_INT_AS_UINT_T mode, [[in]] wchar_t const *__restrict file, [[in]] __TWARGV) {
	int result = -1;
	char *utf8_file, **utf8_argv;
	utf8_file = convert_wcstombs(file);
	if unlikely(!utf8_file)
		goto done;
	utf8_argv = convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	result = spawnvp(mode, utf8_file, utf8_argv);
@@pp_if $has_function(convert_freev)@@
	convert_freev(utf8_argv);
@@pp_endif@@
done_file:
@@pp_if $has_function(free)@@
	free(utf8_file);
@@pp_endif@@
done:
	return result;
}

[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV), decl_include("<bits/types.h>")]]
[[cp, guard, wchar, argument_names(mode, file, ___argv, ___envp), dos_export_alias("_wspawnvpe")]]
[[requires_function(spawnvpe, convert_wcstombs, convert_wcstombsv)]]
$pid_t wspawnvpe(__STDC_INT_AS_UINT_T mode,
                 [[in]] wchar_t const *__restrict file,
                 [[in]] __TWARGV, [[in]] __TWENVP) {
	int result = -1;
	char *utf8_file, **utf8_argv, **utf8_envp;
	utf8_file = convert_wcstombs(file);
	if unlikely(!utf8_file)
		goto done;
	utf8_argv = convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	utf8_envp = NULL;
	if unlikely(___envp && (utf8_envp = convert_wcstombsv(___envp)) == NULL)
		goto done_argv;
	result = spawnvpe(mode, utf8_file, utf8_argv, utf8_envp);
@@pp_if $has_function(convert_freev)@@
	convert_freev(utf8_envp);
@@pp_endif@@
done_argv:
@@pp_if $has_function(convert_freev)@@
	convert_freev(utf8_argv);
@@pp_endif@@
done_file:
@@pp_if $has_function(free)@@
	free(utf8_file);
@@pp_endif@@
done:
	return result;
}

[[cp, guard, wchar, impl_include("<parts/redirect-exec.h>"), decl_include("<features.h>", "<bits/types.h>")]]
[[requires_dependent_function(wspawnv), ATTR_SENTINEL, dos_export_alias("_wspawnl")]]
$pid_t wspawnl(__STDC_INT_AS_UINT_T mode, [[in]] wchar_t const *__restrict path, [[in_opt]] wchar_t const *args, ... /*, (wchar_t *)NULL*/) {
	__REDIRECT_SPAWNL(wchar_t, wspawnv, mode, path, args)
}

[[cp, guard, wchar, impl_include("<parts/redirect-exec.h>"), decl_include("<features.h>", "<bits/types.h>")]]
[[requires_dependent_function(wspawnve), ATTR_SENTINEL_O(1), dos_export_alias("_wspawnle")]]
$pid_t wspawnle(__STDC_INT_AS_UINT_T mode, [[in]] wchar_t const *__restrict path, [[in_opt]] wchar_t const *args, ... /*, (wchar_t *)NULL, [[in]] wchar_t **environ*/) {
	__REDIRECT_SPAWNLE(wchar_t, wspawnve, mode, path, args)
}

[[cp, guard, wchar, impl_include("<parts/redirect-exec.h>"), decl_include("<features.h>", "<bits/types.h>")]]
[[requires_dependent_function(wspawnvp), ATTR_SENTINEL, dos_export_alias("_wspawnlp")]]
$pid_t wspawnlp(__STDC_INT_AS_UINT_T mode, [[in]] wchar_t const *__restrict file, [[in_opt]] wchar_t const *args, ... /*, (wchar_t *)NULL*/) {
	__REDIRECT_SPAWNL(wchar_t, wspawnvp, mode, file, args)
}

[[cp, guard, wchar, impl_include("<parts/redirect-exec.h>"), decl_include("<features.h>", "<bits/types.h>")]]
[[requires_dependent_function(wspawnvpe), ATTR_SENTINEL_O(1), dos_export_alias("_wspawnlpe")]]
$pid_t wspawnlpe(__STDC_INT_AS_UINT_T mode, [[in]] wchar_t const *__restrict file, [[in_opt]] wchar_t const *args, ... /*, (wchar_t *)NULL, [[in]] wchar_t **environ*/) {
	__REDIRECT_SPAWNLE(wchar_t, wspawnvpe, mode, file, args)
}

%[insert:extern(wsystem)]

%{

__SYSDECL_END
#endif /* __CC__ */

}
