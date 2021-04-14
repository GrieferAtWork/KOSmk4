/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
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

/************************************************************************/
/* HANDLE_TYPE_FUTEX                                                    */
/************************************************************************/
/* [struct hop_openfd *arg] Open the datapart associated with a given futex.
 * @return: * : The value written to `result->of_hint'
 * @return: -EOWNERDEAD: The datapart associated with the futex was destroyed. */
#define HOP_FUTEX_OPEN_MPART       HOP_CMD(HANDLE_TYPE_FUTEX, 0x0001)

/* [struct hop_openfd *arg] Open the datablock associated with the datapart associated with a given futex.
 * @return: * : The value written to `result->of_hint'
 * @return: -EOWNERDEAD: The datapart associated with the futex was destroyed. */
#define HOP_FUTEX_OPEN_MFILE       HOP_CMD(HANDLE_TYPE_FUTEX, 0x0002)

/* @return: 1: There are threads currently waiting on the futex
 * @return: 0: No threads are waiting for this futex */
#define HOP_FUTEX_ISWAITING        HOP_CMD(HANDLE_TYPE_FUTEX, 0x0003)

/* Broadcast a wakeup-signal to all threads waiting for this futex.
 * @return: *: The number of threads to which the signal was sent. */
#define HOP_FUTEX_BROADCAST        HOP_CMD(HANDLE_TYPE_FUTEX, 0x0004)

/* TODO: HOP_FUTEX_GET_ADDRESS        (returns the address of the futex within its data-block) */
/* TODO: HOP_FUTEX_STAT               (Return HOP_FUTEX_ISWAITING, HOP_FUTEX_GET_ADDRESS, and some generalized info about HOP_FUTEX_OPEN_MFILE) */

/* HANDLE_TYPE_FUTEXFD */
/* TODO: HOP_FUTEXFD_STAT             (returns a `HANDLE_TYPE_FUTEX' object) */
/* TODO: HOP_FUTEXFD_OPEN_FUTEX       (returns a `HANDLE_TYPE_FUTEX' object) */
/* TODO: HOP_FUTEXFD_OPEN_DATABLOCK   (returns a `HANDLE_TYPE_MFILE' object) */

__DECL_END

#endif /* !_KOS_HOP_FUTEX_H */
