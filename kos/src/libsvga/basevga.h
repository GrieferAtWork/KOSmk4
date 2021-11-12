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
#ifndef GUARD_LIBSVGA_BASEVGA_H
#define GUARD_LIBSVGA_BASEVGA_H 1

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

/* Initialize base-vga global variables.
 * This function initializes:
 * - basevga_flags
 * - basevga_is1rx
 * Called during chipset driver probe functions. */
INTDEF void CC basevga_init(void);

/* Get/Set standard VGA registers.
 * NOTE: Must be called while holding a lock to the true VGA Chipset driver.
 * NOTE: Setting the basevga register state leaves the screen turned off! */
INTDEF NONNULL((1)) void CC basevga_getregs(struct vga_mode *__restrict regs);
INTDEF NONNULL((1)) void CC basevga_setregs(struct vga_mode const *__restrict regs);

/* Same as `basevga_setregs()', but preserve the state of reserved bits.
 * NOTE: Must be called while holding a lock to the true VGA Chipset driver.
 * NOTE: This function leaves the screen turned off! */
INTDEF NONNULL((1)) void CC basevga_setmode(struct vga_mode const *__restrict regs);

/* TODO: basevga_getpal() */
/* TODO: basevga_setpal() */
/* TODO: basevga_copytoplanar16()  {smi_bits_per_pixel: 1, smi_colorbits: 4} */
/* TODO: basevga_copytoplanar256() {smi_bits_per_pixel: 2, smi_colorbits: 8} */


/* Basic VGA adapter flags. (Set of `BASEVGA_FLAG_*') */
INTDEF uint32_t basevga_flags;
#define BASEVGA_FLAG_ISEGA 0x0001 /* FLAG: Video card is EGA-derived */

/* Either `VGA_IS1_RC' or `VGA_IS1_RM' (as appropriate) */
INTDEF port_t basevga_is1rx;

DECL_END

#endif /* !GUARD_LIBSVGA_BASEVGA_H */
