/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_KOS_UNISTD_C
#define GUARD_LIBC_USER_KOS_UNISTD_C 1
#define _ALL_LIMITS_SOURCE 1

#include "../api.h"
/**/

#include <kos/except.h>
#include <kos/except/reason/inval.h>
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
#include "kos.unistd.h"

DECL_BEGIN

INTDEF WUNUSED longptr_t LIBCCALL
libc_do_FPathConf(fd_t fd, __STDC_INT_AS_UINT_T name) THROWS(...);
INTDEF ATTR_IN(1) longptr_t LIBDCALL
libc_do_PathConf(char const *path, __STDC_INT_AS_UINT_T name, oflag_t path_oflags) THROWS(...);


/*[[[head:libc_Execv,hash:CRC-32=0x699785e7]]]*/
/* >> execv(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN ATTR_IN(1) ATTR_IN(2) void
(LIBCCALL libc_Execv)(char const *__restrict path,
                      __TARGV) THROWS(...)
/*[[[body:libc_Execv]]]*/
{
	sys_Xexecve(path, ___argv, environ);
	__builtin_unreachable();
}
/*[[[end:libc_Execv]]]*/

/*[[[head:libc_Execvp,hash:CRC-32=0xef22fc15]]]*/
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN ATTR_IN(1) ATTR_IN(2) void
(LIBCCALL libc_Execvp)(char const *__restrict file,
                       __TARGV) THROWS(...)
/*[[[body:libc_Execvp]]]*/
{
	libc_Execvpe(file, ___argv, environ);
}
/*[[[end:libc_Execvp]]]*/

