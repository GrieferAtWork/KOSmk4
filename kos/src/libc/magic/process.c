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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(pid_t = __pid_t)]

%{
#include <features.h>
#include <bits/types.h>

__SYSDECL_BEGIN

/* `MODE' argument values for spawn() functions. */
#define P_WAIT          0
#define P_NOWAIT        1
#define P_OVERLAY       2
#define P_NOWAITO       3
#define P_DETACH        4

/* `ACTION' argument values for cwait() functions. */
#define WAIT_CHILD      0
#define WAIT_GRANDCHILD 1


}


%{

#ifndef __TARGV
#ifdef __USE_DOS
#   define __TARGV  char const *const *___argv
#   define __TENVP  char const *const *___envp
#else
#   define __TARGV  char *const ___argv[__restrict_arr]
#   define __TENVP  char *const ___envp[__restrict_arr]
#endif
#endif /* !__TARGV */

/* DOS */
#ifdef __USE_DOS
#define _P_WAIT          P_WAIT
#define _P_NOWAIT        P_NOWAIT
#define _P_OVERLAY       P_OVERLAY
#define _P_NOWAITO       P_NOWAITO
#define _P_DETACH        P_DETACH
#define _OLD_P_OVERLAY   P_OVERLAY
#define _WAIT_CHILD      WAIT_CHILD
#define _WAIT_GRANDCHILD WAIT_GRANDCHILD
#define OLD_P_OVERLAY    _OLD_P_OVERLAY


#ifdef __CC__

#ifndef __intptr_t_defined
#define __intptr_t_defined 1
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */
#ifndef __uintptr_t_defined
#define __uintptr_t_defined 1
typedef __uintptr_t uintptr_t;
#endif /* !__uintptr_t_defined */
#ifndef __wchar_t_defined
#define __wchar_t_defined 1
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

}

%[default_impl_section(.text.crt.dos.sched.thread)]
%typedef void (__LIBCCALL *__dos_beginthread_entry_t)(void *__arg);
%typedef __UINT32_TYPE__ (__ATTR_STDCALL *__dos_beginthreadex_entry_t)(void *__arg);
%
_beginthread:(__dos_beginthread_entry_t entry, $u32 stacksz, void *arg) -> uintptr_t;
_beginthreadex:(void *sec, $u32 stacksz, __dos_beginthreadex_entry_t entry, void *arg, $u32 flags, $u32 *threadaddr) -> uintptr_t;
[userimpl][requires($has_function(_endthreadex))] _endthread:() {
	_endthreadex(0);
}
_endthreadex:($u32 exitcode);

%[default_impl_section(.text.crt.sched.process)]

%
%#ifndef _CRT_TERMINATE_DEFINED
%#define _CRT_TERMINATE_DEFINED 1
%[insert:extern(exit)]
%[insert:extern(abort)]
[guard][alias(quick_exit)][alias(exit)][ATTR_NORETURN][throws()]
[crtbuiltin] _exit:(int status) = _Exit;
%#endif /* !_CRT_TERMINATE_DEFINED */

%[default_impl_section(.text.crt.dos.sched.process)]
[throws] _cexit:();
[throws] _c_exit:() {
}

[guard][ATTR_WUNUSED] _getpid:() -> $pid_t = getpid;

%[default_impl_section(.text.crt.dos.fs.exec.exec)]
[alias(*)][attribute(*)] _execv:(*) = execv;
[alias(*)][attribute(*)] _execvp:(*) = execvp;
[alias(*)][attribute(*)] _execve:(*) = execve;
[alias(*)][attribute(*)] _execvpe:(*) = execvpe;
[alias(*)][attribute(*)] _execl:(*) = execl;
[alias(*)][attribute(*)] _execlp:(*) = execlp;
[alias(*)][attribute(*)] _execle:(*) = execle;
[alias(*)][attribute(*)] _execlpe:(*) = execlpe;

