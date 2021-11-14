/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODSVGA_SVGA_C
#define GUARD_MODSVGA_SVGA_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/memory.h>
#include <kernel/mman.h>
#include <kernel/mman/sync.h>
#include <kernel/mman/unmapped.h>
#include <kernel/printk.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <kos/except.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libsvga/api.h>
#include <libsvga/chipset.h>
#include <libsvga/util/vgaio.h>

/**/
#include "svga.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


PRIVATE ATTR_FREETEXT NONNULL((2, 3)) ssize_t LIBSVGA_CC
svga_init_enumstring_callback(void *arg,
                              char const *__restrict name,
                              char const *__restrict value) {
	struct svga_chipset_driver const *driver;
	driver = (struct svga_chipset_driver const *)arg;
	printk(FREESTR(KERN_INFO "[svga] Chipset string %s.%s: %q\n"),
	       driver->scd_name, name, value);
	return 0;
}

#ifdef CONFIG_BUILDING_KERNEL_CORE
INTERN ATTR_FREETEXT void KCALL kernel_initialize_svga_driver(void)
#else /* CONFIG_BUILDING_KERNEL_CORE */
PRIVATE ATTR_FREETEXT DRIVER_INIT void KCALL svga_init(void)
#endif /* !CONFIG_BUILDING_KERNEL_CORE */
{
	struct svgadev *self;
	struct svga_chipset_driver const *drivers;
	size_t i, maxsize;

	/* Load available chipset drivers. */
	drivers = libsvga_chipset_getdrivers();

	/* Figure out the max required struct size for chipsets. */
	maxsize = 0;
	for (i = 0; drivers[i].scd_probe; ++i) {
		if (maxsize < drivers[i].scd_cssize)
			maxsize = drivers[i].scd_cssize;
	}

	/* Allocate an SVGA device buffer that is large enough to support any driver. */
	maxsize += offsetof(struct svgadev, svd_chipset);
	self = (struct svgadev *)kmalloc(maxsize, GFP_NORMAL);
	TRY {
		/* Go through the list of chipsets and probe for each of them. */
		for (i = 0;; ++i) {
			if unlikely(!drivers[i].scd_probe) {
				printk(FREESTR(KERN_ERR "[svga] No supported chipset detected\n"));
				kfree(self);
				return;
			}
			if ((*drivers[i].scd_probe)(&self->svd_chipset))
				break; /* Found one! */
		}
		TRY {
			byte_t *modev;
			size_t modec;

			/* Free unused memory. */
			self = (struct svgadev *)krealloc_in_place(self,
			                                               offsetof(struct svgadev, svd_chipset)+
			                                               drivers[i].scd_cssize,
			                                               GFP_NORMAL);

			self->svd_csdriver = &drivers[i];
			printk(FREESTR(KERN_INFO "[svga] Video chipset detected: %s\n"),
			       self->svd_csdriver->scd_name);

			/* Print chipset-specific strings. */
			if (self->svd_chipset.sc_ops.sco_strings) {
				(*self->svd_chipset.sc_ops.sco_strings)(&self->svd_chipset,
				                                      &svga_init_enumstring_callback,
				                                      (void *)self->svd_csdriver);
			}

			/* Found the chipset. - Now to enumerate all of its supported video modes. */
			self->svd_supmodeS = self->svd_chipset.sc_ops.sco_modeinfosize;
			self->svd_supmodeS = CEIL_ALIGN(self->svd_supmodeS, sizeof(void *));

			modec = 0;
			modev = (byte_t *)kmalloc_nx(32 * self->svd_supmodeS, GFP_NORMAL);
			if (!modev)
				modev = (byte_t *)kmalloc(self->svd_supmodeS, GFP_NORMAL);
			TRY {
				uintptr_t iterator;

				/* Might not make much sense to force a lock here, but it's part of the contract... */
				svga_chipset_write(&self->svd_chipset);
				RAII_FINALLY { svga_chipset_endwrite(&self->svd_chipset); };

				iterator = 0;
				for (;;) {
					struct svga_modeinfo *mode;
					size_t avail, used;
					used  = modec * self->svd_supmodeS;
					avail = kmalloc_usable_size(modev);
					avail -= used;
					if (avail < self->svd_chipset.sc_ops.sco_modeinfosize) {
						byte_t *new_modev;
						avail = kmalloc_usable_size(modev) * 2;
						new_modev = (byte_t *)krealloc_nx(modev, avail, GFP_NORMAL);
						if unlikely(!new_modev) {
							size_t needed;
							needed = used;
							needed += self->svd_chipset.sc_ops.sco_modeinfosize;
							new_modev = (byte_t *)krealloc(modev, needed, GFP_NORMAL);
						}
						modev = new_modev;
					}

					/* Query mode information. */
					mode = (struct svga_modeinfo *)((byte_t *)modev + used);
					if (!(*self->svd_chipset.sc_ops.sco_getmode)(&self->svd_chipset, mode, &iterator))
						break; /* Done! */
					++modec; /* Remember that we've got another mode now! */

#if !defined(NDEBUG) && 1 /* XXX: Remove me */
					{
						char modenamebuf[64];
						char flagsbuf[64] = "", *ptr = flagsbuf;
						if (mode->smi_flags & SVGA_MODEINFO_F_LFB)
							ptr = stpcpy(ptr, "|lfb");
						if (mode->smi_flags & SVGA_MODEINFO_F_PAL)
							ptr = stpcpy(ptr, "|pal");
						if (mode->smi_flags & SVGA_MODEINFO_F_BW)
							ptr = stpcpy(ptr, "|bw");
						if (mode->smi_flags & SVGA_MODEINFO_F_TXT)
							ptr = stpcpy(ptr, "|txt");
						if (mode->smi_flags & SVGA_MODEINFO_F_PLANAR)
							ptr = stpcpy(ptr, "|planar");
						sprintf(modenamebuf, "%" PRIu32 "x%" PRIu32 "x%" PRIu8,
						        mode->smi_resx, mode->smi_resy, mode->smi_bits_per_pixel);

						printk(KERN_INFO "[svga] Supported: %-12s {flags:%s",
						       modenamebuf, flagsbuf + 1);
						if (mode->smi_flags & SVGA_MODEINFO_F_LFB)
							printk(KERN_INFO ",lfb:%#" PRIx64, (uint64_t)mode->smi_lfb);
						printk(KERN_INFO ",scan:%" PRIu32, mode->smi_scanline);
						if (!(mode->smi_flags & SVGA_MODEINFO_F_TXT))
							printk(KERN_INFO ",col:%" PRIu8, mode->smi_colorbits);
						if (!(mode->smi_flags & (SVGA_MODEINFO_F_PAL | SVGA_MODEINFO_F_BW))) {
							printk(KERN_INFO ",r:%" PRIu8 "@%" PRIu8
							                 ",g:%" PRIu8 "@%" PRIu8
							                 ",b:%" PRIu8 "@%" PRIu8,
							       mode->smi_rbits, mode->smi_rshift,
							       mode->smi_gbits, mode->smi_gshift,
							       mode->smi_bbits, mode->smi_bshift);
						}
						printk(KERN_INFO "}\n");
					}
#endif
				}

				/* Verify that we've got at least 1 mode. */
				if unlikely(!modec) {
					printk(FREESTR(KERN_ERR "[svga] No supported video modes detected?\n"));
					THROW(E_IOERROR);
				}

				/* Save the mode list. */
				self->svd_supmodec = modec;
				self->svd_supmodev = modev;

				/* Release unused memory from the modes list. */
				--modec;
				modec *= self->svd_supmodeS;
				modec += self->svd_chipset.sc_ops.sco_modeinfosize;
				modev = (byte_t *)krealloc_nx(modev, modec, GFP_NORMAL);
				if likely(modev != NULL)
					self->svd_supmodev = modev;

				/* By default, nothing is active. */
				awref_init(&self->svd_active, NULL);

				/* Initialize underlying device objects. */
				_chrdev_init(self, &svgadev_ops);

				/* Fill in remaining fields. */
				self->fn_mode   = S_IFCHR | 0600;
				self->dv_driver = incref(&drv_self);

				/* Register the device. */
				TRY {
					device_registerf(self, MKDEV(DEV_MAJOR_AUTO, 0), "svga");
				} EXCEPT {
					decref_nokill(&drv_self);
					RETHROW();
				}
			} EXCEPT {
				kfree(modev);
				RETHROW();
			}
		} EXCEPT {
			(*self->svd_chipset.sc_ops.sco_fini)(&self->svd_chipset);
			RETHROW();
		}
	} EXCEPT {
		kfree(self);
		RETHROW();
	}
}


DECL_END

#endif /* !GUARD_MODSVGA_SVGA_C */
