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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_BOOT_MULTIBOOT_C
#define GUARD_KERNEL_CORE_ARCH_I386_BOOT_MULTIBOOT_C 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/boot.h>
#include <kernel/except.h>
#include <kernel/memory.h>
#include <kernel/mman.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/map.h>
#include <kernel/mman/phys.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/x86/multiboot.h>

#include <hybrid/align.h>

#include <inttypes.h>
#include <malloca.h>
#include <stddef.h>
#include <string.h>

#include <libcmdline/decode.h>

DECL_BEGIN


struct mb_tag {
	u32 mt_magic;
	u32 mt_flags;
	u32 mt_checksum;
};

/* Multiboot header */
#define MB_FLAGS (/*MB_PAGE_ALIGN |*/ MB_MEMORY_INFO /*| MB_VIDEO_MODE*/)
PRIVATE ATTR_SECTION(".x86.mb") ATTR_ALIGNED(MB_HEADER_ALIGN)
ATTR_USED struct mb_tag mb_multiboot = {
	.mt_magic    = MB_HEADER_MAGIC,
	.mt_flags    = MB_FLAGS,
	.mt_checksum = (u32) - (MB_HEADER_MAGIC + MB_FLAGS),
};

/* Multiboot2 header */

#define MB2_TAG   ATTR_USED ATTR_SECTION(".x86.mb2.tag") ATTR_ALIGNED(MB2_TAG_ALIGN)
/* MB2 tags would got here, annotated with `PRIVATE MB2_TAG ...' */



/* MB2 tags terminator */
PRIVATE ATTR_SECTION(".x86.mb2.tag.end")
        ATTR_ALIGNED(MB2_TAG_ALIGN)
ATTR_USED struct mb2_header_tag tag_empty = {
	.type  = MB2_HEADER_TAG_END,
	.flags = 0,
	.size  = sizeof(struct mb2_header_tag),
};


#ifdef __x86_64__
INTDEF byte_t __x86_kernel_mb2_hdrlen_and_chksum[];
#else /* __x86_64__ */
INTDEF byte_t __386_kernel_mb2_hdrlen[];
INTDEF byte_t __386_kernel_mb2_chksum[];
#endif /* !__x86_64__ */
PRIVATE ATTR_SECTION(".x86.mb2") ATTR_ALIGNED(MB2_HEADER_ALIGN)
ATTR_USED struct mb2_header mb_multiboot2 = {
	.magic        = MB2_HEADER_MAGIC,
	.architecture = MB2_ARCHITECTURE_I386,
	{
#ifdef __x86_64__
		(u64)__x86_kernel_mb2_hdrlen_and_chksum
#else /* __x86_64__ */
		{
			/* .header_length = */ (u32)__386_kernel_mb2_hdrlen,
			/* .checksum      = */ (u32)__386_kernel_mb2_chksum
		}
#endif /* !__x86_64__ */
	}
};



/* Convert between  BIOS and  our own  memory bank  typing
 * Note  that we can't just adopt BIOS indices for our own
 * typing, since we encode memory priority as part of bank
 * type  IDs, where during initialization, greater IDs can
 * override  existing mappings, while lower IDs are ignore
 * in areas of overlap  with existing mappings of  greater
 * IDs. */
INTERN_CONST ATTR_FREERODATA u8 const memtype_bios_matrix[6] = {
	[0] = PMEMBANK_TYPE_UNDEF,  /* Undefined (Fallback). */
	[1] = PMEMBANK_TYPE_RAM,    /* Available. */
	[2] = PMEMBANK_TYPE_DEVICE, /* Reserved. */
	[3] = PMEMBANK_TYPE_COUNT,  /* ACPI-Reclaimable. (Ignored) */
	[4] = PMEMBANK_TYPE_NVS,    /* NVS. */
	[5] = PMEMBANK_TYPE_BADRAM, /* Badram. */
};


