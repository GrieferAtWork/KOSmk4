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

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/printk.h>

/**/
#include "svga.h"

DECL_BEGIN




/************************************************************************/
/* TESTING / PLAYING AROUND FROM HERE ON!!!                             */
/************************************************************************/

#include <kos/except.h>

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


PRIVATE ATTR_FREETEXT DRIVER_INIT void KCALL svga_testing(void) {
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
	printk(KERN_DEBUG "[svga] Chipset detected: %q\n", drivers[i].scd_name);
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
}

DECL_END

#endif /* !GUARD_MODSVGA_SVGA_C */
