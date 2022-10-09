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
#ifndef GUARD_KERNEL_CORE_FILESYS_DEVFS_DISKRULES_C
#define GUARD_KERNEL_CORE_FILESYS_DEVFS_DISKRULES_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/blkdev.h>
#include <kernel/fs/devfs-disk.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/ramfs.h>

#include <hybrid/unaligned.h>

#include <ctype.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*
 * These special folders are documented here:
 * https://wiki.archlinux.org/title/Persistent_block_device_naming
 */


DECL_BEGIN

/************************************************************************/
/* /dev/disk/by-label                                                   */
/************************************************************************/
/* Enumerate block-devices based on `fsuper_getlabel()',
 * including for those where no superblock is mounted...
 *
 * Ooof... I feel like this rule is too complex to be done by the kernel
 *         core. - It  should probably be  implemented via a  designated
 *         driver! */
INTERN WUNUSED NONNULL((1, 2)) REF struct blkdev *KCALL
devdisk_label_byname(struct devdiskruledir *__restrict UNUSED(self),
                     struct flookup_info *__restrict info) {
	COMPILER_IMPURE();
	(void)info;
	return NULL;
}

INTERN WUNUSED NONNULL((1, 2, 4)) ssize_t KCALL
devdisk_label_toname(struct devdiskruledir *__restrict UNUSED(self),
                     __pformatprinter printer, void *arg,
                     struct blkdev *__restrict dev, uintptr_t variant) {
	COMPILER_IMPURE();
	(void)variant;
	(void)dev;
	(void)printer;
	(void)arg;
	return 0;
}
/************************************************************************/



/************************************************************************/
/* /dev/disk/by-uuid                                                    */
/************************************************************************/
/* List by filesystem-specific UUID (Ooof: see "/dev/disk/by-label" above...) */

INTERN WUNUSED NONNULL((1, 2)) REF struct blkdev *KCALL
devdisk_uuid_byname(struct devdiskruledir *__restrict UNUSED(self),
                    struct flookup_info *__restrict info) {
	COMPILER_IMPURE();
	(void)info;
	return NULL;
}

INTERN WUNUSED NONNULL((1, 2, 4)) ssize_t KCALL
devdisk_uuid_toname(struct devdiskruledir *__restrict UNUSED(self),
                    __pformatprinter printer, void *arg,
                    struct blkdev *__restrict dev, uintptr_t variant) {
	COMPILER_IMPURE();
	(void)variant;
	(void)dev;
	(void)printer;
	(void)arg;
	return 0;
}
/************************************************************************/



/************************************************************************/
/* /dev/disk/by-partlabel                                               */
/************************************************************************/
/* Enumerate block-devices based on `bp_efi_name' */

INTERN WUNUSED NONNULL((1, 2)) REF struct blkdev *KCALL
devdisk_partlabel_byname(struct devdiskruledir *__restrict UNUSED(self),
                         struct flookup_info *__restrict info) {
	REF struct fnode *node;
	node = fsuper_nodeafter(&devfs, NULL);
	while (node) {
		FINALLY_DECREF_UNLIKELY(node);
		if (fnode_isblkpart(node)) {
			struct blkdev *dev = fnode_asblkdev(node);
			if (strcmpz(dev->bd_partinfo.bp_efi_name,
			            info->flu_name, info->flu_namelen) == 0)
				return mfile_asblkdev(incref(dev));
		}
		node = fsuper_nodeafter(&devfs, node);
	}
	if (info->flu_flags & AT_DOSPATH) {
		node = fsuper_nodeafter(&devfs, NULL);
		while (node) {
			FINALLY_DECREF_UNLIKELY(node);
			if (fnode_isblkpart(node)) {
				struct blkdev *dev = fnode_asblkdev(node);
				if (strlen(dev->bd_partinfo.bp_efi_name) == info->flu_namelen &&
				    memcasecmp(dev->bd_partinfo.bp_efi_name, info->flu_name, info->flu_namelen * sizeof(char)) == 0)
					return mfile_asblkdev(incref(dev));
			}
			node = fsuper_nodeafter(&devfs, node);
		}
	}
	return NULL;
}

INTERN WUNUSED NONNULL((1, 2, 4)) ssize_t KCALL
devdisk_partlabel_toname(struct devdiskruledir *__restrict UNUSED(self),
                         __pformatprinter printer, void *arg,
                         struct blkdev *__restrict dev, uintptr_t variant) {
	if (variant != 0)
		return 0;
	if (!blkdev_ispart(dev))
		return 0;
	if (dev->bd_partinfo.bp_efi_name[0] == '\0')
		return 0;
	return (*printer)(arg, dev->bd_partinfo.bp_efi_name,
	                  strlen(dev->bd_partinfo.bp_efi_name));
}
/************************************************************************/



/************************************************************************/
/* /dev/disk/by-partuuid                                                */
/************************************************************************/
/* Either `bp_efi_partguid', or `TOHEX(*(u32 *)&br_mbr_diskuid[4]) + "-%.2x" % PARTNO' */

