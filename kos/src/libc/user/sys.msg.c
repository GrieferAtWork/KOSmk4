/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_MSG_C
#define GUARD_LIBC_USER_SYS_MSG_C 1

#include "../api.h"
#include "sys.msg.h"

DECL_BEGIN

/*[[[head:libc_msgctl,hash:CRC-32=0x4dac60df]]]*/
INTERN ATTR_SECTION(".text.crt.sched.msg") int
NOTHROW_NCX(LIBCCALL libc_msgctl)(int msqid,
                                  __STDC_INT_AS_UINT_T cmd,
                                  struct msqid_ds *buf)
/*[[[body:libc_msgctl]]]*/
/*AUTO*/{
	(void)msqid;
	(void)cmd;
	(void)buf;
	CRT_UNIMPLEMENTEDF("msgctl(msqid: %x, cmd: %x, buf: %p)", msqid, cmd, buf); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_msgctl]]]*/

/*[[[head:libc_msgget,hash:CRC-32=0x5a133850]]]*/
INTERN ATTR_SECTION(".text.crt.sched.msg") int
NOTHROW_NCX(LIBCCALL libc_msgget)(key_t key,
                                  __STDC_INT_AS_UINT_T msgflg)
/*[[[body:libc_msgget]]]*/
/*AUTO*/{
	(void)key;
	(void)msgflg;
	CRT_UNIMPLEMENTEDF("msgget(key: %" PRIxN(__SIZEOF_KEY_T__) ", msgflg: %x)", key, msgflg); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_msgget]]]*/

/*[[[head:libc_msgrcv,hash:CRC-32=0xe47a8da2]]]*/
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
	CRT_UNIMPLEMENTEDF("msgrcv(msqid: %x, msgp: %p, msgsz: %Ix, msgtyp: %p, msgflg: %x)", msqid, msgp, msgsz, msgtyp, msgflg); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_msgrcv]]]*/

/*[[[head:libc_msgsnd,hash:CRC-32=0xc10861c1]]]*/
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
	CRT_UNIMPLEMENTEDF("msgsnd(msqid: %x, msgp: %p, msgsz: %Ix, msgflg: %x)", msqid, msgp, msgsz, msgflg); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_msgsnd]]]*/





/*[[[start:exports,hash:CRC-32=0x7f590877]]]*/
DEFINE_PUBLIC_ALIAS(msgctl, libc_msgctl);
DEFINE_PUBLIC_ALIAS(msgget, libc_msgget);
DEFINE_PUBLIC_ALIAS(__libc_msgrcv, libc_msgrcv);
DEFINE_PUBLIC_ALIAS(msgrcv, libc_msgrcv);
DEFINE_PUBLIC_ALIAS(__libc_msgsnd, libc_msgsnd);
DEFINE_PUBLIC_ALIAS(msgsnd, libc_msgsnd);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_MSG_C */
