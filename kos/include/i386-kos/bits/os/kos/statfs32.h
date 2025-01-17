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
#ifndef _I386_KOS_BITS_OS_KOS_STATFS32_H
#define _I386_KOS_BITS_OS_KOS_STATFS32_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef statfsx32
#pragma push_macro("statfsx32")
#define __PRIVATE_DID_PUSH_STATFSX32
#endif /* statfsx32 */
#ifdef statfsx32_64
#pragma push_macro("statfsx32_64")
#define __PRIVATE_DID_PUSH_STATFSX32_64
#endif /* statfsx32_64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/*[[[autogen:wrap3264_x32_and_x32_64(
	linkIf:    "defined(__i386__) && !defined(__x86_64__)",
	name:      "statfs",
	name32:    "statfsx32",
	name64:    "statfsx32_64",
	altname64: "__statfsx32_64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_LARGEFILE64)",
	link64If:  "defined(__USE_FILE_OFFSET64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef statfsx32
#undef statfsx32_64
#if !defined(__i386__) || defined(__x86_64__)
#define statfsx32    __statfsx32
#define statfsx32_64 __statfsx32_64
#else /* !__i386__ || __x86_64__ */
#include <features.h>
#ifdef __USE_FILE_OFFSET64
/* Configure:
 *   - `statfsx32_64' as `statfs'
 *   - `statfsx32' as `__statfs32' */
#define statfsx32      __statfs32
#define statfsx32_64   statfs
#define __statfsx32    __statfs32
#define __statfsx32_64 statfs
#define __statfs32     __statfs32
#define __statfs_alt   __statfs32
#ifdef __USE_KOS
#define statfs32 __statfs32
#endif /* !__USE_KOS */
#ifdef __USE_LARGEFILE64
#ifdef __USE_STRUCT64_MACRO
#define statfs64   statfs
#define __statfs64 statfs
#else /* __USE_STRUCT64_MACRO */
#define __statfsx32_64_alt statfs64
#define __statfs64         statfs64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_LARGEFILE64 */
#define __statfs64 statfs
#endif /* !__USE_LARGEFILE64 */

#define __OFFSET_STATFS_TYPE    __OFFSET_STATFSX32_64_TYPE
#define __OFFSET_STATFS_BSIZE   __OFFSET_STATFSX32_64_BSIZE
#define __OFFSET_STATFS_BLOCKS  __OFFSET_STATFSX32_64_BLOCKS
#define __OFFSET_STATFS_BFREE   __OFFSET_STATFSX32_64_BFREE
#define __OFFSET_STATFS_BAVAIL  __OFFSET_STATFSX32_64_BAVAIL
#define __OFFSET_STATFS_FILES   __OFFSET_STATFSX32_64_FILES
#define __OFFSET_STATFS_FFREE   __OFFSET_STATFSX32_64_FFREE
#define __OFFSET_STATFS_FSID    __OFFSET_STATFSX32_64_FSID
#define __OFFSET_STATFS_NAMELEN __OFFSET_STATFSX32_64_NAMELEN
#define __OFFSET_STATFS_FRSIZE  __OFFSET_STATFSX32_64_FRSIZE
#define __OFFSET_STATFS_FLAGS   __OFFSET_STATFSX32_64_FLAGS
#define __OFFSET_STATFS_SPARE   __OFFSET_STATFSX32_64_SPARE
#define __SIZEOF_STATFS         __SIZEOF_STATFSX32_64
#define __ALIGNOF_STATFS        __ALIGNOF_STATFSX32_64

#else /* __USE_FILE_OFFSET64 */
/* Configure:
 *   - `statfsx32_64' as `statfs64' or `__statfs64'
 *   - `statfsx32' as `statfs' */
#define statfsx32   statfs
#define __statfs32  statfs
#define __statfsx32 statfs
#ifdef __USE_KOS
#define statfs32 statfs
#endif /* __USE_KOS */
#ifdef __USE_LARGEFILE64
#define __statfsx32_64 statfs64
#define statfsx32_64   statfs64
#define __statfs64     statfs64
#define __statfs_alt   statfs64
#else /* __USE_LARGEFILE64 */
#define __statfsx32_64 __statfs64
#define statfsx32_64   __statfs64
#define __statfs64     __statfs64
#define __statfs_alt   __statfs64
#endif /* !__USE_LARGEFILE64 */

