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
#ifndef _BITS_OS_GENERIC_SIGSET_WITH_SIZE_H
#define _BITS_OS_GENERIC_SIGSET_WITH_SIZE_H 1

/* File:
 *    <bits/os/generic/sigset_with_size.h>
 *
 * Definitions:
 *    - struct sigset_with_size { ... };
 */

#include <__stdinc.h>

#include <bits/os/sigset.h>
#include <bits/types.h>

#define __OFFSET_SIGSET_WITH_SIZE_SIGSET  0
#define __OFFSET_SIGSET_WITH_SIZE_SIGSIZ  __SIZEOF_POINTER__
#define __SIZEOF_SIGSET_WITH_SIZE         (__SIZEOF_POINTER__ + __SIZEOF_SIZE_T__)
#define __ALIGNOF_SIGSET_WITH_SIZE        __ALIGNOF_POINTER__

#ifdef __CC__
__DECL_BEGIN

struct sigset_with_size /*[PREFIX(sws_)]*/ {
	struct __sigset_struct *sws_sigset; /* [0..sws_sigsiz] Signal set. */
	__size_t                sws_sigsiz; /* Signal set size. */
};

__DECL_END
#endif /* __CC__ */


#endif /* !_BITS_OS_GENERIC_SIGSET_WITH_SIZE_H */
