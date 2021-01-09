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
#ifndef _KOS_HOP_PIDNS_H
#define _KOS_HOP_PIDNS_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include "openfd.h"

__DECL_BEGIN

/* For `HANDLE_TYPE_PIDNS' */
#define HOP_PIDNS_GET_INDIRECTION 0x000f0001 /* [uint64_t *result] Return the indirection level of the given pidns */
#define HOP_PIDNS_OPEN_PARENT     0x000f0002 /* [struct hop_openfd *result] Open the parent of a given pidns.
                                              * @throw: E_NO_SUCH_PIDNS: The given PID namespace is the root-namespace. */

__DECL_END

#endif /* !_KOS_HOP_PIDNS_H */
