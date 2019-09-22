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
#ifndef GUARD_LIBC_USER_KOS_UNISTD_C
#define GUARD_LIBC_USER_KOS_UNISTD_C 1

#include "../api.h"
/**/

#include <kos/except.h>
#include <kos/malloc.h>
#include <kos/syscalls.h>
#include <sys/utsname.h>

#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../libc/capture-varargs.h"
#include "kos.unistd.h"

DECL_BEGIN

#undef environ
#ifndef __environ_defined
#define __environ_defined 1
extern char **environ;
#endif /* !__environ_defined */
DECLARE_NOREL_GLOBAL_META(char **, environ);
#define environ  GET_NOREL_GLOBAL(environ)

/*[[[start:implementation]]]*/

/*[[[head:Execv,hash:CRC-32=0x20d6d5c5]]]*/
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_NORETURN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.exec.exec.Execv") void
(LIBCCALL libc_Execv)(char const *__restrict path,
                      __TARGV)
		__THROWS(...)
/*[[[body:Execv]]]*/
{
	sys_Xexecve(path, ___argv, environ);
	__builtin_unreachable();
}
/*[[[end:Execv]]]*/

/*[[[skip:Execve]]]*/

/*[[[head:Execvp,hash:CRC-32=0x3e8d8bfa]]]*/
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_NORETURN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.exec.exec.Execvp") void
(LIBCCALL libc_Execvp)(char const *__restrict file,
                       __TARGV)
		__THROWS(...)
/*[[[body:Execvp]]]*/
{
	libc_Execvpe(file, ___argv, environ);
}
/*[[[end:Execvp]]]*/

/*[[[head:Execvpe,hash:CRC-32=0x104dbbbf]]]*/
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_NORETURN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.exec.exec.Execvpe") void
(LIBCCALL libc_Execvpe)(char const *__restrict file,
                        __TARGV,
                        __TENVP)
		__THROWS(...)
/*[[[body:Execvpe]]]*/
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
			memcpy(fullpath, env_path, seg_len * sizeof(char));
			if (need_trail) {
				fullpath[seg_len] = '/';
				memcpy(fullpath + seg_len + 1, file, taillen * sizeof(char));
			} else {
				memcpy(fullpath + seg_len, file, taillen * sizeof(char));
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
/*[[[end:Execvpe]]]*/



/*[[[head:Execl,hash:CRC-32=0x77699431]]]*/
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
INTERN ATTR_SENTINEL ATTR_NORETURN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.exec.exec.Execl") void
(VLIBCCALL libc_Execl)(char const *__restrict path,
                       char const *args,
                       ... /*, (char *)NULL*/)
		__THROWS(...)
/*[[[body:Execl]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	Execv(path,
	      (char const *const *)&args);
#else
	va_list vargs;
	char **vector;
	va_start(vargs, args);
	CAPTURE_VARARGS(char, vector, vargs);
	va_end(vargs);
	Execv(path,
	      (char const *const *)vector);
#endif
	__builtin_unreachable();
}
/*[[[end:Execl]]]*/

/*[[[head:Execle,hash:CRC-32=0x87164caf]]]*/
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinal */
INTERN ATTR_SENTINEL ATTR_NORETURN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.exec.exec.Execle") void
(VLIBCCALL libc_Execle)(char const *__restrict path,
                        char const *args,
                        ... /*, (char *)NULL, (char **)environ*/)
		__THROWS(...)
/*[[[body:Execle]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	char **envp = (char **)&args;
	while (*envp++)
		; /* Envp is located 1 after the first NULL-entry */
	Execve(path,
	       (char const *const *)&args,
	       (char const *const *)&envp);
#else
	va_list vargs;
	char **vector, **envp;
	va_start(vargs, args);
	CAPTURE_VARARGS(char, vector, vargs);
	envp = va_arg(vargs, char **);
	va_end(vargs);
	Execve(path,
	       (char const *const *)vector,
	       (char const *const *)envp);
#endif
	__builtin_unreachable();
}
/*[[[end:Execle]]]*/

/*[[[head:Execpl,hash:CRC-32=0xd23ee48d]]]*/
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
INTERN ATTR_SENTINEL ATTR_NORETURN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.exec.exec.Execpl") void
(VLIBCCALL libc_Execpl)(char const *__restrict file,
                        char const *args,
                        ... /*, (char *)NULL*/)
		__THROWS(...)
/*[[[body:Execpl]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	Execvp(file,
	       (char const *const *)&args);
#else
	va_list vargs;
	char **vector;
	va_start(vargs, args);
	CAPTURE_VARARGS(char, vector, vargs);
	va_end(vargs);
	Execvp(file,
	       (char const *const *)vector);
#endif
	__builtin_unreachable();
}
/*[[[end:Execpl]]]*/

