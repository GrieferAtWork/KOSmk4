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
#ifndef _HW_VIDEO_VMWARE_H
#define _HW_VIDEO_VMWARE_H 1

#include <__stdinc.h>

/* Documentation derived from:
 * >> /vmware-svga-svn-r32-trunk/lib/vmware/svga_reg.h
 *
 * See also the following copyright */
/**********************************************************
 * Copyright 1998-2009 VMware, Inc.  All rights reserved.
 *
 * Permission is  hereby  granted,  free of  charge,  to  any  person
 * obtaining a  copy of  this software  and associated  documentation
 * files  (the  "Software"),   to  deal  in   the  Software   without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of  the Software,  and to permit  persons to whom  the Software is
 * furnished  to  do  so,   subject  to  the  following   conditions:
 *
 * The above copyright notice and this permission notice shall  be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS  PROVIDED "AS IS", WITHOUT  WARRANTY OF ANY  KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN  AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE,  ARISING FROM, OUT OF OR  IN
 * CONNECTION  WITH THE SOFTWARE  OR THE USE OR  OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **********************************************************/




/* VMWare PCI IDs. (s.a. `/include/libpciaccess/pciaccess.h') */
#define PCI_VENDOR_ID_VMWARE       0x15ad /* `struct pci_device::pd_vendor_id' */
#define PCI_DEVICE_ID_VMWARE_SVGA2 0x0405 /* `struct pci_device::pd_device_id' */

/* Port offsets, relative to BAR0 */
#define SVGA_INDEX_PORT     0x0
#define SVGA_VALUE_PORT     0x1
#define SVGA_BIOS_PORT      0x2


/* Internal registers */

/* ID 0, 1 and 2 registers */
#define SVGA_REG_ID             0  /* [rw] Specification ID */
#   define SVGA_MAGIC         0x900000UL
#   define SVGA_MAKE_ID(ver)  (SVGA_MAGIC << 8 | (ver))
#   define SVGA_ID_2          SVGA_MAKE_ID(2) /* Version 2 let the address of the frame buffer be unsigned on Win32 */
#   define SVGA_ID_1          SVGA_MAKE_ID(1) /* Version 1 has new registers starting with SVGA_REG_CAPABILITIES so PALETTE_BASE has moved */
#   define SVGA_ID_0          SVGA_MAKE_ID(0) /* Version 0 is the initial version */
#define SVGA_REG_ENABLE         1  /* flag set by the driver when the device should enter SVGA mode */
#   define SVGA_REG_ENABLE_DISABLE     0
#   define SVGA_REG_ENABLE_ENABLE      1
#   define SVGA_REG_ENABLE_HIDE        2
#   define SVGA_REG_ENABLE_ENABLE_HIDE (SVGA_REG_ENABLE_ENABLE | SVGA_REG_ENABLE_HIDE)
#define SVGA_REG_WIDTH          2  /* [rw] current screen width */
#define SVGA_REG_HEIGHT         3  /* [rw] current screen height */
#define SVGA_REG_MAX_WIDTH      4  /* [ro] maximum supported screen width */
#define SVGA_REG_MAX_HEIGHT     5  /* [ro] maximum supported screen height */
#define SVGA_REG_DEPTH          6  /* [rw] ??? (QEMU ignores writes; returns "SVGA_REG_BPP == 32 ? 24 : SVGA_REG_BPP") */
#define SVGA_REG_BPP            7  /* [rw] current screen bits per pixel (NOTE: QEMU only supports "32") */
#define SVGA_REG_PSEUDOCOLOR    8  /* [ro] ??? (Always reads as "0" in QEMU) */
#define SVGA_REG_RED_MASK       9  /* [ro] PDEP bits for the red-part of a pixel */
#define SVGA_REG_GREEN_MASK     10 /* [ro] PDEP bits for the green-part of a pixel */
#define SVGA_REG_BLUE_MASK      11 /* [ro] PDEP bits for the blue-part of a pixel */
#define SVGA_REG_BYTES_PER_LINE 12 /* [ro] Scanline */
#define SVGA_REG_FB_START       13 /* [ro] Address in system memory of the frame buffer */
#define SVGA_REG_FB_OFFSET      14 /* [ro] Offset in the frame buffer to the visible pixel data (may change when resoluation changes) */
#define SVGA_REG_VRAM_SIZE      15 /* [ro] Size of the video RAM */

