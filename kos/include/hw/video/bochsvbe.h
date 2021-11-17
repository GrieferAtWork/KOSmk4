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
#ifndef _HW_VIDEO_BOCHSVBE_H
#define _HW_VIDEO_BOCHSVBE_H 1

#include <__stdinc.h>

#include <bits/types.h>
#include <sys/io.h>

/* From: https://wiki.osdev.org/Bochs_VBE_Extensions */

/* TODO: defines for backing PCI device IDs */

/* Port numbers (16-bit; `VBE_DISPI_IOPORT_INDEX' takes one of `VBE_DISPI_INDEX_*') */
#define VBE_DISPI_IOPORT_INDEX __IOPORT(0x01CE) /* Register index port */
#define VBE_DISPI_IOPORT_DATA  __IOPORT(0x01CF) /* Register data port */

/* Index values for `VBE_DISPI_IOPORT_INDEX' */
#define VBE_DISPI_INDEX_ID               0  /* rd: compatibility version; wr: requested version. (one of `VBE_DISPI_ID*') */
#define VBE_DISPI_INDEX_XRES             1  /* [>= VBE_DISPI_ID0] TODO: Doc */
#define VBE_DISPI_INDEX_YRES             2  /* [>= VBE_DISPI_ID0] TODO: Doc */
#define VBE_DISPI_INDEX_BPP              3  /* [>= VBE_DISPI_ID0] TODO: Doc */
#define VBE_DISPI_INDEX_ENABLE           4  /* [>= VBE_DISPI_ID0] Video chipset enable register (set of `VBE_DISPI_*') */
#define VBE_DISPI_INDEX_BANK             5  /* [>= VBE_DISPI_ID0] TODO: Doc */
#define VBE_DISPI_INDEX_VIRT_WIDTH       6  /* [>= VBE_DISPI_ID1] Virtual display width (in pixels; iow: scanline pixel count) */
#define VBE_DISPI_INDEX_VIRT_HEIGHT      7  /* [>= VBE_DISPI_ID1] Meaningless; only `VBE_DISPI_INDEX_YRES' matters */
#define VBE_DISPI_INDEX_X_OFFSET         8  /* [>= VBE_DISPI_ID1] Display X offset (in pixels) */
#define VBE_DISPI_INDEX_Y_OFFSET         9  /* [>= VBE_DISPI_ID1] Display Y offset (in pixels) */
#define VBE_DISPI_INDEX_VIDEO_MEMORY_64K 10 /* [>= ???] Video memory size in 64K blocks. */

/* Values for `VBE_DISPI_INDEX_ID' */
#define VBE_DISPI_ID0 0xb0c0 /* setting X and Y resolution and bit depth (8 BPP only), banked mode */
#define VBE_DISPI_ID1 0xb0c1 /* virtual width and height, X and Y offset */
#define VBE_DISPI_ID2 0xb0c2 /* 15, 16, 24 and 32 BPP modes, support for linear frame buffer, support for retaining memory contents on mode switching */
#define VBE_DISPI_ID3 0xb0c3 /* support for getting capabilities, support for using 8 bit DAC */
#define VBE_DISPI_ID4 0xb0c4 /* VRAM increased to 8 MB */
#define VBE_DISPI_ID5 0xb0c5 /* VRAM increased to 16 MB */

/* Flags for `VBE_DISPI_INDEX_ENABLE' */
#define VBE_DISPI_DISABLED    0x0000 /* Chipset is disabled */
#define VBE_DISPI_ENABLED     0x0001 /* Chipset is enaled */
#define VBE_DISPI_GETCAPS     0x0002 /* When set, all VBE_DISPI_INDEX_XRES, VBE_DISPI_INDEX_YRES and VBE_DISPI_INDEX_BPP return max supported values. */
/*      VBE_DISPI_            0x0004  */
/*      VBE_DISPI_            0x0008  */
/*      VBE_DISPI_            0x0010  */
#define VBE_DISPI_8BIT_DAC    0x0020 /* ??? */
#define VBE_DISPI_LFB_ENABLED 0x0040 /* Linear frame buffer is enabled */
#define VBE_DISPI_NOCLEARMEM  0x0080 /* Don't clear memory when changing video modes. */
/*      VBE_DISPI_            0x0100  */
/*      VBE_DISPI_            0x0200  */
/*      VBE_DISPI_            0x0400  */
/*      VBE_DISPI_            0x0800  */
/*      VBE_DISPI_            0x1000  */
/*      VBE_DISPI_            0x2000  */
/*      VBE_DISPI_            0x4000  */
/*      VBE_DISPI_            0x8000  */

/* Default physical address of linear frame buffer.
 * WARNING: MAY (AND PROBABLY IS) OVERWRITTEN BY PCI!
 *          ONLY  USE IF PCI DOESN'T KNOW THE DEVICE! */
#define VBE_DISPI_LFB_PHYSICAL_ADDRESS __UINT32_C(0xE0000000)

/* Get/Set BGA (BochsGraphicsAdapter) registers. */
#ifdef __CC__
__DECL_BEGIN

#ifdef __USE_KOS_ALTERATIONS
#define __bga_inw  inw
#define __bga_outw outw
#else /* __USE_KOS_ALTERATIONS */
#define __bga_inw             inw
#define __bga_outw(port, val) outw(val, port)
#endif /* !__USE_KOS_ALTERATIONS */

__FORCELOCAL __ATTR_WUNUSED __uint16_t bga_rdreg(__uint16_t __index) {
	__bga_outw(VBE_DISPI_IOPORT_INDEX, __index);
	return __bga_inw(VBE_DISPI_IOPORT_DATA);
}
__FORCELOCAL void bga_wrreg(__uint16_t __index, __uint16_t __val) {
	__bga_outw(VBE_DISPI_IOPORT_INDEX, __index);
	__bga_outw(VBE_DISPI_IOPORT_DATA, __val);
}

__DECL_END
#endif /* __CC__ */



#endif /* !_HW_VIDEO_BOCHSVBE_H */
