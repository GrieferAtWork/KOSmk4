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
#ifndef GUARD_LIBSVGADRV_API_H
#define GUARD_LIBSVGADRV_API_H 1
#define LIBPHYS_WANT_PROTOTYPES

#include <libsvgadrv/api.h>
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/config/config.h> /* Pull in config-specific macro overrides */

#define CC LIBSVGADRV_CC

#ifndef NOTHROW_KERNEL
#define NOTHROW_KERNEL __NOTHROW_KERNEL
#endif /* !NOTHROW_KERNEL */


/* vvv The driver works and *is* able to init the display, however vmware  requires
 *     drivers to manually indicate when they want the screen to refresh, which  is
 *     something that libsvgadrv has no way of expressing (yet). As such, while KOS
 *     *does* boot, the only way to see the screen refresh is to ALT+TAB in-and-out
 *     of   QEMU   (since   that  happens   to   cause  the   screen   to  refresh)
 * Also: for some reason everything is yellow instead of white... */
#define CONFIG_NO_LIBSVGADRV_CHIPSET_VMWARE

/* Configure supported chipsets. */
/*[[[config CONFIG_HAVE_LIBSVGADRV_CHIPSET_VMWARE = true]]]*/
#ifdef CONFIG_NO_LIBSVGADRV_CHIPSET_VMWARE
#undef CONFIG_HAVE_LIBSVGADRV_CHIPSET_VMWARE
#elif !defined(CONFIG_HAVE_LIBSVGADRV_CHIPSET_VMWARE)
#define CONFIG_HAVE_LIBSVGADRV_CHIPSET_VMWARE
#elif (-CONFIG_HAVE_LIBSVGADRV_CHIPSET_VMWARE - 1) == -1
#undef CONFIG_HAVE_LIBSVGADRV_CHIPSET_VMWARE
#define CONFIG_NO_LIBSVGADRV_CHIPSET_VMWARE
#endif /* ... */
/*[[[end]]]*/

/*[[[config CONFIG_HAVE_LIBSVGADRV_CHIPSET_BOCHSVBE = true]]]*/
#ifdef CONFIG_NO_LIBSVGADRV_CHIPSET_BOCHSVBE
#undef CONFIG_HAVE_LIBSVGADRV_CHIPSET_BOCHSVBE
#elif !defined(CONFIG_HAVE_LIBSVGADRV_CHIPSET_BOCHSVBE)
#define CONFIG_HAVE_LIBSVGADRV_CHIPSET_BOCHSVBE
#elif (-CONFIG_HAVE_LIBSVGADRV_CHIPSET_BOCHSVBE - 1) == -1
#undef CONFIG_HAVE_LIBSVGADRV_CHIPSET_BOCHSVBE
#define CONFIG_NO_LIBSVGADRV_CHIPSET_BOCHSVBE
#endif /* ... */
/*[[[end]]]*/

/*[[[config CONFIG_HAVE_LIBSVGADRV_CHIPSET_VESA = true]]]*/
#ifdef CONFIG_NO_LIBSVGADRV_CHIPSET_VESA
#undef CONFIG_HAVE_LIBSVGADRV_CHIPSET_VESA
#elif !defined(CONFIG_HAVE_LIBSVGADRV_CHIPSET_VESA)
#define CONFIG_HAVE_LIBSVGADRV_CHIPSET_VESA
#elif (-CONFIG_HAVE_LIBSVGADRV_CHIPSET_VESA - 1) == -1
#undef CONFIG_HAVE_LIBSVGADRV_CHIPSET_VESA
#define CONFIG_NO_LIBSVGADRV_CHIPSET_VESA
#endif /* ... */
/*[[[end]]]*/

/*[[[config CONFIG_HAVE_LIBSVGADRV_CHIPSET_VGA = true]]]*/
#ifdef CONFIG_NO_LIBSVGADRV_CHIPSET_VGA
#undef CONFIG_HAVE_LIBSVGADRV_CHIPSET_VGA
#elif !defined(CONFIG_HAVE_LIBSVGADRV_CHIPSET_VGA)
#define CONFIG_HAVE_LIBSVGADRV_CHIPSET_VGA
#elif (-CONFIG_HAVE_LIBSVGADRV_CHIPSET_VGA - 1) == -1
#undef CONFIG_HAVE_LIBSVGADRV_CHIPSET_VGA
#define CONFIG_NO_LIBSVGADRV_CHIPSET_VGA
#endif /* ... */
/*[[[end]]]*/

#endif /* !GUARD_LIBSVGADRV_API_H */
