/* HASH CRC-32:0x4ef4b56d */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_DIRENT_C
#define GUARD_LIBC_AUTO_DIRENT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/dirent.h"
#include "../user/string.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/os/dirent.h>
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_PURE NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_alphasort)(struct dirent const **e1,
                                     struct dirent const **e2) {
	return libc_strcoll((*e1)->d_name, (*e2)->d_name);
}
#ifdef _DIRENT_MATCHES_DIRENT64
DEFINE_INTERN_ALIAS(libc_alphasort64, libc_alphasort);
#else /* _DIRENT_MATCHES_DIRENT64 */
#include <bits/os/dirent.h>
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_PURE NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_alphasort64)(struct dirent64 const **e1,
                                       struct dirent64 const **e2) {
	return libc_strcoll((*e1)->d_name, (*e2)->d_name);
}
#endif /* !_DIRENT_MATCHES_DIRENT64 */
#include <bits/os/dirent.h>
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_PURE NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_versionsort)(struct dirent const **e1,
                                       struct dirent const **e2) {
	return libc_strverscmp((*e1)->d_name, (*e2)->d_name);
}
#ifdef _DIRENT_MATCHES_DIRENT64
DEFINE_INTERN_ALIAS(libc_versionsort64, libc_versionsort);
#else /* _DIRENT_MATCHES_DIRENT64 */
#include <bits/os/dirent.h>
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_PURE NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_versionsort64)(struct dirent64 const **e1,
                                         struct dirent64 const **e2) {
	return libc_strverscmp((*e1)->d_name, (*e2)->d_name);
}
#endif /* !_DIRENT_MATCHES_DIRENT64 */
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(alphasort, libc_alphasort);
DEFINE_PUBLIC_ALIAS(alphasort64, libc_alphasort64);
DEFINE_PUBLIC_ALIAS(versionsort, libc_versionsort);
DEFINE_PUBLIC_ALIAS(versionsort64, libc_versionsort64);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_DIRENT_C */
