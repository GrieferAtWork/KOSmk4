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
#ifndef GUARD_LIBC_USER_KOS_UNISTD_C
#define GUARD_LIBC_USER_KOS_UNISTD_C 1

#include "../api.h"
/**/

#include <kos/except.h>
#include <kos/malloc.h>
#include <kos/syscalls.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <sys/utsname.h>

#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../libc/globals.h"
#include "../libc/capture-varargs.h"
#include "kos.unistd.h"

DECL_BEGIN



/*[[[head:libc_Execv,hash:CRC-32=0x8d22d342]]]*/
/* >> execv(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN NONNULL((1, 2)) void
(LIBCCALL libc_Execv)(char const *__restrict path,
                      __TARGV) THROWS(...)
/*[[[body:libc_Execv]]]*/
{
	sys_Xexecve(path, ___argv, environ);
	__builtin_unreachable();
}
/*[[[end:libc_Execv]]]*/

/*[[[head:libc_Execvp,hash:CRC-32=0x6574024f]]]*/
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN NONNULL((1, 2)) void
(LIBCCALL libc_Execvp)(char const *__restrict file,
                       __TARGV) THROWS(...)
/*[[[body:libc_Execvp]]]*/
{
	libc_Execvpe(file, ___argv, environ);
}
/*[[[end:libc_Execvp]]]*/

/*[[[head:libc_Execvpe,hash:CRC-32=0x6e9667a2]]]*/
/* >> execvpe(3)
 * Replace the  calling process  with the  application  image referred  to by  `file'  and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN NONNULL((1, 2, 3)) void
(LIBCCALL libc_Execvpe)(char const *__restrict file,
                        __TARGV,
                        __TENVP) THROWS(...)
/*[[[body:libc_Execvpe]]]*/
{
	/* Search $PATH */
	size_t taillen = strlen(file);
	char *env_path = getenv("PATH");
	if (env_path && *env_path) {
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
				new_fullpath   = (char *)Realloc(fullpath, (full_len + 1) * sizeof(char));
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
	THROW(E_FSERROR_FILE_NOT_FOUND);
}
/*[[[end:libc_Execvpe]]]*/


/*[[[head:libc_Execl,hash:CRC-32=0x7e39f891]]]*/
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN ATTR_SENTINEL NONNULL((1)) void
(VLIBCCALL libc_Execl)(char const *__restrict path,
                       char const *args,
                       ...) THROWS(...)
/*[[[body:libc_Execl]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	Execv(path, (char *const *)&args);
#else
	va_list vargs;
	char **vector;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char, vector, vargs, args);
	va_end(vargs);
	Execv(path, (char *const *)vector);
#endif
	__builtin_unreachable();
}
/*[[[end:libc_Execl]]]*/

/*[[[head:libc_Execle,hash:CRC-32=0xa4bfdc0a]]]*/
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN ATTR_SENTINEL_O(1) NONNULL((1)) void
(VLIBCCALL libc_Execle)(char const *__restrict path,
                        char const *args,
                        ...) THROWS(...)
/*[[[body:libc_Execle]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	char ***penvp = (char ***)&args;
	while (*penvp++)
		; /* Envp is located 1 after the first NULL-entry */
	Execve(path,
	       (char *const *)&args,
	       (char *const *)*penvp);
#else
	va_list vargs;
	char **vector, **envp;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char, vector, vargs, args);
	envp = va_arg(vargs, char **);
	va_end(vargs);
	Execve(path,
	       (char *const *)vector,
	       (char *const *)envp);
#endif
	__builtin_unreachable();
}
/*[[[end:libc_Execle]]]*/

/*[[[head:libc_Execpl,hash:CRC-32=0x67de5ef2]]]*/
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN ATTR_SENTINEL NONNULL((1)) void
(VLIBCCALL libc_Execpl)(char const *__restrict file,
                        char const *args,
                        ...) THROWS(...)
/*[[[body:libc_Execpl]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	Execvp(file, (char *const *)&args);
#else
	va_list vargs;
	char **vector;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char, vector, vargs, args);
	va_end(vargs);
	Execvp(file, (char *const *)vector);
#endif
	__builtin_unreachable();
}
/*[[[end:libc_Execpl]]]*/

