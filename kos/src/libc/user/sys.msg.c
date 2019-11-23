/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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

/*[[[head:msgctl,hash:CRC-32=0x2e14daed]]]*/
/* Message queue control operation */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.msg.msgctl") int
NOTHROW_NCX(LIBCCALL libc_msgctl)(int msqid,
                                  int cmd,
                                  struct msqid_ds *buf)
/*[[[body:msgctl]]]*/
{
	(void)msqid;
	(void)cmd;
	(void)buf;
	CRT_UNIMPLEMENTED("msgctl"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:msgctl]]]*/

/*[[[head:msgget,hash:CRC-32=0xb918008d]]]*/
/* Get messages queue */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.msg.msgget") int
NOTHROW_NCX(LIBCCALL libc_msgget)(key_t key,
                                  int msgflg)
/*[[[body:msgget]]]*/
{
	(void)key;
	(void)msgflg;
	CRT_UNIMPLEMENTED("msgget"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:msgget]]]*/

/*[[[head:msgrcv,hash:CRC-32=0xf3780846]]]*/
/* Receive message from message queue */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.msg.msgrcv") ssize_t
NOTHROW_RPC(LIBCCALL libc_msgrcv)(int msqid,
                                  void *msgp,
                                  size_t msgsz,
                                  longptr_t msgtyp,
                                  int msgflg)
/*[[[body:msgrcv]]]*/
{
	(void)msqid;
	(void)msgp;
	(void)msgsz;
	(void)msgtyp;
	(void)msgflg;
	CRT_UNIMPLEMENTED("msgrcv"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:msgrcv]]]*/

/*[[[head:msgsnd,hash:CRC-32=0x4b0dd8b0]]]*/
/* Send message to message queue */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.msg.msgsnd") int
NOTHROW_RPC(LIBCCALL libc_msgsnd)(int msqid,
                                  const void *msgp,
                                  size_t msgsz,
                                  int msgflg)
/*[[[body:msgsnd]]]*/
{
	(void)msqid;
	(void)msgp;
	(void)msgsz;
	(void)msgflg;
	CRT_UNIMPLEMENTED("msgsnd"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:msgsnd]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xd4606b2c]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(msgctl, libc_msgctl);
DEFINE_PUBLIC_WEAK_ALIAS(msgget, libc_msgget);
DEFINE_PUBLIC_WEAK_ALIAS(msgrcv, libc_msgrcv);
DEFINE_PUBLIC_WEAK_ALIAS(msgsnd, libc_msgsnd);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_MSG_C */
