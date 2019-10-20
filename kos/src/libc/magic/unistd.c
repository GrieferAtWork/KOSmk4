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

%[define_replacement(fd_t       = __fd_t)]
%[define_replacement(off_t      = __FS_TYPE(off))]
%[define_replacement(pos_t      = __FS_TYPE(pos))]
%[define_replacement(uid_t      = __uid_t)]
%[define_replacement(gid_t      = __gid_t)]
%[define_replacement(pid_t      = __pid_t)]
%[define_replacement(off32_t    = __off32_t)]
%[define_replacement(off64_t    = __off64_t)]
%[define_replacement(pos32_t    = __pos32_t)]
%[define_replacement(pos64_t    = __pos64_t)]
%[define_replacement(atflag_t   = __atflag_t)]
%[define_replacement(useconds_t = __useconds_t)]
%[define_replacement(oflag_t    = __oflag_t)]


%{
#include <features.h>
#include <bits/types.h>
#include <bits/confname.h>
#include <bits/posix_opt.h>
#include <hybrid/typecore.h>
#if defined(__CRT_GLC) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL)
#include <asm/unistd.h>
#endif /* __CRT_GLC || __CRT_KOS || __CRT_KOS_KERNEL */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#include <bits/environments.h>
#endif

__SYSDECL_BEGIN

#ifdef __USE_XOPEN2K8
#   define _POSIX_VERSION    200809L
#elif defined(__USE_XOPEN2K)
#   define _POSIX_VERSION    200112L
#elif defined(__USE_POSIX199506)
#   define _POSIX_VERSION    199506L
#elif defined(__USE_POSIX199309)
#   define _POSIX_VERSION    199309L
#else
#   define _POSIX_VERSION    199009L
#endif
#ifdef __USE_XOPEN2K8
#   define __POSIX2_THIS_VERSION    200809L
#elif defined(__USE_XOPEN2K)
#   define __POSIX2_THIS_VERSION    200112L
#elif defined(__USE_POSIX199506)
#   define __POSIX2_THIS_VERSION    199506L
#else
#   define __POSIX2_THIS_VERSION    199209L
#endif

#define _POSIX2_VERSION   __POSIX2_THIS_VERSION
#define _POSIX2_C_VERSION __POSIX2_THIS_VERSION
#define _POSIX2_C_BIND    __POSIX2_THIS_VERSION
#define _POSIX2_C_DEV     __POSIX2_THIS_VERSION
#define _POSIX2_SW_DEV    __POSIX2_THIS_VERSION
#define _POSIX2_LOCALEDEF __POSIX2_THIS_VERSION

#ifdef __USE_XOPEN2K8
#   define _XOPEN_VERSION    700
#elif defined(__USE_XOPEN2K)
#   define _XOPEN_VERSION    600
#elif defined(__USE_UNIX98)
#   define _XOPEN_VERSION    500
#else
#   define _XOPEN_VERSION    4
#endif
#define _XOPEN_XCU_VERSION   4
#define _XOPEN_XPG2          1
#define _XOPEN_XPG3          1
#define _XOPEN_XPG4          1
#define _XOPEN_UNIX          1
#define _XOPEN_CRYPT         1
#define _XOPEN_ENH_I18N      1
#define _XOPEN_LEGACY        1

#define STDIN_FILENO  0 /* Standard input.  */
#define STDOUT_FILENO 1 /* Standard output.  */
#define STDERR_FILENO 2 /* Standard error output.  */

#define F_OK 0 /* Test for existence.  */
#define X_OK 1 /* Test for execute permission.  */
#define W_OK 2 /* Test for write permission.  */
#define R_OK 4 /* Test for read permission.  */

#ifndef SEEK_SET
#   define SEEK_SET  0 /* Seek from beginning of file.  */
#   define SEEK_CUR  1 /* Seek from current position.  */
#   define SEEK_END  2 /* Seek from end of file.  */
#if defined(__USE_GNU) && (defined(__CRT_KOS) || defined(__CRT_GLC))
#   define SEEK_DATA 3 /* Seek to next data.  */
#   define SEEK_HOLE 4 /* Seek to next hole.  */
#endif /* __USE_GNU && (__CRT_KOS || __CRT_GLC) */
#endif

#ifdef __USE_MISC
#ifndef L_SET
#   define L_SET  SEEK_SET
#   define L_CURR SEEK_CUR
#   define L_INCR SEEK_CUR
#   define L_XTND SEEK_END
#endif /* !L_SET */
#endif

#ifdef __CC__
#ifndef __ssize_t_defined
#define __ssize_t_defined 1
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __gid_t_defined
#define __gid_t_defined 1
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */
#ifndef __uid_t_defined
#define __uid_t_defined 1
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */
#ifndef __off_t_defined
#define __off_t_defined
typedef __typedef_off_t off_t;
#endif /* !__off_t_defined */
#ifndef __useconds_t_defined
#define __useconds_t_defined 1
typedef __useconds_t useconds_t;
#endif /* !__useconds_t_defined */
#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */
#ifdef __USE_LARGEFILE64
#ifndef __off64_t_defined
#define __off64_t_defined 1
typedef __off64_t off64_t;
#endif /* !__off64_t_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#if defined(__USE_XOPEN_EXTENDED) || \
    defined(__USE_XOPEN2K)
#ifndef __intptr_t_defined
#define __intptr_t_defined 1
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */
#endif

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifndef __socklen_t_defined
#define __socklen_t_defined 1
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */
#endif

#ifndef __TARGV
#ifdef __USE_DOS
#   define __TARGV  char const *const *___argv
#   define __TENVP  char const *const *___envp
#else
#   define __TARGV  char *const ___argv[__restrict_arr]
#   define __TENVP  char *const ___envp[__restrict_arr]
#endif
#endif /* !__TARGV */

#ifndef ____environ_defined
#define ____environ_defined 1
#undef __environ
#if defined(__CRT_HAVE_environ) && !defined(__NO_ASMNAME)
__LIBC char **__environ __ASMNAME("environ");
#elif defined(__CRT_HAVE__environ) && !defined(__NO_ASMNAME)
__LIBC char **__environ __ASMNAME("_environ");
#define __environ __environ
#define __environ __environ
#elif defined(__CRT_HAVE__environ)
#undef _environ
#ifndef ___environ_defined
#define ___environ_defined 1
__LIBC char **_environ;
#endif /* !___environ_defined */
#define __environ _environ
#elif defined(__CRT_HAVE_environ)
#undef environ
#ifndef __environ_defined
#define __environ_defined 1
__LIBC char **environ;
#endif /* !__environ_defined */
#define __environ environ
#elif defined(__CRT_HAVE___p__environ)
#ifndef ____p__environ_defined
#define ____p__environ_defined 1
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#endif /* !____p__environ_defined */
#define __environ (*__p__environ())
#else
#undef ____environ_defined
#endif
#endif /* !____environ_defined */

}

%(user){
INTDEF WUNUSED ATTR_CONST ATTR_RETNONNULL char ***NOTHROW(LIBCCALL libc_p_environ)(void);
}

%[default_impl_section(.text.crt.fs.exec.exec)]

@@>> execv(3)
@@Replace the calling process with the application image referred to by `PATH' / `FILE'
@@and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP'
[cp][guard][alias(_execv)][argument_names(path, ___argv)]
[nobuiltin][if(__has_builtin(__builtin_execv) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execv)),
preferred_impl({ return @__builtin_execv@(path, (char *const *)___argv); })]
execv:([notnull] char const *__restrict path, [notnull] @__TARGV@) -> int;

@@>> execve(2)
@@Replace the calling process with the application image referred to by `PATH' / `FILE'
@@and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP'
[cp][guard][alias(_execve)][argument_names(path, ___argv, ___envp)]
[nobuiltin][if(__has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execve)),
preferred_impl({ return @__builtin_execve@(path, (char *const *)___argv, (char *const *)___envp); })]
execve:([notnull] char const *__restrict path, [notnull] @__TARGV@, [notnull] @__TENVP@) -> int;

