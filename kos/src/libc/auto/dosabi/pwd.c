/* HASH CRC-32:0xfe717c25 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_PWD_C
#define GUARD_LIBC_AUTO_DOSABI_PWD_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/pwd.h"

DECL_BEGIN

/* Search for an entry with a matching user ID */
INTERN ATTR_SECTION(".text.crt.dos.database.pwd") struct passwd *
NOTHROW_RPC(LIBDCALL libd_getpwuid)(uid_t uid) {
	return libc_getpwuid(uid);
}
/* Search for an entry with a matching username */
INTERN ATTR_SECTION(".text.crt.dos.database.pwd") NONNULL((1)) struct passwd *
NOTHROW_RPC(LIBDCALL libd_getpwnam)(const char *name) {
	return libc_getpwnam(name);
}
/* Read an entry from STREAM */
INTERN ATTR_SECTION(".text.crt.dos.database.pwd") NONNULL((1)) struct passwd *
NOTHROW_RPC(LIBDCALL libd_fgetpwent)(FILE *__restrict stream) {
	return libc_fgetpwent(stream);
}
/* Write the given entry onto the given stream */
INTERN ATTR_SECTION(".text.crt.dos.database.pwd") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_putpwent)(struct passwd const *__restrict p,
                                    FILE *__restrict f) {
	return libc_putpwent(p, f);
}
/* Search for an entry with a matching user ID */
INTERN ATTR_SECTION(".text.crt.dos.database.pwd") NONNULL((2, 3, 5)) int
NOTHROW_RPC(LIBDCALL libd_getpwuid_r)(__uid_t __uid,
                                      struct passwd *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct passwd **__restrict result) {
	return libc_getpwuid_r(__uid, resultbuf, buffer, buflen, result);
}
/* Search for an entry with a matching username */
INTERN ATTR_SECTION(".text.crt.dos.database.pwd") NONNULL((1, 2, 3, 5)) int
NOTHROW_RPC(LIBDCALL libd_getpwnam_r)(const char *__restrict name,
                                      struct passwd *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct passwd **__restrict result) {
	return libc_getpwnam_r(name, resultbuf, buffer, buflen, result);
}
/* Read an entry from the password-file stream, opening it if necessary */
INTERN ATTR_SECTION(".text.crt.dos.database.pwd") NONNULL((1, 2, 4)) int
NOTHROW_RPC(LIBDCALL libd_getpwent_r)(struct passwd *__restrict resultbuf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct passwd **__restrict result) {
	return libc_getpwent_r(resultbuf, buffer, buflen, result);
}
/* Read an entry from STREAM. This function is not standardized and probably never will */
INTERN ATTR_SECTION(".text.crt.dos.database.pwd") NONNULL((1, 2, 3, 5)) int
NOTHROW_RPC(LIBDCALL libd_fgetpwent_r)(FILE *__restrict stream,
                                       struct passwd *__restrict resultbuf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct passwd **__restrict result) {
	return libc_fgetpwent_r(stream, resultbuf, buffer, buflen, result);
}
/* Re-construct the password-file line for the given uid in the
 * given buffer. This knows the format that the caller will
 * expect, but this need not be the format of the password file */
INTERN ATTR_SECTION(".text.crt.dos.database.pwd") int
NOTHROW_RPC(LIBDCALL libd_getpw)(__uid_t uid,
                                 char *buffer) {
	return libc_getpw(uid, buffer);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$getpwuid, libd_getpwuid);
DEFINE_PUBLIC_ALIAS(DOS$getpwnam, libd_getpwnam);
DEFINE_PUBLIC_ALIAS(DOS$fgetpwent, libd_fgetpwent);
DEFINE_PUBLIC_ALIAS(DOS$putpwent, libd_putpwent);
DEFINE_PUBLIC_ALIAS(DOS$getpwuid_r, libd_getpwuid_r);
DEFINE_PUBLIC_ALIAS(DOS$getpwnam_r, libd_getpwnam_r);
DEFINE_PUBLIC_ALIAS(DOS$getpwent_r, libd_getpwent_r);
DEFINE_PUBLIC_ALIAS(DOS$fgetpwent_r, libd_fgetpwent_r);
DEFINE_PUBLIC_ALIAS(DOS$getpw, libd_getpw);

#endif /* !GUARD_LIBC_AUTO_DOSABI_PWD_C */
