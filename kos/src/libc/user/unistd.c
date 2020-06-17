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
#ifndef GUARD_LIBC_USER_UNISTD_C
#define GUARD_LIBC_USER_UNISTD_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/host.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <asm/pagesize.h>
#include <kos/syscalls.h>
#include <sys/mman.h>
#include <sys/param.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <sys/utsname.h>

#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <limits.h>
#include <paths.h>
#include <pwd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <termios.h>
#include <unistd.h>

#include "../libc/capture-varargs.h"
#include "../libc/dl.h"
#include "../libc/globals.h"
#include "stdlib.h"
#include "unistd.h"

#ifdef __ARCH_PAGESIZE
#define OS_PAGESIZE __ARCH_PAGESIZE
#else /* __ARCH_PAGESIZE */
#define OS_PAGESIZE getpagesize()
#endif /* !__ARCH_PAGESIZE */

DECL_BEGIN

INTERN ATTR_SECTION(".bss.crt.fs.environ.lock")
struct atomic_rwlock libc_environ_lock = ATOMIC_RWLOCK_INIT;

DEFINE_PUBLIC_ALIAS(__p__environ, libc_p_environ);
INTERN WUNUSED ATTR_CONST ATTR_RETNONNULL
ATTR_SECTION(".text.crt.dos.fs.environ.__p__environ") char ***
NOTHROW(LIBCCALL libc_p_environ)(void) {
	return &environ;
}


/*[[[start:implementation]]]*/

/*[[[head:libc_execv,hash:CRC-32=0xf45029ad]]]*/
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_execv)(char const *__restrict path,
                                 __TARGV)
/*[[[body:libc_execv]]]*/
{
	errno_t result;
	atomic_rwlock_read(&libc_environ_lock);
	result = sys_execve(path,
	                    (char *const *)___argv,
	                    (char *const *)environ);
	atomic_rwlock_endread(&libc_environ_lock);
	return (int)libc_seterrno(-result);
}
/*[[[end:libc_execv]]]*/

/*[[[head:libc_execve,hash:CRC-32=0x4dda358b]]]*/
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBCCALL libc_execve)(char const *__restrict path,
                                  __TARGV,
                                  __TENVP)
/*[[[body:libc_execve]]]*/
{
	errno_t result;
	result = sys_execve(path,
	                    (char *const *)___argv,
	                    (char *const *)___envp);
	return (int)libc_seterrno(-result);
}
/*[[[end:libc_execve]]]*/

/*[[[head:libc_execvp,hash:CRC-32=0xfa2c821f]]]*/
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_execvp)(char const *__restrict file,
                                  __TARGV)
/*[[[body:libc_execvp]]]*/
{
	int result;
	atomic_rwlock_read(&libc_environ_lock);
	result = execvpe(file, ___argv, environ);
	atomic_rwlock_endread(&libc_environ_lock);
	return result;
}
/*[[[end:libc_execvp]]]*/

/*[[[head:libd_execl,hash:CRC-32=0x3d5d8b3]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd_execl)(char const *__restrict path,
                                  char const *args,
                                  ...)
/*[[[body:libd_execl]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	return execv(path,
	             (char const *const *)&args);
#else
	va_list vargs;
	char **vector;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char, vector, vargs, args);
	va_end(vargs);
	return execv(path,
	             (char const *const *)vector);
#endif
}
#endif /* MAGIC:impl_if */
/*[[[end:libd_execl]]]*/


/*[[[head:libc_execl,hash:CRC-32=0x4d377473]]]*/
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBCCALL libc_execl)(char const *__restrict path,
                                  char const *args,
                                  ...)
/*[[[body:libc_execl]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	return execv(path,
	             (char const *const *)&args);
#else
	va_list vargs;
	char **vector;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char, vector, vargs, args);
	va_end(vargs);
	return execv(path,
	             (char const *const *)vector);
#endif
}
/*[[[end:libc_execl]]]*/

/*[[[head:libd_execle,hash:CRC-32=0xfe7afc2b]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd_execle)(char const *__restrict path,
                                   char const *args,
                                   ...)
/*[[[body:libd_execle]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	char ***penvp = (char ***)&args;
	while (*penvp++)
		; /* Envp is located 1 after the first NULL-entry */
	return execve(path,
	              (char const *const *)&args,
	              (char const *const *)*penvp);
#else
	va_list vargs;
	char **vector, **envp;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char, vector, vargs, args);
	envp = va_arg(vargs, char **);
	va_end(vargs);
	return execve(path,
	              (char const *const *)vector,
	              (char const *const *)envp);
#endif
}
#endif /* MAGIC:impl_if */
/*[[[end:libd_execle]]]*/

/*[[[head:libc_execle,hash:CRC-32=0xbc42feab]]]*/
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBCCALL libc_execle)(char const *__restrict path,
                                   char const *args,
                                   ...)
/*[[[body:libc_execle]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	char ***penvp = (char ***)&args;
	while (*penvp++)
		; /* Envp is located 1 after the first NULL-entry */
	return execve(path,
	              (char const *const *)&args,
	              (char const *const *)*penvp);
#else
	va_list vargs;
	char **vector, **envp;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char, vector, vargs, args);
	envp = va_arg(vargs, char **);
	va_end(vargs);
	return execve(path,
	              (char const *const *)vector,
	              (char const *const *)envp);
#endif
}
/*[[[end:libc_execle]]]*/

/*[[[head:libd_execlp,hash:CRC-32=0xdb82a92c]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd_execlp)(char const *__restrict file,
                                   char const *args,
                                   ...)
/*[[[body:libd_execlp]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	return execvp(file,
	              (char const *const *)&args);
#else
	va_list vargs;
	char **vector;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char, vector, vargs, args);
	va_end(vargs);
	return execvp(file,
	              (char const *const *)vector);
#endif
}
#endif /* MAGIC:impl_if */
/*[[[end:libd_execlp]]]*/

/*[[[head:libc_execlp,hash:CRC-32=0xb9042683]]]*/
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBCCALL libc_execlp)(char const *__restrict file,
                                   char const *args,
                                   ...)
/*[[[body:libc_execlp]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	return execvp(file,
	              (char const *const *)&args);
#else
	va_list vargs;
	char **vector;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char, vector, vargs, args);
	va_end(vargs);
	return execvp(file,
	              (char const *const *)vector);
#endif
}
/*[[[end:libc_execlp]]]*/

/*[[[head:libc_execvpe,hash:CRC-32=0xe172c175]]]*/
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBCCALL libc_execvpe)(char const *__restrict file,
                                   __TARGV,
                                   __TENVP)
/*[[[body:libc_execvpe]]]*/
{
	/* Search $PATH */
	size_t taillen = strlen(file);
	char *env_path = getenv("PATH");
	if (!env_path || !*env_path) {
		libc_seterrno(ENOENT);
	} else {
		char *fullpath        = NULL;
		size_t fullpath_alloc = 0;
		int sep               = GET_PATHLIST_SEP();
		for (;;) {
			char *path_end  = strchrnul(env_path, sep);
			size_t seg_len  = (size_t)(path_end - env_path);
			size_t full_len = seg_len + taillen;
			bool need_trail = !ISSEP(path_end[-1]);
			if (need_trail)
				++full_len;
			if (full_len > fullpath_alloc) {
				char *new_fullpath;
				new_fullpath = (char *)realloc(fullpath,
				                               (full_len + 1) *
				                               sizeof(char));
				if unlikely(!new_fullpath)
					break;
				fullpath       = new_fullpath;
				fullpath_alloc = full_len + 1;
			}
			/* Construct the full-path string. */
			memcpy(fullpath, env_path, seg_len, sizeof(char));
			if (need_trail) {
				fullpath[seg_len] = '/';
				memcpy(fullpath + seg_len + 1, file, taillen, sizeof(char));
			} else {
				memcpy(fullpath + seg_len, file, taillen, sizeof(char));
			}
			fullpath[full_len] = '\0';
			execve(fullpath, ___argv, ___envp);
			if (!*path_end)
				break;
			env_path = path_end + 1;
		}
		free(fullpath);
	}
	return -1;
}
/*[[[end:libc_execvpe]]]*/

/*[[[head:libd_execlpe,hash:CRC-32=0x91c35d7e]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd_execlpe)(char const *__restrict file,
                                    char const *args,
                                    ...)
/*[[[body:libd_execlpe]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	char ***penvp = (char ***)&args;
	while (*penvp++)
		; /* Envp is located 1 after the first NULL-entry */
	return execvpe(file,
	               (char const *const *)&args,
	               (char const *const *)*penvp);
#else
	va_list vargs;
	char **vector, **envp;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char, vector, vargs, args);
	envp = va_arg(vargs, char **);
	va_end(vargs);
	return execvpe(file,
	               (char const *const *)vector,
	               (char const *const *)envp);
#endif
}
#endif /* MAGIC:impl_if */
/*[[[end:libd_execlpe]]]*/

/*[[[head:libc_execlpe,hash:CRC-32=0x3a7dd4ef]]]*/
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBCCALL libc_execlpe)(char const *__restrict file,
                                    char const *args,
                                    ...)
/*[[[body:libc_execlpe]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	char ***penvp = (char ***)&args;
	while (*penvp++)
		; /* Envp is located 1 after the first NULL-entry */
	return execvpe(file,
	               (char const *const *)&args,
	               (char const *const *)*penvp);
#else
	va_list vargs;
	char **vector, **envp;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char, vector, vargs, args);
	envp = va_arg(vargs, char **);
	va_end(vargs);
	return execvpe(file,
	               (char const *const *)vector,
	               (char const *const *)envp);
#endif
}
/*[[[end:libc_execlpe]]]*/

/*[[[head:libc_getpid,hash:CRC-32=0xcec36af6]]]*/
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
INTERN ATTR_SECTION(".text.crt.sched.process") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_getpid)(void)
/*[[[body:libc_getpid]]]*/
{
	pid_t result = sys_getpid();
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getpid]]]*/

/*[[[head:libc_pipe,hash:CRC-32=0x68f6b91f]]]*/
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer) */
INTERN ATTR_SECTION(".text.crt.io.access") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_pipe)(fd_t pipedes[2])
/*[[[body:libc_pipe]]]*/
{
	errno_t error;
	error = sys_pipe(pipedes);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_pipe]]]*/

/*[[[head:libc_sleep,hash:CRC-32=0xdc9c695b]]]*/
/* >> sleep(3)
 * Sleep for up to `SECONDS' seconds */
INTERN ATTR_SECTION(".text.crt.system.utility") unsigned int
NOTHROW_RPC(LIBCCALL libc_sleep)(unsigned int seconds)
/*[[[body:libc_sleep]]]*/
{
	struct timespec req, rem;
	req.tv_sec  = seconds;
	req.tv_nsec = 0;
	rem.tv_sec  = 0;
	sys_nanosleep(&req, &rem);
	return rem.tv_sec;
}
/*[[[end:libc_sleep]]]*/

/*[[[head:libc_getppid,hash:CRC-32=0xffba2bcf]]]*/
/* >> getppid(2)
 * Return the PID of the calling process's parent.
 * (That is the TID of the leader of the parent of the calling thread's leader)
 * THIS_THREAD->LEADER->PARENT->LEADER->PID */
INTERN ATTR_SECTION(".text.crt.sched.process") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_getppid)(void)
/*[[[body:libc_getppid]]]*/
{
	pid_t result = sys_getppid();
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getppid]]]*/

/*[[[head:libc_getpgrp,hash:CRC-32=0xfcc72f04]]]*/
/* >> getpgrp(2)
 * Return the ID of the calling process's process group.
 * (That is the TID of the leader of the process group of the calling thread's leader)
 * THIS_THREAD->LEADER->GROUP_LEADER->PID */
INTERN ATTR_SECTION(".text.crt.sched.process") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_getpgrp)(void)
/*[[[body:libc_getpgrp]]]*/
{
	pid_t result = sys_getpgid(0);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getpgrp]]]*/

/*[[[head:libc_setpgid,hash:CRC-32=0x4d5e0620]]]*/
/* >> setpgid(2)
 * Change the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `PID' is ZERO(0), use `gettid()' for it instead.
 * When `PGID' is ZERO(0), use `PID' (after it was substituted) for instead */
INTERN ATTR_SECTION(".text.crt.sched.process") int
NOTHROW_NCX(LIBCCALL libc_setpgid)(pid_t pid,
                                   pid_t pgid)
/*[[[body:libc_setpgid]]]*/
{
	errno_t result = sys_setpgid(pid, pgid);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setpgid]]]*/

/*[[[head:libc_setsid,hash:CRC-32=0x23cae8a2]]]*/
/* >> setsid(2)
 * Make the calling thread's process the leader of its associated
 * process group, before also making it its own session leader.
 * Then return the TID of that new session leader, which is also the PID of the calling process.
 *  - THIS_THREAD->LEADER->GROUP_LEADER                 = THIS_THREAD->LEADER;
 *  - THIS_THREAD->LEADER->GROUP_LEADER->SESSION_LEADER = THIS_THREAD->LEADER->GROUP_LEADER;
 *  - return THIS_THREAD->LEADER->PID; */
INTERN ATTR_SECTION(".text.crt.sched.process") pid_t
NOTHROW_NCX(LIBCCALL libc_setsid)(void)
/*[[[body:libc_setsid]]]*/
{
	pid_t result = sys_setsid();
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setsid]]]*/

/*[[[head:libc_getuid,hash:CRC-32=0xf6d31881]]]*/
/* >> getuid(2)
 * Return the real user ID of the calling process */
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED uid_t
NOTHROW_NCX(LIBCCALL libc_getuid)(void)
/*[[[body:libc_getuid]]]*/
{
#ifdef SYS_getuid32
	uint32_t result = sys_getuid32();
#else /* SYS_getuid32 */
	uid_t result = sys_getuid();
#endif /* !SYS_getuid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getuid]]]*/

/*[[[head:libc_geteuid,hash:CRC-32=0x4fa2ab2b]]]*/
/* >> geteuid(2)
 * Return the effective user ID of the calling process */
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED uid_t
NOTHROW_NCX(LIBCCALL libc_geteuid)(void)
/*[[[body:libc_geteuid]]]*/
{
#ifdef SYS_geteuid32
	uint32_t result = sys_geteuid32();
#else /* SYS_geteuid32 */
	uid_t result = sys_geteuid();
#endif /* !SYS_geteuid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_geteuid]]]*/

/*[[[head:libc_getgid,hash:CRC-32=0x144895db]]]*/
/* >> getgid(2)
 * Return the real group ID of the calling process */
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED gid_t
NOTHROW_NCX(LIBCCALL libc_getgid)(void)
/*[[[body:libc_getgid]]]*/
{
#ifdef SYS_getgid32
	uint32_t result = sys_getgid32();
#else /* SYS_getgid32 */
	gid_t result = sys_getgid();
#endif /* !SYS_getgid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getgid]]]*/

/*[[[head:libc_getegid,hash:CRC-32=0x4df40388]]]*/
/* >> getegid(2)
 * Return the effective group ID of the calling process */
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED gid_t
NOTHROW_NCX(LIBCCALL libc_getegid)(void)
/*[[[body:libc_getegid]]]*/
{
#ifdef SYS_getegid32
	uint32_t result = sys_getegid32();
#else /* SYS_getegid32 */
	gid_t result = sys_getegid();
#endif /* !SYS_getegid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getegid]]]*/

/*[[[head:libc_getgroups,hash:CRC-32=0x31b8a826]]]*/
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_getgroups)(int size,
                                     gid_t list[])
/*[[[body:libc_getgroups]]]*/
{
	errno_t result;
#if defined(SYS_setgroups32) && __SIZEOF_GID_T__ == 4
	result = sys_getgroups32((size_t)size, (uint32_t *)list);
#else /* SYS_setgroups32 && __SIZEOF_GID_T__ == 4 */
	result = sys_getgroups((size_t)size, (uint32_t *)list);
#endif /* !SYS_setgroups32 || __SIZEOF_GID_T__ != 4 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getgroups]]]*/

/*[[[head:libc_setuid,hash:CRC-32=0x5b00aa94]]]*/
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `UID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_setuid)(uid_t uid)
/*[[[body:libc_setuid]]]*/
{
	errno_t result;
#ifdef SYS_setuid32
	result = sys_setuid32((uint32_t)uid);
#else /* SYS_setuid32 */
	result = sys_setuid(uid);
#endif /* !SYS_setuid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setuid]]]*/

/*[[[head:libc_setgid,hash:CRC-32=0xbb851fbc]]]*/
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `GID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_setgid)(gid_t gid)
/*[[[body:libc_setgid]]]*/
{
	errno_t result;
#ifdef SYS_setgid32
	result = sys_setgid32((uint32_t)gid);
#else /* SYS_setgid32 */
	result = sys_setgid(gid);
#endif /* !SYS_setgid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setgid]]]*/

/*[[[head:libc_fork,hash:CRC-32=0xfd3b7678]]]*/
/* >> fork(2)
 * Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for */
INTERN ATTR_SECTION(".text.crt.sched.access") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_fork)(void)
/*[[[body:libc_fork]]]*/
{
	pid_t result;
	result = sys_fork();
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fork]]]*/

/*[[[head:libc_alarm,hash:CRC-32=0xc26c7b8b]]]*/
/* >> alarm(2)
 * @return: 0 : No alarm was scheduled before.
 * @return: * : The number of seconds yet to pass before a previous alarm would have elapsed.
 * Schedule an to deliver a `SIGALRM' after letting `seconds' elapse.
 * You may pass ZERO(0) for SECONDS to disable a previously scheduled alarm */
INTERN ATTR_SECTION(".text.crt.system.utility") unsigned int
NOTHROW_NCX(LIBCCALL libc_alarm)(unsigned int seconds)
/*[[[body:libc_alarm]]]*/
{
	syscall_ulong_t result;
	result = sys_alarm(seconds);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_alarm]]]*/

