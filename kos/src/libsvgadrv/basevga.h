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
#ifndef GUARD_LIBSVGADRV_BASEVGA_H
#define GUARD_LIBSVGADRV_BASEVGA_H 1

#include "api.h"
/**/

#include <hw/video/vga.h>
#include <kos/types.h>

#include <stdbool.h>

DECL_BEGIN

#ifndef __port_t_defined
#define __port_t_defined
typedef __port_t port_t;
#endif /* !__port_t_defined */

/* TODO: basevga_copytoplanar16()  {smi_bits_per_pixel: 1, smi_colorbits: 4} */
/* TODO: basevga_copytoplanar256() {smi_bits_per_pixel: 2, smi_colorbits: 8} */

/* Basic VGA adapter flags. (Set of `BASEVGA_FLAG_*') */
INTDEF uint32_t basevga_flags;
#define BASEVGA_FLAG_ISEGA 0x0001 /* FLAG: Video card is EGA-derived */


/* Initialize base-vga global variables.
 * This function initializes:
 * - basevga_flags
 * - basevga_IS1_R
 * Must be called before chipset driver probe functions. */
INTDEF void CC basevga_init(void);

/* Get/Set standard VGA registers.
 * NOTE: Must be called while holding a lock to the true VGA Chipset driver.
 * NOTE: Setting the basevga register state leaves the screen turned off! */
INTDEF NONNULL((1)) void CC basevga_getregs(struct vga_regs *__restrict regs);
INTDEF NONNULL((1)) void CC basevga_setregs(struct vga_regs const *__restrict regs);

/* Same as `basevga_setregs()', but preserve the state of reserved bits.
 * NOTE: Must be called while holding a lock to the true VGA Chipset driver.
 * NOTE: This function leaves the screen turned off! */
INTDEF NONNULL((1)) void CC basevga_setmode(struct vga_mode const *__restrict mode);

/* Current (assumed) EGA register state. */
INTDEF struct vga_regs baseega_registers;

/* Read/write to/from the current color palette.
 * @param: color_index: Starting palette color index.
 * @param: count:       # of color rgb-triples to read/write */
INTDEF NONNULL((2)) void CC basevga_rdpal(uint8_t color_index, struct vga_palcolor *__restrict buf, uint8_t count);
INTDEF NONNULL((2)) void CC basevga_wrpal(uint8_t color_index, struct vga_palcolor const *__restrict buf, uint8_t count);

/* Direct access  to the  standard 256K  of VGA  video  memory.
 * These functions take the current register state into account
 * in order to  work around any  weird address  transformations
 * which may be done by the video card:
 *  - VGA_GR04_READMAP(i)  // For `basevga_rdvmem()'
 *  - VGA_GR05_FREADMODE_* // For `basevga_rdvmem()'
 *  - VGA_GR06_FCHAINOE
 *  - VGA_GR06_FMM_*
 *  - VGA_SR02_FPLANE(i)   // For `basevga_wrvmem()'
 * Any VGA registers modified by these functions will be restored
 * before they return. These functions  aren't very fast and  are
 * meant  to be used to backup and restore base-vga video memory.
 *
 * Here are some important memory locations:
 *  - 00000h: Plane 0
 *    - On-screen text characters in text-mode
 *    - yes: Only the characters (not attributes), tightly packed together
 *  - 10000h: Plane 1
 *    - On-screen text attributes in text-mode
 *    - yes: Text-mode uses `VGA_GR05_FHOSTOE' + `VGA_GR06_FCHAINOE'
 *           and  `VGA_GR06_FMM_32K_HI' to create  a linear array of
 *           u16-cells at `B8000h'
 *  - 20000h: Plane 2
 *    - Text-mode font data as array of 32-byte scanline bitsets,
 *      even though only  the first 16  are used for  characters.
 *    - Actual font location(s) are stored in `VGA_SEQ_CHARACTER_MAP'
 *  - 30000h: Plane 3 */
INTDEF NONNULL((2)) void CC basevga_rdvmem(uint32_t addr, void *buf, uint32_t num_bytes);
INTDEF NONNULL((2)) void CC basevga_wrvmem(uint32_t addr, void const *buf, uint32_t num_bytes);


DECL_END

#endif /* !GUARD_LIBSVGADRV_BASEVGA_H */
