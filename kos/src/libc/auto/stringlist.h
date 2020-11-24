/* HASH CRC-32:0xc5a7efd2 */
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
#ifndef GUARD_LIBC_AUTO_STRINGLIST_H
#define GUARD_LIBC_AUTO_STRINGLIST_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stringlist.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> sl_init(3)
 * Allocates and returns a new StringList object. Upon error, `NULL' is returned */
INTDEF WUNUSED struct _stringlist *NOTHROW_NCX(LIBCCALL libc_sl_init)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sl_add(3)
 * Append a given `NAME' to `SL'. `NAME' is considered
 * inherited if the StringList is destroyed with `1' */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_sl_add)(struct _stringlist *sl, char *name);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sl_add(3)
 * Append a given `NAME' to `SL'. `NAME' is considered
 * inherited if the StringList is destroyed with `1' */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_sl_add)(struct _stringlist *sl, char *name);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sl_free(3)
 * Free a given string list. When `ALL' is non-zero, all contained
 * string pointers (as previously added with `sl_add()') will also
 * be `free(3)'ed. */
INTDEF void NOTHROW_NCX(LIBDCALL libd_sl_free)(struct _stringlist *sl, int all);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sl_free(3)
 * Free a given string list. When `ALL' is non-zero, all contained
 * string pointers (as previously added with `sl_add()') will also
 * be `free(3)'ed. */
INTDEF void NOTHROW_NCX(LIBCCALL libc_sl_free)(struct _stringlist *sl, int all);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sl_find(3)
 * Search for `NAME' within the given StringList. Upon success,
 * return a pointer to the equivalent string within `SL' (i.e. the
 * pointer originally passed to `sl_add()' to insert that string).
 * If `SL' doesn't contain an equivalent string, return `NULL' instead. */
INTDEF ATTR_PURE NONNULL((1, 2)) char *NOTHROW_NCX(LIBDCALL libd_sl_find)(struct _stringlist __KOS_FIXED_CONST *sl, char const *name);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sl_find(3)
 * Search for `NAME' within the given StringList. Upon success,
 * return a pointer to the equivalent string within `SL' (i.e. the
 * pointer originally passed to `sl_add()' to insert that string).
 * If `SL' doesn't contain an equivalent string, return `NULL' instead. */
INTDEF ATTR_PURE NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_sl_find)(struct _stringlist __KOS_FIXED_CONST *sl, char const *name);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sl_delete(3)
 * Remove an entry `name' from `sl'
 * When `freeit' is non-zero, a removed string is deallocated using `free(3)'
 * @return: 0:  Successfully removed a string equal to `name'
 * @return: -1: No string equal to `name' was found in `sl' */
INTDEF WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_sl_delete)(struct _stringlist *sl, char const *name, int freeit);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sl_delete(3)
 * Remove an entry `name' from `sl'
 * When `freeit' is non-zero, a removed string is deallocated using `free(3)'
 * @return: 0:  Successfully removed a string equal to `name'
 * @return: -1: No string equal to `name' was found in `sl' */
INTDEF WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_sl_delete)(struct _stringlist *sl, char const *name, int freeit);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STRINGLIST_H */
