/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBSVGADRV_CS_VGA_H
#define GUARD_LIBSVGADRV_CS_VGA_H 1

#include "api.h"
/**/

#ifdef CONFIG_HAVE_LIBSVGADRV_CHIPSET_VGA
#include <kos/types.h>

#include <stdbool.h>

#include <libsvgadrv/chipset.h>
#include <libsvgadrv/chipsets/vga.h>

DECL_BEGIN

#ifndef __port_t_defined
#define __port_t_defined
typedef __port_t port_t;
#endif /* !__port_t_defined */

struct vga_chipset: svga_chipset {
	port_t gcs_crt_icX; /* Either `VGA_CRT_IC' or `VGA_CRT_IM' */

};

/************************************************************************/
/* Known VGA video modes                                                */
/************************************************************************/
struct vga_known_mode {
	struct svga_modeinfo vkm_info; /* Video mode info. */
	struct vga_mode      vkm_regs; /* VGA register states. */
};

/* Indices for `vga_modelist' */
#define CS_VGAMODE_TEXT        0
#define CS_VGAMODE_320X200X16  1
#define CS_VGAMODE_640X200X16  2
#define CS_VGAMODE_640X350X16  3
#define CS_VGAMODE_640X480X16  4
#define CS_VGAMODE_640X480X2   5
#define CS_VGAMODE_320X200X256 6
#define CS_VGAMODE_320X240X256 7
#define CS_VGAMODE_320X400X256 8
#define CS_VGAMODE_360X480X256 9
#define CS_VGAMODE_720X348X2   10
#define CS_VGAMODE_COUNT       11

/* Indices for `ega_modelist' */
#define CS_EGAMODE_TEXT       0
#define CS_EGAMODE_320X200X16 1
#define CS_EGAMODE_640X200X16 2
#define CS_EGAMODE_640X350X16 3
#define CS_EGAMODE_COUNT      4

/* List of supported VGA modes. */
INTDEF struct vga_known_mode const vga_modelist[CS_VGAMODE_COUNT];
INTDEF struct vga_known_mode const ega_modelist[CS_EGAMODE_COUNT];


/* Functions for use by other chipset drivers to include standard VGA modes as fallback.
 * For this purpose, `result' / `mode' for std-vga don't include any additional  fields. */
INTDEF WUNUSED NONNULL((1, 2, 3)) bool CC
vga_v_getmode(struct svga_chipset *__restrict UNUSED(self),
              struct svga_modeinfo *__restrict result,
              uintptr_t *__restrict p_index)
		THROWS(E_IOERROR);
INTDEF NONNULL((1, 2)) void CC
vga_v_setmode(struct svga_chipset *__restrict self,
              struct svga_modeinfo const *__restrict mode);


/* Probe for VGA support.
 * @return: true:  Chipset found.
 * @return: false: Chipset isn't present. */
INTDEF WUNUSED NONNULL((1)) bool CC
cs_vga_probe(struct svga_chipset *__restrict self);

/* VGA Chipset driver initializer. */
#define SVGA_CHIPSET_DRIVER_INIT_VGA              \
	{                                             \
		.scd_cssize = sizeof(struct vga_chipset), \
		.scd_probe  = &cs_vga_probe,              \
		/* .scd_name = */ "vga",                  \
	}

DECL_END
#endif /* CONFIG_HAVE_LIBSVGADRV_CHIPSET_VGA */

#endif /* !GUARD_LIBSVGADRV_CS_VGA_H */
