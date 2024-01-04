/* HASH CRC-32:0xd651d898 */
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
#ifndef GUARD_LIBC_AUTO_STROPTS_H
#define GUARD_LIBC_AUTO_STROPTS_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stropts.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_FDARG(1) int NOTHROW(LIBDCALL libd_isastream)(fd_t fd);
/* @param: pflags: Set of `MSG_HIPRI | MSG_ANY | MSG_BAND'
 * @return: MORECTL:  ???
 * @return: MOREDATA: ??? */
INTDEF ATTR_FDARG(1) int NOTHROW_RPC(LIBDCALL libd_getmsg)(fd_t fd, struct strbuf *__restrict ctlptr, struct strbuf *__restrict dataptr, __STDC_INT_AS_UINT_T *__restrict pflags);
/* @param: pflags: Set of `MSG_HIPRI | MSG_ANY | MSG_BAND'
 * @return: MORECTL:  ???
 * @return: MOREDATA: ??? */
INTDEF ATTR_FDARG(1) int NOTHROW_RPC(LIBDCALL libd_getpmsg)(fd_t fd, struct strbuf *__restrict ctlptr, struct strbuf *__restrict dataptr, int *__restrict bandp, __STDC_INT_AS_UINT_T *__restrict pflags);
/* @param: flags: Set of `MSG_HIPRI | MSG_ANY | MSG_BAND' */
INTDEF ATTR_FDARG(1) int NOTHROW_RPC(LIBDCALL libd_putmsg)(fd_t fd, struct strbuf const *ctlptr, struct strbuf const *dataptr, __STDC_INT_AS_UINT_T flags);
/* @param: flags: Set of `MSG_HIPRI | MSG_ANY | MSG_BAND' */
INTDEF ATTR_FDARG(1) int NOTHROW_RPC(LIBDCALL libd_putpmsg)(fd_t fd, struct strbuf const *ctlptr, struct strbuf const *dataptr, __STDC_INT_AS_UINT_T band, __STDC_INT_AS_UINT_T flags);
INTDEF ATTR_FDARG(1) ATTR_IN(2) int NOTHROW_RPC_KOS(LIBDCALL libd_fattach)(fd_t fd, char const *__restrict path);
INTDEF ATTR_IN(1) int NOTHROW_RPC_KOS(LIBDCALL libd_fdetach)(char const *__restrict path);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STROPTS_H */
