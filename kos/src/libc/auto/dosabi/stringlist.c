/* HASH CRC-32:0xddc714c3 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_STRINGLIST_C
#define GUARD_LIBC_AUTO_DOSABI_STRINGLIST_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/stringlist.h"

DECL_BEGIN

/* Append a given `NAME' to `SL'. `NAME' is considered
 * inherited if the StringList is destroyed with `1' */
INTERN ATTR_SECTION(".text.crt.dos.bsd.stringlist") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_sl_add)(struct _stringlist *sl,
                                  char *name) {
	return libc_sl_add(sl, name);
}
/* Free a given string list. When `ALL' is non-zero, all contained
 * string pointers (as previously added with `sl_add()') will also
 * be `free(3)'ed. */
INTERN ATTR_SECTION(".text.crt.dos.bsd.stringlist") void
NOTHROW_NCX(LIBDCALL libd_sl_free)(struct _stringlist *sl,
                                   int all) {
	libc_sl_free(sl, all);
}
/* Search for `NAME' within the given StringList. Upon success,
 * return a pointer to the equivalent string within `SL' (i.e. the
 * pointer originally passed to `sl_add()' to insert that string).
 * If `SL' doesn't contain an equivalent string, return `NULL' instead. */
INTERN ATTR_SECTION(".text.crt.dos.bsd.stringlist") ATTR_PURE NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_sl_find)(struct _stringlist __KOS_FIXED_CONST *sl,
                                   char const *name) {
	return libc_sl_find(sl, name);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$sl_add, libd_sl_add);
DEFINE_PUBLIC_ALIAS(DOS$sl_free, libd_sl_free);
DEFINE_PUBLIC_ALIAS(DOS$sl_find, libd_sl_find);

#endif /* !GUARD_LIBC_AUTO_DOSABI_STRINGLIST_C */
