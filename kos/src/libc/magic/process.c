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
#define P_WAIT    0
#define P_NOWAIT  1
#define P_OVERLAY 2
#define P_NOWAITO 3
#define P_DETACH  4

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


%[default_impl_section(".text.crt.dos.sched.thread")]
%typedef void (__LIBCCALL *__dos_beginthread_entry_t)(void *__arg);
%typedef __UINT32_TYPE__ (__ATTR_STDCALL *__dos_beginthreadex_entry_t)(void *__arg);
%

%[define_replacement(__dos_beginthread_entry_t = __dos_beginthread_entry_t)]
%[define_replacement(__dos_beginthreadex_entry_t = __dos_beginthreadex_entry_t)]

uintptr_t _beginthread(__dos_beginthread_entry_t entry, $u32 stacksz, void *arg);
uintptr_t _beginthreadex(void *sec, $u32 stacksz, __dos_beginthreadex_entry_t entry,
                         void *arg, $u32 flags, $u32 *threadaddr);

[[requires($has_function(_endthreadex))]]
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
%[insert:guarded_function(_exit = _Exit)]
%#endif /* !_CRT_TERMINATE_DEFINED */

%[default_impl_section(".text.crt.dos.sched.process")]
[[throws]] void _cexit();
[[throws]] void _c_exit() {
}

%[insert:function(_getpid = getpid)]

%[default_impl_section(".text.crt.dos.fs.exec.exec")]
%[insert:function(_execv = execv)]
%[insert:function(_execvp = execvp)]
%[insert:function(_execve = execve)]
%[insert:function(_execvpe = execvpe)]
%[insert:function(_execl = execl)]
%[insert:function(_execlp = execlp)]
%[insert:function(_execle = execle)]
%[insert:function(_execlpe = execlpe)]

%[default_impl_section(".text.crt.dos.fs.exec.spawn")]
%[insert:function(_cwait = cwait)]

[[argument_names(mode, path, ___argv)]]
intptr_t _spawnv(int mode, [[nonnull]] char const *__restrict path,
                 __TARGV) = spawnv;

[[argument_names(mode, file, ___argv)]]
intptr_t _spawnvp(int mode, [[nonnull]] char const *__restrict file,
                  __TARGV) = spawnvp;

[[argument_names(mode, path, ___argv, ___envp)]]
intptr_t _spawnve(int mode, [[nonnull]] char const *__restrict path,
                  __TARGV, __TENVP) = spawnve;

[[argument_names(mode, file, ___argv, ___envp)]]
intptr_t _spawnvpe(int mode, [[nonnull]] char const *__restrict file,
                   __TARGV, __TENVP) = spawnvpe;

[[allow_macros]]
intptr_t _spawnl(int mode, [[nonnull]] char const *__restrict path,
                 char const *args, ... /*, (char *)NULL*/) = spawnl;
[[allow_macros]]
intptr_t _spawnlp(int mode, [[nonnull]] char const *__restrict file,
                  char const *args, ... /*, (char *)NULL*/) = spawnlp;
[[allow_macros]]
intptr_t _spawnle(int mode, [[nonnull]] char const *__restrict path,
                  char const *args, ... /*, (char *)NULL, (char **)environ*/) = spawnle;
[[allow_macros]]
intptr_t _spawnlpe(int mode, [[nonnull]] char const *__restrict file,
                   char const *args, ... /*, (char *)NULL, (char **)environ*/) = spawnlpe;

%[default_impl_section(".text.crt.fs.exec.system")]
%[insert:extern(system)]

%
%
%
%[define_c_language_keyword(__KOS_FIXED_CONST)]

%[default_impl_section(".text.crt.dos.fs.dlfcn")]
[[throws, decl_include("<features.h>")]]
intptr_t _loaddll(char __KOS_FIXED_CONST *file);

[[throws]]
int _unloaddll(intptr_t hnd);

%
%typedef int (__LIBCCALL *__procfun)(void);
%[define_replacement(__procfun = __procfun)]

[[throws, decl_include("<features.h>")]]
__procfun _getdllprocaddr(intptr_t hnd,
                          char __KOS_FIXED_CONST *symname,
                          intptr_t ord);


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
%[insert:function(_wexecv = wexecv)]
%[insert:function(_wexecvp = wexecvp)]
%[insert:function(_wexecve = wexecve)]
%[insert:function(_wexecvpe = wexecvpe)]
%[insert:function(_wexecl = wexecl)]
%[insert:function(_wexeclp = wexeclp)]
%[insert:function(_wexecle = wexecle)]
%[insert:function(_wexeclpe = wexeclpe)]

