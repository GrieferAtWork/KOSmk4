/* HASH CRC-32:0xea6bed77 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_MSG_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_MSG_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.msg.h"

DECL_BEGIN

/* Message queue control operation */
INTERN ATTR_SECTION(".text.crt.dos.sched.msg") int
NOTHROW_NCX(LIBDCALL libd_msgctl)(int msqid,
                                  __STDC_INT_AS_UINT_T cmd,
                                  struct msqid_ds *buf) {
	return libc_msgctl(msqid, cmd, buf);
}
/* Get messages queue */
INTERN ATTR_SECTION(".text.crt.dos.sched.msg") int
NOTHROW_NCX(LIBDCALL libd_msgget)(key_t key,
                                  __STDC_INT_AS_UINT_T msgflg) {
	return libc_msgget(key, msgflg);
}
/* Receive message from message queue */
INTERN ATTR_SECTION(".text.crt.dos.sched.msg") ssize_t
NOTHROW_RPC(LIBDCALL libd_msgrcv)(int msqid,
                                  void *msgp,
                                  size_t msgsz,
                                  longptr_t msgtyp,
                                  __STDC_INT_AS_UINT_T msgflg) {
	return libc_msgrcv(msqid, msgp, msgsz, msgtyp, msgflg);
}
/* Send message to message queue */
INTERN ATTR_SECTION(".text.crt.dos.sched.msg") int
NOTHROW_RPC(LIBDCALL libd_msgsnd)(int msqid,
                                  const void *msgp,
                                  size_t msgsz,
                                  __STDC_INT_AS_UINT_T msgflg) {
	return libc_msgsnd(msqid, msgp, msgsz, msgflg);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$msgctl, libd_msgctl);
DEFINE_PUBLIC_ALIAS(DOS$msgget, libd_msgget);
DEFINE_PUBLIC_ALIAS(DOS$msgrcv, libd_msgrcv);
DEFINE_PUBLIC_ALIAS(DOS$msgsnd, libd_msgsnd);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_MSG_C */