/*[[[head:libc_Execvpe,hash:CRC-32=0xcc7c40e6]]]*/
/* >> execvpe(3)
 * Replace the  calling process  with the  application  image referred  to by  `file'  and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) void
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
		for (;;) {
			/* NOTE: Because we're using the unix-style `getenv()' (as opposed
			 *       to  `DOS$getenv()'), we're always working with unix paths
			 *       in here! */
			char *path_end  = strchrnul(env_path, ':');
			size_t seg_len  = (size_t)(path_end - env_path);
			size_t full_len = seg_len + taillen;
			bool need_trail = path_end[-1] != '/';
			if (need_trail)
				++full_len;
			if (full_len > fullpath_alloc) {
				fullpath       = (char *)Realloc(fullpath, (full_len + 1) * sizeof(char));
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

/*[[[head:libc_FExecve,hash:CRC-32=0xd11ca980]]]*/
/* >> fexecve(2)
 * Replace the calling process with the application image referred
 * to by `execfd'  and execute it's  `main()' method, passing  the
 * given `argv', and setting `environ' to `envp'. */
INTERN ATTR_SECTION(".text.crt.except.fs.exec.exec") ATTR_NORETURN ATTR_FDREAD(1) ATTR_IN(2) ATTR_IN(3) void
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

/*[[[head:libc_GetCwd,hash:CRC-32=0x404a02cb]]]*/
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTERN ATTR_SECTION(".text.crt.except.fs.basic_property") ATTR_OUTS(1, 2) char *
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

/*[[[skip:libc_PRead]]]*/
/*[[[skip:libc_PWrite]]]*/
#if __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
INTERN ATTR_SECTION(".text.crt.except.io.read") ATTR_OUTS(2, 3) size_t
(LIBCCALL libc_PRead)(fd_t fd,
                      void *buf,
                      size_t bufsize,
                      pos_t offset) THROWS(...) {
	return (size_t)sys_Xpread64(fd, buf, bufsize, (u64)offset);
}

/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
INTERN ATTR_SECTION(".text.crt.except.io.write") ATTR_INS(2, 3) size_t
(LIBCCALL libc_PWrite)(fd_t fd,
                       void const *buf,
                       size_t bufsize,
                       pos_t offset) THROWS(...) {
	return (size_t)sys_Xpwrite64(fd, buf, bufsize, (u64)offset);
}
#endif /* __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__ */

/*[[[head:libc_Nice,hash:CRC-32=0x857a694b]]]*/
INTERN ATTR_SECTION(".text.crt.except.sched.param") int
(LIBCCALL libc_Nice)(int inc) THROWS(...)
/*[[[body:libc_Nice]]]*/
{
#ifdef SYS_nice
	return 20 - sys_Xnice(inc);
#else /* SYS_nice */
	syscall_slong_t prio;
	prio = sys_Xgetpriority(PRIO_PROCESS, 0);
	prio = (20 - prio);
	prio += inc;
	sys_Xsetpriority(PRIO_PROCESS, 0, (syscall_ulong_t)(20 - prio));
	prio = sys_Xgetpriority(PRIO_PROCESS, 0);
	return 20 - prio;
#endif /* !SYS_nice */
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

/*[[[head:libc_GetHostName,hash:CRC-32=0xefdbbbec]]]*/
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTERN ATTR_SECTION(".text.crt.except.system.configuration") ATTR_OUTS(1, 2) void
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

/*[[[head:libc_GetDomainName,hash:CRC-32=0xca4dc977]]]*/
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTERN ATTR_SECTION(".text.crt.except.system.configuration") ATTR_OUTS(1, 2) void
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

/*[[[head:libc_FPathConf,hash:CRC-32=0xa715c2aa]]]*/
/* >> fpathconf(3)
 * @param: name: One   of    `_PC_*'    from    <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `fd'
 * return: * : The configuration limit associated with `name' for `fd'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `fd'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.except.fs.property") WUNUSED ATTR_FDARG(1) longptr_t
(LIBCCALL libc_FPathConf)(fd_t fd,
                          __STDC_INT_AS_UINT_T name) THROWS(...)
/*[[[body:libc_FPathConf]]]*/
{
	return libc_do_FPathConf(fd, name);
}
/*[[[end:libc_FPathConf]]]*/

/*[[[head:libc_PathConf,hash:CRC-32=0x3ce51e33]]]*/
/* >> pathconf(3)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.except.fs.property") ATTR_IN(1) longptr_t
(LIBCCALL libc_PathConf)(char const *path,
                         __STDC_INT_AS_UINT_T name) THROWS(...)
/*[[[body:libc_PathConf]]]*/
{
	return libc_do_PathConf(path, name, O_RDONLY);
}
/*[[[end:libc_PathConf]]]*/

/*[[[head:libc_LPathConf,hash:CRC-32=0xafd0662c]]]*/
/* >> lpathconf(3)
 * Same as `pathconf(3)', but don't dereference `path' if it's a symbolic link */
INTERN ATTR_SECTION(".text.crt.except.fs.property") ATTR_IN(1) longptr_t
(LIBCCALL libc_LPathConf)(char const *path,
                          __STDC_INT_AS_UINT_T name) THROWS(...)
/*[[[body:libc_LPathConf]]]*/
{
	return libc_do_PathConf(path, name, O_RDONLY | O_PATH | O_NOFOLLOW);
}
/*[[[end:libc_LPathConf]]]*/

/*[[[head:libc_ConfStr,hash:CRC-32=0x7f1f67f6]]]*/
/* >> confstr(3)
 * Retrieve a system configuration string specified by `name'
 * @param: name:   One of `_CS_*' from <asm/crt/confname.h>
 * @param: buf:    Target buffer
 * @param: buflen: Available buffer size (including a trailing \0-character)
 * @return: * :    Required buffer size (including a trailing \0-character)
 * @return: 1 :    Empty configuration string.
 * @return: 0 :    [errno=EINVAL] Bad configuration `name'. */
INTERN ATTR_SECTION(".text.crt.except.system.configuration") ATTR_OUTS(2, 3) size_t
(LIBCCALL libc_ConfStr)(__STDC_INT_AS_UINT_T name,
                        char *buf,
                        size_t buflen) THROWS(...)
/*[[[body:libc_ConfStr]]]*/
{
	longptr_t result;
	errno_t old_errno = libc_geterrno();
	(void)libc_seterrno(EOK);
	result = confstr(name, buf, buflen);
	if (result == -1 && libc_geterrno() == EINVAL) {
		(void)libc_seterrno(old_errno);
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_CONFSTR_NAME,
		      name);
	}
	(void)libc_seterrno(old_errno);
	return result;
}
/*[[[end:libc_ConfStr]]]*/


/*[[[head:libc_SysConf,hash:CRC-32=0x32346246]]]*/
/* >> sysconf(2)
 * @param: name: One of `_SC_*' from <asm/crt/confname.h>
 * Return   a   system    configuration   value    `name'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] `name'  refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.except.system.configuration") WUNUSED longptr_t
(LIBCCALL libc_SysConf)(__STDC_INT_AS_UINT_T name) THROWS(...)
/*[[[body:libc_SysConf]]]*/
{
	longptr_t result;
	errno_t old_errno = libc_geterrno();
	(void)libc_seterrno(EOK);
	result = sysconf(name);
	if (result == -1 && libc_geterrno() == EINVAL) {
		(void)libc_seterrno(old_errno);
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SYSCONF_NAME,
		      name);
	}
	(void)libc_seterrno(old_errno);
	return result;
}
/*[[[end:libc_SysConf]]]*/

