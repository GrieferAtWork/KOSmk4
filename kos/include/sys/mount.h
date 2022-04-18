/* HASH CRC-32:0x9753fe1d */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/mount.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/mount.h) */
/* (#) Portability: FreeBSD       (/sys/sys/mount.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/mount.h) */
/* (#) Portability: NetBSD        (/sys/sys/mount.h) */
/* (#) Portability: OpenBSD       (/sys/sys/mount.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/mount.h) */
/* (#) Portability: diet libc     (/include/sys/mount.h) */
/* (#) Portability: libc4/5       (/include/sys/mount.h) */
/* (#) Portability: mintlib       (/include/sys/mount.h) */
/* (#) Portability: musl libc     (/include/sys/mount.h) */
/* (#) Portability: uClibc        (/include/sys/mount.h) */
#ifndef _SYS_MOUNT_H
#define _SYS_MOUNT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/block.h> /* __BLK* (ioctls) */
#include <asm/os/mount.h>



/************************************************************************/
/* A couple of ioctl(2) commands relating to block devices              */
/************************************************************************/
#if !defined(BLKROSET) && defined(__BLKROSET)
#define BLKROSET     __BLKROSET     /* [int const *arg] Set device read-only (0 = read-write) */
#endif /* !BLKROSET && __BLKROSET */
#if !defined(BLKROGET) && defined(__BLKROGET)
#define BLKROGET     __BLKROGET     /* [int *arg] Get read-only status (0 = read_write) */
#endif /* !BLKROGET && __BLKROGET */
#if !defined(BLKRRPART) && defined(__BLKRRPART)
#define BLKRRPART    __BLKRRPART    /* Re-read partition table */
#endif /* !BLKRRPART && __BLKRRPART */
#if !defined(BLKGETSIZE) && defined(__BLKGETSIZE)
#define BLKGETSIZE   __BLKGETSIZE   /* [long *arg] Return device size/512 */
#endif /* !BLKGETSIZE && __BLKGETSIZE */
#if !defined(BLKFLSBUF) && defined(__BLKFLSBUF)
#define BLKFLSBUF    __BLKFLSBUF    /* Flush buffer cache */
#endif /* !BLKFLSBUF && __BLKFLSBUF */
#if !defined(BLKRASET) && defined(__BLKRASET)
#define BLKRASET     __BLKRASET     /* [unsigned long const *arg] Set read ahead for block device */
#endif /* !BLKRASET && __BLKRASET */
#if !defined(BLKRAGET) && defined(__BLKRAGET)
#define BLKRAGET     __BLKRAGET     /* [unsigned long *arg] Get current read ahead setting */
#endif /* !BLKRAGET && __BLKRAGET */
#if !defined(BLKFRASET) && defined(__BLKFRASET)
#define BLKFRASET    __BLKFRASET    /* [unsigned long const *arg] Set filesystem read-ahead. */
#endif /* !BLKFRASET && __BLKFRASET */
#if !defined(BLKFRAGET) && defined(__BLKFRAGET)
#define BLKFRAGET    __BLKFRAGET    /* [unsigned long *arg] Get filesystem read-ahead. */
#endif /* !BLKFRAGET && __BLKFRAGET */
#if !defined(BLKSECTSET) && defined(__BLKSECTSET)
#define BLKSECTSET   __BLKSECTSET   /* [u16 const *arg] Set max sectors per request. */
#endif /* !BLKSECTSET && __BLKSECTSET */
#if !defined(BLKSECTGET) && defined(__BLKSECTGET)
#define BLKSECTGET   __BLKSECTGET   /* [u16 *arg] Get max sectors per request. */
#endif /* !BLKSECTGET && __BLKSECTGET */
#if !defined(BLKSSZGET) && defined(__BLKSSZGET)
#define BLKSSZGET    __BLKSSZGET    /* Get block device sector size */
#endif /* !BLKSSZGET && __BLKSSZGET */
#if !defined(BLKBSZGET) && defined(__BLKBSZGET)
#define BLKBSZGET    __BLKBSZGET    /* [size_t *arg] */
#endif /* !BLKBSZGET && __BLKBSZGET */
#if !defined(BLKBSZSET) && defined(__BLKBSZSET)
#define BLKBSZSET    __BLKBSZSET    /* [size_t const *arg] */
#endif /* !BLKBSZSET && __BLKBSZSET */
#if !defined(BLKGETSIZE64) && defined(__BLKGETSIZE64)
#define BLKGETSIZE64 __BLKGETSIZE64 /* [u64 *arg] return device size in bytes */
#endif /* !BLKGETSIZE64 && __BLKGETSIZE64 */
/************************************************************************/