/*[[[head:libc_pause,hash:CRC-32=0x69734833]]]*/
/* >> pause(2)
 * Suspend execution until the delivery of a POSIX_SIGNAL */
INTERN ATTR_SECTION(".text.crt.system.utility") int
NOTHROW_RPC(LIBCCALL libc_pause)(void)
/*[[[body:libc_pause]]]*/
{
	errno_t result;
	result = sys_pause();
	return (int)libc_seterrno(-result);
}
/*[[[end:libc_pause]]]*/

PRIVATE ATTR_SECTION(".bss.crt.io.tty.ttyname_buffer") char ttyname_buffer[32];

/*[[[head:libc_ttyname,hash:CRC-32=0x276e3f5]]]*/
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED char *
NOTHROW_RPC(LIBCCALL libc_ttyname)(fd_t fd)
/*[[[body:libc_ttyname]]]*/
{
	if unlikely(libc_ttyname_r(fd, ttyname_buffer, sizeof(ttyname_buffer)))
		return NULL;
	return ttyname_buffer;
}
/*[[[end:libc_ttyname]]]*/

PRIVATE ATTR_SECTION(".rodata.crt.io.tty.devpath") char const devpath[] = "/dev";

/*[[[head:libc_ttyname_r,hash:CRC-32=0x47a8f874]]]*/
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_ttyname_r)(fd_t fd,
                                     char *buf,
                                     size_t buflen)
/*[[[body:libc_ttyname_r]]]*/
{
	if unlikely(!libc_isatty(fd)) {
		libc_seterrno(ENOTTY);
		return ENOTTY;
	}
	/* Simply try to realpath() the given `fd' */
	{
		ssize_t reqlen;
		reqlen = sys_frealpath4(fd, buf, buflen, AT_READLINK_REQSIZE);
		if unlikely(E_ISERR(reqlen))
			goto fallback; /* Shouldn't happen... */
		/* Check if the buffer was large enough */
		if unlikely((size_t)reqlen > buflen) {
			libc_seterrno(ERANGE);
			return ERANGE;
		}
		/* Found it! */
		return 0;
	}
	/* Fallback: Search `/dev' for the proper file */
fallback:
	{
		struct stat64 st;
		struct dirent *d;
		DIR *dirstream;
		int safe;
		dev_t rdev;
		ino_t ino;
		if unlikely(buflen < (COMPILER_STRLEN(devpath) + 1) * sizeof(char)) {
			libc_seterrno(ERANGE);
			return ERANGE;
		}
		if unlikely(fstat64(fd, &st) < 0)
			return libc_geterrno();
		if ((dirstream = opendir(devpath)) == NULL)
			return libc_geterrno();
		memcpy(buf, devpath, COMPILER_STRLEN(devpath), sizeof(char));
		buf[COMPILER_STRLEN(devpath)] = '/';
		buflen -= (COMPILER_STRLEN(devpath) + 1) * sizeof(char);
		safe = libc_geterrno();
		rdev = st.st_dev;
		ino  = st.st_ino;
		while ((d = readdir(dirstream)) != NULL) {
			size_t needed;
			/* We need a character device. */
			if (d->d_type != DT_CHR)
				continue;
			if (d->d_ino != ino)
				continue;
#if 0 /* These are symlinks (DT_LNK), so we've already skipped them ;) */
			{
				PRIVATE ATTR_SECTION(".rodata.crt.io.tty.str_stdin")  char const str_stdin[] = "stdin";
				PRIVATE ATTR_SECTION(".rodata.crt.io.tty.str_stdout") char const str_stdout[] = "stdout";
				PRIVATE ATTR_SECTION(".rodata.crt.io.tty.str_stderr") char const str_stderr[] = "stderr";
				/* Ignore the /dev/std(in|out|err) aliases */
				if (strcmp(d->d_name, str_stdin) == 0)
					continue;
				if (strcmp(d->d_name, str_stdout) == 0)
					continue;
				if (strcmp(d->d_name, str_stderr) == 0)
					continue;
			}
#endif
			needed = _D_EXACT_NAMLEN(d);
			if (needed >= buflen) {
				closedir(dirstream);
				libc_seterrno(ERANGE);
				return ERANGE;
			}
			memcpy(&buf[sizeof(devpath)],
			       d->d_name,
			       needed + 1,
			       sizeof(char));
			if (stat64(buf, &st) != 0)
				continue;
			if (st.st_rdev != rdev)
				continue;
			if unlikely(st.st_ino != ino)
				continue;
			if unlikely(!S_ISCHR(st.st_mode))
				continue;
			/* Found it! */
			closedir(dirstream);
			libc_seterrno(safe);
			return 0;
		}
		closedir(dirstream);
		libc_seterrno(safe);
	}
	return ENOTTY;
}
/*[[[end:libc_ttyname_r]]]*/

/*[[[head:libc_tcgetpgrp,hash:CRC-32=0x92b5b83e]]]*/
/* >> tcgetpgrp(2)
 * Return the foreground process group of a given TTY file descriptor */
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_tcgetpgrp)(fd_t fd)
/*[[[body:libc_tcgetpgrp]]]*/
{
	pid_t result;
	if (ioctl(fd, TIOCGPGRP, &result) < 0)
		result = -1;
	return result;
}
/*[[[end:libc_tcgetpgrp]]]*/

/*[[[head:libc_tcsetpgrp,hash:CRC-32=0xfc6f4045]]]*/
/* >> tcsetpgrp(2)
 * Set the foreground process group of a given TTY file descriptor */
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_tcsetpgrp)(fd_t fd,
                                     pid_t pgrp_id)
/*[[[body:libc_tcsetpgrp]]]*/
{
	return ioctl(fd, TIOCSPGRP, &pgrp_id) < 0 ? -1 : 0;
}
/*[[[end:libc_tcsetpgrp]]]*/

/*[[[head:libc_getlogin_r,hash:CRC-32=0xda196cf0]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_getlogin_r)(char *name,
                                      size_t name_len)
/*[[[body:libc_getlogin_r]]]*/
/*AUTO*/{
	(void)name;
	(void)name_len;
	CRT_UNIMPLEMENTED("getlogin_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getlogin_r]]]*/

/*[[[head:libc_getlogin,hash:CRC-32=0xa37530ca]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_getlogin)(void)
/*[[[body:libc_getlogin]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getlogin"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getlogin]]]*/

/*[[[head:libc_setlogin,hash:CRC-32=0x9d72f9a]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_setlogin)(char const *name)
/*[[[body:libc_setlogin]]]*/
/*AUTO*/{
	(void)name;
	CRT_UNIMPLEMENTED("setlogin"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_setlogin]]]*/

/*[[[head:libc_chown,hash:CRC-32=0x61d0972c]]]*/
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_chown)(char const *file,
                                 uid_t owner,
                                 gid_t group)
/*[[[body:libc_chown]]]*/
{
	errno_t result;
#ifdef __NR_chown32
	result = sys_chown32(file, (uint32_t)owner, (uint32_t)group);
#else /* __NR_chown32 */
	result = sys_chown(file, (uint32_t)owner, (uint32_t)group);
#endif /* !__NR_chown32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_chown]]]*/

/*[[[head:libc_link,hash:CRC-32=0x2a0edacd]]]*/
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_link)(char const *from,
                                char const *to)
/*[[[body:libc_link]]]*/
{
	errno_t result;
	result = sys_link(from, to);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_link]]]*/

/*[[[head:libc_read,hash:CRC-32=0x47219639]]]*/
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
INTERN ATTR_SECTION(".text.crt.io.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_read)(fd_t fd,
                                void *buf,
                                size_t bufsize)
/*[[[body:libc_read]]]*/
{
	ssize_t result;
	result = sys_read(fd, buf, bufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_read]]]*/

/*[[[head:libc_write,hash:CRC-32=0x8fd97a]]]*/
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
INTERN ATTR_SECTION(".text.crt.io.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_write)(fd_t fd,
                                 void const *buf,
                                 size_t bufsize)
/*[[[body:libc_write]]]*/
{
	ssize_t result;
	result = sys_write(fd, buf, bufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_write]]]*/

/*[[[head:libc_lseek,hash:CRC-32=0x559c2bf8]]]*/
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
INTERN ATTR_SECTION(".text.crt.io.seek") off_t
NOTHROW_NCX(LIBCCALL libc_lseek)(fd_t fd,
                                 off_t offset,
                                 __STDC_INT_AS_UINT_T whence)
/*[[[body:libc_lseek]]]*/
{
	off_t result;
#ifdef __NR_lseek
	result = sys_lseek(fd, (int32_t)offset, whence);
#else /* __NR_lseek */
	result = sys_lseek64(fd, (int64_t)offset, whence);
#endif /* !__NR_lseek */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_lseek]]]*/

/*[[[head:libc_isatty,hash:CRC-32=0xf74a9548]]]*/
/* >> isatty(2)
 * @return: 1: Is a tty
 * @return: 0: Not a tty
 * Check if the given file handle `FD' refers to a TTY */
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isatty)(fd_t fd)
/*[[[body:libc_isatty]]]*/
{
	struct termios ios;
	return ioctl(fd, TCGETA, &ios) < 0 ? 0 : 1;
}
/*[[[end:libc_isatty]]]*/

/*[[[head:libc_dup2,hash:CRC-32=0xda83cf00]]]*/
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
INTERN ATTR_SECTION(".text.crt.io.access") fd_t
NOTHROW_NCX(LIBCCALL libc_dup2)(fd_t oldfd,
                                fd_t newfd)
/*[[[body:libc_dup2]]]*/
{
	fd_t result;
	result = sys_dup2(oldfd, newfd);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_dup2]]]*/

/*[[[head:libc_dup,hash:CRC-32=0xc51eab6c]]]*/
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `FD' and return its duplicated handle number */
INTERN ATTR_SECTION(".text.crt.io.access") WUNUSED fd_t
NOTHROW_NCX(LIBCCALL libc_dup)(fd_t fd)
/*[[[body:libc_dup]]]*/
{
	fd_t result;
	result = sys_dup(fd);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_dup]]]*/

/*[[[head:libc_close,hash:CRC-32=0x65a66917]]]*/
/* >> close(2)
 * Close a file handle */
INTERN ATTR_SECTION(".text.crt.io.access") int
NOTHROW_NCX(LIBCCALL libc_close)(fd_t fd)
/*[[[body:libc_close]]]*/
{
	errno_t result;
	result = sys_close(fd);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_close]]]*/

/*[[[head:libc_access,hash:CRC-32=0x960e2f3]]]*/
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_access)(char const *file,
                                  __STDC_INT_AS_UINT_T type)
/*[[[body:libc_access]]]*/
{
	errno_t result;
	result = sys_access(file, (syscall_ulong_t)(unsigned int)type);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_access]]]*/

/*[[[head:libc_chdir,hash:CRC-32=0xd3cd439d]]]*/
/* >> chdir(2)
 * Change the current working directory to `PATH' */
INTERN ATTR_SECTION(".text.crt.fs.basic_property") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_chdir)(char const *path)
/*[[[body:libc_chdir]]]*/
{
	errno_t result;
	result = sys_chdir(path);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_chdir]]]*/

/*[[[head:libc_getcwd,hash:CRC-32=0xf7aeb2ae]]]*/
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTERN ATTR_SECTION(".text.crt.fs.basic_property") char *
NOTHROW_RPC(LIBCCALL libc_getcwd)(char *buf,
                                  size_t bufsize)
/*[[[body:libc_getcwd]]]*/
{
	ssize_t result;
	char *buffer = buf;
	if (!buf) {
		if (!bufsize) {
			/* Automatically allocate + determine buffer size. */
			bufsize = PATH_MAX;
			buffer  = (char *)malloc(bufsize);
			if unlikely(!buffer)
				bufsize = 0;
			for (;;) {
				result = sys_frealpath4(AT_FDCWD,
				                        buffer,
				                        bufsize,
				                        AT_READLINK_REQSIZE);
				if unlikely(E_ISERR(result))
					goto err_buffer_result_errno;
				if likely((size_t)result <= bufsize)
					break;
				/* Allocate the required amount of memory. */
				buf = (char *)realloc(buffer, (size_t)result);
				if unlikely(!buf) {
					free(buffer);
					return NULL;
				}
				bufsize = (size_t)result;
				buffer  = buf;
			}
			if ((size_t)result != bufsize) {
				buf = (char *)realloc(buffer, (size_t)result);
				if likely(buf)
					buffer = buf;
			}
			return buffer;
		}
		buffer = (char *)malloc(bufsize);
		if unlikely(!buffer)
			goto done;
	}
	result = sys_getcwd(buffer,
	                    bufsize);
	if (E_ISERR(result)) {
		if (!buf) {
err_buffer_result_errno:
			free(buffer);
		}
		libc_seterrno(-result);
		return NULL;
	}
done:
	return buffer;
}
/*[[[end:libc_getcwd]]]*/

/*[[[head:libc_unlink,hash:CRC-32=0x889af3d5]]]*/
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_unlink)(char const *file)
/*[[[body:libc_unlink]]]*/
{
	errno_t result;
#ifdef __NR_unlink
	result = sys_unlink(file);
#else /* __NR_unlink */
	result = sys_unlinkat(AT_FDCWD, file, 0);
#endif /* !__NR_unlink */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_unlink]]]*/

/*[[[head:libc_rmdir,hash:CRC-32=0x2a419b8]]]*/
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_rmdir)(char const *path)
/*[[[body:libc_rmdir]]]*/
{
	errno_t result;
#ifdef __NR_rmdir
	result = sys_rmdir(path);
#else /* __NR_rmdir */
	result = sys_unlinkat(AT_FDCWD, path, AT_REMOVEDIR);
#endif /* !__NR_rmdir */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_rmdir]]]*/

/*[[[head:libc_euidaccess,hash:CRC-32=0x452a2ec]]]*/
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_euidaccess)(char const *file,
                                      __STDC_INT_AS_UINT_T type)
/*[[[body:libc_euidaccess]]]*/
{
	errno_t result;
	result = sys_faccessat(AT_FDCWD,
	                       file,
	                       (syscall_ulong_t)(unsigned int)type,
	                       AT_EACCESS);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_euidaccess]]]*/

/*[[[head:libc_faccessat,hash:CRC-32=0x1d183b66]]]*/
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
INTERN ATTR_SECTION(".text.crt.fs.property") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_faccessat)(fd_t dfd,
                                     char const *file,
                                     __STDC_INT_AS_UINT_T type,
                                     atflag_t flags)
