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
#ifndef _I386_KOS_BITS_STAT_KOS_CONVERT_H
#define _I386_KOS_BITS_STAT_KOS_CONVERT_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include "stat-kos32.h"
#include "stat-kos64.h"

#ifdef __CC__
__DECL_BEGIN

#if defined(__KERNEL__) && defined(__KOS__)
#define __STATX32_FIELD64(name) name
#elif defined(__USE_FILE_OFFSET64) && defined(__USE_KOS)
#define __STATX32_FIELD64(name) name##64
#elif defined(__USE_FILE_OFFSET64)
#define __STATX32_FIELD64(name) name
#elif defined(__USE_KOS)
#define __STATX32_FIELD64(name) name##64
#else
#define __STATX32_FIELD64(name) __##name##64
#endif

#if defined(__KERNEL__) && defined(__KOS__)
#define __STATX32_TMFIELD64(name) name
#elif defined(__USE_TIME_BITS64)
#define __STATX32_TMFIELD64(name) name
#elif defined(__USE_KOS)
#define __STATX32_TMFIELD64(name) name##64
#else
#define __STATX32_TMFIELD64(name) __##name##64
#endif

#if defined(__KERNEL__) && defined(__KOS__)
#define __STATX32_TMFIELD32(name) __##name##32
#elif !defined(__USE_TIME_BITS64)
#define __STATX32_TMFIELD32(name) name
#elif defined(__USE_KOS)
#define __STATX32_TMFIELD32(name) name##32
#else
#define __STATX32_TMFIELD32(name) __##name##32
#endif

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(kos_statx32_to_kos_statx64)(struct __kos_statx32 const *__restrict __self,
                                          struct __kos_statx64 *__restrict __result) {
	__result->st_dev       = __self->st_dev;
	__result->st_ino       = __self->__STATX32_FIELD64(st_ino);
	__result->st_mode      = __self->st_mode;
	__result->st_nlink     = __self->st_nlink;
	__result->st_uid       = __self->st_uid;
	__result->st_gid       = __self->st_gid;
	__result->st_rdev      = __self->st_rdev;
	__result->st_size      = __self->__STATX32_FIELD64(st_size);
	__result->st_blksize   = (__UINT64_TYPE__)__self->st_blksize;
	__result->st_blocks    = __self->__STATX32_FIELD64(st_blocks);
	__result->st_atime     = __self->__STATX32_TMFIELD64(st_atime);
	__result->st_atimensec = (__UINT64_TYPE__)__self->__STATX32_TMFIELD64(st_atimensec);
	__result->st_mtime     = __self->__STATX32_TMFIELD64(st_mtime);
	__result->st_mtimensec = (__UINT64_TYPE__)__self->__STATX32_TMFIELD64(st_mtimensec);
	__result->st_ctime     = __self->__STATX32_TMFIELD64(st_ctime);
	__result->st_ctimensec = (__UINT64_TYPE__)__self->__STATX32_TMFIELD64(st_ctimensec);
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(kos_statx64_to_kos_statx32)(struct __kos_statx64 const *__restrict __self,
                                          struct __kos_statx32 *__restrict __result) {
	__result->st_dev                                    = __self->st_dev;
	__result->__STATX32_FIELD64(st_ino)                 = __self->st_ino;
	__result->st_mode                                   = __self->st_mode;
	__result->st_nlink                                  = __self->st_nlink;
	__result->st_uid                                    = __self->st_uid;
	__result->st_gid                                    = __self->st_gid;
	__result->st_rdev                                   = __self->st_rdev;
	__result->__STATX32_FIELD64(st_size)                = __self->st_size;
	__result->st_blksize                                = (__UINT32_TYPE__)__self->st_blksize;
	__result->__STATX32_FIELD64(st_blocks)              = __self->st_blocks;
	__result->__STATX32_TMFIELD32(st_atimespec).tv_sec  = (__INT32_TYPE__)__self->st_atime;
	__result->__STATX32_TMFIELD32(st_atimespec).tv_nsec = (__UINT32_TYPE__)__self->st_atimensec;
	__result->__STATX32_TMFIELD32(st_mtimespec).tv_sec  = (__INT32_TYPE__)__self->st_mtime;
	__result->__STATX32_TMFIELD32(st_mtimespec).tv_nsec = (__UINT32_TYPE__)__self->st_mtimensec;
	__result->__STATX32_TMFIELD32(st_ctimespec).tv_sec  = (__INT32_TYPE__)__self->st_ctime;
	__result->__STATX32_TMFIELD32(st_ctimespec).tv_nsec = (__UINT32_TYPE__)__self->st_ctimensec;
	__result->__STATX32_TMFIELD64(st_atime)             = __self->st_atime;
	__result->__STATX32_TMFIELD64(st_atimensec)         = (__UINT32_TYPE__)__self->st_atimensec;
	__result->__STATX32_TMFIELD64(st_mtime)             = __self->st_mtime;
	__result->__STATX32_TMFIELD64(st_mtimensec)         = (__UINT32_TYPE__)__self->st_mtimensec;
	__result->__STATX32_TMFIELD64(st_ctime)             = __self->st_ctime;
	__result->__STATX32_TMFIELD64(st_ctimensec)         = (__UINT32_TYPE__)__self->st_ctimensec;
}

#undef __STATX32_FIELD64
#undef __STATX32_TMFIELD32
#undef __STATX32_TMFIELD64

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_BITS_STAT_KOS_CONVERT_H */
