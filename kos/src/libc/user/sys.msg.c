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
#ifndef GUARD_LIBC_USER_SYS_MSG_C
#define GUARD_LIBC_USER_SYS_MSG_C 1

#include "../api.h"
#include "sys.msg.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_msgctl,hash:CRC-32=0xf717f6e0]]]*/
/* Message queue control operation */
INTERN ATTR_SECTION(".text.crt.sched.msg") int
NOTHROW_NCX(LIBCCALL libc_msgctl)(int msqid,
                                  __STDC_INT_AS_UINT_T cmd,
                                  struct msqid_ds *buf)
/*[[[body:libc_msgctl]]]*/
/*AUTO*/{
	(void)msqid;
	(void)cmd;
	(void)buf;
	CRT_UNIMPLEMENTED("msgctl"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_msgctl]]]*/

/*[[[head:libc_msgget,hash:CRC-32=0x3b93d677]]]*/
/* Get messages queue */
INTERN ATTR_SECTION(".text.crt.sched.msg") int
NOTHROW_NCX(LIBCCALL libc_msgget)(key_t key,
                                  __STDC_INT_AS_UINT_T msgflg)
/*[[[body:libc_msgget]]]*/
/*AUTO*/{
	(void)key;
	(void)msgflg;
	CRT_UNIMPLEMENTED("msgget"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_msgget]]]*/

/*[[[head:libc_msgrcv,hash:CRC-32=0x7f9751e6]]]*/
/* Receive message from message queue */
INTERN ATTR_SECTION(".text.crt.sched.msg") ssize_t
NOTHROW_RPC(LIBCCALL libc_msgrcv)(int msqid,
                                  void *msgp,
                                  size_t msgsz,
                                  longptr_t msgtyp,
                                  __STDC_INT_AS_UINT_T msgflg)
/*[[[body:libc_msgrcv]]]*/
/*AUTO*/{
	(void)msqid;
	(void)msgp;
	(void)msgsz;
	(void)msgtyp;
	(void)msgflg;
	CRT_UNIMPLEMENTED("msgrcv"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_msgrcv]]]*/

/*[[[head:libc_msgsnd,hash:CRC-32=0x2749a6da]]]*/
/* Send message to message queue */
INTERN ATTR_SECTION(".text.crt.sched.msg") int
NOTHROW_RPC(LIBCCALL libc_msgsnd)(int msqid,
                                  const void *msgp,
                                  size_t msgsz,
                                  __STDC_INT_AS_UINT_T msgflg)
/*[[[body:libc_msgsnd]]]*/
/*AUTO*/{
	(void)msqid;
	(void)msgp;
	(void)msgsz;
	(void)msgflg;
	CRT_UNIMPLEMENTED("msgsnd"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_msgsnd]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x5e2c04b0]]]*/
DEFINE_PUBLIC_ALIAS(msgctl, libc_msgctl);
DEFINE_PUBLIC_ALIAS(msgget, libc_msgget);
DEFINE_PUBLIC_ALIAS(msgrcv, libc_msgrcv);
DEFINE_PUBLIC_ALIAS(msgsnd, libc_msgsnd);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_MSG_C */