/*[[[head:libc_Execlpe,hash:CRC-32=0xaf89e92b]]]*/
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN ATTR_SENTINEL_O(1) NONNULL((1)) void
(VLIBCCALL libc_Execlpe)(char const *__restrict file,
                         char const *args,
                         ...) THROWS(...)
/*[[[body:libc_Execlpe]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	char ***penvp = (char ***)&args;
	while (*penvp++)
		; /* Envp is located 1 after the first NULL-entry */
	Execvpe(file,
	        (char *const *)&args,
	        (char *const *)*penvp);
#else
	va_list vargs;
	char **vector, **envp;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char, vector, vargs, args);
	envp = va_arg(vargs, char **);
	va_end(vargs);
	Execvpe(file,
	        (char *const *)vector,
	        (char *const *)envp);
#endif
	__builtin_unreachable();
}
/*[[[end:libc_Execlpe]]]*/




/*[[[head:libc_ReadAll,hash:CRC-32=0x115bba12]]]*/
/* >> readall(3)
 * Same  as `read(2)', however  keep on reading until  `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If  an error occurs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
INTERN ATTR_SECTION(".text.crt.except.io.read") NONNULL((2)) size_t
(LIBCCALL libc_ReadAll)(fd_t fd,
                        void *buf,
                        size_t bufsize) THROWS(...)
/*[[[body:libc_ReadAll]]]*/
{
	size_t result, temp;
	result = Read(fd, buf, bufsize);
	if (result != 0 && result < bufsize) {
		/* Keep on reading */
		for (;;) {
			TRY {
				temp = Read(fd,
				           (byte_t *)buf + (size_t)result,
				            bufsize - (size_t)result);
			} EXCEPT {
				int old_error = libc_geterrno();
				/* Try to un-read data that had already been loaded. */
				lseek(fd, -(off_t)(pos_t)result, SEEK_CUR);
				libc_seterrno(old_error);
				RETHROW();
			}
			if (!temp) {
				result = 0;
				break;
			}
			result += temp;
			if (result >= bufsize)
				break;
		}
	}
	return result;
}
/*[[[end:libc_ReadAll]]]*/


/*[[[head:libc_GetCwd,hash:CRC-32=0xa34d7bfa]]]*/
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTERN ATTR_SECTION(".text.crt.except.fs.basic_property") char *
(LIBCCALL libc_GetCwd)(char *buf,
                       size_t bufsize) THROWS(...)
/*[[[body:libc_GetCwd]]]*/
{
	size_t result;
	char *buffer = buf;
	if (!buf) {
		if (!bufsize) {
			/* Automatically allocate + determine buffer size. */
			bufsize = PATH_MAX;
			buffer  = (char *)malloc(bufsize);
			if unlikely(!buffer)
				bufsize = 0;
			for (;;) {
				result = (size_t)sys_Xfrealpath4(AT_FDCWD,
				                                 buffer,
				                                 bufsize,
				                                 AT_READLINK_REQSIZE);
				if likely(result <= bufsize)
					break;
				/* Allocate the required amount of memory. */
				TRY {
					buf = (char *)Realloc(buffer, result);
				} EXCEPT {
					free(buffer);
					RETHROW();
				}
				bufsize = result;
				buffer  = buf;
			}
			if (result != bufsize) {
				buf = (char *)realloc(buffer, (size_t)result);
				if likely(buf)
					buffer = buf;
			}
			return buffer;
		}
		buffer = (char *)Malloc(bufsize);
		TRY {
			result = sys_Xgetcwd(buffer, bufsize);
		} EXCEPT {
			free(buffer);
			RETHROW();
		}
	} else {
		sys_Xgetcwd(buffer, bufsize);
	}
	return buffer;
}
/*[[[end:libc_GetCwd]]]*/

/*[[[head:libc_PRead,hash:CRC-32=0xf6eff9a6]]]*/
/* >> pread(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
INTERN ATTR_SECTION(".text.crt.except.io.read") NONNULL((2)) size_t
(LIBCCALL libc_PRead)(fd_t fd,
                      void *buf,
                      size_t bufsize,
                      pos_t offset) THROWS(...)
/*[[[body:libc_PRead]]]*/
{
	return (size_t)sys_Xpread64(fd, buf, bufsize, (u64)offset);
}
/*[[[end:libc_PRead]]]*/

