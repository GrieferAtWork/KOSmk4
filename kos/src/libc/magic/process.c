/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: Cygwin       (/winsup/cygwin/include/process.h) */
/* (#) Portability: DJGPP        (/include/process.h) */
/* (#) Portability: EMX kLIBC    (/libc/include/process.h) */
/* (#) Portability: MSVC         (/include/process.h) */
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/process.h) */
/* (#) Portability: Windows Kits (/ucrt/process.h) */
/* (#) Portability: mintlib      (/include/process.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(pid_t = __pid_t)]

%[define_type_class(__TARGV = "TP")]
%[define_type_class(__TENVP = "TP")]

%(auto_source)#include "../libc/dl.h"
%(auto_source)#include "../libc/globals.h"

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/crt/process.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

/* `mode' argument values for spawn() functions. */
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

/* `action' argument values for cwait() functions. */
#ifdef __WAIT_CHILD
#define WAIT_CHILD      __WAIT_CHILD      /* Ignored */
#endif /* __WAIT_CHILD */
#ifdef __WAIT_GRANDCHILD
#define WAIT_GRANDCHILD __WAIT_GRANDCHILD /* Ignored */
#endif /* __WAIT_GRANDCHILD */


#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */

__SYSDECL_BEGIN

/* DOS */
}
%#ifdef __USE_DOS
%{
#ifndef __USE_DOS_CLEAN
#include <corecrt_wprocess.h> /* Include <wchar.h> instead */
#endif /* !__USE_DOS_CLEAN */

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
#define __intptr_t_defined
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */
#ifndef __uintptr_t_defined
#define __uintptr_t_defined
typedef __uintptr_t uintptr_t;
#endif /* !__uintptr_t_defined */
#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

}

%{
#ifndef ____dos_beginthreadex_entry_t_defined
#define ____dos_beginthreadex_entry_t_defined
#ifdef __NO_ATTR_STDCALL
typedef __UINT32_TYPE__ (__LIBDCALL *__dos_beginthreadex_entry_t)(void *__arg);
#else /* __NO_ATTR_STDCALL */
typedef __UINT32_TYPE__ (__ATTR_STDCALL *__dos_beginthreadex_entry_t)(void *__arg);
#endif /* !__NO_ATTR_STDCALL */
#endif /* !____dos_beginthreadex_entry_t_defined */
}
%

%[define(DEFINE_DOS_BEGINTHREADEX_ENTRY_T =
@@pp_ifndef ____dos_beginthreadex_entry_t_defined@@
#define ____dos_beginthreadex_entry_t_defined
#ifdef __NO_ATTR_STDCALL
typedef __UINT32_TYPE__ (__LIBDCALL *__dos_beginthreadex_entry_t)(void *__arg);
#else /* __NO_ATTR_STDCALL */
typedef __UINT32_TYPE__ (__ATTR_STDCALL *__dos_beginthreadex_entry_t)(void *__arg);
#endif /* !__NO_ATTR_STDCALL */
@@pp_endif@@
)]

%[define_type_class(__dos_beginthreadex_entry_t = "TP")]
%[define_replacement(__dos_beginthreadex_entry_t = __dos_beginthreadex_entry_t)]



%[insert:std]
%[insert:guarded_std_function(exit)]
%[insert:guarded_std_function(abort)]

%[insert:guarded_function(_exit = _Exit)]



