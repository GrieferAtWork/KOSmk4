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
#ifndef _KOS_HOP_FUTEX_H
#define _KOS_HOP_FUTEX_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include "openfd.h"

__DECL_BEGIN

/* HANDLE_TYPE_FUTEX */
#define HOP_FUTEX_OPEN_DATAPART          0x00160001 /* [struct hop_openfd *arg] Open the datapart associated with a given futex.
                                                     * @return: * : The value written to `result->of_hint'
                                                     * @return: -EOWNERDEAD: The datapart associated with the futex was destroyed. */
#define HOP_FUTEX_OPEN_DATABLOCK         0x00160002 /* [struct hop_openfd *arg] Open the datablock associated with the datapart associated with a given futex.
                                                     * @return: * : The value written to `result->of_hint'
                                                     * @return: -EOWNERDEAD: The datapart associated with the futex was destroyed. */
#define HOP_FUTEX_ISWAITING              0x00160003 /* @return: 1: There are threads are currently waiting on the futex
                                                     * @return: 0: No threads are waiting for this futex */
#define HOP_FUTEX_BROADCAST              0x00160004 /* Broadcast a wakeup-signal to all threads waiting for this futex.
                                                     * @return: *: The number of threads to which the signal was sent. */
/* TODO: HOP_FUTEX_GET_ADDRESS        (returns the address of the futex within its data-block) */
/* TODO: HOP_FUTEX_STAT               (Return HOP_FUTEX_ISWAITING, HOP_FUTEX_GET_ADDRESS, and some generalized info about HOP_FUTEX_OPEN_DATABLOCK) */

/* HANDLE_TYPE_FUTEXFD */
/* TODO: HOP_FUTEXFD_STAT             (returns a `HANDLE_TYPE_FUTEX' object) */
/* TODO: HOP_FUTEXFD_OPEN_FUTEX       (returns a `HANDLE_TYPE_FUTEX' object) */
/* TODO: HOP_FUTEXFD_OPEN_DATABLOCK   (returns a `HANDLE_TYPE_DATABLOCK' object) */

__DECL_END

#endif /* !_KOS_HOP_FUTEX_H */
