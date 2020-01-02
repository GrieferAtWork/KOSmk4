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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#include <hybrid/compiler.h>
#include <hybrid/host.h>
#include <asm/unistd.h>
#include <bits/types.h>

#define DEFINE_XSYSCALL_EXPORT(name, sys_Xname) \
	DEFINE_INTERN_ALIAS(libc_##name, libc_##sys_Xname) \
	DEFINE_PUBLIC_ALIAS(name, libc_##sys_Xname)


/* Directly alias exception-enabled variants of system functions
 * to the exception-enabled variants of system calls from the
 * system call export table, since they don't need a libc wrapper
 * for handling errno conversion or anything similar */
DEFINE_XSYSCALL_EXPORT(Pipe, sys_Xpipe)
DEFINE_XSYSCALL_EXPORT(Execve, sys_Xexecve)
DEFINE_XSYSCALL_EXPORT(SetPGid, sys_Xsetpgid)
DEFINE_XSYSCALL_EXPORT(SetSid, sys_Xsetsid)
DEFINE_XSYSCALL_EXPORT(Fork, sys_Xfork)
DEFINE_XSYSCALL_EXPORT(VFork, sys_Xfork) /* TODO */
DEFINE_XSYSCALL_EXPORT(Link, sys_Xlink)
DEFINE_XSYSCALL_EXPORT(Read, sys_Xread)
DEFINE_XSYSCALL_EXPORT(Write, sys_Xwrite)
DEFINE_XSYSCALL_EXPORT(Dup2, sys_Xdup2)
DEFINE_XSYSCALL_EXPORT(Dup, sys_Xdup)
DEFINE_XSYSCALL_EXPORT(Chdir, sys_Xchdir)
DEFINE_XSYSCALL_EXPORT(Unlink, sys_Xunlink)
DEFINE_XSYSCALL_EXPORT(Rmdir, sys_Xrmdir)
DEFINE_XSYSCALL_EXPORT(LinkAt, sys_Xlinkat)
DEFINE_XSYSCALL_EXPORT(SymlinkAt, sys_Xsymlinkat)
DEFINE_XSYSCALL_EXPORT(ReadlinkAt, sys_Xreadlinkat)
DEFINE_XSYSCALL_EXPORT(FReadlinkAt, sys_Xfreadlinkat)
DEFINE_XSYSCALL_EXPORT(UnlinkAt, sys_Xunlinkat)
DEFINE_XSYSCALL_EXPORT(PRead64, sys_Xpread64)
DEFINE_XSYSCALL_EXPORT(PWrite64, sys_Xpwrite64)
DEFINE_XSYSCALL_EXPORT(Pipe2, sys_Xpipe2)
DEFINE_XSYSCALL_EXPORT(Dup3, sys_Xdup3)
DEFINE_XSYSCALL_EXPORT(SyncFs, sys_Xsyncfs)
DEFINE_XSYSCALL_EXPORT(FChdir, sys_Xfchdir)
DEFINE_XSYSCALL_EXPORT(GetPGid, sys_Xgetpgid)
DEFINE_XSYSCALL_EXPORT(GetSid, sys_Xgetsid)
DEFINE_XSYSCALL_EXPORT(Symlink, sys_Xsymlink)
DEFINE_XSYSCALL_EXPORT(Readlink, sys_Xreadlink)
DEFINE_XSYSCALL_EXPORT(SetHostName, sys_Xsethostname)
DEFINE_XSYSCALL_EXPORT(SetDomainName, sys_Xsetdomainname)
DEFINE_XSYSCALL_EXPORT(ChRoot, sys_Xchroot)
DEFINE_XSYSCALL_EXPORT(FSync, sys_Xfsync)
DEFINE_XSYSCALL_EXPORT(FDataSync, sys_Xfdatasync)
DEFINE_XSYSCALL_EXPORT(Hop, sys_Xhop)
DEFINE_XSYSCALL_EXPORT(Hopf, sys_Xhopf)
DEFINE_XSYSCALL_EXPORT(KSysctl, sys_Xksysctl)
DEFINE_XSYSCALL_EXPORT(Ioctl, sys_Xioctl)
DEFINE_XSYSCALL_EXPORT(Fcntl, sys_Xfcntl)
DEFINE_XSYSCALL_EXPORT(Open, sys_Xopen)
DEFINE_XSYSCALL_EXPORT(Creat, sys_Xcreat)
DEFINE_XSYSCALL_EXPORT(OpenAt, sys_Xopenat)
DEFINE_XSYSCALL_EXPORT(Open64, sys_Xopen)
DEFINE_XSYSCALL_EXPORT(Creat64, sys_Xcreat)
DEFINE_XSYSCALL_EXPORT(OpenAt64, sys_Xopenat)
DEFINE_XSYSCALL_EXPORT(KStat, sys_Xkstat)         DEFINE_INTERN_ALIAS(libc_Stat, sys_Xkstat)
DEFINE_XSYSCALL_EXPORT(KFStat, sys_Xkfstat)       DEFINE_INTERN_ALIAS(libc_FStat, sys_Xkfstat)
DEFINE_XSYSCALL_EXPORT(KLStat, sys_Xklstat)       DEFINE_INTERN_ALIAS(libc_LStat, sys_Xklstat)
DEFINE_XSYSCALL_EXPORT(KFStatAt, sys_Xkfstatat)   DEFINE_INTERN_ALIAS(libc_FStatAt, sys_Xkfstatat)
DEFINE_XSYSCALL_EXPORT(KStat64, sys_Xkstat)       DEFINE_INTERN_ALIAS(libc_Stat64, sys_Xkstat)
DEFINE_XSYSCALL_EXPORT(KFStat64, sys_Xkfstat)     DEFINE_INTERN_ALIAS(libc_FStat64, sys_Xkfstat)
DEFINE_XSYSCALL_EXPORT(KLStat64, sys_Xklstat)     DEFINE_INTERN_ALIAS(libc_LStat64, sys_Xklstat)
DEFINE_XSYSCALL_EXPORT(KFStatAt64, sys_Xkfstatat) DEFINE_INTERN_ALIAS(libc_FStatAt64, sys_Xkfstatat)
DEFINE_XSYSCALL_EXPORT(Chmod, sys_Xchmod)
DEFINE_XSYSCALL_EXPORT(FChmodAt, sys_Xfchmodat)
DEFINE_XSYSCALL_EXPORT(FChmod, sys_Xfchmod)
DEFINE_XSYSCALL_EXPORT(UTimensAt, sys_Xutimensat)
DEFINE_XSYSCALL_EXPORT(Mkdir, sys_Xmkdir)
DEFINE_XSYSCALL_EXPORT(FMkdirAt, sys_Xfmkdirat)
DEFINE_XSYSCALL_EXPORT(FMknodAt, sys_Xfmknodat)
DEFINE_XSYSCALL_EXPORT(MkdirAt, sys_Xmkdirat)
DEFINE_XSYSCALL_EXPORT(MknodAt, sys_Xmknodat)

#ifdef __NR_getresuid32
DEFINE_XSYSCALL_EXPORT(GetResUid, sys_Xgetresuid32)
DEFINE_XSYSCALL_EXPORT(GetResGid, sys_Xgetresgid32)
DEFINE_XSYSCALL_EXPORT(SetResUid, sys_Xsetresuid32)
DEFINE_XSYSCALL_EXPORT(SetResGid, sys_Xsetresgid32)
DEFINE_XSYSCALL_EXPORT(SetReUid, sys_Xsetreuid32)
DEFINE_XSYSCALL_EXPORT(SetReGid, sys_Xsetregid32)
#else /* __NR_getresuid32 */
DEFINE_XSYSCALL_EXPORT(GetResUid, sys_Xgetresuid)
DEFINE_XSYSCALL_EXPORT(GetResGid, sys_Xgetresgid)
DEFINE_XSYSCALL_EXPORT(SetResUid, sys_Xsetresuid)
DEFINE_XSYSCALL_EXPORT(SetResGid, sys_Xsetresgid)
DEFINE_XSYSCALL_EXPORT(SetReUid, sys_Xsetreuid)
DEFINE_XSYSCALL_EXPORT(SetReGid, sys_Xsetregid)
#endif /* !__NR_getresuid32 */

#ifdef __NR_setuid32
DEFINE_XSYSCALL_EXPORT(SetUid, sys_Xsetuid32)
DEFINE_XSYSCALL_EXPORT(SetGid, sys_Xsetgid32)
#else /* __NR_setuid32 */
DEFINE_XSYSCALL_EXPORT(SetUid, sys_Xsetuid)
DEFINE_XSYSCALL_EXPORT(SetGid, sys_Xsetgid)
#endif /* !__NR_setuid32 */

#ifdef __NR_chown32
DEFINE_XSYSCALL_EXPORT(Chown, sys_Xchown32)
DEFINE_XSYSCALL_EXPORT(FChown, sys_Xfchown32)
DEFINE_XSYSCALL_EXPORT(LChown, sys_Xlchown32)
#else /* __NR_chown32 */
DEFINE_XSYSCALL_EXPORT(Chown, sys_Xchown)
DEFINE_XSYSCALL_EXPORT(FChown, sys_Xfchown)
DEFINE_XSYSCALL_EXPORT(LChown, sys_Xlchown)
#endif /* !__NR_chown32 */

#ifdef __NR_fchownat32
DEFINE_XSYSCALL_EXPORT(FChownAt, sys_Xfchownat32)
#else /* __NR_fchownat32 */
DEFINE_XSYSCALL_EXPORT(FChownAt, sys_Xfchownat)
#endif /* !__NR_fchownat32 */

#ifdef __NR_truncate64
DEFINE_XSYSCALL_EXPORT(Truncate, sys_Xtruncate)
DEFINE_XSYSCALL_EXPORT(Truncate64, sys_Xtruncate64)
DEFINE_XSYSCALL_EXPORT(FTruncate, sys_Xftruncate)
DEFINE_XSYSCALL_EXPORT(FTruncate64, sys_Xftruncate64)
DEFINE_XSYSCALL_EXPORT(LSeek, sys_Xlseek)
DEFINE_XSYSCALL_EXPORT(LSeek64, sys_Xlseek64)
#elif __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_XSYSCALL_EXPORT(Truncate, sys_Xtruncate)
DEFINE_XSYSCALL_EXPORT(Truncate64, sys_Xtruncate)
DEFINE_XSYSCALL_EXPORT(FTruncate, sys_Xftruncate)
DEFINE_XSYSCALL_EXPORT(FTruncate64, sys_Xftruncate)
DEFINE_XSYSCALL_EXPORT(LSeek, sys_Xlseek64)
DEFINE_XSYSCALL_EXPORT(LSeek64, sys_Xlseek64)
#else
#error "Invalid configuration"
#endif

#ifdef __NR_utimensat64
DEFINE_XSYSCALL_EXPORT(UTimensAt64, sys_Xutimensat64)
#elif __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_XSYSCALL_EXPORT(UTimensAt64, sys_Xutimensat)
#else
#error "Invalid configuration"
#endif

#undef DEFINE_XSYSCALL_EXPORT
