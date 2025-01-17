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
#ifndef _BITS_OS_KOS_STATFS_CONVERT_H
#define _BITS_OS_KOS_STATFS_CONVERT_H 1

#include <__stdinc.h>
#include <features.h>

#include "statfs.h"

#ifdef __CC__
__DECL_BEGIN

#ifdef _STATFS_MATCHES_STATFS64
#ifdef __USE_KOS
#define statfs32_to_statfs64(self, result) (void)(*(result) = *(result))
#define statfs64_to_statfs32(self, result) (void)(*(result) = *(result))
#else /* __USE_KOS */
#define statfs32_to_statfs64(self, result) (void)(*(struct statfs *)(result) = *(struct statfs *)(result))
#define statfs64_to_statfs32(self, result) (void)(*(struct statfs *)(result) = *(struct statfs *)(result))
#endif /* !__USE_KOS */
#else /* _STATFS_MATCHES_STATFS64 */
__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(statfs32_to_statfs64)(struct __statfs32 const *__restrict __self,
                                    struct __statfs64 *__restrict __result) {
	__result->f_type    = __self->f_type;
	__result->f_bsize   = __self->f_bsize;
	__result->f_blocks  = (__fsblkcnt64_t)__self->f_blocks;
	__result->f_bfree   = (__fsblkcnt64_t)__self->f_bfree;
	__result->f_bavail  = (__fsblkcnt64_t)__self->f_bavail;
	__result->f_files   = (__fsfilcnt64_t)__self->f_files;
	__result->f_ffree   = (__fsfilcnt64_t)__self->f_ffree;
	__result->f_fsid    = __self->f_fsid;
#ifdef _STATFS_F_NAMELEN
	__result->f_namelen = __self->f_namelen;
#endif /* _STATFS_F_NAMELEN */
#ifdef _STATFS_F_FRSIZE
	__result->f_frsize = __self->f_frsize;
#endif /* _STATFS_F_FRSIZE */
#ifdef _STATFS_F_FLAGS
	__result->f_flags = __self->f_flags;
#endif /* _STATFS_F_FLAGS */
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(statfs64_to_statfs32)(struct __statfs64 const *__restrict __self,
                                    struct __statfs32 *__restrict __result) {
	__result->f_type    = __self->f_type;
	__result->f_bsize   = __self->f_bsize;
	__result->f_blocks  = (__fsblkcnt32_t)__self->f_blocks;
	__result->f_bfree   = (__fsblkcnt32_t)__self->f_bfree;
	__result->f_bavail  = (__fsblkcnt32_t)__self->f_bavail;
	__result->f_files   = (__fsfilcnt32_t)__self->f_files;
	__result->f_ffree   = (__fsfilcnt32_t)__self->f_ffree;
	__result->f_fsid    = __self->f_fsid;
#ifdef _STATFS_F_NAMELEN
	__result->f_namelen = __self->f_namelen;
#endif /* _STATFS_F_NAMELEN */
#ifdef _STATFS_F_FRSIZE
	__result->f_frsize = __self->f_frsize;
#endif /* _STATFS_F_FRSIZE */
#ifdef _STATFS_F_FLAGS
	__result->f_flags = __self->f_flags;
#endif /* _STATFS_F_FLAGS */
}
#endif /* !_STATFS_MATCHES_STATFS64 */

#ifdef __USE_FILE_OFFSET64
#define statfs_to_statfs32               statfs64_to_statfs32
#define statfs_to_statfs64(self, result) (void)(*(result) = *(self))
#define statfs32_to_statfs               statfs32_to_statfs64
#define statfs64_to_statfs(self, result) (void)(*(result) = *(self))
#else /* __USE_FILE_OFFSET64 */
#define statfs_to_statfs32(self, result) (void)(*(result) = *(self))
#define statfs_to_statfs64               statfs32_to_statfs64
#define statfs32_to_statfs(self, result) (void)(*(result) = *(self))
#define statfs64_to_statfs               statfs64_to_statfs32
#endif /* !__USE_FILE_OFFSET64 */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_STATFS_CONVERT_H */
