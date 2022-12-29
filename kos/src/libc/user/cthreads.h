/* HASH CRC-32:0x223fab46 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_CTHREADS_H
#define GUARD_LIBC_USER_CTHREADS_H 1

#include "../api.h"
#include "../auto/cthreads.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <cthreads.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF int NOTHROW_NCX(LIBCCALL libc_cond_signal)(condition_t self);
INTDEF void NOTHROW_NCX(LIBCCALL libc_cond_broadcast)(condition_t self);
INTDEF void NOTHROW_NCX(LIBCCALL libc_condition_wait)(condition_t self, mutex_t mutex);
INTDEF void NOTHROW_NCX(LIBCCALL libc_condition_implies)(condition_t implicator, condition_t implicatand);
INTDEF void NOTHROW_NCX(LIBCCALL libc_condition_unimplies)(condition_t implicator, condition_t implicatand);
INTDEF vm_offset_t NOTHROW_NCX(LIBCCALL libc_cthread_sp)(void);
INTDEF ur_cthread_t NOTHROW_NCX(LIBCCALL libc_ur_cthread_self)(void);
INTDEF ATTR_IN(1) char const *NOTHROW_NCX(LIBCCALL libc_cthread_name)(cthread_t self);
/* >> cthread_count(3)
 * Return the number of running threads (s.a. `DLAUXCTRL_GET_MAIN_TLSSEG') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_cthread_count)(void);
/* >> cthread_set_data(3)
 * Set the value of a TLS variable for `self' */
INTDEF ATTR_ACCESS_NONE(2) int NOTHROW_NCX(LIBCCALL libc_cthread_set_data)(cthread_t self, void *value);
/* >> cthread_data(3)
 * Get the value of a TLS variable for `self' */
INTDEF void *NOTHROW_NCX(LIBCCALL libc_cthread_data)(cthread_t self);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_CTHREADS_H */
