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
#ifndef GUARD_LIBC_LIBC_TLS_H
#define GUARD_LIBC_LIBC_TLS_H 1

/* Keep this one the first */
#include "../api.h"
/**/

#ifndef __KERNEL__
#include <bits/crt/pthreadtypes.h>

#include "dl.h"

#ifdef __CC__
DECL_BEGIN

/* LIBC per-thread data instance.
 * NOTE: This _must_ be the _only_  ATTR_THREAD variable in all of  libc!
 *       If  this assumption is  violated, then `current_from_tls()' will
 *       break, as it assumes that the in-library TLS offset of `current'
 *       is equal to `0'!
 * Also: By making this be the only TLS variable, we can further minimize
 *       the   number  of  relocations   within  the  resulting  libc.so! */
INTDEF ATTR_THREAD struct pthread current;

/* Return a handle for libc.so, as would also be returned by `dlopen("libc.so")'
 * Note however that  this function  doesn't return  a new  reference to  libc's
 * shared library handle, but rather simply returns the raw handle pointer. */
#ifndef libc_handle
#ifdef LIBC_ARCH_HAVE_LIBC_HANDLE
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED void *NOTHROW(LIBCCALL libc_handle)(void);
#else /* LIBC_ARCH_HAVE_LIBC_HANDLE */
#define libc_handle() dlgethandle((void *)&libc_get_dlgethandle, DLGETHANDLE_FNORMAL)
#endif /* !LIBC_ARCH_HAVE_LIBC_HANDLE */
#endif /* !libc_handle */

/* Return a pointer to `current', given a tls_segment
 * pointer,  as   allocated  by   `dltlsallocseg(3D)' */
FORCELOCAL ATTR_PURE WUNUSED NONNULL((1))
struct pthread *LIBCCALL current_from_tls(void *tls_segment) {
	return (struct pthread *)dltlsaddr2(libc_handle(), tls_segment);
}

DECL_END
#endif /* __CC__ */
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_LIBC_TLS_H */
