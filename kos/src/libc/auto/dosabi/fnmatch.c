/* HASH CRC-32:0x2e78e2ba */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_FNMATCH_C
#define GUARD_LIBC_AUTO_DOSABI_FNMATCH_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../fnmatch.h"

DECL_BEGIN

/* Match NAME against the filename pattern PATTERN,
 * returning zero if it matches, FNM_NOMATCH if not */
INTERN ATTR_SECTION(".text.crt.dos.string.match") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_fnmatch)(char const *pattern,
                                   char const *name,
                                   int match_flags) {
	return libc_fnmatch(pattern, name, match_flags);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$fnmatch, libd_fnmatch);

#endif /* !GUARD_LIBC_AUTO_DOSABI_FNMATCH_C */
