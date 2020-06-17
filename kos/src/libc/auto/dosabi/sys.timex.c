/* HASH CRC-32:0xf89133ad */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_TIMEX_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_TIMEX_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.timex.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_adjtimex)(struct timex *__restrict ntx) {
	return libc_adjtimex(ntx);
}
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_ntp_gettimex)(struct ntptimeval *__restrict ntv) {
	return libc_ntp_gettimex(ntv);
}
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_ntp_adjtime)(struct timex *__restrict tntx) {
	return libc_ntp_adjtime(tntx);
}
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_adjtimex64)(struct timex64 *__restrict ntx) {
	return libc_adjtimex64(ntx);
}
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_ntp_adjtime64)(struct timex64 *__restrict tntx) {
	return libc_ntp_adjtime64(tntx);
}
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_ntp_gettimex64)(struct ntptimeval64 *__restrict ntv) {
	return libc_ntp_gettimex64(ntv);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$__adjtimex, libd_adjtimex);
DEFINE_PUBLIC_ALIAS(DOS$adjtimex, libd_adjtimex);
DEFINE_PUBLIC_ALIAS(DOS$ntp_gettimex, libd_ntp_gettimex);
DEFINE_PUBLIC_ALIAS(DOS$ntp_adjtime, libd_ntp_adjtime);
DEFINE_PUBLIC_ALIAS(DOS$__adjtimex64, libd_adjtimex64);
DEFINE_PUBLIC_ALIAS(DOS$adjtimex64, libd_adjtimex64);
DEFINE_PUBLIC_ALIAS(DOS$ntp_adjtime64, libd_ntp_adjtime64);
DEFINE_PUBLIC_ALIAS(DOS$ntp_gettimex64, libd_ntp_gettimex64);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_TIMEX_C */
