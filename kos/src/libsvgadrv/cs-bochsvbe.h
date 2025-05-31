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
#ifndef GUARD_LIBSVGADRV_CS_BOCHSVBE_H
#define GUARD_LIBSVGADRV_CS_BOCHSVBE_H 1

#include "api.h"
/**/

#ifdef CONFIG_HAVE_LIBSVGADRV_CHIPSET_BOCHSVBE
#include <kos/types.h>

#include <stdbool.h>

#include <libsvgadrv/chipset.h>
#include <libsvgadrv/chipsets/bochsvbe.h>

DECL_BEGIN

#ifndef __physaddr_t_defined
#define __physaddr_t_defined
typedef __physaddr_t physaddr_t; /* Physical memory address (== physpage_t * PAGESIZE) */
#endif /* !__physaddr_t_defined */

struct pci_device;
struct bochs_modeinfo: svga_modeinfo {
	uint8_t bmi_modeid; /* Index into the bochsvbe mode table. (or out-of-bounds for standard VGA) */
};

struct bochs_regs {
	uint16_t be_index;             /* Saved index stored in `VBE_DISPI_IOPORT_INDEX' */
	uint16_t be_saved_id;          /* [valid_if(VBE_DISPI_ENABLED)] Saved `VBE_DISPI_INDEX_ID' */
	uint16_t be_saved_xres;        /* [valid_if(VBE_DISPI_ENABLED)] Saved `VBE_DISPI_INDEX_XRES' */
	uint16_t be_saved_yres;        /* [valid_if(VBE_DISPI_ENABLED)] Saved `VBE_DISPI_INDEX_YRES' */
	uint16_t be_saved_bpp;         /* [valid_if(VBE_DISPI_ENABLED)] Saved `VBE_DISPI_INDEX_BPP' */
	uint16_t be_saved_enable;      /* Saved `VBE_DISPI_INDEX_ENABLE' */
	uint16_t be_saved_bank;        /* [valid_if(VBE_DISPI_ENABLED)] Saved `VBE_DISPI_INDEX_BANK' */
	uint16_t be_saved_virt_width;  /* [valid_if(VBE_DISPI_ENABLED)] Saved `VBE_DISPI_INDEX_VIRT_WIDTH' */
	uint16_t be_saved_virt_height; /* [valid_if(VBE_DISPI_ENABLED)] Saved `VBE_DISPI_INDEX_VIRT_HEIGHT' */
	uint16_t be_saved_x_offset;    /* [valid_if(VBE_DISPI_ENABLED)] Saved `VBE_DISPI_INDEX_X_OFFSET' */
	uint16_t be_saved_y_offset;    /* [valid_if(VBE_DISPI_ENABLED)] Saved `VBE_DISPI_INDEX_Y_OFFSET' */
};

struct bochs_chipset: svga_chipset {
	uint16_t           bc_maxresx;      /* [const] Max supported X resolution */
	uint16_t           bc_maxresy;      /* [const] Max supported Y resolution */
	uint16_t           bc_maxbpp;       /* [const] Max supported bpp */
	physaddr_t         bc_lfbaddr;      /* [const] Linear frame buffer address. */
	struct pci_device *bc_pci;          /* [0..1][const] Associated PCI device. */
#ifndef __KERNEL__
	void              *bc_libpciaccess; /* [0..1][const] dlopen(3D) handle for libpciaccess. */
#endif /* !__KERNEL__ */
};

/* Probe for VESA support.
 * @return: true:  Chipset found.
 * @return: false: Chipset isn't present. */
INTDEF WUNUSED NONNULL((1)) bool CC
cs_bochs_probe(struct svga_chipset *__restrict self);


/* VESA Chipset driver initializer. */
#define SVGA_CHIPSET_DRIVER_INIT_BOCHSVBE           \
	{                                               \
		.scd_cssize = sizeof(struct bochs_chipset), \
		.scd_probe  = &cs_bochs_probe,              \
		/* .scd_name = */ "bochsvbe",               \
	}

DECL_END
#endif /* CONFIG_HAVE_LIBSVGADRV_CHIPSET_BOCHSVBE */

#endif /* !GUARD_LIBSVGADRV_CS_BOCHSVBE_H */
