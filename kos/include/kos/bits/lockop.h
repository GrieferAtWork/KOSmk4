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
/*!replace_with_include <kos/lockop.h>*/
#ifndef _KOS_BITS_LOCKOP_H
#define _KOS_BITS_LOCKOP_H 1

#include <__stdinc.h>

#include <kos/anno.h>
#include <kos/asm/lockop.h> /* __LOCKOP_CC */

#ifndef __LOCKOP_CC
#include <__crt.h>
#define __LOCKOP_CC __LIBKCALL
#endif /* !__LOCKOP_CC */

#ifdef __CC__
__DECL_BEGIN

/* Callback prototype for an operation to-be performed once locks have been released. */
typedef __NOBLOCK __ATTR_NONNULL_T((1)) void
__NOTHROW_T(__LOCKOP_CC *__postlockop_callback_t)(struct postlockop *__restrict __self);
typedef __NOBLOCK __ATTR_NONNULL_T((1, 2)) void
__NOTHROW_T(__LOCKOP_CC *__obpostlockop_callback_t)(struct obpostlockop *__restrict __self,
                                                    void *__restrict __obj);

/* Callback prototype for pending locked operations.
 * @return: NULL: Completed.
 * @return: * :   A descriptor for an operation to perform after the lock has been released. */
typedef __NOBLOCK __ATTR_NONNULL_T((1)) struct postlockop *
__NOTHROW_T(__LOCKOP_CC *__lockop_callback_t)(struct lockop *__restrict __self);
typedef __NOBLOCK __ATTR_NONNULL_T((1, 2)) struct obpostlockop *
__NOTHROW_T(__LOCKOP_CC *__oblockop_callback_t)(struct oblockop *__restrict __self, void *__restrict __obj);

struct postlockop {
/*	SLIST_ENTRY(postlockop)                 plo_link; */
	struct { struct postlockop *sle_next; } plo_link; /* [0..1] Next post-lock operation. */
	__postlockop_callback_t                 plo_func; /* [1..1][const] Callback to invoke. */
};

struct obpostlockop {
/*	SLIST_ENTRY(obpostlockop)                 oplo_link; */
	struct { struct obpostlockop *sle_next; } oplo_link; /* [0..1] Next post-lock operation. */
	__obpostlockop_callback_t                 oplo_func; /* [1..1][const] Callback to invoke. */
};

struct lockop {
/*	SLIST_ENTRY(lockop)                 lo_link; */
	struct { struct lockop *sle_next; } lo_link; /* [0..1] Next lock operation. */
	__lockop_callback_t                 lo_func; /* [1..1][const] Operation to perform. */
};

struct oblockop {
/*	SLIST_ENTRY(oblockop)                 olo_link; */
	struct { struct oblockop *sle_next; } olo_link; /* [0..1] Next lock operation. */
	__oblockop_callback_t                 olo_func; /* [1..1][const] Operation to perform. */
};

/* Should be `SLIST_HEAD(lockop_slist, lockop);' (but isn't to prevent dependency on <hybrid/sequence/list.h>) */
struct lockop_slist {
	struct lockop *slh_first; /* [0..1] List head */
};

/* `SLIST_HEAD(postlockop_slist, postlockop);' (but isn't to prevent dependency on <hybrid/sequence/list.h>)  */
struct postlockop_slist {
	struct postlockop *slh_first; /* [0..1] List head */
};

/* `SLIST_HEAD(oblockop_slist, oblockop);' (but isn't to prevent dependency on <hybrid/sequence/list.h>)  */
struct oblockop_slist {
	struct oblockop *slh_first; /* [0..1] List head */
};

/* `SLIST_HEAD(obpostlockop_slist, obpostlockop);' (but isn't to prevent dependency on <hybrid/sequence/list.h>)  */
struct obpostlockop_slist {
	struct obpostlockop *slh_first; /* [0..1] List head */
};


__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_BITS_LOCKOP_H */
