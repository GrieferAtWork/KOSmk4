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
#ifndef _LIBVIOCORE_BITS_VIOCORE_H
#define _LIBVIOCORE_BITS_VIOCORE_H 1

#include <libviocore/api.h>
/**/

#include <libvio/vio.h>

#ifdef __CC__
__DECL_BEGIN

struct vio_emulate_args {
	struct vioargs vea_args;  /* [OVERRIDE(.va_state, [1..1])] Underlying VIO arguments. */
	vio_addr_t     vea_addr;  /* == vioargs_vioaddr(&.vea_args, .vea_ptrlo) */
	void          *vea_ptrlo; /* Lower virtual address at which the VIO fault happened. */
	void          *vea_ptrhi; /* Upper virtual address at which the VIO fault happened. */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIOCORE_BITS_VIOCORE_H */
