/* HASH CRC-32:0x2345b3b */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_FSUID_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_FSUID_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.fsuid.h"

DECL_BEGIN

/* Change uid used for file access control to UID, without affecting
 * other privileges (such as who can send signals at the process) */
INTERN ATTR_SECTION(".text.crt.dos.sched.user") int
NOTHROW_NCX(LIBDCALL libd_setfsuid)(uid_t uid) {
	return libc_setfsuid(uid);
}
/* Ditto for group id */
INTERN ATTR_SECTION(".text.crt.dos.sched.user") int
NOTHROW_NCX(LIBDCALL libd_setfsgid)(gid_t gid) {
	return libc_setfsgid(gid);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$setfsuid, libd_setfsuid);
DEFINE_PUBLIC_ALIAS(DOS$setfsgid, libd_setfsgid);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_FSUID_C */
