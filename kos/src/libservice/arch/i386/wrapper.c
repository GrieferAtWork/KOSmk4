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
#ifndef GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C
#define GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C 1
#define _KOS_SOURCE 1

#include "../../api.h"
/**/

#include <kos/except.h>
#include <kos/types.h>

#include <stdlib.h>
#include <string.h>

#include <libservice/client.h>

#include "../../com.h"

DECL_BEGIN

/* Implemented  by  arch-specific code:  Assemble  a custom
 * function that invokes a function as specified by `info',
 * returning a pointer to the  base of said function.
 * @param: info:   Information about the function to-be called.
 * @param: result: [in|out] Buffer storage info. Actually used buffer
 *                 sizes are written back to `swb_txsiz' and `swb_ehsiz'
 *                 prior to returning `LIBSERVICE_DLSYM_CREATE_WRAPPER_SUCCESS'
 * @param: flags:  Set of `SERVICE_WRAPPER_FLAG_*'
 * @return: * : One of `LIBSERVICE_DLSYM_CREATE_WRAPPER_*' */
INTDEF WUNUSED NONNULL((1, 2, 3)) unsigned int
NOTHROW(CC libservice_dlsym_create_wrapper)(struct service *__restrict self,
                                            struct service_com_funinfo const *__restrict info,
                                            struct service_wrapper_buffer *__restrict buffers,
                                            unsigned int flags) {
	/* TODO */
	(void)self;
	(void)info;
	(void)buffers;
	(void)flags;
	abort();
}

DECL_END

#endif /* !GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C */
