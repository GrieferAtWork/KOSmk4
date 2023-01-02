/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBSVGADRV_CHIPSET_H
#define GUARD_LIBSVGADRV_CHIPSET_H 1

#include "api.h"
/**/

#include <libsvgadrv/chipset.h>

DECL_BEGIN

/* Return the list of supported VGA chipset drivers (terminated by a bzero'd entry)
 * This list is sorted from most specific- to most generic driver. As such, some of
 * the later drivers might also  be usable even when one  of the former ones  could
 * also be used.
 *
 * As such, when probing for devices you should simply iterate this list until you
 * find a driver  for which probing  succeeds. Once that  happens, simply keep  on
 * using that driver. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED struct svga_chipset_driver const *
NOTHROW(CC libsvga_chipset_getdrivers)(void);

DECL_END

#endif /* !GUARD_LIBSVGADRV_CHIPSET_H */
