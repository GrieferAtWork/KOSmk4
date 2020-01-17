/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_SELECT_H
#define _BITS_SELECT_H 1

#include <__stdinc.h>

#ifndef __FD_SETSIZE
#define __FD_SETSIZE 1024
#endif /* !__FD_SETSIZE */

#ifndef __FD_ZERO
#define __FD_ZERO(set)                                                 \
	do {                                                               \
		__size_t __i;                                                  \
		fd_set *const __arr = (set);                                   \
		for (__i = 0; __i < sizeof(fd_set) / sizeof(__fd_mask); ++__i) \
			__FDS_BITS(__arr)                                          \
			[__i] = 0;                                                 \
	} __WHILE0
#endif /* !__FD_ZERO */

#ifndef __FD_SET
#define __FD_SET(d, set) ((void)(__FDS_BITS(set)[__FD_ELT(d)] |= __FD_MASK(d)))
#endif /* !__FD_SET */
#ifndef __FD_CLR
#define __FD_CLR(d, set) ((void)(__FDS_BITS(set)[__FD_ELT(d)] &= ~__FD_MASK(d)))
#endif /* !__FD_CLR */
#ifndef __FD_ISSET
#define __FD_ISSET(d, set) ((__FDS_BITS(set)[__FD_ELT(d)] & __FD_MASK(d)) != 0)
#endif /* !__FD_ISSET */

#endif /* !_BITS_SELECT_H */
