/* HASH CRC-32:0x4902c9d8 */
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
#ifndef GUARD_LIBC_AUTO_KOS_FUTEX_C
#define GUARD_LIBC_AUTO_KOS_FUTEX_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/kos.futex.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <hybrid/__atomic.h>
/* Check if `futex_waitwhile()' would block
 * @return: 0: `futex_waitwhile()' would block
 * @return: 1: `futex_waitwhile()' wouldn't block */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_futex_trywaitwhile)(lfutex_t *uaddr,
                                              lfutex_t equal_to_value) {
	return __hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) == equal_to_value ? 0 : 1;
}
#include <hybrid/__atomic.h>
/* Check if `futex_waituntil()' would block
 * @return: 0: `futex_waituntil()' would block
 * @return: 1: `futex_waituntil()' wouldn't block */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_futex_trywaituntil)(lfutex_t *uaddr,
                                              lfutex_t not_equal_to_value) {
	return __hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) != not_equal_to_value ? 0 : 1;
}
#include <hybrid/__atomic.h>
/* Check if `futex_waitwhile_equal()' would block
 * @return: 0: `futex_waitwhile_equal()' would block
 * @return: 1: `futex_waitwhile_equal()' wouldn't block */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_futex_trywaitwhile_equal)(lfutex_t *uaddr,
                                                    lfutex_t equal_to_value) {
	return __hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) == equal_to_value ? 0 : 1;
}
#include <hybrid/__atomic.h>
/* Check if `futex_waitwhile_notequal()' would block
 * @return: 0: `futex_waitwhile_notequal()' would block
 * @return: 1: `futex_waitwhile_notequal()' wouldn't block */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_futex_trywaitwhile_notequal)(lfutex_t *uaddr,
                                                       lfutex_t not_equal_to_value) {
	return __hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) != not_equal_to_value ? 0 : 1;
}
#include <hybrid/__atomic.h>
/* Check if `futex_waitwhile_above()' would block
 * @return: 0: `futex_waitwhile_above()' would block
 * @return: 1: `futex_waitwhile_above()' wouldn't block */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_futex_trywaitwhile_above)(lfutex_t *uaddr,
                                                    lfutex_t above_value) {
	return __hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) > above_value ? 0 : 1;
}
#include <hybrid/__atomic.h>
/* Check if `futex_waitwhile_below()' would block
 * @return: 0: `futex_waitwhile_below()' would block
 * @return: 1: `futex_waitwhile_below()' wouldn't block */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_futex_trywaitwhile_below)(lfutex_t *uaddr,
                                                    lfutex_t below_value) {
	return __hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) < below_value ? 0 : 1;
}
#include <hybrid/__atomic.h>
/* Check if `futex_waitwhile_aboveequal()' would block
 * @return: 0: `futex_waitwhile_aboveequal()' would block
 * @return: 1: `futex_waitwhile_aboveequal()' wouldn't block */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_futex_trywaitwhile_aboveequal)(lfutex_t *uaddr,
                                                         lfutex_t above_or_equal_value) {
	return __hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) >= above_or_equal_value ? 0 : 1;
}
#include <hybrid/__atomic.h>
/* Check if `futex_waitwhile_belowequal()' would block
 * @return: 0: `futex_waitwhile_belowequal()' would block
 * @return: 1: `futex_waitwhile_belowequal()' wouldn't block */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_futex_trywaitwhile_belowequal)(lfutex_t *uaddr,
                                                         lfutex_t below_or_equal_value) {
	return __hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) <= below_or_equal_value ? 0 : 1;
}
#include <hybrid/__atomic.h>
/* Check if `futex_waitwhile_exactbits()' would block
 * @return: 0: `futex_waitwhile_exactbits()' would block
 * @return: 1: `futex_waitwhile_exactbits()' wouldn't block */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_futex_trywaitwhile_exactbits)(lfutex_t *uaddr,
                                                        lfutex_t bitmask,
                                                        lfutex_t setmask) {
	return (__hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) & bitmask) == setmask ? 0 : 1;
}
#include <hybrid/__atomic.h>
/* Check if `futex_waituntil_exactbits()' would block
 * @return: 0: `futex_waituntil_exactbits()' would block
 * @return: 1: `futex_waituntil_exactbits()' wouldn't block */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_futex_trywaituntil_exactbits)(lfutex_t *uaddr,
                                                        lfutex_t bitmask,
                                                        lfutex_t setmask) {
	return (__hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) & bitmask) != setmask ? 0 : 1;
}
#include <hybrid/__atomic.h>
/* Check if `futex_waitwhile_anybit()' would block
 * @return: 0: `futex_waitwhile_anybit()' would block
 * @return: 1: `futex_waitwhile_anybit()' wouldn't block */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_futex_trywaitwhile_anybit)(lfutex_t *uaddr,
                                                     lfutex_t bitmask) {
	return (__hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) & bitmask) != 0 ? 0 : 1;
}
#include <hybrid/__atomic.h>
/* Check if `futex_waitwhile_allbits()' would block
 * @return: 0: `futex_waitwhile_allbits()' would block
 * @return: 1: `futex_waitwhile_allbits()' wouldn't block */
INTERN ATTR_SECTION(".text.crt.sched.futex") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_futex_trywaitwhile_allbits)(lfutex_t *uaddr,
                                                      lfutex_t bitmask) {
	return (__hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) & bitmask) == bitmask ? 0 : 1;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(futex_trywaitwhile, libc_futex_trywaitwhile);
DEFINE_PUBLIC_ALIAS(futex_trywaituntil, libc_futex_trywaituntil);
DEFINE_PUBLIC_ALIAS(futex_trywaitwhile_equal, libc_futex_trywaitwhile_equal);
DEFINE_PUBLIC_ALIAS(futex_trywaitwhile_notequal, libc_futex_trywaitwhile_notequal);
DEFINE_PUBLIC_ALIAS(futex_trywaitwhile_above, libc_futex_trywaitwhile_above);
DEFINE_PUBLIC_ALIAS(futex_trywaitwhile_below, libc_futex_trywaitwhile_below);
DEFINE_PUBLIC_ALIAS(futex_trywaitwhile_aboveequal, libc_futex_trywaitwhile_aboveequal);
DEFINE_PUBLIC_ALIAS(futex_trywaitwhile_belowequal, libc_futex_trywaitwhile_belowequal);
DEFINE_PUBLIC_ALIAS(futex_trywaitwhile_exactbits, libc_futex_trywaitwhile_exactbits);
DEFINE_PUBLIC_ALIAS(futex_trywaituntil_exactbits, libc_futex_trywaituntil_exactbits);
DEFINE_PUBLIC_ALIAS(futex_trywaitwhile_anybit, libc_futex_trywaitwhile_anybit);
DEFINE_PUBLIC_ALIAS(futex_trywaitwhile_allbits, libc_futex_trywaitwhile_allbits);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_KOS_FUTEX_C */
