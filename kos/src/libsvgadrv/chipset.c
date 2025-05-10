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
#ifndef GUARD_LIBSVGADRV_CHIPSET_C
#define GUARD_LIBSVGADRV_CHIPSET_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <kos/kernel/types.h>
#include <kos/types.h>

#include <stddef.h>

#include <libsvgadrv/chipset.h>

#include "basevga.h"
#include "chipset.h"

/* Include headers of supported chipset drivers. */
#include "cs-bochsvbe.h"
#include "cs-vesa.h"
#include "cs-vga.h"
#include "cs-vmware.h"

DECL_BEGIN


/* List of supported drivers. - Keep sorted most-specific to most-generic. */
PRIVATE struct svga_chipset_driver svga_drivers[] = {
#ifdef SVGA_CHIPSET_DRIVER_INIT_VMWARE
	SVGA_CHIPSET_DRIVER_INIT_VMWARE,
#endif /* SVGA_CHIPSET_DRIVER_INIT_VMWARE */
#ifdef SVGA_CHIPSET_DRIVER_INIT_BOCHSVBE
	SVGA_CHIPSET_DRIVER_INIT_BOCHSVBE,
#endif /* SVGA_CHIPSET_DRIVER_INIT_BOCHSVBE */
#ifdef SVGA_CHIPSET_DRIVER_INIT_VESA
	SVGA_CHIPSET_DRIVER_INIT_VESA,
#endif /* SVGA_CHIPSET_DRIVER_INIT_VESA */
#ifdef SVGA_CHIPSET_DRIVER_INIT_VGA
	SVGA_CHIPSET_DRIVER_INIT_VGA,
#endif /* SVGA_CHIPSET_DRIVER_INIT_VGA */
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

DECL_END

#endif /* !GUARD_LIBSVGADRV_CHIPSET_C */
