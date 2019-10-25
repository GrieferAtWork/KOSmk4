/* HASH CRC-32:0x7ec95364 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_MNTENT_C
#define GUARD_LIBC_AUTO_MNTENT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "mntent.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
/* Search MNT->mnt_opts for an option matching OPT.
 * Returns the address of the substring, or null if none found */
INTERN ATTR_PURE WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.database.mntent.hasmntopt") char *
NOTHROW_NCX(LIBCCALL libc_hasmntopt)(struct mntent const *mnt,
                                     char const *opt) {
#line 120 "kos/src/libc/magic/mntent.c"
	char *str;
	if likely(mnt && opt && (str = mnt->mnt_opts) != NULL) {
		size_t optlen = libc_strlen(opt);
		while (*str) {
			if (memcmp(str, opt, optlen * sizeof(char)) == 0 &&
			   (str[optlen] == ',' || str[optlen] == '\0'))
				return str;
			str = libc_strchrnul(str, ',');
		}
	}
	return NULL;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(hasmntopt, libc_hasmntopt);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_MNTENT_C */
