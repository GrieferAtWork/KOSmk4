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
#ifndef _LIBPCIACCESS_PATHS_H
#define _LIBPCIACCESS_PATHS_H 1

#include "api.h"

#ifdef LIBPCIACCESS_SUPPORTED

/* Default path to the `pci.ids' strings database file.
 * NOTE: When  `make_utility.sh ... zlib'  has been  installed, this  file is
 *       allowed to be compressed (since it will be accessed via `gzopen(3)') */
#ifndef _PATH_PCI_IDS
#define _PATH_PCI_IDS "/usr/share/hwdata/pci.ids"
#endif /* !_PATH_PCI_IDS */

/* This one is only considered when `gzopen(3)' is available. */
#ifndef _PATH_PCI_IDS_GZ
#define _PATH_PCI_IDS_GZ "/usr/share/hwdata/pci.ids.gz"
#endif /* !_PATH_PCI_IDS_GZ */

#endif /* LIBPCIACCESS_SUPPORTED */

#endif /* !_LIBPCIACCESS_PATHS_H */
