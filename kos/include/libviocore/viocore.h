/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBVIOCORE_VIOCORE_H
#define _LIBVIOCORE_VIOCORE_H 1

#include "api.h"

#include <libviocore/bits/viocore.h> /* struct vio_emulate_args */

#ifdef __CC__
__DECL_BEGIN

/* Emulate the instruction pointed-to by `self->vea_args.va_state' and dispatch
 * any memory access made to `self->vea_ptrlo ... self->vea_ptrhi' via the  VIO
 * callback table.
 * Upon success, `self->vea_args.va_state' will point to the updated CPU state,
 * which may  be  placed  at  a  different address  than  it  was  upon  entry.
 * This function is intended to be called from a page fault handler. */
typedef __ATTR_NONNULL_T((1)) void (LIBVIOCORE_CC *PVIOCORE_EMULATE)(struct vio_emulate_args *__restrict self);
#ifdef LIBVIOCORE_WANT_PROTOTYPES
LIBVIOCORE_DECL __ATTR_NONNULL((1)) void LIBVIOCORE_CC viocore_emulate(struct vio_emulate_args *__restrict self);
#endif /* LIBVIOCORE_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIOCORE_VIOCORE_H */