/*[[[head:Execlpe,hash:CRC-32=0x8aa3af5a]]]*/
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinal */
INTERN ATTR_SENTINEL ATTR_NORETURN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.exec.exec.Execlpe") void
(VLIBCCALL libc_Execlpe)(char const *__restrict file,
                         char const *args,
                         ... /*, (char *)NULL, (char **)environ*/)
		__THROWS(...)
/*[[[body:Execlpe]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	char **envp = (char **)&args;
	while (*envp++)
		; /* Envp is located 1 after the first NULL-entry */
	Execvpe(file,
	        (char const *const *)&args,
	        (char const *const *)&envp);
#else
	va_list vargs;
	char **vector, **envp;
	va_start(vargs, args);
	CAPTURE_VARARGS(char, vector, vargs);
	envp = va_arg(vargs, char **);
	va_end(vargs);
	Execvpe(file,
	        (char const *const *)vector,
	        (char const *const *)envp);
#endif
	__builtin_unreachable();
}
/*[[[end:Execlpe]]]*/

/*[[[head:FPathConf,hash:CRC-32=0xcf0e4dee]]]*/
/* >> fpathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `FD' */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.property.FPathConf") long int
(LIBCCALL libc_FPathConf)(fd_t fd,
                          int name)
		__THROWS(...)
/*[[[body:FPathConf]]]*/
{
	CRT_UNIMPLEMENTED("FPathConf"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:FPathConf]]]*/

/*[[[head:PathConf,hash:CRC-32=0xc2013534]]]*/
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.property.PathConf") long int
(LIBCCALL libc_PathConf)(char const *path,
                         int name)
		__THROWS(...)
/*[[[body:PathConf]]]*/
{
	CRT_UNIMPLEMENTED("PathConf"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:PathConf]]]*/


/*[[[head:ReadAll,hash:CRC-32=0x9dde3e2c]]]*/
/* >> readall(3)
 * Same as `read(2)', however keep on reading until `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If an error occurrs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.except.io.read.ReadAll") size_t
(LIBCCALL libc_ReadAll)(fd_t fd,
                        void *buf,
                        size_t bufsize)
		__THROWS(...)
/*[[[body:ReadAll]]]*/
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
/*[[[end:ReadAll]]]*/


/*[[[head:GetCwd,hash:CRC-32=0x74bb4835]]]*/
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.basic_property.GetCwd") char *
(LIBCCALL libc_GetCwd)(char *buf,
                       size_t bufsize)
		__THROWS(...)
/*[[[body:GetCwd]]]*/
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
/*[[[end:GetCwd]]]*/

/*[[[head:PRead,hash:CRC-32=0x88aea0de]]]*/
/* >> pread(2)
 * Read data from a file at a specific offset */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.except.io.read.PRead") size_t
(LIBCCALL libc_PRead)(fd_t fd,
                      void *buf,
                      size_t bufsize,
                      pos_t offset)
		__THROWS(...)
/*[[[body:PRead]]]*/
{
	return (size_t)sys_Xpread64(fd, buf, bufsize, (u64)offset);
}
/*[[[end:PRead]]]*/

/*[[[head:PWrite,hash:CRC-32=0x544807fa]]]*/
/* >> pwrite(2)
 * Write data to a file at a specific offset */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.except.io.write.PWrite") size_t
(LIBCCALL libc_PWrite)(fd_t fd,
                       void const *buf,
                       size_t bufsize,
                       pos_t offset)
		__THROWS(...)
/*[[[body:PWrite]]]*/
{
	return (size_t)sys_Xpwrite64(fd, buf, bufsize, (u64)offset);
}
/*[[[end:PWrite]]]*/

/*[[[head:PReadAll,hash:CRC-32=0x42a91a7f]]]*/
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.except.io.read.PReadAll") size_t
(LIBCCALL libc_PReadAll)(fd_t fd,
                         void *buf,
                         size_t bufsize,
                         pos_t offset)
		__THROWS(...)
/*[[[body:PReadAll]]]*/
{
	return PReadAll64(fd, buf, bufsize, offset);
}
/*[[[end:PReadAll]]]*/

/*[[[head:PReadAll64,hash:CRC-32=0xbce3330a]]]*/
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_PReadAll64, libc_preadall);
#else
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.except.io.large.read.PReadAll64") size_t
(LIBCCALL libc_PReadAll64)(fd_t fd,
                           void *buf,
                           size_t bufsize,
                           pos64_t offset)
		__THROWS(...)