/* ID 1 and 2 registers */
#define SVGA_REG_FB_SIZE             16 /* [ro] size of the frame buffer */
#define SVGA_REG_CAPABILITIES        17 /* [ro] device capabilities */
#   define SVGA_CAP_NONE             0x00000000
#   define SVGA_CAP_RECT_FILL        0x00000001 /* QEMU */
#   define SVGA_CAP_RECT_COPY        0x00000002 /* QEMU */
#   define SVGA_CAP_RECT_PAT_FILL    0x00000004
#   define SVGA_CAP_LEGACY_OFFSCREEN 0x00000008
#   define SVGA_CAP_RASTER_OP        0x00000010
#   define SVGA_CAP_CURSOR           0x00000020 /* QEMU */
#   define SVGA_CAP_CURSOR_BYPASS    0x00000040 /* QEMU -- Legacy (Use Cursor Bypass 3 instead) */
#   define SVGA_CAP_CURSOR_BYPASS_2  0x00000080 /* QEMU -- Legacy (Use Cursor Bypass 3 instead) */
#   define SVGA_CAP_8BIT_EMULATION   0x00000100
#   define SVGA_CAP_ALPHA_CURSOR     0x00000200
#   define SVGA_CAP_GLYPH            0x00000400
#   define SVGA_CAP_GLYPH_CLIPPING   0x00000800
#   define SVGA_CAP_OFFSCREEN_1      0x00001000
#   define SVGA_CAP_ALPHA_BLEND      0x00002000
#   define SVGA_CAP_3D               0x00004000
#   define SVGA_CAP_EXTENDED_FIFO    0x00008000
#   define SVGA_CAP_MULTIMON         0x00010000 /* Legacy multi-monitor support */
#   define SVGA_CAP_PITCHLOCK        0x00020000
#   define SVGA_CAP_IRQMASK          0x00040000
#   define SVGA_CAP_DISPLAY_TOPOLOGY 0x00080000 /* Legacy multi-monitor support */
#   define SVGA_CAP_GMR              0x00100000
#   define SVGA_CAP_TRACES           0x00200000
#   define SVGA_CAP_GMR2             0x00400000
#   define SVGA_CAP_SCREEN_OBJECT_2  0x00800000
#define SVGA_REG_MEM_START           18 /* [ro] Address in system memory of the FIFO */
#define SVGA_REG_MEM_SIZE            19 /* [ro] FIFO size (in bytes) */
#define SVGA_REG_CONFIG_DONE         20 /* [rw] flag to enable FIFO operation (0/1) */
#define SVGA_REG_SYNC                21 /* [rw] flag set by the driver to flush FIFO changes */
#define SVGA_REG_BUSY                22 /* [ro] flag set by the FIFO when it's processed */
#define SVGA_REG_GUEST_ID            23 /* [rw] */
#   define SVGA_REG_GUEST_DOS          0x00
#   define SVGA_REG_GUEST_WINDOWS_3_1  0x01
#   define SVGA_REG_GUEST_WINDOWS_95   0x02
#   define SVGA_REG_GUEST_WINDOWS_98   0x03
#   define SVGA_REG_GUEST_WINDOWS_ME   0x04
#   define SVGA_REG_GUEST_WINDOWS_NT   0x05
#   define SVGA_REG_GUEST_WINDOWS_2000 0x06
#   define SVGA_REG_GUEST_LINUX        0x07
#   define SVGA_REG_GUEST_OS2          0x08
#   define SVGA_REG_GUEST_BSD          0x0a
#   define SVGA_REG_GUEST_WHISTLER     0x0b
#   define SVGA_REG_GUEST_WINDOWS_2003 0x15
#define SVGA_REG_CURSOR_ID           24 /* [rw] */
#define SVGA_REG_CURSOR_X            25 /* [rw] */
#define SVGA_REG_CURSOR_Y            26 /* [rw] */
#define SVGA_REG_CURSOR_ON           27 /* [rw] */
#   define SVGA_CURSOR_ON_HIDE           0x0 /* Must be 0 to maintain backward compatibility */
#   define SVGA_CURSOR_ON_SHOW           0x1 /* Must be 1 to maintain backward compatibility */
#   define SVGA_CURSOR_ON_REMOVE_FROM_FB 0x2 /* Remove the cursor from the framebuffer because we need to see what's under it */
#   define SVGA_CURSOR_ON_RESTORE_TO_FB  0x3 /* Put the cursor back in the framebuffer so the user can see it */
#define SVGA_REG_HOST_BITS_PER_PIXEL 28 /* [ro] */
#define SVGA_REG_SCRATCH_SIZE        29 /* [ro] */
#define SVGA_REG_MEM_REGS            30 /* [ro] ??? (Always reads as "0" in QEMU) */
#define SVGA_REG_NUM_DISPLAYS        31 /* [ro] ??? (Always reads as "0" in QEMU) */
#define SVGA_REG_PITCHLOCK           32 /* [rw] ??? (Always reads as "0" in QEMU) */

