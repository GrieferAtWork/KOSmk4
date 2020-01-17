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
#ifndef GUARD_KERNEL_SRC_DEV_BLOCK_AUTOPART_C
#define GUARD_KERNEL_SRC_DEV_BLOCK_AUTOPART_C 1
#define _KOS_SOURCE 1

#include "block-autopart.h"

#include <kernel/compiler.h>

#include <dev/block.h>
#include <fs/vfs.h>
#include <hybrid/atomic.h>
#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/printk.h>
#include <kernel/types.h>

#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>
#include <hybrid/overflow.h>

#include <kos/dev.h>
#include <kos/guid.h>

#include <stddef.h>
#include <string.h>

DECL_BEGIN

PRIVATE NONNULL((1)) REF struct block_device_partition *KCALL
block_device_autopart_efi_impl(struct basic_block_device *__restrict self,
                               lba_t part_min, lba_t part_max) {
	struct efi_descriptor efi;
	REF struct block_device_partition *result = NULL, *new_result;
	block_device_read(self, &efi, sizeof(efi), (pos_t)part_min * self->bd_sector_size);
	/* Validate the EFI signature magic. */
	if (efi.gpt_signature[0] != EFIMAG0 || efi.gpt_signature[1] != EFIMAG1 ||
	    efi.gpt_signature[2] != EFIMAG2 || efi.gpt_signature[3] != EFIMAG3 ||
	    efi.gpt_signature[4] != EFIMAG4 || efi.gpt_signature[5] != EFIMAG5 ||
	    efi.gpt_signature[6] != EFIMAG6 || efi.gpt_signature[7] != EFIMAG7) {
		printk(KERN_WARNING "[blk] Invalid EFI signature in EFI partition at %#I64x...%#I64x on %.2x:%.2x (%q)\n",
		       (u64)part_min, (u64)part_max,
		       MAJOR(block_device_devno(self)),
		       MINOR(block_device_devno(self)),
		       self->bd_name);
		/* Load the supposed EFI partition as a normal partition. */
		return (REF struct block_device_partition *)-2;
	}
	printk(KERN_INFO "[blk] EFI partition found at %#I64x...%#I64x on %.2x:%.2x (%q)\n",
	       (u64)part_min, (u64)part_max,
	       MAJOR(block_device_devno(self)),
	       MINOR(block_device_devno(self)),
	       self->bd_name);
	efi.gpt_revision        = (le32)LESWAP32(efi.gpt_revision);
	efi.gpt_hdrsize         = (le32)LESWAP32(efi.gpt_hdrsize);
	efi.gpt_hdrcrc32        = (le32)LESWAP32(efi.gpt_hdrcrc32);
	efi.gpt_currlba         = (le64)LESWAP64(efi.gpt_currlba);
	efi.gpt_backlba         = (le64)LESWAP64(efi.gpt_backlba);
	efi.gpt_firstpart       = (le64)LESWAP64(efi.gpt_firstpart);
	efi.gpt_lastpart        = (le64)LESWAP64(efi.gpt_lastpart);
	efi.gpt_partition_start = (le64)LESWAP64(efi.gpt_partition_start);
	efi.gpt_partition_count = (le32)LESWAP32(efi.gpt_partition_count);
	efi.gpt_partition_entsz = (le32)LESWAP32(efi.gpt_partition_entsz);
	efi.gpt_partition_crc32 = (le32)LESWAP32(efi.gpt_partition_crc32);
	if ((u32)efi.gpt_hdrsize < offsetafter(struct efi_descriptor, gpt_partition_count)) {
		printk(KERN_ERR "[blk] EFI header table at %#I64x...%#I64x on %.2x:%.2x (%q) is too small (%I32u bytes)\n",
		       (u64)part_min, (u64)part_max,
		       MAJOR(block_device_devno(self)),
		       MINOR(block_device_devno(self)),
		       self->bd_name, (u32)efi.gpt_hdrsize);
		return (REF struct block_device_partition *)-2;
	}
	/* Substitute missing members. */
	if ((u32)efi.gpt_hdrsize < offsetafter(struct efi_descriptor, gpt_partition_entsz))
		efi.gpt_partition_entsz = (le32)128;
	else if ((u32)efi.gpt_partition_entsz < offsetafter(struct efi_partition, p_part_end)) {
		printk(KERN_ERR "[blk] EFI partition entires in %#I64x...%#I64x on %.2x:%.2x (%q) are too small (%I32u bytes)\n",
		       (u64)part_min, (u64)part_max,
		       MAJOR(block_device_devno(self)),
		       MINOR(block_device_devno(self)),
		       self->bd_name, (u32)efi.gpt_partition_entsz);
		return (REF struct block_device_partition *)-2;
	}
	{
		u32 vecsize, entsize;
		pos_t vecaddr;
		if (OVERFLOW_UMUL((u64)efi.gpt_partition_start, self->bd_sector_size, &vecaddr)) {
			printk(KERN_ERR "[blk] EFI partition table address in %#I64x...%#I64x on %.2x:%.2x (%q) overflows (sector %I64u * %Iu bytes per sector)\n",
			       (u64)part_min, (u64)part_max,
			       MAJOR(block_device_devno(self)),
			       MINOR(block_device_devno(self)),
			       self->bd_name,
			       (u64)efi.gpt_partition_start,
			       (size_t)self->bd_sector_size);
			return (REF struct block_device_partition *)-2;
		}
		vecsize = (u32)efi.gpt_partition_count;
		entsize = (u32)efi.gpt_partition_entsz;
		if (entsize > sizeof(struct efi_partition))
			entsize = sizeof(struct efi_partition);
		for (; vecsize; --vecsize, vecaddr += (pos_t)(u32)efi.gpt_partition_entsz) {
			struct efi_partition part;
			unsigned int name_maxlen, i;
			uintptr_half_t flags;
			char name[COMPILER_LENOF(((struct block_device_partition *)0)->bp_label)], *dst;
			block_device_read(self, &part, entsize, vecaddr);
			if (GUID_EQUALS(part.p_type_guid, 00000000, 0000, 0000, 0000, 000000000000))
				break; /* Sentinel. */
			part.p_part_min = (le64)LESWAP64(part.p_part_min);
			part.p_part_end = (le64)LESWAP64(part.p_part_end);
			if ((u64)part.p_part_end < (u64)part.p_part_min) {
				printk(KERN_ERR "[blk] EFI partition from EFI table in %#I64x...%#I64x on %.2x:%.2x (%q) ends at %I64u before it starts at %I64u\n",
				       (u64)part_min, (u64)part_max,
				       MAJOR(block_device_devno(self)),
				       MINOR(block_device_devno(self)),
				       self->bd_name,
				       (u64)part.p_part_min,
				       (u64)part.p_part_end);
				continue;
			}
			if ((u64)part.p_part_end <= (u64)part.p_part_min)
				continue; /* Empty partition. */
			part.p_flags = (le64)LESWAP64(part.p_flags);
			if (entsize < offsetafter(struct efi_partition, p_flags))
				part.p_flags = (le64)0;
			name_maxlen = 0;
			if (entsize > offsetof(struct efi_partition, p_name))
				name_maxlen = (entsize - offsetof(struct efi_partition, p_name)) / 2;
			dst = name;
			for (i = 0; i < name_maxlen; ++i) {
				u16 ch = LESWAP16(part.p_name[i]);
				*dst++ = (char)ch; /* TODO: utf16_to_utf8 */
			}
			flags = 0;
			if ((u64)part.p_flags & EFI_PART_F_READONLY)
				flags |= BLOCK_DEVICE_FLAG_READONLY;
			new_result = block_device_makepart(self,
			                                   (lba_t)(u64)part.p_part_min,
			                                   (lba_t)(u64)part.p_part_end - (lba_t)1,
			                                   name,
			                                   (size_t)(dst - name),
			                                   0,
			                                   &part.p_type_guid,
			                                   &part.p_part_guid,
			                                   flags);
#if 0
			/* XXX: This is technically correct, but if we use this, KOS will
			 *      attempt to use the grub partition as filesystem root... */
			if ((u64)part.p_flags & EFI_PART_F_ACTIVE)
#else
			/* According to my tutorial, the boot partition should be named `kos'.
			 * Until we've got something better, use that as indicator. */
			if (dst >= name + 3 &&
			    name[0] == 'k' &&
			    name[1] == 'o' &&
			    name[2] == 's')
#endif
			{
				if (!result)
					result = new_result; /* First active partition. */
				else {
					if (result != (REF struct block_device_partition *)-1) {
						printk(KERN_WARNING "[blk] Secondary active EFI partition %.2x:%.2x collides with %.2x:%.2x on %.2x:%.2x\n",
						       MAJOR(block_device_devno(new_result)),
						       MINOR(block_device_devno(new_result)),
						       MAJOR(block_device_devno(result)),
						       MINOR(block_device_devno(result)),
						       MAJOR(block_device_devno(self)),
						       MINOR(block_device_devno(self)));
						decref(result);
						result = (REF struct block_device_partition *)-1;
					} else {
						printk(KERN_WARNING "[blk] Three or more active EFI partition %.2x:%.2x on %.2x:%.2x\n",
						       MAJOR(block_device_devno(new_result)),
						       MINOR(block_device_devno(new_result)),
						       MAJOR(block_device_devno(self)),
						       MINOR(block_device_devno(self)));
					}
					decref(new_result);
				}
			} else {
				decref(new_result);
			}
		}
	}
	return result;
}