@@>> execvp(3)
@@Replace the calling process with the application image referred to by `PATH' / `FILE'
@@and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP'
[cp][guard][alias(_execvp)][argument_names(file, ___argv)]
[nobuiltin][if(__has_builtin(__builtin_execvp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execvp)),
preferred_impl({ return @__builtin_execvp@(file, (char *const *)___argv); })]
execvp:([notnull] char const *__restrict file, [notnull] @__TARGV@) -> int;


@@>> execl(3)
@@Replace the calling process with the application image referred to by `PATH' / `FILE'
@@and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list
[cp][guard][dependency_include(<parts/redirect-exec.h>)]
[requires($has_function(execv))][ATTR_SENTINEL][alias(_execl)][allow_macros][crtbuiltin]
execl:([notnull] char const *__restrict path, char const *args, ... /*, (char *)NULL*/) -> int {
	__REDIRECT_EXECL(char, execv, path, args)
}
@@>> execle(3)
@@Replace the calling process with the application image referred to by `PATH' / `FILE'
@@and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinal
[cp][guard][dependency_include(<parts/redirect-exec.h>)]
[requires($has_function(execve))][ATTR_SENTINEL_O(1)][alias(_execle)][allow_macros][crtbuiltin]
execle:([notnull] char const *__restrict path, char const *args, ... /*, (char *)NULL, (char **)environ*/) -> int {
	__REDIRECT_EXECLE(char, execve, path, args)
}

@@>> execlp(3)
@@Replace the calling process with the application image referred to by `PATH' / `FILE'
@@and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list
[cp][guard][dependency_include(<parts/redirect-exec.h>)]
[requires($has_function(execvp))][ATTR_SENTINEL][alias(_execlp)][allow_macros][crtbuiltin]
execlp:([notnull] char const *__restrict file, char const *args, ... /*, (char *)NULL*/) -> int {
	__REDIRECT_EXECL(char, execvp, file, args)
}

%#if defined(__USE_KOS) || defined(__USE_DOS) || defined(__USE_GNU)
@@>> execvpe(3)
@@Replace the calling process with the application image referred to by `FILE'
@@and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP'
[cp][guard][alias(_execvpe)][argument_names(file, ___argv, ___envp)]
execvpe:([notnull] char const *__restrict file, [notnull] @__TARGV@, [notnull] @__TENVP@) -> int;
%#endif /* __USE_KOS || __USE_DOS || __USE_GNU */

%#if defined(__USE_KOS) || defined(__USE_DOS)
@@>> execlpe(3)
@@Replace the calling process with the application image referred to by `PATH' / `FILE'
@@and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinal
[cp][guard][dependency_include(<parts/redirect-exec.h>)]
[requires($has_function(execvpe))][ATTR_SENTINEL_O(1)][alias(_execlpe)][allow_macros]
execlpe:([notnull] char const *__restrict file, char const *args, ... /*, (char *)NULL, (char **)environ*/) -> int {
	__REDIRECT_EXECLE(char, execvp, file, args)
}
%#endif /* __USE_KOS || __USE_DOS */

%[default_impl_section(.text.crt.sched.process)]

