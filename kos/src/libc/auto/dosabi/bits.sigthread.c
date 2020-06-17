/* HASH CRC-32:0xa043d0aa */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_BITS_SIGTHREAD_C
#define GUARD_LIBC_AUTO_DOSABI_BITS_SIGTHREAD_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/bits.sigthread.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") int
NOTHROW_NCX(LIBDCALL libd_pthread_sigmask)(int how,
                                           sigset_t const *newmask,
                                           sigset_t *oldmask) {
	return libc_pthread_sigmask(how, newmask, oldmask);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") int
NOTHROW_NCX(LIBDCALL libd_pthread_kill)(pthread_t threadid,
                                        int signo) {
	return libc_pthread_kill(threadid, signo);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.pthread") int
NOTHROW_NCX(LIBDCALL libd_pthread_sigqueue)(pthread_t threadid,
                                            int signo,
                                            union sigval const value) {
	return libc_pthread_sigqueue(threadid, signo, value);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$pthread_sigmask, libd_pthread_sigmask);
DEFINE_PUBLIC_ALIAS(DOS$pthread_kill, libd_pthread_kill);
DEFINE_PUBLIC_ALIAS(DOS$pthread_sigqueue, libd_pthread_sigqueue);

#endif /* !GUARD_LIBC_AUTO_DOSABI_BITS_SIGTHREAD_C */