#define __OFFSET_STATFS_TYPE    __OFFSET_STATFSX32_TYPE
#define __OFFSET_STATFS_BSIZE   __OFFSET_STATFSX32_BSIZE
#define __OFFSET_STATFS_BLOCKS  __OFFSET_STATFSX32_BLOCKS
#define __OFFSET_STATFS_BFREE   __OFFSET_STATFSX32_BFREE
#define __OFFSET_STATFS_BAVAIL  __OFFSET_STATFSX32_BAVAIL
#define __OFFSET_STATFS_FILES   __OFFSET_STATFSX32_FILES
#define __OFFSET_STATFS_FFREE   __OFFSET_STATFSX32_FFREE
#define __OFFSET_STATFS_FSID    __OFFSET_STATFSX32_FSID
#define __OFFSET_STATFS_NAMELEN __OFFSET_STATFSX32_NAMELEN
#define __OFFSET_STATFS_FRSIZE  __OFFSET_STATFSX32_FRSIZE
#define __OFFSET_STATFS_FLAGS   __OFFSET_STATFSX32_FLAGS
#define __OFFSET_STATFS_SPARE   __OFFSET_STATFSX32_SPARE
#define __SIZEOF_STATFS         __SIZEOF_STATFSX32
#define __ALIGNOF_STATFS        __ALIGNOF_STATFSX32

#endif /* !__USE_FILE_OFFSET64 */

#define __OFFSET_STATFS32_TYPE    __OFFSET_STATFSX32_TYPE
#define __OFFSET_STATFS32_BSIZE   __OFFSET_STATFSX32_BSIZE
#define __OFFSET_STATFS32_BLOCKS  __OFFSET_STATFSX32_BLOCKS
#define __OFFSET_STATFS32_BFREE   __OFFSET_STATFSX32_BFREE
#define __OFFSET_STATFS32_BAVAIL  __OFFSET_STATFSX32_BAVAIL
#define __OFFSET_STATFS32_FILES   __OFFSET_STATFSX32_FILES
#define __OFFSET_STATFS32_FFREE   __OFFSET_STATFSX32_FFREE
#define __OFFSET_STATFS32_FSID    __OFFSET_STATFSX32_FSID
#define __OFFSET_STATFS32_NAMELEN __OFFSET_STATFSX32_NAMELEN
#define __OFFSET_STATFS32_FRSIZE  __OFFSET_STATFSX32_FRSIZE
#define __OFFSET_STATFS32_FLAGS   __OFFSET_STATFSX32_FLAGS
#define __OFFSET_STATFS32_SPARE   __OFFSET_STATFSX32_SPARE
#define __SIZEOF_STATFS32         __SIZEOF_STATFSX32
#define __ALIGNOF_STATFS32        __ALIGNOF_STATFSX32
#define __OFFSET_STATFS64_TYPE    __OFFSET_STATFSX32_64_TYPE
#define __OFFSET_STATFS64_BSIZE   __OFFSET_STATFSX32_64_BSIZE
#define __OFFSET_STATFS64_BLOCKS  __OFFSET_STATFSX32_64_BLOCKS
#define __OFFSET_STATFS64_BFREE   __OFFSET_STATFSX32_64_BFREE
#define __OFFSET_STATFS64_BAVAIL  __OFFSET_STATFSX32_64_BAVAIL
#define __OFFSET_STATFS64_FILES   __OFFSET_STATFSX32_64_FILES
#define __OFFSET_STATFS64_FFREE   __OFFSET_STATFSX32_64_FFREE
#define __OFFSET_STATFS64_FSID    __OFFSET_STATFSX32_64_FSID
#define __OFFSET_STATFS64_NAMELEN __OFFSET_STATFSX32_64_NAMELEN
#define __OFFSET_STATFS64_FRSIZE  __OFFSET_STATFSX32_64_FRSIZE
#define __OFFSET_STATFS64_FLAGS   __OFFSET_STATFSX32_64_FLAGS
#define __OFFSET_STATFS64_SPARE   __OFFSET_STATFSX32_64_SPARE
#define __SIZEOF_STATFS64         __SIZEOF_STATFSX32_64
#define __ALIGNOF_STATFS64        __ALIGNOF_STATFSX32_64

#define __statfs_defined
#endif /* __i386__ && !__x86_64__*/
/*[[[end]]]*/


#define __OFFSET_STATFSX32_TYPE     0
#define __OFFSET_STATFSX32_BSIZE    4
#define __OFFSET_STATFSX32_BLOCKS   8
#define __OFFSET_STATFSX32_BFREE    12
#define __OFFSET_STATFSX32_BAVAIL   16
#define __OFFSET_STATFSX32_FILES    20
#define __OFFSET_STATFSX32_FFREE    24
#define __OFFSET_STATFSX32_FSID     28
#define __OFFSET_STATFSX32_NAMELEN  36
#define __OFFSET_STATFSX32_FRSIZE   40
#define __OFFSET_STATFSX32_FLAGS    44
#define __OFFSET_STATFSX32_SPARE    48
#define __SIZEOF_STATFSX32          64
#define __ALIGNOF_STATFSX32         __ALIGNOF_INT32__