%
@@>> getpid(2)
@@Return the PID of the calling process (that is the TID of the calling thread group's leader)
@@THIS_THREAD->LEADER->PID
[guard][ATTR_WUNUSED][alias(_getpid)] getpid:() -> $pid_t;

%
%#ifdef __USE_KOS
@@>> gettid(2)
@@Return the TID of the calling thread
@@THIS_THREAD->PID
[section(.text.crt.sched.thread)]
[guard][ATTR_WUNUSED] gettid:() -> $pid_t;
%#endif /* __USE_KOS */

[section(.text.crt.dos.io.access)]
[ignore] dos_pipe:([notnull] $fd_t pipedes[2], $uint32_t pipesize, $oflag_t textmode) -> int = _pipe?;

%
@@>> pipe(2)
@@Create a new pair of connected pipes ([0] = reader, [1] = writer)
[section(.text.crt.io.access)][noexport][requires($has_function(dos_pipe))]
pipe:([notnull] $fd_t pipedes[2]) -> int {
	return dos_pipe(pipedes, 4096, 0x8000); /* O_BINARY */
}

@@Sleep for up to `DURATION' seconds
[section(.text.crt.dos.system.utility)]
[cp][ignore] dos_sleep:($uint32_t duration) = _sleep?;

%
@@>> sleep(3)
@@Sleep for up to `SECONDS' seconds
[section(.text.crt.system.utility)]
[cp][guard][noexport][requires($has_function(dos_sleep))]
sleep:(unsigned int seconds) -> unsigned int {
	dos_sleep((uint32_t)seconds);
	return 0;
}

%
@@>> fsync(2)
@@Synchronize a file (including its descriptor which contains timestamps, and its size),
@@meaning that changes to its data and/or descriptor are written to disk
[cp][alias(_commit, fdatasync)][section(.text.crt.io.sync)][user][noexport]
fsync:($fd_t fd) -> int {
	(void)fd;
	/* NO-OP */
	return 0;
}


%
@@>> getppid(2)
@@Return the PID of the calling process's parent.
@@(That is the TID of the leader of the parent of the calling thread's leader)
@@THIS_THREAD->LEADER->PARENT->LEADER->PID
[ATTR_WUNUSED] getppid:() -> $pid_t;


%
@@>> getpgrp(2)
@@Return the ID of the calling process's process group.
@@(That is the TID of the leader of the process group of the calling thread's leader)
@@THIS_THREAD->LEADER->GROUP_LEADER->PID
[ATTR_WUNUSED] getpgrp:() -> $pid_t;

%
@@>> getpgid(2)
@@Return the ID of the process group associated with `PID's process.
@@(That is the TID of the leader of the process group of `PID's leader)
@@THREAD[PID]->LEADER->GROUP_LEADER->PID
@@When `PID' is ZERO(0), use `gettid()' for it instead
[ATTR_WUNUSED] __getpgid:($pid_t pid) -> $pid_t = getpgid?;

%
@@>> setpgid(2)
@@Change the ID of the process group associated with `PID's process.
@@(That is the TID of the leader of the process group of `PID's leader)
@@THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
@@When `PID' is ZERO(0), use `gettid()' for it instead.
@@When `PGID' is ZERO(0), use `PID' (after it was substituted) for instead
setpgid:($pid_t pid, $pid_t pgid) -> int;

%
@@>> setsid(2)
@@Make the calling thread's process the leader of its associated
@@process group, before also making it its own session leader.
@@Then return the TID of that new session leader, which is also the PID of the calling process.
@@THIS_THREAD->LEADER->GROUP_LEADER                 = THIS_THREAD->LEADER;
@@THIS_THREAD->LEADER->GROUP_LEADER->SESSION_LEADER = THIS_THREAD->LEADER->GROUP_LEADER;
@@return THIS_THREAD->LEADER->PID;
setsid:() -> $pid_t;

%[default_impl_section(.text.crt.sched.user)]

%
@@>> getuid(2)
@@Return the real user ID of the calling process
[ATTR_WUNUSED] getuid:() -> $uid_t;

%
@@>> geteuid(2)
@@Return the effective user ID of the calling process
[ATTR_WUNUSED] geteuid:() -> $uid_t;

%
@@>> getgid(2)
@@Return the real group ID of the calling process
[ATTR_WUNUSED] getgid:() -> $gid_t;

%
@@>> getegid(2)
@@Return the effective group ID of the calling process
[ATTR_WUNUSED] getegid:() -> $gid_t;

%
%/* ... */
getgroups:(int size, $gid_t list[]) -> int;

%
@@>> setuid(2)
@@Set the effective user ID of the calling process
@@@return: 0 : Success
@@@return: -1: [errno=EINVAL] : The given `UID' is invalid
@@@return: -1: [errno=EPERM]  : The current user is not privileged
setuid:($uid_t uid) -> int;

%
@@>> setgid(2)
@@Set the effective group ID of the calling process
@@@return: 0 : Success
@@@return: -1: [errno=EINVAL] : The given `GID' is invalid
@@@return: -1: [errno=EPERM]  : The current user is not privileged
setgid:($gid_t gid) -> int;


%
@@>> fork(2)
@@Clone the calling thread into a second process and return twice, once
@@in the parent process where this function returns the (non-zero) PID
@@of the forked child process, and a second time in the child process
@@itself, where ZERO(0) is returned.
@@The child then usually proceeds by calling `exec(2)' to replace its
@@application image with that of another program that the original
@@parent can then `wait(2)' for
[section(.text.crt.sched.access)][crtbuiltin]
[ATTR_WUNUSED] fork:() -> $pid_t;


%[default_impl_section(.text.crt.system.utility)]

%
@@>> alarm(2)
@@@return: 0 : No alarm was scheduled before.
@@@return: * : The number of seconds yet to pass before a previous alarm would have elapsed.
@@Schedule an to deliver a `SIGALRM' after letting `seconds' elapse.
@@You may pass ZERO(0) for SECONDS to disable a previously scheduled alarm
alarm:(unsigned int seconds) -> unsigned int;

%
@@>> pause(2)
@@Suspend execution until the delivery of a POSIX_SIGNAL
[cp] pause:() -> int;

%
@@>> fpathconf(2)
@@@param: NAME: One of `_PC_*' from <bits/confname.h>
@@Return a path configuration value associated with `NAME' for `FD'
[section(.text.crt.fs.property)]
[cp][ATTR_WUNUSED] fpathconf:($fd_t fd, int name) -> long int;

%[default_impl_section(.text.crt.io.tty)]

%
@@>> ttyname(3)
@@Return the name of a TTY given its file descriptor
[cp][ATTR_WUNUSED] ttyname:($fd_t fd) -> char *;

@@>> ttyname_r(3)
@@Return the name of a TTY given its file descriptor
[cp] ttyname_r:($fd_t fd, [outp(buflen)] char *buf, size_t buflen) -> int;

%
@@>> tcgetpgrp(2)
@@Return the foreground process group of a given TTY file descriptor
[ATTR_WUNUSED] tcgetpgrp:($fd_t fd) -> $pid_t;

%
@@>> tcsetpgrp(2)
@@Set the foreground process group of a given TTY file descriptor
tcsetpgrp:($fd_t fd, $pid_t pgrp_id) -> int;

%
%/* ... */
[ATTR_WUNUSED] getlogin:() -> char *;

%[default_impl_section(.text.crt.fs.modify)]

%
@@>> chown(2)
@@Change the ownership of a given `FILE' to `GROUP:OWNER'
[cp][noexport]
[requires(defined(__CRT_AT_FDCWD) && $has_function(fchownat))]
chown:([notnull] char const *file, $uid_t owner, $gid_t group) -> int {
	return fchownat(__CRT_AT_FDCWD, file, owner, group, 0);
}

%
@@>> pathconf(2)
@@@param: NAME: One of `_PC_*' from <bits/confname.h>
@@Return a path configuration value associated with `NAME' for `PATH'
[cp][section(.text.crt.fs.property)]
pathconf:([notnull] char const *path, int name) -> long int;

%
@@>> link(2)
@@Create a hard link from `FROM', leading to `TO'
[cp][noexport]
[requires(defined(__CRT_AT_FDCWD) && $has_function(linkat))]
link:([notnull] char const *from, [notnull] char const *to) -> int {
	/* TODO: Header-implementation for `link()' on DOS (using the windows API) */
	return linkat(__CRT_AT_FDCWD, from, __CRT_AT_FDCWD, to, 0);
}

%[default_impl_section(.text.crt.sched.access)]
%[insert:extern(exit)]
%[default_impl_section(.text.crt.fs.modify)]

%
@@>> read(2)
@@Read data from a given file descriptor `FD' and return the number of bytes read.
@@A return value of ZERO(0) is indicative of EOF
[cp][guard][alias(_read)][export_alias(__read)][section(.text.crt.io.read)]
read:($fd_t fd, [outp(bufsize)] void *buf, size_t bufsize) -> ssize_t;

%
@@>> write(2)
@@Write data to a given file descriptor `FD' and return the number of bytes written
[cp][guard][alias(_write)][export_alias(__write)][section(.text.crt.io.write)]
write:($fd_t fd, [inp(bufsize)] void const *buf, size_t bufsize) -> ssize_t;

%
%#ifdef __USE_KOS
@@>> readall(3)
@@Same as `read(2)', however keep on reading until `read()' indicates EOF (causing
@@`readall()' to immediately return `0') or the entirety of the given buffer has been
@@filled (in which case `bufsize' is returned).
@@If an error occurrs before all data could be read, try to use SEEK_CUR to rewind
@@the file descriptor by the amount of data that had already been loaded. - Errors
@@during this phase are silently ignored and don't cause `errno' to change
[cp][guard][section(.text.crt.io.read)]
[requires($has_function(read) && $has_function(lseek))]
[dependency_include(<parts/errno.h>)]
readall:($fd_t fd, [outp(bufsize)] void *buf, size_t bufsize) -> ssize_t {
	ssize_t result, temp;
	result = read(fd, buf, bufsize);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = read(fd,
			            (byte_t *)buf + (size_t)result,
			            bufsize - (size_t)result);
			if (temp <= 0) {
#ifdef @__errno@
				int old_error = @__errno@;
#endif /* __errno */
				/* Try to un-read data that had already been loaded. */
				lseek(fd, -(off_t)(pos_t)result, SEEK_CUR);
#ifdef @__errno@
				@__errno@ = old_error;
#endif /* __errno */
				result = temp;
				break;
			}
			result += temp;
			if ((size_t)result >= bufsize)
				break;
		}
	}
	return result;
}

@@>> writeall(3)
@@Same as `write(2)', however keep on writing until `write()' indicates EOF (causing
@@`writeall()' to immediately return `0') or the entirety of the given buffer has been
@@written (in which case `bufsize' is returned).
[cp][guard][section(.text.crt.io.write)]
[requires($has_function(write) && $has_function(lseek))]
[dependency_include(<parts/errno.h>)]
writeall:($fd_t fd, [inp(bufsize)] void const *buf, size_t bufsize) -> ssize_t {
	ssize_t result, temp;
	result = write(fd, buf, bufsize);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on writing */
		for (;;) {
			temp = write(fd,
			             (byte_t *)buf + (size_t)result,
			             bufsize - (size_t)result);
			if (temp <= 0) {
				result = temp;
				break;
			}
			result += temp;
			if ((size_t)result >= bufsize)
				break;
		}
	}
	return result;
}
%#endif /* __USE_KOS */


@@>> lseek32(2)
@@Change the position of the file read/write pointer within a file referred to by `FD'
[ignore][alias(_lseek)][section(.text.crt.io.seek)]
lseek32:($fd_t fd, $off32_t offset, int whence) -> $off32_t = lseek?;

%
@@>> lseek(2)
@@Change the position of the file read/write pointer within a file referred to by `FD'
[guard][noexport]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(lseek64, _lseeki64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(lseek, _lseek)]
[alias_args(lseek64, _lseeki64:($fd_t fd, $off64_t offset, int whence) -> $off64_t)]
[alias_args(lseek, _lseek:($fd_t fd, $off32_t offset, int whence) -> $off32_t)]
[requires(defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek))]
[dependency_string(defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE__lseeki64))]
[section(.text.crt.io.seek)]
lseek:($fd_t fd, $off_t offset, int whence) -> $off_t {
#if defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek)
	return lseek32(fd, ($off32_t)offset, whence);
#else
	return lseek64(fd, ($off64_t)offset, whence);
#endif
}

%
@@>> isatty(2)
@@@return: 1: Is a tty
@@@return: 0: Not a tty
@@Check if the given file handle `FD' refers to a TTY
[section(.text.crt.io.tty)]
[guard][ATTR_WUNUSED][alias(_isatty)]
isatty:($fd_t fd) -> int;

%
@@>> dup2(2)
@@@return: NEWFD: Returns the new handle upon success.
@@Duplicate a file referred to by `OLDFD' into `NEWFD'
[section(.text.crt.io.access)]
[guard][alias(_dup2)] dup2:($fd_t oldfd, $fd_t newfd) -> $fd_t;

%
@@>> dup(2)
@@@return: * : Returns the new handle upon success.
@@Duplicate a file referred to by `FD' and return its duplicated handle number
[section(.text.crt.io.access)]
[guard][ATTR_WUNUSED] dup:($fd_t fd) -> $fd_t;

%
@@>> close(2)
@@Close a file handle
[section(.text.crt.io.access)]
[guard][alias(_close)] close:($fd_t fd) -> int;

%
@@>> access(2)
@@@param: TYPE: Set of `X_OK|W_OK|R_OK'
@@Test for access to the specified file `FILE', testing for `TYPE'
[cp][guard][alias(_access)][ATTR_WUNUSED][noexport]
[requires(defined(__CRT_AT_FDCWD) && $has_function(faccessat))]
[section(.text.crt.fs.property)]
access:([notnull] char const *file, int type) -> int {
	return faccessat(__CRT_AT_FDCWD, file, type, 0);
}

%
@@>> chdir(2)
@@Change the current working directory to `PATH'
[cp][guard][alias(_chdir)]
[section(.text.crt.fs.basic_property)]
chdir:([notnull] char const *path) -> int;

%
@@>> getcwd(2)
@@Return the path of the current working directory, relative to the filesystem root set by `chdir(2)'
[cp][guard][alias(_getcwd)]
[section(.text.crt.fs.basic_property)]
getcwd:([outp_opt(bufsize)] char *buf, size_t bufsize) -> char *;

%[default_impl_section(.text.crt.fs.modify)]

%
@@>> unlink(2)
@@Remove a file, symbolic link, device or FIFO referred to by `FILE'
[cp][guard][alias(_unlink)][noexport]
[requires(defined(__CRT_AT_FDCWD) && $has_function(unlinkat))]
unlink:([notnull] char const *file) -> int {
	return unlinkat(__CRT_AT_FDCWD, file, 0);
}

%
@@>> rmdir(2)
@@Remove a directory referred to by `PATH'
[cp][guard][alias(_rmdir)][noexport]
[requires(defined(__CRT_AT_FDCWD) && $has_function(unlinkat))]
rmdir:([notnull] char const *path) -> int {
	return unlinkat(__CRT_AT_FDCWD, path, 0x0200); /* AT_REMOVEDIR */
}

%[default_impl_section(.text.crt.fs.property)]

%
%#ifdef __USE_GNU
@@>> euidaccess(2)
@@@param: TYPE: Set of `X_OK|W_OK|R_OK'
@@Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids
[cp][alias(eaccess)][noexport][ATTR_WUNUSED]
[if(defined(__CRT_DOS)), alias(_access)]
[requires(defined(__CRT_AT_FDCWD) && $has_function(faccessat))]
euidaccess:([notnull] char const *file, int type) -> int {
	return faccessat(__CRT_AT_FDCWD, file, type, 0x0200); /* AT_EACCESS */
}

%
@@>> eaccess(2)
@@@param: TYPE: Set of `X_OK|W_OK|R_OK'
@@Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids
[cp][noexport][ATTR_WUNUSED]
eaccess:([notnull] char const *file, int type) -> int = euidaccess;

%#endif /* __USE_GNU */

%
%#ifdef __USE_ATFILE
@@>> faccessat(2)
@@@param: TYPE: Set of `X_OK|W_OK|R_OK'
@@Test for access to the specified file `DFD:FILE', testing for `TYPE'
[cp] faccessat:($fd_t dfd, [notnull] char const *file, int type, $atflag_t flags) -> int;

%[default_impl_section(.text.crt.fs.modify)]

%
@@>> fchownat(2)
@@Change the ownership of a given `DFD:FILE' to `GROUP:OWNER'
[cp] fchownat:($fd_t dfd, [notnull] char const *file, $uid_t owner, $gid_t group, $atflag_t flags) -> int;

%
@@>> linkat(2)
@@Create a hard link from `FROMFD:FROM', leading to `TOFD:TO'
[cp] linkat:($fd_t fromfd, [notnull] char const *from,
             $fd_t tofd, [notnull] char const *to, $atflag_t flags) -> int;

%
@@>> symlinkat(3)
@@Create a new symbolic link loaded with `LINK_TEXT' as link
@@text, at the filesystem location referred to by `TOFD:TARGET_PATH'
[cp] symlinkat:([notnull] char const *link_text, $fd_t tofd, [notnull] char const *target_path) -> int;

%[default_impl_section(.text.crt.fs.property)]

%
@@>> readlinkat(2)
@@Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
@@WARNING: This function is badly designed and will neither append a trailing
@@         NUL-character to the buffer, nor will it return the required buffer
@@         size. Instead, it will return the written size, and the caller must
@@         keep on over allocating until the function indicates that it didn't
@@         make use of the buffer in its entirety.
@@When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'.
[cp] readlinkat:($fd_t dfd, [notnull] char const *__restrict path,
                 [outp(buflen)] char *__restrict buf, size_t buflen) -> ssize_t;

%
%#ifdef __USE_KOS
@@>> freadlinkat(2)
@@Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
@@@param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE'
[cp] freadlinkat:($fd_t dfd, [notnull] char const *__restrict path,
                  [outp(buflen)] char *__restrict buf, size_t buflen, $atflag_t flags) -> ssize_t;
%#endif /* __USE_KOS */

%[default_impl_section(.text.crt.fs.modify)]

%
@@>> unlinkat(2)
@@Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME'
[cp] unlinkat:($fd_t dfd, [notnull] char const *name, $atflag_t flags) -> int;
%#endif /* __USE_ATFILE */

%
%
%#ifdef __USE_LARGEFILE64
@@>> lseek64(2)
@@Change the position of the file read/write pointer within a file referred to by `FD'
[off64_variant_of(lseek)][alias(_lseeki64)][noexport][requires($has_function(lseek32))]
[dependency_string(defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek))]
[section(.text.crt.io.large.seek)]
lseek64:($fd_t fd, $off64_t offset, int whence) -> $off64_t {
	return lseek32(fd, (__off32_t)offset, whence);
}
%#endif /* __USE_LARGEFILE64 */

%
%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
%#ifndef __PIO_OFFSET
%#ifdef __USE_KOS
%#define __PIO_OFFSET     __FS_TYPE(pos)
%#define __PIO_OFFSET64   __pos64_t
%#else
%#define __PIO_OFFSET     __FS_TYPE(off)
%#define __PIO_OFFSET64   __off64_t
%#endif
%#endif /* !__PIO_OFFSET */


%
@@>> pread(2)
@@Read data from a file at a specific offset
[cp][impl_prefix(
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif
#endif /* !__PIO_OFFSET */
)][impl_prefix(
#ifndef SEEK_SET
#   define SEEK_SET  0 /* Seek from beginning of file.  */
#   define SEEK_CUR  1 /* Seek from current position.  */
#   define SEEK_END  2 /* Seek from end of file.  */
#if defined(__USE_GNU) && (defined(__CRT_KOS) || defined(__CRT_GLC))
#   define SEEK_DATA 3 /* Seek to next data.  */
#   define SEEK_HOLE 4 /* Seek to next hole.  */
#endif /* __USE_GNU && (__CRT_KOS || __CRT_GLC) */
#endif
)][noexport]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(pread64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(pread)]
[requires(defined(__CRT_HAVE_pread64) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read)) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE__lseeki64))))]
[section(.text.crt.io.read)]
pread:($fd_t fd, [outp(bufsize)] void *buf, size_t bufsize, __PIO_OFFSET offset) -> ssize_t {
#ifdef __CRT_HAVE_pread64
	return pread64(fd, buf, bufsize, (@__PIO_OFFSET64@)offset);
#else
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off_t oldpos;
	ssize_t result;
	oldpos = lseek(fd, 0, SEEK_CUR);
	if __unlikely(oldpos < 0)
		return -1;
	if __unlikely(lseek(fd, (__FS_TYPE(@off@))offset, SEEK_SET) < 0)
		return -1;
	result = read(fd, buf, bufsize);
	lseek(fd, oldpos, SEEK_SET);
	return result;
#endif
}

@@>> pwrite(2)
@@Write data to a file at a specific offset
[cp][impl_prefix(
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif
#endif /* !__PIO_OFFSET */
)][impl_prefix(
#ifndef SEEK_SET
#   define SEEK_SET  0 /* Seek from beginning of file.  */
#   define SEEK_CUR  1 /* Seek from current position.  */
#   define SEEK_END  2 /* Seek from end of file.  */
#if defined(__USE_GNU) && (defined(__CRT_KOS) || defined(__CRT_GLC))
#   define SEEK_DATA 3 /* Seek to next data.  */
#   define SEEK_HOLE 4 /* Seek to next hole.  */
#endif /* __USE_GNU && (__CRT_KOS || __CRT_GLC) */
#endif
)][noexport]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(pwrite64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(pwrite)]
[section(.text.crt.io.write)]
[requires(defined(__CRT_HAVE_pwrite64) || ((defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write)) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE__lseeki64))))]
pwrite:($fd_t fd, [inp(bufsize)] void const *buf, size_t bufsize, __PIO_OFFSET offset) -> ssize_t {
#ifdef __CRT_HAVE_pwrite64
	return pwrite64(fd, buf, bufsize, (__PIO_OFFSET64)offset);
#else
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off_t oldpos;
	ssize_t result;
	oldpos = lseek(fd, 0, SEEK_CUR);
	if __unlikely(oldpos < 0)
		return -1;
	if __unlikely(lseek(fd, (off_t)offset, SEEK_SET) < 0)
		return -1;
	result = write(fd, buf, bufsize);
	lseek(fd, oldpos, SEEK_SET);
	return result;
#endif
}


%
%#ifdef __USE_KOS
@@>> preadall(3)
@@Same as `readall(3)', but using `pread(2)' instead of `read()'
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(preadall64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(preadall)]
[requires($has_function(preadall64))]
[dependency_include(<parts/errno.h>)]
[cp][section(.text.crt.io.read)]
preadall:($fd_t fd, [outp(bufsize)] void *buf, size_t bufsize, __PIO_OFFSET offset) -> ssize_t {
	return preadall64(fd, buf, bufsize, (__PIO_OFFSET64)offset);
}

@@>> pwriteall(3)
@@Same as `writeall(3)', but using `pwrite(2)' instead of `write()'
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(pwriteall64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(pwriteall)]
[requires($has_function(pwriteall64))]
[dependency_include(<parts/errno.h>)]
[cp][section(.text.crt.io.write)]
pwriteall:($fd_t fd, [inp(bufsize)] void const *buf, size_t bufsize, __PIO_OFFSET offset) -> ssize_t {
	return pwriteall64(fd, buf, bufsize, (__PIO_OFFSET64)offset);
}
%#endif /* __USE_KOS */



%
%#ifdef __USE_LARGEFILE64

[section(.text.crt.io.read)][cp][ignore] pread32:($fd_t fd, [outp(bufsize)] void *buf, size_t bufsize, $pos32_t offset) -> ssize_t = pread?;
[section(.text.crt.io.write)][cp][ignore] pwrite32:($fd_t fd, [inp(bufsize)] void const *buf, size_t bufsize, $pos32_t offset) -> ssize_t = pwrite?;

@@>> pread64(2)
@@Read data from a file at a specific offset
[off64_variant_of(pread)][cp][noexport][section(.text.crt.io.large.read)]
[requires(defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read)) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE__lseeki64))))]
pread64:($fd_t fd, [outp(bufsize)] void *buf, size_t bufsize, __PIO_OFFSET64 offset) -> ssize_t {
#if defined(__CRT_HAVE_pread) && ((!defined(__CRT_HAVE__lseeki64) && !defined(__CRT_HAVE_lseek64)) || (!defined(__CRT_HAVE_read) && !defined(__CRT_HAVE__read)))
	return pread32(fd, buf, bufsize, (pos32_t)offset);
#elif defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek64)
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off64_t oldpos;
	ssize_t result;
	oldpos = lseek64(fd, 0, SEEK_CUR);
	if __unlikely(oldpos < 0)
		return -1;
	if __unlikely(lseek64(fd, (off64_t)offset, SEEK_SET) < 0)
		return -1;
	result = read(fd, buf, bufsize);
	lseek64(fd, oldpos, SEEK_SET);
	return result;
#else
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off32_t oldpos;
	ssize_t result;
	oldpos = lseek32(fd, 0, SEEK_CUR);
	if __unlikely(oldpos < 0)
		return -1;
	if __unlikely(lseek32(fd, (off32_t)offset, SEEK_SET) < 0)
		return -1;
	result = read(fd, buf, bufsize);
	lseek32(fd, oldpos, SEEK_SET);
	return result;
#endif
}

@@>> pwrite64(2)
@@Write data to a file at a specific offset
[off64_variant_of(pwrite)][cp][noexport][section(.text.crt.io.large.write)]
[requires(defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write)) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE__lseeki64))))]
pwrite64:($fd_t fd, [inp(bufsize)] void const *buf, size_t bufsize, __PIO_OFFSET64 offset) -> ssize_t {
#if defined(__CRT_HAVE_pwrite) && ((!defined(__CRT_HAVE__lseeki64) && !defined(__CRT_HAVE_lseek64)) || (!defined(__CRT_HAVE_write) && !defined(__CRT_HAVE__write)))
	return pwrite32(fd, buf, bufsize, (pos32_t)offset);
#elif defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_lseek64)
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off64_t oldpos;
	ssize_t result;
	oldpos = lseek64(fd, 0, SEEK_CUR);
	if __unlikely(oldpos < 0)
		return -1;
	if __unlikely(lseek64(fd, (off64_t)offset, SEEK_SET) < 0)
		return -1;
	result = write(fd, buf, bufsize);
	lseek64(fd, oldpos, SEEK_SET);
	return result;
#else
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off32_t oldpos;
	ssize_t result;
	oldpos = lseek32(fd, 0, SEEK_CUR);
	if __unlikely(oldpos < 0)
		return -1;
	if __unlikely(lseek32(fd, (off32_t)offset, SEEK_SET) < 0)
		return -1;
	result = write(fd, buf, bufsize);
	lseek32(fd, oldpos, SEEK_SET);
	return result;
#endif
}

%
%#ifdef __USE_KOS
@@>> preadall64(3)
@@Same as `readall(3)', but using `pread64(2)' instead of `read()'
[off64_variant_of(preadall)][cp][requires($has_function(pread64))][section(.text.crt.io.large.read)]
preadall64:($fd_t fd, [inp(bufsize)] void *buf, size_t bufsize, __PIO_OFFSET64 offset) -> ssize_t {
	ssize_t result, temp;
	result = pread64(fd, buf, bufsize, offset);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = pread64(fd,
			               (byte_t *)buf + (size_t)result,
			               bufsize - (size_t)result,
			               offset + (size_t)result);
			if (temp <= 0) {
				result = temp;
				break;
			}
			result += temp;
			if ((size_t)result >= bufsize)
				break;
		}
	}
	return result;
}

@@>> pwriteall64(3)
@@Same as `writeall(3)', but using `pwrite64(2)' instead of `write()'
[off64_variant_of(pwriteall)][cp][requires($has_function(pwrite64))][section(.text.crt.io.large.write)]
pwriteall64:($fd_t fd, [inp(bufsize)] void *buf, size_t bufsize, __PIO_OFFSET64 offset) -> ssize_t {
	ssize_t result, temp;
	result = pwrite64(fd, buf, bufsize, offset);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on writing */
		for (;;) {
			temp = pwrite64(fd,
			                (byte_t *)buf + (size_t)result,
			                bufsize - (size_t)result,
			                offset + (size_t)result);
			if (temp <= 0) {
				result = temp;
				break;
			}
			result += temp;
			if ((size_t)result >= bufsize)
				break;
		}
	}
	return result;
}
%#endif /* __USE_KOS */

%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

%
%
%#ifdef __USE_GNU
%{
#ifndef __environ_defined
#define __environ_defined 1
#undef environ
#if defined(__CRT_HAVE_environ)
__LIBC char **environ;
#define environ environ
#elif defined(__CRT_HAVE__environ) && !defined(__NO_ASMNAME)
__LIBC char **environ __ASMNAME("_environ");
#define environ environ
#elif defined(__CRT_HAVE__environ)
#undef _environ
#ifndef ___environ_defined
#define ___environ_defined 1
__LIBC char **_environ;
#endif /* !___environ_defined */
#define environ _environ
#elif defined(__CRT_HAVE___p__environ)
#ifndef ____p__environ_defined
#define ____p__environ_defined 1
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#endif /* !____p__environ_defined */
#define environ   (*__p__environ())
#else
#undef __environ_defined
#endif
#endif /* !__environ_defined */
}


[noexport]
[requires($has_function(pipe))]
[section(.text.crt.io.access)]
pipe2:([notnull] $fd_t pipedes[2], $oflag_t flags) -> int {
	(void)flags;
	return pipe(pipedes);
}

[noexport]
[requires($has_function(dup2))]
[section(.text.crt.io.access)]
dup3:($fd_t oldfd, $fd_t newfd, $oflag_t flags) -> $fd_t {
	return newfd != oldfd ? dup2(oldfd, newfd) : -1;
}

[cp][ATTR_WUNUSED][ATTR_MALLOC][noexport]
[requires($has_function(getcwd))]
[section(.text.crt.fs.basic_property)]
get_current_dir_name:() -> char * {
	return getcwd(NULL, 0);
}

[cp][user][noexport][section(.text.crt.fs.modify)]
syncfs:($fd_t fd) -> int {
	(void)fd;
	/* NO-OP */
	return 0;
}

%[default_impl_section(.text.crt.sched.user)]

group_member:($gid_t gid) -> int;
getresuid:($uid_t *ruid, $uid_t *euid, $uid_t *suid) -> int;
getresgid:($gid_t *rgid, $gid_t *egid, $gid_t *sgid) -> int;
setresuid:($uid_t ruid, $uid_t euid, $uid_t suid) -> int;
setresgid:($gid_t rgid, $gid_t egid, $gid_t sgid) -> int;
%#endif /* __USE_GNU */

%#if (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)) || \
%     defined(__USE_MISC)

@@Hidden function exported by DOS that allows for millisecond precision
[section(.text.crt.dos.system.utility)]
[cp][alias(delay)][ignore] __crtSleep:(__UINT32_TYPE__ msecs);


@@Sleep for `useconds' microseconds (1/1.000.000 seconds)
[section(.text.crt.system.utility)]
[cp][requires($has_function(__crtSleep))]
usleep:($useconds_t useconds) -> int {
	__crtSleep(useconds / 1000l); /*USEC_PER_MSEC*/
	return 0;
}

[cp][ATTR_DEPRECATED("Use getcwd()")]
[requires($has_function(getcwd))]
[section(.text.crt.fs.basic_property)]
getwd:([notnull] char *buf) -> char * {
	return getcwd(buf, (size_t)-1);
}

[section(.text.crt.system.utility)]
ualarm:($useconds_t value, $useconds_t interval) -> $useconds_t;

%
@@>> vfork(2)
@@Same as `fork(2)', but suspend the calling process until the child
@@process either calls `exit(2)' or one of the many `exec(2)' functions
[section(.text.crt.sched.access)]
[ATTR_RETURNS_TWICE][ATTR_WUNUSED] vfork:() -> $pid_t;
%#endif

%
@@>> fchown(2)
@@Change the ownership of a given `FD' to `GROUP:OWNER'
[section(.text.crt.fs.modify)]
[cp] fchown:($fd_t fd, $uid_t owner, $gid_t group) -> int;

%
@@>> chdir(2)
@@Change the current working directory to `PATH'
[section(.text.crt.fs.basic_property)]
[cp] fchdir:($fd_t fd) -> int;

%
@@>> getpgid(2)
@@Return the ID of the process group associated with `PID's process.
@@(That is the TID of the leader of the process group of `PID's leader)
@@THREAD[PID]->LEADER->GROUP_LEADER->PID
@@When `PID' is ZERO(0), use `gettid()' for it instead
[section(.text.crt.sched.user)]
[ATTR_WUNUSED] getpgid:($pid_t pid) -> $pid_t;

%
@@>> getsid(2)
@@Return the ID of the session which a process `PID' is apart of.
@@return THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID;
[section(.text.crt.sched.process)]
[ATTR_WUNUSED] getsid:($pid_t pid) -> $pid_t;

%
@@>> lchown(2)
@@Change the ownership of a given `FILE' to `GROUP:OWNER',
@@but don't reference it if that file is a symbolic link
[cp][noexport]
[requires(defined(__CRT_AT_FDCWD) && $has_function(fchownat))]
[section(.text.crt.fs.modify)]
lchown:([notnull] char const *file, $uid_t owner, $gid_t group) -> int {
	return fchownat(__CRT_AT_FDCWD, file, owner, group, 0x0100); /* AT_SYMLINK_NOFOLLOW */
}


%
%{
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif
#endif /* !__PIO_OFFSET */
}

%
@@>> truncate(2)
@@Truncate the given file `FILE' to a length of `LENGTH'
[impl_prefix(
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif
#endif /* !__PIO_OFFSET */
)][noexport]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(truncate64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(truncate)]
[section(.text.crt.fs.modify)]
[requires(defined(__CRT_HAVE_truncate64) || defined(__CRT_HAVE_truncate) || ((defined(__CRT_HAVE_open) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE__open)) && (defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64))))]
truncate:([notnull] char const *file, __PIO_OFFSET length) -> int {
#if defined(__CRT_HAVE_truncate64)
	return truncate64(file, (__PIO_OFFSET64)length);
#elif defined(__CRT_HAVE_truncate)
#ifdef __USE_KOS
	return truncate32(file, (__pos32_t)length);
#else /* __USE_KOS */
	return truncate32(file, (__off32_t)length);
#endif /* !__USE_KOS */
#else
	int result;
	fd_t fd;
	fd = open(file, 1); /* O_WRONLY */
	if __unlikely(fd < 0)
		return -1;
	result = ftruncate(fd, length);
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close)
	close(fd);
#endif
	return result;
#endif
}

[doc_alias(truncate)][section(.text.crt.fs.modify)]
[ignore] truncate32:([notnull] char const *file, $pos32_t length) -> int = truncate?;

%
%#ifdef __USE_LARGEFILE64
@@>> truncate64(2)
@@Truncate the given file `FILE' to a length of `LENGTH'
[off64_variant_of(truncate)][impl_prefix(
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif
#endif /* !__PIO_OFFSET */
)][noexport]
[section(.text.crt.fs.modify)]
[requires(defined(__CRT_HAVE_truncate) || ((defined(__CRT_HAVE_open) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE__open)) && (defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64))))]
truncate64:([notnull] char const *file, __PIO_OFFSET64 length) -> int {
#if defined(__CRT_HAVE_truncate) && (!defined(__CRT_HAVE_open) || !defined(__CRT_HAVE_open64) || !defined(__CRT_HAVE__open) || (!defined(__CRT_HAVE__chsize_s) && !defined(__CRT_HAVE_ftruncate64)))
	return truncate32(file, (__PIO_OFFSET)length);
#else
	int result;
	$fd_t fd;
#if defined(__CRT_HAVE_open64)
	fd = open64(file, 1); /* O_WRONLY */
#else
	fd = open(file, 1); /* O_WRONLY */
#endif
	if __unlikely(fd < 0)
		return -1;
	result = ftruncate64(fd, length);
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close)
	close(fd);
