/* HASH CRC-32:0x1be1b073 */
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
#ifndef _SYS_MOUNT_H
#define _SYS_MOUNT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/ioctls/block.h> /* BLK* (ioctls) */
#include <asm/os/mount.h>

__SYSDECL_BEGIN

#if !defined(BLOCK_SIZE) && defined(__BLOCK_SIZE)
#define BLOCK_SIZE      __BLOCK_SIZE      /* ... */
#endif /* !BLOCK_SIZE && __BLOCK_SIZE */
#if !defined(BLOCK_SIZE_BITS) && defined(__BLOCK_SIZE_BITS)
#define BLOCK_SIZE_BITS __BLOCK_SIZE_BITS /* ... */
#endif /* !BLOCK_SIZE_BITS && __BLOCK_SIZE_BITS */

#if !defined(MS_RDONLY) && defined(__MS_RDONLY)
#define MS_RDONLY      __MS_RDONLY      /* TODO: Document me */
#endif /* !MS_RDONLY && __MS_RDONLY */
#if !defined(MS_NOSUID) && defined(__MS_NOSUID)
#define MS_NOSUID      __MS_NOSUID      /* TODO: Document me */
#endif /* !MS_NOSUID && __MS_NOSUID */
#if !defined(MS_NODEV) && defined(__MS_NODEV)
#define MS_NODEV       __MS_NODEV       /* TODO: Document me */
#endif /* !MS_NODEV && __MS_NODEV */
#if !defined(MS_NOEXEC) && defined(__MS_NOEXEC)
#define MS_NOEXEC      __MS_NOEXEC      /* TODO: Document me */
#endif /* !MS_NOEXEC && __MS_NOEXEC */
#if !defined(MS_SYNCHRONOUS) && defined(__MS_SYNCHRONOUS)
#define MS_SYNCHRONOUS __MS_SYNCHRONOUS /* TODO: Document me */
#endif /* !MS_SYNCHRONOUS && __MS_SYNCHRONOUS */
#if !defined(MS_REMOUNT) && defined(__MS_REMOUNT)
#define MS_REMOUNT     __MS_REMOUNT     /* TODO: Document me */
#endif /* !MS_REMOUNT && __MS_REMOUNT */
#if !defined(MS_MANDLOCK) && defined(__MS_MANDLOCK)
#define MS_MANDLOCK    __MS_MANDLOCK    /* TODO: Document me */
#endif /* !MS_MANDLOCK && __MS_MANDLOCK */
#if !defined(MS_DIRSYNC) && defined(__MS_DIRSYNC)
#define MS_DIRSYNC     __MS_DIRSYNC     /* TODO: Document me */
#endif /* !MS_DIRSYNC && __MS_DIRSYNC */
#if !defined(MS_NOATIME) && defined(__MS_NOATIME)
#define MS_NOATIME     __MS_NOATIME     /* TODO: Document me */
#endif /* !MS_NOATIME && __MS_NOATIME */
#if !defined(MS_NODIRATIME) && defined(__MS_NODIRATIME)
#define MS_NODIRATIME  __MS_NODIRATIME  /* TODO: Document me */
#endif /* !MS_NODIRATIME && __MS_NODIRATIME */
#if !defined(MS_BIND) && defined(__MS_BIND)
#define MS_BIND        __MS_BIND        /* TODO: Document me */
#endif /* !MS_BIND && __MS_BIND */
#if !defined(MS_MOVE) && defined(__MS_MOVE)
#define MS_MOVE        __MS_MOVE        /* TODO: Document me */
#endif /* !MS_MOVE && __MS_MOVE */
#if !defined(MS_REC) && defined(__MS_REC)
#define MS_REC         __MS_REC         /* TODO: Document me */
#endif /* !MS_REC && __MS_REC */
#if !defined(MS_SILENT) && defined(__MS_SILENT)
#define MS_SILENT      __MS_SILENT      /* TODO: Document me */
#endif /* !MS_SILENT && __MS_SILENT */
#if !defined(MS_POSIXACL) && defined(__MS_POSIXACL)
#define MS_POSIXACL    __MS_POSIXACL    /* TODO: Document me */
#endif /* !MS_POSIXACL && __MS_POSIXACL */
#if !defined(MS_UNBINDABLE) && defined(__MS_UNBINDABLE)
#define MS_UNBINDABLE  __MS_UNBINDABLE  /* TODO: Document me */
#endif /* !MS_UNBINDABLE && __MS_UNBINDABLE */
#if !defined(MS_PRIVATE) && defined(__MS_PRIVATE)
#define MS_PRIVATE     __MS_PRIVATE     /* TODO: Document me */
#endif /* !MS_PRIVATE && __MS_PRIVATE */
#if !defined(MS_SLAVE) && defined(__MS_SLAVE)
#define MS_SLAVE       __MS_SLAVE       /* TODO: Document me */
#endif /* !MS_SLAVE && __MS_SLAVE */
#if !defined(MS_SHARED) && defined(__MS_SHARED)
#define MS_SHARED      __MS_SHARED      /* TODO: Document me */
#endif /* !MS_SHARED && __MS_SHARED */
#if !defined(MS_RELATIME) && defined(__MS_RELATIME)
#define MS_RELATIME    __MS_RELATIME    /* TODO: Document me */
#endif /* !MS_RELATIME && __MS_RELATIME */
#if !defined(MS_KERNMOUNT) && defined(__MS_KERNMOUNT)
#define MS_KERNMOUNT   __MS_KERNMOUNT   /* TODO: Document me */
#endif /* !MS_KERNMOUNT && __MS_KERNMOUNT */
#if !defined(MS_I_VERSION) && defined(__MS_I_VERSION)
#define MS_I_VERSION   __MS_I_VERSION   /* TODO: Document me */
#endif /* !MS_I_VERSION && __MS_I_VERSION */
#if !defined(MS_STRICTATIME) && defined(__MS_STRICTATIME)
#define MS_STRICTATIME __MS_STRICTATIME /* TODO: Document me */
#endif /* !MS_STRICTATIME && __MS_STRICTATIME */
#if !defined(MS_LAZYTIME) && defined(__MS_LAZYTIME)
#define MS_LAZYTIME    __MS_LAZYTIME    /* TODO: Document me */
#endif /* !MS_LAZYTIME && __MS_LAZYTIME */
#if !defined(MS_ACTIVE) && defined(__MS_ACTIVE)
#define MS_ACTIVE      __MS_ACTIVE      /* TODO: Document me */
#endif /* !MS_ACTIVE && __MS_ACTIVE */
#if !defined(MS_NOUSER) && defined(__MS_NOUSER)
#define MS_NOUSER      __MS_NOUSER      /* TODO: Document me */
#endif /* !MS_NOUSER && __MS_NOUSER */

