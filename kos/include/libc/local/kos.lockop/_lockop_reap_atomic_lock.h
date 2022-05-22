/* HASH CRC-32:0x98e0bc2b */
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
#ifndef __local__lockop_reap_atomic_lock_defined
#define __local__lockop_reap_atomic_lock_defined
#include <__crt.h>
#include <kos/anno.h>
#ifndef __LOCKOP_CC
#define __LOCKOP_CC __LIBKCALL
#endif /* !__LOCKOP_CC */
struct lockop_slist;
struct atomic_lock;
#ifndef _KOS_LOCKOP_H
#include <kos/lockop.h>
#endif /* !_KOS_LOCKOP_H */
#include <hybrid/__atomic.h>
#include <hybrid/sync/atomic-lock.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_lockop_reap_atomic_lock) __NOBLOCK __ATTR_ACCESS_RW(1) __ATTR_ACCESS_RW(2) void
__NOTHROW(__LOCKOP_CC __LIBC_LOCAL_NAME(_lockop_reap_atomic_lock))(struct lockop_slist *__restrict __self, struct atomic_lock *__restrict __lock) {
#ifndef __INTELLISENSE__
#define __LOCAL_self      __self
#undef __LOCAL_obj
#define __LOCAL_trylock() atomic_lock_tryacquire(__lock)
#define __LOCAL_unlock()  atomic_lock_release(__lock)
#include <libc/template/lockop.h>
#endif /* !__INTELLISENSE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__lockop_reap_atomic_lock_defined
#define __local___localdep__lockop_reap_atomic_lock_defined
#define __localdep__lockop_reap_atomic_lock __LIBC_LOCAL_NAME(_lockop_reap_atomic_lock)
#endif /* !__local___localdep__lockop_reap_atomic_lock_defined */
#endif /* !__local__lockop_reap_atomic_lock_defined */