INTERN ATTR_FREETEXT void
NOTHROW(KCALL memory_load_mb_lower_upper)(u32 mem_lower, u32 mem_upper) {
	minfo_addbank((physaddr_t)0x00000000, (physaddr_t)mem_lower * 1024, PMEMBANK_TYPE_RAM);
	minfo_addbank((physaddr_t)0x00100000, (physaddr_t)mem_upper * 1024, PMEMBANK_TYPE_RAM);
}


/* Length (in bytes) of the kernel commandline, as passed by the boot-loader */
PRIVATE ATTR_FREEBSS size_t x86_kernel_cmdline_length = 0;


/* Copy and split the kernel commandline from bootloader memory. */
INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_commandline_himem)(void) {
	char *cmdline_copy = NULL;
	if (!x86_kernel_cmdline_length)
		return;
	TRY {
		size_t i;
		char *arg;
		/* Copy the kernel commandline from physical memory. */
		cmdline_copy = (char *)kmalloc((x86_kernel_cmdline_length + 2) * sizeof(char), GFP_LOCKED);
		copyfromphys(cmdline_copy,
		             (physaddr_t)((uintptr_t)kernel_driver.d_cmdline - KERNEL_CORE_BASE),
		             x86_kernel_cmdline_length * sizeof(char));
		cmdline_copy[x86_kernel_cmdline_length + 0] = '\0';
		cmdline_copy[x86_kernel_cmdline_length + 1] = '\0';
		kernel_driver.d_cmdline = cmdline_copy;
		kernel_driver.d_argv    = (char **)kmalloc((kernel_driver.d_argc + 1) * sizeof(char *), GFP_LOCKED);
		printk(FREESTR(KERN_INFO "[boot] Loaded kernel commandline: ["));
		for (i = 0, arg = cmdline_copy;
		     i < kernel_driver.d_argc; ++i, arg = strend(arg) + 1) {
			printk(FREESTR(KERN_INFO "%s%q"), i == 0 ? FREESTR("") : FREESTR(", "), arg);
			kernel_driver.d_argv[i] = arg;
		}
		printk(FREESTR(KERN_INFO "]\n"));
	} EXCEPT {
		except_printf(FREESTR("Allocating kernel commandline"));
		kfree(cmdline_copy);
		kernel_driver.d_argc    = 0;
		kernel_driver.d_argv    = NULL;
		kernel_driver.d_cmdline = NULL;
	}
}


#define X86_BOOT_DRIVER_FORMAT_NONE 0 /* No drivers specified */
#define X86_BOOT_DRIVER_FORMAT_MB1  1 /* multiboot1-specific driver list */
#define X86_BOOT_DRIVER_FORMAT_MB2  2 /* multiboot2-specific driver list */
PRIVATE ATTR_FREEBSS int    x86_boot_driver_format = 0;  /* Boot driver support format. */
PRIVATE ATTR_FREEBSS void  *x86_boot_driver_base = NULL; /* Base address for boot driver data. */
PRIVATE ATTR_FREEBSS size_t x86_boot_driver_size = 0;    /* Size of boot driver data. */

PRIVATE ATTR_FREETEXT void KCALL
load_bootloader_driver2(PHYS u32 blob_addr, size_t blob_size, char *cmdline) {
	REF struct driver *drv;
	void *blob;
	size_t aligned_blob_size;
	aligned_blob_size = blob_size + (blob_addr & PAGEMASK);
	aligned_blob_size = CEIL_ALIGN(aligned_blob_size, PAGESIZE);
	/* Create a  temporary  mapping  of  prepared  virtual  memory  which
	 * we can then use to map the driver's data blob into virtual memory. */
	blob = mman_map_res(&mman_kernel,
	                    MHINT_GETADDR(KERNEL_MHINT_TEMPORARY),
	                    aligned_blob_size,
	                    MHINT_GETMODE(KERNEL_MHINT_TEMPORARY) |
	                    MAP_PREPARED | MAP_NOMERGE);
	RAII_FINALLY {
		mman_unmap(&mman_kernel, blob, aligned_blob_size);
	};
	/* Map the driver blob into virtual memory. */
	pagedir_map(blob,
	            aligned_blob_size,
	            (physaddr_t)(blob_addr & ~PAGEMASK),
	            PAGEDIR_PROT_READ);

	/* Load the mapped driver blob as a driver module.
	 * NOTE: We  pass  the  `DRIVER_INSMOD_FLAG_NOINIT'  flag  so-as  to allow
	 *       the driver to be initialized (and have its dependencies be bound)
	 *       once all drivers specified by  the boot loader have been  loaded.
	 *    -> That way,  driver dependencies  can be  loaded in  the same  manner,
	 *       thus not relying on file-system drivers not having any dependencies. */
	drv = driver_loadmod_blob((byte_t *)blob + (blob_addr & PAGEMASK),
	                          blob_size, cmdline);

	/* Drop the reference returned by driver_insmod_blob() */
	decref(drv);
}

