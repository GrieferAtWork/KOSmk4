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
#ifndef _HW_VIDEO_BOCHSVBE_H
#define _HW_VIDEO_BOCHSVBE_H 1

#include <__stdinc.h>

#include <bits/types.h>
#include <sys/io.h>

/* From: https://wiki.osdev.org/Bochs_VBE_Extensions */

/* Port numbers (16-bit; `VBE_DISPI_IOPORT_INDEX' takes one of `VBE_DISPI_INDEX_*') */
#define VBE_DISPI_IOPORT_INDEX __IOPORT(0x01CE) /* Register index port */
#define VBE_DISPI_IOPORT_DATA  __IOPORT(0x01CF) /* Register data port */

/* Index values for `VBE_DISPI_IOPORT_INDEX' */
#define VBE_DISPI_INDEX_ID               0x0000 /* rd: compatibility version; wr: requested version. (one of `VBE_DISPI_ID*') */
#define VBE_DISPI_INDEX_XRES             0x0001 /* [>= VBE_DISPI_ID0] Current screen resolution in X */
#define VBE_DISPI_INDEX_YRES             0x0002 /* [>= VBE_DISPI_ID0] Current screen resolution in Y */
#define VBE_DISPI_INDEX_BPP              0x0003 /* [>= VBE_DISPI_ID0] Current bits-per-pixel. (one of `VBE_DISPI_BPP_*') */
#define VBE_DISPI_INDEX_ENABLE           0x0004 /* [>= VBE_DISPI_ID0] Video chipset enable register (set of `VBE_DISPI_*') */
#define VBE_DISPI_INDEX_BANK             0x0005 /* [>= VBE_DISPI_ID0] Bank index when `VBE_DISPI_LFB_ENABLED' isn't set. */
#define VBE_DISPI_INDEX_VIRT_WIDTH       0x0006 /* [>= VBE_DISPI_ID1] Virtual display width (in pixels; iow: scanline pixel count) */
#define VBE_DISPI_INDEX_VIRT_HEIGHT      0x0007 /* [>= VBE_DISPI_ID1] Meaningless; only `VBE_DISPI_INDEX_YRES' matters */
#define VBE_DISPI_INDEX_X_OFFSET         0x0008 /* [>= VBE_DISPI_ID1] Display X offset (in pixels) */
#define VBE_DISPI_INDEX_Y_OFFSET         0x0009 /* [>= VBE_DISPI_ID1] Display Y offset (in pixels) */
#define VBE_DISPI_INDEX_VIDEO_MEMORY_64K 0x000a /* [>= ???] Video memory size in 64K blocks. (Known available under `VBE_DISPI_ID5') */

/* Values for `VBE_DISPI_INDEX_BPP' */
#define VBE_DISPI_BPP_PAL16     4 /* 16-bit color palette.
                                   * - Pixels go through `VGA_ATC_PALETTEn',  which
                                   *   indexes into `VGA_PEL_D' (`basevga_wrpal()')
                                   * - Every byte holds 2 pixels */
#define VBE_DISPI_BPP_PAL256    8 /* 256-bit color palette.
                                   * - Pixels indexes into `VGA_PEL_D' (`basevga_wrpal()')
                                   * - Every byte holds 1 pixels */
#define VBE_DISPI_BPP_BGR555   15 /* 5-5-5 true color.
                                   * - (u16 *)LFB = 0b0RRRRRGGGGGBBBBB;
                                   * - 2 bytes for every pixel. */
#define VBE_DISPI_BPP_BGR565   16 /* 5-6-5 true color.
                                   * - (u16 *)LFB = 0bRRRRRGGGGGGBBBBB;
                                   * - 2 bytes for every pixel. */
#define VBE_DISPI_BPP_BGR888   24 /* 8-8-8 true color.
                                   * - (u32 *)LFB = 0b________RRRRRRRRGGGGGGGGBBBBBBBB;  ('_' is data of another pixel)
                                   * - 3 bytes for every pixel. */
#define VBE_DISPI_BPP_BGRX8888 32 /* 8-8-8-X true color.
                                   * - (u32 *)LFB = 0b00000000RRRRRRRRGGGGGGGGBBBBBBBB;
                                   * - 4 bytes for every pixel. */


/* Values for `VBE_DISPI_INDEX_ID' */
#define VBE_DISPI_ID0 0xb0c0 /* setting X and Y resolution and bit depth (8 BPP only), banked mode */
#define VBE_DISPI_ID1 0xb0c1 /* virtual width and height, X and Y offset */
#define VBE_DISPI_ID2 0xb0c2 /* 15, 16, 24 and 32 BPP modes, support for linear frame buffer, support for retaining memory contents on mode switching */
#define VBE_DISPI_ID3 0xb0c3 /* support for getting capabilities, support for using 8 bit DAC */
#define VBE_DISPI_ID4 0xb0c4 /* VRAM increased to 8 MB */
#define VBE_DISPI_ID5 0xb0c5 /* VRAM increased to 16 MB */

/* Flags for `VBE_DISPI_INDEX_ENABLE' */
#define VBE_DISPI_DISABLED    0x0000 /* Chipset is disabled */
#define VBE_DISPI_ENABLED     0x0001 /* Chipset is enabled */
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
 *          ONLY  USE IF PCI DOESN'T KNOW THE DEVICE!
 * When a PCI device is found, `pd_regions[0]' should
 * point to physical memory  and be the actual  addr. */
#define VBE_DISPI_LFB_PHYSICAL_ADDRESS __UINT32_C(0xE0000000)

/* Bochs-VBE PCI IDs. (s.a. `/include/libpciaccess/pciaccess.h') */
#define VBE_DISPI_PCI_VENDOR_ID 0x1234 /* `struct pci_device::pd_vendor_id' */
#define VBE_DISPI_PCI_DEVICE_ID 0x1111 /* `struct pci_device::pd_device_id' */


/* Get/Set BGA (BochsGraphicsAdapter) registers. */
#ifdef __port_t
#ifdef __CC__
__DECL_BEGIN

#ifdef __USE_KOS_ALTERATIONS
#define __dispi_inw  inw
#define __dispi_outw outw
#else /* __USE_KOS_ALTERATIONS */
#define __dispi_inw             inw
#define __dispi_outw(port, val) outw(val, port)
#endif /* !__USE_KOS_ALTERATIONS */

__FORCELOCAL __ATTR_WUNUSED __uint16_t dispi_rdreg(__uint16_t __index) {
	__dispi_outw(VBE_DISPI_IOPORT_INDEX, __index);
	return __dispi_inw(VBE_DISPI_IOPORT_DATA);
}
__FORCELOCAL void dispi_wrreg(__uint16_t __index, __uint16_t __val) {
	__dispi_outw(VBE_DISPI_IOPORT_INDEX, __index);
	__dispi_outw(VBE_DISPI_IOPORT_DATA, __val);
}

__DECL_END
#endif /* __CC__ */
#endif /* __port_t */



#endif /* !_HW_VIDEO_BOCHSVBE_H */
