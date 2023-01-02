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
#ifndef _I386_KOS_BITS_OS_KOS_STATFS_CONVERT_H
#define _I386_KOS_BITS_OS_KOS_STATFS_CONVERT_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>

#include "statfs32.h"
#include "statfs64.h"

#ifdef __CC__
__DECL_BEGIN

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(statfsx32_to_statfsx32_64)(struct __statfsx32 const *__restrict __self,
                                         struct __statfsx32_64 *__restrict __result) {
	__result->f_type    = (__ULONG32_TYPE__)__self->f_type;
	__result->f_bsize   = (__ULONG32_TYPE__)__self->f_bsize;
	__result->f_blocks  = (__ULONG64_TYPE__)__self->f_blocks;
	__result->f_bfree   = (__ULONG64_TYPE__)__self->f_bfree;
	__result->f_bavail  = (__ULONG64_TYPE__)__self->f_bavail;
	__result->f_files   = (__ULONG64_TYPE__)__self->f_files;
	__result->f_ffree   = (__ULONG64_TYPE__)__self->f_ffree;
	__result->f_fsid    = __self->f_fsid;
	__result->f_namelen = (__ULONG32_TYPE__)__self->f_namelen;
	__result->f_frsize  = (__ULONG32_TYPE__)__self->f_frsize;
	__result->f_flags   = (__ULONG32_TYPE__)__self->f_flags;
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(statfsx32_64_to_statfsx32)(struct __statfsx32_64 const *__restrict __self,
                                         struct __statfsx32 *__restrict __result) {
	__result->f_type    = (__ULONG32_TYPE__)__self->f_type;
	__result->f_bsize   = (__ULONG32_TYPE__)__self->f_bsize;
	__result->f_blocks  = (__ULONG32_TYPE__)__self->f_blocks;
	__result->f_bfree   = (__ULONG32_TYPE__)__self->f_bfree;
	__result->f_bavail  = (__ULONG32_TYPE__)__self->f_bavail;
	__result->f_files   = (__ULONG32_TYPE__)__self->f_files;
	__result->f_ffree   = (__ULONG32_TYPE__)__self->f_ffree;
	__result->f_fsid    = __self->f_fsid;
	__result->f_namelen = (__ULONG32_TYPE__)__self->f_namelen;
	__result->f_frsize  = (__ULONG32_TYPE__)__self->f_frsize;
	__result->f_flags   = (__ULONG32_TYPE__)__self->f_flags;
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(statfsx32_to_statfsx64)(struct __statfsx32 const *__restrict __self,
                                      struct __statfsx64 *__restrict __result) {
	__result->f_type    = (__ULONG64_TYPE__)__self->f_type;
	__result->f_bsize   = (__ULONG64_TYPE__)__self->f_bsize;
	__result->f_blocks  = (__ULONG64_TYPE__)__self->f_blocks;
	__result->f_bfree   = (__ULONG64_TYPE__)__self->f_bfree;
	__result->f_bavail  = (__ULONG64_TYPE__)__self->f_bavail;
	__result->f_files   = (__ULONG64_TYPE__)__self->f_files;
	__result->f_ffree   = (__ULONG64_TYPE__)__self->f_ffree;
	__result->f_fsid    = __self->f_fsid;
	__result->f_namelen = (__ULONG64_TYPE__)__self->f_namelen;
	__result->f_frsize  = (__ULONG64_TYPE__)__self->f_frsize;
	__result->f_flags   = (__ULONG64_TYPE__)__self->f_flags;
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(statfsx32_64_to_statfsx64)(struct __statfsx32_64 const *__restrict __self,
                                         struct __statfsx64 *__restrict __result) {
	__result->f_type    = (__ULONG64_TYPE__)__self->f_type;
	__result->f_bsize   = (__ULONG64_TYPE__)__self->f_bsize;
	__result->f_blocks  = (__ULONG64_TYPE__)__self->f_blocks;
	__result->f_bfree   = (__ULONG64_TYPE__)__self->f_bfree;
	__result->f_bavail  = (__ULONG64_TYPE__)__self->f_bavail;
	__result->f_files   = (__ULONG64_TYPE__)__self->f_files;
	__result->f_ffree   = (__ULONG64_TYPE__)__self->f_ffree;
	__result->f_fsid    = __self->f_fsid;
	__result->f_namelen = (__ULONG64_TYPE__)__self->f_namelen;
	__result->f_frsize  = (__ULONG64_TYPE__)__self->f_frsize;
	__result->f_flags   = (__ULONG64_TYPE__)__self->f_flags;
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(statfsx64_to_statfsx32)(struct __statfsx64 const *__restrict __self,
                                      struct __statfsx32 *__restrict __result) {
	__result->f_type    = (__ULONG32_TYPE__)__self->f_type;
	__result->f_bsize   = (__ULONG32_TYPE__)__self->f_bsize;
	__result->f_blocks  = (__ULONG32_TYPE__)__self->f_blocks;
	__result->f_bfree   = (__ULONG32_TYPE__)__self->f_bfree;
	__result->f_bavail  = (__ULONG32_TYPE__)__self->f_bavail;
	__result->f_files   = (__ULONG32_TYPE__)__self->f_files;
	__result->f_ffree   = (__ULONG32_TYPE__)__self->f_ffree;
	__result->f_fsid    = __self->f_fsid;
	__result->f_namelen = (__ULONG32_TYPE__)__self->f_namelen;
	__result->f_frsize  = (__ULONG32_TYPE__)__self->f_frsize;
	__result->f_flags   = (__ULONG32_TYPE__)__self->f_flags;
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(statfsx64_to_statfsx32_64)(struct __statfsx64 const *__restrict __self,
                                         struct __statfsx32_64 *__restrict __result) {
	__result->f_type    = (__ULONG32_TYPE__)__self->f_type;
	__result->f_bsize   = (__ULONG32_TYPE__)__self->f_bsize;
	__result->f_blocks  = (__ULONG64_TYPE__)__self->f_blocks;
	__result->f_bfree   = (__ULONG64_TYPE__)__self->f_bfree;
	__result->f_bavail  = (__ULONG64_TYPE__)__self->f_bavail;
	__result->f_files   = (__ULONG64_TYPE__)__self->f_files;
	__result->f_ffree   = (__ULONG64_TYPE__)__self->f_ffree;
	__result->f_fsid    = __self->f_fsid;
	__result->f_namelen = (__ULONG32_TYPE__)__self->f_namelen;
	__result->f_frsize  = (__ULONG32_TYPE__)__self->f_frsize;
	__result->f_flags   = (__ULONG32_TYPE__)__self->f_flags;
}


#ifdef __x86_64__
#define statfsx32_to_statfs                 statfsx32_to_statfsx64
#define statfsx32_to_statfs32               statfsx32_to_statfsx64
#define statfsx32_to_statfs64               statfsx32_to_statfsx64
#define statfsx32_64_to_statfs              statfsx32_64_to_statfsx64
#define statfsx32_64_to_statfs32            statfsx32_64_to_statfsx64
#define statfsx32_64_to_statfs64            statfsx32_64_to_statfsx64
#define statfsx64_to_statfs(self, result)   (void)(*(result) = *(self))
#define statfsx64_to_statfs32(self, result) (void)(*(result) = *(self))
#define statfsx64_to_statfs64(self, result) (void)(*(result) = *(self))
#define statfs_to_statfsx32                 statfsx64_to_statfsx32
#define statfs32_to_statfsx32               statfsx64_to_statfsx32
#define statfs64_to_statfsx32               statfsx64_to_statfsx32
#define statfs_to_statfsx32_64              statfsx64_to_statfsx32_64
#define statfs32_to_statfsx32_64            statfsx64_to_statfsx32_64
#define statfs64_to_statfsx32_64            statfsx64_to_statfsx32_64
#define statfs_to_statfsx64(self, result)   (void)(*(result) = *(self))
#define statfs32_to_statfsx64(self, result) (void)(*(result) = *(self))
#define statfs64_to_statfsx64(self, result) (void)(*(result) = *(self))
#define statfs_to_statfs32(self, result)    (void)(*(result) = *(self))
#define statfs_to_statfs64(self, result)    (void)(*(result) = *(self))
#define statfs32_to_statfs(self, result)    (void)(*(result) = *(self))
#define statfs64_to_statfs(self, result)    (void)(*(result) = *(self))
#define statfs32_to_statfs64(self, result)  (void)(*(result) = *(self))
#define statfs64_to_statfs32(self, result)  (void)(*(result) = *(self))
#else /* __x86_64__ */
#define statfsx32_to_statfs32(self, result)    (void)(*(result) = *(self))
#define statfsx32_to_statfs64                  statfsx32_to_statfsx32_64
#define statfsx32_64_to_statfs32               statfsx32_64_to_statfsx32
#define statfsx32_64_to_statfs64(self, result) (void)(*(result) = *(self))
#define statfsx64_to_statfs32                  statfsx64_to_statfsx32
#define statfsx64_to_statfs64                  statfsx64_to_statfsx32_64
#define statfs32_to_statfsx32(self, result)    (void)(*(result) = *(self))
#define statfs64_to_statfsx32                  statfsx32_64_to_statfsx32
#define statfs32_to_statfsx32_64               statfsx32_to_statfsx32_64
#define statfs64_to_statfsx32_64(self, result) (void)(*(result) = *(self))
#define statfs32_to_statfsx64                  statfsx32_to_statfsx64
#define statfs64_to_statfsx64                  statfsx32_64_to_statfsx64
#define statfs32_to_statfs64                   statfsx32_to_statfsx32_64
#define statfs64_to_statfs32                   statfsx32_64_to_statfsx32
#ifdef __USE_FILE_OFFSET64
#define statfsx32_to_statfs              statfsx32_to_statfs64
#define statfsx32_64_to_statfs           statfsx32_64_to_statfs64
#define statfsx64_to_statfs              statfsx64_to_statfs64
#define statfs_to_statfsx32              statfs64_to_statfsx32
#define statfs_to_statfsx32_64           statfs64_to_statfsx32_64
#define statfs_to_statfsx64              statfs64_to_statfsx64
#define statfs_to_statfs32               statfs64_to_statfs32
#define statfs_to_statfs64(self, result) (void)(*(result) = *(self))
#define statfs32_to_statfs               statfs32_to_statfs64
#define statfs64_to_statfs(self, result) (void)(*(result) = *(self))
#else /* __USE_FILE_OFFSET64 */
#define statfsx32_to_statfs              statfsx32_to_statfs32
#define statfsx32_64_to_statfs           statfsx32_64_to_statfs32
#define statfsx64_to_statfs              statfsx64_to_statfs32
#define statfs_to_statfsx32              statfs32_to_statfsx32
#define statfs_to_statfsx32_64           statfs32_to_statfsx32_64
#define statfs_to_statfsx64              statfs32_to_statfsx64
#define statfs_to_statfs32(self, result) (void)(*(result) = *(self))
#define statfs_to_statfs64               statfs32_to_statfs64
#define statfs32_to_statfs(self, result) (void)(*(result) = *(self))
#define statfs64_to_statfs               statfs64_to_statfs32
#endif /* !__USE_FILE_OFFSET64 */
#endif /* !__x86_64__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_BITS_OS_KOS_STATFS_CONVERT_H */
