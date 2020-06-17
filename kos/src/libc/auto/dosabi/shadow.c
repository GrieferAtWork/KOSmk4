/* HASH CRC-32:0x76a2c775 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SHADOW_C
#define GUARD_LIBC_AUTO_DOSABI_SHADOW_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/shadow.h"

DECL_BEGIN

/* Get shadow entry matching NAME.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.database.shadow") NONNULL((1)) struct spwd *
NOTHROW_RPC(LIBDCALL libd_getspnam)(char const *__restrict name) {
	return libc_getspnam(name);
}
/* Read shadow entry from STRING.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.database.shadow") NONNULL((1)) struct spwd *
NOTHROW_RPC(LIBDCALL libd_sgetspent)(char const *__restrict string) {
	return libc_sgetspent(string);
}
/* Read next shadow entry from STREAM.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.database.shadow") NONNULL((1)) struct spwd *
NOTHROW_RPC(LIBDCALL libd_fgetspent)(FILE *__restrict stream) {
	return libc_fgetspent(stream);
}
/* Write line containing shadow password entry to stream.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.database.shadow") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_putspent)(struct spwd const *__restrict p,
                                    FILE *__restrict stream) {
	return libc_putspent(p, stream);
}
/* Reentrant versions of some of the functions above.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.database.shadow") NONNULL((1, 2, 4)) int
NOTHROW_RPC(LIBDCALL libd_getspent_r)(struct spwd *__restrict result_buf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct spwd **__restrict result) {
	return libc_getspent_r(result_buf, buffer, buflen, result);
}
/* Reentrant versions of some of the functions above.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.database.shadow") NONNULL((1, 2, 3, 5)) int
NOTHROW_RPC(LIBDCALL libd_getspnam_r)(char const *__restrict name,
                                      struct spwd *__restrict result_buf,
                                      char *__restrict buffer,
                                      size_t buflen,
                                      struct spwd **__restrict result) {
	return libc_getspnam_r(name, result_buf, buffer, buflen, result);
}
/* Reentrant versions of some of the functions above.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.database.shadow") NONNULL((1, 2, 3, 5)) int
NOTHROW_RPC(LIBDCALL libd_sgetspent_r)(char const *__restrict string,
                                       struct spwd *__restrict result_buf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct spwd **__restrict result) {
	return libc_sgetspent_r(string, result_buf, buffer, buflen, result);
}
/* Reentrant versions of some of the functions above.
 * These functions are not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.database.shadow") NONNULL((1, 2, 3, 5)) int
NOTHROW_RPC(LIBDCALL libd_fgetspent_r)(FILE *__restrict stream,
                                       struct spwd *__restrict result_buf,
                                       char *__restrict buffer,
                                       size_t buflen,
                                       struct spwd **__restrict result) {
	return libc_fgetspent_r(stream, result_buf, buffer, buflen, result);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$getspnam, libd_getspnam);
DEFINE_PUBLIC_ALIAS(DOS$sgetspent, libd_sgetspent);
DEFINE_PUBLIC_ALIAS(DOS$fgetspent, libd_fgetspent);
DEFINE_PUBLIC_ALIAS(DOS$putspent, libd_putspent);
DEFINE_PUBLIC_ALIAS(DOS$getspent_r, libd_getspent_r);
DEFINE_PUBLIC_ALIAS(DOS$getspnam_r, libd_getspnam_r);
DEFINE_PUBLIC_ALIAS(DOS$sgetspent_r, libd_sgetspent_r);
DEFINE_PUBLIC_ALIAS(DOS$fgetspent_r, libd_fgetspent_r);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SHADOW_C */
