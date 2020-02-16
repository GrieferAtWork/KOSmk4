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
#ifndef GUARD_KERNEL_SRC_DEV_NIC_C
#define GUARD_KERNEL_SRC_DEV_NIC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/types.h>
#include <kernel/aio.h>
#include <stddef.h>

DECL_BEGIN

/* Default write-operator for NIC devices. */
PUBLIC NONNULL((1)) size_t KCALL
nic_device_write(struct character_device *__restrict self,
                 USER CHECKED void const *src,
                 size_t num_bytes, iomode_t UNUSED(mode))
		THROWS(...) {
	struct nic_packet packet;
	struct nic_device *me;
	struct aio_handle_generic aio;
	me = (struct nic_device *)self;
	aio_handle_generic_init(&aio);

	/* Send a simple packet. */
	packet.np_head   = (USER CHECKED void *)src;
	packet.np_headsz = num_bytes;
	packet.np_inner  = NULL;
	packet.np_tail   = NULL;
	packet.np_tailsz = 0;
	packet.np_total  = num_bytes;
	(*me->nd_ops.nd_send)(me, &packet, &aio);

	/* Wait for the send to finish. */
	TRY {
		aio_handle_generic_waitfor(&aio);
		aio_handle_generic_checkerror(&aio);
	} EXCEPT {
		aio_handle_generic_fini(&aio);
		RETHROW();
	}
	aio_handle_generic_fini(&aio);
	return num_bytes;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_NIC_C */
