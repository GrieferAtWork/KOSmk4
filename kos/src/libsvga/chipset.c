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
#ifndef GUARD_LIBSVGA_CHIPSET_C
#define GUARD_LIBSVGA_CHIPSET_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <kos/kernel/types.h>
#include <kos/types.h>

#include <stddef.h>

#include <libsvga/chipset.h>

#include "chipset.h"

/* Include headers of supported chipset drivers. */
#ifdef CONFIG_SVGA_HAVE_CHIPSET_VESA
#include "cs-vesa.h"
#endif /* CONFIG_SVGA_HAVE_CHIPSET_VESA */

DECL_BEGIN


/* List of supported drivers. - Keep sorted most-specific to most-generic. */
PRIVATE struct svga_chipset_driver svga_drivers[] = {
#ifdef CONFIG_SVGA_HAVE_CHIPSET_VESA
	SVGA_CHIPSET_DRIVER_INIT_VESA,
#endif /* CONFIG_SVGA_HAVE_CHIPSET_VESA */
	{ 0, NULL },
};


/* Return the list of supported VGA chipset drivers (terminated by a bzero'd entry)
 * This list is sorted from most specific- to most generic driver. As such, some of
 * the later drivers might also  be usable even when one  of the former ones  could
 * also be used.
 *
 * As such, when probing for devices you should simply iterate this list until you
 * find a driver  for which probing  succeeds. Once that  happens, simply keep  on
 * using that driver. */
DEFINE_PUBLIC_ALIAS(svga_chipset_getdrivers, libsvga_chipset_getdrivers);
INTERN ATTR_PURE ATTR_RETNONNULL WUNUSED struct svga_chipset_driver const *
NOTHROW(CC libsvga_chipset_getdrivers)(void) {
	COMPILER_IMPURE();
	return svga_drivers;
}


/************************************************************************/
/* TESTING / PLAYING AROUND FROM HERE ON!!!                             */
/************************************************************************/

#include <kos/except.h>
#include <kos/kernel/printk.h>

#include <alloca.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>


PRIVATE NONNULL((2, 3)) ssize_t LIBSVGA_CC
svga_chipset_enumstring_print_cb(void *arg,
                                 char const *__restrict name,
                                 char const *__restrict value) {
	struct svga_chipset_driver const *driver;
	driver = (struct svga_chipset_driver const *)arg;
	printk(KERN_INFO "[svga] %s.%s: %q\n", driver->scd_name, name, value);
	return 0;
}

INTERN void libsvga_init(void) {
	struct svga_chipset_driver const *drivers;
	size_t i, max_bufsize;
	uintptr_t modeid;
	struct svga_chipset *cs;
	struct svga_modeinfo *mode;
	drivers = libsvga_chipset_getdrivers();
	max_bufsize = 0;
	for (i = 0; drivers[i].scd_probe; ++i) {
		if (max_bufsize < drivers[i].scd_cssize)
			max_bufsize = drivers[i].scd_cssize;
	}
	cs = (struct svga_chipset *)alloca(max_bufsize);
	for (i = 0;; ++i) {
		if (!drivers[i].scd_probe) {
			printk(KERN_DEBUG "[svga] No supported chipset detected\n");
			return;
		}
		if ((*drivers[i].scd_probe)(cs))
			break;
	}
	RAII_FINALLY { (*cs->sc_ops.sco_fini)(cs); };
	svga_chipset_write(cs);
	RAII_FINALLY { svga_chipset_endwrite(cs); };

	/* Enumerate driver-specific strings. */
	if (cs->sc_ops.sco_strings)
		(*cs->sc_ops.sco_strings)(cs, &svga_chipset_enumstring_print_cb, (void *)&drivers[i]);

	/* Enumerate supported modes. */
	mode = (struct svga_modeinfo *)alloca(cs->sc_ops.sco_modeinfosize);
	for (modeid = 0; (*cs->sc_ops.sco_getmode)(cs, mode, &modeid);) {
		char modenamebuf[64];
		char flagsbuf[64] = "", *ptr = flagsbuf;
		if (mode->smi_flags & SVGA_MODEINFO_F_LFB)
			ptr = stpcpy(ptr, "|lfb");
		if (mode->smi_flags & SVGA_MODEINFO_F_PAL)
			ptr = stpcpy(ptr, "|pal");
		if (mode->smi_flags & SVGA_MODEINFO_F_BW)
			ptr = stpcpy(ptr, "|bw");
		sprintf(modenamebuf, "%" PRIu32 "x%" PRIu32 "x%" PRIu8,
		        mode->smi_resx, mode->smi_resy, mode->smi_bits_per_pixel);

		printk(KERN_INFO "[svga] Supported: %-12s {flags:%s",
		       modenamebuf, flagsbuf + 1);
		if (mode->smi_flags & SVGA_MODEINFO_F_LFB) {
			printk(KERN_INFO ",lfb:%#" PRIx64, (uint64_t)mode->smi_lfb);
		} else {
			printk(KERN_INFO ",vpage:%#" PRIxSIZ, mode->smi_vpagesiz);
		}
		printk(KERN_INFO ",scan:%" PRIu32 ",col:%" PRIu8,
		       mode->smi_scanline, mode->smi_colorbits);
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
}

DECL_END

#endif /* !GUARD_LIBSVGA_CHIPSET_C */
