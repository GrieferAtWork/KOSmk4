/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_OS_KOS_STATFS_H
#define _BITS_OS_KOS_STATFS_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>

#define _STATFS_F_NAMELEN 1
#define _STATFS_F_FRSIZE 1
#define _STATFS_F_FLAGS 1
#if (__SIZEOF_FSBLKCNT64_T__ == __SIZEOF_FSBLKCNT32_T__ && \
     __SIZEOF_FSFILCNT64_T__ == __SIZEOF_FSFILCNT32_T__)
#define _STATFS_MATCHES_STATFS64 1
#endif /* ... */


#ifdef __USE_FILE_OFFSET64
#if defined(_STATFS_MATCHES_STATFS64) && defined(__USE_KOS)
#define __statfs32 statfs
#define __statfs64 statfs
#ifdef __USE_KOS
#define statfs32 __statfs32
#endif /* __USE_KOS */
#else /* _STATFS_MATCHES_STATFS64 && __USE_KOS */
#define __statfs64 statfs
#ifdef __USE_KOS
#define __statfs32 statfs32
#endif /* __USE_KOS */
#endif /* !_STATFS_MATCHES_STATFS64 || !__USE_KOS */
#ifdef __USE_LARGEFILE64
#define statfs64 statfs
#endif /* __USE_LARGEFILE64 */

#define __OFFSET_STATFS_TYPE     __OFFSET_STATFS64_TYPE
#define __OFFSET_STATFS_BSIZE    __OFFSET_STATFS64_BSIZE
#define __OFFSET_STATFS_BLOCKS   __OFFSET_STATFS64_BLOCKS
#define __OFFSET_STATFS_BFREE    __OFFSET_STATFS64_BFREE
#define __OFFSET_STATFS_BAVAIL   __OFFSET_STATFS64_BAVAIL
#define __OFFSET_STATFS_FILES    __OFFSET_STATFS64_FILES
#define __OFFSET_STATFS_FFREE    __OFFSET_STATFS64_FFREE
#define __OFFSET_STATFS_FSID     __OFFSET_STATFS64_FSID
#define __OFFSET_STATFS_NAMELEN  __OFFSET_STATFS64_NAMELEN
#define __OFFSET_STATFS_FRSIZE   __OFFSET_STATFS64_FRSIZE
#define __OFFSET_STATFS_FLAGS    __OFFSET_STATFS64_FLAGS
#define __OFFSET_STATFS_SPARE    __OFFSET_STATFS64_SPARE
#define __ALIGNOF_STATFS         __ALIGNOF_STATFS64
#define __SIZEOF_STATFS          __SIZEOF_STATFS64
#else /* __USE_FILE_OFFSET64 */

#define __statfs32 statfs
#ifdef __USE_KOS
#define statfs32   statfs
#endif /* __USE_KOS */

#ifdef __USE_LARGEFILE64
#if defined(_STATFS_MATCHES_STATFS64) && defined(__USE_KOS)
#define statfs64   statfs
#else /* _STATFS_MATCHES_STATFS64 && __USE_KOS */
#define __statfs64 statfs64
#endif /* !_STATFS_MATCHES_STATFS64 || !__USE_KOS */
#endif /* __USE_LARGEFILE64 */

#if defined(_STATFS_MATCHES_STATFS64) && defined(__USE_KOS)
#define __statfs64 statfs
#endif /* _STATFS_MATCHES_STATFS64 && __USE_KOS */