/*[[[head:libc_PWrite,hash:CRC-32=0x59d73efb]]]*/
/* >> pwrite(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
INTERN ATTR_SECTION(".text.crt.except.io.write") NONNULL((2)) size_t
(LIBCCALL libc_PWrite)(fd_t fd,
                       void const *buf,
                       size_t bufsize,
                       pos_t offset) THROWS(...)
/*[[[body:libc_PWrite]]]*/
{
	return (size_t)sys_Xpwrite64(fd, buf, bufsize, (u64)offset);
}
/*[[[end:libc_PWrite]]]*/

/*[[[head:libc_PReadAll,hash:CRC-32=0x42df31c5]]]*/
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTERN ATTR_SECTION(".text.crt.except.io.read") NONNULL((2)) size_t
(LIBCCALL libc_PReadAll)(fd_t fd,
                         void *buf,
                         size_t bufsize,
                         pos_t offset) THROWS(...)
/*[[[body:libc_PReadAll]]]*/
{
	return PReadAll64(fd, buf, bufsize, offset);
}
/*[[[end:libc_PReadAll]]]*/

/*[[[head:libc_PReadAll64,hash:CRC-32=0x2ef5e7a0]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_PReadAll64, libc_PReadAll);
#else /* MAGIC:alias */
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
INTERN ATTR_SECTION(".text.crt.except.io.large.read") NONNULL((2)) size_t
(LIBCCALL libc_PReadAll64)(fd_t fd,
                           void *buf,
                           size_t bufsize,
                           pos64_t offset) THROWS(...)
/*[[[body:libc_PReadAll64]]]*/
{
	size_t result, temp;
	result = PRead64(fd, buf, bufsize, offset);
	if (result != 0 && (size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = PRead64(fd,
			              (byte_t *)buf + result,
			               bufsize - result,
			               offset + result);
			if (!temp) {
				result = 0;
				break;
			}
			result += temp;
			if (result >= bufsize)
				break;
		}
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_PReadAll64]]]*/

/*[[[head:libc_GetCurrentDirName,hash:CRC-32=0x749e7a69]]]*/
INTERN ATTR_SECTION(".text.crt.except.fs.basic_property") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED char *
(LIBCCALL libc_GetCurrentDirName)(void) THROWS(...)
/*[[[body:libc_GetCurrentDirName]]]*/
{
	return GetCwd(NULL, 0);
}
/*[[[end:libc_GetCurrentDirName]]]*/

/*[[[head:libc_FExecve,hash:CRC-32=0x3700e3c]]]*/
/* >> fexecve(2)
 * Replace the  calling  process  with the  application  image  referred to  by  `fd'  and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN NONNULL((2, 3)) void
(LIBCCALL libc_FExecve)(fd_t fd,
                        __TARGV,
                        __TENVP) THROWS(...)
/*[[[body:libc_FExecve]]]*/
{
	sys_Xexecveat(fd,
	              "",
	              (char *const *)___argv,
	              (char *const *)___envp,
	              AT_EMPTY_PATH);
	__builtin_unreachable();
}
/*[[[end:libc_FExecve]]]*/

/*[[[head:libc_Nice,hash:CRC-32=0x857a694b]]]*/
INTERN ATTR_SECTION(".text.crt.except.sched.param") int
(LIBCCALL libc_Nice)(int inc) THROWS(...)
/*[[[body:libc_Nice]]]*/
{
#ifdef __sys_Xnice_defined
	return 20 - sys_Xnice(inc);
#else /* __sys_Xnice_defined */
	syscall_slong_t prio;
	prio = sys_Xgetpriority(PRIO_PROCESS, 0);
	prio = (20 - prio);
	prio += inc;
	sys_Xsetpriority(PRIO_PROCESS, 0, (syscall_ulong_t)(20 - prio));
	prio = sys_Xgetpriority(PRIO_PROCESS, 0);
	return 20 - prio;
#endif /* !__sys_Xnice_defined */
}
/*[[[end:libc_Nice]]]*/

