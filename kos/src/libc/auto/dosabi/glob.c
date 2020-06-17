/* HASH CRC-32:0xc3ec7d6e */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_GLOB_C
#define GUARD_LIBC_AUTO_DOSABI_GLOB_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/glob.h"

DECL_BEGIN

/* Do glob searching for PATTERN, placing results in PGLOB.
 * The bits defined above may be set in FLAGS.
 * If a directory cannot be opened or read and ERRFUNC is not nil,
 * it is called with the pathname that caused the error, and the
 * `errno' value from the failing call; if it returns non-zero
 * `glob' returns GLOB_ABEND; if it returns zero, the error is ignored.
 * If memory cannot be allocated for PGLOB, GLOB_NOSPACE is returned.
 * Otherwise, `glob' returns zero */
INTERN ATTR_SECTION(".text.crt.dos.utility.glob") NONNULL((1, 4)) int
NOTHROW_NCX(LIBDCALL libd_glob)(char const *__restrict pattern,
                                int flags,
                                __glob_errfunc_t errfunc,
                                glob_t *__restrict pglob) {
	return libc_glob(pattern, flags, errfunc, pglob);
}
/* Free storage allocated in PGLOB by a previous `glob' call */
INTERN ATTR_SECTION(".text.crt.dos.utility.glob") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_globfree)(glob_t *pglob) {
	libc_globfree(pglob);
}
/* Do glob searching for PATTERN, placing results in PGLOB.
 * The bits defined above may be set in FLAGS.
 * If a directory cannot be opened or read and ERRFUNC is not nil,
 * it is called with the pathname that caused the error, and the
 * `errno' value from the failing call; if it returns non-zero
 * `glob' returns GLOB_ABEND; if it returns zero, the error is ignored.
 * If memory cannot be allocated for PGLOB, GLOB_NOSPACE is returned.
 * Otherwise, `glob' returns zero */
INTERN ATTR_SECTION(".text.crt.dos.utility.glob") NONNULL((1, 4)) int
NOTHROW_NCX(LIBDCALL libd_glob64)(const char *__restrict pattern,
                                  int flags,
                                  __glob_errfunc_t errfunc,
                                  struct __glob64_struct *__restrict pglob) {
	return libc_glob64(pattern, flags, errfunc, pglob);
}
/* Free storage allocated in PGLOB by a previous `glob' call */
INTERN ATTR_SECTION(".text.crt.dos.utility.glob") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_globfree64)(struct __glob64_struct *pglob) {
	libc_globfree64(pglob);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$glob, libd_glob);
DEFINE_PUBLIC_ALIAS(DOS$globfree, libd_globfree);
DEFINE_PUBLIC_ALIAS(DOS$glob64, libd_glob64);
DEFINE_PUBLIC_ALIAS(DOS$globfree64, libd_globfree64);

#endif /* !GUARD_LIBC_AUTO_DOSABI_GLOB_C */
