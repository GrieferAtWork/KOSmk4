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
/* (#) Portability: Linux (/usr/include/linux/magic.h) */
#ifndef _LINUX_MAGIC_H
#define _LINUX_MAGIC_H 1

#include <__stdinc.h>

#define AFS_SUPER_MAGIC        0x5346414f
#define AUTOFS_SUPER_MAGIC     0x00000187
#define CRAMFS_MAGIC_WEND      0x453dcd28
#define DEBUGFS_MAGIC          0x64626720
#define SYSFS_MAGIC            0x62656572
#define SECURITYFS_MAGIC       0x73636673
#define SELINUX_MAGIC          0xf97cff8c
#define RAMFS_MAGIC            0x858458f6 /* some random number */
#define SQUASHFS_MAGIC         0x73717368
#define XENFS_SUPER_MAGIC      0xabba1974
#define BTRFS_SUPER_MAGIC      0x9123683e
#define ANON_INODE_FS_MAGIC    0x09041934
#define MINIX3_SUPER_MAGIC     0x00004d5a
#define CGROUP_SUPER_MAGIC     0x0027e0eb
#define FUTEXFS_SUPER_MAGIC    0x0bad1dea
#define INOTIFYFS_SUPER_MAGIC  0x2bad1dea
#define DEVPTS_SUPER_MAGIC     0x00001cd1
#define SOCKFS_MAGIC           0x534f434b
#define ADFS_SUPER_MAGIC       0x0000adf5
#define AFFS_SUPER_MAGIC       0x0000adff
#define BEFS_SUPER_MAGIC       0x42465331
#define BFS_MAGIC              0x1badface
#define CIFS_MAGIC_NUMBER      0xff534d42
#define CODA_SUPER_MAGIC       0x73757245
#define COH_SUPER_MAGIC        0x012ff7b7
#define CRAMFS_MAGIC           0x28cd3d45 /* some random number */
#define CRAMFS_MAGIC_WEND      0x453dcd28 /* magic number with the wrong endianess */
#define DEVFS_SUPER_MAGIC      0x00001373
#define EFS_SUPER_MAGIC        0x00414a53
#define EXT_SUPER_MAGIC        0x0000137d
#define EXT2_OLD_SUPER_MAGIC   0x0000ef51
#define EXT2_SUPER_MAGIC       0x0000ef53
#define EXT3_SUPER_MAGIC       0x0000ef53
#define EXT4_SUPER_MAGIC       0x0000ef53
#define HFS_SUPER_MAGIC        0x00004244
#define HPFS_SUPER_MAGIC       0xf995e849
#define HUGETLBFS_MAGIC        0x958458f6 /* some random number */
#define ISOFS_SUPER_MAGIC      0x00009660
#define JFFS2_SUPER_MAGIC      0x000072b6
#define JFS_SUPER_MAGIC        0x3153464a
#define MINIX_SUPER_MAGIC      0x0000137f /* original minix fs */
#define MINIX_SUPER_MAGIC2     0x0000138f /* minix fs, 30 char names */
#define MINIX2_SUPER_MAGIC     0x00002468 /* minix V2 fs */
#define MINIX2_SUPER_MAGIC2    0x00002478 /* minix V2 fs, 30 char names */
#define MINIX3_SUPER_MAGIC     0x00004d5a /* minix V3 fs */
#define MSDOS_SUPER_MAGIC      0x00004d44 /* MD */
#define NCP_SUPER_MAGIC        0x0000564c /* Guess, what 0x564c is :-) */
#define NFS_SUPER_MAGIC        0x00006969
#define NTFS_SB_MAGIC          0x5346544e
#define OPENPROM_SUPER_MAGIC   0x00009fa1
#define PROC_SUPER_MAGIC       0x00009fa0
#define QNX4_SUPER_MAGIC       0x0000002f /* qnx4 fs detection */
#define REISERFS_SUPER_MAGIC   0x52654973 /* used by gcc */
#define ROMFS_MAGIC            0x00007275
#define SMB_SUPER_MAGIC        0x0000517b
#define SYSV2_SUPER_MAGIC      0x012ff7b6
#define SYSV4_SUPER_MAGIC      0x012ff7b5
#define TMPFS_MAGIC            0x01021994
#define UDF_SUPER_MAGIC        0x15013346
#define UFS_MAGIC              0x00011954
#define USBDEVICE_SUPER_MAGIC  0x00009fa2
#define VXFS_SUPER_MAGIC       0xa501fcf5
#define XENIX_SUPER_MAGIC      0x012ff7b4
#define XFS_SUPER_MAGIC        0x58465342
#define _XIAFS_SUPER_MAGIC     0x012fd16d


/* <linux/magic.h> normally doesn't have constants for these, so we make our own... */
#ifdef __KOS__
#define TARFS_SUPER_MAGIC ('t' << 16 | 'a' << 8 | 'r')
#endif /* __KOS__ */

#endif /* !_LINUX_MAGIC_H */
