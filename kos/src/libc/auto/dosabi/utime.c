/* HASH CRC-32:0xd313df27 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_UTIME_C
#define GUARD_LIBC_AUTO_DOSABI_UTIME_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/utime.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_utime)(char const *filename,
                                 struct utimbuf const *file_times) {
	return libc_utime(filename, file_times);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_utime64)(char const *filename,
                                   struct utimbuf64 const *file_times) {
	return libc_utime64(filename, file_times);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") int
NOTHROW_RPC(LIBDCALL libd_futime)(fd_t fd,
                                  struct utimbuf const *file_times) {
	return libc_futime(fd, file_times);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify_time") int
NOTHROW_RPC(LIBDCALL libd_futime64)(fd_t fd,
                                    struct utimbuf64 const *file_times) {
	return libc_futime64(fd, file_times);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$_utime32, libd_utime);
DEFINE_PUBLIC_ALIAS(DOS$utime, libd_utime);
DEFINE_PUBLIC_ALIAS(DOS$_utime64, libd_utime64);
DEFINE_PUBLIC_ALIAS(DOS$utime64, libd_utime64);
DEFINE_PUBLIC_ALIAS(DOS$_futime32, libd_futime);
DEFINE_PUBLIC_ALIAS(DOS$futime, libd_futime);
DEFINE_PUBLIC_ALIAS(DOS$_futime64, libd_futime64);
DEFINE_PUBLIC_ALIAS(DOS$futime64, libd_futime64);

#endif /* !GUARD_LIBC_AUTO_DOSABI_UTIME_C */