/* Automatically parse the MBR/EFI tables of the disk, and try to partition if accordingly.
 * If one of the partitions found have the ACTIVE/BOOTABLE flag set, a reference to that
 * partition is returned to the caller. If more than one partition has that flag set, or
 * if none of them do, `NULL' is returned instead, though the function has still succeeded.
 * NOTE: The caller should invoke `block_device_delparts' in the master partition beforehand.
 * NOTE: When `self' is a partition itself, its contents will still be parsed for partition
 *       tables like they usually would, though new partitions will still be added to the
 *       master device, as `block_device_makepart()' is used to create them. */
PRIVATE NONNULL((1)) REF struct block_device_partition *KCALL
block_device_autopart_impl(struct basic_block_device *__restrict self,
                           lba_t part_min, lba_t part_max)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct block_device_partition *result = NULL;
#if 0 /* There is no other mechanism that we support, so always try to use this one... */
	if (self->bd_sector_size == 512)
#endif
	{
		struct mbr_data mbr;
		unsigned int i;
		block_device_read(self, &mbr, sizeof(mbr),
		                  ((pos_t)part_min * (pos_t)self->bd_sector_size) +
		                  (pos_t)MBR_DATA_OFFSET);
		if (mbr.mbr_sig[0] != 0x55 || mbr.mbr_sig[1] != 0xAA)
			return NULL; /* Not MBR formatted */
		/* Load the MBR, and check if it refers to a GPT. */
		for (i = 0; i < 4; ++i) {
			REF struct block_device_partition *new_result;
			lba_t lba_min, lba_max, lba_siz;
			if (mbr.mbr_part[i].pt.pt_sysid == 0)
				continue; /* Empty partition */
			if ((mbr.mbr_part[i].pt.pt_bootable & PART_BOOTABLE_LBA48) &&
			    (mbr.mbr_part[i].pt_48.pt_sig1 == PART48_SIG1 &&
			     mbr.mbr_part[i].pt_48.pt_sig2 == PART48_SIG2)) {
				lba_min = (lba_t)(u64)LESWAP32(mbr.mbr_part[i].pt_48.pt_lbastart);
				lba_min |= (lba_t)(u64)LESWAP16(mbr.mbr_part[i].pt_48.pt_lbastarthi) << 32;
				lba_siz = (lba_t)(u64)LESWAP32(mbr.mbr_part[i].pt_48.pt_lbasize);
				lba_siz |= (lba_t)(u64)LESWAP16(mbr.mbr_part[i].pt_48.pt_lbasizehi) << 32;
			} else {
				lba_min = (lba_t)(u64)LESWAP32(mbr.mbr_part[i].pt_32.pt_lbastart);
				lba_siz = (lba_t)(u64)LESWAP32(mbr.mbr_part[i].pt_32.pt_lbasize);
			}
			if unlikely(!lba_siz) {
				bool has_other_partitions;
				if (!(mbr.mbr_part[i].pt.pt_bootable & PART_BOOTABLE_ACTICE))
					continue; /* Empty */
				/* Check if this is a whole-disk partition. */
				if (i != 0)
					continue; /* Nope... */
				has_other_partitions = false;
				for (i = 1; i < 4; ++i) {
					if (mbr.mbr_part[i].pt_32.pt_lbasize) {
						has_other_partitions = true;
						break;
					}
				}
				i = 0;
				if (has_other_partitions)
					continue;
				/* It is a whole-disk partition! */
				lba_siz = (part_max - lba_min) + 1;
			}
			if unlikely(OVERFLOW_UADD(lba_min, part_min, &lba_min))
				continue; /* Overflow */
			if unlikely(OVERFLOW_UADD(lba_min, lba_siz - (lba_t)1, &lba_max))
				lba_max = (lba_t)-1;
			if unlikely(lba_max > part_max) {
				printk(KERN_WARNING "[blk] Partition #%u of %q expands past the end of the "
				                    "disk (part:%#I64x...%#I64x,disk:%#I64x...%#I64x) (truncate it)\n",
				       i, self->bd_name,
				       (u64)lba_min, (u64)lba_max,
				       (u64)part_min, (u64)part_max);
				lba_max = part_max;
			}
			if (mbr.mbr_part[i].pt.pt_sysid == 0xee) {
				/* Special case: EFI partition */
				new_result = block_device_autopart_efi_impl(self, lba_min, lba_max);
				if (new_result == (REF struct block_device_partition *)-2)
					goto load_normal_partition;
			} else if (mbr.mbr_part[i].pt.pt_sysid == 0x05 ||
			           mbr.mbr_part[i].pt.pt_sysid == 0x0f) {
				/* Special case: extended partition. */
				if (lba_min <= part_min && lba_max >= part_max)
					continue; /* Extended partition forms an infinite loop. */
				new_result = block_device_autopart_impl(self, lba_min, lba_max);
			} else {
				/* Normal partition. */
load_normal_partition:
				new_result = block_device_makepart(self, lba_min, lba_max, NULL, 0,
				                                   mbr.mbr_part[i].pt.pt_sysid,
				                                   (guid_t *)&mbr.mbr_part[i],
				                                   (guid_t *)&mbr.mbr_part[i],
				                                   BLOCK_DEVICE_FLAG_NORMAL);
				if (!(mbr.mbr_part[i].pt.pt_bootable & PART_BOOTABLE_ACTICE)) {
					decref(new_result);
					new_result = NULL;
				}
			}
			if (!new_result)
				;
			else if unlikely(result) {
				/* Error: more than one active partition.
				 *       (log a warning, and indicate that the
				 *        active partition cannot be determined) */
				if (result != (REF struct block_device_partition *)-1) {
					printk(KERN_WARNING "[blk] Secondary active partition %.2x:%.2x collides with %.2x:%.2x on %.2x:%.2x\n",
					       MAJOR(block_device_devno(new_result)),
					       MINOR(block_device_devno(new_result)),
					       MAJOR(block_device_devno(result)),
					       MINOR(block_device_devno(result)),
					       MAJOR(block_device_devno(self)),
					       MINOR(block_device_devno(self)));
					decref(result);
					result = (REF struct block_device_partition *)-1;
				} else {
					printk(KERN_WARNING "[blk] Three or more active partition %.2x:%.2x on %.2x:%.2x\n",
					       MAJOR(block_device_devno(new_result)),
					       MINOR(block_device_devno(new_result)),
					       MAJOR(block_device_devno(self)),
					       MINOR(block_device_devno(self)));
				}
				decref(new_result);
			} else {
				result = new_result;
			}
		}
	}
	return result;
}