%[default_impl_section("{.text.crt.wchar.fs.exec.spawn|.text.crt.dos.wchar.fs.exec.spawn}")]
[[argument_names(mode, path, ___argv)]]
intptr_t _wspawnv(int mode, [[nonnull]] wchar_t const *__restrict path,
                  __TWARGV) = wspawnv;

[[argument_names(mode, path, ___argv)]]
intptr_t _wspawnvp(int mode, [[nonnull]] wchar_t const *__restrict path,
                   __TWARGV) = wspawnvp;

[[argument_names(mode, path, ___argv, ___envp)]]
intptr_t _wspawnve(int mode, [[nonnull]] wchar_t const *__restrict path,
                   __TWARGV, __TWENVP) = wspawnve;

[[argument_names(mode, path, ___argv, ___envp)]]
intptr_t _wspawnvpe(int mode, [[nonnull]] wchar_t const *__restrict path,
                    __TWARGV, __TWENVP) = wspawnvpe;

[[allow_macros]]
intptr_t _wspawnl(int mode, [[nonnull]] wchar_t const *__restrict path,
                  wchar_t const *args, ... /*, (wchar_t *)NULL*/) = wspawnl;

[[allow_macros]]
intptr_t _wspawnlp(int mode, [[nonnull]] wchar_t const *__restrict path,
                   wchar_t const *args, ... /*, (wchar_t *)NULL*/) = wspawnlp;

[[allow_macros]]
intptr_t _wspawnle(int mode, [[nonnull]] wchar_t const *__restrict path,
                   wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) = wspawnle;

[[allow_macros]]
intptr_t _wspawnlpe(int mode, [[nonnull]] wchar_t const *__restrict path,
                    wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) = wspawnlpe;
%#endif /* !_WPROCESS_DEFINED */

%
%[insert:function(_wsystem = wsystem, guardName: "_CRT_WSYSTEM_DEFINED")]



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
[[cp, export_alias("_cwait")]]
$pid_t cwait(int *tstat, $pid_t pid, int action);

%[default_impl_section(".text.crt.fs.exec.spawn")]

[[cp, guard, argument_names(mode, path, ___argv), export_alias("_spawnv")]]
$pid_t spawnv(int mode, [[nonnull]] char const *__restrict path, [[nonnull]] __TARGV);

[[cp, guard, argument_names(mode, file, ___argv), export_alias("_spawnvp")]]
$pid_t spawnvp(int mode, [[nonnull]] char const *__restrict file, [[nonnull]] __TARGV);

[[cp, guard, argument_names(mode, path, ___argv, ___envp), export_alias("_spawnve")]]
$pid_t spawnve(int mode, [[nonnull]] char const *__restrict path, [[nonnull]] __TARGV, [[nonnull]] __TENVP);

[[cp, guard, argument_names(mode, file, ___argv, ___envp), export_alias("_spawnvpe")]]
$pid_t spawnvpe(int mode, [[nonnull]] char const *__restrict file, [[nonnull]] __TARGV, [[nonnull]] __TENVP);

[[cp, guard, allow_macros, ATTR_SENTINEL, impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function("spawnv"), export_alias("_spawnl")]]
$pid_t spawnl(int mode, [[nonnull]] char const *__restrict path,
              char const *args, ... /*, (char *)NULL*/) {
	__REDIRECT_SPAWNL(char, spawnv, mode, path, args)
}

[[cp, guard, allow_macros, ATTR_SENTINEL, impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function("spawnvp"), export_alias("_spawnlp")]]
$pid_t spawnlp(int mode, [[nonnull]] char const *__restrict file,
               char const *args, ... /*, (char *)NULL*/) {
	__REDIRECT_SPAWNL(char, spawnvp, mode, file, args)
}

[[cp, guard, allow_macros, ATTR_SENTINEL_O(1), impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function("spawnve"), export_alias("_spawnle")]]
$pid_t spawnle(int mode, [[nonnull]] char const *__restrict path,
               char const *args, ... /*, (char *)NULL, char **environ*/) {
	__REDIRECT_SPAWNLE(char, spawnve, mode, path, args)
}

[[cp, guard, allow_macros, ATTR_SENTINEL_O(1), impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function("spawnvpe"), export_alias("_spawnlpe")]]
$pid_t spawnlpe(int mode, [[nonnull]] char const *__restrict file,
                char const *args, ... /*, (char *)NULL, char **environ*/) {
	__REDIRECT_SPAWNLE(char, spawnvpe, mode, file, args)
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