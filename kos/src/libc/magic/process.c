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


#ifndef __TARGV
#ifdef __USE_DOS
#define __TARGV  char const *const *___argv
#define __TENVP  char const *const *___envp
#else /* __USE_DOS */
#define __TARGV  char *const ___argv[__restrict_arr]
#define __TENVP  char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__TARGV */

/* DOS */
}
%#ifdef __USE_DOS
%{
#define _P_WAIT          P_WAIT
#define _P_NOWAIT        P_NOWAIT
#define _P_OVERLAY       P_OVERLAY
#define _P_NOWAITO       P_NOWAITO
#define _P_DETACH        P_DETACH
#define _OLD_P_OVERLAY   P_OVERLAY
#define _WAIT_CHILD      WAIT_CHILD
#define _WAIT_GRANDCHILD WAIT_GRANDCHILD
#define OLD_P_OVERLAY    _OLD_P_OVERLAY


}
%#ifdef __CC__
%{

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

uintptr_t _beginthread(__dos_beginthread_entry_t entry, $u32 stacksz, void *arg);
uintptr_t _beginthreadex(void *sec, $u32 stacksz, __dos_beginthreadex_entry_t entry, void *arg, $u32 flags, $u32 *threadaddr);

[[userimpl, requires($has_function(_endthreadex))]]
void _endthread() {
	_endthreadex(0);
}

void _endthreadex($u32 exitcode);

%[default_impl_section(".text.crt.sched.process")]

%
%#ifndef _CRT_TERMINATE_DEFINED
%#define _CRT_TERMINATE_DEFINED 1
%[insert:extern(exit)]
%[insert:extern(abort)]
_exit(*) = _Exit;
%#endif /* !_CRT_TERMINATE_DEFINED */

%[default_impl_section(".text.crt.dos.sched.process")]
[[throws]] _cexit:();
[[throws]] _c_exit:() {
}

[[guard, ATTR_WUNUSED]] _getpid:() -> $pid_t = getpid;

%[default_impl_section(.text.crt.dos.fs.exec.exec)]
_execv(*) = execv;
_execvp(*) = execvp;
_execve(*) = execve;
_execvpe(*) = execvpe;
_execl(*) = execl;
_execlp(*) = execlp;
_execle(*) = execle;
_execlpe(*) = execlpe;

%[default_impl_section(.text.crt.dos.fs.exec.spawn)]
_cwait(*) = cwait;
[[[argument_names(mode, path, ___argv)]]]          _spawnv(int mode, char const *__restrict path, __TARGV) -> intptr_t = spawnv;
[[[argument_names(mode, file, ___argv)]]]          _spawnvp(int mode, char const *__restrict file, __TARGV) -> intptr_t = spawnvp;
[[[argument_names(mode, path, ___argv, ___envp)]]] _spawnve(int mode, char const *__restrict path, __TARGV, __TENVP) -> intptr_t = spawnve;
[[[argument_names(mode, file, ___argv, ___envp)]]] _spawnvpe(int mode, char const *__restrict file, __TARGV, __TENVP) -> intptr_t = spawnvpe;
[[allow_macros]] _spawnl(int mode, char const *__restrict path, char const *args, ... /*, (char *)NULL*/) -> intptr_t = spawnl;
[[allow_macros]] _spawnlp(int mode, char const *__restrict file, char const *args, ... /*, (char *)NULL*/) -> intptr_t = spawnlp;
[[allow_macros]] _spawnle(int mode, char const *__restrict path, char const *args, ... /*, (char *)NULL, (char **)environ*/) -> intptr_t = spawnle;
[[allow_macros]] _spawnlpe(int mode, char const *__restrict file, char const *args, ... /*, (char *)NULL, (char **)environ*/) -> intptr_t = spawnlpe;

%[default_impl_section(.text.crt.fs.exec.system)]
%[insert:extern(system)]

%
%
%
%[define_c_language_keyword(__KOS_FIXED_CONST)]

%[default_impl_section(.text.crt.dos.fs.dlfcn)]
[[throws]] _loaddll:(char __KOS_FIXED_CONST *file) -> intptr_t;

[[throws]] _unloaddll:(intptr_t hnd) -> int;

%
%typedef int (__LIBCCALL *__procfun)(void);
[[throws]] _getdllprocaddr:(intptr_t hnd, char __KOS_FIXED_CONST *symname, intptr_t ord) -> __procfun;


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
#define __TWARGV wchar_t const *const *__restrict ___argv
#define __TWENVP wchar_t const *const *__restrict ___envp
#else /* __USE_DOS */
#define __TWARGV wchar_t *const ___argv[__restrict_arr]
#define __TWENVP wchar_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__TWARGV */

}

%
%#ifndef _WPROCESS_DEFINED
%#define _WPROCESS_DEFINED 1
%[default_impl_section("{.text.crt.wchar.fs.exec.exec|.text.crt.dos.wchar.fs.exec.exec}")]
_wexecv(*) = wexecv;
_wexecvp(*) = wexecvp;
_wexecve(*) = wexecve;
_wexecvpe(*) = wexecvpe;
_wexecl(*) = wexecl;
_wexeclp(*) = wexeclp;
_wexecle(*) = wexecle;
_wexeclpe(*) = wexeclpe;