/*[[[body:PReadAll64]]]*/
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
/*[[[end:PReadAll64]]]*/

/*[[[head:GetCurrentDirName,hash:CRC-32=0x1e38de7]]]*/
INTERN WUNUSED ATTR_RETNONNULL ATTR_MALLOC
ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.basic_property.GetCurrentDirName") char *
(LIBCCALL libc_GetCurrentDirName)(void)
		__THROWS(...)
/*[[[body:GetCurrentDirName]]]*/
{
	return GetCwd(NULL, 0);
}
/*[[[end:GetCurrentDirName]]]*/

/*[[[head:FExecve,hash:CRC-32=0x9cc9a3ce]]]*/
/* >> fexecve(2)
 * Replace the calling process with the application image referred to by `FD' and
 * execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_NORETURN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.except.fs.exec.exec.FExecve") void
(LIBCCALL libc_FExecve)(fd_t fd,
                        __TARGV,
                        __TENVP)
		__THROWS(...)
/*[[[body:FExecve]]]*/
{
	sys_Xexecveat(fd,
	              "",
	              (char const *const *)___argv,
	              (char const *const *)___envp,
	              AT_EMPTY_PATH);
	__builtin_unreachable();
}
/*[[[end:FExecve]]]*/

/*[[[head:Nice,hash:CRC-32=0xdb38ede6]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.except.sched.param.Nice") int
(LIBCCALL libc_Nice)(int inc)
		__THROWS(...)
/*[[[body:Nice]]]*/
{
	return 20 - sys_Xnice(-inc);
}
/*[[[end:Nice]]]*/

/*[[[head:SetPGrp,hash:CRC-32=0xd2c4da8b]]]*/
/* >> setpgrp(3)
 * Move the calling process into its own process group.
 * Equivalent to `setpgid(0, 0)' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.except.sched.process.SetPGrp") void
(LIBCCALL libc_SetPGrp)(void)
		__THROWS(...)
/*[[[body:SetPGrp]]]*/
{
	sys_Xsetpgid(0, 0);
}
/*[[[end:SetPGrp]]]*/

/*[[[head:SetEUid,hash:CRC-32=0xee65fbd2]]]*/
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EUID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.except.sched.user.SetEUid") void
(LIBCCALL libc_SetEUid)(uid_t euid)
		__THROWS(...)
/*[[[body:SetEUid]]]*/
{
	uint32_t ruid;
	sys_Xgetresuid32(&ruid, NULL, NULL);
	sys_Xsetreuid32(ruid, (uint32_t)euid);
}
/*[[[end:SetEUid]]]*/

/*[[[head:SetEGid,hash:CRC-32=0x1eb8561a]]]*/
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EGID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.except.sched.user.SetEGid") void
(LIBCCALL libc_SetEGid)(gid_t egid)
		__THROWS(...)
/*[[[body:SetEGid]]]*/
{
	uint32_t rgid;
	sys_Xgetresgid32(&rgid, NULL, NULL);
	sys_Xsetregid32(rgid, (uint32_t)egid);
}
/*[[[end:SetEGid]]]*/

/*[[[head:GetHostName,hash:CRC-32=0x6c477876]]]*/
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.system.configuration.GetHostName") void
(LIBCCALL libc_GetHostName)(char *name,
                            size_t buflen)
		__THROWS(...)
/*[[[body:GetHostName]]]*/
{
	struct utsname uts;
	size_t len;
	sys_Xuname(&uts);
	len = strnlen(uts.nodename, _UTSNAME_NODENAME_LENGTH);
	if (buflen <= len)
		THROW(E_BUFFER_TOO_SMALL, len, buflen);
	memcpy(name, uts.nodename, len * sizeof(char));
	name[len] = '\0';
}
/*[[[end:GetHostName]]]*/

/*[[[head:GetDomainName,hash:CRC-32=0x19e73961]]]*/
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.except.system.configuration.GetDomainName") void
(LIBCCALL libc_GetDomainName)(char *name,
                              size_t buflen)
		__THROWS(...)
/*[[[body:GetDomainName]]]*/
{
	struct utsname uts;
	size_t len;
	sys_Xuname(&uts);
	len = strnlen(uts.domainname, _UTSNAME_DOMAIN_LENGTH);
	if (buflen <= len)
		THROW(E_BUFFER_TOO_SMALL, len, buflen);
	memcpy(name, uts.domainname, len * sizeof(char));
	name[len] = '\0';
}
/*[[[end:GetDomainName]]]*/