/*[[[head:libc_SetPGrp,hash:CRC-32=0xc2d23811]]]*/
/* >> setpgrp(3)
 * Move the calling process into its own process group.
 * Equivalent to `setpgid(0, 0)' */
INTERN ATTR_SECTION(".text.crt.except.sched.process") void
(LIBCCALL libc_SetPGrp)(void) THROWS(...)
/*[[[body:libc_SetPGrp]]]*/
{
	sys_Xsetpgid(0, 0);
}
/*[[[end:libc_SetPGrp]]]*/

/*[[[head:libc_SetEUid,hash:CRC-32=0x88c95a73]]]*/
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `euid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.except.sched.user") void
(LIBCCALL libc_SetEUid)(uid_t euid) THROWS(...)
/*[[[body:libc_SetEUid]]]*/
{
#ifdef SYS_getresuid32
	uint32_t ruid;
	sys_Xgetresuid32(&ruid, NULL, NULL);
	sys_Xsetreuid32(ruid, euid);
#else /* SYS_getresuid32 */
	uid_t ruid;
	sys_Xgetresuid(&ruid, NULL, NULL);
	sys_Xsetreuid(ruid, euid);
#endif /* !SYS_getresuid32 */
}
/*[[[end:libc_SetEUid]]]*/

/*[[[head:libc_SetEGid,hash:CRC-32=0xf1e709d3]]]*/
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `egid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.except.sched.user") void
(LIBCCALL libc_SetEGid)(gid_t egid) THROWS(...)
/*[[[body:libc_SetEGid]]]*/
{
#ifdef SYS_getresgid32
	uint32_t rgid;
	sys_Xgetresgid32(&rgid, NULL, NULL);
	sys_Xsetregid32(rgid, egid);
#else /* SYS_getresgid32 */
	gid_t rgid;
	sys_Xgetresgid(&rgid, NULL, NULL);
	sys_Xsetregid(rgid, egid);
#endif /* !SYS_getresgid32 */
}
/*[[[end:libc_SetEGid]]]*/

/*[[[head:libc_GetHostName,hash:CRC-32=0x76a2aaf6]]]*/
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTERN ATTR_SECTION(".text.crt.except.system.configuration") NONNULL((1)) void
(LIBCCALL libc_GetHostName)(char *name,
                            size_t buflen) THROWS(...)
/*[[[body:libc_GetHostName]]]*/
{
	struct utsname uts;
	size_t len;
	sys_Xuname(&uts);
	len = strnlen(uts.nodename, _UTSNAME_NODENAME_LENGTH);
	if (buflen <= len)
		THROW(E_BUFFER_TOO_SMALL, len, buflen);
	memcpy(name, uts.nodename, len, sizeof(char));
	name[len] = '\0';
}
/*[[[end:libc_GetHostName]]]*/

/*[[[head:libc_GetDomainName,hash:CRC-32=0x39d964ef]]]*/
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTERN ATTR_SECTION(".text.crt.except.system.configuration") NONNULL((1)) void
(LIBCCALL libc_GetDomainName)(char *name,
                              size_t buflen) THROWS(...)
/*[[[body:libc_GetDomainName]]]*/
{
	struct utsname uts;
	size_t len;
	sys_Xuname(&uts);
	len = strnlen(uts.domainname, _UTSNAME_DOMAIN_LENGTH);
	if (buflen <= len)
		THROW(E_BUFFER_TOO_SMALL, len, buflen);
	memcpy(name, uts.domainname, len, sizeof(char));
	name[len] = '\0';
}
/*[[[end:libc_GetDomainName]]]*/