/*[[[skip:libc_Execve]]]*/
/*[[[skip:libc_Pipe]]]*/
/*[[[skip:libc_SetPGid]]]*/
/*[[[skip:libc_SetSid]]]*/
/*[[[skip:libc_SetUid]]]*/
/*[[[skip:libc_SetGid]]]*/
/*[[[skip:libc_Fork]]]*/
/*[[[skip:libc_ChOwn]]]*/
/*[[[skip:libc_Link]]]*/
/*[[[skip:libc_Read]]]*/
/*[[[skip:libc_Write]]]*/
/*[[[skip:libc_LSeek]]]*/
/*[[[skip:libc_Dup2]]]*/
/*[[[skip:libc_Dup]]]*/
/*[[[skip:libc_ChDir]]]*/
/*[[[skip:libc_Unlink]]]*/
/*[[[skip:libc_RmDir]]]*/
/*[[[skip:libc_FChOwnAt]]]*/
/*[[[skip:libc_LinkAt]]]*/
/*[[[skip:libc_SymlinkAt]]]*/
/*[[[skip:libc_ReadLinkAt]]]*/
/*[[[skip:libc_FReadLinkAt]]]*/
/*[[[skip:libc_UnlinkAt]]]*/
/*[[[skip:libc_LSeek64]]]*/
/*[[[skip:libc_PRead64]]]*/
/*[[[skip:libc_PWrite64]]]*/
/*[[[skip:libc_Pipe2]]]*/
/*[[[skip:libc_Dup3]]]*/
/*[[[skip:libc_SyncFS]]]*/
/*[[[skip:libc_GetRESUid]]]*/
/*[[[skip:libc_GetRESGid]]]*/
/*[[[skip:libc_SetRESUid]]]*/
/*[[[skip:libc_SetRESGid]]]*/
/*[[[skip:libc_VFork]]]*/
/*[[[skip:libc_FChOwn]]]*/
/*[[[skip:libc_FChDir]]]*/
/*[[[skip:libc_GetPGid]]]*/
/*[[[skip:libc_GetSid]]]*/
/*[[[skip:libc_LChOwn]]]*/
/*[[[skip:libc_Truncate]]]*/
/*[[[skip:libc_Truncate64]]]*/
/*[[[skip:libc_SetREUid]]]*/
/*[[[skip:libc_SetREGid]]]*/
/*[[[skip:libc_Symlink]]]*/
/*[[[skip:libc_ReadLink]]]*/
/*[[[skip:libc_SetHostName]]]*/
/*[[[skip:libc_SetDomainName]]]*/
/*[[[skip:libc_ChRoot]]]*/
/*[[[skip:libc_FTruncate64]]]*/
/*[[[skip:libc_FDataSync]]]*/
/*[[[skip:libc_Syscall]]]*/
/*[[[skip:libc_Syscall64]]]*/
/*[[[skip:libc_FTruncate]]]*/
/*[[[skip:libc_FSync]]]*/
/*[[[skip:libc_FChDirAt]]]*/
/*[[[skip:libc_FSymlinkAt]]]*/
/*[[[skip:libc_CloseRange]]]*/



