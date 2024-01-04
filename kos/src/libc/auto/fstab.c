/* HASH CRC-32:0xcd0d5109 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_FSTAB_C
#define GUARD_LIBC_AUTO_FSTAB_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/fstab.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/crt/db/fstab.h>
/* >> getfsspec(3)
 * Find and return the fstab entry with `strcmp(ent->fs_spec, special_file) == 0'
 * @return: * :   Pointer to a statically allocated fstab entry for `special_file'
 * @return: NULL: [errno = <unchanged>] No entry exists matching `special_file'
 * @return: NULL: [errno = *] Error */
INTERN ATTR_SECTION(".text.crt.database.fstab") WUNUSED ATTR_IN(1) struct fstab *
NOTHROW_NCX(LIBCCALL libc_getfsspec)(const char *special_file) {
	struct fstab *result;
	if (!libc_setfsent())
		return NULL;
	while ((result = libc_getfsent()) != NULL) {
		if (libc_strcmp(result->fs_spec, special_file) == 0)
			break;
	}
	return result;
}
#include <bits/crt/db/fstab.h>
/* >> getfsfile(3)
 * Find and return the fstab entry with `strcmp(ent->fs_file, mount_point) == 0'
 * @return: * :   Pointer to a statically allocated fstab entry for `mount_point'
 * @return: NULL: [errno = <unchanged>] No entry exists matching `mount_point'
 * @return: NULL: [errno = *] Error */
INTERN ATTR_SECTION(".text.crt.database.fstab") WUNUSED ATTR_IN(1) struct fstab *
NOTHROW_NCX(LIBCCALL libc_getfsfile)(const char *mount_point) {
	struct fstab *result;
	if (!libc_setfsent())
		return NULL;
	while ((result = libc_getfsent()) != NULL) {
		if (libc_strcmp(result->fs_file, mount_point) == 0)
			break;
	}
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(getfsspec, libc_getfsspec);
DEFINE_PUBLIC_ALIAS(getfsfile, libc_getfsfile);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_FSTAB_C */
