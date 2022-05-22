/* HASH CRC-32:0xf94a6d4a */
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
#ifndef GUARD_LIBC_AUTO_PTHREAD_NP_C
#define GUARD_LIBC_AUTO_PTHREAD_NP_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "pthread_np.h"
#include "../user/pthread.h"

DECL_BEGIN

#ifndef __KERNEL__
/* >> pthread_stackseg_np(3)
 * Convenience wrapper for `pthread_getattr_np(3)' + `pthread_attr_getstack()' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_stackseg_np)(pthread_t pthread,
                                               stack_t *sinfo) {
	errno_t result;
	pthread_attr_t attr;
	result = libc_pthread_getattr_np(pthread, &attr);
	if likely(result == 0) {
		void *stackaddr;
		size_t stacksize;
		result = libc_pthread_attr_getstack(&attr, &stackaddr, &stacksize);
		if likely(result == 0) {
			sinfo->ss_sp    = stackaddr;
			sinfo->ss_size  = stacksize;
			sinfo->ss_flags = 0;
		}

		libc_pthread_attr_destroy(&attr);

	}
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(pthread_stackseg_np, libc_pthread_stackseg_np);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PTHREAD_NP_C */