PUBLIC NONNULL((1)) REF struct block_device_partition *KCALL
block_device_autopart_ex(struct basic_block_device *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct block_device_partition *result;
	result = block_device_autopart_impl(self, (lba_t)0, self->bd_sector_count - (lba_t)1);
	if (result == (REF struct block_device_partition *)-1)
		result = NULL;
	return result;
}

PUBLIC NONNULL((1)) void KCALL
block_device_autopart(struct basic_block_device *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct block_device_partition *active_part;
	active_part = block_device_autopart_ex(self);
	if (active_part) {
		/* If the the root VFS has already been mounted, then we've moved past the
		 * early boot phase of trying to figure out what device was used to boot us.
		 * In that case, simply ignore any possible active partition. */
		if (ATOMIC_READ(vfs_kernel.p_inode) != NULL)
			goto do_decref_active_part;
		printk(FREESTR(KERN_INFO "[boot] Found boot partition: %.2x:%.2x (%q)\n"),
		       MAJOR(active_part->bd_devlink.a_vaddr),
		       MINOR(active_part->bd_devlink.a_vaddr),
		       active_part->bd_name);
		if likely(!boot_partition) {
			boot_partition = active_part; /* Inherit reference. */
		} else if unlikely(boot_partition == (REF struct basic_block_device *)-1) {
do_decref_active_part:
			decref_unlikely(active_part);
		} else {
			printk(FREESTR(KERN_WARNING "[boot] Ambigous boot partition: could be %.2x:%.2x (%q) or %.2x:%.2x (%q)\n"),
			       MAJOR(active_part->bd_devlink.a_vaddr),
			       MINOR(active_part->bd_devlink.a_vaddr),
			       active_part->bd_name,
			       MAJOR(boot_partition->bd_devlink.a_vaddr),
			       MINOR(boot_partition->bd_devlink.a_vaddr),
			       boot_partition->bd_name);
			decref(active_part);
			decref(boot_partition);
			boot_partition = (REF struct basic_block_device *)-1;
		}
	}
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_BLOCK_AUTOPART_C */
