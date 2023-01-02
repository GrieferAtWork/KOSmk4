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

#include <hybrid/compiler.h>

#include <hybrid/host.h>

#include <asm/pkey.h>
#include <asm/unistd.h>
#include <bits/types.h>

#include <syscall.h>

#define DEFINE_XSYSCALL_EXPORT(name, sys_Xname)        \
	DEFINE_INTERN_ALIAS(libc_##name, libc_##sys_Xname) \
	DEFINE_PUBLIC_ALIAS(name, libc_##sys_Xname)


/* Directly  alias exception-enabled variants of system functions
 * to the  exception-enabled variants  of system  calls from  the
 * system call export table, since they don't need a libc wrapper
 * for handling errno conversion or anything similar */
DEFINE_XSYSCALL_EXPORT(Pipe, sys_Xpipe)
DEFINE_XSYSCALL_EXPORT(Execve, sys_Xexecve)
DEFINE_XSYSCALL_EXPORT(SetPGid, sys_Xsetpgid)
DEFINE_XSYSCALL_EXPORT(SetSid, sys_Xsetsid)
DEFINE_XSYSCALL_EXPORT(Fork, sys_Xfork)
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
DEFINE_XSYSCALL_EXPORT(MMap, sys_Xmmap)
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_XSYSCALL_EXPORT(MMap64, sys_Xmmap)
#endif /* __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */
DEFINE_XSYSCALL_EXPORT(MUnmap, sys_Xmunmap)
DEFINE_XSYSCALL_EXPORT(MProtect, sys_Xmprotect)
DEFINE_XSYSCALL_EXPORT(MSync, sys_Xmsync)
DEFINE_XSYSCALL_EXPORT(MLock, sys_Xmlock)
DEFINE_XSYSCALL_EXPORT(MUnlock, sys_Xmunlock)
DEFINE_XSYSCALL_EXPORT(MLockAll, sys_Xmlockall)
DEFINE_XSYSCALL_EXPORT(MUnlockAll, sys_Xmunlockall)
DEFINE_XSYSCALL_EXPORT(MAdvise, sys_Xmadvise)
DEFINE_XSYSCALL_EXPORT(MInCore, sys_Xmincore)
DEFINE_XSYSCALL_EXPORT(MRemap, sys_Xmremap)
DEFINE_XSYSCALL_EXPORT(RemapFilePages, sys_Xremap_file_pages)
DEFINE_XSYSCALL_EXPORT(MemFdCreate, sys_Xmemfd_create)
DEFINE_XSYSCALL_EXPORT(MLock2, sys_Xmlock2)
DEFINE_XSYSCALL_EXPORT(RpcSchedule, sys_Xrpc_schedule)
DEFINE_XSYSCALL_EXPORT(EPollCreate, sys_Xepoll_create)
DEFINE_XSYSCALL_EXPORT(EPollCreate1, sys_Xepoll_create1)
DEFINE_XSYSCALL_EXPORT(EPollCtl, sys_Xepoll_ctl)
DEFINE_XSYSCALL_EXPORT(EPollWait, sys_Xepoll_wait)

#ifdef __ARCH_HAVE_PKEY
DEFINE_XSYSCALL_EXPORT(PKeyAlloc, sys_Xpkey_alloc)
DEFINE_XSYSCALL_EXPORT(PKeyFree, sys_Xpkey_free)
DEFINE_XSYSCALL_EXPORT(PKeyMProtect, sys_Xpkey_mprotect)
#endif /* __ARCH_HAVE_PKEY */

DEFINE_XSYSCALL_EXPORT(Socket, sys_Xsocket)
DEFINE_XSYSCALL_EXPORT(SocketPair, sys_Xsocketpair)
DEFINE_XSYSCALL_EXPORT(Bind, sys_Xbind)
DEFINE_XSYSCALL_EXPORT(GetSockName, sys_Xgetsockname)
DEFINE_XSYSCALL_EXPORT(Connect, sys_Xconnect)
DEFINE_XSYSCALL_EXPORT(GetPeerName, sys_Xgetpeername)
DEFINE_XSYSCALL_EXPORT(GetSockOpt, sys_Xgetsockopt)
DEFINE_XSYSCALL_EXPORT(SetSockOpt, sys_Xsetsockopt)
DEFINE_XSYSCALL_EXPORT(Listen, sys_Xlisten)
DEFINE_XSYSCALL_EXPORT(Shutdown, sys_Xshutdown)
#ifdef SYS_accept
DEFINE_XSYSCALL_EXPORT(Accept, sys_Xaccept)
#endif /* SYS_accept */
DEFINE_XSYSCALL_EXPORT(Accept4, sys_Xaccept4)
#ifdef SYS_recvmmsg_time64
DEFINE_XSYSCALL_EXPORT(RecvMMsg64, sys_Xrecvmmsg_time64)
#elif __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_XSYSCALL_EXPORT(RecvMMsg64, sys_Xrecvmmsg)
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
#ifdef SYS_send
DEFINE_XSYSCALL_EXPORT(Send, sys_Xsend)
#endif /* SYS_send */
#ifdef SYS_sendto
DEFINE_XSYSCALL_EXPORT(SendTo, sys_Xsendto)
#endif /* SYS_sendto */
#ifdef SYS_sendmsg
DEFINE_XSYSCALL_EXPORT(SendMsg, sys_Xsendmsg)
#endif /* SYS_sendmsg */
DEFINE_XSYSCALL_EXPORT(SendMMsg, sys_Xsendmmsg)
#ifdef SYS_recv
DEFINE_XSYSCALL_EXPORT(Recv, sys_Xrecv)
#endif /* SYS_recv */
#ifdef SYS_recvmsg
DEFINE_XSYSCALL_EXPORT(RecvMsg, sys_Xrecvmsg)
#endif /* SYS_recvmsg */
DEFINE_XSYSCALL_EXPORT(RecvMMsg, sys_Xrecvmmsg)
#ifdef SYS_recvfrom
DEFINE_XSYSCALL_EXPORT(RecvFrom, sys_Xrecvfrom)
#endif /* SYS_recvfrom */



#ifdef SYS_getresuid32
DEFINE_XSYSCALL_EXPORT(GetResUid, sys_Xgetresuid32)
DEFINE_XSYSCALL_EXPORT(GetResGid, sys_Xgetresgid32)
DEFINE_XSYSCALL_EXPORT(SetResUid, sys_Xsetresuid32)
DEFINE_XSYSCALL_EXPORT(SetResGid, sys_Xsetresgid32)
DEFINE_XSYSCALL_EXPORT(SetReUid, sys_Xsetreuid32)
DEFINE_XSYSCALL_EXPORT(SetReGid, sys_Xsetregid32)
#else /* SYS_getresuid32 */
DEFINE_XSYSCALL_EXPORT(GetResUid, sys_Xgetresuid)
DEFINE_XSYSCALL_EXPORT(GetResGid, sys_Xgetresgid)
DEFINE_XSYSCALL_EXPORT(SetResUid, sys_Xsetresuid)
DEFINE_XSYSCALL_EXPORT(SetResGid, sys_Xsetresgid)
DEFINE_XSYSCALL_EXPORT(SetReUid, sys_Xsetreuid)
DEFINE_XSYSCALL_EXPORT(SetReGid, sys_Xsetregid)
#endif /* !SYS_getresuid32 */

#ifdef SYS_setuid32
DEFINE_XSYSCALL_EXPORT(SetUid, sys_Xsetuid32)
DEFINE_XSYSCALL_EXPORT(SetGid, sys_Xsetgid32)
#else /* SYS_setuid32 */
DEFINE_XSYSCALL_EXPORT(SetUid, sys_Xsetuid)
DEFINE_XSYSCALL_EXPORT(SetGid, sys_Xsetgid)
#endif /* !SYS_setuid32 */

#ifdef SYS_chown32
DEFINE_XSYSCALL_EXPORT(Chown, sys_Xchown32)
DEFINE_XSYSCALL_EXPORT(FChown, sys_Xfchown32)
DEFINE_XSYSCALL_EXPORT(LChown, sys_Xlchown32)
#else /* SYS_chown32 */
DEFINE_XSYSCALL_EXPORT(Chown, sys_Xchown)
DEFINE_XSYSCALL_EXPORT(FChown, sys_Xfchown)
DEFINE_XSYSCALL_EXPORT(LChown, sys_Xlchown)
#endif /* !SYS_chown32 */

#ifdef SYS_fchownat32
DEFINE_XSYSCALL_EXPORT(FChownAt, sys_Xfchownat32)
#else /* SYS_fchownat32 */
DEFINE_XSYSCALL_EXPORT(FChownAt, sys_Xfchownat)
#endif /* !SYS_fchownat32 */

#ifdef SYS_truncate64
DEFINE_XSYSCALL_EXPORT(Truncate, sys_Xtruncate)
DEFINE_XSYSCALL_EXPORT(Truncate64, sys_Xtruncate64)
DEFINE_XSYSCALL_EXPORT(FTruncate, sys_Xftruncate)
DEFINE_XSYSCALL_EXPORT(FTruncate64, sys_Xftruncate64)
#elif __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_XSYSCALL_EXPORT(Truncate, sys_Xtruncate)
DEFINE_XSYSCALL_EXPORT(Truncate64, sys_Xtruncate)
DEFINE_XSYSCALL_EXPORT(FTruncate, sys_Xftruncate)
DEFINE_XSYSCALL_EXPORT(FTruncate64, sys_Xftruncate)
#else /* ... */
#error "Invalid configuration"
#endif /* !... */

#ifdef SYS_lseek64
DEFINE_XSYSCALL_EXPORT(LSeek, sys_Xlseek)
DEFINE_XSYSCALL_EXPORT(LSeek64, sys_Xlseek64)
#elif __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_XSYSCALL_EXPORT(LSeek, sys_Xlseek)
DEFINE_XSYSCALL_EXPORT(LSeek64, sys_Xlseek)
#else /* ... */
#error "Invalid configuration"
#endif /* !... */

#ifdef SYS_utimensat_time64
DEFINE_XSYSCALL_EXPORT(UTimensAt64, sys_Xutimensat_time64)
#elif __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_XSYSCALL_EXPORT(UTimensAt64, sys_Xutimensat)
#else /* ... */
#error "Invalid configuration"
#endif /* !... */

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_XSYSCALL_EXPORT(LFutexExpr, sys_Xlfutexexpr)
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
DEFINE_XSYSCALL_EXPORT(LFutexExpr64, sys_Xlfutexexpr)

#undef DEFINE_XSYSCALL_EXPORT