#endif
	return result;
#endif
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */
%
%#ifdef __USE_XOPEN2K8

%
@@>> fexecve(2)
@@Replace the calling process with the application image referred to by `FD' and
@@execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP'
[cp][guard][argument_names(fd, ___argv, ___envp)][section(.text.crt.fs.exec.exec)]
fexecve:($fd_t fd, [notnull] @__TARGV@, [notnull] @__TENVP@) -> int;

%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_GNU
%[insert:extern(execvpe)]
%#endif /* __USE_GNU */


%
%#if defined(__USE_MISC) || defined(__USE_XOPEN)
[section(.text.crt.sched.param)][noexport][user]
nice:(int inc) -> int {
	(void)inc;
	/* It should be sufficient to emulate this is a no-op. */
	return 0;
}
%#endif /* __USE_MISC || __USE_XOPEN */

%
%[insert:extern(_exit)]


%
%#ifdef __USE_POSIX2
[section(.text.crt.system.configuration)]
confstr:(int name, char *buf, size_t buflen) -> size_t;

%
%[push_macro @undef { optarg optind opterr optopt }]%{
#ifdef __CRT_HAVE_optarg
__LIBC char *optarg;
#endif
#ifdef __CRT_HAVE_optind
__LIBC int optind;
#endif
#ifdef __CRT_HAVE_opterr
__LIBC int opterr;
#endif
#ifdef __CRT_HAVE_optopt
__LIBC int optopt;
#endif
}
%[pop_macro]
%


[guard][ATTR_WUNUSED][section(.text.crt.application.options)][noexport][nouser]
[if(defined(__USE_POSIX2) && !defined(__USE_POSIX_IMPLICITLY) && !defined(__USE_GNU)), preferred_alias(__posix_getopt)]
getopt:(int argc, char *const argv[], char const *shortopts) -> int;

%#endif /* __USE_POSIX2 */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)

%
@@>> sync(2)
@@Synchronize all disk operations of all mounted file systems and flush
@@unwritten buffers down to the hardware layer, ensuring that modifications
@@made become visible on the underlying, persistent media
[section(.text.crt.fs.modify)]
[cp][user][noexport] sync:() {
	/* NO-OP */
}

%
@@>> setpgrp(3)
@@Move the calling process into its own process group.
@@Equivalent to `setpgid(0, 0)'
[section(.text.crt.sched.process)]
setpgrp:() -> int;

