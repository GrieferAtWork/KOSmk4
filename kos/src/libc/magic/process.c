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
%(c_prefix){
/* (#) Portability: Cygwin (/winsup/cygwin/include/process.h) */
/* (#) Portability: DJGPP  (/include/process.h) */
/* (#) Portability: MSVC   (/include/process.h) */
/* (#) Portability: MinGW  (/mingw-w64-headers/crt/process.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(pid_t = __pid_t)]

%[define_type_class(__TARGV = "TP")]
%[define_type_class(__TENVP = "TP")]

%(auto_source)#include "../libc/dl.h"
%(auto_source)#include "../libc/globals.h"

%{
#include <features.h>

#include <asm/crt/process.h>
#include <bits/types.h>
#include <kos/anno.h>

__SYSDECL_BEGIN

/* `MODE' argument values for spawn() functions. */
#ifdef __P_WAIT
#define P_WAIT    __P_WAIT    /* Wait for the process to terminate, and return its exit status */
#endif /* __P_WAIT */
#ifdef __P_NOWAIT
#define P_NOWAIT  __P_NOWAIT  /* Spawn the process asynchronously, and return its PID */
#endif /* __P_NOWAIT */
#ifdef __P_OVERLAY
#define P_OVERLAY __P_OVERLAY /* Don't spawn, but rather try to exec() the new program */
#endif /* __P_OVERLAY */
#ifdef __P_NOWAITO
#define P_NOWAITO __P_NOWAITO /* Same as `P_NOWAIT' */
#endif /* __P_NOWAITO */
#ifdef __P_DETACH
#define P_DETACH  __P_DETACH  /* Create the new process as detached and return `0' */
#endif /* __P_DETACH */

/* `ACTION' argument values for cwait() functions. */
#ifdef __WAIT_CHILD
#define WAIT_CHILD      __WAIT_CHILD      /* Ignored */
#endif /* __WAIT_CHILD */
#ifdef __WAIT_GRANDCHILD
#define WAIT_GRANDCHILD __WAIT_GRANDCHILD /* Ignored */
#endif /* __WAIT_GRANDCHILD */


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


%[default:section(".text.crt.dos.sched.thread")]
%{
#ifndef ____dos_beginthread_entry_t_defined
#define ____dos_beginthread_entry_t_defined 1
typedef void (__LIBDCALL *__dos_beginthread_entry_t)(void *__arg);
#endif /* !____dos_beginthread_entry_t_defined */
#ifndef ____dos_beginthreadex_entry_t_defined
#define ____dos_beginthreadex_entry_t_defined 1
#ifdef __NO_ATTR_STDCALL
typedef __UINT32_TYPE__ (__LIBDCALL *__dos_beginthreadex_entry_t)(void *__arg);
#else /* __NO_ATTR_STDCALL */
typedef __UINT32_TYPE__ (__ATTR_STDCALL *__dos_beginthreadex_entry_t)(void *__arg);
#endif /* !__NO_ATTR_STDCALL */
#endif /* !____dos_beginthreadex_entry_t_defined */
}
%

%[define(DEFINE_DOS_BEGINTHREAD_ENTRY_T =
@@pp_ifndef ____dos_beginthread_entry_t_defined@@
#define ____dos_beginthread_entry_t_defined 1
typedef void (__LIBDCALL *__dos_beginthread_entry_t)(void *__arg);
@@pp_endif@@
)]

%[define(DEFINE_DOS_BEGINTHREADEX_ENTRY_T =
@@pp_ifndef ____dos_beginthreadex_entry_t_defined@@
#define ____dos_beginthreadex_entry_t_defined 1
#ifdef __NO_ATTR_STDCALL
typedef __UINT32_TYPE__ (__LIBDCALL *__dos_beginthreadex_entry_t)(void *__arg);
#else /* __NO_ATTR_STDCALL */
typedef __UINT32_TYPE__ (__ATTR_STDCALL *__dos_beginthreadex_entry_t)(void *__arg);
#endif /* !__NO_ATTR_STDCALL */
@@pp_endif@@
)]


%[define_type_class(__dos_beginthread_entry_t = "TP")]
%[define_type_class(__dos_beginthreadex_entry_t = "TP")]

%[define_replacement(__dos_beginthread_entry_t = __dos_beginthread_entry_t)]
%[define_replacement(__dos_beginthreadex_entry_t = __dos_beginthreadex_entry_t)]

[[decl_include("<hybrid/typecore.h>")]]
[[decl_prefix(DEFINE_DOS_BEGINTHREAD_ENTRY_T)]]
uintptr_t _beginthread(__dos_beginthread_entry_t entry, $u32 stacksz, void *arg);

[[decl_include("<hybrid/typecore.h>")]]
[[decl_prefix(DEFINE_DOS_BEGINTHREADEX_ENTRY_T)]]
uintptr_t _beginthreadex(void *sec, $u32 stacksz, __dos_beginthreadex_entry_t entry,
                         void *arg, $u32 flags, $u32 *threadaddr);

[[requires($has_function(_endthreadex))]]
void _endthread() {
	_endthreadex(0);
}

[[decl_include("<hybrid/typecore.h>")]]
void _endthreadex($u32 exitcode);

%[default:section(".text.crt{|.dos}.sched.process")]

%
%#ifndef _CRT_TERMINATE_DEFINED
%#define _CRT_TERMINATE_DEFINED 1
%[insert:extern(exit)]
%[insert:extern(abort)]
%[insert:guarded_function(_exit = _Exit)]
%#endif /* !_CRT_TERMINATE_DEFINED */

%[default:section(".text.crt.dos.sched.process")]
[[throws]] void _cexit();
[[throws]] void _c_exit() {
}

%[insert:function(_getpid = getpid)]

%[default:section(".text.crt.dos.fs.exec.exec")]
%[insert:function(_execv = execv)]
%[insert:function(_execvp = execvp)]
%[insert:function(_execve = execve)]
%[insert:function(_execvpe = execvpe)]
%[insert:function(_execl = execl)]
%[insert:function(_execlp = execlp)]
%[insert:function(_execle = execle)]
%[insert:function(_execlpe = execlpe)]

%[default:section(".text.crt.dos.fs.exec.spawn")]
%[insert:function(_cwait = cwait)]

[[argument_names(mode, path, ___argv)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
intptr_t _spawnv(__STDC_INT_AS_UINT_T mode,
                 [[nonnull]] char const *__restrict path,
                 __TARGV) = spawnv;

[[argument_names(mode, file, ___argv)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
intptr_t _spawnvp(__STDC_INT_AS_UINT_T mode,
                  [[nonnull]] char const *__restrict file,
                  __TARGV) = spawnvp;

[[argument_names(mode, path, ___argv, ___envp)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
intptr_t _spawnve(__STDC_INT_AS_UINT_T mode,
                  [[nonnull]] char const *__restrict path,
                  __TARGV, __TENVP) = spawnve;

[[argument_names(mode, file, ___argv, ___envp)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
intptr_t _spawnvpe(__STDC_INT_AS_UINT_T mode,
                   [[nonnull]] char const *__restrict file,
                   __TARGV, __TENVP) = spawnvpe;

[[decl_include("<features.h>", "<bits/types.h>")]]
intptr_t _spawnl(__STDC_INT_AS_UINT_T mode,
                 [[nonnull]] char const *__restrict path,
                 char const *args, ... /*, (char *)NULL*/) = spawnl;

[[decl_include("<features.h>", "<bits/types.h>")]]
intptr_t _spawnlp(__STDC_INT_AS_UINT_T mode,
                  [[nonnull]] char const *__restrict file,
                  char const *args, ... /*, (char *)NULL*/) = spawnlp;

[[decl_include("<features.h>", "<bits/types.h>")]]
intptr_t _spawnle(__STDC_INT_AS_UINT_T mode,
                  [[nonnull]] char const *__restrict path,
                  char const *args, ... /*, (char *)NULL, (char **)environ*/) = spawnle;

[[decl_include("<features.h>", "<bits/types.h>")]]
intptr_t _spawnlpe(__STDC_INT_AS_UINT_T mode,
                   [[nonnull]] char const *__restrict file,
                   char const *args, ... /*, (char *)NULL, (char **)environ*/) = spawnlpe;

%[default:section(".text.crt{|.dos}.fs.exec.system")]
%[insert:extern(system)]

%
%
%
%[define_c_language_keyword(__KOS_FIXED_CONST)]

%[default:section(".text.crt.dos.fs.dlfcn")]
[[throws, decl_include("<features.h>", "<bits/types.h>")]]
[[requires_include("<libdl/asm/dlfcn.h>")]]
[[requires(defined(__CRT_HAVE_dlopen))]]
[[impl_include("<dlfcn.h>")]]
intptr_t _loaddll(char __KOS_FIXED_CONST *file) {
@@pp_if defined(@RTLD_LOCAL@)@@
	return (intptr_t)(uintptr_t)@dlopen@(file, @RTLD_LOCAL@);
@@pp_elif defined(@RTLD_GLOBAL@)@@
	return (intptr_t)(uintptr_t)@dlopen@(file, @RTLD_GLOBAL@);
@@pp_else@@
	return (intptr_t)(uintptr_t)@dlopen@(file, 0);
@@pp_endif@@
}

[[throws, decl_include("<bits/types.h>")]]
[[impl_include("<dlfcn.h>")]]
int _unloaddll(intptr_t hnd) {
@@pp_ifdef __CRT_HAVE_dlclose@@
	return @dlclose@((void *)(uintptr_t)hnd);
@@pp_else@@
	return 0;
@@pp_endif@@
}

%
%{
#ifndef ____procfun_defined
#define ____procfun_defined 1
typedef int (*__procfun)(void);
#endif /* !____procfun_defined */
}
%[define_replacement(__procfun = __procfun)]
%[define_type_class(__procfun = "TP")]
%[define(DEFINE_PROCFUN =
#ifndef ____procfun_defined
#define ____procfun_defined 1
typedef int (*__procfun)(void);
#endif /* !____procfun_defined */
)]

[[throws, decl_include("<features.h>", "<bits/types.h>")]]
[[decl_prefix(DEFINE_PROCFUN)]]
[[requires_include("<libdl/asm/dlfcn.h>")]]
[[requires(defined(__CRT_HAVE_dlsym))]]
[[impl_include("<dlfcn.h>")]]
__procfun _getdllprocaddr(intptr_t hnd,
                          char __KOS_FIXED_CONST *symname,
                          intptr_t ord) {
	(void)ord;
	return (__procfun)@dlsym@((void *)(uintptr_t)hnd, symname);
}


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

%[define_type_class(__TWARGV = "TP")]
%[define_type_class(__TWENVP = "TP")]

%
%#ifndef _WPROCESS_DEFINED
%#define _WPROCESS_DEFINED 1
%[default:section(".text.crt{|.dos}.wchar.fs.exec.exec")]
%[insert:function(_wexecv = wexecv)]
%[insert:function(_wexecvp = wexecvp)]
%[insert:function(_wexecve = wexecve)]
%[insert:function(_wexecvpe = wexecvpe)]
%[insert:function(_wexecl = wexecl)]
%[insert:function(_wexeclp = wexeclp)]
%[insert:function(_wexecle = wexecle)]
%[insert:function(_wexeclpe = wexeclpe)]

%[default:section(".text.crt{|.dos}.wchar.fs.exec.spawn")]
[[argument_names(mode, path, ___argv)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
intptr_t _wspawnv(__STDC_INT_AS_UINT_T mode,
                  [[nonnull]] wchar_t const *__restrict path,
                  __TWARGV) = wspawnv;

[[argument_names(mode, path, ___argv)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
intptr_t _wspawnvp(__STDC_INT_AS_UINT_T mode,
                   [[nonnull]] wchar_t const *__restrict path,
                   __TWARGV) = wspawnvp;

[[argument_names(mode, path, ___argv, ___envp)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
intptr_t _wspawnve(__STDC_INT_AS_UINT_T mode,
                   [[nonnull]] wchar_t const *__restrict path,
                   __TWARGV, __TWENVP) = wspawnve;

[[argument_names(mode, path, ___argv, ___envp)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
intptr_t _wspawnvpe(__STDC_INT_AS_UINT_T mode,
                    [[nonnull]] wchar_t const *__restrict path,
                    __TWARGV, __TWENVP) = wspawnvpe;

[[decl_include("<features.h>", "<bits/types.h>")]]
intptr_t _wspawnl(__STDC_INT_AS_UINT_T mode, [[nonnull]] wchar_t const *__restrict path,
                  wchar_t const *args, ... /*, (wchar_t *)NULL*/) = wspawnl;

[[decl_include("<features.h>", "<bits/types.h>")]]
intptr_t _wspawnlp(__STDC_INT_AS_UINT_T mode, [[nonnull]] wchar_t const *__restrict path,
                   wchar_t const *args, ... /*, (wchar_t *)NULL*/) = wspawnlp;

[[decl_include("<features.h>", "<bits/types.h>")]]
intptr_t _wspawnle(__STDC_INT_AS_UINT_T mode, [[nonnull]] wchar_t const *__restrict path,
                   wchar_t const *args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) = wspawnle;

[[decl_include("<features.h>", "<bits/types.h>")]]
intptr_t _wspawnlpe(__STDC_INT_AS_UINT_T mode, [[nonnull]] wchar_t const *__restrict path,
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

%[default:section(".text.crt.dos.fs.exec.spawn")]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[cp, export_alias("_cwait"), requires_function(waitpid)]]
$pid_t cwait(int *tstat, $pid_t pid, __STDC_INT_AS_UINT_T action) {
	/* This one's pretty simple, because it's literally just a waitpid() system call...
	 * (It even returns the same  thing, that being the  PID of the joined  process...) */
	/* NOTE: Apparently, the `action' argument is completely ignored... */
	(void)action;
	return waitpid(pid, tstat, WEXITED);
}

%[default:section(".text.crt{|.dos}.fs.exec.spawn")]

[[cp, guard, argument_names(mode, path, ___argv), export_alias("_spawnv")]]
[[decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_TARGV)]]
[[requires_include("<libc/local/environ.h>"), requires($has_function(spawnve) && defined(__LOCAL_environ))]]
[[impl_include("<libc/local/environ.h>")]]
$pid_t spawnv(__STDC_INT_AS_UINT_T mode, [[nonnull]] char const *__restrict path, [[nonnull]] __TARGV) {
	return spawnve(mode, path, ___argv, __LOCAL_environ);
}

[[cp, guard, argument_names(mode, file, ___argv)]]
[[export_alias("_spawnvp")]]
[[decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_TARGV)]]
[[requires_include("<libc/local/environ.h>")]]
[[requires($has_function(spawnvpe) && defined(__LOCAL_environ))]]
[[impl_include("<libc/local/environ.h>")]]
$pid_t spawnvp(__STDC_INT_AS_UINT_T mode, [[nonnull]] char const *__restrict file, [[nonnull]] __TARGV) {
	return spawnvpe(mode, file, ___argv, __LOCAL_environ);
}

[[cp, guard, argument_names(mode, path, ___argv, ___envp)]]
[[export_alias("_spawnve"), requires_function(open, fspawnve)]]
[[decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_TARGV)]]
[[impl_include("<asm/os/oflags.h>")]]
$pid_t spawnve(__STDC_INT_AS_UINT_T mode,
               [[nonnull]] char const *__restrict path,
               [[nonnull]] __TARGV, [[nonnull]] __TENVP) {
	fd_t fd;
	pid_t result = -1;
@@pp_if defined(O_RDONLY) && defined(O_CLOEXEC)@@
	fd = open(path, O_RDONLY | O_CLOEXEC);
@@pp_elif defined(O_RDONLY)@@
	fd = open(path, O_RDONLY);
@@pp_else@@
	fd = open(path, 0);
@@pp_endif@@
	if likely(fd >= 0) {
		result = fspawnve(mode, fd, ___argv, ___envp);
@@pp_if $has_function(close)@@
		close(fd);
@@pp_endif@@
	}
	return result;
}

[[cp, guard, argument_names(mode, file, ___argv, ___envp)]]
[[export_alias("_spawnvpe")]]
[[decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_TARGV)]]
[[requires_include("<hybrid/__alloca.h>")]]
[[requires($has_function(getenv) && $has_function(spawnve) && defined(__hybrid_alloca))]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_include("<libc/errno.h>")]]
[[impl_prefix(
@@push_namespace(local)@@
__LOCAL_LIBC(__spawnvpe_impl) __ATTR_NOINLINE __ATTR_NONNULL((2, 4, 6, 7)) $pid_t
(__LIBCCALL __spawnvpe_impl)(__STDC_INT_AS_UINT_T mode,
                             char const *__restrict path, $size_t path_len,
                             char const *__restrict file, $size_t file_len,
                             __TARGV, __TENVP) {
	char *fullpath, *dst;
@@pp_ifdef _WIN32@@
	while (path_len && (path[path_len - 1] == '/' ||
	                    path[path_len - 1] == '\\'))
		--path_len;
@@pp_else@@
	while (path_len && path[path_len - 1] == '/')
		--path_len;
@@pp_endif@@
	fullpath = (char *)__hybrid_alloca((path_len + 1 + file_len + 1) *
	                                   sizeof(char));
	dst = (char *)mempcpyc(fullpath, path, path_len, sizeof(char));
	*dst++ = '/';
	dst = (char *)mempcpyc(dst, file, file_len, sizeof(char));
	*dst = '\0';
	return spawnve(mode, fullpath, ___argv, ___envp);
}
@@pop_namespace@@
)]]
$pid_t spawnvpe(__STDC_INT_AS_UINT_T mode,
                [[nonnull]] char const *__restrict file,
                [[nonnull]] __TARGV, [[nonnull]] __TENVP) {
	char *env_path;
	/* [...]
	 * If the specified filename includes a slash character,
	 * then $PATH is ignored, and the file at the  specified
	 * pathname is executed.
	 * [...] */
@@pp_ifdef _WIN32@@
	if (strchr(file, '/') || strchr(file, '\\'))
		return spawnve(mode, file, ___argv, ___envp);
@@pp_else@@
	if (strchr(file, '/'))
		return spawnve(mode, file, ___argv, ___envp);
@@pp_endif@@
	env_path = getenv("PATH");
	if (env_path && *env_path) {
		size_t filelen;
		filelen  = strlen(file);
		for (;;) {
			$pid_t result;
			char *path_end;
@@pp_ifdef _WIN32@@
			path_end = strchrnul(env_path, ';');
@@pp_else@@
			path_end = strchrnul(env_path, ':');
@@pp_endif@@
			result = (__NAMESPACE_LOCAL_SYM __spawnvpe_impl)(mode, env_path, (size_t)(path_end - env_path),
			                                                 file, filelen, ___argv, ___envp);
			if (result >= 0)
				return result;
			if (!*path_end)
				break;
			env_path = path_end + 1;
		}
	} else {
@@pp_ifdef ENOENT@@
		__libc_seterrno(ENOENT);
@@pp_endif@@
	}
	return -1;
}

[[cp, guard, ATTR_SENTINEL, impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function("spawnv"), export_alias("_spawnl")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
$pid_t spawnl(__STDC_INT_AS_UINT_T mode, [[nonnull]] char const *__restrict path,
              char const *args, ... /*, (char *)NULL*/) {
	__REDIRECT_SPAWNL(char, spawnv, mode, path, args)
}

[[cp, guard, ATTR_SENTINEL, impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function("spawnvp"), export_alias("_spawnlp")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
$pid_t spawnlp(__STDC_INT_AS_UINT_T mode, [[nonnull]] char const *__restrict file,
               char const *args, ... /*, (char *)NULL*/) {
	__REDIRECT_SPAWNL(char, spawnvp, mode, file, args)
}

[[cp, guard, ATTR_SENTINEL_O(1), impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function("spawnve"), export_alias("_spawnle")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
$pid_t spawnle(__STDC_INT_AS_UINT_T mode, [[nonnull]] char const *__restrict path,
               char const *args, ... /*, (char *)NULL, char **environ*/) {
	__REDIRECT_SPAWNLE(char, spawnve, mode, path, args)
}

[[cp, guard, ATTR_SENTINEL_O(1), impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function("spawnvpe"), export_alias("_spawnlpe")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
$pid_t spawnlpe(__STDC_INT_AS_UINT_T mode, [[nonnull]] char const *__restrict file,
                char const *args, ... /*, (char *)NULL, char **environ*/) {
	__REDIRECT_SPAWNLE(char, spawnvpe, mode, file, args)
}

%#ifdef __USE_KOS
[[cp, guard, argument_names(mode, path, ___argv, ___envp)]]
[[export_alias("_spawnve")]]
[[decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_TARGV)]]
[[impl_include("<asm/crt/process.h>", "<libc/errno.h>", "<asm/os/vfork.h>")]]
[[requires_include("<asm/os/oflags.h>", "<asm/os/vfork.h>")]]
[[requires($has_function(fexecve) && $has_function(_Exit) &&
           ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && $has_function(vfork)) ||
            ($has_function(fork) && ($has_function(pipe2) && defined(O_CLOEXEC)) &&
             $has_function(read) && $has_function(write) && $has_function(close))) &&
           $has_function(fexecve) && $has_function(waitpid)
)]]
$pid_t fspawnve(__STDC_INT_AS_UINT_T mode,
                $fd_t execfd,
                [[nonnull]] __TARGV,
                [[nonnull]] __TENVP) {
	int status;
@@pp_if !defined(__ARCH_HAVE_SHARED_VM_VFORK) || !$has_function(vfork)@@
	fd_t pipes[2];
	errno_t error;
	ssize_t temp;
@@pp_else@@
	errno_t old_errno;
@@pp_endif@@
	pid_t child;
	if (mode == P_OVERLAY)
		return fexecve(execfd, ___argv, ___envp);
@@pp_if defined(__ARCH_HAVE_SHARED_VM_VFORK) && $has_function(vfork)@@
	old_errno = __libc_geterrno_or(0);
	__libc_seterrno(0);
@@pp_endif@@
@@pp_if !defined(__ARCH_HAVE_SHARED_VM_VFORK) || !$has_function(vfork)@@
	/* Create a pair of pipes for temporary communication. */
	if (pipe2(pipes, O_CLOEXEC))
		goto err;
@@pp_endif@@
	if (mode == P_DETACH) {
		/* Daemonize (detach) the process using detach(2), or double-fork. */
@@pp_if $has_function(vfork)@@
		if (vfork() == 0)
@@pp_else@@
		if (fork() == 0)
@@pp_endif@@
		{
@@pp_if $has_function(detach)@@
			detach(0); /* Detach myself from my parent. */
			goto do_exec;
@@pp_else@@
@@pp_if $has_function(vfork)@@
			if (vfork() == 0)
@@pp_else@@
			if (fork() == 0)
@@pp_endif@@
				goto do_exec;
			_Exit(0); /* Just terminate the intermediate process. */
@@pp_endif@@
		}
		child = 0;
		goto read_child_errors;
	}
	if (mode == P_WAIT) {
		/* Spawn and join the process */
@@pp_if defined(__ARCH_HAVE_SHARED_VM_VFORK) && $has_function(vfork)@@
		child = vfork();
@@pp_else@@
		child = fork();
@@pp_endif@@
		if (child == 0)
			goto do_exec;
		if (child < 0)
			goto err;
@@pp_if defined(__ARCH_HAVE_SHARED_VM_VFORK) && $has_function(vfork)@@
		/* Check for errors that may have happened in  the
		 * child process _after_ we did the vfork() above. */
		if (__libc_geterrno_or(0) != 0)
			goto err_join_zombie_child;
		/* Success (but still restore the old errno
		 * since  we  overwrote it  to be  0 above) */
		__libc_seterrno(old_errno);
@@pp_else@@
		close(pipes[1]); /* Close the writer. */
		temp = read(pipes[0], &error, sizeof(error));
		close(pipes[0]); /* Close the reader. */
		if (temp < 0)
			goto err_join_zombie_child;
		if (temp == sizeof(error)) {
			/* If something was read, then it is the errno value that caused the failure. */
			__libc_seterrno(error);
			goto err;
		}
@@pp_endif@@
		/* Join the child. */
		while (waitpid(child, &status, 0) < 0) {
@@pp_ifdef EINTR@@
			if (__libc_geterrno() == EINTR)
				continue;
@@pp_endif@@
			goto err;
		}
		return (pid_t)(int)(unsigned int)WEXITSTATUS(status);
	}

	/* Spawn asynchronously. */
@@pp_if defined(__ARCH_HAVE_SHARED_VM_VFORK) && $has_function(vfork)@@
	child = vfork();
@@pp_else@@
	child = fork();
@@pp_endif@@
	if (child == 0)
		goto do_exec;
read_child_errors:
@@pp_if defined(__ARCH_HAVE_SHARED_VM_VFORK) && $has_function(vfork)@@
	/* Check if the vfork() from  the child returned success, but  left
	 * our (vm-shared) errno as non-zero (which would indicate that the
	 * child encountered an error at  some point after vfork()  already
	 * succeeded) */
	if (__libc_geterrno_or(0) != 0)
		goto err_join_zombie_child;
	/* Complete success (but we must still restore the old errno from
	 * before we were called) */
	__libc_seterrno(old_errno);
	/* Return the child's PID */
	return child;
@@pp_else@@
	/* Read from the communication pipe
	 * (NOTE: If exec() succeeds, the pipe will be
	 *        closed and  read() returns  ZERO(0)) */
	close(pipes[1]); /* Close the writer. */
	temp = read(pipes[0], &error, sizeof(error));
	close(pipes[0]); /* Close the reader. */
	if (temp < 0)
		goto err_join_zombie_child;
	/* This means that `fexecve()' below closed the pipe during a successful exec(). */
	if (temp != sizeof(error))
		return child;
	/* If something was read, then it is the errno value that caused the failure. */
	__libc_seterrno(error);
@@pp_endif@@
err_join_zombie_child:
	if (mode != P_DETACH) {
		/* Unless the child was already spawned as detached,
		 * we still have to re-join  it, or else it will  be
		 * left dangling as a zombie process! */
		if (waitpid(child, &status, 0) < 0) {
@@pp_ifdef EINTR@@
			if (__libc_geterrno() == EINTR)
				goto err_join_zombie_child;
@@pp_endif@@
		}
	}
err:
	return -1;
do_exec:
	/* When the exec succeeds, the pipe is auto-
	 * closed because it's marked as  O_CLOEXEC! */
	fexecve(execfd, ___argv, ___envp);
@@pp_if defined(__ARCH_HAVE_SHARED_VM_VFORK) && $has_function(vfork)@@
	/* If the exec fails, it will have modified `errno' to indicate this fact.
	 * And since we're sharing VMs with  our parent process, the error  reason
	 * will have already  been written  back to  our parent's  VM, so  there's
	 * actually nothing left for us to do, but to simply exit! */
@@pp_else@@
	/* Write the exec-error back to our parent. */
@@pp_ifdef ENOENT@@
	error = __libc_geterrno_or(ENOENT);
@@pp_else@@
	error = __libc_geterrno_or(1);
@@pp_endif@@
	/* Communicate back why this failed. */
	write(pipes[1], &error, sizeof(error));
	/* No need to close the pipe, it's auto-closed by the kernel! */
@@pp_endif@@
	_Exit(127);
}
%#endif /* __USE_KOS */
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
