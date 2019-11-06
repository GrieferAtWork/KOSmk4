/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]
%[define_replacement(pid_t = __pid_t)]

%{
#include <features.h>
#include <process.h>
#include <uchar.h>
#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__

}

%[define_wchar_replacement(__TWARGV = __T16ARGV, __T32ARGV)]
%[define_wchar_replacement(__TWENVP = __T16ENVP, __T32ENVP)]
%{
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

[attribute(*)][argument_names(path, ___argv)]
[if(__SIZEOF_WCHAR_T__ == 2), alias(_wexecv)][alias(DOS$_wexecv)]
c16execv:(char16_t const *__restrict path, [nonnull] @__T16ARGV@) -> int %{uchar(wexecv)}

[attribute(*)][argument_names(path, ___argv)]
[if(__SIZEOF_WCHAR_T__ == 4), alias(_wexecv)]
c32execv:(char32_t const *__restrict path, [nonnull] @__T32ARGV@) -> int %{uchar(wexecv)}

[attribute(*)][argument_names(path, ___argv, ___envp)]
[if(__SIZEOF_WCHAR_T__ == 2), alias(_wexecve)][alias(DOS$_wexecve)]
c16execve:(char16_t const *__restrict path, [nonnull] @__T16ARGV@, [nonnull] @__T16ENVP@) -> int %{uchar(wexecve)}

[attribute(*)][argument_names(path, ___argv, ___envp)]
[if(__SIZEOF_WCHAR_T__ == 4), alias(_wexecve)]
c32execve:(char32_t const *__restrict path, [nonnull] @__T32ARGV@, [nonnull] @__T32ENVP@) -> int %{uchar(wexecve)}

[attribute(*)][argument_names(path, ___argv)]
[if(__SIZEOF_WCHAR_T__ == 2), alias(_wexecvp)][alias(DOS$_wexecvp)]
c16execvp:(char16_t const *__restrict path, [nonnull] @__T16ARGV@) -> int %{uchar(wexecvp)}

[attribute(*)][argument_names(path, ___argv)]
[if(__SIZEOF_WCHAR_T__ == 4), alias(_wexecvp)]
c32execvp:(char32_t const *__restrict path, [nonnull] @__T32ARGV@) -> int %{uchar(wexecvp)}

[attribute(*)][argument_names(path, ___argv, ___envp)]
[if(__SIZEOF_WCHAR_T__ == 2), alias(_wexecvpe)][alias(DOS$_wexecvpe)]
c16execvpe:(char16_t const *__restrict path, [nonnull] @__T16ARGV@, [nonnull] @__T16ENVP@) -> int %{uchar(wexecvpe)}

[attribute(*)][argument_names(path, ___argv, ___envp)]
[if(__SIZEOF_WCHAR_T__ == 4), alias(_wexecvpe)]
c32execvpe:(char32_t const *__restrict path, [nonnull] @__T32ARGV@, [nonnull] @__T32ENVP@) -> int %{uchar(wexecvpe)}


[cp][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(c16execv)][ATTR_SENTINEL][allow_macros]
[if(__SIZEOF_WCHAR_T__ == 2), preferred_alias(wexecl, _wexecl)]
[preferred_alias(DOS$_wexecl)][nocrt][noexport][nouser][doc_alias(wexecl)]
c16execl:([nonnull] char16_t const *__restrict path, char16_t const *args, ... /*, (char16_t *)NULL*/) -> int {
	__REDIRECT_EXECL(char16_t, c16execv, path, args)
}

[cp][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(c32execv)][ATTR_SENTINEL][allow_macros]
[if(__SIZEOF_WCHAR_T__ == 4), preferred_alias(wexecl, _wexecl)]
[nocrt][noexport][nouser][doc_alias(wexecl)]
c32execl:([nonnull] char32_t const *__restrict path, char32_t const *args, ... /*, (char32_t *)NULL*/) -> int {
	__REDIRECT_EXECL(char32_t, c32execv, path, args)
}

[cp][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(c16execvp)][ATTR_SENTINEL][allow_macros]
[if(__SIZEOF_WCHAR_T__ == 2), preferred_alias(wexeclp, _wexeclp)]
[preferred_alias(DOS$_wexeclp)][nocrt][noexport][nouser][doc_alias(wexeclp)]
c16execlp:([nonnull] char16_t const *__restrict file, char16_t const *args, ... /*, (char16_t *)NULL*/) -> int {
	__REDIRECT_EXECL(char16_t, c16execvp, file, args)
}

[cp][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(c32execvp)][ATTR_SENTINEL][allow_macros]
[if(__SIZEOF_WCHAR_T__ == 4), preferred_alias(wexeclp, _wexeclp)]
[nocrt][noexport][nouser][doc_alias(wexeclp)]
c32execlp:([nonnull] char32_t const *__restrict file, char32_t const *args, ... /*, (char32_t *)NULL*/) -> int {
	__REDIRECT_EXECL(char32_t, c32execvp, file, args)
}




[cp][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(c16execve)][ATTR_SENTINEL_O(1)][allow_macros]
[if(__SIZEOF_WCHAR_T__ == 2), preferred_alias(wexecle, _wexecle)]
[preferred_alias(DOS$_wexecle)][nocrt][noexport][nouser][doc_alias(wexecle)]
c16execle:([nonnull] char16_t const *__restrict path, char16_t const *args, ... /*, (char16_t *)NULL, char16_t **environ*/) -> int {
	__REDIRECT_EXECLE(char16_t, c16execve, path, args)
}

[cp][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(c32execve)][ATTR_SENTINEL_O(1)][allow_macros]
[if(__SIZEOF_WCHAR_T__ == 4), preferred_alias(wexecle, _wexecle)]
[nocrt][noexport][nouser][doc_alias(wexecle)]
c32execle:([nonnull] char32_t const *__restrict path, char32_t const *args, ... /*, (char32_t *)NULL, char32_t **environ*/) -> int {
	__REDIRECT_EXECLE(char32_t, c32execve, path, args)
}

[cp][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(c16execvpe)][ATTR_SENTINEL_O(1)][allow_macros]
[if(__SIZEOF_WCHAR_T__ == 2), preferred_alias(wexeclpe, _wexeclpe)]
[preferred_alias(DOS$_wexeclpe)][nocrt][noexport][nouser][doc_alias(wexeclpe)]
c16execlpe:([nonnull] char16_t const *__restrict file, char16_t const *args, ... /*, (char16_t *)NULL, char16_t **environ*/) -> int {
	__REDIRECT_EXECLE(char16_t, c16execvpe, file, args)
}

[cp][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(c32execvpe)][ATTR_SENTINEL_O(1)][allow_macros]
[if(__SIZEOF_WCHAR_T__ == 4), preferred_alias(wexeclpe, _wexeclpe)]
[nocrt][noexport][nouser][doc_alias(wexeclpe)]
c32execlpe:([nonnull] char32_t const *__restrict file, char32_t const *args, ... /*, (char32_t *)NULL, char32_t **environ*/) -> int {
	__REDIRECT_EXECLE(char32_t, c32execvpe, file, args)
}




[attribute(*)][argument_names(mode, path, ___argv)]
[if(__SIZEOF_WCHAR_T__ == 2), alias(_wspawnv)][alias(DOS$_wspawnv)]
c16spawnv:(int mode, [nonnull] char16_t const *__restrict path, [nonnull] @__T16ARGV@) -> $pid_t %{uchar(wspawnv)}

[attribute(*)][argument_names(mode, path, ___argv)]
[if(__SIZEOF_WCHAR_T__ == 4), alias(_wspawnv)]
c32spawnv:(int mode, [nonnull] char32_t const *__restrict path, [nonnull] @__T32ARGV@) -> $pid_t %{uchar(wspawnv)}

[attribute(*)][argument_names(mode, path, ___argv, ___envp)]
[if(__SIZEOF_WCHAR_T__ == 2), alias(_wspawnve)][alias(DOS$_wspawnve)]
c16spawnve:(int mode, [nonnull] char16_t const *__restrict path, [nonnull] @__T16ARGV@, [nonnull] @__T16ENVP@) -> $pid_t %{uchar(wspawnve)}

[attribute(*)][argument_names(mode, path, ___argv, ___envp)]
[if(__SIZEOF_WCHAR_T__ == 4), alias(_wspawnve)]
c32spawnve:(int mode, [nonnull] char32_t const *__restrict path, [nonnull] @__T32ARGV@, [nonnull] @__T32ENVP@) -> $pid_t %{uchar(wspawnve)}

[attribute(*)][argument_names(mode, path, ___argv)]
[if(__SIZEOF_WCHAR_T__ == 2), alias(_wspawnvp)][alias(DOS$_wspawnvp)]
c16spawnvp:(int mode, [nonnull] char16_t const *__restrict path, [nonnull] @__T16ARGV@) -> $pid_t %{uchar(wspawnvp)}

[attribute(*)][argument_names(mode, path, ___argv)]
[if(__SIZEOF_WCHAR_T__ == 4), alias(_wspawnvp)]
c32spawnvp:(int mode, [nonnull] char32_t const *__restrict path, [nonnull] @__T32ARGV@) -> $pid_t %{uchar(wspawnvp)}

[attribute(*)][argument_names(mode, path, ___argv, ___envp)]
[if(__SIZEOF_WCHAR_T__ == 2), alias(_wspawnvpe)][alias(DOS$_wspawnvpe)]
c16spawnvpe:(int mode, [nonnull] char16_t const *__restrict path, [nonnull] @__T16ARGV@, [nonnull] @__T16ENVP@) -> $pid_t %{uchar(wspawnvpe)}

[attribute(*)][argument_names(mode, path, ___argv, ___envp)]
[if(__SIZEOF_WCHAR_T__ == 4), alias(_wspawnvpe)]
c32spawnvpe:(int mode, [nonnull] char32_t const *__restrict path, [nonnull] @__T32ARGV@, [nonnull] @__T32ENVP@) -> $pid_t %{uchar(wspawnvpe)}


[cp][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(c16spawnv)][ATTR_SENTINEL][allow_macros]
[if(__SIZEOF_WCHAR_T__ == 2), preferred_alias(wspawnl, _wspawnl)]
[preferred_alias(DOS$_wspawnl)][nocrt][noexport][nouser][doc_alias(wspawnl)]
c16spawnl:(int mode, [nonnull] char16_t const *__restrict path, char16_t const *args, ... /*, (char16_t *)NULL*/) -> $pid_t {
	__REDIRECT_SPAWNL(char16_t, c16spawnv, mode, path, args)
}

[cp][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(c32spawnv)][ATTR_SENTINEL][allow_macros]
[if(__SIZEOF_WCHAR_T__ == 4), preferred_alias(wspawnl, _wspawnl)]
[nocrt][noexport][nouser][doc_alias(wspawnl)]
c32spawnl:(int mode, [nonnull] char32_t const *__restrict path, char32_t const *args, ... /*, (char32_t *)NULL*/) -> $pid_t {
	__REDIRECT_SPAWNL(char32_t, c32spawnv, mode, path, args)
}

[cp][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(c16spawnvp)][ATTR_SENTINEL][allow_macros]
[if(__SIZEOF_WCHAR_T__ == 2), preferred_alias(wspawnlp, _wspawnlp)]
[preferred_alias(DOS$_wspawnlp)][nocrt][noexport][nouser][doc_alias(wspawnlp)]
c16spawnlp:(int mode, [nonnull] char16_t const *__restrict file, char16_t const *args, ... /*, (char16_t *)NULL*/) -> $pid_t {
	__REDIRECT_SPAWNL(char16_t, c16spawnvp, mode, file, args)
}

[cp][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(c32spawnvp)][ATTR_SENTINEL][allow_macros]
[if(__SIZEOF_WCHAR_T__ == 4), preferred_alias(wspawnlp, _wspawnlp)]
[nocrt][noexport][nouser][doc_alias(wspawnlp)]
c32spawnlp:(int mode, [nonnull] char32_t const *__restrict file, char32_t const *args, ... /*, (char32_t *)NULL*/) -> $pid_t {
	__REDIRECT_SPAWNL(char32_t, c32spawnvp, mode, file, args)
}




[cp][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(c16spawnve)][ATTR_SENTINEL_O(1)][allow_macros]
[if(__SIZEOF_WCHAR_T__ == 2), preferred_alias(wspawnle, _wspawnle)]
[preferred_alias(DOS$_wspawnle)][nocrt][noexport][nouser][doc_alias(wspawnle)]
c16spawnle:(int mode, [nonnull] char16_t const *__restrict path, char16_t const *args, ... /*, (char16_t *)NULL, char16_t **environ*/) -> $pid_t {
	__REDIRECT_SPAWNLE(char16_t, c16spawnve, mode, path, args)
}

[cp][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(c32spawnve)][ATTR_SENTINEL_O(1)][allow_macros]
[if(__SIZEOF_WCHAR_T__ == 4), preferred_alias(wspawnle, _wspawnle)]
[nocrt][noexport][nouser][doc_alias(wspawnle)]
c32spawnle:(int mode, [nonnull] char32_t const *__restrict path, char32_t const *args, ... /*, (char32_t *)NULL, char32_t **environ*/) -> $pid_t {
	__REDIRECT_SPAWNLE(char32_t, c32spawnve, mode, path, args)
}

[cp][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(c16spawnvpe)][ATTR_SENTINEL_O(1)][allow_macros]
[if(__SIZEOF_WCHAR_T__ == 2), preferred_alias(wspawnlpe, _wspawnlpe)]
[preferred_alias(DOS$_wspawnlpe)][nocrt][noexport][nouser][doc_alias(wspawnlpe)]
c16spawnlpe:(int mode, [nonnull] char16_t const *__restrict file, char16_t const *args, ... /*, (char16_t *)NULL, char16_t **environ*/) -> $pid_t {
	__REDIRECT_SPAWNLE(char16_t, c16spawnvpe, mode, file, args)
}

[cp][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(c32spawnvpe)][ATTR_SENTINEL_O(1)][allow_macros]
[if(__SIZEOF_WCHAR_T__ == 4), preferred_alias(wspawnlpe, _wspawnlpe)]
[nocrt][noexport][nouser][doc_alias(wspawnlpe)]
c32spawnlpe:(int mode, [nonnull] char32_t const *__restrict file, char32_t const *args, ... /*, (char32_t *)NULL, char32_t **environ*/) -> $pid_t {
	__REDIRECT_SPAWNLE(char32_t, c32spawnvpe, mode, file, args)
}


[alias(*)][attribute(*)] c16system:(*) %{uchar(wsystem)}
[alias(*)][attribute(*)] c32system:(*) %{uchar(wsystem)}

%{

#endif /* __CC__ */

__SYSDECL_END

}

