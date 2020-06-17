/* HASH CRC-32:0x3479820c */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_TIMEB_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_TIMEB_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.timeb.h"

DECL_BEGIN

/* Fill in TIMEBUF with information about the current time */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd__ftime32)(struct timeb32 *timebuf) {
	libc__ftime32(timebuf);
}
/* Fill in TIMEBUF with information about the current time */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd__ftime64)(struct timeb64 *timebuf) {
	libc__ftime64(timebuf);
}
/* Fill in TIMEBUF with information about the current time */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) errno_t
NOTHROW_NCX(LIBDCALL libd__ftime32_s)(struct timeb32 *timebuf) {
	return libc__ftime32_s(timebuf);
}
/* Fill in TIMEBUF with information about the current time */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) errno_t
NOTHROW_NCX(LIBDCALL libd__ftime64_s)(struct timeb64 *timebuf) {
	return libc__ftime64_s(timebuf);
}
/* Fill in TIMEBUF with information about the current time */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_ftime)(struct timeb *timebuf) {
	return libc_ftime(timebuf);
}
/* Fill in TIMEBUF with information about the current time */
INTERN ATTR_SECTION(".text.crt.dos.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_ftime64)(struct timeb64 *timebuf) {
	return libc_ftime64(timebuf);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$_ftime32, libd__ftime32);
DEFINE_PUBLIC_ALIAS(DOS$_ftime64, libd__ftime64);
DEFINE_PUBLIC_ALIAS(DOS$_ftime32_s, libd__ftime32_s);
DEFINE_PUBLIC_ALIAS(DOS$_ftime64_s, libd__ftime64_s);
DEFINE_PUBLIC_ALIAS(DOS$ftime, libd_ftime);
DEFINE_PUBLIC_ALIAS(DOS$ftime64, libd_ftime64);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_TIMEB_C */
