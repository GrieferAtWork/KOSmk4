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
#ifndef _I386_KOS_BITS_OS_KOS_STATFS64_H
#define _I386_KOS_BITS_OS_KOS_STATFS64_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/types.h>


#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef statfsx64
#pragma push_macro("statfsx64")
#define __PRIVATE_DID_PUSH_STATFSX64
#endif /* statfsx64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/*[[[autogen:wrap3264_x64(
	linkIf:    "defined(__x86_64__)",
	name:      "statfs",
	name64:    "statfsx64",
	altname64: "__statfsx64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_LARGEFILE64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef statfsx64
#ifndef __x86_64__
#define statfsx64 __statfsx64
#else /* !__x86_64__ */
#include <features.h>
#define __OFFSET_STATFS_TYPE      __OFFSET_STATFSX64_TYPE
#define __OFFSET_STATFS_BSIZE     __OFFSET_STATFSX64_BSIZE
#define __OFFSET_STATFS_BLOCKS    __OFFSET_STATFSX64_BLOCKS
#define __OFFSET_STATFS_BFREE     __OFFSET_STATFSX64_BFREE
#define __OFFSET_STATFS_BAVAIL    __OFFSET_STATFSX64_BAVAIL
#define __OFFSET_STATFS_FILES     __OFFSET_STATFSX64_FILES
#define __OFFSET_STATFS_FFREE     __OFFSET_STATFSX64_FFREE
#define __OFFSET_STATFS_FSID      __OFFSET_STATFSX64_FSID
#define __OFFSET_STATFS_NAMELEN   __OFFSET_STATFSX64_NAMELEN
#define __OFFSET_STATFS_FRSIZE    __OFFSET_STATFSX64_FRSIZE
#define __OFFSET_STATFS_FLAGS     __OFFSET_STATFSX64_FLAGS
#define __OFFSET_STATFS_SPARE     __OFFSET_STATFSX64_SPARE
#define __SIZEOF_STATFS           __SIZEOF_STATFSX64
#define __ALIGNOF_STATFS          __ALIGNOF_STATFSX64
#define __OFFSET_STATFS32_TYPE    __OFFSET_STATFSX64_TYPE
#define __OFFSET_STATFS32_BSIZE   __OFFSET_STATFSX64_BSIZE
#define __OFFSET_STATFS32_BLOCKS  __OFFSET_STATFSX64_BLOCKS
#define __OFFSET_STATFS32_BFREE   __OFFSET_STATFSX64_BFREE
#define __OFFSET_STATFS32_BAVAIL  __OFFSET_STATFSX64_BAVAIL
#define __OFFSET_STATFS32_FILES   __OFFSET_STATFSX64_FILES
#define __OFFSET_STATFS32_FFREE   __OFFSET_STATFSX64_FFREE
#define __OFFSET_STATFS32_FSID    __OFFSET_STATFSX64_FSID
#define __OFFSET_STATFS32_NAMELEN __OFFSET_STATFSX64_NAMELEN
#define __OFFSET_STATFS32_FRSIZE  __OFFSET_STATFSX64_FRSIZE
#define __OFFSET_STATFS32_FLAGS   __OFFSET_STATFSX64_FLAGS
#define __OFFSET_STATFS32_SPARE   __OFFSET_STATFSX64_SPARE
#define __SIZEOF_STATFS32         __SIZEOF_STATFSX64
#define __ALIGNOF_STATFS32        __ALIGNOF_STATFSX64
#define __OFFSET_STATFS64_TYPE    __OFFSET_STATFSX64_TYPE
#define __OFFSET_STATFS64_BSIZE   __OFFSET_STATFSX64_BSIZE
#define __OFFSET_STATFS64_BLOCKS  __OFFSET_STATFSX64_BLOCKS
#define __OFFSET_STATFS64_BFREE   __OFFSET_STATFSX64_BFREE
#define __OFFSET_STATFS64_BAVAIL  __OFFSET_STATFSX64_BAVAIL
#define __OFFSET_STATFS64_FILES   __OFFSET_STATFSX64_FILES
#define __OFFSET_STATFS64_FFREE   __OFFSET_STATFSX64_FFREE
#define __OFFSET_STATFS64_FSID    __OFFSET_STATFSX64_FSID
#define __OFFSET_STATFS64_NAMELEN __OFFSET_STATFSX64_NAMELEN
#define __OFFSET_STATFS64_FRSIZE  __OFFSET_STATFSX64_FRSIZE
#define __OFFSET_STATFS64_FLAGS   __OFFSET_STATFSX64_FLAGS
#define __OFFSET_STATFS64_SPARE   __OFFSET_STATFSX64_SPARE
#define __SIZEOF_STATFS64         __SIZEOF_STATFSX64
#define __ALIGNOF_STATFS64        __ALIGNOF_STATFSX64
#define statfsx64                 statfs
#define __statfsx64               statfs
#define __statfs32                statfs
#define __statfs_alt              statfs
#define _STATFS_MATCHES_STATFS64 1
#ifdef __USE_KOS
#define statfs32 statfs
#endif /* __USE_KOS */
#ifdef __USE_LARGEFILE64
#ifdef __USE_STRUCT64_MACRO
#define statfs64   statfs
#define __statfs64 statfs
#else /* __USE_STRUCT64_MACRO */
#define __statfsx64_alt statfs64
#define __statfs64      statfs64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_LARGEFILE64 */
#define __statfs64 statfs
#endif /* !__USE_LARGEFILE64 */
#define __statfs_defined
#endif /* __x86_64__ */
/*[[[end]]]*/


