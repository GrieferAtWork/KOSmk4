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
#ifndef GUARD_MODSVGA_SVGA_C
#define GUARD_MODSVGA_SVGA_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver-param.h>
#include <kernel/driver.h>
#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/printk.h>

#include <hybrid/align.h>

#include <kos/except.h>
#include <sys/mkdev.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libsvgadrv/chipset.h>

/**/
#include "svga.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


PRIVATE ATTR_FREETEXT NONNULL((2, 3)) ssize_t LIBSVGADRV_CC
svga_init_enumstring_callback(void *arg,
                              char const *__restrict name,
                              char const *__restrict value) {
	struct svga_chipset_driver const *driver;
	driver = (struct svga_chipset_driver const *)arg;
	printk(FREESTR(KERN_INFO "[svga] Chipset string %s.%s: %q\n"),
	       driver->scd_name, name, value);
	return 0;
}


/* Default graphics mode hints.
 *
 * Note that modes can always be switched via ioctl(2).
 * These are on hints used to select the initial  mode. */
DEFINE_CMDLINE_PARAM_UINT32_VAR(default_resx, "xres", 1280);
DEFINE_CMDLINE_PARAM_UINT32_VAR(default_resy, "yres", 768);
DEFINE_CMDLINE_PARAM_UINT8_VAR(default_bpp, "bpp", 8);


PRIVATE NOBLOCK ATTR_FREETEXT ATTR_PURE WUNUSED NONNULL((1)) uint64_t
NOTHROW(FCALL calculate_mode_cost)(struct svga_modeinfo const *__restrict mode,
                                   uint32_t xres, uint32_t yres, uint8_t bpp) {
	uint64_t result = 0;
	int32_t real_mode_resx;
	int32_t real_mode_resy;
	real_mode_resx = (int32_t)mode->smi_resx;
	real_mode_resy = (int32_t)mode->smi_resy;
	if (mode->smi_flags & SVGA_MODEINFO_F_TXT) {
		real_mode_resx *= 9;
		real_mode_resy *= 16;
	}
	result += abs((int32_t)xres - real_mode_resx);
	result += abs((int32_t)yres - real_mode_resy);
	result += abs((int8_t)bpp - (int8_t)mode->smi_bits_per_pixel);
	if (mode->smi_bits_per_pixel > 32)
		return (uint64_t)-1; /* We only support BPP up to 32-bit! */
#if 1 /* TODO: 4-bit mode */
	if (mode->smi_bits_per_pixel == 4)
		return (uint64_t)-1;
#endif
	return result;
}

PRIVATE NOBLOCK ATTR_FREETEXT ATTR_RETNONNULL ATTR_PURE WUNUSED NONNULL((1)) struct svga_modeinfo const *
NOTHROW(FCALL select_closest_video_mode)(struct svgadev *__restrict self,
                                         uint32_t xres, uint32_t yres, uint8_t bpp) {
	size_t i;
	uint64_t winner_cost;
	struct svga_modeinfo const *winner;
	winner      = svgadev_supmode(self, 0);
	winner_cost = calculate_mode_cost(winner, xres, yres, bpp);
	for (i = 1; i < self->svd_supmodec; ++i) {
		struct svga_modeinfo const *mode;
		uint64_t cost;
		mode = svgadev_supmode(self, i);
		cost = calculate_mode_cost(mode, xres, yres, bpp);
		if (winner_cost > cost) {
			winner_cost = cost;
			winner      = mode;
		}
	}
	return winner;
}

PRIVATE NOBLOCK ATTR_FREETEXT ATTR_RETNONNULL ATTR_PURE WUNUSED NONNULL((1)) struct svga_modeinfo const *
NOTHROW(FCALL get_default_video_mode)(struct svgadev *__restrict self) {
	return select_closest_video_mode(self, default_resx, default_resy, default_bpp);
}


#ifdef BUILDING_KERNEL_CORE
INTERN ATTR_FREETEXT void KCALL kernel_initialize_svga_driver(void)
#else /* BUILDING_KERNEL_CORE */
PRIVATE ATTR_FREETEXT DRIVER_INIT void KCALL svga_init(void)
#endif /* !BUILDING_KERNEL_CORE */
{
	struct svgadev *self;
	struct svga_chipset_driver const *drivers;
	size_t i, maxsize;

	/* Initialize the base-VGA system. */
	basevga_init();

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

			/* Free unused memory. (Use *_in_place because init by `scd_probe()' mustn't be relocated) */
			self = (struct svgadev *)krealloc_in_place(self,
			                                           offsetof(struct svgadev, svd_chipset) +
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
				iterator = 0;
				for (;;) {
					struct svga_modeinfo *mode;
					size_t j, avail, used;
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
again_load_mode:
					mode = (struct svga_modeinfo *)((byte_t *)modev + used);
					if (!(*self->svd_chipset.sc_ops.sco_getmode)(&self->svd_chipset, mode, &iterator))
						break; /* Done! */

					/* Safety check if a duplicate mode already exists.
					 * For  this purpose, we  only compare non-chipset-specific fields!
					 * This is necessary since user-space  selects modes based on  only
					 * these public fields, and if multiple modes with identical fields
					 * were to exist, that would create ambiguity. */
					for (j = 0; j < modec; ++j) {
						struct svga_modeinfo *oldmode;
						oldmode = (struct svga_modeinfo *)((byte_t *)modev +
						                                   (j * self->svd_chipset.sc_ops.sco_modeinfosize));
						if (bcmp(mode, oldmode, sizeof(struct svga_modeinfo)) == 0)
							goto again_load_mode;
					}
					++modec; /* Remember that we've got another mode now! */
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

				/* Select the default video mode. */
				self->svd_defmode = get_default_video_mode(self);

				/* Initialize underlying video device. */
				_viddev_init(self, &svgadev_ops);

				/* Fill in remaining fields. */
				self->fn_mode   = S_IFCHR | 0600;
				self->dv_driver = incref(&drv_self);

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
				/* Allocate+initialize a tty for the builtin debugger. */
				svgadev_dbg_init(self);
				TRY
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
				{
					/* Register the device. */
					TRY {
						device_registerf(self,
						                 makedev(MKDEV_MAJOR_AUTO, 0),
						                 "svga");
					} EXCEPT {
						decref_nokill(&drv_self);
						RETHROW();
					}
				}
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
				EXCEPT {
					svgadev_dbg_fini(self);
					RETHROW();
				}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
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

	/* If none has already been defined, remember `self' as the default video adapter. */
	axref_cmpxch(&viddev_default, NULL, self);
	decref_unlikely(self);
}


DECL_END

#endif /* !GUARD_MODSVGA_SVGA_C */
