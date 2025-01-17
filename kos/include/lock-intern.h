/* HASH CRC-32:0xf627fc9a */
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
/* (#) Portability: GNU C Library (/mach/lock-intern.h) */
/* (#) Portability: GNU Hurd      (/usr/include/lock-intern.h) */
#ifndef _LOCK_INTERN_H
#define _LOCK_INTERN_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <kos/bits/shared-lock.h>
#include <kos/sched/shared-lock.h>
#include <hybrid/sched/__yield.h>

#ifdef __CC__
__SYSDECL_BEGIN

typedef unsigned int __spin_lock_t;
#define __SPIN_LOCK_INITIALIZER 0

#ifdef __CRT_HAVE___spin_lock_init
__CEIDECLARE(__ATTR_OUT(1),void,__NOTHROW_NCX,__spin_lock_init,(__spin_lock_t *__lock),{ *__lock = 0; })
#else /* __CRT_HAVE___spin_lock_init */
__LOCAL __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL __spin_lock_init)(__spin_lock_t *__lock) { *__lock = 0; }
#endif /* !__CRT_HAVE___spin_lock_init */
#ifdef __CRT_HAVE___spin_lock_solid
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__spin_lock_solid,(__spin_lock_t *__lock),(__lock))
#elif defined(__CRT_HAVE___spin_lock)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__spin_lock_solid,(__spin_lock_t *__lock),__spin_lock,(__lock))
#elif defined(__CRT_HAVE___mutex_lock)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__spin_lock_solid,(__spin_lock_t *__lock),__mutex_lock,(__lock))
#elif defined(__CRT_HAVE___mutex_lock_solid)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__spin_lock_solid,(__spin_lock_t *__lock),__mutex_lock_solid,(__lock))
#elif defined(__CRT_HAVE_mutex_wait_lock)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__spin_lock_solid,(__spin_lock_t *__lock),mutex_wait_lock,(__lock))
#elif defined(__CRT_HAVE_shared_lock_acquire) || defined(__KERNEL__) || defined(__shared_lock_wait_impl)
#include <libc/local/lock-intern/__spin_lock_solid.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__spin_lock_solid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) void __NOTHROW_NCX(__LIBCCALL __spin_lock_solid)(__spin_lock_t *__lock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__spin_lock_solid))(__lock); })
#endif /* ... */
#ifdef __CRT_HAVE___spin_lock
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__spin_lock,(__spin_lock_t *__lock),(__lock))
#elif defined(__CRT_HAVE___spin_lock_solid)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__spin_lock,(__spin_lock_t *__lock),__spin_lock_solid,(__lock))
#elif defined(__CRT_HAVE___mutex_lock)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__spin_lock,(__spin_lock_t *__lock),__mutex_lock,(__lock))
#elif defined(__CRT_HAVE___mutex_lock_solid)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__spin_lock,(__spin_lock_t *__lock),__mutex_lock_solid,(__lock))
#elif defined(__CRT_HAVE_mutex_wait_lock)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__spin_lock,(__spin_lock_t *__lock),mutex_wait_lock,(__lock))
#elif defined(__CRT_HAVE_shared_lock_acquire) || defined(__KERNEL__) || defined(__shared_lock_wait_impl)
#include <libc/local/lock-intern/__spin_lock_solid.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) void __NOTHROW_NCX(__LIBCCALL __spin_lock)(__spin_lock_t *__lock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__spin_lock_solid))(__lock); }
#endif /* ... */
#ifdef __CRT_HAVE___spin_unlock
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__spin_unlock,(__spin_lock_t *__lock),(__lock))
#elif defined(__CRT_HAVE___mutex_unlock)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__spin_unlock,(__spin_lock_t *__lock),__mutex_unlock,(__lock))
#elif defined(__CRT_HAVE_mutex_unlock)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__spin_unlock,(__spin_lock_t *__lock),mutex_unlock,(__lock))
#elif defined(__CRT_HAVE_shared_lock_release_ex) || defined(__shared_lock_release_ex) || (defined(__shared_lock_sendone) && defined(__shared_lock_sendall))
#include <libc/local/lock-intern/__spin_unlock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__spin_unlock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) void __NOTHROW_NCX(__LIBCCALL __spin_unlock)(__spin_lock_t *__lock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__spin_unlock))(__lock); })
#endif /* ... */
#ifdef __CRT_HAVE___spin_try_lock
__CDECLARE(__ATTR_INOUT(1),int,__NOTHROW_NCX,__spin_try_lock,(__spin_lock_t *__lock),(__lock))
#elif defined(__CRT_HAVE___mutex_trylock)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__spin_try_lock,(__spin_lock_t *__lock),__mutex_trylock,(__lock))
#else /* ... */
#include <libc/local/lock-intern/__spin_try_lock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__spin_try_lock, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL __spin_try_lock)(__spin_lock_t *__lock) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__spin_try_lock))(__lock); })
#endif /* !... */
#ifdef __CRT_HAVE___spin_lock_locked
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_NCX,__spin_lock_locked,(__spin_lock_t __KOS_FIXED_CONST *__lock),(__lock))
#elif defined(__shared_lock_available)
#include <libc/local/lock-intern/__spin_lock_locked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__spin_lock_locked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL __spin_lock_locked)(__spin_lock_t __KOS_FIXED_CONST *__lock) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__spin_lock_locked))(__lock); })
#endif /* ... */



/************************************************************************/
/* """Mutex""" API                                                      */
/************************************************************************/