/*[[[start:exports,hash:CRC-32=0xe7e4cf1a]]]*/
DEFINE_PUBLIC_ALIAS_P_VOID(Execv,libc_Execv,ATTR_NORETURN ATTR_IN(1) ATTR_IN(2),THROWING(...),LIBCCALL,(char const *__restrict path, __TARGV),(path,___argv));
DEFINE_PUBLIC_ALIAS_P_VOID(Execvp,libc_Execvp,ATTR_NORETURN ATTR_IN(1) ATTR_IN(2),THROWING(...),LIBCCALL,(char const *__restrict file, __TARGV),(file,___argv));
DEFINE_PUBLIC_ALIAS_P(FPathConf,libc_FPathConf,WUNUSED ATTR_FDARG(1),longptr_t,THROWING(...),LIBCCALL,(fd_t fd, __STDC_INT_AS_UINT_T name),(fd,name));
DEFINE_PUBLIC_ALIAS_P(PathConf,libc_PathConf,ATTR_IN(1),longptr_t,THROWING(...),LIBCCALL,(char const *path, __STDC_INT_AS_UINT_T name),(path,name));
DEFINE_PUBLIC_ALIAS_P(GetCwd,libc_GetCwd,ATTR_OUTS(1, 2),char *,THROWING(...),LIBCCALL,(char *buf, size_t bufsize),(buf,bufsize));
DEFINE_PUBLIC_ALIAS_P_VOID(FExecve,libc_FExecve,ATTR_NORETURN ATTR_FDREAD(1) ATTR_IN(2) ATTR_IN(3),THROWING(...),LIBCCALL,(fd_t fd, __TARGV, __TENVP),(fd,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P_VOID(Execvpe,libc_Execvpe,ATTR_NORETURN ATTR_IN(1) ATTR_IN(2) ATTR_IN(3),THROWING(...),LIBCCALL,(char const *__restrict file, __TARGV, __TENVP),(file,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(ConfStr,libc_ConfStr,ATTR_OUTS(2, 3),size_t,THROWING(...),LIBCCALL,(__STDC_INT_AS_UINT_T name, char *buf, size_t buflen),(name,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(Nice,libc_Nice,,int,THROWING(...),LIBCCALL,(int inc),(inc));
DEFINE_PUBLIC_ALIAS_P_VOID(SetPGrp,libc_SetPGrp,,THROWING(...),LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID(SetEUid,libc_SetEUid,,THROWING(...),LIBCCALL,(uid_t euid),(euid));
DEFINE_PUBLIC_ALIAS_P_VOID(SetEGid,libc_SetEGid,,THROWING(...),LIBCCALL,(gid_t egid),(egid));
DEFINE_PUBLIC_ALIAS_P_VOID(GetHostName,libc_GetHostName,ATTR_OUTS(1, 2),THROWING(...),LIBCCALL,(char *name, size_t buflen),(name,buflen));
DEFINE_PUBLIC_ALIAS_P_VOID(GetDomainName,libc_GetDomainName,ATTR_OUTS(1, 2),THROWING(...),LIBCCALL,(char *name, size_t buflen),(name,buflen));
DEFINE_PUBLIC_ALIAS_P(LPathConf,libc_LPathConf,ATTR_IN(1),longptr_t,THROWING(...),LIBCCALL,(char const *path, __STDC_INT_AS_UINT_T name),(path,name));
DEFINE_PUBLIC_ALIAS_P(SysConf,libc_SysConf,WUNUSED,longptr_t,THROWING(...),LIBCCALL,(__STDC_INT_AS_UINT_T name),(name));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_UNISTD_C */