%[default_impl_section(.text.crt.dos.fs.exec.spawn)]
[alias(*)][attribute(*)] _cwait:(int *tstat, intptr_t pid, int action) -> intptr_t = cwait;
[alias(*)][attribute(*)][argument_names(mode, path, ___argv)]          _spawnv:(int mode, char const *__restrict path, @__TARGV@) -> intptr_t = spawnv;
[alias(*)][attribute(*)][argument_names(mode, file, ___argv)]          _spawnvp:(int mode, char const *__restrict file, @__TARGV@) -> intptr_t = spawnvp;
[alias(*)][attribute(*)][argument_names(mode, path, ___argv, ___envp)] _spawnve:(int mode, char const *__restrict path, @__TARGV@, @__TENVP@) -> intptr_t = spawnve;
[alias(*)][attribute(*)][argument_names(mode, file, ___argv, ___envp)] _spawnvpe:(int mode, char const *__restrict file, @__TARGV@, @__TENVP@) -> intptr_t = spawnvpe;
[alias(*)][attribute(*)][allow_macros] _spawnl:(int mode, char const *__restrict path, char const *args, ... /*, (char *)NULL*/) -> intptr_t = spawnl;
[alias(*)][attribute(*)][allow_macros] _spawnlp:(int mode, char const *__restrict file, char const *args, ... /*, (char *)NULL*/) -> intptr_t = spawnlp;
[alias(*)][attribute(*)][allow_macros] _spawnle:(int mode, char const *__restrict path, char const *args, ... /*, (char *)NULL, (char **)environ*/) -> intptr_t = spawnle;
[alias(*)][attribute(*)][allow_macros] _spawnlpe:(int mode, char const *__restrict file, char const *args, ... /*, (char *)NULL, (char **)environ*/) -> intptr_t = spawnlpe;

%[default_impl_section(.text.crt.fs.exec.system)]
%[insert:extern(system)]

%
%
%

%[default_impl_section(.text.crt.dos.fs.dlfcn)]
[throws] _loaddll:(char __KOS_FIXED_CONST *file) -> intptr_t;

[throws] _unloaddll:(intptr_t hnd) -> int;

%
%typedef int (__LIBCCALL *__procfun)(void);
[throws] _getdllprocaddr:(intptr_t hnd, char __KOS_FIXED_CONST *symname, intptr_t ord) -> __procfun;


%{

#ifndef __wchar_t_defined
#define __wchar_t_defined 1
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef __intptr_t_defined
#define __intptr_t_defined 1
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */

#ifndef __TWARGV
#ifdef __USE_DOS
#   define __TWARGV wchar_t const *const *__restrict ___argv
#   define __TWENVP wchar_t const *const *__restrict ___envp
#else
#   define __TWARGV wchar_t *const ___argv[__restrict_arr]
#   define __TWENVP wchar_t *const ___envp[__restrict_arr]
#endif
#endif /* !__TWARGV */

}

%
%#ifndef _WPROCESS_DEFINED
%#define _WPROCESS_DEFINED 1
%[default_impl_section({.text.crt.wchar.fs.exec.exec|.text.crt.dos.wchar.fs.exec.exec})]
[alias(*)][attribute(*)] _wexecv:(*) = wexecv;
[alias(*)][attribute(*)] _wexecvp:(*) = wexecvp;
[alias(*)][attribute(*)] _wexecve:(*) = wexecve;
[alias(*)][attribute(*)] _wexecvpe:(*) = wexecvpe;
[alias(*)][attribute(*)] _wexecl:(*) = wexecl;
[alias(*)][attribute(*)] _wexeclp:(*) = wexeclp;
[alias(*)][attribute(*)] _wexecle:(*) = wexecle;
[alias(*)][attribute(*)] _wexeclpe:(*) = wexeclpe;

%[default_impl_section({.text.crt.wchar.fs.exec.spawn|.text.crt.dos.wchar.fs.exec.spawn})]
[alias(*)][attribute(*)][argument_names(mode, path, ___argv)]          _wspawnv:(int mode, wchar_t const *__restrict path, @__TWARGV@) -> intptr_t = wspawnv;
[alias(*)][attribute(*)][argument_names(mode, path, ___argv)]          _wspawnvp:(int mode, wchar_t const *__restrict path, @__TWARGV@) -> intptr_t = wspawnvp;
[alias(*)][attribute(*)][argument_names(mode, path, ___argv, ___envp)] _wspawnve:(int mode, wchar_t const *__restrict path, @__TWARGV@, @__TWENVP@) -> intptr_t = wspawnve;
[alias(*)][attribute(*)][argument_names(mode, path, ___argv, ___envp)] _wspawnvpe:(int mode, wchar_t const *__restrict path, @__TWARGV@, @__TWENVP@) -> intptr_t = wspawnvpe;
[alias(*)][attribute(*)][allow_macros] _wspawnl:(int mode, wchar_t const *__restrict path, wchar_t const *args, ... /*, (wchar_t *)NULL*/) -> intptr_t = wspawnl;
[alias(*)][attribute(*)][allow_macros] _wspawnlp:(int mode, wchar_t const *__restrict path, wchar_t const *args, ... /*, (wchar_t *)NULL*/) -> intptr_t = wspawnlp;
[alias(*)][attribute(*)][allow_macros] _wspawnle:(int mode, wchar_t const *__restrict path, wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) -> intptr_t = wspawnle;
[alias(*)][attribute(*)][allow_macros] _wspawnlpe:(int mode, wchar_t const *__restrict path, wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) -> intptr_t = wspawnlpe;
%#endif /* !_WPROCESS_DEFINED */