%
%/* ... */
[section(.text.crt.sched.user)]
setreuid:($uid_t ruid, $uid_t euid) -> int;

%
%/* ... */
[section(.text.crt.sched.user)]
setregid:($gid_t rgid, $gid_t egid) -> int;

%
%/* ... */
[section(.text.crt.system.configuration)]
[ATTR_WUNUSED] gethostid:() -> long int;

%#if defined(__USE_MISC) || !defined(__USE_XOPEN2K)
@@>> getpagesize(3)
@@Return the size of a PAGE (in bytes)
[section(.text.crt.system.configuration)]
[ATTR_CONST][ATTR_WUNUSED]
[dependency_include(<hybrid/__limits.h>)]
getpagesize:() -> int {
#ifdef __SIZEOF_PAGE__
	return __SIZEOF_PAGE__;
#else
	return 4096;
#endif
}

%
%/* ... */
[section(.text.crt.system.configuration)]
[ATTR_CONST][ATTR_WUNUSED] getdtablesize:() -> int {
#if defined(__KOS__)
	return 0x7fffffff; /* INT_MAX */
#elif defined(__linux__) || defined(__linux) || defined(linux)
	return 0x10000;    /* UINT16_MAX + 1 */
#else
	return 256;        /* UINT8_MAX + 1 */
#endif
}