#define __OFFSET_STATFS_TYPE     __OFFSET_STATFS32_TYPE
#define __OFFSET_STATFS_BSIZE    __OFFSET_STATFS32_BSIZE
#define __OFFSET_STATFS_BLOCKS   __OFFSET_STATFS32_BLOCKS
#define __OFFSET_STATFS_BFREE    __OFFSET_STATFS32_BFREE
#define __OFFSET_STATFS_BAVAIL   __OFFSET_STATFS32_BAVAIL
#define __OFFSET_STATFS_FILES    __OFFSET_STATFS32_FILES
#define __OFFSET_STATFS_FFREE    __OFFSET_STATFS32_FFREE
#define __OFFSET_STATFS_FSID     __OFFSET_STATFS32_FSID
#define __OFFSET_STATFS_NAMELEN  __OFFSET_STATFS32_NAMELEN
#define __OFFSET_STATFS_FRSIZE   __OFFSET_STATFS32_FRSIZE
#define __OFFSET_STATFS_FLAGS    __OFFSET_STATFS32_FLAGS
#define __OFFSET_STATFS_SPARE    __OFFSET_STATFS32_SPARE
#define __ALIGNOF_STATFS         __ALIGNOF_STATFS32
#define __SIZEOF_STATFS          __SIZEOF_STATFS32
#endif /* !__USE_FILE_OFFSET64 */


#define __OFFSET_STATFS32_TYPE     0
#define __OFFSET_STATFS32_BSIZE    __SIZEOF_SYSCALL_LONG_T__
#define __OFFSET_STATFS32_BLOCKS   (__SIZEOF_SYSCALL_LONG_T__ * 2)
#define __OFFSET_STATFS32_BFREE    (__SIZEOF_SYSCALL_LONG_T__ * 2 + __SIZEOF_FSBLKCNT32_T__)
#define __OFFSET_STATFS32_BAVAIL   (__SIZEOF_SYSCALL_LONG_T__ * 2 + __SIZEOF_FSBLKCNT32_T__ * 2)
#define __OFFSET_STATFS32_FILES    (__SIZEOF_SYSCALL_LONG_T__ * 2 + __SIZEOF_FSBLKCNT32_T__ * 3)
#define __OFFSET_STATFS32_FFREE    (__SIZEOF_SYSCALL_LONG_T__ * 2 + __SIZEOF_FSBLKCNT32_T__ * 3 + __SIZEOF_FSFILCNT32_T__)
#define __OFFSET_STATFS32_FSID     (__SIZEOF_SYSCALL_LONG_T__ * 2 + __SIZEOF_FSBLKCNT32_T__ * 3 + __SIZEOF_FSFILCNT32_T__ * 2)
#define __OFFSET_STATFS32_NAMELEN  (__SIZEOF_SYSCALL_LONG_T__ * 2 + __SIZEOF_FSBLKCNT32_T__ * 3 + __SIZEOF_FSFILCNT32_T__ * 2 + __SIZEOF_FSID_T__)
#define __OFFSET_STATFS32_FRSIZE   (__SIZEOF_SYSCALL_LONG_T__ * 3 + __SIZEOF_FSBLKCNT32_T__ * 3 + __SIZEOF_FSFILCNT32_T__ * 2 + __SIZEOF_FSID_T__)
#define __OFFSET_STATFS32_FLAGS    (__SIZEOF_SYSCALL_LONG_T__ * 4 + __SIZEOF_FSBLKCNT32_T__ * 3 + __SIZEOF_FSFILCNT32_T__ * 2 + __SIZEOF_FSID_T__)
#define __OFFSET_STATFS32_SPARE    (__SIZEOF_SYSCALL_LONG_T__ * 5 + __SIZEOF_FSBLKCNT32_T__ * 3 + __SIZEOF_FSFILCNT32_T__ * 2 + __SIZEOF_FSID_T__)
#if (__SIZEOF_FSBLKCNT32_T__ >= __SIZEOF_SYSCALL_LONG_T__ && \
     __SIZEOF_FSBLKCNT32_T__ >= __SIZEOF_FSFILCNT32_T__)
