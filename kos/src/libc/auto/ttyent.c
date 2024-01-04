/* HASH CRC-32:0x66e7855 */
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
#ifndef GUARD_LIBC_AUTO_TTYENT_C
#define GUARD_LIBC_AUTO_TTYENT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/ttyent.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/crt/db/ttyent.h>
/* >> getttynam(3) */
INTERN ATTR_SECTION(".text.crt.database.tty") ATTR_IN(1) struct ttyent *
NOTHROW_RPC_KOS(LIBCCALL libc_getttynam)(char const *tty) {
	struct ttyent *result;
	if (!libc_setttyent())
		return NULL;
	while ((result = libc_getttyent()) != NULL) {
		if (libc_strcmp(result->ty_name, tty) == 0)
			break;
	}
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(getttynam, libc_getttynam);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_TTYENT_C */