%#endif /* __USE_MISC || !__USE_XOPEN2K */
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%
%#ifdef __USE_XOPEN2K

@@>> seteuid(2)
@@Set the effective user ID of the calling process
@@@return: 0 : Success
@@@return: -1: [errno=EINVAL] : The given `EUID' is invalid
@@@return: -1: [errno=EPERM]  : The current user is not privileged
[section(.text.crt.sched.user)]
seteuid:($uid_t euid) -> int;

%
@@>> setegid(2)
@@Set the effective group ID of the calling process
@@@return: 0 : Success
@@@return: -1: [errno=EINVAL] : The given `EGID' is invalid
@@@return: -1: [errno=EPERM]  : The current user is not privileged
[section(.text.crt.sched.user)]
setegid:($gid_t egid) -> int;

%#endif /* __USE_XOPEN2K */

%
%#if defined(__USE_MISC) || \
%   (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_UNIX98))

%/* ... */
[section(.text.crt.io.tty)]
[ATTR_WUNUSED] ttyslot:() -> int;

%#endif

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)

@@>> symlink(3)
@@Create a new symbolic link loaded with `LINK_TEXT' as link
@@text, at the filesystem location referred to by `TARGET_PATH'.
@@Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)'
[cp][noexport][section(.text.crt.fs.modify)]
[requires(defined(__CRT_AT_FDCWD) && $has_function(symlinkat))]
symlink:([notnull] char const *link_text, [notnull] char const *target_path) -> int {
	/* TODO: Header-implementation for `symlink()' on DOS (using the windows API) */
	return symlinkat(link_text, __CRT_AT_FDCWD, target_path);
}

