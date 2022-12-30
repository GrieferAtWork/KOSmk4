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
/* (#) Portability: Linux (/usr/include/linux/msdos_fs.h) */
#ifndef _LINUX_MSDOS_FS_H
#define _LINUX_MSDOS_FS_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <asm/ioctl.h>
#include <bits/os/dirent.h> /* __DIRENT_HAVE_U_D_INO */
#include <linux/types.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("d_off")
#pragma push_macro("d_reclen")
#pragma push_macro("d_name")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#undef d_ino
#undef d_off
#undef d_reclen
#undef d_name
struct __fat_dirent {
#ifdef __USE_KOS_ALTERATIONS
#ifndef __DIRENT_HAVE_U_D_INO
	__ULONGPTR_TYPE__     d_ino;
#else /* !__DIRENT_HAVE_U_D_INO */
	union {
		__ULONGPTR_TYPE__ d_ino;
	} __u_d_ino;
#define d_ino __u_d_ino.d_ino
#endif /* __DIRENT_HAVE_U_D_INO */
	__ULONGPTR_TYPE__     d_off;
#else /* __USE_KOS_ALTERATIONS */
#ifndef __DIRENT_HAVE_U_D_INO
	__LONGPTR_TYPE__      d_ino;
#else /* !__DIRENT_HAVE_U_D_INO */
	union {
		__LONGPTR_TYPE__  d_ino;
	} __u_d_ino;
#define d_ino __u_d_ino.d_ino
#endif /* __DIRENT_HAVE_U_D_INO */
	__LONGPTR_TYPE__      d_off;
#endif /* !__USE_KOS_ALTERATIONS */
	__UINT16_TYPE__       d_reclen;
	char                  d_name[256];
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("d_name")
#pragma pop_macro("d_reclen")
#pragma pop_macro("d_off")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

/* File attribute flags for `struct fat_dirent::f_attr' */
#define FATATTR_NONE   0x00 /* no attribute bits */
#define FATATTR_RO     0x01 /* read-only */
#define FATATTR_HIDDEN 0x02 /* hidden */
#define FATATTR_SYS    0x04 /* system */
#define FATATTR_VOLUME 0x08 /* volume label */
#define FATATTR_DIR    0x10 /* directory */
#define FATATTR_ARCH   0x20 /* archived */
#ifdef __USE_KOS
#define FATATTR_LFN (FATATTR_RO | FATATTR_HIDDEN | FATATTR_SYS | FATATTR_VOLUME)
#endif /* __USE_KOS */

/* Don't intrude on the ATTR_* namespace when using pure system headers! */
#ifndef __USE_KOS_PURE
#define ATTR_NONE   FATATTR_NONE   /* no attribute bits */
#define ATTR_RO     FATATTR_RO     /* read-only */
#define ATTR_HIDDEN FATATTR_HIDDEN /* hidden */
#define ATTR_SYS    FATATTR_SYS    /* system */
#define ATTR_VOLUME FATATTR_VOLUME /* volume label */
#define ATTR_DIR    FATATTR_DIR    /* directory */
#define ATTR_ARCH   FATATTR_ARCH   /* archived */
#endif /* !__USE_KOS_PURE */

/* ioctl commands */
#define VFAT_IOCTL_READDIR_BOTH  _IOR('r', 1, struct __fat_dirent[2])
#define VFAT_IOCTL_READDIR_SHORT _IOR('r', 2, struct __fat_dirent[2])
#define FAT_IOCTL_GET_ATTRIBUTES _IOR('r', 0x10, __u32) /* Get set of `FATATTR_*' */
#define FAT_IOCTL_SET_ATTRIBUTES _IOW('r', 0x11, __u32) /* Set set of `FATATTR_*' */
#define FAT_IOCTL_GET_VOLUME_ID  _IOR('r', 0x13, __u32) /* Return volume ID of superblock (https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system#EBPB_OFS_1Ch) */


#endif /* _LINUX_MSDOS_FS_H */
