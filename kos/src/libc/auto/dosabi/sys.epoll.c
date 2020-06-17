/* HASH CRC-32:0x715110fc */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_EPOLL_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_EPOLL_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.epoll.h"

DECL_BEGIN

/* Creates an epoll instance.  Returns an fd for the new instance.
 * The "size" parameter is a hint specifying the number of file
 * descriptors to be associated with the new instance. The fd
 * returned by epoll_create() should be closed with close() */
INTERN ATTR_SECTION(".text.crt.dos.io.poll") WUNUSED fd_t
NOTHROW_NCX(LIBDCALL libd_epoll_create)(__STDC_INT_AS_SIZE_T size) {
	return libc_epoll_create(size);
}
/* Same as epoll_create but with an FLAGS parameter.
 * The unused SIZE parameter has been dropped
 * @param: flags: Set of `EPOLL_*' */
INTERN ATTR_SECTION(".text.crt.dos.io.poll") WUNUSED fd_t
NOTHROW_NCX(LIBDCALL libd_epoll_create1)(__STDC_INT_AS_UINT_T flags) {
	return libc_epoll_create1(flags);
}
/* Manipulate an epoll instance "epfd". Returns 0 in case of success,
 * -1 in case of error (the "errno" variable will contain the
 * specific error code) The "op" parameter is one of the EPOLL_CTL_*
 * constants defined above. The "fd" parameter is the target of the
 * operation. The "event" parameter describes which events the caller
 * is interested in and any associated user data */
INTERN ATTR_SECTION(".text.crt.dos.io.poll") int
NOTHROW_NCX(LIBDCALL libd_epoll_ctl)(fd_t epfd,
                                     enum __epoll_ctl op,
                                     fd_t fd,
                                     struct epoll_event *event) {
	return libc_epoll_ctl(epfd, op, fd, event);
}
/* Wait for events on an epoll instance "epfd". Returns the number of
 * triggered events returned in "events" buffer. Or -1 in case of
 * error with the "errno" variable set to the specific error code. The
 * "events" parameter is a buffer that will contain triggered
 * events. The "maxevents" is the maximum number of events to be
 * returned (usually size of "events"). The "timeout" parameter
 * specifies the maximum wait time in milliseconds (-1 == infinite). */
INTERN ATTR_SECTION(".text.crt.dos.io.poll") int
NOTHROW_RPC(LIBDCALL libd_epoll_wait)(fd_t epfd,
                                      struct epoll_event *events,
                                      __STDC_INT_AS_SIZE_T maxevents,
                                      int timeout) {
	return libc_epoll_wait(epfd, events, maxevents, timeout);
}
/* Same as epoll_wait, but the thread's signal mask is temporarily
 * and atomically replaced with the one provided as parameter */
INTERN ATTR_SECTION(".text.crt.dos.io.poll") int
NOTHROW_RPC(LIBDCALL libd_epoll_pwait)(fd_t epfd,
                                       struct epoll_event *events,
                                       __STDC_INT_AS_SIZE_T maxevents,
                                       int timeout,
                                       sigset_t const *ss) {
	return libc_epoll_pwait(epfd, events, maxevents, timeout, ss);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$epoll_create, libd_epoll_create);
DEFINE_PUBLIC_ALIAS(DOS$epoll_create1, libd_epoll_create1);
DEFINE_PUBLIC_ALIAS(DOS$epoll_ctl, libd_epoll_ctl);
DEFINE_PUBLIC_ALIAS(DOS$epoll_wait, libd_epoll_wait);
DEFINE_PUBLIC_ALIAS(DOS$epoll_pwait, libd_epoll_pwait);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_EPOLL_C */