#define __ALIGNOF_STATFS32         __SIZEOF_FSBLKCNT32_T__
#elif __SIZEOF_FSFILCNT32_T__ >= __SIZEOF_SYSCALL_LONG_T__
#define __ALIGNOF_STATFS32         __SIZEOF_FSFILCNT32_T__
#else
#define __ALIGNOF_STATFS32         __SIZEOF_SYSCALL_LONG_T__
#endif
#define __RAW_SIZEOF_STATFS32      (__SIZEOF_SYSCALL_LONG_T__ * 9 + __SIZEOF_FSBLKCNT32_T__ * 3 + __SIZEOF_FSFILCNT32_T__ * 2 + __SIZEOF_FSID_T__)
#define __SIZEOF_STATFS32          ((__RAW_SIZEOF_STATFS32 + (__ALIGNOF_STATFS32 - 1)) & ~(__ALIGNOF_STATFS32 - 1))

#define __OFFSET_STATFS64_TYPE     0
#define __OFFSET_STATFS64_BSIZE    __SIZEOF_SYSCALL_LONG_T__
#define __OFFSET_STATFS64_BLOCKS   (__SIZEOF_SYSCALL_LONG_T__ * 2)
#define __OFFSET_STATFS64_BFREE    (__SIZEOF_SYSCALL_LONG_T__ * 2 + __SIZEOF_FSBLKCNT64_T__)
#define __OFFSET_STATFS64_BAVAIL   (__SIZEOF_SYSCALL_LONG_T__ * 2 + __SIZEOF_FSBLKCNT64_T__ * 2)
#define __OFFSET_STATFS64_FILES    (__SIZEOF_SYSCALL_LONG_T__ * 2 + __SIZEOF_FSBLKCNT64_T__ * 3)
#define __OFFSET_STATFS64_FFREE    (__SIZEOF_SYSCALL_LONG_T__ * 2 + __SIZEOF_FSBLKCNT64_T__ * 3 + __SIZEOF_FSFILCNT64_T__)
#define __OFFSET_STATFS64_FSID     (__SIZEOF_SYSCALL_LONG_T__ * 2 + __SIZEOF_FSBLKCNT64_T__ * 3 + __SIZEOF_FSFILCNT64_T__ * 2)
#define __OFFSET_STATFS64_NAMELEN  (__SIZEOF_SYSCALL_LONG_T__ * 2 + __SIZEOF_FSBLKCNT64_T__ * 3 + __SIZEOF_FSFILCNT64_T__ * 2 + __SIZEOF_FSID_T__)
#define __OFFSET_STATFS64_FRSIZE   (__SIZEOF_SYSCALL_LONG_T__ * 3 + __SIZEOF_FSBLKCNT64_T__ * 3 + __SIZEOF_FSFILCNT64_T__ * 2 + __SIZEOF_FSID_T__)
#define __OFFSET_STATFS64_FLAGS    (__SIZEOF_SYSCALL_LONG_T__ * 4 + __SIZEOF_FSBLKCNT64_T__ * 3 + __SIZEOF_FSFILCNT64_T__ * 2 + __SIZEOF_FSID_T__)
#define __OFFSET_STATFS64_SPARE    (__SIZEOF_SYSCALL_LONG_T__ * 5 + __SIZEOF_FSBLKCNT64_T__ * 3 + __SIZEOF_FSFILCNT64_T__ * 2 + __SIZEOF_FSID_T__)
#if (__SIZEOF_FSBLKCNT64_T__ >= __SIZEOF_SYSCALL_LONG_T__ && \
     __SIZEOF_FSBLKCNT64_T__ >= __SIZEOF_FSFILCNT64_T__)