/* Flags that can be changed when combined with `MS_REMOUNT' */
#if !defined(MS_RMT_MASK) && defined(__MS_RMT_MASK)
#define MS_RMT_MASK __MS_RMT_MASK
#endif /* !MS_RMT_MASK && __MS_RMT_MASK /

/* Magic mount flag number. Must be or'd with flag values. */
#if !defined(MS_MGC_VAL) && defined(__MS_MGC_VAL)
#define MS_MGC_VAL __MS_MGC_VAL /* Magic flag indicating ~new~ flags. */
#endif /* !MS_MGC_VAL && __MS_MGC_VAL */
#if !defined(MS_MGC_MSK) && defined(__MS_MGC_MSK)
#define MS_MGC_MSK __MS_MGC_MSK /* Magic flag mask. */
#endif /* !MS_MGC_MSK && __MS_MGC_MSK */

/* Flags for `umount2(2)' */
#if !defined(MNT_FORCE) && defined(__MNT_FORCE)
#define MNT_FORCE       __MNT_FORCE       /* Force unmount. */
#endif /* !MNT_FORCE && __MNT_FORCE */
#if !defined(MNT_DETACH) && defined(__MNT_DETACH)
#define MNT_DETACH      __MNT_DETACH      /* Only detach from the file-tree. */
#endif /* !MNT_DETACH && __MNT_DETACH */
#if !defined(MNT_EXPIRE) && defined(__MNT_EXPIRE)
#define MNT_EXPIRE      __MNT_EXPIRE      /* Mark mounting point as expired. */
#endif /* !MNT_EXPIRE && __MNT_EXPIRE */
#if !defined(UMOUNT_NOFOLLOW) && defined(__UMOUNT_NOFOLLOW)
#define UMOUNT_NOFOLLOW __UMOUNT_NOFOLLOW /* Don't follow symbolic links. */
#endif /* !UMOUNT_NOFOLLOW && __UMOUNT_NOFOLLOW */

#ifdef __CC__
/* @param: mountflags: Set of `MS_*' from <sys/mount.h> */
__CDECLARE_OPT(,int,__NOTHROW_RPC,mount,(char const *__special_file, char const *__dir, char const *__fstype, __ULONGPTR_TYPE__ __mountflags, void const *__data),(__special_file,__dir,__fstype,__mountflags,__data))
#ifdef __CRT_HAVE_umount
__CDECLARE(,int,__NOTHROW_RPC,umount,(char const *__special_file),(__special_file))
#elif defined(__CRT_HAVE_umount2)
#include <libc/local/sys.mount/umount.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(umount, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL umount)(char const *__special_file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(umount))(__special_file); })
#endif /* ... */
/* @param: flags: Set of `MNT_FORCE | MNT_DETACH | MNT_EXPIRE | UMOUNT_NOFOLLOW' */
__CDECLARE_OPT(,int,__NOTHROW_RPC,umount2,(char const *__special_file, __STDC_INT_AS_UINT_T __flags),(__special_file,__flags))
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_MOUNT_H */