/************************************************************************/
/* ??? Block size ??? (don't use; I have no idea what this references)  */
/************************************************************************/
#if !defined(BLOCK_SIZE) && defined(__BLOCK_SIZE)
#define BLOCK_SIZE      __BLOCK_SIZE      /* ... */
#endif /* !BLOCK_SIZE && __BLOCK_SIZE */
#if !defined(BLOCK_SIZE_BITS) && defined(__BLOCK_SIZE_BITS)
#define BLOCK_SIZE_BITS __BLOCK_SIZE_BITS /* ... */
#endif /* !BLOCK_SIZE_BITS && __BLOCK_SIZE_BITS */
/************************************************************************/




/************************************************************************/
/* Flags for `mount(2)'                                                 */
/************************************************************************/

/* Disallow `write(2)',  as  well  as  `PROT_WRITE | PROT_SHARED'  mappings.
 * Attempting to do either will result in `E_FSERROR_READONLY' being thrown. */
#if !defined(MS_RDONLY) && defined(__MS_RDONLY)
#define MS_RDONLY      __MS_RDONLY
#endif /* !MS_RDONLY && __MS_RDONLY */

/* Ignore `S_ISGID' and `S_ISUID' bits */
#if !defined(MS_NOSUID) && defined(__MS_NOSUID)
#define MS_NOSUID      __MS_NOSUID
#endif /* !MS_NOSUID && __MS_NOSUID */

/* ??? */
#if !defined(MS_NODEV) && defined(__MS_NODEV)
#define MS_NODEV       __MS_NODEV
#endif /* !MS_NODEV && __MS_NODEV */

/* Disallow execution of files. */
#if !defined(MS_NOEXEC) && defined(__MS_NOEXEC)
#define MS_NOEXEC      __MS_NOEXEC
#endif /* !MS_NOEXEC && __MS_NOEXEC */

/* ??? */
#if !defined(MS_SYNCHRONOUS) && defined(__MS_SYNCHRONOUS)
#define MS_SYNCHRONOUS __MS_SYNCHRONOUS
#endif /* !MS_SYNCHRONOUS && __MS_SYNCHRONOUS */

/* ACTION: Modify mounting point flags */
#if !defined(MS_REMOUNT) && defined(__MS_REMOUNT)
#define MS_REMOUNT     __MS_REMOUNT
#endif /* !MS_REMOUNT && __MS_REMOUNT */

/* ??? */
#if !defined(MS_MANDLOCK) && defined(__MS_MANDLOCK)
#define MS_MANDLOCK    __MS_MANDLOCK
#endif /* !MS_MANDLOCK && __MS_MANDLOCK */

/* ??? */
#if !defined(MS_DIRSYNC) && defined(__MS_DIRSYNC)
#define MS_DIRSYNC     __MS_DIRSYNC
#endif /* !MS_DIRSYNC && __MS_DIRSYNC */

/* Don't modify the value of `ATIME' (implies `MS_NODIRATIME') */
#if !defined(MS_NOATIME) && defined(__MS_NOATIME)
#define MS_NOATIME     __MS_NOATIME
#endif /* !MS_NOATIME && __MS_NOATIME */

/* Don't update `ATIME' during path traversal */
#if !defined(MS_NODIRATIME) && defined(__MS_NODIRATIME)
#define MS_NODIRATIME  __MS_NODIRATIME
#endif /* !MS_NODIRATIME && __MS_NODIRATIME */

/* ACTION: Bind fdirnode at `source' to `target' (MS_REMOUNT: override mounting point at target) */
#if !defined(MS_BIND) && defined(__MS_BIND)
#define MS_BIND        __MS_BIND
#endif /* !MS_BIND && __MS_BIND */