%
@@>> readlink(3)
@@Read the text of a symbolic link under `PATH' into the provided buffer.
@@Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
@@WARNING: This function is badly designed and will neither append a trailing
@@         NUL-character to the buffer, nor will it return the required buffer
@@         size. Instead, it will return the written size, and the caller must
@@         keep on over allocating until the function indicates that it didn't
@@         make use of the buffer in its entirety.
@@When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'
[cp][noexport]
[requires(defined(__CRT_AT_FDCWD) && $has_function(readlinkat))]
[section(.text.crt.fs.property)]
readlink:([notnull] char const *__restrict path,
          [outp(buflen)] char *__restrict buf, size_t buflen) -> ssize_t {
	return readlinkat(__CRT_AT_FDCWD, path, buf, buflen);
}

%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

%
%#if defined(__USE_REENTRANT) || defined(__USE_POSIX199506)
[cp][section(.text.crt.io.tty)]
getlogin_r:([outp(name_len)] char *name, size_t name_len) -> int;
%#endif /* __USE_REENTRANT || __USE_POSIX199506 */

%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
@@>> gethostname(3)
@@Return the name assigned to the hosting machine, as set by `sethostname(2)'
[section(.text.crt.system.configuration)]
gethostname:([outp(buflen)] char *name, size_t buflen) -> int;
%#endif /* __USE_UNIX98 || __USE_XOPEN2K */

%
%#ifdef __USE_MISC
%/* ... */
[section(.text.crt.io.tty)]
setlogin:([nonnull] char const *name) -> int;
%
@@>> sethostname(2)
@@Set the name of the hosting machine
[section(.text.crt.system.configuration)]
sethostname:([inp(len)] char const *name, size_t len) -> int;