#define __OFFSET_STATFSX32_64_TYPE     0
#define __OFFSET_STATFSX32_64_BSIZE    4
#define __OFFSET_STATFSX32_64_BLOCKS   8
#define __OFFSET_STATFSX32_64_BFREE    16
#define __OFFSET_STATFSX32_64_BAVAIL   24
#define __OFFSET_STATFSX32_64_FILES    32
#define __OFFSET_STATFSX32_64_FFREE    40
#define __OFFSET_STATFSX32_64_FSID     48
#define __OFFSET_STATFSX32_64_NAMELEN  56
#define __OFFSET_STATFSX32_64_FRSIZE   60
#define __OFFSET_STATFSX32_64_FLAGS    64
#define __OFFSET_STATFSX32_64_SPARE    68
#define __SIZEOF_STATFSX32_64          88
#define __ALIGNOF_STATFSX32_64         __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN

/* NOTE: Documentation taken from https://linux.die.net/man/2/fstatfs */
struct statfsx32 /*[PREFIX(f_)]*/ {
	__ULONG32_TYPE__ f_type;     /* Type of file system (one of the constants from <linux/magic.h>) */
	__ULONG32_TYPE__ f_bsize;    /* Optimal transfer block size */
	__ULONG32_TYPE__ f_blocks;   /* Total data blocks in file system */
	__ULONG32_TYPE__ f_bfree;    /* Free blocks in fs */
	__ULONG32_TYPE__ f_bavail;   /* Free blocks available to unprivileged user */
	__ULONG32_TYPE__ f_files;    /* Total file nodes in file system */
	__ULONG32_TYPE__ f_ffree;    /* Free file nodes in fs */
	__fsid_t         f_fsid;     /* File system id */
	__ULONG32_TYPE__ f_namelen;  /* Maximum length of filenames */
	__ULONG32_TYPE__ f_frsize;   /* Fragment size (since Linux 2.6) */
	__ULONG32_TYPE__ f_flags;    /* Mount flags (set of `ST_*' from <sys/statvfs.h>) */
	__ULONG32_TYPE__ f_spare[4]; /* ??? */
};

struct statfsx32_64 /*[PREFIX(f_)]*/ {
	__ULONG32_TYPE__ f_type;     /* Type of file system (one of the constants from <linux/magic.h>) */
	__ULONG32_TYPE__ f_bsize;    /* Optimal transfer block size */
	__ULONG64_TYPE__ f_blocks;   /* Total data blocks in file system */
	__ULONG64_TYPE__ f_bfree;    /* Free blocks in fs */
	__ULONG64_TYPE__ f_bavail;   /* Free blocks available to unprivileged user */
	__ULONG64_TYPE__ f_files;    /* Total file nodes in file system */
	__ULONG64_TYPE__ f_ffree;    /* Free file nodes in fs */
	__fsid_t         f_fsid;     /* File system id */
	__ULONG32_TYPE__ f_namelen;  /* Maximum length of filenames */
	__ULONG32_TYPE__ f_frsize;   /* Fragment size (since Linux 2.6) */
	__ULONG32_TYPE__ f_flags;    /* Mount flags (set of `ST_*' from <sys/statvfs.h>) */
	__ULONG32_TYPE__ f_spare[4]; /* ??? */
	__byte_t       __f_pad[4];
};

#ifdef __statfsx32_64_alt
struct __statfsx32_64_alt {
	__ULONG32_TYPE__ f_type;     /* Type of file system (one of the constants from <linux/magic.h>) */
	__ULONG32_TYPE__ f_bsize;    /* Optimal transfer block size */
	__ULONG64_TYPE__ f_blocks;   /* Total data blocks in file system */
	__ULONG64_TYPE__ f_bfree;    /* Free blocks in fs */
	__ULONG64_TYPE__ f_bavail;   /* Free blocks available to unprivileged user */
	__ULONG64_TYPE__ f_files;    /* Total file nodes in file system */
	__ULONG64_TYPE__ f_ffree;    /* Free file nodes in fs */
	__fsid_t         f_fsid;     /* File system id */
	__ULONG32_TYPE__ f_namelen;  /* Maximum length of filenames */
	__ULONG32_TYPE__ f_frsize;   /* Fragment size (since Linux 2.6) */
	__ULONG32_TYPE__ f_flags;    /* Mount flags (set of `ST_*' from <sys/statvfs.h>) */
	__ULONG32_TYPE__ f_spare[4]; /* ??? */
	__byte_t       __f_pad[4];
};
#undef __statfsx32_64_alt
#endif /* __statfsx32_64_alt */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef statfsx32
#undef statfsx32_64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_STATFSX32_64
#undef __PRIVATE_DID_PUSH_STATFSX32_64
#pragma pop_macro("statfsx32_64")
#endif /* __PRIVATE_DID_PUSH_STATFSX32_64 */
#ifdef __PRIVATE_DID_PUSH_STATFSX32
#undef __PRIVATE_DID_PUSH_STATFSX32
#pragma pop_macro("statfsx32")
#endif /* __PRIVATE_DID_PUSH_STATFSX32 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_KOS_STATFS32_H */