INTERN WUNUSED NONNULL((1, 2)) REF struct blkdev *KCALL
devdisk_partuuid_byname(struct devdiskruledir *__restrict UNUSED(self),
                        struct flookup_info *__restrict info) {
	if (info->flu_namelen == COMPILER_STRLEN("00000000-0000-0000-0000-000000000000")) {
		REF struct fnode *node;
		guid_t guid;
		unsigned int i;
		char text[COMPILER_STRLEN("00000000-0000-0000-0000-000000000000")];
		memcpy(text, info->flu_name, sizeof(text));
		if (info->flu_flags & AT_DOSPATH) {
			for (i = 0; i < lengthof(text); ++i)
				text[i] = tolower(text[i]);
		}
		for (i = 0; i < lengthof(text); ++i) {
			if (!islower(text[i]) && !isdigit(text[i]) && text[i] != '-')
				return NULL;
		}
		if (!guid_fromstr(text, &guid))
			return NULL;
		if (GUID_EQUALS(guid, 00000000, 0000, 0000, 0000, 000000000000))
			return NULL;
		node = fsuper_nodeafter(&devfs, NULL);
		while (node) {
			FINALLY_DECREF_UNLIKELY(node);
			if (fnode_isblkpart(node)) {
				struct blkdev *dev = fnode_asblkdev(node);
				if (bcmp(&dev->bd_partinfo.bp_efi_partguid, &guid, sizeof(guid)) == 0)
					return mfile_asblkdev(incref(dev));
			}
			node = fsuper_nodeafter(&devfs, node);
		}
		return NULL;
	}

	if (info->flu_namelen == COMPILER_STRLEN("00000000-00")) {
		REF struct fnode *node;
		unsigned int i;
		char text[COMPILER_STRLEN("00000000-00\0")];
		uint32_t mbrsig;
		uint8_t partno;
		*(char *)mempcpy(text, info->flu_name, sizeof(text) - sizeof(char)) = '\0';
		if (info->flu_flags & AT_DOSPATH) {
			for (i = 0; i < lengthof(text); ++i)
				text[i] = tolower(text[i]);
		}
		for (i = 0; i < COMPILER_STRLEN("00000000-00"); ++i) {
			if (i == COMPILER_STRLEN("00000000")
			    ? text[i] != '-'
			    : (!islower(text[i]) &&
			       !isdigit(text[i])))
				return NULL;
		}
		mbrsig = strtou32(text + 0, NULL, 16);
		partno = (uint8_t)strtou32(text + 9, NULL, 16);
		node   = fsuper_nodeafter(&devfs, NULL);
		while (node) {
			FINALLY_DECREF_UNLIKELY(node);
			if (fnode_isblkpart(node)) {
				struct blkdev *dev = fnode_asblkdev(node);
				if (dev->bd_partinfo.bp_partno == partno &&
				    blkdev_get_mbr_disksig(dev->bd_partinfo.bp_master) == mbrsig)
					return mfile_asblkdev(incref(dev));
			}
			node = fsuper_nodeafter(&devfs, node);
		}
		return NULL;
	}
	return NULL;
}

INTERN WUNUSED NONNULL((1, 2, 4)) ssize_t KCALL
devdisk_partuuid_toname(struct devdiskruledir *__restrict UNUSED(self),
                        __pformatprinter printer, void *arg,
                        struct blkdev *__restrict dev, uintptr_t variant) {
	uint32_t mbr_partid;
	if (variant != 0)
		return 0;
	if (!blkdev_ispart(dev))
		return 0;
	if (!GUID_EQUALS(dev->bd_partinfo.bp_efi_partguid, 00000000, 0000, 0000, 0000, 000000000000)) {
		/* EFI partition GUID. */
		return format_printf(printer, arg,
		                     "%.8" PRIx32 "-%.4" PRIx16 "-%.4" PRIx16 "-%.4" PRIx16 "-%.12" PRIx64,
		                     GUID_A(dev->bd_partinfo.bp_efi_partguid),
		                     GUID_B(dev->bd_partinfo.bp_efi_partguid),
		                     GUID_C(dev->bd_partinfo.bp_efi_partguid),
		                     GUID_D(dev->bd_partinfo.bp_efi_partguid),
		                     GUID_E(dev->bd_partinfo.bp_efi_partguid));
	}

	/* Fallback: MBR partition id. */
	mbr_partid = blkdev_get_mbr_disksig(dev->bd_partinfo.bp_master);
	if (mbr_partid != 0) {
		return format_printf(printer, arg, "%.8" PRIx32 "-%.2" PRIx8,
		                     mbr_partid, (uint8_t)dev->bd_partinfo.bp_partno);
	}
	return 0;
}
/************************************************************************/



/************************************************************************/
/* /dev/disk/by-id                                                      */
/************************************************************************/
/* TODO: ??? */

INTERN WUNUSED NONNULL((1, 2)) REF struct blkdev *KCALL
devdisk_id_byname(struct devdiskruledir *__restrict UNUSED(self),
                  struct flookup_info *__restrict info) {
	/* TODO */
	COMPILER_IMPURE();
	(void)info;
	return NULL;
}

INTERN WUNUSED NONNULL((1, 2, 4)) ssize_t KCALL
devdisk_id_toname(struct devdiskruledir *__restrict UNUSED(self),
                  __pformatprinter printer, void *arg,
                  struct blkdev *__restrict dev, uintptr_t variant) {
	/* TODO */
	COMPILER_IMPURE();
	(void)variant;
	(void)dev;
	(void)printer;
	(void)arg;
	return 0;
}
/************************************************************************/



/************************************************************************/
/* /dev/disk/by-path                                                    */
/************************************************************************/
/* TODO: ??? */

INTERN WUNUSED NONNULL((1, 2)) REF struct blkdev *KCALL
devdisk_path_byname(struct devdiskruledir *__restrict UNUSED(self),
                    struct flookup_info *__restrict info) {
	/* TODO */
	COMPILER_IMPURE();
	(void)info;
	return NULL;
}

INTERN WUNUSED NONNULL((1, 2, 4)) ssize_t KCALL
devdisk_path_toname(struct devdiskruledir *__restrict UNUSED(self),
                    __pformatprinter printer, void *arg,
                    struct blkdev *__restrict dev, uintptr_t variant) {
	/* TODO */
	COMPILER_IMPURE();
	(void)variant;
	(void)dev;
	(void)printer;
	(void)arg;
	return 0;
}
/************************************************************************/

DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DEVFS_DISKRULES_C */