#define SVGA_PALETTE_BASE 1024 /* [rw] Base of SVGA color map (Always reads as "0" in QEMU) */
#define SVGA_PALETTE_END  (SVGA_PALETTE_BASE + 767)
#define SVGA_SCRATCH_BASE (SVGA_PALETTE_BASE + 768) /* [rw] # of registers is `SVGA_REG_SCRATCH_SIZE' */



/* FIFO register indices.
 *
 * The FIFO is a chunk of device memory mapped at "SVGA_REG_MEM_START" */

/* Block 1 (basic registers): The originally defined FIFO registers.
 * These exist and are valid for all versions of the FIFO  protocol. */
#define SVGA_FIFO_MIN          0
#define SVGA_FIFO_MAX          1 /* The distance from MIN to MAX must be at least 10K */
#define SVGA_FIFO_NEXT_CMD     2
#define SVGA_FIFO_STOP         3

#define SVGA_FIFO_CAPABILITIES 4 /* [valid_if(SVGA_CAP_EXTENDED_FIFO)] Fifo caps */
#   define SVGA_FIFO_CAP_NONE                 0x00000000
#   define SVGA_FIFO_CAP_FENCE                0x00000001
#   define SVGA_FIFO_CAP_ACCELFRONT           0x00000002
#   define SVGA_FIFO_CAP_PITCHLOCK            0x00000004
#   define SVGA_FIFO_CAP_VIDEO                0x00000008
#   define SVGA_FIFO_CAP_CURSOR_BYPASS_3      0x00000010
#   define SVGA_FIFO_CAP_ESCAPE               0x00000020
#   define SVGA_FIFO_CAP_RESERVE              0x00000040
#   define SVGA_FIFO_CAP_SCREEN_OBJECT        0x00000080
#   define SVGA_FIFO_CAP_GMR2                 0x00000100
#   define SVGA_FIFO_CAP_3D_HWVERSION_REVISED SVGA_FIFO_CAP_GMR2
#   define SVGA_FIFO_CAP_SCREEN_OBJECT_2      0x00000200
#   define SVGA_FIFO_CAP_DEAD                 0x00000400
#define SVGA_FIFO_FLAGS                5
#define SVGA_FIFO_FENCE                6   /* [valid_if(SVGA_FIFO_CAP_FENCE)] */
#define SVGA_FIFO_3D_HWVERSION         7
#define SVGA_FIFO_PITCHLOCK            8   /* [valid_if(SVGA_FIFO_CAP_PITCHLOCK)] */
#define SVGA_FIFO_CURSOR_ON            9   /* [valid_if(SVGA_FIFO_CAP_CURSOR_BYPASS_3)] Cursor bypass 3 show/hide register */
#define SVGA_FIFO_CURSOR_X             10  /* [valid_if(SVGA_FIFO_CAP_CURSOR_BYPASS_3)] Cursor bypass 3 x register */
#define SVGA_FIFO_CURSOR_Y             11  /* [valid_if(SVGA_FIFO_CAP_CURSOR_BYPASS_3)] Cursor bypass 3 y register */
#define SVGA_FIFO_CURSOR_COUNT         12  /* [valid_if(SVGA_FIFO_CAP_CURSOR_BYPASS_3)] Incremented when any of the other 3 change */
#define SVGA_FIFO_CURSOR_LAST_UPDATED  13  /* [valid_if(SVGA_FIFO_CAP_CURSOR_BYPASS_3)] Last time the host updated the cursor */
#define SVGA_FIFO_RESERVED             14  /* [valid_if(SVGA_FIFO_CAP_RESERVE)] Bytes past NEXT_CMD with real contents */
#define SVGA_FIFO_CURSOR_SCREEN_ID     15  /* [valid_if(SVGA_FIFO_CAP_SCREEN_OBJECT || SVGA_FIFO_CAP_SCREEN_OBJECT_2)] */
#define SVGA_FIFO_DEAD                 16  /* [valid_if(SVGA_FIFO_CAP_DEAD)] */
#define SVGA_FIFO_3D_HWVERSION_REVISED 17  /* [valid_if(SVGA_FIFO_CAP_3D_HWVERSION_REVISED)] */
#define SVGA_FIFO_3D_CAPS              32  /* [valid_if(SVGA_FIFO_3D_HWVERSION >= SVGA3D_HWVERSION_WS6_B1)] */
#define SVGA_FIFO_3D_CAPS_LAST         287 /* [valid_if(SVGA_FIFO_3D_HWVERSION >= SVGA3D_HWVERSION_WS6_B1)] */