/*[[[body:libc_faccessat]]]*/
{
	errno_t result;
	result = sys_faccessat(dfd,
	                       file,
	                       (syscall_ulong_t)(unsigned int)type,
	                       flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_faccessat]]]*/

/*[[[head:libc_fchownat,hash:CRC-32=0x2f5885f8]]]*/
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_fchownat)(fd_t dfd,
                                    char const *file,
                                    uid_t owner,
                                    gid_t group,
                                    atflag_t flags)
/*[[[body:libc_fchownat]]]*/
{
	errno_t result;
	result = sys_fchownat(dfd,
	                      file,
	                      (uint32_t)owner,
	                      (uint32_t)group,
	                      flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fchownat]]]*/

/*[[[head:libc_linkat,hash:CRC-32=0x1bef3774]]]*/
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2, 4)) int
NOTHROW_RPC(LIBCCALL libc_linkat)(fd_t fromfd,
                                  char const *from,
                                  fd_t tofd,
                                  char const *to,
                                  atflag_t flags)
/*[[[body:libc_linkat]]]*/
{
	errno_t result;
	result = sys_linkat(fromfd,
	                    from,
	                    tofd,
	                    to,
	                    flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_linkat]]]*/

/*[[[head:libc_symlinkat,hash:CRC-32=0xe23c488]]]*/
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1, 3)) int
NOTHROW_RPC(LIBCCALL libc_symlinkat)(char const *link_text,
                                     fd_t tofd,
                                     char const *target_path)
/*[[[body:libc_symlinkat]]]*/
{
	errno_t result;
	result = sys_symlinkat(link_text,
	                       tofd,
	                       target_path);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_symlinkat]]]*/

/*[[[head:libc_readlinkat,hash:CRC-32=0x8f4f8829]]]*/
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTERN ATTR_SECTION(".text.crt.fs.property") NONNULL((2, 3)) ssize_t
NOTHROW_RPC(LIBCCALL libc_readlinkat)(fd_t dfd,
                                      char const *__restrict path,
                                      char *__restrict buf,
                                      size_t buflen)
/*[[[body:libc_readlinkat]]]*/
{
	errno_t result;
	result = sys_readlinkat(dfd,
	                        path,
	                        buf,
	                        buflen);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_readlinkat]]]*/

/*[[[head:libc_unlinkat,hash:CRC-32=0x3d902d39]]]*/
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_unlinkat)(fd_t dfd,
                                    char const *name,
                                    atflag_t flags)
/*[[[body:libc_unlinkat]]]*/
{
	errno_t result;
	result = sys_unlinkat(dfd,
	                      name,
	                      flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_unlinkat]]]*/

/*[[[head:libc_lseek64,hash:CRC-32=0x804bca6]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_lseek64, libc_lseek);
#else /* MAGIC:alias */
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
INTERN ATTR_SECTION(".text.crt.io.large.seek") off64_t
NOTHROW_NCX(LIBCCALL libc_lseek64)(fd_t fd,
                                   off64_t offset,
                                   __STDC_INT_AS_UINT_T whence)
/*[[[body:libc_lseek64]]]*/
{
	off64_t result;
	result = sys_lseek64(fd,
	                     offset,
	                     whence);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_lseek64]]]*/

/*[[[head:libc_pread,hash:CRC-32=0x49c6d49d]]]*/
/* >> pread(2)
 * Read data from a file at a specific offset */
INTERN ATTR_SECTION(".text.crt.io.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_pread)(fd_t fd,
                                 void *buf,
                                 size_t bufsize,
                                 __PIO_OFFSET offset)
/*[[[body:libc_pread]]]*/
{
	ssize_t result;
	result = sys_pread64(fd,
	                     buf,
	                     bufsize,
	                     (uint64_t)(uint32_t)offset);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_pread]]]*/

/*[[[head:libc_pwrite,hash:CRC-32=0xad8b5ce3]]]*/
/* >> pwrite(2)
 * Write data to a file at a specific offset */
INTERN ATTR_SECTION(".text.crt.io.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_pwrite)(fd_t fd,
                                  void const *buf,
                                  size_t bufsize,
                                  __PIO_OFFSET offset)
/*[[[body:libc_pwrite]]]*/
{
	ssize_t result;
	result = sys_pwrite64(fd,
	                      buf,
	                      bufsize,
	                      (uint64_t)(uint32_t)offset);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_pwrite]]]*/

/*[[[head:libc_pread64,hash:CRC-32=0xa822560a]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_pread64, libc_pread);
#else /* MAGIC:alias */
/* >> pread64(2)
 * Read data from a file at a specific offset */
INTERN ATTR_SECTION(".text.crt.io.large.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_pread64)(fd_t fd,
                                   void *buf,
                                   size_t bufsize,
                                   __PIO_OFFSET64 offset)
/*[[[body:libc_pread64]]]*/
{
	ssize_t result;
	result = sys_pread64(fd,
	                     buf,
	                     bufsize,
	                     (uint64_t)offset);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_pread64]]]*/

/*[[[head:libc_pwrite64,hash:CRC-32=0xbd5df9c6]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_pwrite64, libc_pwrite);
#else /* MAGIC:alias */
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
INTERN ATTR_SECTION(".text.crt.io.large.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_pwrite64)(fd_t fd,
                                    void const *buf,
                                    size_t bufsize,
                                    __PIO_OFFSET64 offset)
/*[[[body:libc_pwrite64]]]*/
{
	ssize_t result;
	result = sys_pwrite64(fd,
	                      buf,
	                      bufsize,
	                      (uint64_t)offset);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_pwrite64]]]*/

/*[[[head:libc_pipe2,hash:CRC-32=0x9bb86b5]]]*/
INTERN ATTR_SECTION(".text.crt.io.access") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_pipe2)(fd_t pipedes[2],
                                 oflag_t flags)
/*[[[body:libc_pipe2]]]*/
{
	errno_t result;
	result = sys_pipe2(pipedes,
	                   flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_pipe2]]]*/

/*[[[head:libc_dup3,hash:CRC-32=0x88bdc54a]]]*/
INTERN ATTR_SECTION(".text.crt.io.access") fd_t
NOTHROW_NCX(LIBCCALL libc_dup3)(fd_t oldfd,
                                fd_t newfd,
                                oflag_t flags)
/*[[[body:libc_dup3]]]*/
{
	fd_t result;
	result = sys_dup3(oldfd,
	                  newfd,
	                  flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_dup3]]]*/

/*[[[head:libc_get_current_dir_name,hash:CRC-32=0x4c0969ed]]]*/
INTERN ATTR_SECTION(".text.crt.fs.basic_property") ATTR_MALLOC WUNUSED char *
NOTHROW_RPC(LIBCCALL libc_get_current_dir_name)(void)
/*[[[body:libc_get_current_dir_name]]]*/
{
	return getcwd(NULL, 0);
}
/*[[[end:libc_get_current_dir_name]]]*/


PRIVATE ATTR_NOINLINE int LIBCCALL
group_member_impl(gid_t gid, unsigned int bufsize) {
	int n; unsigned int i;
	gid_t *groups;
	groups = (gid_t *)alloca(bufsize * sizeof(*groups));
	n = getgroups((int)bufsize, groups);
	if unlikely(n < 0)
		return n;
	for (i = 0; i < (unsigned int)n; ++i) {
		if (groups[i] == gid)
			return 1;
	}
	return 0;
}

/*[[[head:libc_group_member,hash:CRC-32=0x8c8ecfec]]]*/
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_group_member)(gid_t gid)
/*[[[body:libc_group_member]]]*/
{
	int result;
#if !defined(NGROUPS_MAX) || NGROUPS_MAX > 32
	unsigned int size = 32;
#else /* !NGROUPS_MAX || NGROUPS_MAX > 32 */
	unsigned int size = NGROUPS_MAX;
#endif /* NGROUPS_MAX && NGROUPS_MAX <= 32 */
	while ((result = group_member_impl(gid, size)) < 0 && libc_geterrno() == EINVAL)
		size *= 2;
	return result;
}
/*[[[end:libc_group_member]]]*/

/*[[[head:libc_getresuid,hash:CRC-32=0x806e2ee8]]]*/
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_getresuid)(uid_t *ruid,
                                     uid_t *euid,
                                     uid_t *suid)
/*[[[body:libc_getresuid]]]*/
{
	errno_t result;
#ifdef SYS_getresuid32
	result = sys_getresuid32((uint32_t *)ruid,
	                         (uint32_t *)euid,
	                         (uint32_t *)suid);
#else /* SYS_getresuid32 */
	result = sys_getresuid(ruid, euid, suid);
#endif /* !SYS_getresuid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getresuid]]]*/

/*[[[head:libc_getresgid,hash:CRC-32=0xf1a2dfa2]]]*/
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_getresgid)(gid_t *rgid,
                                     gid_t *egid,
                                     gid_t *sgid)
/*[[[body:libc_getresgid]]]*/
{
	errno_t result;
#ifdef SYS_getresgid32
	result = sys_getresgid32((uint32_t *)rgid,
	                         (uint32_t *)egid,
	                         (uint32_t *)sgid);
#else /* SYS_getresgid32 */
	result = sys_getresgid(rgid, egid, sgid);
#endif /* !SYS_getresgid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getresgid]]]*/

/*[[[head:libc_setresuid,hash:CRC-32=0x9f09ac68]]]*/
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_setresuid)(uid_t ruid,
                                     uid_t euid,
                                     uid_t suid)
/*[[[body:libc_setresuid]]]*/
{
	errno_t result;
#ifdef SYS_setresuid32
	result = sys_setresuid32((uint32_t)ruid,
	                         (uint32_t)euid,
	                         (uint32_t)suid);
#else /* SYS_setresuid32 */
	result = sys_setresuid(ruid, euid, suid);
#endif /* !SYS_setresuid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setresuid]]]*/

/*[[[head:libc_setresgid,hash:CRC-32=0xdf303ae7]]]*/
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_setresgid)(gid_t rgid,
                                     gid_t egid,
                                     gid_t sgid)
/*[[[body:libc_setresgid]]]*/
{
	errno_t result;
#ifdef SYS_setresgid32
	result = sys_setresgid32((uint32_t)rgid,
	                         (uint32_t)egid,
	                         (uint32_t)sgid);
#else /* SYS_setresgid32 */
	result = sys_setresgid(rgid, egid, sgid);
#endif /* !SYS_setresgid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setresgid]]]*/

/*[[[head:libc_usleep,hash:CRC-32=0xe9ff7436]]]*/
/* Sleep for `useconds' microseconds (1/1.000.000 seconds) */
INTERN ATTR_SECTION(".text.crt.system.utility") int
NOTHROW_RPC(LIBCCALL libc_usleep)(useconds_t useconds)
/*[[[body:libc_usleep]]]*/
{
	struct timespec ts;
	ts.tv_sec  = (time_t)(useconds / USEC_PER_SEC);
	ts.tv_nsec = (syscall_ulong_t)(useconds % USEC_PER_SEC) * NSEC_PER_USEC;
	return nanosleep(&ts, NULL);
}
/*[[[end:libc_usleep]]]*/

/*[[[head:libc_getwd,hash:CRC-32=0x411bae1b]]]*/
INTERN ATTR_SECTION(".text.crt.fs.basic_property") ATTR_DEPRECATED("Use getcwd()") NONNULL((1)) char *
NOTHROW_RPC(LIBCCALL libc_getwd)(char *buf)
/*[[[body:libc_getwd]]]*/
{
	return getcwd(buf, (size_t)-1);
}
/*[[[end:libc_getwd]]]*/

/*[[[head:libc_ualarm,hash:CRC-32=0x3b758142]]]*/
INTERN ATTR_SECTION(".text.crt.system.utility") useconds_t
NOTHROW_NCX(LIBCCALL libc_ualarm)(useconds_t value,
                                  useconds_t interval)
/*[[[body:libc_ualarm]]]*/
{
	struct itimerval timer, otimer;
	timer.it_value.tv_sec     = value / 1000000;
	timer.it_value.tv_usec    = value % 1000000;
	timer.it_interval.tv_sec  = interval / 1000000;
	timer.it_interval.tv_usec = interval % 1000000;
	if (setitimer(ITIMER_REAL, &timer, &otimer) < 0)
		goto err;
	return (otimer.it_value.tv_sec * 1000000) +
	       (otimer.it_value.tv_usec);
err:
	return (useconds_t)-1;
}
/*[[[end:libc_ualarm]]]*/

/*[[[head:libc_vfork,hash:CRC-32=0x108454d0]]]*/
/* >> vfork(2)
 * Same as `fork(2)', but possibly suspend the calling process until the
 * child process either calls `exit(2)' or one of the many `exec(2)' functions */
INTERN ATTR_SECTION(".text.crt.sched.access") ATTR_RETURNS_TWICE WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_vfork)(void)
/*[[[body:libc_vfork]]]*/
{
	/* The regular fork() can be used to substitue vfork()
	 * However, implementing vfork() for real would be even
	 * better (but would require quite significant additions
	 * to kernel-space)... */
	return fork();
}
/*[[[end:libc_vfork]]]*/

/*[[[head:libc_fchown,hash:CRC-32=0x17d60241]]]*/
/* >> fchown(2)
 * Change the ownership of a given `FD' to `GROUP:OWNER' */
INTERN ATTR_SECTION(".text.crt.fs.modify") int
NOTHROW_RPC(LIBCCALL libc_fchown)(fd_t fd,
                                  uid_t owner,
                                  gid_t group)
/*[[[body:libc_fchown]]]*/
{
	errno_t result;
#ifdef __NR_fchown32
	result = sys_fchown32(fd,
	                      (uint32_t)owner,
	                      (uint32_t)group);
#else /* __NR_fchown32 */
	result = sys_fchown(fd,
	                    (uint32_t)owner,
	                    (uint32_t)group);
#endif /* !__NR_fchown32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fchown]]]*/

/*[[[head:libc_fchdir,hash:CRC-32=0xbff54254]]]*/
/* >> chdir(2)
 * Change the current working directory to `PATH' */
INTERN ATTR_SECTION(".text.crt.fs.basic_property") int
NOTHROW_RPC(LIBCCALL libc_fchdir)(fd_t fd)
/*[[[body:libc_fchdir]]]*/
{
	errno_t result;
	result = sys_fchdir(fd);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fchdir]]]*/

/*[[[head:libc_getpgid,hash:CRC-32=0x9d2b3e0c]]]*/
/* >> getpgid(2)
 * Return the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `PID' is ZERO(0), use `gettid()' for it instead */
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_getpgid)(pid_t pid)
/*[[[body:libc_getpgid]]]*/
{
	pid_t result;
	result = sys_getpgid(pid);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getpgid]]]*/

/*[[[head:libc_getsid,hash:CRC-32=0xd4f82285]]]*/
/* >> getsid(2)
 * Return the ID of the session which a process `PID' is apart of.
 * return THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
INTERN ATTR_SECTION(".text.crt.sched.process") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_getsid)(pid_t pid)
/*[[[body:libc_getsid]]]*/
{
	pid_t result;
	result = sys_getsid(pid);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getsid]]]*/

/*[[[head:libc_lchown,hash:CRC-32=0xebc0d16b]]]*/
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_lchown)(char const *file,
                                  uid_t owner,
                                  gid_t group)
/*[[[body:libc_lchown]]]*/
{
	errno_t result;
#ifdef __NR_lchown32
	result = sys_lchown32(file,
	                      (uint32_t)owner,
	                      (uint32_t)group);
#else /* __NR_lchown32 */
	result = sys_lchown(file,
	                    (uint32_t)owner,
	                    (uint32_t)group);
#endif /* !__NR_lchown32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_lchown]]]*/

/*[[[head:libc_truncate,hash:CRC-32=0xbe92bdae]]]*/
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_truncate)(char const *file,
                                    __PIO_OFFSET length)
/*[[[body:libc_truncate]]]*/
{
	errno_t result;
	result = sys_truncate(file,
	                      (uint32_t)length);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_truncate]]]*/

/*[[[head:libc_truncate64,hash:CRC-32=0x43661925]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_truncate64, libc_truncate);
#else /* MAGIC:alias */
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_truncate64)(char const *file,
                                      __PIO_OFFSET64 length)
