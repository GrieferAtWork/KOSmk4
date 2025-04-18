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
/*!included_by <sys/select.h>*/
#ifndef _BITS_OS_FD_SET_H
#define _BITS_OS_FD_SET_H 1

/* File:
 *    <bits/os/epoll.h>
 *
 * Definitions:
 *    - union epoll_data { ... };
 *    - struct epoll_event { ... };
 */

#include <__stdinc.h>
#include <features.h>

#include <asm/os/fd_set.h> /* __FD_SETSIZE */
#include <bits/types.h>

#define __SIZEOF_FD_MASK __SIZEOF_POINTER__
#define __SIZEOF_FD_SET  (__FD_SETSIZE / __CHAR_BIT__)
#define __NFDBITS        (__SIZEOF_FD_MASK * __CHAR_BIT__)
#define __FD_ELT(d)      ((d) / __NFDBITS)
#define __FD_MASK(d)     (__CCAST(__fd_mask)1 << ((d) % __NFDBITS))

#ifdef __CC__
__DECL_BEGIN

#define __fd_mask __intptr_t

typedef struct __fd_set_struct {
#ifdef __USE_XOPEN
	__fd_mask fds_bits[__FD_SETSIZE / __NFDBITS];
#define __FDS_BITS(set) ((set)->fds_bits)
#else /* __USE_XOPEN */
	__fd_mask __fds_bits[__FD_SETSIZE / __NFDBITS];
#define __FDS_BITS(set) ((set)->__fds_bits)
#endif /* !__USE_XOPEN */
} fd_set;

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_FD_SET_H */