// Valid if register exists:
#define SVGA_FIFO_GUEST_3D_HWVERSION 288 /* Guest driver's 3D version */
#define SVGA_FIFO_FENCE_GOAL         289 /* Matching target for SVGA_IRQFLAG_FENCE_GOAL */
#define SVGA_FIFO_BUSY               290 /* See "FIFO Synchronization Registers" */

/*
    * Always keep this last.  This defines the maximum number of
    * registers we know about.  At power-on, this value is placed in
    * the SVGA_REG_MEM_REGS register, and we expect the guest driver
    * to allocate this much space in FIFO memory for registers.
    */
#define SVGA_FIFO_NUM_REGS 291



/* FIFO Opcodes.
 *
 * FIFO commands are sequences of 32-bit data-words,  the first of which is one  of
 * the following, with the remainder being the operands for the respective command. */
#define SVGA_CMD_INVALID_CMD            0
#define SVGA_CMD_UPDATE                 1 /* [QEMU][x, y, width, height] Update a rect of on-screen pixels */
#define SVGA_CMD_RECT_FILL              2 /* [QEMU][color, x, y, width, height] Fill rect with color */
#define SVGA_CMD_RECT_COPY              3 /* [QEMU][sx, sy, dx, dy, width, height] Move rect of pixels to other on-screen loc */
#define SVGA_CMD_DEFINE_BITMAP          4
#define SVGA_CMD_DEFINE_BITMAP_SCANLINE 5
#define SVGA_CMD_DEFINE_PIXMAP          6
#define SVGA_CMD_DEFINE_PIXMAP_SCANLINE 7
#define SVGA_CMD_RECT_BITMAP_FILL       8
#define SVGA_CMD_RECT_PIXMAP_FILL       9
#define SVGA_CMD_RECT_BITMAP_COPY       10
#define SVGA_CMD_RECT_PIXMAP_COPY       11
#define SVGA_CMD_FREE_OBJECT            12
#define SVGA_CMD_RECT_ROP_FILL          13
#define SVGA_CMD_RECT_ROP_COPY          14
#define SVGA_CMD_RECT_ROP_BITMAP_FILL   15
#define SVGA_CMD_RECT_ROP_PIXMAP_FILL   16
#define SVGA_CMD_RECT_ROP_BITMAP_COPY   17
#define SVGA_CMD_RECT_ROP_PIXMAP_COPY   18
#define SVGA_CMD_DEFINE_CURSOR          19 /* [QEMU][id, hot_x, hot_y, width, height, ???, bpp] */
#define SVGA_CMD_DISPLAY_CURSOR         20
#define SVGA_CMD_MOVE_CURSOR            21
#define SVGA_CMD_DEFINE_ALPHA_CURSOR    22
#define SVGA_CMD_DRAW_GLYPH             23
#define SVGA_CMD_DRAW_GLYPH_CLIPPED     24
#define SVGA_CMD_UPDATE_VERBOSE         25 /* [QEMU][x, y, width, height] like `SVGA_CMD_UPDATE' */
#define SVGA_CMD_SURFACE_FILL           26
#define SVGA_CMD_SURFACE_COPY           27
#define SVGA_CMD_SURFACE_ALPHA_BLEND    28
#define SVGA_CMD_FRONT_ROP_FILL         29
#define SVGA_CMD_FENCE                  30


#endif /* !_HW_VIDEO_VMWARE_H */