/* ACTION: Move a mounting point from `source' to `target' (MS_REMOUNT: override mounting point at target) */
#if !defined(MS_MOVE) && defined(__MS_MOVE)
#define MS_MOVE        __MS_MOVE
#endif /* !MS_MOVE && __MS_MOVE */

/* ??? */
#if !defined(MS_REC) && defined(__MS_REC)
#define MS_REC         __MS_REC
#endif /* !MS_REC && __MS_REC */

/* ??? */
#if !defined(MS_SILENT) && defined(__MS_SILENT)
#define MS_SILENT      __MS_SILENT
#endif /* !MS_SILENT && __MS_SILENT */

/* ??? */
#if !defined(MS_POSIXACL) && defined(__MS_POSIXACL)
#define MS_POSIXACL    __MS_POSIXACL
#endif /* !MS_POSIXACL && __MS_POSIXACL */

/* ??? */
#if !defined(MS_UNBINDABLE) && defined(__MS_UNBINDABLE)
#define MS_UNBINDABLE  __MS_UNBINDABLE
#endif /* !MS_UNBINDABLE && __MS_UNBINDABLE */

/* ??? */
#if !defined(MS_PRIVATE) && defined(__MS_PRIVATE)
#define MS_PRIVATE     __MS_PRIVATE
#endif /* !MS_PRIVATE && __MS_PRIVATE */

/* ??? */
#if !defined(MS_SLAVE) && defined(__MS_SLAVE)
#define MS_SLAVE       __MS_SLAVE
#endif /* !MS_SLAVE && __MS_SLAVE */

/* ??? */
#if !defined(MS_SHARED) && defined(__MS_SHARED)
#define MS_SHARED      __MS_SHARED
#endif /* !MS_SHARED && __MS_SHARED */

/* Only relevant when `MS_NOATIME' isn't set: the last-accessed timestamp is only changed to the
 * current realtime() when `OLD(ATIME) < MTIME'.  As such, ATIME can  only be used to  determine
 * accessed-after-last-modified when this flag has been set. */
#if !defined(MS_RELATIME) && defined(__MS_RELATIME)
#define MS_RELATIME    __MS_RELATIME
#endif /* !MS_RELATIME && __MS_RELATIME */

/* ??? */
#if !defined(MS_KERNMOUNT) && defined(__MS_KERNMOUNT)
#define MS_KERNMOUNT   __MS_KERNMOUNT
#endif /* !MS_KERNMOUNT && __MS_KERNMOUNT */

/* ??? */
#if !defined(MS_I_VERSION) && defined(__MS_I_VERSION)
#define MS_I_VERSION   __MS_I_VERSION
#endif /* !MS_I_VERSION && __MS_I_VERSION */

/* ??? */
#if !defined(MS_STRICTATIME) && defined(__MS_STRICTATIME)
#define MS_STRICTATIME __MS_STRICTATIME
#endif /* !MS_STRICTATIME && __MS_STRICTATIME */

/* ??? */
#if !defined(MS_LAZYTIME) && defined(__MS_LAZYTIME)
#define MS_LAZYTIME    __MS_LAZYTIME
#endif /* !MS_LAZYTIME && __MS_LAZYTIME */

/* ??? */
#if !defined(MS_ACTIVE) && defined(__MS_ACTIVE)
#define MS_ACTIVE      __MS_ACTIVE
#endif /* !MS_ACTIVE && __MS_ACTIVE */

/* ??? */
#if !defined(MS_NOUSER) && defined(__MS_NOUSER)
#define MS_NOUSER      __MS_NOUSER
#endif /* !MS_NOUSER && __MS_NOUSER */
/************************************************************************/

/* Flags that can be changed when combined with `MS_REMOUNT' */
#if !defined(MS_RMT_MASK) && defined(__MS_RMT_MASK)
#define MS_RMT_MASK __MS_RMT_MASK
#endif /* !MS_RMT_MASK && __MS_RMT_MASK */