/*[[[body:libc_truncate64]]]*/
{
	errno_t result;
	result = sys_truncate64(file,
	                        (uint64_t)length);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_truncate64]]]*/

/*[[[head:libc_fexecve,hash:CRC-32=0xa71cb333]]]*/
/* >> fexecve(2)
 * Replace the calling process with the application image referred to by `FD' and
 * execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") NONNULL((2, 3)) int
NOTHROW_RPC(LIBCCALL libc_fexecve)(fd_t fd,
                                   __TARGV,
                                   __TENVP)
/*[[[body:libc_fexecve]]]*/
{
	errno_t error;
	error = sys_execveat(fd,
	                     "",
	                     (char const *const *)___argv,
	                     (char const *const *)___envp,
	                     AT_EMPTY_PATH);
	return (int)libc_seterrno(-error);
}
/*[[[end:libc_fexecve]]]*/

/*[[[head:libc_setpgrp,hash:CRC-32=0xeef27930]]]*/
/* >> setpgrp(3)
 * Move the calling process into its own process group.
 * Equivalent to `setpgid(0, 0)' */
INTERN ATTR_SECTION(".text.crt.sched.process") int
NOTHROW_NCX(LIBCCALL libc_setpgrp)(void)
/*[[[body:libc_setpgrp]]]*/
{
	errno_t error;
	error = sys_setpgid(0, 0);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_setpgrp]]]*/

/*[[[head:libc_setreuid,hash:CRC-32=0xe0eef986]]]*/
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_setreuid)(uid_t ruid,
                                    uid_t euid)
/*[[[body:libc_setreuid]]]*/
{
	errno_t error;
#ifdef SYS_setreuid32
	error = sys_setreuid32((uint32_t)ruid,
	                       (uint32_t)euid);
#else /* SYS_setreuid32 */
	error = sys_setreuid(ruid, euid);
#endif /* !SYS_setreuid32 */
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_setreuid]]]*/

/*[[[head:libc_setregid,hash:CRC-32=0x8bdb5855]]]*/
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_setregid)(gid_t rgid,
                                    gid_t egid)
/*[[[body:libc_setregid]]]*/
{
	errno_t error;
#ifdef SYS_setregid32
	error = sys_setregid32((uint32_t)rgid,
	                       (uint32_t)egid);
#else /* SYS_setregid32 */
	error = sys_setregid(rgid, egid);
#endif /* !SYS_setregid32 */
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_setregid]]]*/

PRIVATE ATTR_SECTION(".rodata.crt.system.configuration.hostid_pathname") char const hostid_pathname[] = "/etc";
PRIVATE ATTR_SECTION(".rodata.crt.system.configuration.hostid_filename") char const hostid_filename[] = "/etc/hostid";

/*[[[head:libc_gethostid,hash:CRC-32=0x309164ac]]]*/
INTERN ATTR_SECTION(".text.crt.system.configuration") WUNUSED longptr_t
NOTHROW_NCX(LIBCCALL libc_gethostid)(void)
/*[[[body:libc_gethostid]]]*/
{
	fd_t fd;
	uint32_t id32;
	fd = sys_open(hostid_filename, O_RDONLY, 0);
	if (fd >= 0) {
		ssize_t count;
		count = readall(fd, &id32, 4);
		sys_close(fd);
		if (count == 4)
			return (long int)(unsigned long int)id32;
	}
	/* XXX: Glibc also tries to use the host's IP address here... */
	return 0;
}
/*[[[end:libc_gethostid]]]*/

/*[[[head:libc_sethostid,hash:CRC-32=0x804d684b]]]*/
INTERN ATTR_SECTION(".text.crt.system.configuration") int
NOTHROW_NCX(LIBCCALL libc_sethostid)(longptr_t id)
/*[[[body:libc_sethostid]]]*/
{
	fd_t fd;
	ssize_t count;
	uint32_t id32;
#if __SIZEOF_LONG__ > 4
	if (id & ~UINT32_C(0xffffffff)) {
		libc_seterrno(EOVERFLOW);
		return -1;
	}
#endif /* __SIZEOF_LONG__ > 4 */
	fd = sys_open(hostid_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0) {
		if (fd == -ENOTDIR) {
			/* Check if /etc was already created. */
			fd = sys_mkdir(hostid_pathname, 0755);
			if (fd == -EOK || fd == -EEXIST) {
				fd = sys_open(hostid_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (fd >= 0)
					goto got_fd;
			}
		}
		return libc_seterrno_syserr(fd);
	}
got_fd:
	id32  = (uint32_t)(unsigned long int)id;
	count = writeall(fd, &id32, 4);
	sys_close(fd);
	if (count <= 0) {
		if (!count)
			libc_seterrno(ENOSPC); /* ??? */
		return -1;
	}
	return 0;
}
/*[[[end:libc_sethostid]]]*/

/*[[[head:libc_seteuid,hash:CRC-32=0x17145d9f]]]*/
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EUID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_seteuid)(uid_t euid)
/*[[[body:libc_seteuid]]]*/
{
	errno_t error;
#ifdef SYS_getresuid32
	uint32_t ruid;
	error = sys_getresuid32(&ruid, NULL, NULL);
#else /* SYS_getresuid32 */
	uid_t ruid;
	error = sys_getresuid(&ruid, NULL, NULL);
#endif /* !SYS_getresuid32 */
	if (E_ISOK(error)) {
#ifdef SYS_setreuid32
		error = sys_setreuid32(ruid, (uint32_t)euid);
#else /* SYS_setreuid32 */
		error = sys_setreuid(ruid, euid);
#endif /* !SYS_setreuid32 */
	}
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_seteuid]]]*/

/*[[[head:libc_setegid,hash:CRC-32=0x52fc1bfe]]]*/
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EGID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_setegid)(gid_t egid)
/*[[[body:libc_setegid]]]*/
{
	errno_t error;
#ifdef SYS_getresgid32
	uint32_t rgid;
	error = sys_getresgid32(&rgid, NULL, NULL);
#else /* SYS_getresgid32 */
	gid_t rgid;
	error = sys_getresgid(&rgid, NULL, NULL);
#endif /* !SYS_getresgid32 */
	if (E_ISOK(error)) {
#ifdef SYS_setregid32
		error = sys_setregid32(rgid, (uint32_t)egid);
#else /* SYS_setregid32 */
		error = sys_setregid(rgid, egid);
#endif /* !SYS_setregid32 */
	}
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_setegid]]]*/

/*[[[head:libc_ttyslot,hash:CRC-32=0xfed7d754]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED int
NOTHROW_NCX(LIBCCALL libc_ttyslot)(void)
/*[[[body:libc_ttyslot]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("ttyslot"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ttyslot]]]*/

/*[[[head:libc_symlink,hash:CRC-32=0x18a9125e]]]*/
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_symlink)(char const *link_text,
                                   char const *target_path)
/*[[[body:libc_symlink]]]*/
{
	errno_t result;
	result = sys_symlink(link_text, target_path);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_symlink]]]*/

/*[[[head:libc_readlink,hash:CRC-32=0x270a309b]]]*/
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTERN ATTR_SECTION(".text.crt.fs.property") NONNULL((1, 2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_readlink)(char const *__restrict path,
                                    char *__restrict buf,
                                    size_t buflen)
/*[[[body:libc_readlink]]]*/
{
	ssize_t result;
	result = sys_readlink(path, buf, buflen);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_readlink]]]*/

/*[[[head:libc_gethostname,hash:CRC-32=0xd7e1249d]]]*/
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTERN ATTR_SECTION(".text.crt.system.configuration") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_gethostname)(char *name,
                                       size_t buflen)
/*[[[body:libc_gethostname]]]*/
{
	struct utsname uts;
	int result = uname(&uts);
	if (result == 0) {
		size_t len = strnlen(uts.nodename, _UTSNAME_NODENAME_LENGTH);
		if (buflen <= len) {
			/* EINVAL For getdomainname() under libc: name is NULL or name is longer than len bytes. */
			return (int)libc_seterrno(EINVAL);
		}
		memcpy(name, uts.nodename, len, sizeof(char));
		name[len] = '\0';
	}
	return result;
}
/*[[[end:libc_gethostname]]]*/

/*[[[head:libc_sethostname,hash:CRC-32=0x60798dac]]]*/
/* >> sethostname(2)
 * Set the name of the hosting machine */
INTERN ATTR_SECTION(".text.crt.system.configuration") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sethostname)(char const *name,
                                       size_t len)
/*[[[body:libc_sethostname]]]*/
{
	errno_t result;
	result = sys_sethostname(name, len);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sethostname]]]*/

/*[[[head:libc_getdomainname,hash:CRC-32=0x973a241a]]]*/
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTERN ATTR_SECTION(".text.crt.system.configuration") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_getdomainname)(char *name,
                                         size_t buflen)
/*[[[body:libc_getdomainname]]]*/
{
	struct utsname uts;
	int result = uname(&uts);
	if (result == 0) {
		size_t len = strnlen(uts.domainname, _UTSNAME_DOMAIN_LENGTH);
		if (buflen <= len) {
			/* EINVAL For getdomainname() under libc: name is NULL or name is longer than len bytes. */
			return (int)libc_seterrno(EINVAL);
		}
		memcpy(name, uts.domainname, len, sizeof(char));
		name[len] = '\0';
	}
	return result;
}
/*[[[end:libc_getdomainname]]]*/

/*[[[head:libc_setdomainname,hash:CRC-32=0xde26f8ae]]]*/
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
INTERN ATTR_SECTION(".text.crt.system.configuration") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_setdomainname)(char const *name,
                                         size_t len)
/*[[[body:libc_setdomainname]]]*/
{
	errno_t result;
	result = sys_setdomainname(name, len);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setdomainname]]]*/

/*[[[head:libc_vhangup,hash:CRC-32=0x3044b4c0]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_vhangup)(void)
/*[[[body:libc_vhangup]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("vhangup"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_vhangup]]]*/

/*[[[head:libc_profil,hash:CRC-32=0x994cbdf3]]]*/
INTERN ATTR_SECTION(".text.crt.system.utility") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_profil)(uint16_t *sample_buffer,
                                  size_t size,
                                  size_t offset,
                                  unsigned int scale)
/*[[[body:libc_profil]]]*/
{
#ifdef SYS_profil
	errno_t result;
	result = sys_profil((uint16_t *)sample_buffer,
	                    size,
	                    offset,
	                    (syscall_ulong_t)scale);
	return libc_seterrno_syserr(result);
#else /* SYS_profil */
	(void)sample_buffer;
	(void)size;
	(void)offset;
	(void)scale;
	libc_seterrno(ENOSYS);
	return -1;
#endif /* !SYS_profil */
}
/*[[[end:libc_profil]]]*/

/*[[[head:libc_getusershell,hash:CRC-32=0x89f58eb4]]]*/
INTERN ATTR_SECTION(".text.crt.database.shell") WUNUSED char *
NOTHROW_RPC(LIBCCALL libc_getusershell)(void)
/*[[[body:libc_getusershell]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getusershell"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getusershell]]]*/

/*[[[head:libc_endusershell,hash:CRC-32=0xddd668fc]]]*/
INTERN ATTR_SECTION(".text.crt.database.shell") void
NOTHROW_NCX(LIBCCALL libc_endusershell)(void)
/*[[[body:libc_endusershell]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endusershell"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endusershell]]]*/

/*[[[head:libc_setusershell,hash:CRC-32=0xa958a6d9]]]*/
INTERN ATTR_SECTION(".text.crt.database.shell") void
NOTHROW_RPC(LIBCCALL libc_setusershell)(void)
/*[[[body:libc_setusershell]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("setusershell"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setusershell]]]*/

PRIVATE ATTR_SECTION(".rodata.crt.system.utility.root") char const root[] = "/";
PRIVATE ATTR_SECTION(".rodata.crt.system.utility.dev_null") char const dev_null[] = "/dev/null";

/*[[[head:libc_daemon,hash:CRC-32=0xae3ecb6]]]*/
INTERN ATTR_SECTION(".text.crt.system.utility") int
NOTHROW_RPC(LIBCCALL libc_daemon)(__STDC_INT_AS_UINT_T nochdir,
                                  __STDC_INT_AS_UINT_T noclose)
/*[[[body:libc_daemon]]]*/
{
	pid_t cpid;
	cpid = fork();
	if (cpid < 0)
		return -1;
	if (cpid != 0)
		_Exit(0); /* The parent process dies. */
	if (setsid() < 0)
		return -1;
	if (!nochdir)
		chdir(root);
	if (!noclose) {
		fd_t i, nul = open(dev_null, O_RDWR);
		if (nul < 0)
			return -1;
		/* NOTE: Glibc does an additional check to ensure that `nul' really
		 *       is a character-device with the correct dev_t. We could do
		 *       that as well, however I'd consider a system where /dev/null
		 *       isn't actually /dev/null to already be broken... (and the
		 *       check only adds unnecessary overhead if you ask me) */
		for (i = 0; i < 3; ++i) {
			if (nul != i)
				sys_dup2(nul, i);
		}
		if (nul >= 3)
			sys_close(nul);
	}
	return 0;
}
/*[[[end:libc_daemon]]]*/

/*[[[head:libc_revoke,hash:CRC-32=0x78e6ad8b]]]*/
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_revoke)(char const *file)
/*[[[body:libc_revoke]]]*/
/*AUTO*/{
	(void)file;
	CRT_UNIMPLEMENTED("revoke"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_revoke]]]*/

/*[[[head:libd_syscall,hash:CRC-32=0xe92a633b]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
INTERN ATTR_SECTION(".text.crt.dos.system.utility") longptr_t
NOTHROW_RPC(VLIBDCALL libd_syscall)(longptr_t sysno,
                                    ...)
/*[[[body:libd_syscall]]]*/
/*AUTO*/{
	(void)sysno;
	CRT_UNIMPLEMENTED("syscall"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:impl_if */
/*[[[end:libd_syscall]]]*/

/*[[[head:libd_syscall64,hash:CRC-32=0x42d78139]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
INTERN ATTR_SECTION(".text.crt.dos.system.utility") __LONG64_TYPE__
NOTHROW_RPC(VLIBDCALL libd_syscall64)(syscall_ulong_t sysno,
                                      ...)
/*[[[body:libd_syscall64]]]*/
/*AUTO*/{
	(void)sysno;
	CRT_UNIMPLEMENTED("syscall64"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:impl_if */
/*[[[end:libd_syscall64]]]*/

/* `syscall' needs to be implemented in assembly! */
/*[[[skip:libc_syscall]]]*/
/*[[[skip:libc_syscall64]]]*/

/*[[[head:libc_chroot,hash:CRC-32=0xd6905a0e]]]*/
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
INTERN ATTR_SECTION(".text.crt.fs.utility") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_chroot)(char const *__restrict path)
/*[[[body:libc_chroot]]]*/
{
	errno_t result;
	result = sys_chroot(path);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_chroot]]]*/

/*[[[head:libc_getpass,hash:CRC-32=0x3bec8ea3]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED NONNULL((1)) char *
NOTHROW_RPC(LIBCCALL libc_getpass)(char const *__restrict prompt)
/*[[[body:libc_getpass]]]*/
/*AUTO*/{
	(void)prompt;
	CRT_UNIMPLEMENTED("getpass"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getpass]]]*/

/*[[[head:libc_ftruncate,hash:CRC-32=0xe79ad65f]]]*/
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.io.write") int
NOTHROW_NCX(LIBCCALL libc_ftruncate)(fd_t fd,
                                     __PIO_OFFSET length)
/*[[[body:libc_ftruncate]]]*/
{
	errno_t result;
	result = sys_ftruncate(fd, (uint32_t)length);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_ftruncate]]]*/

/*[[[head:libc_ftruncate64,hash:CRC-32=0x5703b896]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_ftruncate64, libc_ftruncate);
#else /* MAGIC:alias */
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.io.large.write") int
NOTHROW_NCX(LIBCCALL libc_ftruncate64)(fd_t fd,
                                       __PIO_OFFSET64 length)
/*[[[body:libc_ftruncate64]]]*/
{
	errno_t result;
	result = sys_ftruncate64(fd, (uint64_t)length);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_ftruncate64]]]*/


