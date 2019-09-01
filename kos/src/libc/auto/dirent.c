/* HASH 0xa58ce232 */
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
#ifndef GUARD_LIBC_AUTO_DIRENT_C
#define GUARD_LIBC_AUTO_DIRENT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "dirent.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
/* Sort the 2 given directory entries `E1' and `E2' the same way `strcmp(3)' would */
INTERN ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.alphasort") int
NOTHROW_NCX(LIBCCALL libc_alphasort)(struct dirent const **e1,
                                     struct dirent const **e2) {
#line 231 "kos/src/libc/magic/dirent.c"
	return libc_strcoll((*e1)->d_name, (*e2)->d_name);
}

/* 64-bit variant of `alphasort()' */
#if defined(_DIRENT_MATCHES_DIRENT64)
DEFINE_INTERN_ALIAS(libc_alphasort64, libc_alphasort);
#else
INTERN ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.alphasort64") int
NOTHROW_NCX(LIBCCALL libc_alphasort64)(struct dirent64 const **e1,
                                       struct dirent64 const **e2) {
#line 237 "kos/src/libc/magic/dirent.c"
	return libc_strcoll((*e1)->d_name, (*e2)->d_name);
}
#endif /* MAGIC:alias */

/* Sort the 2 given directory entries `E1' and `E2' the same way `strvercmp(3)' would. */
INTERN ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.versionsort") int
NOTHROW_NCX(LIBCCALL libc_versionsort)(struct dirent const **e1,
                                       struct dirent const **e2) {
#line 298 "kos/src/libc/magic/dirent.c"
	return libc_strverscmp((*e1)->d_name, (*e2)->d_name);
}

/* 64-bit variant of `versionsort()' */
#if defined(_DIRENT_MATCHES_DIRENT64)
DEFINE_INTERN_ALIAS(libc_versionsort64, libc_versionsort);
#else
INTERN ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.versionsort64") int
NOTHROW_NCX(LIBCCALL libc_versionsort64)(struct dirent64 const **e1,
                                         struct dirent64 const **e2) {
#line 304 "kos/src/libc/magic/dirent.c"
	return libc_strverscmp((*e1)->d_name, (*e2)->d_name);
}
#endif /* MAGIC:alias */

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(alphasort, libc_alphasort);
DEFINE_PUBLIC_WEAK_ALIAS(alphasort64, libc_alphasort64);
DEFINE_PUBLIC_WEAK_ALIAS(versionsort, libc_versionsort);
DEFINE_PUBLIC_WEAK_ALIAS(versionsort64, libc_versionsort64);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_DIRENT_C */
