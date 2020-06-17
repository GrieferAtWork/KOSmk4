/* HASH CRC-32:0x47d6667f */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_STROPTS_C
#define GUARD_LIBC_AUTO_DOSABI_STROPTS_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/stropts.h"

DECL_BEGIN

/* Test whether FILDES is associated with a STREAM-based file */
INTERN ATTR_SECTION(".text.crt.dos.io.stropts") int
NOTHROW(LIBDCALL libd_isastream)(fd_t fildes) {
	return libc_isastream(fildes);
}
/* Receive next message from a STREAMS file */
INTERN ATTR_SECTION(".text.crt.dos.io.stropts") int
NOTHROW_RPC(LIBDCALL libd_getmsg)(fd_t fildes,
                                  struct strbuf *__restrict ctlptr,
                                  struct strbuf *__restrict dataptr,
                                  int *__restrict flagsp) {
	return libc_getmsg(fildes, ctlptr, dataptr, flagsp);
}
/* Receive next message from a STREAMS file, with *FLAGSP allowing to control which message. */
INTERN ATTR_SECTION(".text.crt.dos.io.stropts") int
NOTHROW_RPC(LIBDCALL libd_getpmsg)(fd_t fildes,
                                   struct strbuf *__restrict ctlptr,
                                   struct strbuf *__restrict dataptr,
                                   int *__restrict bandp,
                                   int *__restrict flagsp) {
	return libc_getpmsg(fildes, ctlptr, dataptr, bandp, flagsp);
}
/* Send a message on a STREAM */
INTERN ATTR_SECTION(".text.crt.dos.io.stropts") int
NOTHROW_RPC(LIBDCALL libd_putmsg)(fd_t fildes,
                                  struct strbuf const *ctlptr,
                                  struct strbuf const *dataptr,
                                  int flags) {
	return libc_putmsg(fildes, ctlptr, dataptr, flags);
}
/* Send a message on a STREAM to the BAND */
INTERN ATTR_SECTION(".text.crt.dos.io.stropts") int
NOTHROW_RPC(LIBDCALL libd_putpmsg)(fd_t fildes,
                                   struct strbuf const *ctlptr,
                                   struct strbuf const *dataptr,
                                   int band,
                                   int flags) {
	return libc_putpmsg(fildes, ctlptr, dataptr, band, flags);
}
/* Attach a STREAMS-based file descriptor FILDES to a file PATH in the file system name space */
INTERN ATTR_SECTION(".text.crt.dos.io.stropts") NONNULL((2)) int
NOTHROW_RPC_KOS(LIBDCALL libd_fattach)(fd_t fildes,
                                       char const *__restrict path) {
	return libc_fattach(fildes, path);
}
/* Detach a name PATH from a STREAMS-based file descriptor */
INTERN ATTR_SECTION(".text.crt.dos.io.stropts") NONNULL((1)) int
NOTHROW_RPC_KOS(LIBDCALL libd_fdetach)(char const *__restrict path) {
	return libc_fdetach(path);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$isastream, libd_isastream);
DEFINE_PUBLIC_ALIAS(DOS$getmsg, libd_getmsg);
DEFINE_PUBLIC_ALIAS(DOS$getpmsg, libd_getpmsg);
DEFINE_PUBLIC_ALIAS(DOS$putmsg, libd_putmsg);
DEFINE_PUBLIC_ALIAS(DOS$putpmsg, libd_putpmsg);
DEFINE_PUBLIC_ALIAS(DOS$fattach, libd_fattach);
DEFINE_PUBLIC_ALIAS(DOS$fdetach, libd_fdetach);

#endif /* !GUARD_LIBC_AUTO_DOSABI_STROPTS_C */