PRIVATE byte_t *brk_curr = NULL;
PRIVATE DEFINE_ATOMIC_RWLOCK(brk_lock);

PRIVATE int LIBCCALL do_brk(void *addr) {
	byte_t *real_oldbrk, *real_newbrk;
	if ((real_oldbrk = brk_curr) == NULL) {
		/* Lookup the end address of the main executable
		 * NOTE: We do this lazily to prevent the necessity of a `R_386_GLOB_DAT' relocation */
		void *temp = dlsym(RTLD_DEFAULT, "_end");
		if unlikely(!temp && dlerror())
			goto err_perm;
		real_oldbrk = (byte_t *)CEIL_ALIGN((uintptr_t)temp, OS_PAGESIZE);
	} else {
		real_oldbrk = (byte_t *)CEIL_ALIGN((uintptr_t)real_oldbrk, OS_PAGESIZE);
	}
	real_newbrk = (byte_t *)CEIL_ALIGN((uintptr_t)addr, OS_PAGESIZE);
	if (real_newbrk < real_oldbrk) {
		/* Release memory */
		if unlikely(munmap(real_newbrk, real_oldbrk - real_newbrk) == -1)
			goto err;
	} else if (real_newbrk > real_oldbrk) {
		void *map_result;
		/* Allocate more memory */
		map_result = mmap(real_oldbrk,
		                  real_newbrk - real_oldbrk,
		                  PROT_READ | PROT_WRITE,
		                  MAP_FIXED | MAP_ANONYMOUS,
		                  -1,
		                  0);
		if unlikely(map_result == MAP_FAILED)
			goto err;
		assertf(map_result == real_oldbrk,
		        "%p != %p",
		        map_result,
		        real_oldbrk);
	}
	brk_curr = (byte_t *)addr;
	return 0;
err_perm:
	libc_seterrno(EPERM);
err:
	return -1;
}


/*[[[head:libc_brk,hash:CRC-32=0xcf35a87e]]]*/
/* >> brk(2), sbrk(2)
 * Change the program break, allowing for a rudimentary implementation of a heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
INTERN ATTR_SECTION(".text.crt.heap.utility") int
NOTHROW_NCX(LIBCCALL libc_brk)(void *addr)
/*[[[body:libc_brk]]]*/
{
	int result;
	atomic_rwlock_write(&brk_lock);
	result = do_brk(addr);
	atomic_rwlock_endwrite(&brk_lock);
	return result;
}
/*[[[end:libc_brk]]]*/

/*[[[head:libc_sbrk,hash:CRC-32=0x4e0ccd70]]]*/
INTERN ATTR_SECTION(".text.crt.heap.utility") void *
NOTHROW_NCX(LIBCCALL libc_sbrk)(intptr_t delta)
/*[[[body:libc_sbrk]]]*/
{
	byte_t *result;
	atomic_rwlock_write(&brk_lock);
	if ((result = brk_curr) == NULL) {
		/* Lookup the end address of the main executable
		 * NOTE: We do this lazily to prevent the necessity of a relocation */
		void *temp = dlsym(RTLD_DEFAULT, "_end");
		if unlikely(!temp && dlerror())
			goto err_perm;
		result = (byte_t *)CEIL_ALIGN((uintptr_t)temp, OS_PAGESIZE);
	}
	if (do_brk(result + delta) != 0)
		result = (byte_t *)-1;
	atomic_rwlock_endwrite(&brk_lock);
	return result;
err_perm:
	atomic_rwlock_endwrite(&brk_lock);
	libc_seterrno(EPERM);
	return NULL;
}
/*[[[end:libc_sbrk]]]*/



/*[[[head:libc_ctermid,hash:CRC-32=0xa4338509]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") char *
NOTHROW_NCX(LIBCCALL libc_ctermid)(char *s)
/*[[[body:libc_ctermid]]]*/
{
	char *name = (char *)"/dev/tty";
	if (s == NULL)
		return name;
	return strcpy(s, name);
}
/*[[[end:libc_ctermid]]]*/

