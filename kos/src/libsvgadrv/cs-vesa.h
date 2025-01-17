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
#ifndef GUARD_LIBSVGADRV_CS_VESA_H
#define GUARD_LIBSVGADRV_CS_VESA_H 1

#include "api.h"
/**/

#ifdef CONFIG_HAVE_LIBSVGADRV_CHIPSET_VESA
#include <stdbool.h>

#include <libbios86/bios.h>
#include <libsvgadrv/chipset.h>
#include <libsvgadrv/chipsets/vesa.h>

DECL_BEGIN

struct vesa_modeinfo: svga_modeinfo {
	struct vbe_modeinfo vm_vesa;   /* VESA mode information. */
	uint16_t            vm_modeid; /* VESA mode ID */
};

struct vesa_chipset: svga_chipset {
	struct vbe_modeinfo    vc_mode;         /* [lock(EXTERNAL)][valid_if(WAS_CALLED(sco_setmode))]
	                                         * VBE mode information  for the  current video  mode. */
	struct bios86_emulator vc_emu;          /* BIOS emulator. */
	struct vbe_biosinfo   *vc_info;         /* [const] VESA BIOS information. */
	uint16_t const        *vc_modelist;     /* [1..1][const] VESA mode info list. */
	uint16_t               vc_regsavebits;  /* [const] Set of registers to save/load in AX=4F04h (default to 0x0E;
	                                         * all except controller registers which  are standard across VGA  and
	                                         * normally saved by the caller) */
	shift_t                vc_wingranshift; /* [lock(EXTERNAL)] ilog2 of current mode window granularity */
#ifndef __KERNEL__
	/* libbios86 library bindings. */
	void                 *_vc_bios86;       /* [1..1][const] dlopen(3D) library binding */
	PBIOS86_EMULATOR_INT  _vc_bios86_int;   /* [1..1][const] Library function */
	PBIOS86_EMULATOR_FINI _vc_bios86_fini;  /* [1..1][const] Library function */
#endif /* !__KERNEL__ */
};

/* BIOS Buffer offsets (into `vc_emu.b86e_bios.b86_biosbase') */
#define VESA_CHIPSET_BIOSADDR_BIOSINFO (BIOS86_MEM_GPBAS + 0)                                                         /* struct vbe_biosinfo */
#define VESA_CHIPSET_BIOSADDR_MODEINFO (BIOS86_MEM_GPBAS + sizeof(struct vbe_biosinfo))                               /* struct vbe_modeinfo */
#define VESA_CHIPSET_BIOSADDR_REGBUF   (BIOS86_MEM_GPBAS + sizeof(struct vbe_biosinfo) + sizeof(struct vbe_modeinfo)) /* Register buffer */
#define vesa_chipset_biosaddr(self, offset) \
	((self)->vc_emu.b86e_bios.b86_biosbase + (offset))
#define vesa_farptr(self, seg, off) bios86_emulator_farptr(&(self)->vc_emu, seg, off)

#define vesa_chipset_get_oem_string(self)       ((char const *)vesa_farptr(self, (self)->vc_info->vbi_oem_string_seg, (self)->vc_info->vbi_oem_string_off))
#define vesa_chipset_get_oem_vendor_name(self)  ((char const *)vesa_farptr(self, (self)->vc_info->vbi_oem_vendor_name_seg, (self)->vc_info->vbi_oem_vendor_name_off))
#define vesa_chipset_get_oem_product_name(self) ((char const *)vesa_farptr(self, (self)->vc_info->vbi_oem_product_name_seg, (self)->vc_info->vbi_oem_product_name_off))
#define vesa_chipset_get_oem_product_rev(self)  ((char const *)vesa_farptr(self, (self)->vc_info->vbi_oem_product_rev_seg, (self)->vc_info->vbi_oem_product_rev_off))

/* Probe for VESA support.
 * @return: true:  Chipset found.
 * @return: false: Chipset isn't present. */
INTDEF WUNUSED NONNULL((1)) bool CC
cs_vesa_probe(struct svga_chipset *__restrict self);


/* VESA Chipset driver initializer. */
#define SVGA_CHIPSET_DRIVER_INIT_VESA              \
	{                                              \
		.scd_cssize = sizeof(struct vesa_chipset), \
		.scd_probe  = &cs_vesa_probe,              \
		/* .scd_name = */ "vesa",                  \
	}

DECL_END
#endif /* CONFIG_HAVE_LIBSVGADRV_CHIPSET_VESA */

#endif /* !GUARD_LIBSVGADRV_CS_VESA_H */
