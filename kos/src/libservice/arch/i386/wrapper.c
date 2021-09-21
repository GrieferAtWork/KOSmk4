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

#include <hybrid/align.h>
#include <hybrid/host.h>

#include <kos/bits/userprocmask.h>
#include <kos/except.h>
#include <kos/syscalls.h>
#include <kos/types.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <libgen86/gen.h>
#include <libservice/client.h>

#include "../../com.h"

DECL_BEGIN

#ifndef __getuserprocmask_defined
#error "Generated wrapper functions assume that userprocmask is available and supported!"
#endif /* !__getuserprocmask_defined */



/* When the currently set exception is RT-level, return `false'.
 * Otherwise, clear the exception and return `true'. */
INTERN bool NOTHROW(FCALL libservice_aux_com_discard_nonrt_exception)(void) {
	struct exception_data *d = error_data();
	if (ERRORCLASS_ISRTLPRIORITY(d->e_class))
		return false;
	d->e_code = ERROR_CODEOF(E_OK);
	return true;
}

#define IS_NONBUFFER_TYPE(typ)                                                                    \
	((((typ) & _SERVICE_TYPE_CLASSMASK) == (_SERVICE_TYPE_ARCH_MIN & _SERVICE_TYPE_CLASSMASK)) && \
	 (((typ) & _SERVICE_TYPE_PARAMMASK) >= (_SERVICE_TYPE_ARCH_MIN & _SERVICE_TYPE_PARAMMASK)))

#ifdef __x86_64__
#define REGISTER_ARGUMENT_COUNT COMPILER_LENOF(sysvabi_registers)
static uint8_t const sysvabi_registers[] = {
	GEN86_R_RDI, GEN86_R_RSI, GEN86_R_RDX,
	GEN86_R_RCX, GEN86_R_R8, GEN86_R_R9
};
#else /* __x86_64__ */
#define REGISTER_ARGUMENT_COUNT 0
#endif /* !__x86_64__ */

#define USE_LODS_THRESHOLD 2 /* Use `lodsP' for stack arguments when there are at least this many word-sized reads */
#define USE_STOS_THRESHOLD 4 /* Use `stosP' when there are at least this many word-sized writes */





/* Implemented  by  arch-specific code:  Assemble  a custom
 * function that invokes a function as specified by `info',
 * returning a pointer to the base of said function.
 * @param: info:   Information about the function to-be called.
 * @param: result: [in|out] Buffer   storage   info.   Actually   used   buffer
 *                 sizes  are  written  back  to  `swb_txsiz'  and  `swb_ehsiz'
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
	return LIBSERVICE_DLSYM_CREATE_WRAPPER_SUCCESS;
}

DECL_END

#endif /* !GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C */
