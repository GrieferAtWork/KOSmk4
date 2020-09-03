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
#ifndef __GUARD_HYBRID___VA_SIZE_H
#define __GUARD_HYBRID___VA_SIZE_H 1

#include "../__stdinc.h"
#include "host.h"

/* __VA_SIZE: Minimal size of integral type arguments in ellipsis
 *            May be used to optimize PRI* macros from <inttypes.h>,
 *            as well as implement a more efficient `printf()' function. */
#ifndef __VA_SIZE
#if defined(__x86_64__)
/* Must still be 4 because gcc (understandably) doesn't sign-extend
 * 32-bit integers to 64 bits when passed through ellipsis. */
#define __VA_SIZE 4
#elif defined(__i386__)
#define __VA_SIZE 4
#else /* ... */
#include "typecore.h"
/* The C standard implies a minimal alignment for int-types.
 * With this in mind (and so-as not to do something wrong), assume
 * integer alignment an all other cases */
#define __VA_SIZE __SIZEOF_INT__
#endif /* !... */
#endif /* !__VA_SIZE */


#endif /* !__GUARD_HYBRID___VA_SIZE_H */