/* Magic mount flag number. Must be or'd with flag values. */
#if !defined(MS_MGC_VAL) && defined(__MS_MGC_VAL)
#define MS_MGC_VAL __MS_MGC_VAL /* Magic flag indicating ~new~ flags. */
#endif /* !MS_MGC_VAL && __MS_MGC_VAL */
#if !defined(MS_MGC_MSK) && defined(__MS_MGC_MSK)
#define MS_MGC_MSK __MS_MGC_MSK /* Magic flag mask. */
#endif /* !MS_MGC_MSK && __MS_MGC_MSK */




/************************************************************************/
/* Flags for `umount2(2)'                                               */
/************************************************************************/

/* Force unmount. */
#if !defined(MNT_FORCE) && defined(__MNT_FORCE)
#define MNT_FORCE       __MNT_FORCE
#endif /* !MNT_FORCE && __MNT_FORCE */

/* Only detach from the file-tree. (Umount happens once no more path-references exist) */
#if !defined(MNT_DETACH) && defined(__MNT_DETACH)
#define MNT_DETACH      __MNT_DETACH
#endif /* !MNT_DETACH && __MNT_DETACH */

/* Mark mounting point as expired. */
#if !defined(MNT_EXPIRE) && defined(__MNT_EXPIRE)
#define MNT_EXPIRE      __MNT_EXPIRE
#endif /* !MNT_EXPIRE && __MNT_EXPIRE */

/* Don't follow symbolic links. */
#if !defined(UMOUNT_NOFOLLOW) && defined(__UMOUNT_NOFOLLOW)
#define UMOUNT_NOFOLLOW __UMOUNT_NOFOLLOW
#endif /* !UMOUNT_NOFOLLOW && __UMOUNT_NOFOLLOW */
/************************************************************************/

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_mount
/* >> mount(2)
 * @param: mountflags: Set of `MS_*' from <sys/mount.h> */
__CDECLARE(,int,__NOTHROW_RPC,mount,(char const *__special_file, char const *__dir, char const *__fstype, __ULONGPTR_TYPE__ __mountflags, void const *__data),(__special_file,__dir,__fstype,__mountflags,__data))
#elif defined(__CRT_HAVE___mount)
/* >> mount(2)
 * @param: mountflags: Set of `MS_*' from <sys/mount.h> */
__CREDIRECT(,int,__NOTHROW_RPC,mount,(char const *__special_file, char const *__dir, char const *__fstype, __ULONGPTR_TYPE__ __mountflags, void const *__data),__mount,(__special_file,__dir,__fstype,__mountflags,__data))
#elif defined(__CRT_HAVE___libc_mount)
/* >> mount(2)
 * @param: mountflags: Set of `MS_*' from <sys/mount.h> */
__CREDIRECT(,int,__NOTHROW_RPC,mount,(char const *__special_file, char const *__dir, char const *__fstype, __ULONGPTR_TYPE__ __mountflags, void const *__data),__libc_mount,(__special_file,__dir,__fstype,__mountflags,__data))
#endif /* ... */
#ifdef __CRT_HAVE_umount
/* >> umount(2) */
__CDECLARE(,int,__NOTHROW_RPC,umount,(char const *__special_file),(__special_file))
#elif defined(__CRT_HAVE___umount)
/* >> umount(2) */
__CREDIRECT(,int,__NOTHROW_RPC,umount,(char const *__special_file),__umount,(__special_file))
#elif defined(__CRT_HAVE___libc_umount)
/* >> umount(2) */
__CREDIRECT(,int,__NOTHROW_RPC,umount,(char const *__special_file),__libc_umount,(__special_file))
#elif defined(__CRT_HAVE_umount2)
#include <libc/local/sys.mount/umount.h>
/* >> umount(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(umount, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL umount)(char const *__special_file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(umount))(__special_file); })
#endif /* ... */
/* >> umount2(2)
 * @param: flags: Set of `MNT_FORCE | MNT_DETACH | MNT_EXPIRE | UMOUNT_NOFOLLOW' */
__CDECLARE_OPT(,int,__NOTHROW_RPC,umount2,(char const *__special_file, __STDC_INT_AS_UINT_T __flags),(__special_file,__flags))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_MOUNT_H */