#define __ALIGNOF_STATFS64         __SIZEOF_FSBLKCNT64_T__
#elif __SIZEOF_FSFILCNT64_T__ >= __SIZEOF_SYSCALL_LONG_T__
#define __ALIGNOF_STATFS64         __SIZEOF_FSFILCNT64_T__
#else
#define __ALIGNOF_STATFS64         __SIZEOF_SYSCALL_LONG_T__
#endif
#define __RAW_SIZEOF_STATFS64      (__SIZEOF_SYSCALL_LONG_T__ * 9 + __SIZEOF_FSBLKCNT64_T__ * 3 + __SIZEOF_FSFILCNT64_T__ * 2 + __SIZEOF_FSID_T__)
#define __SIZEOF_STATFS64          ((__RAW_SIZEOF_STATFS64 + (__ALIGNOF_STATFS64 - 1)) & ~(__ALIGNOF_STATFS64 - 1))

#ifdef __CC__
__DECL_BEGIN

#if 0 /* For assert_types.c */
struct statfs /*[PREFIX(f_)]*/ {};
struct statfs32 /*[PREFIX(f_)]*/ {};
struct statfs64 /*[PREFIX(f_)]*/ {};
#endif

/* NOTE: Documentation taken from https://linux.die.net/man/2/fstatfs */
struct __statfs32 /*[PREFIX(f_)][NAME(statfs32)]*/ {
	__syscall_ulong_t f_type;     /* Type of file system (one of the constants from <linux/magic.h>) */
	__syscall_ulong_t f_bsize;    /* Optimal transfer block size */
	__fsblkcnt32_t    f_blocks;   /* Total data blocks in file system */
	__fsblkcnt32_t    f_bfree;    /* Free blocks in fs */
	__fsblkcnt32_t    f_bavail;   /* Free blocks available to unprivileged user */
	__fsfilcnt32_t    f_files;    /* Total file nodes in file system */
	__fsfilcnt32_t    f_ffree;    /* Free file nodes in fs */
	__fsid_t          f_fsid;     /* File system id */
	__syscall_ulong_t f_namelen;  /* Maximum length of filenames */
	__syscall_ulong_t f_frsize;   /* Fragment size (since Linux 2.6) */
	__syscall_ulong_t f_flags;    /* Mount flags (set of `ST_*' from <sys/statvfs.h>) */
	__syscall_ulong_t f_spare[4]; /* ??? */
#if __SIZEOF_STATFS32 > __RAW_SIZEOF_STATFS32
	__byte_t __f_pad[__SIZEOF_STATFS32 - __RAW_SIZEOF_STATFS32];
#endif /* __SIZEOF_STATFS32 > __RAW_SIZEOF_STATFS32 */
};

#if !defined(_STATFS_MATCHES_STATFS64) || !defined(__USE_KOS)
struct __statfs64 /*[PREFIX(f_)][NAME(statfs64)]*/ {
	__syscall_ulong_t f_type;     /* Type of file system (one of the constants from <linux/magic.h>) */
	__syscall_ulong_t f_bsize;    /* Optimal transfer block size */
	__fsblkcnt64_t    f_blocks;   /* Total data blocks in file system */
	__fsblkcnt64_t    f_bfree;    /* Free blocks in fs */
	__fsblkcnt64_t    f_bavail;   /* Free blocks available to unprivileged user */
	__fsfilcnt64_t    f_files;    /* Total file nodes in file system */
	__fsfilcnt64_t    f_ffree;    /* Free file nodes in fs */
	__fsid_t          f_fsid;     /* File system id */
	__syscall_ulong_t f_namelen;  /* Maximum length of filenames */
	__syscall_ulong_t f_frsize;   /* Fragment size (since Linux 2.6) */
	__syscall_ulong_t f_flags;    /* Mount flags (set of `ST_*' from <sys/statvfs.h>) */
	__syscall_ulong_t f_spare[4]; /* ??? */
#if __SIZEOF_STATFS64 > __RAW_SIZEOF_STATFS64
	__byte_t __f_pad[__SIZEOF_STATFS64 - __RAW_SIZEOF_STATFS64];
#endif /* __SIZEOF_STATFS64 > __RAW_SIZEOF_STATFS64 */
};
#endif /* !_STATFS_MATCHES_STATFS64 || !__USE_KOS */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_STATFS_H */