/*[[[skip:libc_Execve]]]*/
/*[[[skip:libc_Pipe]]]*/
/*[[[skip:libc_SetPGid]]]*/
/*[[[skip:libc_SetSid]]]*/
/*[[[skip:libc_SetUid]]]*/
/*[[[skip:libc_SetGid]]]*/
/*[[[skip:libc_Fork]]]*/
/*[[[skip:libc_Chown]]]*/
/*[[[skip:libc_Link]]]*/
/*[[[skip:libc_Read]]]*/
/*[[[skip:libc_Write]]]*/
/*[[[skip:libc_LSeek]]]*/
/*[[[skip:libc_Dup2]]]*/
/*[[[skip:libc_Dup]]]*/
/*[[[skip:libc_Chdir]]]*/
/*[[[skip:libc_Unlink]]]*/
/*[[[skip:libc_Rmdir]]]*/
/*[[[skip:libc_FChownAt]]]*/
/*[[[skip:libc_LinkAt]]]*/
/*[[[skip:libc_SymlinkAt]]]*/
/*[[[skip:libc_ReadlinkAt]]]*/
/*[[[skip:libc_FReadlinkAt]]]*/
/*[[[skip:libc_UnlinkAt]]]*/
/*[[[skip:libc_LSeek64]]]*/
/*[[[skip:libc_PRead64]]]*/
/*[[[skip:libc_PWrite64]]]*/
/*[[[skip:libc_Pipe2]]]*/
/*[[[skip:libc_Dup3]]]*/
/*[[[skip:libc_SyncFs]]]*/
/*[[[skip:libc_GetResUid]]]*/
/*[[[skip:libc_GetResGid]]]*/
/*[[[skip:libc_SetResUid]]]*/
/*[[[skip:libc_SetResGid]]]*/
/*[[[skip:libc_VFork]]]*/
/*[[[skip:libc_FChown]]]*/
/*[[[skip:libc_FChdir]]]*/
/*[[[skip:libc_GetPGid]]]*/
/*[[[skip:libc_GetSid]]]*/
/*[[[skip:libc_LChown]]]*/
/*[[[skip:libc_Truncate]]]*/
/*[[[skip:libc_Truncate64]]]*/
/*[[[skip:libc_SetReUid]]]*/
/*[[[skip:libc_SetReGid]]]*/
/*[[[skip:libc_Symlink]]]*/
/*[[[skip:libc_Readlink]]]*/
/*[[[skip:libc_SetHostName]]]*/
/*[[[skip:libc_SetDomainName]]]*/
/*[[[skip:libc_ChRoot]]]*/
/*[[[skip:libc_FTruncate64]]]*/
/*[[[skip:libc_FDataSync]]]*/
/*[[[skip:libc_Syscall]]]*/
/*[[[skip:libc_Syscall64]]]*/
/*[[[skip:libc_FTruncate]]]*/
/*[[[skip:libc_FSync]]]*/





/*[[[start:exports,hash:CRC-32=0x28eb2e37]]]*/
DEFINE_PUBLIC_ALIAS(Execv, libc_Execv);
DEFINE_PUBLIC_ALIAS(Execvp, libc_Execvp);
DEFINE_PUBLIC_ALIAS(Execl, libc_Execl);
DEFINE_PUBLIC_ALIAS(Execle, libc_Execle);
DEFINE_PUBLIC_ALIAS(Execpl, libc_Execpl);
DEFINE_PUBLIC_ALIAS(Execlpe, libc_Execlpe);
DEFINE_PUBLIC_ALIAS(ReadAll, libc_ReadAll);
DEFINE_PUBLIC_ALIAS(GetCwd, libc_GetCwd);
DEFINE_PUBLIC_ALIAS(PRead, libc_PRead);
DEFINE_PUBLIC_ALIAS(PWrite, libc_PWrite);
DEFINE_PUBLIC_ALIAS(PReadAll, libc_PReadAll);
DEFINE_PUBLIC_ALIAS(PReadAll64, libc_PReadAll64);
DEFINE_PUBLIC_ALIAS(GetCurrentDirName, libc_GetCurrentDirName);
DEFINE_PUBLIC_ALIAS(FExecve, libc_FExecve);
DEFINE_PUBLIC_ALIAS(Execvpe, libc_Execvpe);
DEFINE_PUBLIC_ALIAS(Nice, libc_Nice);
DEFINE_PUBLIC_ALIAS(SetPGrp, libc_SetPGrp);
DEFINE_PUBLIC_ALIAS(SetEUid, libc_SetEUid);
DEFINE_PUBLIC_ALIAS(SetEGid, libc_SetEGid);
DEFINE_PUBLIC_ALIAS(GetHostName, libc_GetHostName);
DEFINE_PUBLIC_ALIAS(GetDomainName, libc_GetDomainName);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_UNISTD_C */