%
%/* ... */
[section(.text.crt.system.configuration)]
sethostid:(long int id) -> int;

%
@@>> getdomainname(3)
@@Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)'
[section(.text.crt.system.configuration)]
getdomainname:([outp(buflen)] char *name, size_t buflen) -> int;

%
@@>> setdomainname(2)
@@Set the name of the hosting machine's domain
[section(.text.crt.system.configuration)]
setdomainname:([inp(len)] char const *name, size_t len) -> int;

%
%/* ... */
[section(.text.crt.io.tty)]
vhangup:() -> int;

%
%/* ... */
[section(.text.crt.system.utility)]
profil:([nonnull] unsigned short int *sample_buffer,
        size_t size, size_t offset, unsigned int scale) -> int;

%
%/* ... */
[section(.text.crt.database.shell)]
[cp][ATTR_WUNUSED] getusershell:() -> char *;

%
%/* ... */
[section(.text.crt.database.shell)]
endusershell:();

%
%/* ... */
[section(.text.crt.database.shell)]
[cp] setusershell:();

%
%/* ... */
[section(.text.crt.system.utility)]
[cp] daemon:(int nochdir, int noclose) -> int;

%
%/* ... */
[section(.text.crt.fs.modify)]
[cp] revoke:([nonnull] char const *file) -> int;

%
%/* ... */
[section(.text.crt.fs.modify)]
[cp] acct:([nullable] char const *name) -> int;

[cp][section(.text.crt.system.utility)]
syscall:(long int sysno, ...) -> long int;

%#ifdef __USE_KOS
[cp][section(.text.crt.system.utility)][preferred_alias(syscall)]
syscall64:(__syscall_ulong_t sysno, ...) -> __LONG64_TYPE__;
%#endif /* __USE_KOS */

%#endif /* __USE_MISC */

%
%#if defined(__USE_MISC) || \
%   (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
@@>> chroot(2)
@@Change the root directory of the calling `CLONE_FS' group of threads
@@(usually the process) to a path that was previously address by `PATH'
[section(.text.crt.fs.utility)]
[cp] chroot:([nonnull] char const *__restrict path) -> int;

%
%/* ... */
[cp][ATTR_WUNUSED][section(.text.crt.io.tty)]
getpass:([nonnull] char const *__restrict prompt) -> char *;
%#endif /* ... */

%
%#if defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)

@@>> ftruncate(2)
@@Truncate the given file `FD' to a length of `LENGTH'
[section(.text.crt.io.write)]
[ignore] ftruncate32:($fd_t fd, __pos32_t length) -> int = ftruncate?;

@@>> ftruncate(2)
@@Truncate the given file `FD' to a length of `LENGTH'
[alias(_chsize_s)][noexport]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(ftruncate64, _chsize_s)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(ftruncate, _chsize, chsize)]
[requires(defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s))]
[section(.text.crt.io.write)]
ftruncate:($fd_t fd, __PIO_OFFSET length) -> int {
#if defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE__chsize)
	return ftruncate32(fd, (__pos32_t)length);
#else
	return ftruncate64(fd, (__pos64_t)length);
#endif
}

%
%#ifdef __USE_LARGEFILE64
@@>> ftruncate64(2)
@@Truncate the given file `FD' to a length of `LENGTH'
[off64_variant_of(ftruncate)][impl_prefix(
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif
#endif /* !__PIO_OFFSET */
)][alias(_chsize_s)][noexport]
[requires(defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE__chsize))]
[section(.text.crt.io.large.write)]
ftruncate64:($fd_t fd, __PIO_OFFSET64 length) -> int {
	return ftruncate32(fd, (pos32_t)length);
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

%
%#if (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K)) || \
%     defined(__USE_MISC)
@@>> brk(2), sbrk(2)
@@Change the program break, allowing for a rudimentary implementation of a heap.
@@It is recommended to use the much more advanced functions found in <sys/mman.h> instead
[section(.text.crt.heap.utility)] brk:(void *addr) -> int;
[section(.text.crt.heap.utility)] sbrk:(intptr_t delta) -> void *;
%#endif

%
%#if defined(__USE_POSIX199309) || defined(__USE_UNIX98)
@@>> fdatasync(2)
@@Synchronize only the data of a file (not its descriptor which contains
@@timestamps, and its size), meaning that changes are written to disk
[section(.text.crt.io.sync)][cp][user] fdatasync:($fd_t fd) -> int = fsync;
%#endif /* __USE_POSIX199309 || __USE_UNIX98 */

%
%#ifdef __USE_XOPEN
%[insert:extern(crypt)]
%[insert:extern(encrypt)]

%
@@Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
@@exchanging the order of even and odd bytes ("123456" --> "214365")
@@When `n_bytes <= 1', don't do anything and return immediately
[alias(_swab)][guard]
[section(.text.crt.string.memory)]
swab:([nonnull] void const *__restrict from,
      [nonnull] void *__restrict to, int n_bytes) {
	n_bytes &= ~1;
	while (n_bytes >= 2) {
		byte_t a, b;
		a = ((byte_t *)from)[--n_bytes];
		b = ((byte_t *)from)[--n_bytes];
		((byte_t *)to)[n_bytes+0] = a;
		((byte_t *)to)[n_bytes+1] = b;
	}
}

%#endif /* __USE_XOPEN */

%
%#if defined(_ALL_SOURCE) || \
%   (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
%/* ... */
[section(.text.crt.io.tty)]
[guard] ctermid:(char *s) -> char *;
%#endif /* _ALL_SOURCE || (__USE_XOPEN && !__USE_XOPEN2K) */

%
%#if defined(__USE_REENTRANT)
@@Same as `ctermid', but return `NULL' when `S' is `NULL'
[section(.text.crt.io.tty)]
[requires($has_function(ctermid))][noexport][user][same_impl]
ctermid_r:([nullable] char *s) -> char * {
	return s ? ctermid(s) : NULL;
}
%#endif /* __USE_REENTRANT */

%
@@>> sysconf(2)
@@@param: NAME: One of `_SC_*' from <bits/confname.h>
@@Return a system configuration value `NAME'
[section(.text.crt.system.configuration)]
[ATTR_WUNUSED][export_alias(_sysconf,__sysconf)]
sysconf:(int name) -> long int;


%#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_POSIX))
%#ifndef F_LOCK
%#define F_ULOCK 0 /* Unlock a previously locked region. */
%#define F_LOCK  1 /* Lock a region for exclusive use. */
%#define F_TLOCK 2 /* Test and lock a region for exclusive use. */
%#define F_TEST  3 /* Test a region for other processes locks. */
%#endif /* !F_LOCK */
%[insert:extern(lockf)]
%#ifdef __USE_LARGEFILE64
%[insert:extern(lockf64)]
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_POSIX) */
%
%
%{
#ifdef __USE_GNU
#ifdef __COMPILER_HAVE_TYPEOF
#define TEMP_FAILURE_RETRY(expression) \
	__XBLOCK({ __typeof__(expression) __result; \
	           do __result = (expression); \
	           while (__result == -1L && errno == EINTR); \
	           __XRETURN __result; }))
#else /* __COMPILER_HAVE_TYPEOF */
#define TEMP_FAILURE_RETRY(expression) \
	__XBLOCK({ long int __result; \
	           do __result = (long int)(expression); \
	           while (__result == -1L && errno == EINTR); \
	           __XRETURN __result; }))
#endif /* !__COMPILER_HAVE_TYPEOF */
#endif /* __USE_GNU */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_UNISTD_H)
#include <parts/wchar/unistd.h>
#endif
#endif /* __USE_KOS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_UNISTD_H)
#include <parts/uchar/unistd.h>
#endif
#endif /* __USE_UTF */

}

