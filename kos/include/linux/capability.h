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
/* (#) Portability: Linux (/include/linux/capability.h) */
#ifndef _LINUX_CAPABILITY_H
#define _LINUX_CAPABILITY_H 1

#include <__stdinc.h>

#include <kos/capability.h> /* On KOS, this header defines CAP_* macros */
#include <linux/types.h>

/* Derived from (and binary-compatible with) the linux header of the same name. */
#define _LINUX_CAPABILITY_VERSION_1 0x19980330
#define _LINUX_CAPABILITY_U32S_1    1
#define _LINUX_CAPABILITY_VERSION_2 0x20071026
#define _LINUX_CAPABILITY_U32S_2    2
#define _LINUX_CAPABILITY_VERSION_3 0x20080522
#define _LINUX_CAPABILITY_U32S_3    2

#define _LINUX_CAPABILITY_VERSION _LINUX_CAPABILITY_VERSION_1
#define _LINUX_CAPABILITY_U32S    _LINUX_CAPABILITY_U32S_1

#define VFS_CAP_REVISION_MASK   0xff000000
#define VFS_CAP_REVISION_SHIFT  24
#define VFS_CAP_FLAGS_MASK      ~VFS_CAP_REVISION_MASK
#define VFS_CAP_FLAGS_EFFECTIVE 0x000001
#define VFS_CAP_REVISION_1      0x01000000
#define VFS_CAP_U32_1           1
#define XATTR_CAPS_SZ_1         (sizeof(__le32) * (1 + 2 * VFS_CAP_U32_1))
#define VFS_CAP_REVISION_2      0x02000000
#define VFS_CAP_U32_2           2
#define XATTR_CAPS_SZ_2         (sizeof(__le32) * (1 + 2 * VFS_CAP_U32_2))
#define VFS_CAP_REVISION_3      0x03000000
#define VFS_CAP_U32_3           2
#define XATTR_CAPS_SZ_3         (sizeof(__le32) * (2 + 2 * VFS_CAP_U32_3))
#define XATTR_CAPS_SZ           XATTR_CAPS_SZ_3
#define VFS_CAP_U32             VFS_CAP_U32_3
#define VFS_CAP_REVISION        VFS_CAP_REVISION_3


#ifdef __CC__
__DECL_BEGIN

struct __user_cap_header_struct {
	__u32 version;
	int pid;
};
struct __user_cap_data_struct {
	__u32 effective;
	__u32 permitted;
	__u32 inheritable;
};
typedef struct __user_cap_header_struct *cap_user_header_t;
typedef struct __user_cap_data_struct *cap_user_data_t;

struct vfs_cap_data {
	__le32 magic_etc;
	struct {
		__le32 permitted;
		__le32 inheritable;
	} data[VFS_CAP_U32];
};

struct vfs_ns_cap_data {
	__le32 magic_etc;
	struct {
		__le32 permitted;
		__le32 inheritable;
	} data[VFS_CAP_U32];
	__le32 rootid;
};

__DECL_END
#endif /* __CC__ */

#define cap_valid(x)    ((x) >= 0 && (x) <= CAP_LAST_CAP)
#define CAP_TO_INDEX(x) ((x) >> 5) /* NOTE: 5 == ffs(32), where 32 == NBBY*sizeof(u32) */
#define CAP_TO_MASK(x)  (1 << ((x)&31))

#endif /* _LINUX_CAPABILITY_H */
