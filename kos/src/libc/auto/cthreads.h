/* HASH CRC-32:0xe061a979 */
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
#ifndef GUARD_LIBC_AUTO_CTHREADS_H
#define GUARD_LIBC_AUTO_CTHREADS_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <cthreads.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF vm_offset_t NOTHROW_NCX(LIBCCALL libc_cthread_init)(void);
INTDEF NONNULL((1)) cthread_t NOTHROW_NCX(LIBCCALL libc_cthread_fork)(any_t (LIBCCALL *start_routine)(any_t arg), any_t arg);
INTDEF any_t NOTHROW_NCX(LIBCCALL libc_cthread_join)(cthread_t self);
INTDEF int NOTHROW_NCX(LIBCCALL libc_cthread_abort)(cthread_t self);
/* >> cthread_set_limit(3)
 * No-op */
INTDEF void NOTHROW_NCX(LIBCCALL libc_cthread_set_limit)(int limit);
/* >> cthread_limit(3)
 * No-op (always returns `INT_MAX') */
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc_cthread_limit)(void);
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_cthread_keycreate)(cthread_key_t *key);
INTDEF ATTR_OUT(2) int NOTHROW_NCX(LIBCCALL libc_cthread_getspecific)(cthread_key_t key, void **p_value);
INTDEF ATTR_ACCESS_NONE(2) int NOTHROW_NCX(LIBCCALL libc_cthread_setspecific)(cthread_key_t key, void *value);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CTHREADS_H */
