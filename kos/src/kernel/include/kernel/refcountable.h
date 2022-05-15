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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_REFCOUNTABLE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_REFCOUNTABLE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

/*
 * General purpose, refcountable object base (w/ handle support)
 *
 * This type of object is mainly meant for use with other kernel
 * API that require the use of handle-compatible objects,  where
 * the current use case is such  that the object in question  is
 * never actually exposed to user-space.
 *
 * `refcountable' (HANDLE_TYPE_REFCOUNTABLE) objects can in theory
 * be exposed to user-space, but userspace probably won't be  able
 * to do anything with them other than standard handle  operations
 * as well as `close(2)'
 */
struct refcountable {
	/* [HANDLE_TYPE(HANDLE_TYPE_REFCOUNTABLE)] */
	WEAK refcnt_t rca_refcnt; /* Reference counter */

	/* [1..1][const] Destructor callback */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (FCALL *rca_destroy)(struct refcountable *__restrict self);

	/* The real *magic* of what this object probably is goes here. (sub-classes) */
};

#define refcountable_destroy(self) ((*(self)->rca_destroy)(self))
DEFINE_REFCNT_FUNCTIONS(struct refcountable, rca_refcnt, refcountable_destroy)

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_REFCOUNTABLE_H */
