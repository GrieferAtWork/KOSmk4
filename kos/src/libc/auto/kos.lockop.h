/* HASH CRC-32:0xc2b6ea47 */
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
#ifndef GUARD_LIBC_AUTO_KOS_LOCKOP_H
#define GUARD_LIBC_AUTO_KOS_LOCKOP_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/lockop.h>

DECL_BEGIN

INTDEF __NOBLOCK ATTR_INOUT(1) NONNULL((2, 3)) void NOTHROW(__LOCKOP_CC libc_lockop_reap_ex)(struct lockop_slist *__restrict self, __BOOL (__LOCKOP_CC *trylock)(void *cookie), void (__LOCKOP_CC *unlock)(void *cookie), void *cookie);
INTDEF __NOBLOCK ATTR_INOUT(1) NONNULL((2, 3, 5)) void NOTHROW(__LOCKOP_CC libc_oblockop_reap_ex)(struct oblockop_slist *__restrict self, __BOOL (__LOCKOP_CC *trylock)(void *cookie), void (__LOCKOP_CC *unlock)(void *cookie), void *cookie, void *__restrict obj);
INTDEF __NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) void NOTHROW(__LOCKOP_CC libc_lockop_reap_atomic_lock)(struct lockop_slist *__restrict self, struct atomic_lock *__restrict lock);
INTDEF __NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) NONNULL((3)) void NOTHROW(__LOCKOP_CC libc_oblockop_reap_atomic_lock)(struct oblockop_slist *__restrict self, struct atomic_lock *__restrict lock, void *__restrict obj);
INTDEF __NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) void NOTHROW(__LOCKOP_CC libc_lockop_reap_atomic_rwlock)(struct lockop_slist *__restrict self, struct atomic_rwlock *__restrict lock);
INTDEF __NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) NONNULL((3)) void NOTHROW(__LOCKOP_CC libc_oblockop_reap_atomic_rwlock)(struct oblockop_slist *__restrict self, struct atomic_rwlock *__restrict lock, void *__restrict obj);
INTDEF __NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) void NOTHROW(__LOCKOP_CC libc_lockop_reap_shared_lock)(struct lockop_slist *__restrict self, struct shared_lock *__restrict lock);
INTDEF __NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) NONNULL((3)) void NOTHROW(__LOCKOP_CC libc_oblockop_reap_shared_lock)(struct oblockop_slist *__restrict self, struct shared_lock *__restrict lock, void *__restrict obj);
INTDEF __NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) void NOTHROW(__LOCKOP_CC libc_lockop_reap_shared_rwlock)(struct lockop_slist *__restrict self, struct shared_rwlock *__restrict lock);
INTDEF __NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) NONNULL((3)) void NOTHROW(__LOCKOP_CC libc_oblockop_reap_shared_rwlock)(struct oblockop_slist *__restrict self, struct shared_rwlock *__restrict lock, void *__restrict obj);

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_LOCKOP_H */
