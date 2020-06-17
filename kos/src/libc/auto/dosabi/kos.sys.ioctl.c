/* HASH CRC-32:0x771ab7ff */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_KOS_SYS_IOCTL_C
#define GUARD_LIBC_AUTO_DOSABI_KOS_SYS_IOCTL_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/kos.sys.ioctl.h"

DECL_BEGIN

/* Perform the I/O control operation specified by REQUEST on FD.
 * One argument may follow; its presence and type depend on REQUEST.
 * Return value depends on REQUEST. Usually -1 indicates error */
INTERN ATTR_SECTION(".text.crt.dos.except.io.utility") ssize_t
(VLIBDCALL libd_Ioctl)(fd_t fd,
                       unsigned long int request,
                       ...) THROWS(...) {
	va_list args;
	void *v0;
	va_start(args, request);
	v0 = va_arg(args, void *);
	va_end(args);
	return libc_Ioctl(fd, request, v0);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$Ioctl, libd_Ioctl);

#endif /* !GUARD_LIBC_AUTO_DOSABI_KOS_SYS_IOCTL_C */