/*[[[skip:Pipe]]]*/
/*[[[skip:SetPGid]]]*/
/*[[[skip:SetSid]]]*/
/*[[[skip:SetUid]]]*/
/*[[[skip:SetGid]]]*/
/*[[[skip:Fork]]]*/
/*[[[skip:Chown]]]*/
/*[[[skip:Link]]]*/
/*[[[skip:Read]]]*/
/*[[[skip:Write]]]*/
/*[[[skip:LSeek]]]*/
/*[[[skip:Dup2]]]*/
/*[[[skip:Dup]]]*/
/*[[[skip:Chdir]]]*/
/*[[[skip:Unlink]]]*/
/*[[[skip:Rmdir]]]*/
/*[[[skip:FChownAt]]]*/
/*[[[skip:LinkAt]]]*/
/*[[[skip:SymlinkAt]]]*/
/*[[[skip:ReadlinkAt]]]*/
/*[[[skip:FReadlinkAt]]]*/
/*[[[skip:UnlinkAt]]]*/
/*[[[skip:LSeek64]]]*/
/*[[[skip:PRead64]]]*/
/*[[[skip:PWrite64]]]*/
/*[[[skip:Pipe2]]]*/
/*[[[skip:Dup3]]]*/
/*[[[skip:SyncFs]]]*/
/*[[[skip:GetResUid]]]*/
/*[[[skip:GetResGid]]]*/
/*[[[skip:SetResUid]]]*/
/*[[[skip:SetResGid]]]*/
/*[[[skip:VFork]]]*/
/*[[[skip:FChown]]]*/
/*[[[skip:FChdir]]]*/
/*[[[skip:GetPGid]]]*/
/*[[[skip:GetSid]]]*/
/*[[[skip:LChown]]]*/
/*[[[skip:Truncate]]]*/
/*[[[skip:Truncate64]]]*/
/*[[[skip:SetReUid]]]*/
/*[[[skip:SetReGid]]]*/
/*[[[skip:Symlink]]]*/
/*[[[skip:Readlink]]]*/
/*[[[skip:SetHostName]]]*/
/*[[[skip:SetDomainName]]]*/
/*[[[skip:ChRoot]]]*/
/*[[[skip:FTruncate64]]]*/
/*[[[skip:FDataSync]]]*/
/*[[[skip:Syscall]]]*/
/*[[[skip:Syscall64]]]*/
/*[[[skip:FTruncate]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x73c8397f]]]*/
#undef Execl
#undef Execle
#undef Execpl
#undef Execlpe
DEFINE_PUBLIC_WEAK_ALIAS(Execv, libc_Execv);
DEFINE_PUBLIC_WEAK_ALIAS(Execvp, libc_Execvp);
DEFINE_PUBLIC_WEAK_ALIAS(Execl, libc_Execl);
DEFINE_PUBLIC_WEAK_ALIAS(Execle, libc_Execle);
DEFINE_PUBLIC_WEAK_ALIAS(Execpl, libc_Execpl);
DEFINE_PUBLIC_WEAK_ALIAS(Execlpe, libc_Execlpe);
DEFINE_PUBLIC_WEAK_ALIAS(FPathConf, libc_FPathConf);
DEFINE_PUBLIC_WEAK_ALIAS(PathConf, libc_PathConf);
DEFINE_PUBLIC_WEAK_ALIAS(ReadAll, libc_ReadAll);
DEFINE_PUBLIC_WEAK_ALIAS(GetCwd, libc_GetCwd);
DEFINE_PUBLIC_WEAK_ALIAS(PRead, libc_PRead);
DEFINE_PUBLIC_WEAK_ALIAS(PWrite, libc_PWrite);
DEFINE_PUBLIC_WEAK_ALIAS(PReadAll, libc_PReadAll);
DEFINE_PUBLIC_WEAK_ALIAS(PReadAll64, libc_PReadAll64);
DEFINE_PUBLIC_WEAK_ALIAS(GetCurrentDirName, libc_GetCurrentDirName);
DEFINE_PUBLIC_WEAK_ALIAS(FExecve, libc_FExecve);
DEFINE_PUBLIC_WEAK_ALIAS(Execvpe, libc_Execvpe);
DEFINE_PUBLIC_WEAK_ALIAS(Nice, libc_Nice);
DEFINE_PUBLIC_WEAK_ALIAS(SetPGrp, libc_SetPGrp);
DEFINE_PUBLIC_WEAK_ALIAS(SetEUid, libc_SetEUid);
DEFINE_PUBLIC_WEAK_ALIAS(SetEGid, libc_SetEGid);
DEFINE_PUBLIC_WEAK_ALIAS(GetHostName, libc_GetHostName);
DEFINE_PUBLIC_WEAK_ALIAS(GetDomainName, libc_GetDomainName);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_UNISTD_C */