%
%#ifndef _CRT_WSYSTEM_DEFINED
%#define _CRT_WSYSTEM_DEFINED 1
[guard][alias(*)][attribute(*)] _wsystem:(*) = wsystem;
%#endif /* !_CRT_WSYSTEM_DEFINED */



%
%#endif /* __CC__ */
%#endif /* __USE_DOS */

%
%
%#if defined(__USE_DOS) || defined(__USE_KOS)

%[insert:extern(getpid)]
%[insert:extern(execv)]
%[insert:extern(execvp)]
%[insert:extern(execve)]
%[insert:extern(execvpe)]
%[insert:extern(execl)]
%[insert:extern(execlp)]
%[insert:extern(execle)]
%[insert:extern(execlpe)]

%[default_impl_section(.text.crt.dos.fs.exec.spawn)]
[cp][alias(_cwait)] cwait:(int *tstat, $pid_t pid, int action) -> $pid_t;

%[default_impl_section(.text.crt.fs.exec.spawn)]
[cp][guard][argument_names(mode, path, ___argv)][alias(_spawnv)]
spawnv:(int mode, [nonnull] char const *__restrict path, [nonnull] @__TARGV@) -> $pid_t;
[cp][guard][argument_names(mode, file, ___argv)][alias(_spawnvp)]
spawnvp:(int mode, [nonnull] char const *__restrict file, [nonnull] @__TARGV@) -> $pid_t;
[cp][guard][argument_names(mode, path, ___argv, ___envp)][alias(_spawnve)]
spawnve:(int mode, [nonnull] char const *__restrict path, [nonnull] @__TARGV@, [nonnull] @__TENVP@) -> $pid_t;
[cp][guard][argument_names(mode, file, ___argv, ___envp)][alias(_spawnvpe)]
spawnvpe:(int mode, [nonnull] char const *__restrict file, [nonnull] @__TARGV@, [nonnull] @__TENVP@) -> $pid_t;

[cp][guard][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(spawnv)][ATTR_SENTINEL][alias(_spawnl)][allow_macros]
spawnl:(int mode, [nonnull] char const *__restrict path, char const *args, ... /*, (char *)NULL*/) -> $pid_t {
	__REDIRECT_SPAWNL(char, spawnv, mode, path, args)
}

[cp][guard][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(spawnvp)][ATTR_SENTINEL][alias(_spawnlp)][allow_macros]
spawnlp:(int mode, [nonnull] char const *__restrict file, char const *args, ... /*, (char *)NULL*/) -> $pid_t {
	__REDIRECT_SPAWNLP(char, spawnvp, mode, file, args)
}

[cp][guard][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(spawnve)][ATTR_SENTINEL_O(1)][alias(_spawnle)][allow_macros]
spawnle:(int mode, [nonnull] char const *__restrict path, char const *args, ... /*, (char *)NULL, char **environ*/) -> $pid_t {
	__REDIRECT_SPAWNLE(char, spawnve, mode, path, args)
}

[cp][guard][dependency_include(<parts/redirect-exec.h>)]
[requires_dependency(spawnvpe)][ATTR_SENTINEL_O(1)][alias(_spawnlpe)][allow_macros]
spawnlpe:(int mode, [nonnull] char const *__restrict file, char const *args, ... /*, (char *)NULL, char **environ*/) -> $pid_t {
	__REDIRECT_SPAWNLPE(char, spawnvpe, mode, file, args)
}

%#endif /* __USE_DOS || __USE_KOS */

//TODO:#ifdef __USE_KOS
//TODO:#ifndef _PARTS_KOS2_PROCESS_H
//TODO:#include <parts/kos2/process.h>
//TODO:#endif
//TODO:#ifdef _WCHAR_H
//TODO:#ifndef _PARTS_KOS2_WPROCESS_H
//TODO:#include <parts/kos2/wprocess.h>
//TODO:#endif
//TODO:#endif
//TODO:#endif /* __USE_KOS */
//TODO:
//TODO:#ifdef __USE_KOS3
//TODO:#ifndef _PARTS_KOS3_PROCESS_H
//TODO:#include <parts/kos3/process.h>
//TODO:#endif
//TODO:#ifdef _WCHAR_H
//TODO:#ifndef _PARTS_KOS3_WPROCESS_H
//TODO:#include <parts/kos3/wprocess.h>
//TODO:#endif
//TODO:#endif
//TODO:#endif /* __USE_KOS3 */


%{

__SYSDECL_END

#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_PROCESS_H)
#include <parts/wchar/process.h>
#endif /* _WCHAR_H && !_PARTS_WCHAR_PROCESS_H */
#endif /* __USE_KOS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_PROCESS_H)
#include <parts/uchar/process.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_PROCESS_H */
#endif /* __USE_UTF */

}