/*[[[head:libc_fpathconf,hash:CRC-32=0x68bc5593]]]*/
/* >> fpathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `FD'
 * return: * : The configuration limit associated with `NAME' for `FD'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `FD'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED longptr_t
NOTHROW_RPC(LIBCCALL libc_fpathconf)(fd_t fd,
                                     int name)
/*[[[body:libc_fpathconf]]]*/
/*AUTO*/{
	(void)fd;
	(void)name;
	CRT_UNIMPLEMENTED("fpathconf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_fpathconf]]]*/


/*[[[head:libc_pathconf,hash:CRC-32=0xa51c8ad0]]]*/
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.fs.property") NONNULL((1)) longptr_t
NOTHROW_RPC(LIBCCALL libc_pathconf)(char const *path,
                                    __STDC_INT_AS_UINT_T name)
/*[[[body:libc_pathconf]]]*/
/*AUTO*/{
	(void)path;
	(void)name;
	CRT_UNIMPLEMENTED("pathconf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_pathconf]]]*/

/*[[[head:libc_confstr,hash:CRC-32=0x3fd15238]]]*/
/* Retrieve a system configuration string specified by `name'
 * @param: name:   One of `_CS_*' from <bits/confname.h>
 * @param: buf:    Target buffer
 * @param: buflen: Available buffer size (including a trailing \0-character)
 * @return: * :    Required buffer size (including a trailing \0-character)
 * @return: 1 :    Empty configuration string.
 * @return: 0 :    [errno=EINVAL] Bad configuration `name'. */
INTERN ATTR_SECTION(".text.crt.system.configuration") size_t
NOTHROW_NCX(LIBCCALL libc_confstr)(__STDC_INT_AS_UINT_T name,
                                   char *buf,
                                   size_t buflen)
/*[[[body:libc_confstr]]]*/
{
#define DEFINE_STRING(name, text) \
	PRIVATE ATTR_SECTION(".rodata.crt.system.configuration.confstr_" #name) char const name[] = text
	size_t result;
	DEFINE_STRING(empty_string, "");
	char const *result_string = empty_string;
	switch (name) {

	case _CS_PATH: {
		DEFINE_STRING(cs_path, _PATH_DEFPATH);
		result_string = cs_path;
	}	break;

	case _CS_GNU_LIBC_VERSION:
	case _CS_GNU_LIBPTHREAD_VERSION:
	case _CS_V6_WIDTH_RESTRICTED_ENVS:
	case _CS_V5_WIDTH_RESTRICTED_ENVS:
	case _CS_V7_WIDTH_RESTRICTED_ENVS:
	case _CS_XBS5_ILP32_OFF32_CFLAGS:
	case _CS_XBS5_ILP32_OFF32_LDFLAGS:
	case _CS_XBS5_ILP32_OFFBIG_CFLAGS:
	case _CS_XBS5_ILP32_OFFBIG_LDFLAGS:
	case _CS_XBS5_LP64_OFF64_CFLAGS:
	case _CS_XBS5_LP64_OFF64_LDFLAGS:
	case _CS_POSIX_V6_ILP32_OFF32_CFLAGS:
	case _CS_POSIX_V6_ILP32_OFF32_LDFLAGS:
	case _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS:
	case _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS:
	case _CS_POSIX_V6_LP64_OFF64_CFLAGS:
	case _CS_POSIX_V6_LP64_OFF64_LDFLAGS:
	case _CS_POSIX_V7_ILP32_OFF32_CFLAGS:
	case _CS_POSIX_V7_ILP32_OFF32_LDFLAGS:
	case _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS:
	case _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS:
	case _CS_POSIX_V7_LP64_OFF64_CFLAGS:
	case _CS_POSIX_V7_LP64_OFF64_LDFLAGS:
		/* TODO? */
		break;

	case _CS_LFS_CFLAGS:
	case _CS_LFS_LINTFLAGS: {
		DEFINE_STRING(define_LFS, "-D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64");
		result_string = define_LFS;
	}	break;

	case _CS_LFS64_CFLAGS:
	case _CS_LFS64_LINTFLAGS: {
		DEFINE_STRING(define_LFS64, "-D_LARGEFILE64_SOURCE");
		result_string = define_LFS64;
	}	break;

	case _CS_LFS_LDFLAGS:
	case _CS_LFS_LIBS:
	case _CS_LFS64_LDFLAGS:
	case _CS_LFS64_LIBS:
	case _CS_XBS5_ILP32_OFF32_LIBS:
	case _CS_XBS5_ILP32_OFF32_LINTFLAGS:
	case _CS_XBS5_ILP32_OFFBIG_LIBS:
	case _CS_XBS5_ILP32_OFFBIG_LINTFLAGS:
	case _CS_XBS5_LP64_OFF64_LIBS:
	case _CS_XBS5_LP64_OFF64_LINTFLAGS:
	case _CS_XBS5_LPBIG_OFFBIG_CFLAGS:
	case _CS_XBS5_LPBIG_OFFBIG_LDFLAGS:
	case _CS_XBS5_LPBIG_OFFBIG_LIBS:
	case _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS:
	case _CS_POSIX_V6_ILP32_OFF32_LIBS:
	case _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS:
	case _CS_POSIX_V6_ILP32_OFFBIG_LIBS:
	case _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS:
	case _CS_POSIX_V6_LP64_OFF64_LIBS:
	case _CS_POSIX_V6_LP64_OFF64_LINTFLAGS:
	case _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS:
	case _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS:
	case _CS_POSIX_V6_LPBIG_OFFBIG_LIBS:
	case _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS:
	case _CS_POSIX_V7_ILP32_OFF32_LIBS:
	case _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS:
	case _CS_POSIX_V7_ILP32_OFFBIG_LIBS:
	case _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS:
	case _CS_POSIX_V7_LP64_OFF64_LIBS:
	case _CS_POSIX_V7_LP64_OFF64_LINTFLAGS:
	case _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS:
	case _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS:
	case _CS_POSIX_V7_LPBIG_OFFBIG_LIBS:
	case _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS:
		break;

	case _CS_V6_ENV:
	case _CS_V7_ENV: {
		DEFINE_STRING(cs_v67_env, "POSIXLY_CORRECT=1");
		result_string = cs_v67_env;
	}	break;

	default:
		libc_seterrno(EINVAL);
		return 0;
	}
	result = strlen(result_string) + 1;
	if (buflen && buf) {
		if (buflen >= result) {
			memcpy(buf, result_string, result, sizeof(char));
		} else {
			memcpy(buf, result_string, buflen - 1, sizeof(char));
			buf[buflen - 1] = '\0';
		}
	}
	return result;
}
/*[[[end:libc_confstr]]]*/

/*[[[head:libc_sysconf,hash:CRC-32=0xa1c47dad]]]*/
/* >> sysconf(2)
 * @param: NAME: One of `_SC_*' from <bits/confname.h>
 * Return a system configuration value `NAME'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] `NAME' referrs to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.system.configuration") WUNUSED longptr_t
NOTHROW_RPC(LIBCCALL libc_sysconf)(__STDC_INT_AS_UINT_T name)
/*[[[body:libc_sysconf]]]*/
{
	long int result;
	switch (name) {

	case _SC_CLK_TCK:
		result = CLK_TCK; /* TODO */
		break;

	case _SC_NGROUPS_MAX:
		result = NGROUPS_MAX;
		break;

	case _SC_STREAM_MAX:
		/* Unlimited, but needs a fixed value for historical reasons... */
#ifdef STREAM_MAX
		result = STREAM_MAX;
#else /* STREAM_MAX */
		result = FOPEN_MAX;
#endif /* !STREAM_MAX */
		break;

	case _SC_JOB_CONTROL:
		result = _POSIX_JOB_CONTROL;
		break;

	case _SC_SAVED_IDS:
		result = _POSIX_SAVED_IDS;
		break;

	case _SC_REALTIME_SIGNALS:
		result = _POSIX_REALTIME_SIGNALS;
		break;

	case _SC_PRIORITY_SCHEDULING:
		result = _POSIX_PRIORITY_SCHEDULING;
		break;

	case _SC_TIMERS:
		result = _POSIX_TIMERS;
		break;

	case _SC_ASYNCHRONOUS_IO:
		result = _POSIX_ASYNCHRONOUS_IO;
		break;

	case _SC_PRIORITIZED_IO:
		result = _POSIX_PRIORITIZED_IO;
		break;

	case _SC_SYNCHRONIZED_IO:
		result = _POSIX_SYNCHRONIZED_IO;
		break;

	case _SC_FSYNC:
		result = _POSIX_FSYNC;
		break;

	case _SC_MAPPED_FILES:
		result = _POSIX_MAPPED_FILES;
		break;

	case _SC_MEMLOCK:
		result = _POSIX_MEMLOCK;
		break;

	case _SC_MEMLOCK_RANGE:
		result = _POSIX_MEMLOCK_RANGE;
		break;

	case _SC_MEMORY_PROTECTION:
		result = _POSIX_MEMORY_PROTECTION;
		break;

	case _SC_MESSAGE_PASSING:
		result = _POSIX_MESSAGE_PASSING;
		break;

	case _SC_SEMAPHORES:
		result = _POSIX_SEMAPHORES;
		break;

	case _SC_SHARED_MEMORY_OBJECTS:
		result = _POSIX_SHARED_MEMORY_OBJECTS;
		break;

	case _SC_AIO_LISTIO_MAX:
		result = _POSIX_AIO_LISTIO_MAX;
		break;

	case _SC_AIO_MAX:
		result = _POSIX_AIO_MAX;
		break;

	case _SC_AIO_PRIO_DELTA_MAX:
		result = AIO_PRIO_DELTA_MAX;
		break;

	case _SC_DELAYTIMER_MAX:
		result = DELAYTIMER_MAX;
		break;

	case _SC_MQ_OPEN_MAX:
		result = _POSIX_MQ_OPEN_MAX;
		break;

	case _SC_MQ_PRIO_MAX:
		result = MQ_PRIO_MAX;
		break;

	case _SC_VERSION:
		result = _POSIX_VERSION;
		break;

	case _SC_PAGESIZE:
		result = OS_PAGESIZE;
		break;

	case _SC_RTSIG_MAX:
		result = RTSIG_MAX;
		break;

	case _SC_SEM_NSEMS_MAX:
		result = _POSIX_SEM_NSEMS_MAX;
		break;

	case _SC_SEM_VALUE_MAX:
		result = SEM_VALUE_MAX;
		break;

	case _SC_SIGQUEUE_MAX:
		result = _POSIX_SIGQUEUE_MAX;
		break;

	case _SC_TIMER_MAX:
		result = _POSIX_TIMER_MAX;
		break;

	case _SC_BC_BASE_MAX:
		result = BC_BASE_MAX;
		break;

	case _SC_BC_DIM_MAX:
		result = BC_DIM_MAX;
		break;

	case _SC_BC_SCALE_MAX:
		result = BC_SCALE_MAX;
		break;

	case _SC_BC_STRING_MAX:
		result = BC_STRING_MAX;
		break;

	case _SC_COLL_WEIGHTS_MAX:
		result = COLL_WEIGHTS_MAX;
		break;

	case _SC_EXPR_NEST_MAX:
		result = EXPR_NEST_MAX;
		break;

	case _SC_LINE_MAX:
		result = LINE_MAX; /* NOTE: Can be increased. */
		break;

	case _SC_RE_DUP_MAX:
		result = RE_DUP_MAX;
		break;

	case _SC_CHARCLASS_NAME_MAX:
		result = CHARCLASS_NAME_MAX;
		break;

	case _SC_2_VERSION:
		result = _POSIX2_VERSION;
		break;

	case _SC_2_C_BIND:
#ifdef _POSIX2_C_BIND
		result = _POSIX2_C_BIND;
		break;
#else /* _POSIX2_C_BIND */
		goto unlimited;
#endif /* !_POSIX2_C_BIND */

	case _SC_2_C_DEV:
#ifdef _POSIX2_C_DEV
		result = _POSIX2_C_DEV;
		break;
#else /* _POSIX2_C_DEV */
		goto unlimited;
#endif /* !_POSIX2_C_DEV */

	case _SC_2_FORT_DEV:
#ifdef _POSIX2_FORT_DEV
		result = _POSIX2_FORT_DEV;
		break;
#else /* _POSIX2_FORT_DEV */
		goto unlimited;
#endif /* !_POSIX2_FORT_DEV */

	case _SC_2_FORT_RUN:
#ifdef _POSIX2_FORT_RUN
		result = _POSIX2_FORT_RUN;
		break;
#else /* _POSIX2_FORT_RUN */
		goto unlimited;
#endif /* !_POSIX2_FORT_RUN */

	case _SC_2_SW_DEV:
#ifdef _POSIX2_SW_DEV
		result = _POSIX2_SW_DEV;
		break;
#else /* _POSIX2_SW_DEV */
		goto unlimited;
#endif /* !_POSIX2_SW_DEV */

	case _SC_2_LOCALEDEF:
#ifdef _POSIX2_LOCALEDEF
		result = _POSIX2_LOCALEDEF;
		break;
#else /* _POSIX2_LOCALEDEF */
		goto unlimited;
#endif /* !_POSIX2_LOCALEDEF */

	case _SC_PII:
#ifdef _POSIX_PII
		result = 1;
		break;
#else /* _POSIX_PII */
		goto unlimited;
#endif /* !_POSIX_PII */

	case _SC_PII_XTI:
#ifdef _POSIX_PII_XTI
		result = 1;
		break;
#else /* _POSIX_PII_XTI */
		goto unlimited;
#endif /* !_POSIX_PII_XTI */

	case _SC_PII_SOCKET:
#ifdef _POSIX_PII_SOCKET
		result = 1;
		break;
#else /* _POSIX_PII_SOCKET */
		goto unlimited;
#endif /* !_POSIX_PII_SOCKET */

	case _SC_PII_INTERNET:
#ifdef _POSIX_PII_INTERNET
		result = 1;
		break;
#else /* _POSIX_PII_INTERNET */
		goto unlimited;
#endif /* !_POSIX_PII_INTERNET */

	case _SC_PII_OSI:
#ifdef _POSIX_PII_OSI
		result = 1;
		break;
#else /* _POSIX_PII_OSI */
		goto unlimited;
#endif /* !_POSIX_PII_OSI */

	case _SC_POLL:
#ifdef _POSIX_POLL
		result = 1;
		break;
#else /* _POSIX_POLL */
		goto unlimited;
#endif /* !_POSIX_POLL */

	case _SC_SELECT:
#ifdef _POSIX_SELECT
		result = 1;
		break;
#else /* _POSIX_SELECT */
		goto unlimited;
#endif /* !_POSIX_SELECT */

	case _SC_PII_INTERNET_STREAM:
#ifdef _POSIX_PII_INTERNET_STREAM
		result = 1;
		break;
#else /* _POSIX_PII_INTERNET_STREAM */
		goto unlimited;
#endif /* !_POSIX_PII_INTERNET_STREAM */

	case _SC_PII_INTERNET_DGRAM:
#ifdef _POSIX_PII_INTERNET_DGRAM
		result = 1;
		break;
#else /* _POSIX_PII_INTERNET_DGRAM */
		goto unlimited;
#endif /* !_POSIX_PII_INTERNET_DGRAM */

	case _SC_PII_OSI_COTS:
#ifdef _POSIX_PII_OSI_COTS
		result = 1;
		break;
#else /* _POSIX_PII_OSI_COTS */
		goto unlimited;
#endif /* !_POSIX_PII_OSI_COTS */

	case _SC_PII_OSI_CLTS:
#ifdef _POSIX_PII_OSI_CLTS
		result = 1;
		break;
#else /* _POSIX_PII_OSI_CLTS */
		goto unlimited;
#endif /* !_POSIX_PII_OSI_CLTS */

	case _SC_PII_OSI_M:
#ifdef _POSIX_PII_OSI_M
		result = 1;
		break;
#else /* _POSIX_PII_OSI_M */
		goto unlimited;
#endif /* !_POSIX_PII_OSI_M */

	case _SC_THREADS:
		result = _POSIX_THREADS;
		break;

	case _SC_THREAD_SAFE_FUNCTIONS:
		result = _POSIX_THREAD_SAFE_FUNCTIONS;
		break;

	case _SC_GETGR_R_SIZE_MAX:
		result = NSS_BUFLEN_GROUP;
		break;
	case _SC_GETPW_R_SIZE_MAX:
		result = NSS_BUFLEN_PASSWD;
		break;

	case _SC_LOGIN_NAME_MAX:
		result = LOGIN_NAME_MAX;
		break;

	case _SC_TTY_NAME_MAX:
		result = TTY_NAME_MAX;
		break;

	case _SC_THREAD_DESTRUCTOR_ITERATIONS:
		result = _POSIX_THREAD_DESTRUCTOR_ITERATIONS;
		break;

	case _SC_THREAD_KEYS_MAX:
		result = _POSIX_THREAD_KEYS_MAX;
		break;

	case _SC_THREAD_STACK_MIN:
		result = PTHREAD_STACK_MIN;
		break;

	case _SC_THREAD_ATTR_STACKADDR:
		result = _POSIX_THREAD_ATTR_STACKADDR;
		break;

	case _SC_THREAD_ATTR_STACKSIZE:
		result = _POSIX_THREAD_ATTR_STACKSIZE;
		break;

	case _SC_THREAD_PRIORITY_SCHEDULING:
		result = _POSIX_THREAD_PRIORITY_SCHEDULING;
		break;

	case _SC_THREAD_PRIO_INHERIT:
		result = _POSIX_THREAD_PRIO_INHERIT;
		break;

	case _SC_THREAD_PRIO_PROTECT:
		result = _POSIX_THREAD_PRIO_PROTECT;
		break;

	case _SC_THREAD_PROCESS_SHARED:
		result = _POSIX_THREAD_PROCESS_SHARED;
		break;

	case _SC_NPROCESSORS_CONF:
		result = get_nprocs_conf();
		break;

	case _SC_NPROCESSORS_ONLN:
		result = get_nprocs();
		break;

	case _SC_PHYS_PAGES:
		result = get_phys_pages();
		break;

	case _SC_AVPHYS_PAGES:
		result = get_avphys_pages();
		break;

	case _SC_ATEXIT_MAX:
	case _SC_PASS_MAX:
		result = 1024;
		break;

	case _SC_XOPEN_VERSION:
		result = _XOPEN_VERSION;
		break;

	case _SC_XOPEN_XCU_VERSION:
		result = _XOPEN_XCU_VERSION;
		break;

	case _SC_XOPEN_UNIX:
		result = _XOPEN_UNIX;
		break;

	case _SC_XOPEN_CRYPT:
		result = _XOPEN_CRYPT;
		break;

	case _SC_XOPEN_ENH_I18N:
		result = _XOPEN_ENH_I18N;
		break;

	case _SC_XOPEN_SHM:
		result = _XOPEN_SHM;
		break;

	case _SC_2_CHAR_TERM:
		result = _POSIX2_CHAR_TERM;
		break;

	case _SC_2_C_VERSION:
		result = _POSIX2_C_VERSION;
		break;

	case _SC_2_UPE:
#ifdef _POSIX2_UPE
		result = _POSIX2_UPE;
		break;
#else
		goto unlimited;
#endif

	case _SC_XOPEN_XPG2:
		result = _XOPEN_XPG2;
		break;

	case _SC_XOPEN_XPG3:
		result = _XOPEN_XPG3;
		break;

	case _SC_XOPEN_XPG4:
		result = _XOPEN_XPG4;
		break;

	case _SC_CHAR_BIT:
		result = CHAR_BIT;
		break;

	case _SC_CHAR_MAX:
		result = CHAR_MAX;
		break;

	case _SC_CHAR_MIN:
		result = CHAR_MIN;
		break;

	case _SC_INT_MAX:
		result = INT_MAX;
		break;

	case _SC_INT_MIN:
		result = INT_MIN;
		break;

	case _SC_LONG_BIT:
		result = LONG_BIT;
		break;

	case _SC_WORD_BIT:
		result = WORD_BIT;
		break;

	case _SC_MB_LEN_MAX:
		result = MB_LEN_MAX;
		break;

	case _SC_NZERO:
		result = NZERO;
		break;

	case _SC_SSIZE_MAX:
		result = SSIZE_MAX;
		break;

	case _SC_SCHAR_MAX:
		result = SCHAR_MAX;
		break;

	case _SC_SCHAR_MIN:
		result = SCHAR_MIN;
		break;

	case _SC_SHRT_MAX:
		result = SHRT_MAX;
		break;

	case _SC_SHRT_MIN:
		result = SHRT_MIN;
		break;

	case _SC_UCHAR_MAX:
		result = UCHAR_MAX;
		break;

	case _SC_UINT_MAX:
		result = UINT_MAX;
		break;

	case _SC_ULONG_MAX:
		result = ULONG_MAX;
		break;

	case _SC_USHRT_MAX:
		result = USHRT_MAX;
		break;

	case _SC_NL_ARGMAX:
		result = NL_ARGMAX;
		break;

	case _SC_NL_LANGMAX:
		result = NL_LANGMAX;
		break;

	case _SC_NL_MSGMAX:
		result = NL_MSGMAX;
		break;

	case _SC_NL_NMAX:
		result = NL_NMAX;
		break;

	case _SC_NL_SETMAX:
		result = NL_SETMAX;
		break;

	case _SC_NL_TEXTMAX:
		result = NL_TEXTMAX;
		break;

	case _SC_XOPEN_LEGACY:
		result = _XOPEN_LEGACY;
		break;

	case _SC_XOPEN_REALTIME:
#ifdef _XOPEN_REALTIME
		result = _XOPEN_REALTIME;
		break;
#else /* _XOPEN_REALTIME */
		goto unlimited;
#endif /* !_XOPEN_REALTIME */

	case _SC_XOPEN_REALTIME_THREADS:
#ifdef _XOPEN_REALTIME_THREADS
		result = _XOPEN_REALTIME_THREADS;
		break;
#else /* _XOPEN_REALTIME_THREADS */
		goto unlimited;
#endif /* !_XOPEN_REALTIME_THREADS */

	case _SC_ADVISORY_INFO:
		result = _POSIX_ADVISORY_INFO;
		break;

	case _SC_BARRIERS:
		result = _POSIX_BARRIERS;
		break;

	case _SC_BASE:
#ifdef _POSIX_BASE
		result = _POSIX_BASE;
		break;
#else /* _POSIX_BASE */
		goto unlimited;
#endif /* !_POSIX_BASE */

	case _SC_C_LANG_SUPPORT:
#ifdef _POSIX_C_LANG_SUPPORT
		result = _POSIX_C_LANG_SUPPORT;
		break;
#else /* _POSIX_C_LANG_SUPPORT */
		goto unlimited;
#endif /* !_POSIX_C_LANG_SUPPORT */

	case _SC_C_LANG_SUPPORT_R:
#ifdef _POSIX_C_LANG_SUPPORT_R
		result = _POSIX_C_LANG_SUPPORT_R;
		break;
#else /* _POSIX_C_LANG_SUPPORT_R */
		goto unlimited;
#endif /* !_POSIX_C_LANG_SUPPORT_R */

	case _SC_CLOCK_SELECTION:
#ifdef _POSIX_CLOCK_SELECTION
		result = _POSIX_CLOCK_SELECTION;
		break;
#else /* _POSIX_CLOCK_SELECTION */
		goto unlimited;
#endif /* !_POSIX_CLOCK_SELECTION */

	case _SC_CPUTIME:
#ifdef _POSIX_CPUTIME
		result = _POSIX_CPUTIME;
		break;
#else /* _POSIX_CPUTIME */
		goto unlimited;
#endif /* !_POSIX_CPUTIME */

	case _SC_THREAD_CPUTIME:
#ifdef _POSIX_THREAD_CPUTIME
		result = _POSIX_THREAD_CPUTIME;
		break;
#else /* _POSIX_THREAD_CPUTIME */
		goto unlimited;
#endif /* !_POSIX_THREAD_CPUTIME */

	case _SC_DEVICE_IO:
#ifdef _POSIX_DEVICE_IO
		result = _POSIX_DEVICE_IO;
		break;
#else /* _POSIX_DEVICE_IO */
		goto unlimited;
#endif /* !_POSIX_DEVICE_IO */

	case _SC_DEVICE_SPECIFIC:
#ifdef _POSIX_DEVICE_SPECIFIC
		result = _POSIX_DEVICE_SPECIFIC;
		break;
#else /* _POSIX_DEVICE_SPECIFIC */
		goto unlimited;
#endif /* !_POSIX_DEVICE_SPECIFIC */

	case _SC_DEVICE_SPECIFIC_R:
#ifdef _POSIX_DEVICE_SPECIFIC_R
		result = _POSIX_DEVICE_SPECIFIC_R;
		break;
#else /* _POSIX_DEVICE_SPECIFIC_R */
		goto unlimited;
#endif /* !_POSIX_DEVICE_SPECIFIC_R */

	case _SC_FD_MGMT:
#ifdef _POSIX_FD_MGMT
		result = _POSIX_FD_MGMT;
		break;
#else /* _POSIX_FD_MGMT */
		goto unlimited;
#endif /* !_POSIX_FD_MGMT */

	case _SC_FIFO:
#ifdef _POSIX_FIFO
		result = _POSIX_FIFO;
		break;
#else /* _POSIX_FIFO */
		goto unlimited;
#endif /* !_POSIX_FIFO */

	case _SC_PIPE:
#ifdef _POSIX_PIPE
		result = _POSIX_PIPE;
		break;
#else /* _POSIX_PIPE */
		goto unlimited;
#endif /* !_POSIX_PIPE */

	case _SC_FILE_ATTRIBUTES:
#ifdef _POSIX_FILE_ATTRIBUTES
		result = _POSIX_FILE_ATTRIBUTES;
		break;
#else /* _POSIX_FILE_ATTRIBUTES */
		goto unlimited;
#endif /* !_POSIX_FILE_ATTRIBUTES */

	case _SC_FILE_LOCKING:
#ifdef _POSIX_FILE_LOCKING
		result = _POSIX_FILE_LOCKING;
		break;
#else /* _POSIX_FILE_LOCKING */
		goto unlimited;
#endif /* !_POSIX_FILE_LOCKING */

	case _SC_FILE_SYSTEM:
#ifdef _POSIX_FILE_SYSTEM
		result = _POSIX_FILE_SYSTEM;
		break;
#else /* _POSIX_FILE_SYSTEM */
		goto unlimited;
#endif /* !_POSIX_FILE_SYSTEM */


	case _SC_MONOTONIC_CLOCK:
#ifdef _POSIX_MONOTONIC_CLOCK
		result = _POSIX_MONOTONIC_CLOCK;
		break;
#else /* _POSIX_MONOTONIC_CLOCK */
		goto unlimited;
#endif /* !_POSIX_MONOTONIC_CLOCK */

	case _SC_MULTI_PROCESS:
#ifdef _POSIX_MULTI_PROCESS
		result = _POSIX_MULTI_PROCESS;
		break;
#else /* _POSIX_MULTI_PROCESS */
		goto unlimited;
#endif /* !_POSIX_MULTI_PROCESS */

	case _SC_SINGLE_PROCESS:
#ifdef _POSIX_SINGLE_PROCESS
		result = _POSIX_SINGLE_PROCESS;
		break;
#else /* _POSIX_SINGLE_PROCESS */
		goto unlimited;
#endif /* !_POSIX_SINGLE_PROCESS */

	case _SC_NETWORKING:
#ifdef _POSIX_NETWORKING
		result = _POSIX_NETWORKING;
		break;
#else /* _POSIX_NETWORKING */
		goto unlimited;
#endif /* !_POSIX_NETWORKING */

	case _SC_READER_WRITER_LOCKS:
#ifdef _POSIX_READER_WRITER_LOCKS
		result = _POSIX_READER_WRITER_LOCKS;
		break;
#else /* _POSIX_READER_WRITER_LOCKS */
		goto unlimited;
#endif /* !_POSIX_READER_WRITER_LOCKS */

	case _SC_SPIN_LOCKS:
#ifdef _POSIX_SPIN_LOCKS
		result = _POSIX_SPIN_LOCKS;
		break;
#else /* _POSIX_SPIN_LOCKS */
		goto unlimited;
#endif /* !_POSIX_SPIN_LOCKS */

	case _SC_REGEXP:
#ifdef _POSIX_REGEXP
		result = _POSIX_REGEXP;
		break;
#else /* _POSIX_REGEXP */
		goto unlimited;
#endif /* !_POSIX_REGEXP */

	case _SC_SHELL:
#ifdef _POSIX_SHELL
		result = _POSIX_SHELL;
		break;
#else /* _POSIX_SHELL */
		goto unlimited;
#endif /* !_POSIX_SHELL */

	case _SC_SIGNALS:
#ifdef _POSIX_SIGNALS
		result = _POSIX_SIGNALS;
		break;
#else /* _POSIX_SIGNALS */
		goto unlimited;
#endif /* !_POSIX_SIGNALS */

	case _SC_SPAWN:
#ifdef _POSIX_SPAWN
		result = _POSIX_SPAWN;
		break;
#else /* _POSIX_SPAWN */
		goto unlimited;
#endif /* !_POSIX_SPAWN */

	case _SC_SPORADIC_SERVER:
#ifdef _POSIX_SPORADIC_SERVER
		result = _POSIX_SPORADIC_SERVER;
		break;
#else /* _POSIX_SPORADIC_SERVER */
		goto unlimited;
#endif /* !_POSIX_SPORADIC_SERVER */

	case _SC_THREAD_SPORADIC_SERVER:
#ifdef _POSIX_THREAD_SPORADIC_SERVER
		result = _POSIX_THREAD_SPORADIC_SERVER;
		break;
#else /* _POSIX_THREAD_SPORADIC_SERVER */
		goto unlimited;
#endif /* !_POSIX_THREAD_SPORADIC_SERVER */

	case _SC_SYSTEM_DATABASE:
#ifdef _POSIX_SYSTEM_DATABASE
		result = _POSIX_SYSTEM_DATABASE;
		break;
#else /* _POSIX_SYSTEM_DATABASE */
		goto unlimited;
#endif /* !_POSIX_SYSTEM_DATABASE */

	case _SC_SYSTEM_DATABASE_R:
#ifdef _POSIX_SYSTEM_DATABASE_R
		result = _POSIX_SYSTEM_DATABASE_R;
		break;
#else /* _POSIX_SYSTEM_DATABASE_R */
		goto unlimited;
#endif /* !_POSIX_SYSTEM_DATABASE_R */

	case _SC_TIMEOUTS:
#ifdef _POSIX_TIMEOUTS
		result = _POSIX_TIMEOUTS;
		break;
#else /* _POSIX_TIMEOUTS */
		goto unlimited;
#endif /* !_POSIX_TIMEOUTS */

	case _SC_TYPED_MEMORY_OBJECTS:
#ifdef _POSIX_TYPED_MEMORY_OBJECTS
		result = _POSIX_TYPED_MEMORY_OBJECTS;
		break;
#else /* _POSIX_TYPED_MEMORY_OBJECTS */
		goto unlimited;
#endif /* !_POSIX_TYPED_MEMORY_OBJECTS */

	case _SC_USER_GROUPS:
#ifdef _POSIX_USER_GROUPS
		result = _POSIX_USER_GROUPS;
		break;
#else /* _POSIX_USER_GROUPS */
		goto unlimited;
#endif /* !_POSIX_USER_GROUPS */

	case _SC_USER_GROUPS_R:
#ifdef _POSIX_USER_GROUPS_R
		result = _POSIX_USER_GROUPS_R;
		break;
#else /* _POSIX_USER_GROUPS_R */
		goto unlimited;
#endif /* !_POSIX_USER_GROUPS_R */

	case _SC_2_PBS:
#ifdef _POSIX2_PBS
		result = _POSIX2_PBS;
		break;
#else /* _POSIX2_PBS */
		goto unlimited;
#endif /* !_POSIX2_PBS */

	case _SC_2_PBS_ACCOUNTING:
#ifdef _POSIX2_PBS_ACCOUNTING
		result = _POSIX2_PBS_ACCOUNTING;
		break;
#else /* _POSIX2_PBS_ACCOUNTING */
		goto unlimited;
#endif /* !_POSIX2_PBS_ACCOUNTING */

	case _SC_2_PBS_LOCATE:
#ifdef _POSIX2_PBS_LOCATE
		result = _POSIX2_PBS_LOCATE;
		break;
#else /* _POSIX2_PBS_LOCATE */
		goto unlimited;
#endif /* !_POSIX2_PBS_LOCATE */

	case _SC_2_PBS_MESSAGE:
#ifdef _POSIX2_PBS_MESSAGE
		result = _POSIX2_PBS_MESSAGE;
		break;
#else /* _POSIX2_PBS_MESSAGE */
		goto unlimited;
#endif /* !_POSIX2_PBS_MESSAGE */

	case _SC_2_PBS_TRACK:
#ifdef _POSIX2_PBS_TRACK
		result = _POSIX2_PBS_TRACK;
		break;
#else /* _POSIX2_PBS_TRACK */
		goto unlimited;
#endif /* !_POSIX2_PBS_TRACK */

	case _SC_SYMLOOP_MAX:
		result = MAXSYMLINKS; /* TODO: Kernel:`THIS_FS->f_lnkmax' */
		break;

	case _SC_2_PBS_CHECKPOINT:
#ifdef _POSIX2_PBS_CHECKPOINT
		result = _POSIX2_PBS_CHECKPOINT;
		break;
#else /* _POSIX2_PBS_CHECKPOINT */
		goto unlimited;
#endif /* !_POSIX2_PBS_CHECKPOINT */

	case _SC_HOST_NAME_MAX:
		result = HOST_NAME_MAX;
		break;

	case _SC_TRACE:
#ifdef _POSIX_TRACE
		result = _POSIX_TRACE;
		break;
#else /* _POSIX_TRACE */
		goto unlimited;
#endif /* !_POSIX_TRACE */

	case _SC_TRACE_EVENT_FILTER:
#ifdef _POSIX_TRACE_EVENT_FILTER
		result = _POSIX_TRACE_EVENT_FILTER;
		break;
#else /* _POSIX_TRACE_EVENT_FILTER */
		goto unlimited;
#endif /* !_POSIX_TRACE_EVENT_FILTER */

	case _SC_TRACE_INHERIT:
#ifdef _POSIX_TRACE_INHERIT
		result = _POSIX_TRACE_INHERIT;
		break;
#else /* _POSIX_TRACE_INHERIT */
		goto unlimited;
#endif /* !_POSIX_TRACE_INHERIT */

	case _SC_TRACE_LOG:
#ifdef _POSIX_TRACE_LOG
		result = _POSIX_TRACE_LOG;
		break;
#else /* _POSIX_TRACE_LOG */
		goto unlimited;
#endif /* !_POSIX_TRACE_LOG */

	case _SC_LEVEL1_ICACHE_SIZE:
	case _SC_LEVEL1_ICACHE_ASSOC:
	case _SC_LEVEL1_ICACHE_LINESIZE:
	case _SC_LEVEL1_DCACHE_SIZE:
	case _SC_LEVEL1_DCACHE_ASSOC:
	case _SC_LEVEL1_DCACHE_LINESIZE:
	case _SC_LEVEL2_CACHE_SIZE:
	case _SC_LEVEL2_CACHE_ASSOC:
	case _SC_LEVEL2_CACHE_LINESIZE:
	case _SC_LEVEL3_CACHE_SIZE:
	case _SC_LEVEL3_CACHE_ASSOC:
	case _SC_LEVEL3_CACHE_LINESIZE:
	case _SC_LEVEL4_CACHE_SIZE:
	case _SC_LEVEL4_CACHE_ASSOC:
	case _SC_LEVEL4_CACHE_LINESIZE:
		result = 0;
		break;

	case _SC_IPV6:
#ifdef _POSIX_IPV6
		result = _POSIX_IPV6;
		break;
#else
		goto unlimited;
#endif

	case _SC_RAW_SOCKETS:
#ifdef _POSIX_RAW_SOCKETS
		result = _POSIX_RAW_SOCKETS;
		break;
#else
		goto unlimited;
#endif

	case _SC_SS_REPL_MAX:
#ifdef _POSIX_SS_REPL_MAX
		result = _POSIX_SS_REPL_MAX;
		break;
#else
		goto unlimited;
#endif

	case _SC_THREAD_ROBUST_PRIO_INHERIT:
#ifdef _POSIX_THREAD_ROBUST_PRIO_INHERIT
		result = _POSIX_THREAD_ROBUST_PRIO_INHERIT;
		break;
#else
		goto unlimited;
#endif

	case _SC_THREAD_ROBUST_PRIO_PROTECT:
#ifdef _POSIX_THREAD_ROBUST_PRIO_PROTECT
		result = _POSIX_THREAD_ROBUST_PRIO_PROTECT;
		break;
#else
		goto unlimited;
#endif

	default:
	case _SC_EQUIV_CLASS_MAX:
	case _SC_V6_ILP32_OFF32:
	case _SC_V6_ILP32_OFFBIG:
	case _SC_V6_LP64_OFF64:
	case _SC_V6_LPBIG_OFFBIG:
	case _SC_XBS5_ILP32_OFF32:
	case _SC_XBS5_ILP32_OFFBIG:
	case _SC_XBS5_LP64_OFF64:
	case _SC_XBS5_LPBIG_OFFBIG:
	case _SC_V7_ILP32_OFF32:
	case _SC_V7_ILP32_OFFBIG:
	case _SC_V7_LP64_OFF64:
	case _SC_V7_LPBIG_OFFBIG:
		libc_seterrno(EINVAL);
		ATTR_FALLTHROUGH
	case _SC_TZNAME_MAX:           /* Unlimited */
	case _SC_ARG_MAX:              /* Unlimited */
	case _SC_CHILD_MAX:            /* Unlimited */
	case _SC_OPEN_MAX:             /* Unlimited */
	case _SC_THREAD_THREADS_MAX:   /* Unlimited */
	case _SC_UIO_MAXIOV:           /* Unlimited */
	case _SC_T_IOV_MAX:            /* Unlimited */
	case _SC_REGEX_VERSION:        /* Deprecated */
	case _SC_STREAMS:              /* Unsupported */
	case _SC_TRACE_EVENT_NAME_MAX: /* Unsupported */
	case _SC_TRACE_NAME_MAX:       /* Unsupported */
	case _SC_TRACE_SYS_MAX:        /* Unsupported */
	case _SC_TRACE_USER_EVENT_MAX: /* Unsupported */
	case _SC_XOPEN_STREAMS:        /* Unsupported */
unlimited: ATTR_UNUSED;
		result = -1;
		break;
	}
	return result;
}
/*[[[end:libc_sysconf]]]*/

/*[[[head:libc_freadlinkat,hash:CRC-32=0x738f4274]]]*/
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
INTERN ATTR_SECTION(".text.crt.fs.property") NONNULL((2, 3)) ssize_t
NOTHROW_RPC(LIBCCALL libc_freadlinkat)(fd_t dfd,
                                       char const *__restrict path,
                                       char *__restrict buf,
                                       size_t buflen,
                                       atflag_t flags)
/*[[[body:libc_freadlinkat]]]*/
{
	ssize_t result;
	result = sys_freadlinkat(dfd, path, buf, buflen, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_freadlinkat]]]*/

/*[[[head:libc_readall,hash:CRC-32=0xab651c4f]]]*/
/* >> readall(3)
 * Same as `read(2)', however keep on reading until `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If an error occurrs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
INTERN ATTR_SECTION(".text.crt.io.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_readall)(fd_t fd,
                                   void *buf,
                                   size_t bufsize)
/*[[[body:libc_readall]]]*/
{
	ssize_t result, temp;
	result = read(fd, buf, bufsize);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = read(fd,
			            (byte_t *)buf + (size_t)result,
			            bufsize - (size_t)result);
			if (temp <= 0) {
				errno_t old_error = libc_geterrno();
				/* Try to un-read data that had already been loaded. */
				libc_lseek64(fd, -(off64_t)(pos64_t)result, SEEK_CUR);
				libc_seterrno(old_error);
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
/*[[[end:libc_readall]]]*/

/*[[[head:libc_writeall,hash:CRC-32=0xa9ae1bd1]]]*/
/* >> writeall(3)
 * Same as `write(2)', however keep on writing until `write()' indicates EOF (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
INTERN ATTR_SECTION(".text.crt.io.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_writeall)(fd_t fd,
                                    void const *buf,
                                    size_t bufsize)
/*[[[body:libc_writeall]]]*/
{
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
/*[[[end:libc_writeall]]]*/

/*[[[head:libc_preadall,hash:CRC-32=0x208b5ffc]]]*/
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTERN ATTR_SECTION(".text.crt.io.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_preadall)(fd_t fd,
                                    void *buf,
                                    size_t bufsize,
                                    __PIO_OFFSET offset)
/*[[[body:libc_preadall]]]*/
{
	ssize_t result, temp;
	result = pread(fd, buf, bufsize, offset);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = pread(fd,
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
/*[[[end:libc_preadall]]]*/

/*[[[head:libc_preadall64,hash:CRC-32=0x65d5e44c]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_preadall64, libc_preadall);
#else /* MAGIC:alias */
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
INTERN ATTR_SECTION(".text.crt.io.large.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_preadall64)(fd_t fd,
                                      void *buf,
                                      size_t bufsize,
                                      __PIO_OFFSET64 offset)
/*[[[body:libc_preadall64]]]*/
{
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
#endif /* MAGIC:alias */
/*[[[end:libc_preadall64]]]*/

/*[[[head:libc_pwriteall,hash:CRC-32=0x61cf24d8]]]*/
/* >> pwriteall(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
INTERN ATTR_SECTION(".text.crt.io.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_pwriteall)(fd_t fd,
                                     void const *buf,
                                     size_t bufsize,
                                     __PIO_OFFSET offset)
/*[[[body:libc_pwriteall]]]*/
{
	ssize_t result, temp;
	result = pwrite(fd, buf, bufsize, offset);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on writing */
		for (;;) {
			temp = pwrite(fd,
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
/*[[[end:libc_pwriteall]]]*/

/*[[[head:libc_pwriteall64,hash:CRC-32=0x4aa10dd8]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_pwriteall64, libc_pwriteall);
#else /* MAGIC:alias */
/* >> pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite64(2)' instead of `write()' */
INTERN ATTR_SECTION(".text.crt.io.large.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_pwriteall64)(fd_t fd,
                                       void *buf,
                                       size_t bufsize,
                                       __PIO_OFFSET64 offset)
/*[[[body:libc_pwriteall64]]]*/
{
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
#endif /* MAGIC:alias */
/*[[[end:libc_pwriteall64]]]*/

#if !defined(__OPTIMIZE_SIZE__) && \
    !defined(__NO_ATTR_THREAD)
#define HAVE_CACHED_TID 1
PRIVATE ATTR_THREAD pid_t cached_tid = 0;
#endif

/*[[[head:libc_gettid,hash:CRC-32=0xccb67c13]]]*/
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
INTERN ATTR_SECTION(".text.crt.sched.thread") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_gettid)(void)
/*[[[body:libc_gettid]]]*/
{
#ifdef HAVE_CACHED_TID
	pid_t result;
	/* Cache the TID as a thread-local variable */
	result = cached_tid;
	if (!result) {
		result = sys_gettid();
		if unlikely(E_ISERR(result))
			return (pid_t)libc_seterrno(-result);
		cached_tid = result;
	}
	return result;
#else
	pid_t result = sys_gettid();
	return libc_seterrno_syserr(result);
#endif
}
/*[[[end:libc_gettid]]]*/

/*[[[head:libc_sync,hash:CRC-32=0x1431d596]]]*/
/* >> sync(2)
 * Synchronize all disk operations of all mounted file systems and flush
 * unwritten buffers down to the hardware layer, ensuring that modifications
 * made become visible on the underlying, persistent media */
INTERN ATTR_SECTION(".text.crt.fs.modify") void
NOTHROW_RPC(LIBCCALL libc_sync)(void)
/*[[[body:libc_sync]]]*/
{
	sys_sync();
}
/*[[[end:libc_sync]]]*/

/*[[[head:libc_syncfs,hash:CRC-32=0x95a3c051]]]*/
INTERN ATTR_SECTION(".text.crt.fs.modify") int
NOTHROW_RPC(LIBCCALL libc_syncfs)(fd_t fd)
/*[[[body:libc_syncfs]]]*/
{
	errno_t error;
	error = sys_syncfs(fd);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_syncfs]]]*/

/*[[[head:libc_nice,hash:CRC-32=0x314a2f67]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") int
NOTHROW_NCX(LIBCCALL libc_nice)(int inc)
/*[[[body:libc_nice]]]*/
{
	syscall_slong_t error;
#ifdef __sys_nice_defined
	error = sys_nice(-inc);
	if unlikely(E_ISERR(error))
		goto err;
#else /* __sys_Xnice_defined */
	error = sys_getpriority(PRIO_PROCESS, 0);
	if unlikely(E_ISERR(error))
		goto err;
	error = (20 - error);
	error += inc;
	error = sys_setpriority(PRIO_PROCESS, 0, (syscall_ulong_t)(20 - error));
	if unlikely(E_ISERR(error))
		goto err;
	error = sys_getpriority(PRIO_PROCESS, 0);
	if unlikely(E_ISERR(error))
		goto err;
#endif /* !__sys_Xnice_defined */
	return 20 - error;
err:
	libc_seterrno(-error);
	return -1;
}
/*[[[end:libc_nice]]]*/

/*[[[head:libc_fsync,hash:CRC-32=0x9bcfb5e6]]]*/
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
INTERN ATTR_SECTION(".text.crt.io.sync") int
NOTHROW_RPC(LIBCCALL libc_fsync)(fd_t fd)
/*[[[body:libc_fsync]]]*/
{
	errno_t error;
	error = sys_fsync(fd);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_fsync]]]*/

/*[[[head:libc_fdatasync,hash:CRC-32=0xcadd0612]]]*/
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
INTERN ATTR_SECTION(".text.crt.io.sync") int
NOTHROW_RPC(LIBCCALL libc_fdatasync)(fd_t fd)
/*[[[body:libc_fdatasync]]]*/
{
	errno_t error;
	error = sys_fdatasync(fd);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_fdatasync]]]*/

/*[[[head:libc_ctermid_r,hash:CRC-32=0xf415d72d]]]*/
/* Same as `ctermid', but return `NULL' when `S' is `NULL' */
INTERN ATTR_SECTION(".text.crt.io.tty") char *
NOTHROW_NCX(LIBCCALL libc_ctermid_r)(char *s)
/*[[[body:libc_ctermid_r]]]*/
/*AUTO*/{
	return s ? ctermid(s) : NULL;
}
/*[[[end:libc_ctermid_r]]]*/


/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x8eac1e83]]]*/
DEFINE_PUBLIC_ALIAS(_execv, libc_execv);
DEFINE_PUBLIC_ALIAS(execv, libc_execv);
DEFINE_PUBLIC_ALIAS(_execve, libc_execve);
DEFINE_PUBLIC_ALIAS(execve, libc_execve);
DEFINE_PUBLIC_ALIAS(_execvp, libc_execvp);
DEFINE_PUBLIC_ALIAS(execvp, libc_execvp);
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$_execl, libd_execl);
DEFINE_PUBLIC_ALIAS(DOS$execl, libd_execl);
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(_execl, libc_execl);
DEFINE_PUBLIC_ALIAS(execl, libc_execl);
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$_execle, libd_execle);
DEFINE_PUBLIC_ALIAS(DOS$execle, libd_execle);
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(_execle, libc_execle);
DEFINE_PUBLIC_ALIAS(execle, libc_execle);
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$_execlp, libd_execlp);
DEFINE_PUBLIC_ALIAS(DOS$execlp, libd_execlp);
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(_execlp, libc_execlp);
DEFINE_PUBLIC_ALIAS(execlp, libc_execlp);
DEFINE_PUBLIC_ALIAS(_execvpe, libc_execvpe);
DEFINE_PUBLIC_ALIAS(execvpe, libc_execvpe);
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$_execlpe, libd_execlpe);
DEFINE_PUBLIC_ALIAS(DOS$execlpe, libd_execlpe);
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(_execlpe, libc_execlpe);
DEFINE_PUBLIC_ALIAS(execlpe, libc_execlpe);
DEFINE_PUBLIC_ALIAS(_getpid, libc_getpid);
DEFINE_PUBLIC_ALIAS(__getpid, libc_getpid);
DEFINE_PUBLIC_ALIAS(getpid, libc_getpid);
DEFINE_PUBLIC_ALIAS(gettid, libc_gettid);
DEFINE_PUBLIC_ALIAS(__pipe, libc_pipe);
DEFINE_PUBLIC_ALIAS(pipe, libc_pipe);
DEFINE_PUBLIC_ALIAS(sleep, libc_sleep);
DEFINE_PUBLIC_ALIAS(_commit, libc_fsync);
DEFINE_PUBLIC_ALIAS(fsync, libc_fsync);
DEFINE_PUBLIC_ALIAS(getppid, libc_getppid);
DEFINE_PUBLIC_ALIAS(getpgrp, libc_getpgrp);
DEFINE_PUBLIC_ALIAS(__setpgid, libc_setpgid);
DEFINE_PUBLIC_ALIAS(setpgid, libc_setpgid);
DEFINE_PUBLIC_ALIAS(setsid, libc_setsid);
DEFINE_PUBLIC_ALIAS(getuid, libc_getuid);
DEFINE_PUBLIC_ALIAS(geteuid, libc_geteuid);
DEFINE_PUBLIC_ALIAS(getgid, libc_getgid);
DEFINE_PUBLIC_ALIAS(getegid, libc_getegid);
DEFINE_PUBLIC_ALIAS(getgroups, libc_getgroups);
DEFINE_PUBLIC_ALIAS(setuid, libc_setuid);
DEFINE_PUBLIC_ALIAS(setgid, libc_setgid);
DEFINE_PUBLIC_ALIAS(__fork, libc_fork);
DEFINE_PUBLIC_ALIAS(fork, libc_fork);
DEFINE_PUBLIC_ALIAS(alarm, libc_alarm);
DEFINE_PUBLIC_ALIAS(pause, libc_pause);
DEFINE_PUBLIC_ALIAS(fpathconf, libc_fpathconf);
DEFINE_PUBLIC_ALIAS(ttyname, libc_ttyname);
DEFINE_PUBLIC_ALIAS(ttyname_r, libc_ttyname_r);
DEFINE_PUBLIC_ALIAS(tcgetpgrp, libc_tcgetpgrp);
DEFINE_PUBLIC_ALIAS(tcsetpgrp, libc_tcsetpgrp);
DEFINE_PUBLIC_ALIAS(getlogin, libc_getlogin);
DEFINE_PUBLIC_ALIAS(chown, libc_chown);
DEFINE_PUBLIC_ALIAS(pathconf, libc_pathconf);
DEFINE_PUBLIC_ALIAS(link, libc_link);
DEFINE_PUBLIC_ALIAS(_read, libc_read);
DEFINE_PUBLIC_ALIAS(__read, libc_read);
DEFINE_PUBLIC_ALIAS(read, libc_read);
DEFINE_PUBLIC_ALIAS(_write, libc_write);
DEFINE_PUBLIC_ALIAS(__write, libc_write);
DEFINE_PUBLIC_ALIAS(write, libc_write);
DEFINE_PUBLIC_ALIAS(readall, libc_readall);
DEFINE_PUBLIC_ALIAS(writeall, libc_writeall);
DEFINE_PUBLIC_ALIAS(_lseek, libc_lseek);
DEFINE_PUBLIC_ALIAS(__lseek, libc_lseek);
DEFINE_PUBLIC_ALIAS(lseek, libc_lseek);
DEFINE_PUBLIC_ALIAS(_isatty, libc_isatty);
DEFINE_PUBLIC_ALIAS(isatty, libc_isatty);
DEFINE_PUBLIC_ALIAS(_dup2, libc_dup2);
DEFINE_PUBLIC_ALIAS(__dup2, libc_dup2);
DEFINE_PUBLIC_ALIAS(dup2, libc_dup2);
DEFINE_PUBLIC_ALIAS(_dup, libc_dup);
DEFINE_PUBLIC_ALIAS(dup, libc_dup);
DEFINE_PUBLIC_ALIAS(_close, libc_close);
DEFINE_PUBLIC_ALIAS(__close, libc_close);
DEFINE_PUBLIC_ALIAS(close, libc_close);
DEFINE_PUBLIC_ALIAS(_access, libc_access);
DEFINE_PUBLIC_ALIAS(access, libc_access);
DEFINE_PUBLIC_ALIAS(_chdir, libc_chdir);
DEFINE_PUBLIC_ALIAS(chdir, libc_chdir);
DEFINE_PUBLIC_ALIAS(_getcwd, libc_getcwd);
DEFINE_PUBLIC_ALIAS(getcwd, libc_getcwd);
DEFINE_PUBLIC_ALIAS(_unlink, libc_unlink);
DEFINE_PUBLIC_ALIAS(unlink, libc_unlink);
DEFINE_PUBLIC_ALIAS(_rmdir, libc_rmdir);
DEFINE_PUBLIC_ALIAS(rmdir, libc_rmdir);
DEFINE_PUBLIC_ALIAS(eaccess, libc_euidaccess);
DEFINE_PUBLIC_ALIAS(euidaccess, libc_euidaccess);
DEFINE_PUBLIC_ALIAS(faccessat, libc_faccessat);
DEFINE_PUBLIC_ALIAS(fchownat, libc_fchownat);
DEFINE_PUBLIC_ALIAS(linkat, libc_linkat);
DEFINE_PUBLIC_ALIAS(symlinkat, libc_symlinkat);
DEFINE_PUBLIC_ALIAS(readlinkat, libc_readlinkat);
DEFINE_PUBLIC_ALIAS(freadlinkat, libc_freadlinkat);
DEFINE_PUBLIC_ALIAS(unlinkat, libc_unlinkat);
DEFINE_PUBLIC_ALIAS(_lseeki64, libc_lseek64);
DEFINE_PUBLIC_ALIAS(lseek64, libc_lseek64);
DEFINE_PUBLIC_ALIAS(pread, libc_pread);
DEFINE_PUBLIC_ALIAS(pwrite, libc_pwrite);
DEFINE_PUBLIC_ALIAS(preadall, libc_preadall);
DEFINE_PUBLIC_ALIAS(pwriteall, libc_pwriteall);
DEFINE_PUBLIC_ALIAS(__pread64, libc_pread64);
DEFINE_PUBLIC_ALIAS(pread64, libc_pread64);
DEFINE_PUBLIC_ALIAS(__pwrite64, libc_pwrite64);
DEFINE_PUBLIC_ALIAS(pwrite64, libc_pwrite64);
DEFINE_PUBLIC_ALIAS(preadall64, libc_preadall64);
DEFINE_PUBLIC_ALIAS(pwriteall64, libc_pwriteall64);
DEFINE_PUBLIC_ALIAS(pipe2, libc_pipe2);
DEFINE_PUBLIC_ALIAS(dup3, libc_dup3);
DEFINE_PUBLIC_ALIAS(get_current_dir_name, libc_get_current_dir_name);
DEFINE_PUBLIC_ALIAS(syncfs, libc_syncfs);
DEFINE_PUBLIC_ALIAS(group_member, libc_group_member);
DEFINE_PUBLIC_ALIAS(getresuid, libc_getresuid);
DEFINE_PUBLIC_ALIAS(getresgid, libc_getresgid);
DEFINE_PUBLIC_ALIAS(setresuid, libc_setresuid);
DEFINE_PUBLIC_ALIAS(setresgid, libc_setresgid);
DEFINE_PUBLIC_ALIAS(usleep, libc_usleep);
DEFINE_PUBLIC_ALIAS(getwd, libc_getwd);
DEFINE_PUBLIC_ALIAS(ualarm, libc_ualarm);
DEFINE_PUBLIC_ALIAS(__vfork, libc_vfork);
DEFINE_PUBLIC_ALIAS(vfork, libc_vfork);
DEFINE_PUBLIC_ALIAS(fchown, libc_fchown);
DEFINE_PUBLIC_ALIAS(fchdir, libc_fchdir);
DEFINE_PUBLIC_ALIAS(__getpgid, libc_getpgid);
DEFINE_PUBLIC_ALIAS(getpgid, libc_getpgid);
DEFINE_PUBLIC_ALIAS(getsid, libc_getsid);
DEFINE_PUBLIC_ALIAS(lchown, libc_lchown);
DEFINE_PUBLIC_ALIAS(truncate, libc_truncate);
DEFINE_PUBLIC_ALIAS(truncate64, libc_truncate64);
DEFINE_PUBLIC_ALIAS(fexecve, libc_fexecve);
DEFINE_PUBLIC_ALIAS(nice, libc_nice);
DEFINE_PUBLIC_ALIAS(confstr, libc_confstr);
DEFINE_PUBLIC_ALIAS(sync, libc_sync);
DEFINE_PUBLIC_ALIAS(setpgrp, libc_setpgrp);
DEFINE_PUBLIC_ALIAS(setreuid, libc_setreuid);
DEFINE_PUBLIC_ALIAS(setregid, libc_setregid);
DEFINE_PUBLIC_ALIAS(gethostid, libc_gethostid);
DEFINE_PUBLIC_ALIAS(seteuid, libc_seteuid);
DEFINE_PUBLIC_ALIAS(setegid, libc_setegid);
DEFINE_PUBLIC_ALIAS(ttyslot, libc_ttyslot);
DEFINE_PUBLIC_ALIAS(symlink, libc_symlink);
DEFINE_PUBLIC_ALIAS(readlink, libc_readlink);
DEFINE_PUBLIC_ALIAS(getlogin_r, libc_getlogin_r);
DEFINE_PUBLIC_ALIAS(gethostname, libc_gethostname);
DEFINE_PUBLIC_ALIAS(setlogin, libc_setlogin);
DEFINE_PUBLIC_ALIAS(sethostname, libc_sethostname);
DEFINE_PUBLIC_ALIAS(sethostid, libc_sethostid);
DEFINE_PUBLIC_ALIAS(getdomainname, libc_getdomainname);
DEFINE_PUBLIC_ALIAS(setdomainname, libc_setdomainname);
DEFINE_PUBLIC_ALIAS(vhangup, libc_vhangup);
DEFINE_PUBLIC_ALIAS(profil, libc_profil);
DEFINE_PUBLIC_ALIAS(getusershell, libc_getusershell);
DEFINE_PUBLIC_ALIAS(endusershell, libc_endusershell);
DEFINE_PUBLIC_ALIAS(setusershell, libc_setusershell);
DEFINE_PUBLIC_ALIAS(daemon, libc_daemon);
DEFINE_PUBLIC_ALIAS(revoke, libc_revoke);
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$syscall, libd_syscall);
DEFINE_PUBLIC_ALIAS(DOS$syscall64, libd_syscall64);
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(chroot, libc_chroot);
DEFINE_PUBLIC_ALIAS(getpass, libc_getpass);
DEFINE_PUBLIC_ALIAS(_chsize, libc_ftruncate);
DEFINE_PUBLIC_ALIAS(chsize, libc_ftruncate);
DEFINE_PUBLIC_ALIAS(ftruncate, libc_ftruncate);
DEFINE_PUBLIC_ALIAS(_chsize_s, libc_ftruncate64);
DEFINE_PUBLIC_ALIAS(ftruncate64, libc_ftruncate64);
DEFINE_PUBLIC_ALIAS(brk, libc_brk);
DEFINE_PUBLIC_ALIAS(__sbrk, libc_sbrk);
DEFINE_PUBLIC_ALIAS(sbrk, libc_sbrk);
DEFINE_PUBLIC_ALIAS(fdatasync, libc_fdatasync);
DEFINE_PUBLIC_ALIAS(ctermid, libc_ctermid);
DEFINE_PUBLIC_ALIAS(ctermid_r, libc_ctermid_r);
DEFINE_PUBLIC_ALIAS(_sysconf, libc_sysconf);
DEFINE_PUBLIC_ALIAS(__sysconf, libc_sysconf);
DEFINE_PUBLIC_ALIAS(sysconf, libc_sysconf);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_UNISTD_C */