%[default_impl_section({.text.crt.wchar.fs.exec.spawn|.text.crt.dos.wchar.fs.exec.spawn})]
[[[argument_names(mode, path, ___argv)]]]          _wspawnv:(int mode, wchar_t const *__restrict path, __TWARGV) -> intptr_t = wspawnv;
[[[argument_names(mode, path, ___argv)]]]          _wspawnvp:(int mode, wchar_t const *__restrict path, __TWARGV) -> intptr_t = wspawnvp;
[[[argument_names(mode, path, ___argv, ___envp)]]] _wspawnve:(int mode, wchar_t const *__restrict path, __TWARGV, __TWENVP) -> intptr_t = wspawnve;
[[[argument_names(mode, path, ___argv, ___envp)]]] _wspawnvpe:(int mode, wchar_t const *__restrict path, __TWARGV, __TWENVP) -> intptr_t = wspawnvpe;
[[allow_macros]] _wspawnl:(int mode, wchar_t const *__restrict path, wchar_t const *args, ... /*, (wchar_t *)NULL*/) -> intptr_t = wspawnl;
[[allow_macros]] _wspawnlp:(int mode, wchar_t const *__restrict path, wchar_t const *args, ... /*, (wchar_t *)NULL*/) -> intptr_t = wspawnlp;
[[allow_macros]] _wspawnle:(int mode, wchar_t const *__restrict path, wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) -> intptr_t = wspawnle;
[[allow_macros]] _wspawnlpe:(int mode, wchar_t const *__restrict path, wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) -> intptr_t = wspawnlpe;
%#endif /* !_WPROCESS_DEFINED */

%
%#ifndef _CRT_WSYSTEM_DEFINED
%#define _CRT_WSYSTEM_DEFINED 1
[[guard]] _wsystem(*) = wsystem;
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

%[default_impl_section(".text.crt.dos.fs.exec.spawn")]
[[cp]][alias(_cwait)] cwait:(int *tstat, $pid_t pid, int action) -> $pid_t;

%[default_impl_section(.text.crt.fs.exec.spawn)]
[[cp, guard, argument_names(mode, path, ___argv), export_alias("_spawnv")]]
$pid_t spawnv(int mode, [[nonnull]] char const *__restrict path, [[nonnull]] __TARGV);
[[cp, guard, argument_names(mode, file, ___argv), export_alias("_spawnvp")]]
$pid_t spawnvp(int mode, [[nonnull]] char const *__restrict file, [[nonnull]] __TARGV);
[[cp, guard, argument_names(mode, path, ___argv, ___envp), export_alias("_spawnve")]]
$pid_t spawnve(int mode, [[nonnull]] char const *__restrict path, [[nonnull]] __TARGV, [[nonnull]] __TENVP);
[[cp, guard, argument_names(mode, file, ___argv, ___envp), export_alias("_spawnvpe")]]
$pid_t spawnvpe(int mode, [[nonnull]] char const *__restrict file, [[nonnull]] __TARGV, [[nonnull]] __TENVP);

[[cp, guard, allow_macros, ATTR_SENTINEL, impl_include("<parts/redirect-exec.h>")]]
[[userimpl, requires_dependent_function("spawnv"), export_alias("_spawnl")]]
spawnl:(int mode, [[nonnull]] char const *__restrict path, char const *args, ... /*, (char *)NULL*/) -> $pid_t {
	__REDIRECT_SPAWNL(char, spawnv, mode, path, args)
}

[[cp, guard, allow_macros, ATTR_SENTINEL, impl_include("<parts/redirect-exec.h>")]]
[[userimpl, requires_dependent_function("spawnvp"), export_alias("_spawnlp")]]
spawnlp:(int mode, [[nonnull]] char const *__restrict file, char const *args, ... /*, (char *)NULL*/) -> $pid_t {
	__REDIRECT_SPAWNLP(char, spawnvp, mode, file, args)
}

[[cp, guard, allow_macros, ATTR_SENTINEL_O(1), impl_include("<parts/redirect-exec.h>")]]
[[userimpl, requires_dependent_function("spawnve"), export_alias("_spawnle")]]
spawnle:(int mode, [[nonnull]] char const *__restrict path, char const *args, ... /*, (char *)NULL, char **environ*/) -> $pid_t {
	__REDIRECT_SPAWNLE(char, spawnve, mode, path, args)
}

[[cp, guard, allow_macros, ATTR_SENTINEL_O(1), impl_include("<parts/redirect-exec.h>")]]
[[userimpl, requires_dependent_function("spawnvpe"), export_alias("_spawnlpe")]]
spawnlpe:(int mode, [[nonnull]] char const *__restrict file, char const *args, ... /*, (char *)NULL, char **environ*/) -> $pid_t {
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