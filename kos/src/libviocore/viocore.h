/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBVIOCORE_VIOCORE_H
#define GUARD_LIBVIOCORE_VIOCORE_H 1

#include "api.h"
/**/

#include <libviocore/viocore.h>

#ifdef LIBVIO_CONFIG_ENABLED
DECL_BEGIN

/* Emulate the instruction pointed-to by `self->vea_args.va_state' and dispatch
 * any memory access made to `self->vea_ptrlo ... self->vea_ptrhi' via the  VIO
 * callback table.
 * Upon success, `self->vea_args.va_state' will point to the updated CPU state,
 * which may  be  placed  at  a  different address  than  it  was  upon  entry.
 * This function is intended to be called from a page fault handler. */
INTDEF void CC libviocore_emulate(struct vio_emulate_args *__restrict self);


DECL_END
#endif /* LIBVIO_CONFIG_ENABLED */

#endif /* !GUARD_LIBVIOCORE_VIOCORE_H */