PRIVATE ATTR_FREETEXT void KCALL
load_bootloader_driver(PHYS u32 blob_addr, size_t blob_size,
                       PHYS u32 cmdline_addr, size_t cmdline_maxsize) {
	if (!cmdline_maxsize) {
		load_bootloader_driver2(blob_addr, blob_size, NULL);
	} else {
		char *cmdline;
		cmdline = (char *)malloca((cmdline_maxsize + 1) * sizeof(char));
		RAII_FINALLY { freea(cmdline); };
		/* Copy the commandline into our buffer. */
		copyfromphys(cmdline,
		             (physaddr_t)cmdline_addr,
		             cmdline_maxsize);
		cmdline[cmdline_maxsize] = '\0';
		/* Load the driver blob. */
		load_bootloader_driver2(blob_addr,
		                        blob_size,
		                        cmdline);
	}
}



INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_bootloader_drivers)(void) {
	switch (x86_boot_driver_format) {

	case X86_BOOT_DRIVER_FORMAT_MB1: {
		mb_module_t driver_descriptor;
		size_t i;
		for (i = 0; i < x86_boot_driver_size; ++i) {
			copyfromphys(&driver_descriptor,
			             (physaddr_t)((uintptr_t)&((PHYS mb_module_t *)x86_boot_driver_base)[i]),
			             sizeof(driver_descriptor));
			if unlikely(driver_descriptor.mod_start >= driver_descriptor.mod_end)
				continue;
			TRY {
				load_bootloader_driver((u32)driver_descriptor.mod_start,
				                       (size_t)(driver_descriptor.mod_end -
				                                driver_descriptor.mod_start),
				                       driver_descriptor.cmdline,
				                       (size_t)driver_descriptor.pad);
			} EXCEPT {
				except_printf(FREESTR("Loading bootloader driver from %" PRIp32 "...%" PRIp32),
				              (u32)driver_descriptor.mod_start,
				              (u32)driver_descriptor.mod_end - 1);
			}
		}
	}	break;

	case X86_BOOT_DRIVER_FORMAT_MB2: {
		PHYS struct mb2_tag *tag_begin, *tag_iter, *tag_end;
		/* Enumerate MB2-tags that may potentially contain driver descriptors. */
		tag_begin = (struct mb2_tag *)x86_boot_driver_base;
		tag_end   = (struct mb2_tag *)((byte_t *)tag_begin + x86_boot_driver_size);
		for (tag_iter = tag_begin; tag_iter < tag_end;) {
			struct mb2_tag_module_no_cmdline tag;
			copyfromphys(&tag, (physaddr_t)(uintptr_t)tag_iter, sizeof(tag));
			if (tag.type == MB2_TAG_TYPE_MODULE) {
				/* Got a driver tag. */
				if unlikely(tag.mod_start >= tag.mod_end)
					continue;
				TRY {
					size_t cmdline_max_length;
					PHYS struct mb2_tag_module *mod;
					cmdline_max_length = tag.size - offsetof(struct mb2_tag_module, cmdline);
					if unlikely(tag.size < offsetof(struct mb2_tag_module, cmdline))
						cmdline_max_length = 0;
					mod = (PHYS struct mb2_tag_module *)tag_iter;
					load_bootloader_driver((PHYS u32)tag.mod_start,
					                       (size_t)(tag.mod_end - tag.mod_start),
					                       (PHYS u32)(PHYS uintptr_t)&mod->cmdline[0],
					                       cmdline_max_length);
				} EXCEPT {
					except_printf(FREESTR("Loading bootloader driver from %" PRIp32 "...%" PRIp32),
					              (u32)tag.mod_start,
					              (u32)tag.mod_end - 1);
				}
			}
			tag_iter = (PHYS struct mb2_tag *)((byte_t *)tag_iter + CEIL_ALIGN(tag.size, MB2_TAG_ALIGN));
		}
	}	break;

	default: break;
	}
}



INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_load_mb1info)(/*PHYS*/ u32 info) {
	VIRT mb_info_t *vinfo;
	vinfo = (VIRT mb_info_t *)((uintptr_t)info + KERNEL_CORE_BASE);
	if (vinfo->flags & MB_INFO_BOOTDEV) {
		/* Extract boot device information. */
		boot_device.bdi_biosdev           = (u8)((vinfo->boot_device & 0xff000000) >> 24);
		boot_device.bdi_partition         = (u8)((vinfo->boot_device & 0x00ff0000) >> 16);
		boot_device.bdi_sub_partition     = (u8)((vinfo->boot_device & 0x0000ff00) >> 8);
		boot_device.bdi_sub_sub_partition = (u8)(vinfo->boot_device & 0x000000ff);
	}
	if (vinfo->flags & MB_INFO_MEM_MAP) {
		mb_memory_map_t *iter, *end;
		minfo_addbank((physaddr_t)vinfo->mmap_addr,
		              (physaddr_t)vinfo->mmap_length,
		              PMEMBANK_TYPE_PRESERVE);
		TRY {
			iter = (struct mb_mmap_entry *)(uintptr_t)vinfo->mmap_addr;
			end  = (mb_memory_map_t *)((uintptr_t)iter + vinfo->mmap_length);
			iter = (mb_memory_map_t *)((uintptr_t)iter + KERNEL_CORE_BASE);
			end  = (mb_memory_map_t *)((uintptr_t)end + KERNEL_CORE_BASE);
			for (; iter < end; iter = (mb_memory_map_t *)((uintptr_t)&iter->addr + iter->size)) {
				if (iter->type >= lengthof(memtype_bios_matrix))
					iter->type = 0;
				if (memtype_bios_matrix[iter->type] >= PMEMBANK_TYPE_COUNT)
					continue;
				minfo_addbank((physaddr_t)iter->addr,
				              (physaddr_t)iter->len,
				              memtype_bios_matrix[iter->type]);
			}
		} EXCEPT {
			except_printf(FREESTR("Loading multiboot memory map"));
		}
	}
	if (vinfo->flags & MB_MEMORY_INFO)
		memory_load_mb_lower_upper(vinfo->mem_lower, vinfo->mem_upper);
	if (vinfo->flags & MB_INFO_CMDLINE) {
		/* Save the kernel commandline pointer (will be loaded later) */
		kernel_driver.d_cmdline = (char *)(uintptr_t)vinfo->cmdline;
		if (kernel_driver.d_cmdline) {
			kernel_driver.d_cmdline = (char *)((uintptr_t)kernel_driver.d_cmdline + KERNEL_CORE_BASE);
			if (!kernel_driver.d_cmdline[0]) {
				kernel_driver.d_cmdline = NULL;
			} else {
				char *cmdline_end;
				/* Reserve memory used by the kernel commandline. */
				x86_kernel_cmdline_length = strlen(kernel_driver.d_cmdline);
				/* Split the kernel commandline into arguments. */
				kernel_driver.d_argc = cmdline_split(kernel_driver.d_cmdline, &cmdline_end);
				minfo_addbank((physaddr_t)((uintptr_t)kernel_driver.d_cmdline - KERNEL_CORE_BASE),
				              (physaddr_t)(size_t)(cmdline_end - kernel_driver.d_cmdline),
				              PMEMBANK_TYPE_PRESERVE);
			}
		}
	}
	if (vinfo->flags & MB_INFO_MODS) {
		size_t i;
		PHYS mb_module_t *base;
		/* Load modules (drivers) provided by the bootloader */
		base = (PHYS mb_module_t *)((uintptr_t)vinfo->mods_addr + KERNEL_CORE_BASE);
		for (i = 0; i < vinfo->mods_count; ++i) {
			uintptr_t start, end;
			start = base[i].mod_start;
			end   = base[i].mod_end;
			if unlikely(start >= end)
				continue;
			/* Preserve memory for the driver memory blob. */
			minfo_addbank((physaddr_t)start,
			              (physaddr_t)end - (physaddr_t)start,
			              PMEMBANK_TYPE_PRESERVE);
			if (base[i].cmdline) {
				char *cmdline;
				size_t cmdline_length;
				cmdline = (char *)((uintptr_t)base[i].cmdline + KERNEL_CORE_BASE);
				/* Abuse the padding data entry to store the length of the cmdline. */
				base[i].pad = (u32)(cmdline_length = strlen(cmdline));
				minfo_addbank((physaddr_t)((uintptr_t)cmdline - KERNEL_CORE_BASE),
				              (physaddr_t)(uintptr_t)cmdline_length + 1,
				              PMEMBANK_TYPE_PRESERVE);
			} else {
				base[i].pad = 0;
			}
		}
		x86_boot_driver_format = X86_BOOT_DRIVER_FORMAT_MB1;
		x86_boot_driver_base   = (void *)(uintptr_t)vinfo->mods_addr;
		x86_boot_driver_size   = vinfo->mods_count;
	}
}

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_load_mb2info)(/*PHYS*/ u32 info) {
	/* Multiboot 2 information. */
	struct mb2_tag *tag_begin, *tag_iter, *tag_end;
	size_t mbt_min_size, temp;
	mbt_min_size = *(u32 const *)((uintptr_t)info + KERNEL_CORE_BASE);
	tag_begin    = (struct mb2_tag *)((uintptr_t)info + KERNEL_CORE_BASE + 8);
	/* Make sure that we're not protecting too little amount of data. */
	for (tag_end = tag_begin;
	     tag_end->type != MB2_TAG_TYPE_END && tag_end->size != 0;
	     tag_end = (struct mb2_tag *)((byte_t *)tag_end + CEIL_ALIGN(tag_end->size, MB2_TAG_ALIGN)))
		;
	temp = (uintptr_t)tag_end - (uintptr_t)tag_begin;
	if unlikely(mbt_min_size < temp) {
		printk(FREESTR(KERN_WARNING "Announced MBT size %" PRIuSIZ " is smaller "
		                            "than actual size %" PRIuSIZ "\n"),
		       mbt_min_size, temp);
	}
	mbt_min_size = temp;
	printk(FREESTR(KERN_INFO "Parsing MB2 parameter block %p...%p\n"),
	       (uintptr_t)info, (uintptr_t)info + mbt_min_size - 1);

	/* Protect the multiboot information buffer from being overwritten too early. */
	minfo_addbank((physaddr_t)info,
	              (physaddr_t)mbt_min_size,
	              PMEMBANK_TYPE_PRESERVE);

	for (tag_iter = tag_begin; tag_iter < tag_end;
	     tag_iter = (struct mb2_tag *)((byte_t *)tag_iter +
	                                   CEIL_ALIGN(tag_iter->size, MB2_TAG_ALIGN))) {
#define TAG(T) ((struct T *)tag_iter)
		TRY {
			switch (tag_iter->type) {

			case MB2_TAG_TYPE_CMDLINE:
				if (!kernel_driver.d_cmdline &&
				    TAG(mb2_tag_string)->size > offsetof(struct mb2_tag_string, string)) {
					kernel_driver.d_cmdline = TAG(mb2_tag_string)->string;
					x86_kernel_cmdline_length = strnlen(TAG(mb2_tag_string)->string,
					                                    (TAG(mb2_tag_string)->size -
					                                     offsetof(struct mb2_tag_string, string)) /
					                                    sizeof(char));
					if unlikely(kernel_driver.d_cmdline[x86_kernel_cmdline_length] != 0) {
						/* By accessing 1 byte before `TAG(mb2_tag_string)->string', we're doing
						 * a  /bad/ thing and gcc doesn't like  that (and admittedly: it's got a
						 * point in complaining).
						 *
						 * So we have to hide the origin of `kernel_driver.d_cmdline' -- :P */
						COMPILER_DELETE_ASSUMPTIONS(kernel_driver.d_cmdline);
						kernel_driver.d_cmdline = (char *)memmovedown(kernel_driver.d_cmdline - 1,
						                                              kernel_driver.d_cmdline,
						                                              x86_kernel_cmdline_length);
						kernel_driver.d_cmdline[x86_kernel_cmdline_length] = 0;
					}
					kernel_driver.d_argc = cmdline_split(kernel_driver.d_cmdline, NULL);
				}
				break;

			case MB2_TAG_TYPE_BASIC_MEMINFO:
				memory_load_mb_lower_upper(TAG(mb2_tag_basic_meminfo)->mem_lower,
				                           TAG(mb2_tag_basic_meminfo)->mem_upper);
				break;

			case MB2_TAG_TYPE_MMAP:
				if likely(TAG(mb2_tag_mmap)->entry_size) {
					mb2_memory_map_t *iter, *end;
					iter = TAG(mb2_tag_mmap)->entries;
					end  = (mb2_memory_map_t *)((byte_t *)TAG(mb2_tag_mmap) + TAG(mb2_tag_mmap)->size);
					for (; iter < end;
					     iter = (mb2_memory_map_t *)((byte_t *)iter + TAG(mb2_tag_mmap)->entry_size)) {
						if (iter->type >= lengthof(memtype_bios_matrix))
							iter->type = 0;
						if (memtype_bios_matrix[iter->type] >= PMEMBANK_TYPE_COUNT)
							continue;
						minfo_addbank((physaddr_t)iter->addr,
						              (physaddr_t)iter->len,
						              memtype_bios_matrix[iter->type]);
					}
				}
				break;

			case MB2_TAG_TYPE_MODULE:
				if unlikely(TAG(mb2_tag_module)->mod_start >= TAG(mb2_tag_module)->mod_end)
					break;
				/* Preserve memory image of the driver file */
				minfo_addbank((physaddr_t)(TAG(mb2_tag_module)->mod_start),
				              (physaddr_t)(TAG(mb2_tag_module)->mod_end - TAG(mb2_tag_module)->mod_start),
				              PMEMBANK_TYPE_PRESERVE);
				/* Save the fact that MB2-compliant driver definitions are available. */
				if (x86_boot_driver_format == X86_BOOT_DRIVER_FORMAT_NONE) {
					x86_boot_driver_format = X86_BOOT_DRIVER_FORMAT_MB2;
					x86_boot_driver_base   = (byte_t *)tag_iter - KERNEL_CORE_BASE;
				}
				/* Remember the offset of the last driver tag, so we may enumerate
				 * them once  again  during  `x86_initialize_bootloader_drivers()' */
				x86_boot_driver_size = (size_t)((byte_t *)tag_end -
				                                ((byte_t *)x86_boot_driver_base +
				                                 KERNEL_CORE_BASE));
				break;

			case MB2_TAG_TYPE_BOOTDEV:
				boot_device.bdi_biosdev           = TAG(mb2_tag_bootdev)->biosdev & 0xff;
				boot_device.bdi_partition         = TAG(mb2_tag_bootdev)->partition & 0xff;
				boot_device.bdi_sub_partition     = TAG(mb2_tag_bootdev)->sub_partition & 0xff;
				boot_device.bdi_sub_sub_partition = 0xff;
				break;

			default:
				printk(FREESTR(KERN_WARNING "Unrecognized MB2 TAG: %" PRIu32 " (%#" PRIx32 ")\n"),
				       tag_iter->type, tag_iter->type);
				break;
			}
		} EXCEPT {
			except_printf(FREESTR("Loading MB2 tag at %p"),
			              tag_iter);
		}
	}
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_BOOT_MULTIBOOT_C */
