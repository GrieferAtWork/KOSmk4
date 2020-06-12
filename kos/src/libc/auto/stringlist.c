/* HASH CRC-32:0x9a944df6 */
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
#ifndef GUARD_LIBC_AUTO_STRINGLIST_C
#define GUARD_LIBC_AUTO_STRINGLIST_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/stringlist.h"
#include "../user/string.h"

DECL_BEGIN

#ifndef __KERNEL__
/* Search for `NAME' within the given StringList. Upon success,
 * return a pointer to the equivalent string within `SL' (i.e. the
 * pointer originally passed to `sl_add()' to insert that string).
 * If `SL' doesn't contain an equivalent string, return `NULL' instead. */
INTERN ATTR_SECTION(".text.crt.bsd.stringlist") ATTR_PURE NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_sl_find)(struct _stringlist __KOS_FIXED_CONST *sl,
                                   char const *name) {
	size_t i;
	for (i = 0; i < sl->sl_cur; ++i) {
		char *s = sl->sl_str[i];
		if (libc_strcmp(s, name) == 0)
			return s;
	}
	return NULL;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(sl_find, libc_sl_find);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_STRINGLIST_C */
