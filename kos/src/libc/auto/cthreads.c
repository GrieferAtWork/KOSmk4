/* HASH CRC-32:0x14302fd2 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_CTHREADS_C
#define GUARD_LIBC_AUTO_CTHREADS_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/cthreads.h"
#include "../user/pthread.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") vm_offset_t
NOTHROW_NCX(LIBCCALL libc_cthread_init)(void) {
	COMPILER_IMPURE();
	return (vm_offset_t)libc_pthread_self();
}
#include <libc/errno.h>
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") NONNULL((1)) cthread_t
NOTHROW_NCX(LIBCCALL libc_cthread_fork)(any_t (LIBCCALL *start_routine)(any_t arg),
                                        any_t arg) {
	pthread_t result;
	errno_t error;
	error = libc_pthread_create(&result, NULL, start_routine, arg);
	if unlikely(error != 0) {
		__libc_seterrno(error);
		result = (pthread_t)NULL;
	}
	return (cthread_t)result;
}
#include <bits/crt/pthreadtypes.h>
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") any_t
NOTHROW_NCX(LIBCCALL libc_cthread_join)(cthread_t self) {
	void *result;
	libc_pthread_getresult_np((pthread_t)self, &result);
	return result;
}
#include <bits/crt/pthreadtypes.h>
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") int
NOTHROW_NCX(LIBCCALL libc_cthread_abort)(cthread_t self) {
	return libc_pthread_cancel((pthread_t)self) == 0 ? 0 : -1;
}
/* >> cthread_set_limit(3)
 * No-op */
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") void
NOTHROW_NCX(LIBCCALL libc_cthread_set_limit)(int limit) {
	COMPILER_IMPURE();
	(void)limit;
}
#include <hybrid/limitcore.h>
/* >> cthread_limit(3)
 * No-op (always returns `INT_MAX') */
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") WUNUSED int
NOTHROW_NCX(LIBCCALL libc_cthread_limit)(void) {
	COMPILER_IMPURE();
	return INT_MAX;
}
#include <bits/crt/pthreadtypes.h>
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_cthread_keycreate)(cthread_key_t *key) {
	return libc_pthread_key_create((pthread_key_t *)key, NULL) == 0 ? 0 : -1;
}
#include <bits/crt/pthreadtypes.h>
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_cthread_getspecific)(cthread_key_t key,
                                               void **p_value) {
	*p_value = libc_pthread_getspecific((pthread_key_t)key);
	return 0;
}
#include <bits/crt/pthreadtypes.h>
#include <bits/types.h>
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") ATTR_ACCESS_NONE(2) int
NOTHROW_NCX(LIBCCALL libc_cthread_setspecific)(cthread_key_t key,
                                               void *value) {
	errno_t error = libc_pthread_setspecific((pthread_key_t)key, value);
	return error == 0 ? 0 : -1;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(cthread_init, libc_cthread_init);
DEFINE_PUBLIC_ALIAS(cthread_fork, libc_cthread_fork);
DEFINE_PUBLIC_ALIAS(cthread_join, libc_cthread_join);
DEFINE_PUBLIC_ALIAS(cthread_abort, libc_cthread_abort);
DEFINE_PUBLIC_ALIAS(cthread_set_limit, libc_cthread_set_limit);
DEFINE_PUBLIC_ALIAS(cthread_limit, libc_cthread_limit);
DEFINE_PUBLIC_ALIAS(cthread_keycreate, libc_cthread_keycreate);
DEFINE_PUBLIC_ALIAS(cthread_getspecific, libc_cthread_getspecific);
DEFINE_PUBLIC_ALIAS(cthread_setspecific, libc_cthread_setspecific);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_CTHREADS_C */
