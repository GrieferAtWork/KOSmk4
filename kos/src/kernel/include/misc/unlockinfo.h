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
#ifndef GUARD_KERNEL_INCLUDE_MISC_UNLOCKINFO_H
#define GUARD_KERNEL_INCLUDE_MISC_UNLOCKINFO_H 1

#include <kernel/compiler.h>

#ifdef __CC__
DECL_BEGIN

struct unlockinfo;
struct unlockinfo {
	/* [1..1] Callback that is invoked in order to release
	 *        additional locks when  a blocking  operation
	 *        is performed by an `*_or_unlock()' function.
	 * This callback may then be used to release additional atomic
	 * locks which the caller may be holding, and it guarantied to
	 * be called on all `return == false' and `EXCEPT' braches  of
	 * the called `*_or_unlock()' function. */
#ifdef __INTELLISENSE__
	/*   */ NONNULL_T((1)) void NOTHROW_T(FCALL *ui_unlock)(struct unlockinfo *__restrict self);
#else /* __INTELLISENSE__ */
	NOBLOCK NONNULL_T((1)) void NOTHROW_T(FCALL *ui_unlock)(struct unlockinfo *__restrict self);
#endif /* !__INTELLISENSE__ */
};

/* NOTE: *_or_unlock() functions that use `struct unlockinfo' usually follow
 *       the following locking logic:
 *  - return == true:   REQUESTED_CONDITION_MET && UNLOCK_NOT_INVOKED;
 *  - return == false:  UNLOCK_INVOKED;
 *  - EXCEPT:           UNLOCK_INVOKED; */


/* When `self' is non-NULL, invoke it's `ui_unlock'-callback. */
#define unlockinfo_xunlock(self) \
	(void)(!(self) || ((*(self)->ui_unlock)(self), 0))
#define unlockinfo_unlock(self) \
	(void)((*(self)->ui_unlock)(self), 0)

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_MISC_UNLOCKINFO_H */