#define __OFFSET_STATFSX64_TYPE     0
#define __OFFSET_STATFSX64_BSIZE    8
#define __OFFSET_STATFSX64_BLOCKS   16
#define __OFFSET_STATFSX64_BFREE    24
#define __OFFSET_STATFSX64_BAVAIL   32
#define __OFFSET_STATFSX64_FILES    40
#define __OFFSET_STATFSX64_FFREE    48
#define __OFFSET_STATFSX64_FSID     56
#define __OFFSET_STATFSX64_NAMELEN  64
#define __OFFSET_STATFSX64_FRSIZE   72
#define __OFFSET_STATFSX64_FLAGS    80
#define __OFFSET_STATFSX64_SPARE    88
#define __SIZEOF_STATFSX64          120
#define __ALIGNOF_STATFSX64         __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN

struct statfsx64 /*[PREFIX(f_)]*/ {
	__ULONG64_TYPE__ f_type;     /* Type of file system (one of the constants from <linux/magic.h>) */
	__ULONG64_TYPE__ f_bsize;    /* Optimal transfer block size */
	__ULONG64_TYPE__ f_blocks;   /* Total data blocks in file system */
	__ULONG64_TYPE__ f_bfree;    /* Free blocks in fs */
	__ULONG64_TYPE__ f_bavail;   /* Free blocks available to unprivileged user */
	__ULONG64_TYPE__ f_files;    /* Total file nodes in file system */
	__ULONG64_TYPE__ f_ffree;    /* Free file nodes in fs */
	__fsid_t         f_fsid;     /* File system id */
	__ULONG64_TYPE__ f_namelen;  /* Maximum length of filenames */
	__ULONG64_TYPE__ f_frsize;   /* Fragment size (since Linux 2.6) */
	__ULONG64_TYPE__ f_flags;    /* Mount flags (set of `ST_*' from <sys/statvfs.h>) */
	__ULONG64_TYPE__ f_spare[4]; /* ??? */
};

#ifdef __statfsx64_alt
struct __statfsx64_alt {
	__ULONG64_TYPE__ f_type;     /* Type of file system (one of the constants from <linux/magic.h>) */
	__ULONG64_TYPE__ f_bsize;    /* Optimal transfer block size */
	__ULONG64_TYPE__ f_blocks;   /* Total data blocks in file system */
	__ULONG64_TYPE__ f_bfree;    /* Free blocks in fs */
	__ULONG64_TYPE__ f_bavail;   /* Free blocks available to unprivileged user */
	__ULONG64_TYPE__ f_files;    /* Total file nodes in file system */
	__ULONG64_TYPE__ f_ffree;    /* Free file nodes in fs */
	__fsid_t         f_fsid;     /* File system id */
	__ULONG64_TYPE__ f_namelen;  /* Maximum length of filenames */
	__ULONG64_TYPE__ f_frsize;   /* Fragment size (since Linux 2.6) */
	__ULONG64_TYPE__ f_flags;    /* Mount flags (set of `ST_*' from <sys/statvfs.h>) */
	__ULONG64_TYPE__ f_spare[4]; /* ??? */
};
#undef __statfsx64_alt
#endif /* __statfsx64_alt */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef statfsx64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_STATFSX64
#undef __PRIVATE_DID_PUSH_STATFSX64
#pragma pop_macro("statfsx64")
#endif /* __PRIVATE_DID_PUSH_STATFSX64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_KOS_STATFS64_H */
