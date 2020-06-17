/* HASH CRC-32:0x52391bb */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_DOSABI_LIBGEN_C
#define GUARD_LIBC_AUTO_DOSABI_LIBGEN_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../libgen.h"

DECL_BEGIN

/* Return directory part of PATH or "." if none is available */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") ATTR_RETNONNULL char *
NOTHROW_NCX(LIBDCALL libd_dirname)(char *path) {
	return libc_dirname(path);
}
/* Return final component of PATH.
 * This is the weird XPG version of this function. It sometimes will
 * modify its argument. Therefore we normally use the GNU version (in
 * <string.h>) and only if this header is included make the XPG
 * version available under the real name */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") ATTR_RETNONNULL char *
NOTHROW_NCX(LIBDCALL libd___xpg_basename)(char *filename) {
	return libc___xpg_basename(filename);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$dirname, libd_dirname);
DEFINE_PUBLIC_ALIAS(DOS$__xpg_basename, libd___xpg_basename);

#endif /* !GUARD_LIBC_AUTO_DOSABI_LIBGEN_C */