#if 0
/* Hurd defines this struct here, but then it also defines it once  again
 * in `<cthreads.h>', which in turn also includes this header right here.
 *
 * So I have no idea how they're able to get gcc to compile a header that
 * effectively defines the same `struct mutex' 2 times (and even more so:
 * with differing field names).
 *
 * Anyways: KOS's Hurd emulation only defines this one in `<cthreads.h>' */
struct mutex {
	__spin_lock_t __held;   /* The actually used lock */
	__spin_lock_t __lock;   /* unused */
	const char   *__name;   /* unused */
	void         *__head;   /* unused */
	void         *__tail;   /* unused */
	void         *__holder; /* unused */
};
#define MUTEX_INITIALIZER { 0, 0, __NULLPTR, __NULLPTR, __NULLPTR, __NULLPTR }
#endif

#ifdef __CRT_HAVE___mutex_init
__CDECLARE_VOID(__ATTR_OUT(1),__NOTHROW_NCX,__mutex_init,(void *__lock),(__lock))
#elif defined(__CRT_HAVE___spin_lock_init)
__CREDIRECT_VOID(__ATTR_OUT(1),__NOTHROW_NCX,__mutex_init,(void *__lock),__spin_lock_init,(__lock))
#else /* ... */
__LOCAL __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL __mutex_init)(void *__lock) { *(unsigned int *)__lock = 0; }
#endif /* !... */
#ifdef __CRT_HAVE___mutex_lock
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__mutex_lock,(void *__lock),(__lock))
#elif defined(__CRT_HAVE___mutex_lock_solid)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__mutex_lock,(void *__lock),__mutex_lock_solid,(__lock))
#elif defined(__CRT_HAVE_mutex_wait_lock)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__mutex_lock,(void *__lock),mutex_wait_lock,(__lock))
#elif defined(__CRT_HAVE___spin_lock)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__mutex_lock,(void *__lock),__spin_lock,(__lock))
#elif defined(__CRT_HAVE___spin_lock_solid)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__mutex_lock,(void *__lock),__spin_lock_solid,(__lock))
#elif defined(__CRT_HAVE_shared_lock_acquire) || defined(__KERNEL__) || defined(__shared_lock_wait_impl)
#include <libc/local/lock-intern/__spin_lock_solid.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) void __NOTHROW_NCX(__LIBCCALL __mutex_lock)(void *__lock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__spin_lock_solid))((unsigned int *)__lock); }
#endif /* ... */
#ifdef __CRT_HAVE___mutex_lock_solid
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__mutex_lock_solid,(void *__lock),(__lock))
#elif defined(__CRT_HAVE___mutex_lock)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__mutex_lock_solid,(void *__lock),__mutex_lock,(__lock))
#elif defined(__CRT_HAVE_mutex_wait_lock)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__mutex_lock_solid,(void *__lock),mutex_wait_lock,(__lock))
#elif defined(__CRT_HAVE___spin_lock)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__mutex_lock_solid,(void *__lock),__spin_lock,(__lock))
#elif defined(__CRT_HAVE___spin_lock_solid)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__mutex_lock_solid,(void *__lock),__spin_lock_solid,(__lock))
#elif defined(__CRT_HAVE_shared_lock_acquire) || defined(__KERNEL__) || defined(__shared_lock_wait_impl)
#include <libc/local/lock-intern/__spin_lock_solid.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) void __NOTHROW_NCX(__LIBCCALL __mutex_lock_solid)(void *__lock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__spin_lock_solid))((unsigned int *)__lock); }
#endif /* ... */
#ifdef __CRT_HAVE___mutex_unlock
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__mutex_unlock,(void *__lock),(__lock))
#elif defined(__CRT_HAVE_mutex_unlock)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__mutex_unlock,(void *__lock),mutex_unlock,(__lock))
#elif defined(__CRT_HAVE___spin_unlock)
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__mutex_unlock,(void *__lock),__spin_unlock,(__lock))
#elif defined(__CRT_HAVE_shared_lock_release_ex) || defined(__shared_lock_release_ex) || (defined(__shared_lock_sendone) && defined(__shared_lock_sendall))
#include <libc/local/lock-intern/__spin_unlock.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) void __NOTHROW_NCX(__LIBCCALL __mutex_unlock)(void *__lock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__spin_unlock))((unsigned int *)__lock); }
#endif /* ... */
#ifdef __CRT_HAVE___mutex_unlock_solid
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,__mutex_unlock_solid,(void *__lock),(__lock))
#elif defined(__CRT_HAVE_shared_lock_waitfor) || defined(__KERNEL__) || defined(__shared_lock_wait_impl)
#include <libc/local/lock-intern/__mutex_unlock_solid.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__mutex_unlock_solid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) void __NOTHROW_NCX(__LIBCCALL __mutex_unlock_solid)(void *__lock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__mutex_unlock_solid))(__lock); })
#endif /* ... */
#ifdef __CRT_HAVE___mutex_trylock
__CDECLARE(__ATTR_INOUT(1),int,__NOTHROW_NCX,__mutex_trylock,(void *__lock),(__lock))
#elif defined(__CRT_HAVE___spin_try_lock)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__mutex_trylock,(void *__lock),__spin_try_lock,(__lock))
#else /* ... */
#include <libc/local/lock-intern/__spin_try_lock.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL __mutex_trylock)(void *__lock) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__spin_try_lock))((unsigned int *)__lock); }
#endif /* !... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_LOCK_INTERN_H */