[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt.dos.sched.thread")]]
uintptr_t _beginthread(void (LIBDCALL *entry)(void *arg), $u32 stacksz, void *arg);

[[decl_include("<hybrid/typecore.h>")]]
[[decl_prefix(DEFINE_DOS_BEGINTHREADEX_ENTRY_T)]]
[[section(".text.crt.dos.sched.thread")]]
uintptr_t _beginthreadex(void *sec, $u32 stacksz, __dos_beginthreadex_entry_t entry,
                         void *arg, $u32 flags, $u32 *threadaddr);

[[requires($has_function(_endthreadex))]]
[[section(".text.crt.dos.sched.thread")]]
void _endthread() {
	_endthreadex(0);
}

[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt.dos.sched.thread")]]
void _endthreadex($u32 exitcode);

[[throws, section(".text.crt.dos.sched.process")]]
void _cexit();

[[throws, section(".text.crt.dos.sched.process")]]
void _c_exit() {
}

%[define(DEFINE__tls_callback_type =
@@pp_ifndef ___tls_callback_type_defined@@
#define ___tls_callback_type_defined
#ifdef __NO_ATTR_STDCALL
typedef void (__ATTR_MSABI *_tls_callback_type)(void * /*???*/, __ULONG32_TYPE__ /*???*/, void * /*???*/);
#else /* __NO_ATTR_STDCALL */
typedef void (__ATTR_STDCALL *_tls_callback_type)(void * /*???*/, __ULONG32_TYPE__ /*???*/, void * /*???*/);
#endif /* !__NO_ATTR_STDCALL */
@@pp_endif@@
)]
%[define_replacement(_tls_callback_type = _tls_callback_type)]

%[insert:prefix(DEFINE__tls_callback_type)]

[[section(".text.crt.dos.sched.process")]]
[[crt_dos_only, decl_prefix(DEFINE__tls_callback_type)]]
void _register_thread_local_exe_atexit_callback([[nonnull]] _tls_callback_type callback);




%[insert:function(_getpid = getpid)]

[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
int _execv([[in]] char const *__restrict path,
           [[in]] char const *const *___argv) = execv;

[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
int _execvp([[in]] char const *__restrict file,
            [[in]] char const *const *___argv) = execvp;

[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
int _execve([[in]] char const *__restrict path,
            [[in]] char const *const *___argv,
            [[in]] char const *const *___envp) = execve;

[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
int _execvpe([[in]] char const *__restrict file,
             [[in]] char const *const *___argv,
             [[in]] char const *const *___envp) = execvpe;

%[insert:function(_execl = execl)]
%[insert:function(_execlp = execlp)]
%[insert:function(_execle = execle)]
%[insert:function(_execlpe = execlpe)]

%[insert:function(_cwait = cwait)]

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
intptr_t _spawnv(__STDC_INT_AS_UINT_T mode,
                 [[in]] char const *__restrict path,
                 [[in]] char const *const *___argv) = spawnv;

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
intptr_t _spawnvp(__STDC_INT_AS_UINT_T mode,
                  [[in]] char const *__restrict file,
                  [[in]] char const *const *___argv) = spawnvp;

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
intptr_t _spawnve(__STDC_INT_AS_UINT_T mode,
                  [[in]] char const *__restrict path,
                  [[in]] char const *const *___argv,
                  [[in]] char const *const *___envp) = spawnve;

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
intptr_t _spawnvpe(__STDC_INT_AS_UINT_T mode,
                   [[in]] char const *__restrict file,
                   [[in]] char const *const *___argv,
                   [[in]] char const *const *___envp) = spawnvpe;

[[ATTR_SENTINEL, decl_include("<features.h>", "<hybrid/typecore.h>")]]
intptr_t _spawnl(__STDC_INT_AS_UINT_T mode,
                 [[in]] char const *__restrict path,
                 [[in_opt]] char const *args, ... /*, (char *)NULL*/) = spawnl;

[[ATTR_SENTINEL, decl_include("<features.h>", "<hybrid/typecore.h>")]]
intptr_t _spawnlp(__STDC_INT_AS_UINT_T mode,
                  [[in]] char const *__restrict file,
                  [[in_opt]] char const *args, ... /*, (char *)NULL*/) = spawnlp;

[[ATTR_SENTINEL_O(1), decl_include("<features.h>", "<hybrid/typecore.h>")]]
intptr_t _spawnle(__STDC_INT_AS_UINT_T mode,
                  [[in]] char const *__restrict path,
                  [[in_opt]] char const *args, ... /*, (char *)NULL, [[in]] (char **)environ*/) = spawnle;

[[ATTR_SENTINEL_O(1), decl_include("<features.h>", "<hybrid/typecore.h>")]]
intptr_t _spawnlpe(__STDC_INT_AS_UINT_T mode,
                   [[in]] char const *__restrict file,
                   [[in_opt]] char const *args, ... /*, (char *)NULL, [[in]] (char **)environ*/) = spawnlpe;

%[insert:extern(system)]

%
%
%
%[define_c_language_keyword(__KOS_FIXED_CONST)]

[[section(".text.crt.dos.fs.dlfcn")]]
[[throws, decl_include("<features.h>", "<bits/types.h>")]]
[[requires_include("<libdl/asm/dlfcn.h>")]]
[[requires(defined(__CRT_HAVE_dlopen))]]
[[crt_dos_variant, userimpl, impl_include("<dlfcn.h>")]]
intptr_t _loaddll([[in_opt]] char __KOS_FIXED_CONST *file) {
@@pp_if defined(@RTLD_LOCAL@)@@
	return (intptr_t)(uintptr_t)@dlopen@(file, @RTLD_LOCAL@);
@@pp_elif defined(@RTLD_GLOBAL@)@@
	return (intptr_t)(uintptr_t)@dlopen@(file, @RTLD_GLOBAL@);
@@pp_else@@
	return (intptr_t)(uintptr_t)@dlopen@(file, 0);
@@pp_endif@@
}

[[section(".text.crt.dos.fs.dlfcn")]]
[[throws, decl_include("<bits/types.h>")]]
[[impl_include("<dlfcn.h>")]]
int _unloaddll(intptr_t hnd) {
@@pp_ifdef __CRT_HAVE_dlclose@@
	return @dlclose@((void *)(uintptr_t)hnd);
@@pp_else@@
	(void)hnd;
	return 0;
@@pp_endif@@
}

%
%{
#ifndef ____procfun_defined
#define ____procfun_defined
typedef int (*__procfun)(void);
#endif /* !____procfun_defined */
}
%[define_replacement(__procfun = __procfun)]
%[define_type_class(__procfun = "TP")]
%[define(DEFINE_PROCFUN =
#ifndef ____procfun_defined
#define ____procfun_defined
typedef int (*__procfun)(void);
#endif /* !____procfun_defined */
)]

[[section(".text.crt.dos.fs.dlfcn")]]
[[throws, decl_include("<features.h>", "<bits/types.h>")]]
[[decl_prefix(DEFINE_PROCFUN)]]
[[requires_include("<libdl/asm/dlfcn.h>")]]
[[requires(defined(__CRT_HAVE_dlsym))]]
[[impl_include("<dlfcn.h>")]]
__procfun _getdllprocaddr(intptr_t hnd,
                          [[in_opt]] char __KOS_FIXED_CONST *symname,
                          intptr_t ord) {
	(void)ord;
	return (__procfun)@dlsym@((void *)(uintptr_t)hnd, symname);
}


%{

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef __intptr_t_defined
#define __intptr_t_defined
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */

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


@@>> cwait(3)
@@DOS name for `waitpid(2)', except that `action' is ignored. Use
@@this function together with the `spawn(3)' family of functions.
@@@return: pid: Child process exited.
@@@return: -1:  Error (s.a. `errno')
[[section(".text.crt.dos.fs.exec.spawn")]]
[[decl_include("<features.h>", "<bits/types.h>")]]
[[cp, dos_only_export_alias("_cwait"), requires_function(waitpid)]]
$pid_t cwait([[out_opt]] int *tstat, $pid_t pid, __STDC_INT_AS_UINT_T action) {
	/* This one's pretty simple, because it's literally just a waitpid() system call...
	 * (It even returns the same  thing, that being the  PID of the joined  process...) */
	/* NOTE: Apparently, the `action' argument is completely ignored... */
	(void)action;
	/* NOTE: `waitpid(2)' with `options: 0' means `WEXITED' */
	return waitpid(pid, tstat, 0);
}

[[section(".text.crt{|.dos}.fs.exec.spawn")]]
[[cp, guard, argument_names(mode, path, ___argv), dos_export_alias("_spawnv")]]
[[decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_TARGV)]]
[[requires_include("<libc/template/environ.h>"), requires($has_function(spawnve) && defined(__LOCAL_environ))]]
[[impl_include("<libc/template/environ.h>"), crt_dos_variant]]
$pid_t spawnv(__STDC_INT_AS_UINT_T mode, [[in]] char const *__restrict path, [[in]] __TARGV) {
	return spawnve(mode, path, ___argv, __LOCAL_environ);
}

[[section(".text.crt{|.dos}.fs.exec.spawn")]]
[[cp, guard, argument_names(mode, file, ___argv), dos_export_alias("_spawnvp")]]
[[decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_TARGV)]]
[[requires_include("<libc/template/environ.h>"), crt_dos_variant]]
[[requires($has_function(spawnvpe) && defined(__LOCAL_environ))]]
[[impl_include("<libc/template/environ.h>")]]
$pid_t spawnvp(__STDC_INT_AS_UINT_T mode, [[in]] char const *__restrict file, [[in]] __TARGV) {
	return spawnvpe(mode, file, ___argv, __LOCAL_environ);
}

[[section(".text.crt{|.dos}.fs.exec.spawn")]]
[[cp, guard, argument_names(mode, path, ___argv, ___envp)]]
[[dos_export_alias("_spawnve"), requires_function(open, fspawnve)]]
[[decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_TARGV)]]
[[impl_include("<asm/os/oflags.h>"), crt_dos_variant]]
$pid_t spawnve(__STDC_INT_AS_UINT_T mode,
               [[in]] char const *__restrict path,
               [[in]] __TARGV, [[in]] __TENVP) {
	fd_t fd;
	pid_t result = -1;
@@pp_ifdef O_RDONLY@@
	fd = open(path, O_RDONLY | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
@@pp_else@@
	fd = open(path, __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
@@pp_endif@@
	if likely(fd >= 0) {
		result = fspawnve(mode, fd, ___argv, ___envp);
@@pp_if $has_function(close)@@
		close(fd);
@@pp_endif@@
	}
	return result;
}

[[section(".text.crt{|.dos}.fs.exec.spawn")]]
[[cp, guard, argument_names(mode, file, ___argv, ___envp), dos_export_alias("_spawnvpe")]]
[[decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_TARGV)]]
[[requires_include("<hybrid/__alloca.h>")]]
[[requires($has_function(getenv) && $has_function(spawnve) && defined(__hybrid_alloca))]]
[[dependency(mempcpyc, spawnve)]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_include("<libc/errno.h>")]]
[[crt_dos_variant({
prefix: {
@@push_namespace(local)@@
__LOCAL_LIBC(__dos_spawnvpe_impl) __ATTR_NOINLINE __ATTR_NONNULL((2, 4, 6, 7)) $pid_t
(__LIBCCALL __dos_spawnvpe_impl)(__STDC_INT_AS_UINT_T mode,
                                 char const *__restrict path, $size_t path_len,
                                 char const *__restrict file, $size_t file_len,
                                 __TARGV, __TENVP) {
	char *fullpath, *dst;
	while (path_len && (path[path_len - 1] == '/' ||
	                    path[path_len - 1] == '\\'))
		--path_len;
	fullpath = (char *)__hybrid_alloca((path_len + 1 + file_len + 1) *
	                                   sizeof(char));
	dst = (char *)mempcpyc(fullpath, path, path_len, sizeof(char));
	*dst++ = '/';
	dst = (char *)mempcpyc(dst, file, file_len, sizeof(char));
	*dst = '\0';
	return libd_spawnve(mode, fullpath, ___argv, ___envp);
}
@@pop_namespace@@
},
impl: {
	char *env_path;
	/* [...]
	 * If the specified filename includes a slash character,
	 * then $PATH is ignored, and the file at the  specified
	 * pathname is executed.
	 * [...] */
	if (strchr(file, '/') || strchr(file, '\\'))
		return spawnve(mode, file, ___argv, ___envp);
	env_path = getenv("PATH");
	if (env_path && *env_path) {
		size_t filelen;
		filelen  = strlen(file);
		for (;;) {
			$pid_t result;
			char *path_end;
			path_end = strchrnul(env_path, ';');
			result = (__NAMESPACE_LOCAL_SYM __dos_spawnvpe_impl)(mode, env_path, (size_t)(path_end - env_path),
			                                                     file, filelen, ___argv, ___envp);
			if (result >= 0)
				return result;
			if (!*path_end)
				break;
			env_path = path_end + 1;
		}
	} else {
@@pp_ifdef ENOENT@@
		(void)libc_seterrno(ENOENT);
@@pp_endif@@
	}
	return -1;
}
})]]
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
                [[in]] char const *__restrict file,
                [[in]] __TARGV, [[in]] __TENVP) {
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
		(void)libc_seterrno(ENOENT);
@@pp_endif@@
	}
	return -1;
}

[[section(".text.crt{|.dos}.fs.exec.spawn")]]
[[cp, guard, ATTR_SENTINEL, impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function("spawnv"), dos_export_alias("_spawnl")]]
[[decl_include("<features.h>", "<bits/types.h>"), crt_dos_variant]]
$pid_t spawnl(__STDC_INT_AS_UINT_T mode, [[in]] char const *__restrict path,
              [[in_opt]] char const *args, ... /*, (char *)NULL*/) {
	__REDIRECT_SPAWNL(char, spawnv, mode, path, args)
}

[[section(".text.crt{|.dos}.fs.exec.spawn")]]
[[cp, guard, ATTR_SENTINEL, impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function("spawnvp"), dos_export_alias("_spawnlp")]]
[[decl_include("<features.h>", "<bits/types.h>"), crt_dos_variant]]
$pid_t spawnlp(__STDC_INT_AS_UINT_T mode, [[in]] char const *__restrict file,
               [[in_opt]] char const *args, ... /*, (char *)NULL*/) {
	__REDIRECT_SPAWNL(char, spawnvp, mode, file, args)
}

[[section(".text.crt{|.dos}.fs.exec.spawn")]]
[[cp, guard, ATTR_SENTINEL_O(1), impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function("spawnve"), dos_export_alias("_spawnle")]]
[[decl_include("<features.h>", "<bits/types.h>"), crt_dos_variant]]
$pid_t spawnle(__STDC_INT_AS_UINT_T mode, [[in]] char const *__restrict path,
               [[in_opt]] char const *args, ... /*, (char *)NULL, [[in]] char **environ*/) {
	__REDIRECT_SPAWNLE(char, spawnve, mode, path, args)
}

[[section(".text.crt{|.dos}.fs.exec.spawn")]]
[[cp, guard, ATTR_SENTINEL_O(1), impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function("spawnvpe"), dos_export_alias("_spawnlpe")]]
[[decl_include("<features.h>", "<bits/types.h>"), crt_dos_variant]]
$pid_t spawnlpe(__STDC_INT_AS_UINT_T mode, [[in]] char const *__restrict file,
                [[in_opt]] char const *args, ... /*, (char *)NULL, [[in]] char **environ*/) {
	__REDIRECT_SPAWNLE(char, spawnvpe, mode, file, args)
}

%#ifdef __USE_KOS
[[section(".text.crt{|.dos}.fs.exec.spawn")]]
[[cp, guard, argument_names(mode, path, ___argv, ___envp)]]
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
                [[in]] __TARGV,
                [[in]] __TENVP) {
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
	old_errno = libc_geterrno_or(0);
	(void)libc_seterrno(0);
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
		if (libc_geterrno_or(0) != 0)
			goto err_join_zombie_child;
		/* Success (but still restore the old errno
		 * since  we  overwrote it  to be  0 above) */
		(void)libc_seterrno(old_errno);
@@pp_else@@
		close(pipes[1]); /* Close the writer. */
		temp = read(pipes[0], &error, sizeof(error));
		close(pipes[0]); /* Close the reader. */
		if (temp < 0)
			goto err_join_zombie_child;
		if (temp == sizeof(error)) {
			/* If something was read, then it is the errno value that caused the failure. */
			(void)libc_seterrno(error);
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
	if (libc_geterrno_or(0) != 0)
		goto err_join_zombie_child;
	/* Complete success (but we must still restore the old errno from
	 * before we were called) */
	(void)libc_seterrno(old_errno);
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
	(void)libc_seterrno(error);
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
	error = libc_geterrno_or(ENOENT);
@@pp_else@@
	error = libc_geterrno_or(1);
@@pp_endif@@
	/* Communicate back why this failed. */
	write(pipes[1], &error, sizeof(error));
	/* No need to close the pipe, it's auto-closed by the kernel! */
@@pp_endif@@
	_Exit(127);
}

%[insert:extern(fexecve)] /* Also defined in <unistd.h> */

%#endif /* __USE_KOS */
%#endif /* __USE_DOS || __USE_KOS */

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
