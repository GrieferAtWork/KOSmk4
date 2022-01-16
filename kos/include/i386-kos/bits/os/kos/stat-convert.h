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
#ifndef _I386_KOS_BITS_OS_KOS_STAT_CONVERT_H
#define _I386_KOS_BITS_OS_KOS_STAT_CONVERT_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include "stat32.h"
#include "stat64.h"

#ifdef __CC__
__DECL_BEGIN

#define __PRIVATE_SETFIELD(ResultType, resultOffset, SelfType, selfOffset) \
	*(ResultType *)((__BYTE_TYPE__ *)__result + resultOffset) =            \
	*(SelfType *)((__BYTE_TYPE__ *)__self + selfOffset)

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(kos_statx32_to_kos_statx64)(struct __kos_statx32 const *__restrict __self,
                                          struct __kos_statx64 *__restrict __result) {
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX64_DEV, __UINT64_TYPE__, __OFFSET_KOS_STATX32_DEV);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX64_INO, __UINT64_TYPE__, __OFFSET_KOS_STATX32_INO);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX64_MODE, __UINT32_TYPE__, __OFFSET_KOS_STATX32_MODE);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX64_NLINK, __UINT32_TYPE__, __OFFSET_KOS_STATX32_NLINK);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX64_UID, __UINT32_TYPE__, __OFFSET_KOS_STATX32_UID);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX64_GID, __UINT32_TYPE__, __OFFSET_KOS_STATX32_GID);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX64_RDEV, __UINT64_TYPE__, __OFFSET_KOS_STATX32_RDEV);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX64_SIZE, __UINT64_TYPE__, __OFFSET_KOS_STATX32_SIZE);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX64_BLKSIZE, __UINT64_TYPE__, __OFFSET_KOS_STATX32_BLKSIZE);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX64_BLOCKS, __UINT64_TYPE__, __OFFSET_KOS_STATX32_BLOCKS);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX64_ATIME, __UINT64_TYPE__, __OFFSET_KOS_STATX32_ATIME64);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX64_ATIMENSEC, __UINT32_TYPE__, __OFFSET_KOS_STATX32_ATIMENSEC64);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX64_MTIME, __UINT64_TYPE__, __OFFSET_KOS_STATX32_MTIME64);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX64_MTIMENSEC, __UINT32_TYPE__, __OFFSET_KOS_STATX32_MTIMENSEC64);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX64_CTIME, __UINT64_TYPE__, __OFFSET_KOS_STATX32_CTIME64);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX64_CTIMENSEC, __UINT32_TYPE__, __OFFSET_KOS_STATX32_CTIMENSEC64);
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(kos_statx64_to_kos_statx32)(struct __kos_statx64 const *__restrict __self,
                                          struct __kos_statx32 *__restrict __result) {
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX32_DEV, __UINT64_TYPE__, __OFFSET_KOS_STATX64_DEV);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX32_INO, __UINT64_TYPE__, __OFFSET_KOS_STATX64_INO);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX32_MODE, __UINT32_TYPE__, __OFFSET_KOS_STATX64_MODE);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX32_NLINK, __UINT32_TYPE__, __OFFSET_KOS_STATX64_NLINK);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX32_UID, __UINT32_TYPE__, __OFFSET_KOS_STATX64_UID);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX32_GID, __UINT32_TYPE__, __OFFSET_KOS_STATX64_GID);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX32_RDEV, __UINT64_TYPE__, __OFFSET_KOS_STATX64_RDEV);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX32_SIZE, __UINT64_TYPE__, __OFFSET_KOS_STATX64_SIZE);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX32_BLKSIZE, __UINT64_TYPE__, __OFFSET_KOS_STATX64_BLKSIZE);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX32_BLOCKS, __UINT64_TYPE__, __OFFSET_KOS_STATX64_BLOCKS);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX32_ATIME32, __UINT64_TYPE__, __OFFSET_KOS_STATX64_ATIME);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX32_ATIMENSEC32, __UINT64_TYPE__, __OFFSET_KOS_STATX64_ATIMENSEC);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX32_MTIME32, __UINT64_TYPE__, __OFFSET_KOS_STATX64_MTIME);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX32_MTIMENSEC32, __UINT64_TYPE__, __OFFSET_KOS_STATX64_MTIMENSEC);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX32_CTIME32, __UINT64_TYPE__, __OFFSET_KOS_STATX64_CTIME);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX32_CTIMENSEC32, __UINT64_TYPE__, __OFFSET_KOS_STATX64_CTIMENSEC);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX32_ATIME64, __UINT64_TYPE__, __OFFSET_KOS_STATX64_ATIME);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX32_ATIMENSEC64, __UINT64_TYPE__, __OFFSET_KOS_STATX64_ATIMENSEC);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX32_MTIME64, __UINT64_TYPE__, __OFFSET_KOS_STATX64_MTIME);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX32_MTIMENSEC64, __UINT64_TYPE__, __OFFSET_KOS_STATX64_MTIMENSEC);
	__PRIVATE_SETFIELD(__UINT64_TYPE__, __OFFSET_KOS_STATX32_CTIME64, __UINT64_TYPE__, __OFFSET_KOS_STATX64_CTIME);
	__PRIVATE_SETFIELD(__UINT32_TYPE__, __OFFSET_KOS_STATX32_CTIMENSEC64, __UINT64_TYPE__, __OFFSET_KOS_STATX64_CTIMENSEC);
}
#undef __PRIVATE_SETFIELD

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_BITS_OS_KOS_STAT_CONVERT_H */
