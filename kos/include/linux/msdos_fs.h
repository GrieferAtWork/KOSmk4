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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LINUX_MSDOS_FS_H
#define _LINUX_MSDOS_FS_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>
#include <linux/types.h>
#include <asm/ioctl.h>

__DECL_BEGIN

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("d_ino")
#pragma push_macro("d_off")
#pragma push_macro("d_reclen")
#pragma push_macro("d_name")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#undef d_ino
#undef d_off
#undef d_reclen
#undef d_name
struct __fat_dirent {
	__LONGPTR_TYPE__ d_ino;
	__LONGPTR_TYPE__ d_off;
	__UINT16_TYPE__  d_reclen;
	char             d_name[256];
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("d_name")
#pragma pop_macro("d_reclen")
#pragma pop_macro("d_off")
#pragma pop_macro("d_ino")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

#ifndef __KERNEL__
#define ATTR_NONE   0  /* no attribute bits */
#define ATTR_RO     1  /* read-only */
#define ATTR_HIDDEN 2  /* hidden */
#define ATTR_SYS    4  /* system */
#define ATTR_VOLUME 8  /* volume label */
#define ATTR_DIR    16 /* directory */
#define ATTR_ARCH   32 /* archived */
#endif

/* ioctl commands */
#define VFAT_IOCTL_READDIR_BOTH  _IOR('r', 1, struct __fat_dirent[2])
#define VFAT_IOCTL_READDIR_SHORT _IOR('r', 2, struct __fat_dirent[2])
#define FAT_IOCTL_GET_ATTRIBUTES _IOR('r', 0x10, __u32)
#define FAT_IOCTL_SET_ATTRIBUTES _IOW('r', 0x11, __u32)
#define FAT_IOCTL_GET_VOLUME_ID  _IOR('r', 0x13, __u32)

__DECL_END


#endif /* _LINUX_MSDOS_FS_H */
